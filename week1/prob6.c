// 모든 테스트 입력에 대한 출력이 동일합니다.
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double prob(int n, int k);
int main()
{
    // 1. 6번 던져서 1번 이상 나오는 경우
    // 2. 12번 던져서 2번 이상 나오는 경우를 구하기 위한 반복문
    int cnt = 2;
    for (int i = 0; i < cnt; i++)
    {
        int n, k;
        scanf("%d %d", &n, &k);
        printf("%lf\n", prob(n, k));
    }

    return 0;
}
double prob(int n, int k)
{
    int T = 1000000;
    int one_total = 0;
    srand((unsigned int)time(NULL));
    for (int i = 0; i < T; i++)
    {
        int one_cnt = 0;
        for (int j = 0; j < n; j++)
        {
            int diceNumber = rand() % 6 + 1;
            if (diceNumber == 1)
                one_cnt += 1;
        }
        if (one_cnt >= k)
            one_total += 1;
    }
    // 함수가 반환하는 데이터 형태가 double 이기 때문에 형변환을 해줌
    return (double)one_total / T;
}