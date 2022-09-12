// 모든 테스트 입력에 대한 출력이 동일합니다.
#include <stdio.h>
#include <stdlib.h>
#define MAX 100

int main()
{
    int arr[MAX];

    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    int k;
    scanf("%d", &k);

    int tmp = abs(arr[0] - k);
    int ans = 0;
    for (int i = 1; i < n; i++){
        if (abs(arr[i] - k) < tmp)
        {
            ans = arr[i];
            tmp = abs(arr[i] - k);
        }
    }
    printf("%d", ans);
    return 0;
}