#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define a 10
#define b 100

struct cvor;
typedef struct cvor CVOR;
typedef struct cvor * poz;
struct cvor {
	int br;
	poz next;
};
int pushr(poz*, poz);
int pushs(poz);
int pop(poz);

int main() {
	CVOR red;
	CVOR stog;
	poz last;
	last = &red;
	red.next = NULL;
	stog.next = NULL;
	srand((unsigned)(time(NULL)));
	puts("Red");
	pushr(&last, &red);
	pushr(&last, &red);
	pushr(&last, &red);
	pushr(&last, &red);
	pop(&red);
	pop(&red);
	pop(&red);
	pop(&red);
	pushr(&last, &red);
	puts("Stog");
	pushs(&stog);
	pushs(&stog);
	pushs(&stog);
	pop(&stog);
	pop(&stog);
	return 0;
}
int pushr(poz* l, poz r) {
	poz q;
	q = (poz)malloc(sizeof(CVOR));
	q->br = rand() % (b - a + 1) + a;
	q->next = (**l).next;
	(**l).next = q;
	*l = q;
	printf("PUSH %d\n", q->br);
	return 1;
}
int pushs(poz l) {
	poz q;
	q = (poz)malloc(sizeof(CVOR));
	q->br = rand() % (b - a + 1) + a;
	q->next = l->next;
	l->next = q;
	printf("PUSH %d\n", q->br);
	return 1;
}
int pop(poz p) {
	poz temp;
	temp = p->next;
	printf("POP %d\n", temp->br);
	p->next = temp->next;
	free(temp);
	return 1;
}
