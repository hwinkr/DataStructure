// 모든 테스트 입력에 대한 출력이 동일합니다.

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#define MAX 100

int main(){
    FILE * fp = fopen("sample.html", "r");
    FILE *result = fopen("sample.txt", "w");

    char buffer; 
    bool istag = false;

    while(fscanf(fp, "%c", &buffer) != EOF){
        if(buffer == '<'){
            istag = true;
            continue;
        }else if(buffer == '>'){
            istag = false;
            continue;
        }

        if(istag) continue;
        else fprintf(result, "%c", buffer);
    }
    fclose(fp);
    
    return 0;
}