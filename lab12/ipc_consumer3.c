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
int main() {
	int running = 1;
	int msgid, i;
	char receive[BUFSIZ];
	struct msgBuff myName, receiveId;
	int msgToReceive = 0;
	char *myId;

	msgid = msgget((key_t)1234, 0666 |IPC_CREAT);
	// 메세지큐 생성
	if ( msgid == -1 ) {
		fprintf(stderr, "메세지큐 생성 실패\n");
		return -1;
	} // 메세지큐 생성 실패
	
	if (running == 1) {
		if ( msgrcv(msgid, (void *)&receiveId, BUFSIZ, msgToReceive, 0) == -1 ) {
			// 메세지큐 수신
			fprintf(stderr, "메세지 수신 실패\n");
			return -1;
		}
		printf("Producer->Consumer :: %s\n", receiveId.text);
		running = 2;
		// 메세지 발신으로 이동
	}

	if (running == 2) {
		myId = strtok(receiveId.text, ", ");
		myName.msgType = 1;
		sprintf(myName.text, "%d,wooyo", getpid());
//		strcpy(myName.text, "wooyo"); // 내 이름 지정
		if ( msgsnd(msgid, (void *)&myName, MAXTEXT, 0) == -1) {
			// 메세지 발신하기 
			fprintf(stderr, "메세지 발신 실패\n");
			return -1;
		} // 메세지 발신 실패
	}
/*
	if (msgctl(msgid, IPC_RMID, 0) == -1) {
		fprintf(stderr, "메세지 삭제 완료\n");
		return -1;
	}
*/
	// 메세지 대기열 삭제 연산
	return 0;
}
