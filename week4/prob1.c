#include<stdio.h>
#define MAX 100
int main(){
    int arr[MAX];
    int n;
    int cnt = 0;
    scanf("%d", &n);

    for(int i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    
    for(int i = 0; i < n - 1; i++){
        for(int j = i + 1; j < n; j++){
            if(arr[i] > arr[j]) cnt += 1;
        }
    }
    
    printf("%d", cnt);
    return 0;
}