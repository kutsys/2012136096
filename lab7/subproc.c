#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
int count = 0;
int test_funct() {
	time_t locTime; // 현재 시각을 불러오기 위한 연산
	struct tm *t;
	long seed = getpid() + count; // seed값 임의지정, 모든 프로세스가 다른 랜덤값을 갖도록
	srand(seed);
	int r = rand()%10; // sleep 할 r 지정(0부터 10까지)

	locTime = time(NULL); // 초 단위로 현재시각 얻기
	t = localtime(&locTime); // 초 단위 시간을 분리, 구조체에 넣어누기

	sleep(r);
	printf("pid :: %d, count :: %d, ", getpid(), count);
	printf("localTime :: %4d년 %2d월 %2d일 %2d시 %2d분 %2d초\n",
		 t->tm_year+1900, t->tm_mon+1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);
	return ++count;
}
int main() {
	while (test_funct() <= 20) {
	 // test_funct 호출 하면서 횟수까지 반환, 20회 넘어가면 종료하도록
		if (test_funct() == 20) break;
	}
	return 0;
}
