#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

void *threadFunction(void *arg);
int main() {
	const int TOTALTHREAD = 10; //총 쓰레드 갯수
	int res = 0;
	pthread_t a_thread[TOTALTHREAD]; //TOTALTHREAD만큼 쓰레드 선언
	int *threadResult;	

	printf("2012136096 이우용\n"); // 학번, 이름 출력

	// 쓰레드 여러개 생성 연산
	for ( int i = 0 ; i < TOTALTHREAD ; i++ ) {	
		res = pthread_create(&(a_thread[i]), NULL, &threadFunction, (void *)i);
		printf("쓰레드 %d 생성\n", i);
		if (res != 0) {
			printf("Thread Creation Failed\n");
			return -1;
		} // 쓰레드 생성 실패 시
	}
	
	sleep(3);
	// 쓰레드 여러개 종료 연산
	for ( int i = TOTALTHREAD - 1 ; i >= 0 ; i-- ) {
		res = pthread_join(a_thread[i], (void **)&threadResult);
		printf("쓰레드 %d 종료\n", i);
		if (res != 0) {
			printf("Thread Join Failed\n");
			return -1;
		}
	}
	printf("Finished (Thread)\n");

	return 0;
}

void *threadFunction(void *arg) {
	int count = 0;
	int r = 0;
	int num =(int *)arg;
	time_t locTime;
	struct tm *t; // 시간 구조체 포인터 생성

	while ( count++ <= 20 ) {
		if ( count == 20 ) { // 카운트 20 세고나서
			printf("Thread Exit\n");
			break;
		} 

		long seed = rand()%1000 + 1;
		srand(seed); // 임의의 seed값 할당
		r = rand() % 10;	
	
		// 시간 출력 연산
		locTime = time(NULL);
		t = localtime(&locTime);

		sleep(r);
		printf("Thread No. :: %2d, count :: %d, ", num+1, count);
		printf("localTime :: %4d년 %2d월 %2d일 %2d시 %2d분 %2d초\n", t->tm_year+1900, t->tm_mon+1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);
	}
	pthread_exit(NULL);
}
