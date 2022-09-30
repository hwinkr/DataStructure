#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define CAPACITY 100
#define BUFFER_MAX 100
// type : person 인 자료구조 정의하기 
// 구조체 person을 정의 하면서 동시에 Person으로 renaming 하기
typedef struct person{
    char *name;
    char *number;
    char *email;
    char *group;
} Person;

Person directory[CAPACITY];
int n = 0;

int read_line(FILE *fp, char *str ,int n);
int compose_name(char *str, int limit);

void add(char *name, char *number, char *email, char *group);
void handle_add(char *name);

void load(char *fileName);
int search(char *name);
void find(char *name);
void print_person(Person p);
void status();

void save(char *fileName);
void remove(char *name);

int main(){
    char command_line[BUFFER_MAX];
    char *command, *argument;
    char name_str[BUFFER_MAX];

    while(1){
        printf("$ ");
        // 키보드로 부터 입력을 받음 표준 입력 stdin
        if(read_line(stdin, command_line, BUFFER_MAX) <= 0)
            continue;
        
        command = strtok(command_line, " ");
        
        if(strcmp(command, "read") == 0){
            argument = strtok(command, " ");
            if (argument == NULL){
                printf("Invalid Input.\n");
                continue;
            }
            load(argument);
        // 파일로부터 읽어와서 전화번호부에 추가하는 경우가 아니라, 사용자가 직접 이름을 포함한 정보를 전화번호부에 추가 하려고 할때, 사이의 공백은 1칸씩만 가져와서 저장 해야한다.
        // 유저가 추가할때는 띄어쓰기 공백에 제한이 없으므로, add [userName] 이렇에 한 공백만 인정하고 Js의 trim 기능을 구현해야한다.
        // 사용자의 이름 공백만 처리해주는 함수이다 
        }else if(strcmp(command, "add") == 0){
            if(compose_name(name_str, BUFFER_MAX) <= 0){
                printf("Name Required\n");
                continue;
            }
            handle_add(name_str);
        }else if(strcmp(command, "find") == 0){
            if(compose_name(name_str, BUFFER_MAX) <= 0){
                printf("Name Required\n");
                continue;
            }
            find(name_str);
        }else if(strcmp(command, "status") == 0){
            status();
        }else if(strcmp(command, "delete") == 0){
            if(compose_name(name_str, BUFFER_MAX) <= 0){
                printf("Name Required\n");
                continue;
            }
            remove(name_str);
        }else if(strcmp(command, "save") == 0){
            argument = strcmp(NULL, " ");
            if(strcmp(argument, "as") != 0){
                printf("Invalid Input\n");
                continue;
            }
            argument = strtok(NULL, " ");
            if(argument == NULL){
                printf("File Name Required\n");
                continue;
            }
            save(argument);
        }else if(strcmp(command, "exit") == 0){
            printf("Program Ended...\n");
            break;
        }else{
            printf("Invalid Command!\n");
        }
    }
    return 0;
}

int read_line(FILE *fp, char *str ,int n){
    int ch, i = 0;

    while((ch = fgetc(fp)) != '\n' && ch != EOF){
        if(i < n) str[i ++] = ch;
    }
    str[i] = '\0';
    return i;
}

int compose_name(char *str, int limit){
    char *ptr;
    int len = 0;
    // 사람 이름이 있으면, 사람이름이 ptr에 저장될 것.
    ptr = strtok(NULL, " ");
    if(ptr == NULL){
        return 0;
    }
    // 문자열을 복사 했기 때문에 현재 문자열 str에는 사람 이름이 저장되어 있을 것이다.
    strcpy(str, ptr);
    len += strlen(ptr);

    while((ptr = strtok(NULL, " ")) != NULL){
        if(len + strlen(ptr) + 1 < limit){
            str[len ++] = ' ';
            str[len] = '\0';
            strcat(str, ptr);
            len += strlen(ptr);
        }
    }
    return len; 
}

// 추가할 때, 사람의 이름을 기준으로 사전식 정렬하기
void add(char *name, char *number, char *email, char *group){
    int i = n - 1;
    // 이미 저장되어 있는, directory[i].name 가 사전식 정렬 했을때, 뒤에 있으면 한칸씩 계속 이동시켜줘야함
    while(i >= 0 && strcmp(directory[i].name, name) > 0){
        directory[i + 1] = directory[i];
        i -= 1;
    }

    directory[i + 1].name = strdup(name);
    directory[i + 1].number = strdup(number);
    directory[i + 1].email = strdup(email);
    directory[i + 1].group = strdup(group);
    
    n += 1;
}
// 명령 한줄에 이름, 전화번호, 메일, 그룹 전체를 입력하는 구조가 아니라
// 먼저 이름을 입력받고, 그 다음에 추가 정보를 물어보는 형식
void handle_add(char *name){
    char number[BUFFER_MAX], email[BUFFER_MAX], group[BUFFER_MAX];
    char empty[] = " ";

    printf("  Phone:  ");
    read_line(stdin, number, BUFFER_MAX);

    printf("  Email:  ");
    read_line(stdin, email, BUFFER_MAX);

    printf("  Group:  ");
    read_line(stdin, group, BUFFER_MAX);

    add(name, (char *)(strlen(number) > 0 ? number : empty),
              (char *)(strlen(email) > 0 ? email : empty),
              (char *)(strlen(group) > 0 ? group : empty));
}

void load(char *fileName){
    char buffer[BUFFER_MAX];
    char *name, *number, *email, *group;
    FILE *fp = fopen(fileName, "r");

    if(fp == NULL){
        printf("This File doesn't exist\n");
    }

    while(1){
        if(read_line(fp, buffer, BUFFER_MAX) <= 0)
            break;

        name = strtok(buffer, "#");
        number = strtok(buffer, "#");
        email = strtok(buffer, "#");
        group = strtok(buffer, "#");
        add(name, number, email, group);
    }
}

int search(char *name){
    for(int i = 0; i < n; i++){
        if(strcmp(directory[i].name, name) == 0){
            return i;
        }
    }
    return -1;
}

void find(char *name){
    int idx = search(name);
    if(idx == -1){
        printf("No Person in this Directroy, %s\n", name);
    }else{
        print_person(directory[idx]);
    }
}

void print_person(Person p){
    printf("%s: \n", p.name);
    printf("   Phone: %s\n", p.number);
    printf("   Email: %s \n", p.email);
    printf("   Group: %s\n", p.group);
}

void status(){
    for(int i = 0; i < n; i++){
        print_person(directory[i]);
    }
    printf("Total %d Person in this Directory.\n", n);
}

void save(char *fileName){
    FILE * fp = fopen(fileName, "w");

    if(fp == NULL){
        printf("File Name Please..\n");
        return;
    }
    for(int i = 0; i < n; i++){
        fprintf(fp, "%s#", directory[i].name);
        fprintf(fp, "%s#", directory[i].number);
        fprintf(fp, "%s#", directory[i].email);
        fprintf(fp, "%s#\n", directory[i].group);
    }
}

void remove(char *name){
    int i = search(name);
    if(i == -1){
        printf("No Person in this Directroy, %s\n", name);
        return;
    }

    for(int j = i; j < n - 1; j ++){
        directory[j] = directory[j + 1];
    }
    n -= 1;
    printf("'%s' was Deleted Successfully.\n", name);
}




