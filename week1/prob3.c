// 모든 테스트 입력에 대한 출력이 동일합니다.
#include <stdio.h>
#include <stdbool.h>
#define MAX 100
int main()
{
    int arr[MAX];
    int i = 0;
    while (1)
    {
        bool isSame = false;
        scanf("%d", &arr[i]);
        if (arr[i] == -1)
        {
            break;
        }
        else
        {
            for (int j = i - 1; j >= 0; j--)
            {
                if (arr[j] == arr[i])
                {
                    isSame = true;
                    break;
                }
            }
            if (!isSame)
            {
                for (int m = i; m > 0; m--)
                {
                    for (int n = 0; n < i; n++)
                    {
                        if (arr[n + 1] < arr[n])
                        {
                            int tmp = arr[n + 1];
                            arr[n + 1] = arr[n];
                            arr[n] = tmp;
                        }
                    }
                }

                for (int k = 0; k <= i; k++)
                {
                    printf("%d ", arr[k]);
                }
                printf("\n");
                i++;
            }

            else
            {
                printf("duplicate\n");
            }
        }
    }
}