#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX 100
int main (){
    // 4 : 행 , 열의 평균과 표준편차

    int n;
    FILE * fp = fopen("input.txt" , "r");
    fscanf(fp, "%d", &n);
    int arr[MAX][MAX];

    double avglst_row[MAX];
    double avglst_col[MAX];

    double devlst_row[MAX];
    double devlst_col[MAX];

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            fscanf(fp , "%d" , &arr[i][j]);
        }
    }
    fclose(fp);

    for(int i = 0; i < n; i++){
        int sum_row = 0, sum_col = 0;
        double avg_row = 0, avg_col = 0;

        for(int j = 0; j < n; j++){
            sum_row += arr[i][j];
            sum_col += arr[j][i];
        }
        avg_row = (double)sum_row / n;
        avg_col = (double)sum_col / n;

        avglst_row[i] = avg_row;
        avglst_col[i] = avg_col;

        double dev_row, dev_col = 0;
        double dessum_row, dessum_col = 0;
        for(int k = 0; k < n; k++){
            dessum_row += pow(avg_row - arr[i][k], 2);
            dessum_col += pow(avg_col - arr[k][i], 2);
        }
        dev_row = sqrt(dessum_row / n);
        dev_col = sqrt(dessum_col / n);

        devlst_row[i] = dev_row;
        devlst_col[i] = dev_col;
    }   

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            printf("%d ", arr[i][j]);
        }
        printf("%.2lf ", avglst_row[i]);
        printf("%.2lf\n", devlst_row[i]);
    }

    for(int i = 0; i < n; i++){
        printf("%.2lf ", avglst_col[i]);
    }
    printf("\n");
    for(int i = 0; i < n; i++){
        printf("%.2lf ", devlst_col[i]);
    }

    return 0;
}