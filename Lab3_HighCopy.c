#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
// HighLevel 파일 처리 함수를 이용한 Copy 에서는 
//  stdio.h에 있는 표준 IO 라이브러리 함수들을 이용한다.

const int TIMEINTERVAL = 2;

int main() { // 여기서는 인자를 넣지 않고 직접 파일을 지정하였다.
	FILE *in, *out;
	char c[64]; // 64byte씩 받아오기
	time_t time1, time2;
	int temp = 0;
	// 복사당할 파일은 test.mp4, 복사해서 생성할 파일은 test.out으로 쓰겠다.
	if ( (in = fopen("test.mp4", "r")) == NULL) {
		printf("Cannot open the Read file\n");
		exit(1);
	} // 복사할 파일을 열 때 오류가 나면 출력한다.

	if ( (out = fopen("file.out", "w")) == NULL ) { 
		printf("Cannot Open  the  Write file\n");
		exit(1);
	} // 복사를 당할  파일을 열 때  오류가 나면 오류를 출력한다.
	
	time(&time1);	
	while((temp = fread(c, sizeof(char), sizeof(c)/sizeof(char), in)) >0) {
		time(&time2);
		fwrite(c, sizeof(char), temp, out);
		if ((time2 - time1) ==  1) {
			printf("*\n");
			sleep(1);
			time2 = time1;
		}
	}	

	fclose(in);
	fclose(out);
	//파일 닫기
	printf("%s -> %s \n","test.mp4", "test.out");
	printf("파일 복사 완료!!");

	exit(0);
}
