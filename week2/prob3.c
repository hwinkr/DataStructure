#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 100000
#define BUFFER_SIZE 20

// 입력된 단어 사전식 출력 + 각 단어의 등장빈도수 같이 출력하기, 동일한 단어 중복 출력 x
void sort(char **words, int *cnt, int size);
int main(){     
    char *words[MAX];
    int cnt[MAX];
    char buffer[BUFFER_SIZE];
    int n = 0;

    FILE *fp = fopen("harry.txt", "r");
    
    // 만약 words에 새로 넣는 단어가 없으면 추가해주고 cnt를 1로 추가, 단어가 있으면 그 i에 cnt +=1 해준다.
    // n은 words에 지금 넣는 단어가 이미 존재 하지 않는 경우에만 +1 해준다
    while(fscanf(fp, "%s", buffer) != EOF){
        int isSame = 0;
        int location = -1;
        
        for(int i = n - 1; i >= 0; i --){
            if(strcmp(words[i], buffer) == 0){
                isSame = 1;
                location = i;
                break;
            }
        }
        
        if(isSame == 1){
            cnt[location] += 1;
        }else{
            if(strlen(buffer) >= 6){
                words[n] = strdup(buffer);
                cnt[n] = 1;
                n += 1;
            }
        }
    }

    sort(words, cnt, n);

    for(int i = 0; i < n ; i++){
        printf("%s: %d\n", words[i], cnt[i]);
    }

    printf("%d", n);
    return 0;
}

void sort(char **words, int *cnt, int size){
    for(int i = size - 1; i > 0; i--){
        for(int j = 0; j < i; j ++){
            // 앞의 단어가 더 큰 경우에 양수 반환
            if(strcmp(words[j], words[j + 1]) > 0){
                char *tmp1 = words[j + 1];
                words[j + 1] = words[j];
                words[j] = tmp1;

                int tmp2 = cnt[j + 1];
                cnt[j + 1] = cnt[j];
                cnt[j] = tmp2;
            }
        }
    }
}