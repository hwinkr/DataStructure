// 모든 테스트 입력에 대한 출력이 동일합니다.
#include<stdio.h>
#include<string.h>
#define MAX 100
#define BURRER_SIZE 20

void sort(char *words[], int size);
void swap(char **a, char **b);
int main(){
    char *words[MAX];
    char buffer[BURRER_SIZE];
    int n;
    scanf("%d", &n);

    for(int i = 0; i < n; i++){
        scanf("%s", buffer);
        words[i] = strdup(buffer);
    }
    printf("\n");
    // 포인터 배열의 첫 주소를 넘겨주고,
    sort(words, n);
    for(int i = 0; i < n; i++){
        printf("%s\n", words[i]);
    }
    return 0;  
}
// ! 포인터 배열은 더블 포인터로 받아야 한다.
void swap(char **a, char **b){
    char *tmp = *a;
    *a = *b;
    *b = tmp;
}
// 포인터 배열이기 때문에 배열 형식으로 받는다.
void sort(char *words[], int size){
    // 길이 기준 오름차순
    for(int i = size - 1; i > 0; i--){
        for(int j = 0; j < i; j++){
            if(strlen(words[j]) > strlen(words[j + 1])){
                swap(&words[j + 1], &words[j]);
            }
        }   
    }
    // 길이가 같은 경우에만 사전식 정렬하기
    for(int i = 0; i < size; i++){
        for(int j = i + 1; j < size; j++){
            if (strlen(words[i]) == strlen(words[j])){
                if (strcmp(words[i], words[j]) == 1){
                    swap(&words[j], &words[i]);
                }
            }
        }
    }
}