//HighCopy.c

#include <unistd.h> // sleep함수를 사용하기 위함
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

const int TIMESIZE = 3000; // 실제로 몇 초가 지난 후에 .을 찍어 ㅐ는가를 결정할 변수

int main() { // 여기서는 인자를 넣지 않고 파일 내부에 직접 지정하였다.
	File *in *out;
	char c[64]; // 64byte씩 받아오기 위한 c
	time_t time1, time2; // time변수 정의
	int temp = 0; // read, write에 결과 반환값으로 선언한 temp변수
	
	// 복사당할 파일은 test.mp4, 복사해서 생성할 파일은 test.out
	if ( (in = fopen("test.mp4", "r")) == NULL) { // 읽기모드로 연다
		printf("Cannot open the Read File\n");
		exit(1);
	} // 파일이 없으면 오류를 출력한다.

	if ( (out = fopen("test.out", "w")) == NULL) { // 쓰기모드로 연다.
		printf("Cannot open the Write File\n");
		exit(1);
	} // 파일이 없으면 오류를 출력한다.

	while ((temp = fread(c, sizeof(char), sizeof(c)/sizeof(char), in)) >0 {
	// 파일을 64byte짜리 문자열타입을 이용하여 이 단위로 계속 읽어나간다.
		time(&time2);
		fwrite(c, sizeof(char), temp, out); // 파일 쓰기연산을 한다.
		if ((time2 - time1) == 1 ) {
			printf("*\n");
			sleep(1); // 1초마다 *문자를 찍는다.
		}
	}
	printf("%s -> %s \n", "test.mp4", "test.out");
	printf("파일 복사 완료!!\n");
	exit(0);
}
