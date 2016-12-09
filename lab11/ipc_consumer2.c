#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/shm.h>
char *PATH = "/home/wooyo/IPC/ipc_producer2";
int main(int argc, char *argv[]) {
	const int IDLENGTH = 12;
	int i = 0, prodPid;
	char *shared_memory;
	char *shared_stuff;
	char *myName, myId[IDLENGTH];
	int shmid;
	int consumerPid;
	pid_t pid;

//	sscanf(argv[1], "%d", &prodPid);

	shmid = shmget((key_t)1234, 20 , 0666 | IPC_CREAT); // 공유 메모리 생성
	if ( shmid < 0 ) {
		fprintf(stderr, "shmget failed\n");
		return -1;
	} // 공유메모리 생성 실패

	shared_memory = shmat(shmid, NULL , 0);
	if ( shared_memory == (void *)-1 ) {
		fprintf(stderr, "shmat failed\n");
		return -1;
	}

	// printf("생성된 공유메모리 주소 :: %X\n", (int)shared_memory);
	
	//printf("ipc_consumer2에서.. \n");
	printf("producer -> consumer :: ");
	for ( shared_stuff = shared_memory ; *shared_stuff != NULL ; shared_stuff++) {
		// 공유메모리를 참조한 곳을 shared_stuff가 받아서 가리키는 곳의 끝까지
		putchar(*shared_stuff);
		if ( *shared_stuff == ',' || ( (i > 0) && (i <= 12) ) ) { // 열두자리의  학번 추출
			myId[i++ - 1] = *shared_stuff; // myId에다가 필요한 정보들을 쏙쏙 넣음
		}
	}
	putchar('\n');
	*shared_memory = '*';

	sleep(1);
	myName = shared_memory; // shared_memory의 포인터를 myName으로 일단 지정
// 	sprintf(myName, "%d,producerPid:%d,%s,wooyo", getpid(), prodPid, myId);
	sprintf(myName, "%d,%s,wooyo", getpid(), myId);
	myName = NULL;
	
	// 공유메모리 삭제
	if (shmdt(shared_memory) == -1) {
		fprintf(stderr, "shmdt failed\n");
		return -1;
	} //공유메모리 삭제 실패
	exit(0);
	return 0;
}

