#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/msg.h>
#define MAXTEXT 64
struct msgBuff {
	long int msgType;
	char text[MAXTEXT];
};
char *PATH = "/home/wooyo/IPC/lab12/ipc_consumer3";
int main() {
	int running = 0;
	struct msgBuff myId, receiveName;
	int msgid, msgToReceive = 0;
	char buffer[BUFSIZ];
	pid_t pid;
	
	msgid = msgget((key_t)1234, 0666 | IPC_CREAT);
	// 메시지큐 생성
	if ( msgid == -1 ) {
		fprintf(stderr, "메세지큐 생성 실패\n");
		return -1;
	} // 메세지큐 생성 실패
	if ( running == 0 ) {
		printf("input start >> ");
		fgets(buffer, BUFSIZ, stdin);
		if ( strncmp(buffer, "start", 5) == 0 )
			running = 1;
		else {
			printf("입력 오류!\n");
			memset(buffer, '\0', BUFSIZ);
		}
	}


	if (running == 1) {
	 	myId.msgType = 1; // 메세지 타입 지정
		sprintf(myId.text, "%d,2012136096", getpid()); // producer pid값과 학번 지정
//		strcpy(myId.text, "2012136096"); // 내 학번 지정 
		if ( msgsnd(msgid, (void *)&myId, MAXTEXT, 0) == -1) {
			// 메세지 발신하기
			fprintf(stderr, "메세지 발신 실패\n");
			return -1;
		}
		pid = fork(); // 자식 프로세스 생성
 		if ( pid < 0 ) {
			printf("fork Failed\n");
			return -1;
		} // 자식 생성 실패
		else if ( pid == 0 ) { // 자식 프로세스에서 연산
			execl(PATH, "ipc_consumer3", NULL, NULL);
			printf("execl Failed\n");
		}
		else { // 부모 프로세스에서 연산
			sleep(3);
			if ( msgrcv(msgid, (void *)&receiveName, MAXTEXT, msgToReceive, 0) == -1) {
				fprintf(stderr, "메세지 수신 실패\n");
				return -1;
			} // 메세지 수신 실패
			printf("Consumer->Producer :: %s,", receiveName.text);
			printf("%s\n", myId.text);	
		}
	}
	return 0;
}
