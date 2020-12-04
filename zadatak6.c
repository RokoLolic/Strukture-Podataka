#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define a 10
#define b 100

struct cvor;
typedef struct cvor CVOR; 
typedef struct cvor * poz;
struct cvor{
	int br;
	poz next;
};
int push(poz);
int pop(poz);

int main(){
	CVOR red;
	CVOR stog;
	poz last;
	last=&red;
	red.next=NULL;
	stog.next=NULL;
	srand((unsigned)(time(NULL)));
	puts("Red");
	push(last);
	push(last);
	push(last);
	push(last);
	pop(&red);
	pop(&red);
	pop(&red);
	puts("Stog");
	push(&stog);
	push(&stog);
	push(&stog);
	pop(&stog);
	pop(&stog);
	return 0;
}
int push(poz l){
	poz q;
	q=(poz)malloc(sizeof(CVOR));
	q->br=rand()%(b-a+1)+a;
	q->next=l->next;
	l->next=q;
	l=q;
	return 1;
}
int pop(poz p){
	poz temp;
	temp=p->next;
	printf("%d", temp->br);
	p->next=temp->next;
	free(temp);
	return 1;
}
