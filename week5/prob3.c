// 모든 테스트 입력에 대한 출력이 동일 합니다.

#include<stdio.h>
#include<stdlib.h>
#define MAX 100

int arr[8][2] = {
    {-1, -1}, {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}
};
int table[MAX][MAX];

int check_black_win(int x, int y);
int check_white_win(int x, int y);

int main(){
    // TODO : 1 검은돌 , 2 흰돌

    FILE *fp = fopen("board.txt", "r");
    int n;
    fscanf(fp, "%d", &n);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            fscanf(fp, "%d", &table[i][j]);
        }
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            int res;
            if(table[i][j] == 1){
                res = check_black_win(i, j);
                if(res == 1){
                    printf("Black Win");
                    exit(0);
                }
            }else if(table[i][j] == 2){
                res = check_white_win(i, j);
                if(res == 1){
                    printf("White Win");
                    exit(0);
                }
            }
        }
    }
    printf("Not Finished");
    fclose(fp);

    return 0;
}

int check_black_win(int x , int y){
    int nx , ny;
    for(int i = 0; i < 8; i++){
        nx = x + arr[i][0];
        ny = y + arr[i][1];
        int cnt = 1;
        while(table[nx][ny] == 1){
            cnt += 1;
            nx += arr[i][0];
            ny += arr[i][1]; 
        }
        if (cnt == 5) return 1;
    }
    return 0;
}

int check_white_win(int x, int y){
    int nx , ny;
    for(int i = 0; i < 8; i++){
        nx = x + arr[i][0];
        ny = y + arr[i][1];
        int cnt = 1;
        while(table[nx][ny] == 2){
            cnt += 1;
            nx += arr[i][0];
            ny += arr[i][1]; 
        }
        if (cnt == 5) return 1;
    }
    return 0;
}