// 모든 테스트 입력에 대한 출력이 동일 합니다.

#include<stdio.h>
#include<string.h>

#define MAX 100

int data[MAX][MAX];
void show(int size);
void colmax(int size);
void colmin(int size);
void rowmax(int size);
void rowmin(int size);
void slice(int x, int p, int y, int q, int size);

int main(){
    FILE *fp = fopen("data.txt", "r");
    int n;
    fscanf(fp, "%d", &n);

    // TODO : show, colmax, rowmax, colmax, colmin, slice, exit

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            fscanf(fp, "%d", &data[i][j]);
        }
    }

    while(1){
        printf("$ ");
        char command[MAX];
        scanf("%s", command);
        if(strcmp(command, "show") == 0){
            show(n);
        }else if(strcmp(command, "colmax") == 0){
            colmax(n);
        }else if(strcmp(command, "colmin") == 0){
            colmin(n);
        }else if(strcmp(command, "rowmax") == 0){
            rowmax(n);
        }else if(strcmp(command, "rowmin") == 0){
            rowmin(n);
        }else if(strcmp(command, "rowmin") == 0){
            rowmin(n);
        }else if(strcmp(command, "slice") == 0){
            int x, p, y, q;
            scanf("%d %d %d %d", &x, &p, &y, &q);
            slice(x, p, y, q, n);
            
        }else if(strcmp(command, "exit") == 0){
            break;
        }
    }    
    fclose(fp);
    return 0;
}
// show
void show(int size){
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            printf("%d  ", data[i][j]);
        }
        printf("\n");
    }
}
// colmax
void colmax(int size){
    int max_list[MAX];
    int idx = 0;
    for(int i = 0; i < size; i++){
        int max = data[0][i];
        for(int j = 0; j < size; j++)
            if(max < data[j][i])
                max = data[j][i];
            
        
        max_list[idx ++] = max;
    }

    for(int i = 0; i < size; i++){
        printf("%d ", max_list[i]);
    }
}
// colmin
void colmin(int size){
    int min_list[MAX];
    int idx = 0;
    for(int i = 0; i < size; i++){
        int min = data[0][i];
        for(int j = 0; j < size; j ++) 
            if(min > data[j][i]) 
                min = data[j][i];   

        min_list[idx++] = min;
    }

    for(int i = 0; i < size; i++){
        printf("%d ", min_list[i]);
    }
}
// rowmax
void rowmax(int size){
    int max_list[MAX];
    int idx = 0;
    for(int i = 0; i < size; i++){
        int max = data[i][0];
        for(int j = 0; j < size; j++)
            if(max < data[i][j])
                max = data[i][j];
        
        max_list[idx ++] = max;
    }

    for(int i = 0; i < size; i++){
        printf("%d ", max_list[i]);
    }
}
// rowmin
void rowmin(int size){
    int min_list[MAX];
    int idx = 0;
    for(int i = 0; i < size; i++){
        int min = data[i][0];
        for(int j = 0; j < size; j ++) 
            if(min > data[i][j]) 
                min = data[i][j];   

        min_list[idx++] = min;
    }

    for(int i = 0; i < size; i++){
        printf("%d ", min_list[i]);
    }
}
// slice
void slice(int x, int p, int y, int q, int size){
    for(int i = x; i < size; i += p){
        for(int j = y; j < size; j += q)
            printf("%d ", data[i][j]);
        
        printf("\n");
    }
}