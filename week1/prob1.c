// 모든 테스트 입력에 대한 출력값이 동일 합니다.
#include <stdio.h>

int main()
{
    int N;
    scanf("%d", &N);
    while (N > 0)
    {
        N /= 2;
        printf("%d ", N);
    }
    return 0;
}