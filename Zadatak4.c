#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)
#define m 40 // najveci broj clanova  u retku datoteke
typedef struct clan cl;
typedef struct clan * poz;
struct clan {
	int ke;
	int ex;
	poz next;
};

int unos(poz, int);
int elem(int, int, poz);
int ispis(poz);
int zbroj(poz, poz, poz);
int mnoz(poz, poz, poz);
poz skok(poz); //pokazivac na clan gleda moze li skociti na sljedeci
int brisi(poz);

int main() {
	cl pl1, pl2, zb, mn;
	pl1.next = NULL;
	pl2.next = NULL;
	zb.next = NULL;
	mn.next = NULL;
	unos(&pl1, 1); //fajl s vise redaka, svaki redak jedan polinom, broj pored je broj retka s kojeg citamo
	unos(&pl2, 2);
	ispis(&pl1);
	ispis(&pl2);
	zbroj(&pl1, &pl2, &zb);
	ispis(&zb);
	brisi(&zb);
	ispis(&zb);
	mnoz(&pl1, &pl2, &mn);
	ispis(&mn);
	return 0;
}

int unos(poz p, int r) {
	FILE *fp;
	int i;
	char *b, *temp;
	b = (char *)malloc(sizeof(char)*m);
	temp = (char *)malloc(sizeof(char)*m);
	temp = b;
	int bk, be, n; //bk-buffer keoficijenta, be-buffer exponenta
	fp = fopen("polinom.txt", "r");
	if (fp == NULL) {
		puts("Pogreska, fajl nije ucitan");
	}
	for (i = 0; i < r - 1; i++) {
		fgets(b, m, fp);
	}
	fgets(b, m, fp);
	while (strlen(b)!=0) {
		sscanf(b, "%d %d %n", &bk, &be, &n);
		elem(bk, be, p);
		b = (b + n);
		}
	b = temp;
	free(temp);
	return 0;
}
int elem(int bk, int be, poz p) {
	while (p->next != NULL && be > p->next->ex) {
		p = p->next;
	}
	poz q;
	q = (poz)malloc(sizeof(cl));
	q->ex = be;
	q->ke = bk;
	q->next = p->next;
	p->next = q;
	return 0;
}

int ispis(poz p) {
	while (p->next != NULL) {
		p = p->next;
		printf("%dx^%d + ", p->ke, p->ex);
	}
	puts("");
	return 0;
}
int zbroj(poz p, poz q, poz z) {
	while (p->next != NULL) {
		p = p->next;
		elem(p->ke, p->ex, z);
	}
	while (q->next != NULL) {
		q = q->next;
		elem(q->ke, q->ex, z);
	}
	int check = 1;
	while (z->next != NULL) {
		poz prev = z;
		if(check)
			z = z->next;
		check = 1;
		while ((z->next != NULL) && (z->ex == z->next->ex)) {
			poz ne = z->next; //sljedeci clan
			z->ke += ne->ke;
			z->next = ne->next;
			free(ne);
		}
		if (z->ke == 0) {
			poz temp = z;
			prev->next = z->next;
			z = z->next;
			check = 0;
			free(temp);
		}
	}
	return 1;
}
int mnoz(poz p, poz q, poz z) {
	cl r1, r2;
	r1.next = NULL;
	r2.next = NULL;
	while (p->next != NULL) {
		p = p->next;
		while (q->next != NULL) {
			q = q->next;
			elem(p->ke*q->ke, p->ex + q->ex, &r1);
		}
		zbroj(&r1, &r2, z);
	}
	return 1;
}
int brisi(poz p) {
	/*poz poc = p;*/
	poz poc = p;
	poz temp;
	p = p->next;
	while (p != NULL) {
		temp = p;
		p = p->next;
		free(temp);
	}
	free(poc->next);
	/*temp = poc->next;
	free(temp);*/
	return 1;
}
/*int zbroj(poz p, poz q, poz z) {
	p = p->next;
	q = q->next;
	while (p->next != NULL && q->next != NULL) {
		while (p->ex < q->ex) {
			elem(p->ke, p->ex, z);
			p=skok(p);
		}
		while (p->ex > q->ex) {
			elem(q->ke, q->ex, z);
			q=skok(q);
		}
		if (p->ke + q->ke != 0) {
			elem(p->ke + q->ke, p->ex, z);
			p=skok(p);
			q=skok(q);
		}
	}
	if (p->next == NULL) {
		int check = 0; //provjerava je li zadnji p iskoristen
		do {
			if ((p->ex==q->ex)&& (p->ke + q->ke != 0)&& check==0) {
				elem(p->ke + q->ke, p->ex, z);
				check = 1;
			}
			else {
				elem(q->ke,q->ex, z);
				q = skok(q);
			}
		} while (q->next != NULL);
		}
	if (q->next == NULL) {
		int check = 0;
		do {
			if ((p->ex == q->ex) && p->ke + q->ke != 0 && check==0) {
				elem(p->ke + q->ke, p->ex, z);
				p = skok(p);
				check = 1;
			}
			else {
				elem(p->ke, p->ex, z);
				p = skok(p);
			}
		} while (p->next != NULL);
	}
	return 1;
}

poz skok(poz p) {
	if ((p->next) != NULL)
	{
		p = (p->next);
	}
	return p;
}*/
