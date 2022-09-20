#include <stdio.h>
#define MAX 100
int main(){
    int arr[MAX];
    int n;
    scanf("%d", &n);

    for(int i = 0; i < n; i++){
        scanf("%d", &arr[i]);
    }
    // sort 
    for(int i = n - 1; i > 0; i--){
        int max_num = arr[0];
        int idx = 0;
        for(int j = 0; j < i; j++){
            if(arr[j] > max_num){
                max_num = arr[j];
                idx = j;
            }
        }
        if(arr[i] > max_num) 
            continue;

        int tmp = arr[i];
        arr[i] = arr[idx];
        arr[idx] = tmp;
    
    }
    for(int i = 0; i < n; i++){
        printf("%d ", arr[i]);
    }
    return 0;
}