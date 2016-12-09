#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 20

char *PIPEPATH = "./fifo";  // named pipe 경로

int main() {
	char number[SIZE]; 
	char name[] = "wooyo";
	char readBuf[SIZE], writeBuf[SIZE];
	char pidBuf[SIZE]; // pid를 문자열로 전달할 변수
	int fp_r, fp_w; // filePointer read,write
	pid_t pid;
/*
	if ( mkfifo(PIPENAME, 0666 != 0 ) {
		printf("fifo Error\n");
		return -1;
	} // fifo 생성 실패
*/
	if ( (fp_r = open(PIPEPATH, O_RDONLY)) < 0 || 
		(fp_w = open(PIPEPATH, O_WRONLY)) < 0 ) {
		printf("named Pipe open Error\n");
		return -1;
	} // 파이프 생성 실패

	memset(readBuf, '\0' , SIZE);
	memset(writeBuf, '\0', SIZE);
	
	// 파이프로부터 읽어오기
	read(fp_r, readBuf, SIZE);
	strcpy(number, readBuf);
	read(fp_r, readBuf, SIZE);
	strcpy(pidBuf, readBuf);
	printf("producer -> consumer :: %s,%s\n", number, pidBuf);
	close(fp_r);

	// 파이프에 쓰기
	sprintf(pidBuf, "%d", getpid());
	write(fp_w, name, SIZE);
	write(fp_w, pidBuf, SIZE);
	close(fp_w);
	return 0;
}
