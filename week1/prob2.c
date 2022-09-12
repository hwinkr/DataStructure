// 모든 테스트 입력에 대한 출력이 동일합니다.
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int N;
    scanf("%d", &N);

    int *arr = (int *)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++)
        scanf("%d", &arr[i]);

    int first_min = arr[0];
    int second_min = arr[1];

    if (first_min > second_min)
    {
        int tmp = first_min;
        first_min = second_min;
        second_min = tmp;
    }
    for (int i = 2; i < N; i++)
    {
        if (arr[i] < first_min)
        {
            second_min = first_min;
            first_min = arr[i];
        }
        else if (arr[i] >= first_min && arr[i] < second_min)
        {
            second_min = arr[i];
        }
    }

    printf("%d %d", first_min, second_min);
    return 0;
}