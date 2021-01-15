#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)
#define max 20
struct cvor;
typedef struct cvor CVOR;
typedef struct cvor * poz;
struct cvor {
	char *znak;
	poz lijevo;
	poz desno;
};

struct stog;
typedef struct stog STOG;
typedef struct stog * spoin;
struct stog{
	poz simb;
	spoin next;
}

int push(poz, spoin);
poz pop(spoin);

int add(poz, poz, poz, spoin);
int readf(char*);
int writef(char*);
int toinfix(poz, char*);

int push(poz p, spoin s){
	spoin q;
	q=(spoin)malloc(sizeof(STOG));
	if(q==NULL){
		puts("Alokacija memorije falila.");
		return -1;
	}
	q->simb=p;
	q->next=s->next;
	s->next=q;
	return 1;
}
poz pop(spoin s){
	spoin temp;
	poz simbol;
	temp=s->next;
	s->next=temp->next;
	simbol=temp->simb;
	free(temp);
	return simbol;
}
int readf(char* s){
	FILE* f;
	f=fopen("postfix.txt", "r");
	if(f==NULL){
		puts("Alokacija memorije falila.");
		return -1;
	}
	while(feof==0){
		fgets(s, max, f);
	}
	fclose(f);
	return 1;
}
int writef(char* s){
	FILE* f;
	f=fopen("infix.txt", "w");
	fputs(s, f);
	return 1;
}
int add(poz l, poz r, poz cv, spoin s){
	cv->desno=r;
	cv->lijevo=l;
	push(cv, s);
	return 1;
}

int main(){
	STOG head;
	char s[max], infix[max];
	int n;

	head.next=NULL;
	readf(s);
	sscanf(s, "%s %n", 

