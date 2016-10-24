// pmon.c

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
const char *path = "/home/wooyo/processMtr/ptest"; // 파일의 경로 설정

pid_t excuteChild(pid_t pid, char* exec) { // pid값과 실행파일 명령을 받아오도록
	pid = fork(); // 자식프로세스 생성 및 PID 할당
	if ( pid == -1 ) // fork 에러
		exit(1);
	if ( pid == 0 ) // 성공적으로 생성 되었을 경우
		execl(path, exec, NULL, NULL); // path에 따른 새로운 프로세스(exec)를 띄움
	return pid;
}

int main(void) {
	pid_t pid;
	char command; //사용자 입력받을 커맨드
	
	pid = fork();
	if ( pid == -1 ) {
		printf("Fork Error!\n");
		exit(1);
	} // fork에 에러가 발생할 경우 pmon 강제종료
	
	if ( pid == 0 ) // 자식프로세스 생성 
		execl(path, "ptest", NULL, NULL);
	
	else { // 부모프로세스 계속 실행중
		printf("Parent Process Excute!\n");		
		printf("Please Input Q, K, S, R \n ");
		while ( 1 ) {
			printf("%ld\n", pid);
			if ( pid >= 0 ) printf("running!\n");
			else printf("not existed\n");			

			printf(" >> ");
			scanf("%c", &command); 			
			switch (command) {
			case 'Q' : // pmon 종료
				printf("Quit pmon!!\n");
				if ( pid >= 0 ) // 자식프로세스를 제거한 후
					kill(pid, SIGKILL);
				sleep(2); // 신호 대기시간을 충분히 주기 위함
				exit(1); // 프로그램 종료
			
			case 'K' : // ptest 종료
				printf("Kill ptest!!\n");
				if ( pid >= 0 )
					kill(pid, SIGKILL);
				pid = -2;
				break;
			
			case 'S' : // ptest 실행
				if ( pid >= 0 )  // 이미 자식프로세스가 살아있는 경우
					printf("Already running!!\n");
				else { // 그렇지 않을 경우 살리기
					pid = excuteChild(pid, "ptest");
					printf("ptest excute!\n");
				}
				break;
			
			case 'R' : // ptest를 종료 후 재실행
				if ( pid < 0 ) // 자식프로세스가 없는 경우
					printf("newly started!!\n");
				else { // 있는 경우
					kill(pid, SIGKILL);
					pid = -2;
				}
				pid = excuteChild(pid, "ptest");
				break;
			}
			printf("%d!\n", pid);
			sleep(5);
		}
	}
	return 0;
}