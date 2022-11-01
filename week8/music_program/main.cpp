#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "string_tools.h"
#include "library.h"

#define BUFFER_LENGTH 200
// ! MP3 Program

// TODO
// * 1. 프로그램 실행시 로드할 데이터 파일을 물어봄. 필수값이 아니고 없으면 다음 명령행으로 이동
// * 2. status : 저장된 모든 노래의 번호, 가수, 제목, 파일의 경로 출력 노래는 알파벳 순 정렬
// * 3. 가수 이름, 노래 제목 2단어 이상 가능
// * 4. search : 가수이름, 노래제목으로 검색 둘중 하나 입력 가능 / 둘 다 가능
// * 5. play + song number : music play
// * remove : delete file
// * save as [File_Name] : 목록 저장

void handle_add();
void process_command();
void handle_load();
void handle_search();
void handle_play();

int main(){
    initiallize();
    handle_load();
    process_command();
    return 0;
}

void handle_load(){
    char buffer[BUFFER_LENGTH];
    printf("Data file name ? ");
    if (read_line(stdin, buffer, BUFFER_LENGTH) <= 0)
        return;

    FILE *fp = fopen(buffer, "r");
    if (fp == NULL){
        printf("No such file exist..\n");
        return;
    }

    load(fp);
    fclose(fp);
}

void handle_search(){
    char name[BUFFER_LENGTH], title[BUFFER_LENGTH];

    printf("    Artist: ");
    if(read_line(stdin, name, BUFFER_LENGTH) <= 0){
        printf("    Artist name required.");
        return;
    }

    printf("    Title: ");
    int title_length = read_line(stdin, title, BUFFER_LENGTH);
    
    if(title_length <= 0) 
        search_song(name);
    else 
        search_song(name, title);
}

void handle_add(){
    char buffer[BUFFER_LENGTH];
    char *artist = NULL, *title = NULL, *path = NULL;
    // ! 가수와 노래 제목은 2단어 이상일 수 있다.
    printf("    Artist: ");
    if (read_line(stdin, buffer, BUFFER_LENGTH) > 0){
        artist = strdup(buffer);
    }
    printf("    Title: ");
    if (read_line(stdin, buffer, BUFFER_LENGTH) > 0){
        title = strdup(buffer);
    }
    printf("    File: ");
    if (read_line(stdin, buffer, BUFFER_LENGTH) > 0){
        path = strdup(buffer);
    }
    add_song(artist, title, path);
}

void handle_play(){
    char *id_str = strtok(NULL, " ");
    int index = atoi(id_str);
    play(index);
}

void process_command(){
    char command_line[BUFFER_LENGTH];
    char *command;

    while (1){
        printf("$ ");
        if (read_line(stdin, command_line, BUFFER_LENGTH) <= 0)
            continue;

        command = strtok(command_line, " ");

        if (strcmp(command, "add") == 0){
            handle_add();
        }else if (strcmp(command, "status") == 0){
            status();
        }else if (strcmp(command, "search") == 0){
            handle_search();
        }else if (strcmp(command, "play") == 0){
            handle_play();
        }else if (strcmp(command, "exit") == 0){
            break;
        }
    }
}
