#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 20

char *PATH = "/home/wooyo/IPC/lab10/ipc_consumer";
char *PIPEPATH = "./fifo";  // named pipe 경로

int main() {
	char number[] = "2012136096";
	char name[SIZE];
	char readBuf[SIZE], writeBuf[SIZE];
	char pidBuf[SIZE]; // pid를 문자열로 전달할 변수
	int fp_r, fp_w; // filePointer read,write
	pid_t pid;
	int running = 0;
	char buffer[BUFSIZ]; //최초 start 받는 버퍼
	int res;
	while ( running == 0 ) {
		printf("Input start Text >> ");
		fgets(buffer, BUFSIZ, stdin);
		if ( strncmp(buffer, "start", 5) == 0 ) {
			running = 1;
			break;
		}
		else {
			printf("입력 오류 \n");
			memset(buffer, '\0', BUFSIZ);
		}	
	}
/*	
	res = mkfifo(PIPEPATH, 0666);
	if ( res != 0 ) {
		printf("fifo Error\n");
		return -1;
	} // fifo 파일 생성 실패
*/	
	if ( (fp_r = open(PIPEPATH, O_RDONLY)) < 0 || 
		(fp_w = open(PIPEPATH, O_WRONLY)) < 0 ) {
		printf("named Pipe open Error\n");
		return -1;
	} // 파이프 생성 실패

	memset(readBuf, '\0', SIZE);
	memset(writeBuf, '\0', SIZE);
	printf("aaa");	
	pid = fork(); 
	
	if ( pid < 0 ) {
		printf("fork Error\n");
		return -1;
	}
	if ( pid == 0 ) {
		execl(PATH, "ipc_consumer", NULL, NULL);
		printf("execl Error\n");
	} // 자식 프로세스
	else { // pid > 0 , 부모프로세스
		// 파이프에 쓰기 연산
		sprintf(pidBuf, "%d", getpid());
		 // 부모의 피드값 string으로 저장
		write(fp_w, number, SIZE);
		write(fp_w, pidBuf, SIZE); // 부모 피드값 쓰기
		sleep(1);
	}
	close(fp_w);
	// 쓰기 파이프 닫고

	// 파이프를 통해 자식프로세스에서 온거 읽기 연산
	read(fp_r, readBuf, SIZE);
	strcpy(name, readBuf);
	read(fp_r, readBuf, SIZE);
	strcpy(pidBuf, readBuf);
	printf("consumer -> producer ::  %s,%s,",  pidBuf, name);
	printf("%s,%d\n", number, getpid());
	close(fp_r);
	return 0;
}
