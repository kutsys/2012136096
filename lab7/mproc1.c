#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int killCount = 0;
char *PATH= "/home/wooyo/MultiProcess/subproc";
void childKill(int sig) {
	int status;
	pid_t pid;
	while ( (pid = waitpid(-1, &status, WNOHANG)) > 0) {
		printf("Child %d Exit!!\n", pid);
		killCount++;
	}
}
int main() {
	int TOTALPROCESS = 10; //총 프로세스 갯수
	pid_t pid[TOTALPROCESS];
	printf("2012136096 이우용\n"); // 학번, 이름 출력
//	signal(SIGCHLD, (void *)childKill);
	
	printf("parent process : %ld\n", (long)getpid());
	for ( int i = 0 ; i < TOTALPROCESS ; i++ ) {
		// 10개의 프로세스 생성하는 연산
		pid[i] = fork(); // fork생성 연산
		if (pid[i] < 0) {
			printf("fork생성 실패\n");
			return -1;
		} // fork연산 실패 시
		else if ( pid[i] == 0 ) {
			sleep(3);
			printf("child process : %ld\n", (long)getpid());
			execl(PATH, "subproc", NULL, NULL); // subproc 생성, 부모pid 인자로 넘겨봄
			printf("execl Error\n");
			return -1;
		} // 자식 프로세스
		else {
		} // 부모 프로세스
	}
	// 모든 프로세스 종료 시
	for (int i = 0 ; i < TOTALPROCESS ; i++ ) {
		wait(&pid[i]);
	}
	printf("Finished (Process)!\n");
	return 0;
}
