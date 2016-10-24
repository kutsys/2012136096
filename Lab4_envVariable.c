//envVariable.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
	int setenvChecking = 0; // setenv함수 수행 후 결과를 받을 변수
	// 1. getenv() 함수를 사용해서 각각의 환경변수에 설정된 값을 화면에 표시하기
	printf("$HOME = %s\n", get("HOME")); // echo $HOME
	printf("$PS1 = %s\n", get("PS1")); // echo $PS1
	printf("$PATH = %s\n", get("PATH")); // echo $PATH
	printf("$LD_LIBRARY_PATH = %s\n", get("LD_LIBRARY_PATH")); // echo $LD_LIBRARY_PATH

	// 2. setenv() 함수를 사용해서 $TEST_ENV 라는 환경변수를 정의하고
	// 그 값을 1234로 정의한다.
	setenvChecking = setenv("TEST_ENV", "1234", 1);
	// setenv(환경변수이름, 변수값, 이미 같은 이름이 있다면 값을 변경할 지의 여부
	if (setenvChecking < 0) printf("setenv\5517
	return 0;
}
