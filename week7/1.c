#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX 100
#define BUFFER_LEN 100

// TODO : 1차원 다항식 정의하기, 다항식의 이름은 f,g 와 같은 x 를 제외한 영문 소문자
// * 변수는 항상 x 이다 
// * 각 항의 지수는 음이 아닌 정수, 계수는 정수 
// * 다항식을 정의할 때, 문장에 공백은 자유롭고 프로그램에서 처리 해준다
// * 항들이 차수에 대해서 내림차순으로 정의 되지 않았지만 print 명령을 받아서 출력할 때는 지수에 대한 내림차순으로 정렬 해줘야 한다.
// * 동일 이름의 함수를 재정의 할수도 있지만, 그렇게 되면 같은 이름을 사용하던 기존의 함수는 지워진다

// * 연결리스트로 구현한다. 하나의 다항식을 표현하는 구조체 polynomial 을 하나 정의 한다.
// * 그 다항식의 항 또한 구조체를 사용한 연결리스트로 구현한다 

typedef struct term{
    int coef; //지수
    int expo; //차수
    struct term *next;
} Term;

typedef struct polynomial{
    Term *first;
    char *name;
    // 다항식에 존재하는 항의 갯수
    int size;
} Polynomial;
// 여러개의 다항식들을 저장해 두기 위한 polynomial 배열
Polynomial *polys[MAX];
// polys 배열에 저장 되어 있는 다항식의 갯수
int n = 0;

// ! 구조체 객체를 구성하는 멤버들의 값을 초기화 하기
Term *create_term_instance(){
    Term *t = (Term *)malloc(sizeof(Term));
    t->coef = 0;
    t->expo = 0;
    return t;
}

Polynomial *create_polynomial_instance(char name){
    Polynomial *p = (Polynomial *)malloc(sizeof(Polynomial));
    p->first = NULL;
    p->name = name;
    p->size = 0;
    return p;
}
// poly가 가리키는 다항식에 새로운 하나의 항 (c, e) 를 추가하는 경우 c^e
// 1. 추가하려는 항이 이미 존재하는 항인 경우 : 계수만큼 더해준다
// 2. 없는 경우 : 내림차순으로 정렬하고 추가한다 내림차순 하는 경우 e를 기준으로 정렬 한다. add_after / add_first
void add_term(int c, int e, Polynomial *poly){
    if(c == 0) return;

    Term *p = poly->first;
    Term *q = NULL;

    while(p != NULL & p->expo > e){
        q = p;
        p = p->next;
    }

    // 특이 케이스 처리하기
    // 1. 추가하려는 항이 이미 다항식에 존재하는 경우
    if(p != NULL && p->expo == e){
        p->coef += c;
        // ! 이미 존재하는 항의 차수여서 계수끼리 더했더니 0이 되는 경우, 그 노드를 연결리스트에서 삭제 해줘야함
        if(p->coef == 0){
            if(q == NULL) poly->first = p->next; // 첫번째 항이 삭제되는 경우
            else q->next = p->next;
            
            poly->size -= 1;
            free(p); // p 동적 메모리 해제
        }
        return ;
    }
    // 일반 케이스 처리하기
    // 1. 추가하려는 항이 다항식에 존재하지 않는 경우
    Term *term = create_term_instance();
    term->coef = c;
    term->expo = c;

    if(q == NULL){
        term->next = poly->first;
        poly->first = term;
    }else{
        term->next = p;
        q->next = term;
    }
    poly->size += 1;
}
// 다항식의 값 계산해서 전달하기
int eval(Polynomial *poly, int x){
    int result = 0;
    Term *t = poly->first;
    while(t != NULL){
        result += eval(t, x);
        t = t->next;
    }
    return result;
}
int eval(Term *term, int x){
    int result = term->coef;
    for(int i = 0; i < term->expo; i ++) result *= x;

    return result;
}
// 다항식 출력하기
void print_poly(Polynomial *poly){
    printf("%c = ", poly->name);
    Term *t = poly->first;
    while(t != NULL){
        print_term(t->coef, t->expo);
        if(t->next->coef >= 0) printf("+");
        t = t->next;
    }
}
void print_term(int c, int e){
    if(e == 0) printf("%d", c);
    else if(e == 1) printf("$dx", c);
    else printf("%dx^%d",c, e);
}
// 사용자에게 명령 입력 받기
int read_line(FILE *fp, char *str ,int n){
    int ch, i = 0;

    while((ch = fgetc(fp)) != '\n' && ch != EOF){
        if(i < n) str[i ++] = ch;
    }
    str[i] = '\0';
    return i;
}

