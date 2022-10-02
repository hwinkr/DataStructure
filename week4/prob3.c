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
    int max_lengths[MAX];
    while(fgets(buffer, MAX, fp) != NULL){
        token = strtok(buffer, "&");
        save[i][0] = strdup(token);
        for(int j = 1; j < n; j++){
            token = strtok(NULL, "&");
            save[i][j] = strdup(token);
        }
        i += 1;
    }

    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            delete_space(save[i][j], strlen(save[i][j]));
        }
    }

    for(int i = 0; i < m; i++){
        int max_len = strlen(save[0][i]);
        for(int j = 0; j < n; j ++){
            if(max_len < strlen(save[j][i])){
                max_len = strlen(save[j][i]);
            }
        }
        max_lengths[i] = max_len;
    }
    FILE *newFp = fopen("output.txt", "w");
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n - 1; j++){
            fprintf(newFp, "%s", save[i][j]);
            int tmp = max_lengths[j] - strlen(save[i][j]);
            for(int k = 0; k < tmp; k ++) fprintf(newFp, " ");
        }
        fprintf(newFp, "%s", save[i][n - 1]);
    }
    fclose(fp);
    return 0;
}
// 불필요한 공백문자 제거 함수.
void delete_space(char *str, int size){
    int i = 0, j = 0;
    while(j < size){
        if(!isspace(str[j]) || j > 0 && !isspace(str[j - 1])){
            str[i ++] = str[j];
        }
        j ++;
    }
    str[i] = '\0';
}
