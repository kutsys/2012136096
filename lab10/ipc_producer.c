#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 20

char *PATH = "/home/wooyo/IPC/lab10/ipc_consumer";
char *PIPEPATH = "./fifo";  // named pipe 경로
typedef struct Data{
	char myId[13];
	char myName[10];
	int pid;
}Data;

int main() {
	char pidBuf[SIZE]; // pid를 문자열로 전달할 변수
	int fp_r, fp_w; // filePointer read,write
	pid_t pid;
	int running = 0;
	char buffer[BUFSIZ]; //최초 start 받는 버퍼
	int res;
	Data data;
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
	
	if (access(PIPEPATH, F_OK) == -1) {	
		res = mkfifo(PIPEPATH, 0777);
		if ( res == -1 ) {
			printf("fifo Error\n");
			return -1;
		} // fifo 파일 생성 실패
	}

	pid = fork(); 
	if ( running == 1 ) { 
		if ( pid < 0 ) {
			printf("fork Error\n");
			return -1;
		}
		if ( pid == 0 ) {
			execl("./ipc_consumer" , "ipc_consumer", NULL, NULL);
			printf("execl Error\n");
		} // 자식 프로세스
		else { //  부모프로세스
			data.pid = getpid();
			strcpy(data.myId, "2012136096"); // 쓸 데이터 지정 후, write	
			fp_w = open(PIPEPATH, O_WRONLY); // 파이프에 쓰기 연산
			write(fp_w, &data, sizeof(data));
			close(fp_w); // 쓰기 파이프 닫고
		}
	}
	// 파이프를 통해 자식프로세스에서 온거 읽기 연산
	fp_r = open(PIPEPATH, O_RDONLY);
	read(fp_r, &data, sizeof(data));
	close(fp_r);

	printf("\nipc_producer 에서..\n");	
	printf("consumer -> producer ::  %d,%s\n", data.pid, data.myName);
	printf("                         %d,%s\n", getpid(), data.myId);
	return 0;
}