void handle_print(char name){
    for(int i = 0; i < n; i++){
        if(strcmp(polys[i]->first, name) == 0) print_poly(polys[i]);
        return; 
    }
    printf("No Polynomial..."); 
}

void handle_calc(char name, char *x_str){
    // ! char *x_str 문자형 -> 정수형
    for(int i = 0; i < n; i++){
        if(strcmp(polys[i]->first, name) == 0) eval(polys[i], (int)x_str[0]);
        return; 
    }
    printf("No Polynomial...");
}
// expression 공백 제거
void erase_blanks(char *str, int size){
    int i = 0, j = 0;
    while(j < size){
        if(str[j] != " ") str[i++] = str[j];
        j += 1;
    }
    str[i] = '\0';
}
Term *parse_and_add_term(char *expr, int start, int end, Polynomial *p_poly){
    int i = start;
    int sign_coef = 1, coef = 0, expo = 1;

    // 지수 : 0(상수), 1, 1 이상
    // 계수 : 1, -1, -2 이하, 2 이상

    // 부호 check
    if(expr[i] == '+') i++;
    else if(expr[i] == '-'){
        sign_coef = -1;
        i ++;
    }

    // 문자열로 돼있는 값 읽어서 숫자로 변경하기 절댓값 읽기
    while(i < end && expr[i] >= '0' && expr[i] <= '9'){
        coef = coef * 10 + (int)(expr[i] - '0');
        i ++;
    }   
    // 부호 계산하기
    if(coef == 0) coef = sign_coef;
    else coef *= sign_coef;

    // 계수 부분만 읽었는데, i >= end 를 만족한다는 것은 x 가 존재하지 않는다는 것 -> 상수항
    if(i >= end){
        add_term(coef, 0, p_poly);
        return 1;
    }

    if(expr[i] != 'x') return 0;
    i++;

    if(i >= end){
        add_term(coef, 1, p_poly);
        return 1;
    }

    if(expr[i] != '^') return 0;
    i ++;

    expo = 0;
    while(i < end && expr[i] >= '0' && expr[i] <= '9'){
        expo = expo * 10 + (int)(expr[i] - '0');
        i ++;
    }

    add_term(coef, expo, p_poly);
    return 1;
}
// 새로운 다항식을 추가하는 함수
Polynomial *create_by_parse_polynomial(char name, char *body){
    Polynomial *ptr_poly = create_polynomial_instance(name);

    int i = 0, begin_term = 0;
    // begin_term ~ i 가 하나의 항을 의미함 [begin_term, i) 시작 폐구간 ~ 끝 개구간
    while(i < strlen(body)){
        if(body[i] == '+' || body[i] == '-') i ++;
        while(i < strlen(body) && body[i] != '+' && body[i] != '-') i ++;
        /*
        int result = parse_and_add_term(body, begin_term, i, ptr_poly);
        if(result == 0){
            destroy_polynomial(ptr_poly);
            return NULL;
        }
        */
        begin_term = i;
    }
    return ptr_poly;
}
// 새로 만들어진 다항식을 polys 배열에 넣기
void insert_polynomial(Polynomial *ptr_poly){
    for(int i = 0; i < n; i++){
        if(polys[i]->name == ptr_poly->name){
            //destroy_polynomial(polys[i]);
            polys[i] = ptr_poly;
            return;
        }
    }
    polys[n++] = ptr_poly;
}
// 다항식 생성에 문제가 있거나, 기존의 다항식과 같은 이름의 다항식을 덮어쓰는 경우 기존의 다항식을 삭제 시켜야함
void destroy_polynomial(Polynomial *ptr_poly){
    if(ptr_poly == NULL) return;
    // 다항식을 가리키는 Poly 구조체 한개, 그리고 그 poly 구조체에 속하는 term 구조체들 모두 동적메모리 할당을 통해 만든 것 이므로, 시작부터 끝까지 따로 free
    Term *t = ptr_poly->first, *tmp;
    while(t != NULL){
        tmp = t;
        t = t->next;
        free(tmp);
    }
    free(ptr_poly);
}
void handle_definition(char *expression){
    // 새로운 다항식을 정의하는 명령 문자열을 받으면 우선 모든 공백을 제거 해준다
    erase_blanks(expression, strlen(expression));

    char *f_name = strtok(expression, "=");
    if(f_name == NULL || strlen(f_name) != 1){
        printf("Unsupportted Commnad...\n");
        return;
    }
    char *exp_body = strtok(NULL, "=");
    if(exp_body == NULL || strlen(exp_body) <= 0){
        printf("Invaild expression format...\n");
        return;
    }
    // 기존의 함수를 재정의 or  완전 새로운 함수 정의 
    if(exp_body[0] >= 'a' && exp_body[0] <= 'z' && exp_body[0] != 'x'){
        char *former = strtok(exp_body, "+");
        if(former == NULL || strlen(former) != 1){
            printf("Invalid expression format...\n");
            return;
        }
        char *later = strtok(exp_body, "+");
        if(later == NULL || strlen(later) != 1){
            printf("Invalid expression format...\n");
            return;
        }
        /*
        // 존재하는 다항식의 합으로 새로운 다항식을 만드는 경우
        // Polynomial *pol = create_by_add_two_polynomias(f_name[0], former[0], later[0]);
        if(pol == NULL){
            printf("Invaild expression format...\n");
            return;
        }
        // 여러개의 다항식이 존재하는 polys 배열에 추가 해야함
        // 여기서 f = f+g 와 같이 이미 존재하는 f 에 대한 재정의를 해주는 경우와 같은 특수 케이스를 처리해줘야함.
        insert_polynomial(pol);
        */
    }else{
        Polynomial *pol = create_by_parse_polynomial(f_name[0], exp_body);
        if(pol == NULL){
            printf("Invaild expression format...\n");
            return;
        }
        insert_polynomial(pol);
    }
}
 

