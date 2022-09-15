#include <stdio.h>
#include <string.h>
#define MAX 100
#define BUFFER_SIZE 100

void add(char **names, char **numbers, int *size);
void find(char **names, char **numbers, int *size);
void status(char **names, char **numbers, int *size);
void delete(char **names, char **numbers, int *size);
int search(char **names, char *str, int size);
void load(char **names, char **numbers, int *size);
void save(char **names, char **numbers, int *size);

int main(){
    char *names[MAX];
    char *numbers[MAX];
    int n = 0;

    while(1){
        char command[MAX];

        printf("$ ");
        scanf("%s", command);

        if(strcmp(command, "add") == 0){
            add(names, numbers, &n);
        }else if(strcmp(command, "find") == 0){
            find(names, numbers, &n);
        }else if(strcmp(command, "status") == 0){
            status(names, numbers, &n);
        }else if(strcmp(command, "delete") == 0){
            delete(names, numbers, &n);
        }else if(strcmp(command, "load") == 0){
            load(names, numbers, &n);
        }else if(strcmp(command, "save") == 0){
            save(names, numbers, &n);
        }else if(strcmp(command, "exit") == 0){
            break;
        }
    }

    return 0;
}

void add(char **names, char **numbers, int *size){
    char buf1[BUFFER_SIZE], buf2[BUFFER_SIZE];
    scanf("%s", buf1);
    scanf("%s", buf2);
    int i = *size - 1;
    // strcmp(str1, str2) : str1이 더 크면 양수
    while(i > 0 && strcmp(names[i], buf1) > 0){
        names[i + 1] = names[i];
        numbers[i + 1] = numbers[i];
        i -= 1;
    }
    names[i + 1] = strdup(buf1);
    numbers[i + 1] = strdup(buf2);
    *size += 1;
    
    printf("%s was added successfully\n", buf1);
}

void find(char **names, char **numbers, int *size){
    char buf[BUFFER_SIZE];
    scanf("%s", buf);

    int idx = search(names, buf, *size);

    if (idx == -1){
        printf("No person '%s' exists\n", buf);
    }else{
        printf("%s\n", numbers[idx]);
    }
}

void status(char **names, char **numbers, int *size){
    for(int i = 0; i < *size; i++){
        printf("%s %s\n", names[i], numbers[i]);
    }
    printf("total %d persons\n", *size);
}

void delete(char **names, char **numbers, int *size){
    char buf[BUFFER_SIZE];
    scanf("%s", buf);

    int idx = search(names, buf, *size);
    if(idx == -1){
        printf("No person name '%s'\n", buf);
        return;
    }
    for(int i = idx; i < *size - 1; i ++){
        names[i] = names[i + 1];
        numbers[i] = numbers[i + 1];
    }
    *size -= 1;
    printf("%s was deleted successfully\n", buf);
}

int search(char **names, char *str, int size){
    for(int i = 0; i < size; i++){
        if(strcmp(names[i], str) == 0){
            return i;
        }
    }

    return -1;
}
void load(char **names, char **numbers, int *size){
    char FileName[BUFFER_SIZE];
    char buf1[BUFFER_SIZE];
    char buf2[BUFFER_SIZE];

    scanf("%s", FileName);
    
    FILE *fp = fopen(FileName, "r");

    if(FileName == NULL){
        printf("load failed\n");
        return;
    }
    while(fscanf(fp, "%s", buf1) != EOF){
        fscanf(fp, "%s", buf2);
        names[*size] = strdup(buf1);
        numbers[*size] = strdup(buf2);
        *size += 1;
    }
    fclose(fp);
}

// 파일 저장하기 새로  
void save(char **names, char **numbers, int *size){
    char FileName[BUFFER_SIZE];
    char tmp[BUFFER_SIZE];

    scanf("%s", tmp);
    scanf("%s", FileName);

    // 파일을 쓰기 모드로 연다
    FILE *fp = fopen(FileName, "w");

    if(FileName == NULL){
        printf("Open failed\n");
        return;
    }
    for(int i = 0; i < *size; i++){
        fprintf(fp, "%s %s\n", names[i], numbers[i]); 
    }
    fclose(fp);
}
