#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define maxi 30
#pragma warning(disable:4996)

struct cvor;
typedef struct cvor CVOR;
typedef struct cvor * poz;
struct cvor {
	char znak[1];
	poz lijevo;
	poz desno;
};

struct stog;
typedef struct stog STOG;
typedef struct stog * spoin;
struct stog {
	poz simb;
	spoin next;
};

int push(poz, spoin);
poz pop(spoin);

int printtree(poz, char*);

int addzn(poz, poz, spoin, char*);
int readf(char*);
int writef(char*);
int toinfix(poz, char*);

int push(poz p, spoin s) {
	spoin q;
	q = (spoin)malloc(sizeof(STOG));
	if (q == NULL) {
		puts("Alokacija memorije falila.");
		return -1;
	}
	q->simb = p;
	q->next = s->next;
	s->next = q;
	return 1;
}
poz pop(spoin s) {
	spoin temp;
	poz simbol;
	temp = s->next;
	s->next = temp->next;
	simbol = temp->simb;
	free(temp);
	return simbol;
}
int readf(char* s) {
	FILE* f;
	f = fopen("postfix.txt", "r");
	if (f == NULL) {
		puts("Alokacija memorije falila.");
		return -1;
	}
	while (feof(f) == 0) {
		fgets(s, maxi, f);
	}
	fclose(f);
	return 1;
}
int writef(char* s) {
	FILE* f;
	f = fopen("infix.txt", "w");
	fputs(s, f);
	fclose(f);
	return 1;
}
int addzn(poz l, poz r, spoin s, char *zn) {
	poz cv;
	cv = (poz)malloc(sizeof(CVOR));
	cv->desno = r;
	cv->lijevo = l;
	strcpy(cv->znak, zn);
	push(cv, s);
	return 1;
}
int addbr(spoin s, char *zn) {
	poz cv;
	cv = (poz)malloc(sizeof(struct cvor));
	strcpy(cv->znak, zn);
	cv->desno = NULL;
	cv->lijevo = NULL;
	push(cv, s);
	return 1;
}
int printtree(poz p, char *s) {
	if (p == NULL)
		return 1;
	if(isalnum(*(p->znak))==0)
		strcat(s, "(");
	printtree(p->lijevo, s);
	strcat(s, p->znak);
	printtree(p->desno, s);
	if (isalnum(*(p->znak)) == 0)
		strcat(s, ")");
	return 1;
}

int clear(poz p) {
	if (p == NULL) {
		return 1;
	}
	clear(p->lijevo);
	clear(p->desno);
	free(p);
	return 1;
}

int main() {
	STOG head;
	char *s, *spoc, infix[maxi], znak[5];
	int n = 0;
	poz temp, ltemp, rtemp;

	s = (char*)malloc(sizeof(char)*maxi);
	spoc = s;
	temp = ltemp = rtemp = NULL;
	strcpy(infix, "");
	strcpy(s, "");
	head.next = NULL;
	readf(s);
	while (strlen(s) != 0) {
		sscanf(s, "%s %n", znak, &n);
		if (isalnum(*znak) != 0) {
			addbr(&head, znak);
		}
		else {
			rtemp = pop(&head);
			ltemp = pop(&head);
			addzn(ltemp, rtemp, &head, znak);
		}
		s += n;
	}
	temp=pop(&head);
	printtree(temp, infix);
	printf("%s", infix);
	writef(infix);
	clear(temp);
	free(spoc);
	return 0;
}
