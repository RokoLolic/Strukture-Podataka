#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define m 15 //najveci dopusten naziv
#pragma warning(disable:4996)
typedef struct direktorij DIREKTORIJ;
typedef struct direktorij* poz;

struct direktorij {
	char ime[m];
	poz child;
	poz sibling;
};

typedef struct stog stog;
typedef struct stog* clan;

struct stog {
	poz mapa;
	clan next;
};

int md(char*, poz);
int cddir(char*, poz*);
poz cd(clan);
int dir(poz);
int die(poz, poz);

int pop(clan);
int push(clan ,poz);
int clear(clan);

char* zadnji(char, char*);

int main() {
	char input[m], path[50];
	DIREKTORIJ c;
	poz p; //trenutna pozicija
	p = &c;
	poz glavni = &c;
	stog head; //inicijalizira stog za cd..
	head.next = NULL;
	strcpy(path, "C:");
	strcpy(c.ime, "C:");
	c.child = NULL;
	c.sibling = NULL;
	char com[m], name[m]; //com=naredba, name=ime datoteke
	push(&head, &c);
	while (1) {
		fgets(input, m, stdin);
		sscanf(input, "%s %s", com, name);
		if(strcmp(com, "md")==0){
			md(name, p);
		}
		else if (strcmp(com, "cddir") == 0) {
			cddir(name, &p);
			push(&head, p);
			strcat(path, "\\");
			strcat(path, p->ime);
			printf("%s\n", path);
		}
		else if (strcmp(com, "cd..") == 0) {
			p=cd(&head);
			char* kraj = zadnji('\\', path);
			*kraj = '\0';
			printf("%s\n", path);
		}
		else if (strcmp(com, "dir") == 0) {
			dir(p);
			printf("%s\n", path);
		}
		else {
			clear(&head); 
			die(&c, glavni);
			break;
		}
	}
	return 0;
}

poz cd(clan s) {
	pop(s);
	poz p = s->next->mapa;
	return p;
}

int md(char* n, poz p){
	poz q;
	q = (poz)malloc(sizeof(DIREKTORIJ));
	q->child = NULL;
	q->sibling = NULL;
	strcpy(q->ime, n);
	if (p->child == NULL) {
		p->child = q;
	}
	else {
		poz temp;
		temp = p->child;
		while (temp->sibling != NULL) {
			temp = temp->sibling;
		}
		temp->sibling = q;
	}
	return 1;
}
int cddir(char* n, poz* p) {
	if ((**p).child != NULL) {
		*p = (**p).child;
		while ((**p).sibling!=NULL) {
			if (strcmp((**p).ime, n) == 0)
				return 1;
			*p = (**p).sibling;
		}
	}
	return 1;
}

int dir(poz p) {
	poz temp = p->child;
	while (temp != NULL) {
		printf("%s ; ", temp->ime);
		puts("");
		temp = temp->sibling;
	}
	return 1;
}

int die(poz p, poz g) {
	if (p == NULL)
		return 1;
	die(p->child, g);
	die(p->sibling, g);
	if(p!=g)
		free(p);
	return 1;
}

int push(clan s , poz p) {
	clan q;
	q = (clan)malloc(sizeof(stog));
	q->next = s->next;
	s->next = q;
	q->mapa = p;
	return 1;
}

int pop(clan s) {
	clan temp;
	temp = s->next;
	s->next = temp->next;
	/*temp->mapa->child = NULL;
	temp->mapa->sibling = NULL;*/
	temp->mapa = NULL;
	free(temp);
	return 1;
	//poz povratna = temp->mapa; //adresa mape koje vraca
	//temp->mapa = null;
	//free(temp);
	//return povratna;
}
int clear(clan s) { //cisti cijeli stog i vraca adresu prvog direktorija (C:)
	clan temp;
	while (s->next != NULL) {
		temp = s->next;
		s->next = temp->next;
		free(temp);
	}
	return 1;
}
char* zadnji(char c, char* r) { //zadnja pojava chara c u stringu r
	char * rez = NULL;
	while (*r != '\0') {
		if (c == *r) {
			rez = r;
		}
		r++;
	}
	return rez;
}
