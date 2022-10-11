// 모든 테스트 케이스에 대한 출력이 동일 합니다.

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 30

typedef struct node{
    char *word;
    int count;
    struct node *next;
} Node;

typedef struct sort_node{
    char *word;
    int count;
    struct sort_node *next;
} Sort_node;

void add_first(char *data);
void add_after(Node *prev, char *data);
void add_ordered_list(char *data);
void remove_under_ten();

Node *remove_first();
Node *remove_after(Node *prev);

void add_sorted_first(Node *node);
void add_sorted_after(Sort_node *prev, Node *node);
void add_sorted_count(Node *node);

Node *head = NULL;
Sort_node *sort_head = NULL;

int main(){
    FILE *fp = fopen("harry.txt", "r");
    char buffer[MAX];

    // 파일에서 읽어와서 노드 만들기
    while(fscanf(fp, "%s", buffer) != EOF){
        Node *p = head;
        while(p != NULL && strcmp(p->word, buffer) != 0){
            p = p->next;
        }
        if(p != NULL) p->count += 1;
        else{
            add_ordered_list(buffer);
        }      
    }
    // 단어의 빈도수가 10 이하인 문자들을 제거
    remove_under_ten();
    // 단어들의 빈도수를 내림차순으로 저장해둔 연결리스트를 하나 더 만들고, 만약 빈도수가 같다면 단어들을 사전식 정렬
    Node *q = head;
    while(q != NULL) {
        add_sorted_count(q);
        q = q->next;
    }

    Sort_node *p = sort_head;
    int sort_node_count = 0;
    while(p != NULL){
        printf("%s : %d\n", p->word, p->count);
        p = p->next;
        sort_node_count += 1;
    }
    printf("%d", sort_node_count);

    fclose(fp);

    return 0;
}

void add_sorted_first(Node *node){
    Sort_node *tmp = (Sort_node *)malloc(sizeof(Sort_node));

    tmp->word = node->word;
    tmp->count = node->count;
    tmp->next = sort_head;

    sort_head = tmp;
}

void add_sorted_after(Sort_node *prev, Node *node){
    Sort_node *tmp = (Sort_node *)malloc(sizeof(Sort_node));

    tmp->word = node->word;
    tmp->count = node->count;
    tmp->next = prev->next;
    prev->next = tmp;
}

void add_sorted_count(Node *node){
    Sort_node *prev = NULL;
    Sort_node *curr = sort_head;

    while(curr != NULL && curr->count >= node->count){
        prev = curr;
        curr = curr->next;
    }

    if (prev == NULL) add_sorted_first(node);
    else add_sorted_after(prev, node);
}

void add_first(char *data){
    Node *tmp = (Node *)malloc(sizeof(Node));

    tmp->word = strdup(data);
    tmp->count = 1;
    tmp->next = head;
    
    head = tmp;
}

void add_after(Node *prev, char *data){
    Node *tmp = (Node *)malloc(sizeof(Node));

    tmp->word = strdup(data);
    tmp->count = 1;
    tmp->next = prev->next;
    prev->next = tmp;
}

void add_ordered_list(char *data){
    Node *q = NULL;
    Node *p = head;

    while(p != NULL && strcmp(p->word, data) <= 0){
        q = p;
        p = p->next;
    }
    
    if(q == NULL) add_first(data);
    else add_after(q, data);
}

void remove_under_ten(){
    // 등장빈도 10 이하인 노드 제거하기
    Node *prev = NULL;
    Node *curr = head;

    while(curr != NULL){
        while(curr->count > 10){
            prev = curr;
            curr = curr->next;
        }
        if(prev == NULL){
            Node *remove_node = remove_first();
            curr = curr->next;
            free(remove_node);
        }else{
            Node *remove_node = remove_after(prev);
            curr = curr->next;
            free(remove_node);
        }
    }
}

Node *remove_first(){
    if(head == NULL) return NULL;
    Node *tmp = head;
    head = head->next;

    return tmp;
}

Node *remove_after(Node *prev){
    Node *tmp = prev->next;
    prev->next = prev->next->next;

    return tmp;
}

