#include "library.h"
#include "string_tools.h"

#define NUM_CHARS 256
#define SIZE_INDEX_TABLE 10
#define BUFFER_LENGTH 200

// ! 다른 소스 파일에게 공유 하지 않아도 되지만 현재 소스 파일에서 필요한 자료구조 : artist_directory, index_directory(크기를 10으로 나눈 나머지가 같은 노래끼리 묶음
Artist *find_artist(char *name);
SNode *find_SNode(Artist *ptr_artist, char *title);
void insert_node(Artist *ptr_artist, SNode *ptr_snode);
void print_song(Song *ptr_song);
void print_artist(Artist *p);
void insert_to_index_directory(Song *ptr_song);
SNode *find_song(int index);

Artist *artist_directory[NUM_CHARS];
SNode *index_directory[SIZE_INDEX_TABLE];

int num_index = 0;

void initiallize(){
    for (int i = 0; i < NUM_CHARS; i++)
        artist_directory[i] = NULL;

    for(int i = 0; i < SIZE_INDEX_TABLE; i++)
        index_directory[i] = NULL;
}

void load(FILE *fp){
    char buffer[BUFFER_LENGTH];
    char *name, *title, *path;

    while (read_line(fp, buffer, BUFFER_LENGTH) > 0){
        name = strtok(buffer, "#");
        if (strcmp(name, " ") == 0)
            name = NULL;
        else
            name = strdup(name);

        title = strtok(NULL, "#");
        if (strcmp(title, " ") == 0)
            title = NULL;
        else
            title = strdup(title);

        path = strtok(NULL, "#");
        if (strcmp(path, " ") == 0)
            path = NULL;
        else
            path = strdup(path);

        add_song(name, title, path);
    }
}
// * search
void search_song(char *artist){
    Artist *ptr_artist = find_artist(artist);
    if(ptr_artist == NULL){
        printf("No such artist exists...\n");
        return;
    }

    printf("Found :\n");
    print_artist(ptr_artist);
}
  
void search_song(char *artist, char *title){
    Artist *ptr_artist = find_artist(artist);
    if(ptr_artist == NULL){
        printf("No such artist exists...\n");
        return;
    }

    SNode *ptr_snode = find_SNode(ptr_artist, title);
    if(ptr_snode != NULL){
        printf("Found :\n");
        print_song(ptr_snode->song);
    }else{
        printf("No such song exists...\n");
        return;
    }
}

SNode *find_SNode(Artist *ptr_artist, char *title){
    SNode *ptr_snode = ptr_artist->head;
    while(ptr_snode != NULL && strcmp(ptr_snode->song->title, title) < 0){
        ptr_snode = ptr_snode->next;
    }

    if(ptr_snode !=  NULL && strcmp(ptr_snode->song->title, title) == 0){
        return ptr_snode;
    } 
    else{
        printf("No such song exists...\n");
        return NULL;
    }
}

Artist *create_artist_instance(char *name){
    Artist *ptr_artist = (Artist *)malloc(sizeof(Artist));

    ptr_artist->name = name;
    ptr_artist->head = NULL;
    ptr_artist->tail = NULL;
    // 시작 문자가 같고, 사전식으로 다음에 위치하는 struct artist 를 가르킴
    ptr_artist->next = NULL;

    return ptr_artist;
}

Artist *find_artist(char *name){
    Artist *p = artist_directory[(unsigned char)name[0]];

    // ! 같은 문자로 시작하는 artist 의 끝까지 비교할 필요가 없다.
    // ! 현재 airtst 들은 사전식으로 정렬 되어 있고, 찾고자 하는 artist 보다 사전식순서가 뒤에 있는 이름을 만나면 더이상 p->next 를 해줄 필요가 없다.
    // * while 문을 빠져 나오는 경우
    // 1. 찾고자 하는 이름이 없는 경우 -> null return
    // 2. 나보다 사전식 순서에서 뒤에 있는 이름을 만난 경우 p != null && strcmp(p->name, name) != 0 -> return null
    // 3. 이름을 찾은 경우 p == null && strcmp(p->name, name) == 0 -> return p
    while (p != NULL && strcmp(p->name, name) < 0)
        p = p->next;

    if (p != NULL && strcmp(p->name, name) == 0)
        return p;
    else
        return NULL;
}

Artist *add_artist(char *name)
{
    // ! struct artist 는 단방향 연결 리스트이다.
    // * create_artist_instance 를 프로토타입 선언 하지 않아도 되는 이유는 이미 위에서 정의한 함수를 사용하고 있기 떄문에
    Artist *ptr_artist = create_artist_instance(name);

    Artist *p = artist_directory[(unsigned char)name[0]]; // first node in artist_directory[name[0]]
    Artist *q = NULL;

    // artist 의 이름을 사전식 기준으로 정렬하기
    while (p != NULL && strcmp(p->name, name) < 0){
        q = p;
        p = p->next;
    }

    if (p == NULL && q == NULL){
        artist_directory[(unsigned char)name[0]] = ptr_artist;
    }else if (q == NULL){
        // 추가 하려는 artist 를 add first
        ptr_artist->next = artist_directory[(unsigned char)name[0]];
        artist_directory[(unsigned char)name[0]] = ptr_artist;
    }else{
        // add_after
        ptr_artist->next = p;
        q->next = ptr_artist;
    }
    return ptr_artist;
}