void process_command(){
    char command_line[BUFFER_LEN];
    char copied[BUFFER_LEN];
    char *command, *arg1, *arg2;

    while(1){
        printf("$ ");
        if(read_line(stdin, command_line, BUFFER_LEN) <= 0) continue;

        strcpy(copied, command_line);
        command = strtok(command_line, " ");
        if(strcmp(command, "print") == 0){
            arg1 = strtok(NULL, " ");
            if(arg1 == NULL){
                printf("Invalid Input...\n");
                continue;
            }
            handle_print(arg1[0]);
        }else if(strcmp(command, "calc") == 0){
            arg1 = strtok(NULL, " ");
            if(arg1 == NULL){
                printf("Invalid Input...\n");
                continue;
            }
            arg2 = strtok(NULL, " ");
            if(arg2 == NULL){
                printf("Invalid Input...\n");
                continue;
            }
            // ! arg2 는 문자열에서 토크나이징을 통해서 얻은 char 형 변수 이므로 계산을 위해서는 형변환을 해줘야함
            hadle_calc(arg1[0], arg2);
        }else if(strcmp(NULL, "exit") == 0){
            break;
        }else{
            // 출력, 계산, 반복문 종료도 아니면 새 다항식을 poly 배열에 추가하는 것을 의미함. 따라서 copied 전체를 인자로 넘겨준다
            handle_definition(copied);
        }
    }
}

int main(){
    
    return 0;
}