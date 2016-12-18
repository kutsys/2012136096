#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

char SOCKETNAME[10] = "SOCKET"; 
typedef struct Data {
	char myName[10];
	char myId[12];
	int pid;
}Data;

int main(){
	int res, fd;
	pid_t pid;
	Data data;
	char buffer[BUFSIZ];
	int running = 0;
	int producer_sockfd, consumer_sockfd;
	int producer_len, consumer_len;
	struct sockaddr_un producer_address, consumer_address;

	memset(buffer, '\0', BUFSIZ);
	while ( running == 0 ) {
		printf("Input some Text >> ");
		fgets(buffer, BUFSIZ, stdin);
		if ( strncmp(buffer, "start", 5) == 0) {
			running = 1;
			break;
		}
		else
			printf("입력 오류 \n");
		memset(buffer, '\0', BUFSIZ);
	}
	
	pid = fork();
	if ( running == 1 ) {
		if (pid == -1) {
			printf("Fork error.!!\n");
			return -1;
		}
		if (pid == 0) {	
			execl("./ipc_consumer4", "ipc_consumer4",NULL,  NULL);
			printf("execl failed!!\n");
		}
		else {
			// 기존에 만들어진 소켓 삭제 및 소켓 생성
			unlink(SOCKETNAME);
			producer_sockfd = socket(AF_UNIX,SOCK_STREAM, 0);

			// 소켓에 이름 부여
			producer_address.sun_family = AF_UNIX; // 유닉스용 소켓
			strcpy(producer_address.sun_path, SOCKETNAME);
			producer_len = sizeof(producer_address);
			bind(producer_sockfd, (struct sockaddr *)&producer_address, producer_len);
		}
	}
	
	// 연결 대기열 생성, consumer의 요청을 기다림
	listen(producer_sockfd, 5);

	consumer_len = sizeof(consumer_address);
	consumer_sockfd = accept(producer_sockfd, (struct sockaddr *)&consumer_address, &consumer_len);

	data.pid = getpid();
	strcpy(data.myId, "2012136096");

	// consumer_sockfd를 이용한 clienct와 자료 주고 받기
	write(consumer_sockfd, &data, sizeof(data));
	sleep(2);	
	read(consumer_sockfd, &data, sizeof(data));
	close(consumer_sockfd);

	printf("ipc_producer4 에서.. \n");
	printf("consumer->producer :: %d,%s\n", data.pid, data.myName);
	printf("                      %d,%s\n", getpid(), data.myId);		
			
	return 0;
}
