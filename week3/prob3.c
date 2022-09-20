#include <stdio.h>
#include <string.h>
#define MAX 10000

char * words[MAX];
char * desc[MAX];
int n = 0;

void sort();
int main(){
    // char *delim = "\t";
    // ! 지역변수의 메모리 차지가 너무 크면 에러가 발생할 수 있음. 따라서 전역변수로 설정해줘서 함수의 무게를 줄여줘야함. 메인함수도 메모리에서 동작하는 함수중 하나.
    char * sentence[MAX];
    char tmp[MAX];

    FILE * fp = fopen("shuffle.txt", "r");
    
    while(fgets(tmp, MAX, fp) != NULL){
        sentence[n++] = strdup(tmp);
    }
    
    for(int i = 0; i < n; i++){
        words[i] = strtok(sentence[i], "\t");
        desc[i] = strtok(NULL, "\t");
    }

    sort();
    for(int i = 0; i < n; i++){
        printf("%s  %s\n", words[i], desc[i]);
    }
    
    fclose(fp);
    return 0;   
}
void sort(){
    for(int i = n - 1; i > 0 ; i--){
        for(int j = 0; j < i; j++){
            if(strcmp(words[j], words[j + 1]) > 0){
                char *tmp1 = words[j + 1];
                char *tmp2 = desc[j + 1];

                words[j + 1] = words[j];
                words[j] = tmp1;

                desc[j + 1] = desc[j];
                desc[j] = tmp2;
            }
        }
    }
}