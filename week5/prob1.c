// 모든 테스트 입력에 대한 출력이 동일 합니다.

#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#define MAX 100

int isMo(char target);

int main(){
    char *consonant[MAX];
    int cons_size = 0;

    char str[MAX];
    int ch, size_str = 0;
    
    while((ch = getchar()) != '\n'){
        str[size_str++] = ch;
    }
    str[size_str] = '\0';
 
    char buffer[MAX];
    int buffer_size = 0;

    for(int i = 0; i < size_str; i++){
        int res = isMo(str[i]);
        if(res){
            buffer[buffer_size] = '\0';
            consonant[cons_size++] = strdup(buffer);
            for(int j = 0; j < buffer_size; j++){
                buffer[j] = '\0';
            }
            buffer_size = 0;
            continue;
        }
        buffer[buffer_size] = str[i];
        buffer_size += 1;
    }
    
    int idx = 0;
    for(int i = 0; i < cons_size; i++){
        if(strlen(consonant[i]) > strlen(consonant[idx])){
            idx = i;
        }
    }

    printf("%s", consonant[idx]);
    printf("hi");

    return 0;
}

int isMo(char target){
    char collection[5] = {'a', 'e', 'i', 'o', 'u'};
    for(int i = 0; i < 5; i ++) if(target == collection[i]) return 1;

    return 0;
}