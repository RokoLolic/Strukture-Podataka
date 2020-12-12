#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define m 20
#pragma warning(disable:4996)
typedef struct cvor cl;
typedef struct cvor * poz;
struct cvor {
	float br;
	poz next;
};

float pop(poz);
int push(poz, float);
float racun(char *);
int postfix(char **);
int main() {
	char *s;
	s = (char*)malloc(sizeof(cl)*m);
	float rez;
	fgets(s, m, stdin);
	//postfix(&s);
	rez=racun(s);
	printf("%f", rez);
	return 0;
}

/*int postfix(char **i) {
	char z[1];
	int n;
	char* a, b;
	cl stog;
	stog.next = NULL;
	while (strlen(*i) != 0) {
		sscanf
	}
}*/

float racun(char* s) {
	int n, i;
	float a, b, z;
	char o; //operand
	cl stog;
	stog.next = NULL;
	while (strlen(s) != 0) {
		i=sscanf(s, "%f %n", &z, &n);
		if (i) {
			push(&stog, z);
		}
		else {
			o = s[0];
			switch (o) {
			case '+':
				a = pop(&stog);
				b = pop(&stog);
				push(&stog, a + b);
				break;
			case '-':
				a = pop(&stog);
				b = pop(&stog);
				push(&stog, b - a);
				break;
			case '*':
				a = pop(&stog);
				b = pop(&stog);
				push(&stog, a * b);
				break;
			case '/':
				a = pop(&stog);
				b = pop(&stog);
				push(&stog, b / a);
				break;
			default:
				puts("Krivi simbol");
			}
		}
		s += n;
	}
	return pop(&stog);
}

int push(poz p, float x) {
	poz q;
	q = (poz)malloc(sizeof(cl));
	q->next = p->next;
	p->next = q;
	q->br = x;
	return 1;
}

float pop(poz p) {
	float x;
	poz temp;
	temp = p->next;
	p->next = temp->next;
	x = temp->br;
	free(temp);
	return x;

}
