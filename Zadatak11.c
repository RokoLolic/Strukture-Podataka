#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#pragma warning(disable:4996)

#define max 11
#define str 256

struct cvorliste;
typedef struct cvorliste * poz;
typedef struct cvorliste * lista;
struct hashT;
typedef struct hashT *hashtab;

hashtab inicijaliziraj(int);
void izbrisi(hashtab);
poz trazi(char*, char*, hashtab);
void dodaj(char*, char*, int, hashtab);
int dobijkljuc(char*);
void push(poz, char*, char*, int);
void ispisi(hashtab);

struct cvorliste {
	char ime[str];
	char prez[str];
	int matbr;
	poz next;
};
struct hashT {
	int velicina;
	poz* red;
};
int main() {
	hashtab tablica;
	tablica = inicijaliziraj(max);
	char p[] = "iva", d[] = "kovac", a[]="luka", b[]="prancic", c[]="ante", e[]="kola", ime[str], prezime[str];
	poz temp;
	dodaj(p, d, 123, tablica);
	dodaj(a, b, 321, tablica);
	dodaj(c, e, 564, tablica);
	dodaj(a, d, 986, tablica);
	ispisi(tablica);
	puts("Upisite ime, zatim prezime ucenika");
	scanf("%s %s", ime, prezime);
	temp = trazi(ime, prezime, tablica);
	if (temp != NULL) {
		printf("%d", temp->matbr);
	}
	izbrisi(tablica);

	return 1;
}
void izbrisi(hashtab tab) {
	poz vezlist, temp, brisi;

	for (int i = 0; i < tab->velicina; i++) {
		temp = tab->red[i];
		while (temp->next != NULL) {
			brisi = temp->next;
			temp->next = brisi->next;
			free(brisi);
		}
		free(tab->red[i]);
	}
}

poz trazi(char * im, char* pr, hashtab tab) {
	int kljuc = dobijkljuc(pr) % (tab->velicina);
	poz temp = tab->red[kljuc];
	while (temp->next != NULL) {
		temp = temp->next;
		if ((strcmp(temp->ime, im)==0) && (strcmp(temp->prez, pr)==0)) {
			return temp;
		}
	}
	return NULL;
}
hashtab inicijaliziraj(int vel) {
	hashtab tablica;
	int i = 0;
	poz* linije;
	//tablica = (hashtab)malloc(sizeof(lista)*vel + sizeof(int));
	tablica = (hashtab)malloc(sizeof(hashT));
	linije = (poz*)malloc(sizeof(poz)*vel);
	tablica->red = linije;
	tablica->velicina = vel;
	for (i = 0; i < vel; i++) {
		(*(tablica->red + i)) = (poz)malloc(sizeof(cvorliste));
		(*(tablica->red + i))->next = NULL;
	}
	return tablica;
}
int dobijkljuc(char* naziv) {
	int kljuc=0, i=0;
	while (strlen(naziv) != 0 && i < 5) {
		kljuc += (int) *(naziv + i);
		i++;
	}
	return kljuc;
}
void dodaj(char* im, char* pr, int mb, hashtab tab) {
	int kljuc;
	kljuc = dobijkljuc(pr) % (tab->velicina);
	push(tab->red[kljuc], im, pr, mb);
	return;
}
void ispisi(hashtab tab) {
	poz temp;
	for (int i = 0; i < tab->velicina; i++) {
		printf("%d. red: ", i);
		temp = tab->red[i];
		//temp = temp->next;
		while (temp->next != NULL) {
			temp = temp->next;
			printf("|%s %s %d| ",temp->prez, temp->ime, temp->matbr);
		}
		puts("");
	}
}
void push(poz p, char* im, char* pr, int m) {
	poz q;
	char punoip[str], punoiptemp[str];
	strcpy(punoip, im);
	strcat(punoip, " ");
	strcat(punoip, pr);
	while (p->next != NULL) {
		if (strcmp(pr, p->prez) > 0) {
			break;
		}
		else if ((strcmp(pr, p->prez) == 0) && (strcmp(im, p->ime) >= 0)) {
			break;
		}
		else {
			p = p->next;
		}
	}
	q = (poz)malloc(sizeof(cvorliste));
	strcpy(q->ime, im);
	strcpy(q->prez, pr);
	q->matbr = m;
	q->next = p->next;
	p->next = q;
	return;
}
