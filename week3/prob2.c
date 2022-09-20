#include <stdio.h>
#define MAX 100

int main(){
    int start[MAX];
    int end[MAX];

    int n;
    scanf("%d", &n);

    for(int i = 0; i< n; i++){
        scanf("%d", &start[i]);
        scanf("%d", &end[i]);
    }

    for(int i = n - 1; i > 0; i--){
        for(int j = 0; j < i; j ++){
            if(start[j] > start[j + 1]){
                int tmp1 = start[j + 1];
                int tmp2 = end[j + 1];

                start[j + 1] = start[j];
                start[j] = tmp1;

                end[j + 1] = end[j];
                end[j] = tmp2;
            }else if(start[j] == start[j + 1]){
                if(end[j] > end[j + 1]){
                    int tmp1 = start[j + 1];
                    int tmp2 = end[j + 1];

                    start[j + 1] = start[j];
                    start[j] = tmp1;

                    end[j + 1] = end[j];
                    end[j] = tmp2;
                }
            }
        }
    }

    for(int i = 0; i < n; i++){
        printf("%d ", start[i]);
        printf("%d\n", end[i]);
    }
    return 0;
}