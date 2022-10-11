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

void add_first(char *data);
void add_after(Node *prev, char *data);
void add_ordered_list(char *data);

Node *remove_first();
Node *remove_after(Node *prev);
void remove_under_ten();

Node *head = NULL;

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

    remove_under_ten();

    Node *q = head;
    int node_count = 0;
    while(q != NULL){
        printf("%s : %d\n", q->word, q->count);
        q = q->next;
        node_count += 1;
    }
    printf("%d", node_count);

    fclose(fp);
    return 0;
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

Node *remove_after(Node *prev){
    Node *tmp = prev->next;
    prev->next = prev->next->next;

    return tmp;
}

Node *remove_first(){
    if(head == NULL) return NULL;
    Node *tmp = head;
    head = head->next;

    return tmp;
}

void remove_under_ten(){
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