#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <semaphore.h>

#define TOTALTHREAD 10 //총 쓰레드 갯수, 쓰레드 함수에서도 쓰므로 전역으로 옮김
void *threadFunction(void *arg);

void initCompleteCount();
int compareThreadCount(int cnt); 
int minimumCount();

sem_t bin_sem; // 세마포 변수 선언
int thCount[TOTALTHREAD]; // [쓰레드의 일련변호], count 출력이 끝난 쓰레드의 배열값  1, 그렇지 않으면 0
int main() {
	int res = 0;
	pthread_t a_thread[TOTALTHREAD]; //TOTALTHREAD만큼 쓰레드 선언
	int *threadResult;	

	printf("2012136096 이우용\n"); // 학번, 이름 출력

	// 세마포 초기값 0으로 설정, 현재 프로세스에서만 유효한 세마포 생성
	res = sem_init(&bin_sem, 0, 0);
	if (res != 0) { 
		printf("Semaphore Error!!\n");
	 	return -1;
	} // 세마포 생성 실패 시
	
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
	sem_post(&bin_sem);
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
	int count = 0, complete = 0;
	int r = 0;
	int running = 0;
	int num =(int *)arg; // thread의 일련번호
	time_t locTime;
	struct tm *t; // 시간 구조체 포인터 생성

	initCompleteCount();
	sem_wait(&bin_sem); // 프로세스 수행 전에 일단 자원 0으로
	while ( 1 ) {
		if ( count == 20 ) { // 카운트 20 세고나서
			printf("Thread Exit\n");
			break;
		} 

		if ( count == minimumCount() && complete == 0 ) { // totalCount에 도달할 때 까지
			long seed = rand()%1000 + 1;
			srand(seed); // 임의의 seed값 할당
			r = rand() % 10;	
	
			// 시간 추출 연산
			locTime = time(NULL);
			t = localtime(&locTime);

			// 정보 출력 및 0~9초간 대기
			printf("num :: %2d, count :: %d, ", num+1, count);
			printf("localTime :: %4d년 %2d월 %2d일 %2d시 %2d분 %2d초\n",
			 t->tm_year+1900, t->tm_mon+1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);

			thCount[num]++; // 하나의 쓰레드가 count 출력을 완료하면 하나씩 증가
			sem_post(&bin_sem); // 세마포아 대기모드 	
			complete = 1; // 한타임 완료 시 complete 1로 만들어 주고
			sleep(r);
		}
		else {
			sem_post(&bin_sem); // 세마포아 
			sleep(1);
			// printf("num :: %d 대기중..%d \n", num+1, thCount[num]);
		}

		if ( compareThreadCount(count) ) { // count 한개 올려주는 연산
			sem_wait(&bin_sem); // 프로세스 수행 전에 일단 자원 0으로
			count++;
			complete = 0; // complete 초기화
			sleep(1);
		}
	} 
	pthread_exit(NULL);
}

void initCompleteCount() {
	int i;
	for ( i = 0 ; i < TOTALTHREAD; i++ )
		thCount[i] = 0;
}

int compareThreadCount(int cnt) {
 // 해당 count값과 Thread 일련번호 배열인자 확인, 겹치는거 없으면 프로세스 계속 진행해게끔
	int i, check = 0;
	for ( i = 0 ; i < TOTALTHREAD ; i++ ) {
		if ( thCount[i] == cnt )
			check++;
	}
	if ( check == 0 )
		return 1;
	else
		return 0;	
}

int minimumCount() { // Thread일련번호 배열에서 최소 count 얻어내기
	int i, min = 0;
	for ( i = 0 ; i < TOTALTHREAD ; i++ ) {
		if ( thCount[min] > thCount[i] )
			min = i;
	}
	return thCount[min];
}
