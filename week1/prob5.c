// 모든 테스트 입력에 대한 출력이 동일합니다.
#include <stdio.h>
#define MAX 100

int main()
{
    int n;
    scanf("%d", &n);
    int arr[MAX];
    int res[MAX];
    int a = 0;

    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    // 배열의 중복 요소 제거하기
    for (int i = 0; i < n; i++)
    {
        int cnt = 1;
        for (int j = i + 1; j < n; j++)
            if (arr[i] == arr[j])
                cnt += 1;
        if (cnt == 1)
        {
            res[a] = arr[i];
            a += 1;
        }
    }
    // 중복요소 제거된 배열 오름차순 정렬하기
    for (int m = a - 1; m > 0; m--)
    {
        for (int n = 0; n < m; n++)
        {
            if (res[n] > res[n + 1])
            {
                int tmp = res[n + 1];
                res[n + 1] = res[n];
                res[n] = tmp;
            }
        }
    }

    for (int i = 0; i < a; i++)
    {
        printf("%d ", res[i]);
    }

    return 0;
}