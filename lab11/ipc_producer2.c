#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/shm.h>

char* PATH = "/home/wooyo/IPC/lab11/ipc_consumer2";
int main() {
	int running = 0;	
	char *shared_memory;
	char *myId; 
	char *shared_stuff;	
	char buffer[BUFSIZ];
	int shmid;
	int producerPid;
	pid_t pid;

	shmid = shmget((key_t)1234, 20, 0666 | IPC_CREAT);  // 공유메모리 생성
	if ( shmid < 0 ) {
		fprintf(stderr, "shmget failed\n");
		return -1;
	} // 공유메모리 생성  실패 시
	
	shared_memory = shmat(shmid, NULL, 0);
	// 공유메모리 접속, 읽기/쓰기 모드로 생성
	if (shared_memory == -1) {
		fprintf(stderr, "shmat failed\n");
		return -1;
	} // 공유메모리 접속 실패
	
	// 표준 입력을 받아서 start 나오면 실행
	memset(buffer, '\0', BUFSIZ);
	producerPid = getpid();
	if ( running == 0 ) {
		printf("Input some Text >> ");
		fgets(buffer, BUFSIZ, stdin);
		if ( strncmp(buffer, "start", 5) == 0 ) {
			running = 1;
		}
		else 
			printf("입력 오류\n");
		memset(buffer, '\0', BUFSIZ);
	}

	pid = fork(); // 자식 프로세스 생성
	if ( running == 1 ) {
		if (pid == -1) {
			printf("fork Failed!\n");
			return -1;
		}
		else if ( pid == 0 ) { // 자식 프로세스 에서
			myId = shared_memory; // myId 포인터를 공유메모리에 연결
			sprintf(myId, "%d,2012136096", producerPid);
			// myId에 producer pid값이랑 학번 집어넣음
			execl(PATH, "ipc_consumer2", NULL, NULL); // 실행파일 이름 넘기구
			printf("execl failed\n");
		}
		else { // 부모프로세스에서의 처리
			sleep(2);
			printf("ipc_producer2에서.. \n");
			printf("consumer -> producer :: ");
			for ( shared_stuff = shared_memory ; *shared_stuff != NULL ; shared_stuff++ ) {
				putchar(*shared_stuff);
			}
		}
		printf(",%d\n", getpid());
	}
	
	*shared_memory = '*';
	
	myId = NULL; // myId 해제
	// 공유메모리 해제
	if ( shmdt(shared_memory) == -1 ) {
		fprintf(stderr, "shmdt failed\n");
		return -1;
	} // 공유메모리 해제 실패
	exit(0);
	return 0;
}
