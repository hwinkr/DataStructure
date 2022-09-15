#include <stdio.h>
#include <string.h>
#define MAX 100
#define BUFFER_SIZE 100


// ! 포인터 변수는 어떤 변수의 메모리 주소를 저장하는 변수
// ! 배열에서 배열의 이름은 메모리에서 배열의 시작 주소이다. int *arr = &nums[0] == nums
// ? 그렇다면 포인터 배열은? -> 포인터 배열은 각 자리에 어떤변수들의 메모리 주소를 저장한다 포인터 배열을 매개변수로 사용해서 함수의 인수로 넘겨주는 경우에는 이중 포인터를 사용해야함. 그 포인터 배열의 시작주소를 넘겨줘야하는데 그 포인터 배열자체가 또 하나의 포인터이기때문에 *를 사용해서 선언, 내 생각에는 이걸 구분해주기 위해서 이중포인터를 사용해서 **로 넘겨주는듯
void add(char **names, char **numbers, int *size);
void find(char **names, char **numbers, int *size);
void status(char **names, char **numbers, int *size);
void delete(char **names, char **numbers, int *size);

int main(){
    char *names[MAX];
    char *numbers[MAX];

    // 저장된 사람의 수
    int n = 0;
    char command[BUFFER_SIZE];
    while(1){
        // 사용자의 명령 
        // ex) add Woong 01082807333
        printf("$ ");
        scanf("%s", command);

        if(strcmp(command, "add") == 0){
            add(names, numbers, &n);
        }else if(strcmp(command, "find") == 0){
            find(names, numbers, &n);
        }else if(strcmp(command, "status") == 0){
            status(names, numbers, &n);
        }else if(strcmp(command, "delete") == 0){
            delete(names, command, &n);
        }else if(strcmp(command, "exit") == 0){
            break;
        }
    }
    printf("%d\n", n);
    return 0;
}

void add(char **names, char **numbers, int *size){
    char buf1[BUFFER_SIZE], buf2[BUFFER_SIZE];
    scanf("%s", buf1);
    scanf("%s", buf2);

    names[*size] = strdup(buf1);
    numbers[*size] = strdup(buf2);

    *size +=1;

    printf("%s was added sucessfully\n", buf1);
}

void find(char **names, char **numbers, int *size){
    char buf[BUFFER_SIZE];
    scanf("%s", buf);

    for(int i = 0; i < *size; i++){
        if(strcmp(buf, names[i]) == 0){
            printf("%s\n", numbers[i]);
            return;
        }
    }
    printf("No Person name '%s' exists.\n", buf); 
}

void status(char **names, char **numbers, int *size){
    for(int i = 0; i < *size; i++){
        printf("%s %s\n", names[i], numbers[i]);
    }
    printf("Person Total : %d\n", *size);
}

void delete(char **names, char **numbers, int *size){
    char buf[BUFFER_SIZE];
    scanf("%s", buf);

    for(int i = 0; i < *size; i++){
        if(strcmp(buf, numbers[i]) == 0){
            // 맨 마지막에 있는 사람을 삭제된 자리로 옮긴다
            names[i] = names[*size - 1];
            numbers[i] = numbers[*size - 1];
            size -= 1;
            printf("%s deleted sucessfully", names[i]);
            return;
        }
    }

    printf("No Person name '%s' exists", buf);
}