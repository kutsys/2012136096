#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

char SOCKETNAME[10] = "SOCKET";
typedef struct Data {
	char myName[10];
	char myId[12];
	int pid;
}Data;

int main() {
	int fd;
	int sockfd, len, result;
	struct sockaddr_un address;
	pid_t pid;	
	Data data;
	
	// consumer쪽 소켓 생성
	sockfd = socket(AF_UNIX, SOCK_STREAM, 0);

	// producer쪽 소켓 이름 지정하기	
	address.sun_family = AF_UNIX;
	strcpy(address.sun_path, SOCKETNAME);
	len = sizeof(address);

	// consumer-producer 소켓 연결
	result = connect(sockfd, (struct sockaddr *)&address, len);
	if(result == -1) {
		perror("consumer connect error.\n");
		return -1;
	}

	read(sockfd, &data, sizeof(data));
	printf("ipc_consumer4 에서 ..\n");
	printf("producer -> consumer :: %d,%s\n", data.pid, data.myId);
	
	data.pid = getpid();
	strcpy(data.myName, "wooyo");	

	write(sockfd, &data, sizeof(data));
	close(sockfd);
	return 1;
}
