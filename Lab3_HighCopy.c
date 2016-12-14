#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
// HighLevel 파일 처리 함수를 이용한 Copy 에서는 
//  stdio.h에 있는 표준 IO 라이브러리 함수들을 이용한다.

const int TIMEINTERVAL = 2;
const int NAMESIZE =50;
int main(int argc, char *argv[]) { 
	FILE *in, *out;
	char fname_in[NAMESIZE],fname_out[NAMESIZE];
	// 각각 복사할 파일 이름, 복사당할 파일 이름
	char c[64]; // 64byte씩 받아오기
	time_t time1, time2;
	int temp = 0;

	if (argc != 3 ) {
		printf("Please Write that:HighCopy [inFile] [outFile] shape\n");
		exit(1);
	}

	if (strlen(argv[1]) > NAMESIZE || strlen(argv[2]) > NAMESIZE ) {
		printf("Please Write filename below 50\n");
		exit(1);
	}
	
	strcpy(fname_in, argv[1]);
	strcpy(fname_out, argv[2]);

	if ( (in = fopen(fname_in, "r")) == NULL) {
		printf("Cannot open the Read file\n");
		exit(1);
	} // 복사할 파일을 열 때 오류가 나면 출력한다.

	if ( (out = fopen(fname_out, "w")) == NULL ) { 
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
	printf("%s -> %s \n",fname_in, fname_out);
	printf("파일 복사 완료!!");

	exit(0);
}
