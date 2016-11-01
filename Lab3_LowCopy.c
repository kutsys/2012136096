#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
const int NAMESIZE = 50;
const int TIMEINTERVAL = 2; // 실제로 몇 초가 지난 후에 .을 찍어내는지
 
int main(int argc, char *argv[]) {
	char fname_in[NAMESIZE],fname_out[NAMESIZE];
	 // 각각 복사할 파일 이름, 복사당할  파일 이름
	int in, out;
	char buf[64]; // 64byte씩 전송을 위한 버퍼
	time_t time1, time2;
	
	// 명령어의 인자가 3이 아닌경우 조건에 맞지 않음
	// 실행파일 + in파일 + out파일 : 3개의 인자가 필수적임
	if (argc != 3) {
		printf("Please Write that:LowCopy [inFile] [outFile] shape\n");
		exit(1);
	}

	// 파일의 길이가 설정한 NAMESIZE값 보다 클 경우
	// strlen 함수를 이용하여 파라미터로 들어온 파일이름 검사
	if (strlen(argv[1]) > NAMESIZE || strlen(argv[2]) > NAMESIZE ) {
		printf("Please Write filename below 50\n");
		exit(1);
	}

	strcpy(fname_in, argv[1]);
	strcpy(fname_out, argv[2]);

	in = open(fname_in, O_RDONLY);
	//  in에다가 fname_in을 읽기전용으로 열고 난 파일 서술자를 반환한다.
	// in은 fname_in 파일에 대한 파일 디스크립터다.
	if ( in < 0 ) { 
		printf("Cannot open the file\n");
		exit(1);
	} // 파일 읽기에 오류가 나면 오류를 출력한다.

	out = open(fname_out, O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR);
	// fname_out을 쓰기로 열고, 생성옵션까지 추가하였다.
	// 추가적으로 소유자에게 읽기와 쓰기 권한을 주도록 지정하였다.
	// out은 fname_out 파일에 대한 파일 디스크립터다.
	if ( out < 0 ) {
		printf("Cannot Write the file\n");
		exit(1);
	} // 파일 쓰기에 오류가 나면 출력한다.

	// fname_in에서 fname_out으로 8byte씩 복사케 한다.
	time(&time1);	
	while (read(in, buf, sizeof(buf)) > 0) {
		time(&time2); //time2 설정, 8바이트씩 파일을 복사할 때 마다
		write(out, buf, sizeof(buf));
		if ( (time2 - time1) % TIMEINTERVAL== 1 ) {
			printf(".\n"); // 파일 복사 수행에  1초마다 한번씩 .찍기
			sleep(1);
		}
	}
	printf("%s -> %s \n", fname_in, fname_out);
	printf("파일 복사 완료!!\n");
	exit(0);	
}
