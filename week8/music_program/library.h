#ifndef LIBRARY_H
#define LIBRARY_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct song Song;
typedef struct snode SNode;
typedef struct artist Artist;

struct song
{
    Artist *artist;
    char *title;
    char *path;
    int index;
};

struct snode
{
    SNode *prev, *next;
    Song *song;
};

struct artist
{
    char *name;
    // * artist 의 이름을 사전식 순으로 정렬
    Artist *next;
    SNode *head, *tail;
};

void initiallize();
void add_song(char *artist, char *title, char *path);
void status();
void load(FILE *fp);
void search_song(char *artist);
void search_song(char *artist, char *title);

#endif