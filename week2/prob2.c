#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 100000
#define BUFFER_SIZE 20

void delete_same(char **words, int *size);
void sort(char **words, int *size);

int main(){
    char *words[MAX];
    char buffer[BUFFER_SIZE];

    int n = 0;

    char find[BUFFER_SIZE];
    scanf("%s", find);
    int find_size = strlen(find);
    
    FILE * fp = fopen("harry.txt", "r");

    while(fscanf(fp , "%s", buffer) != EOF){
        int cnt = 0;
        for(int i = 0; i < find_size; i ++){
            if(find[i] == buffer[i]){
                cnt += 1;
            }
        }
        if (cnt == find_size){
            int isSame = 0;
            for(int i = n - 1; i >= 0; i--){
                if(strcmp(words[i], buffer) == 0){
                    isSame = 1;
                    break;
                }
            }
            if(!isSame){
                words[n] = strdup(buffer);
                n += 1;
            }
        }
    }

    int size = n;
    sort(words, &size);

    for (int i = 0; i < size; i++){
        printf("%s\n", words[i]);
    }

    printf("%d", size);
    fclose(fp);

    return 0;
}
 
void sort(char **words, int * size){
    
    for(int i = *size - 1; i > 0; i--){
        for(int j = 0; j < i ; j ++){
            // 앞에 있는게 사전식 뒤면 swap
            if(strcmp(words[j],words[j + 1]) > 0){
                char *tmp = words[j + 1];
                words[j + 1] = words[j];
                words[j] = tmp;
            }
        }
    }
}