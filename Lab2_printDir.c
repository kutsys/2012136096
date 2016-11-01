#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>

void printdir(char *dir, int depth)
{
	DIR *dp; // 디렉토리 포인터변수 dp 선언
	struct dirent *entry; // 파일, 또는 디렉토리가 가지고 있는 정보 구조체인// dirent 변수의 포인터 entry 선언
	struct stat statbuf; // 파일 정보를 담는 stat구조체를 하나 생성한다.

	if ( (dp = opendir(dir)) == NULL) { // 디렉토리를 열 수 없을 경우를 점검한다
		fprintf(stderr, "Cannot Open Directory!!: %s\n", dir);
		return;
	}
	chdir(dir); // 점검 후 지정한 디렉터리를 현재 디렉터리로 만든다.
	while ((entry = readdir(dp)) != NULL) { // dp가 가리키는 항목에 대한 정보 가져오기
		lstat(entry->d_name, &statbuf);
		if (S_ISDIR(statbuf.st_mode)) {
			if(strcmp(".", entry->d_name) == 0 || 
				strcmp("..", entry->d_name) == 0)
				continue;
			if ( entry->d_name[0] == '.') {  }
			else {
				printf("%*s%s\n", depth,"",entry->d_name);
			}
		//	printf("%*s%s/\n", depth, "", entry->d_name);
			printdir(entry->d_name, depth+4);
		}
		//else if (strncmp(".", entry->d_name, 1)) {
		//	printf("%*s%s\n", depth,"",entry->d_name);
		//}
	}
	chdir("..");
	closedir(dp);
}

int main() {
	printf("Directory scan of /home/wooyo:\n");
	printdir("/home/wooyo", 0);
	printf("done.\n");

	exit(0);
}
