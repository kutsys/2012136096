#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

int main(void) {
	int setenvChecking = 0; // setenv함수 수행 후 결과를 받을 변수
	// 1. getenv() 함수를 사용해서 각각의 환경변수에 설정된 값을 화면에 표시하기
	printf("$HOME = %s\n", getenv("HOME")); // echo $HOME
	printf("$PS1 = %s\n", getenv("PS1")); // echo $PS1
	printf("$PATH = %s\n", getenv("PATH")); // echo $PATH
	printf("$LD_LIBRARY_PATH = %s\n", getenv("LD_LIBRARY_PATH")); // echo LD_LIBRARY_PATH

	// 2. setenv() 함수를 사용해서 $TEST_ENV 라는 환경변수를 정의하고
	// 그 값을 1234로 설정한다.
	setenvChecking = setenv("TEST_ENV", "1234", 1); // setenv(환경변수이름, 변수값, 이미 같은 이름이 있다면 값을 변경할 지의 여부
	printf("환경변수 TEST_ENV 생성 및 값 정의한 것 출력 :: \n");
	printf("$TEST_ENV = %s\n", getenv("TEST_ENV"));
	if ( setenvChecking < 0) printf("setEnv error\n");
	return 0;
} 
