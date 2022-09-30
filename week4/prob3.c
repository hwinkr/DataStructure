#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#define MAX 100
// 빈칸 처리하기
// & & 사이에 단어들의 공백을 하나로 줄이기
void delete_space(char *str, int size);
int main(){
    FILE * fp = fopen("table.txt", "r");
    char buffer[MAX];
    char *token;

    int m, n;
    int i =0;
    fscanf(fp, "%d %d ", &m, &n);
    char *save[MAX][MAX];
    while(fgets(buffer, MAX, fp) != NULL){
        token = strtok(buffer, "&");
        save[i][0] = strdup(token);
        for(int j = 1; j < n; j++){
            token = strtok(NULL, "&");
            save[i][j] = strdup(token);
        }
        i += 1;
    }
    // 필요없는 공백문자 제거하기 + 이쁘게 출력하기
    // 맨앞, 맨뒤 공백 제거하기
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            delete_space(save[i][j], strlen(save[i][j]));
        }
    }
     for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            printf("%s", save[i][j]);;
        }
        printf("\n");
    }
    fclose(fp);
    return 0;
}
void delete_space(char *str, int size){
    while(*str == " ") str++;
}