Song *create_song_instance(Artist *artist, char *title, char *path){
    Song *ptr_song = (Song *)malloc(sizeof(Song));

    ptr_song->artist = artist;
    ptr_song->title = title;
    ptr_song->path = path;
    // 모든 song 객체들이 다른 index 값을 가지게 하기 위함, 삭제해서 그 번호가 사라지면 중간에 번호가 비는 것은 상관 없다고 침
    ptr_song->index = num_index;
    num_index += 1;

    return ptr_song;
}

void insert_node(Artist *ptr_artist, SNode *ptr_snode){
    // TODO : 노래들은 한명의 artist가 거느리고 있는 SNode 이중 연결리스트에서 노래의 제목의 알파벳 순으로 정렬해서 추가한다.
    SNode *p = ptr_artist->head;

    // * 이중 연결리스트이기 때문에, 투 포인터 사용할 필요 없음

    while (p != NULL && strcmp(p->song->title, ptr_snode->song->title) < 0){
        p = p->next;
    }

    // TODO : 케이스 나눠서 처리
    if (ptr_artist->head == NULL){ 
        // 1. empty list
        ptr_artist->head = ptr_snode;
        ptr_artist->tail = ptr_snode;
    }else if (p == ptr_artist->head){ 
        // 2. add first
        ptr_snode->next = ptr_artist->head;
        ptr_artist->head->prev = ptr_snode;
        ptr_artist->head = ptr_snode;
    }else if (p == NULL){ 
        // 3. add end
        ptr_snode->prev = ptr_artist->tail;
        ptr_artist->tail->next = ptr_snode;
        ptr_artist->tail = ptr_snode;
    }else{ 
        // 4. add before
        ptr_snode->next = p;
        ptr_snode->prev = p->prev;
        p->prev->next = ptr_snode;
        p->prev = ptr_snode;
    }
}

void add_song(char *artist, char *title, char *path){
    // TODO
    // * 1. artist_directory 에 사전식으로 현재 추가하려는 artist를 추가
    // * 2. Song 노드 생성하고 데이터 입력
    // * 3. artist 가 거느리고 있는 이중연결 리스트에 노래제목을 알파벳 순으로 ordered_list 로 추가
    Artist *ptr_artist = find_artist(artist);
    // ! song 을 추가하려고 하는데, 이 노래를 부른 가수가 directory 에 저장되어 있지 않은 경우
    // ! 만약 ptr_artist 가 NULL 이라면, 새롭게 artist stucht 를 하나 만들어준다.
    if (ptr_artist == NULL){
        ptr_artist = add_artist(artist);
    }
    // add the song to the artist pointed by prt_artist
    Song *ptr_song = create_song_instance(ptr_artist, title, path);
    // ! SNode 는 이중연결리스트로 구현한다.
    SNode *ptr_snode = (SNode *)malloc(sizeof(SNode));
    ptr_snode->song = ptr_song;
    ptr_snode->next = NULL;
    ptr_snode->prev = NULL;
    // insert snode double linked list
    insert_node(ptr_artist, ptr_snode);
    insert_to_index_directory(ptr_song);
}

void insert_to_index_directory(Song *ptr_song){
    SNode *ptr_snode = (SNode *)malloc(sizeof(SNode));
    ptr_snode->song = ptr_song;
    ptr_snode->next = NULL;
    ptr_snode->prev = NULL; // unused

    int index = ptr_song->index % SIZE_INDEX_TABLE;

    // add the snode into the single linkedlist at index_table[index]
    // * 단방향 연결리스트 + add_after
    SNode *p = index_directory[index];
    SNode *q = NULL;
    while(p != NULL && strcmp(p->song->title, ptr_song->title) < 0){
        q = p;
        p = p->next;
    }

    if(q == NULL){ // add_first
        ptr_snode->next = p;
        index_directory[index] = ptr_snode;
    }else{ // add_after
        ptr_snode->next = p;
        q->next = ptr_snode;
    }
}

SNode *find_song(int index){
    SNode *ptr_snode = index_directory[index % SIZE_INDEX_TABLE];
    while(ptr_snode != NULL && ptr_snode->song->index != index){
        ptr_snode= ptr_snode->next;
    }

    return ptr_snode;
}

void play(int index){
    SNode *ptr_snode = find_song(index);
    if(ptr_snode == NULL){
        printf("No such song exists...\n");
        return;
    }

    printf("Found the song: %s\n", ptr_snode->song->title);
}

void print_song(Song *ptr_song){
    printf("    %d: %s %s\n", ptr_song->index, ptr_song->title, ptr_song->path);
}

void print_artist(Artist *p){
    printf("%s\n", p->name);
    SNode *ptr_snode = p->head;
    while (ptr_snode != NULL){
        print_song(ptr_snode->song);
        ptr_snode = ptr_snode->next;
    }
}

void status(){
    for (int i = 0; i < NUM_CHARS; i++){
        if (artist_directory[i] != NULL){
            Artist *p = artist_directory[i];
            while (p != NULL){
                print_artist(p);
                p = p->next;
            }
        }
    }
}
