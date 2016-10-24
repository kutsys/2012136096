// printDir.c

#include <unistd.h>
#include <stdio.h>
#include <dirent.h>  
#include <string.h>
#include <sys/stat.h>  
#include <stdlib.h>

 
void printdir(char *dir,int depth)
{
     DIR *dp;  // 디렉토리 포인터 변수 dp 선언
     struct dirent *entry; // 파일 또는 디렉토리가 가지고 있는 정보 구조체인
                            // dirent 변수인 포인터 entry 생성
     struct stat statbuf; // 파일 정보를 담는 구조체 stat버퍼 변수 선언

     if((dp=opendir(dir)) == NULL) // 디렉토리 오픈
     {
         fprintf(stderr,"cannot open directory : %s \n ",dir);
         return;
     } // 열지 못하면 에러메세지를 콘솔에 띄워줌
     chdir(dir); // 지정한 디렉터리 dir을 현재 디렉터리로 설정
 
     while((entry = readdir(dp)) !=NULL)  {
     //  dp가 가리키는 항목에 대한 정보 가져오기
        lstat(entry->d_name,&statbuf); // 디렉토리에 대한 정보 저장
        if(S_ISDIR(statbuf.st_mode)) { // 현재 항목이 디렉터리이고
            if(strcmp(".",entry->d_name) == 0 ||   //현재 또는 부모 디렉터리면
              strcmp("..",entry->d_name) ==0) continue; // 그냥 넘어가기

            if ( entry->d_name[0] == '.' ) { }
            else {
                print("%s*s%s\n", depth, "", entry->d_name);
            }
            printdir(entry->d_name, depth+4);
        }
     }
     chdir("..");
     closedir(dp);
}

 
int main()
{
	printf("Directory scan of /home/wooyo : \n");
	printdir("/home/wooyo",0); //함수호출
	printf("done.\n");
 	exit(0);
} 
