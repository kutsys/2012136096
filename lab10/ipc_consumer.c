#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 20

char *PIPEPATH = "./fifo";  // named pipe 경로
typedef struct Data{
	char myId[13];
	char myName[10];
	int pid;
}Data;

int main() {
	int fp_r, fp_w; // filePointer read,write
	pid_t pid;
	Data data;
	int res;
	if (access(PIPEPATH, F_OK) == -1) {
		res = mkfifo(PIPEPATH, 0777);
		if ( res == -1 ) {
			printf("fifo Error\n");
			return -1;
		}
	}
	
	// 파이프로부터 읽어오기
	fp_r = open(PIPEPATH, O_RDONLY);
	read(fp_r, &data, sizeof(data));
	printf("ipc_consumer에서 .. \n");
	printf("producer -> consumer :: %d,%s\n", data.pid, data.myId);
	close(fp_r);
	
	sleep(1);
	// 파이프에 쓰기
	fp_w = open(PIPEPATH, O_WRONLY); 
	data.pid = getpid();
	strcpy(data.myName, "wooyo");
	// 데이터 지정
	write(fp_w, &data, sizeof(data));
	close(fp_w);
	return 0;
}
