#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct clan cl;
typedef struct clan* poz;
struct clan {
	int br;
	poz next;
};

int unija(poz, poz, poz);
int presj(poz, poz);
int unos(poz, int);
int ispis(poz);

int main() {
	cl l1, l2, un, pr;
	l1.next = NULL;
	l2.next = NULL;
	un.next = NULL;
	pr.next = NULL;
	unos(&l1, 2);
	unos(&l1, 3);
	unos(&l1, -3);
	unos(&l1, -2);
	unos(&l1, 0);
	unos(&l2, 3);
	unos(&l2, 3);
	unos(&l2, -3);
	unos(&l2, 0);
	ispis(&l1);
	ispis(&l2);
	unija(&l1, &l2, &un);
	ispis(&un);
	presj(&l1, &l2, &pr);
	ispis(&pr);
	return 0;
}

int ispis(poz p) {
	while (p->next != NULL) {
		p = p->next;
		printf("%d ", p->br);
	}
	puts("");
	return 1;
}

int unos(poz p, int x) {
	while (p->next != NULL && x <= p->next->br) {
		p = p->next;
	}
	if (x != p->br) {
		poz q;
		q = (poz)malloc(sizeof(cl));
		q->br = x;
		q->next = p->next;
		p->next = q;
	}
	return 1;
}
int unija(poz p, poz q, poz z) {
	while (p->next != NULL) {
		p = p->next;
		unos(z, p->br);
	}
	while (q->next != NULL) {
		q = q->next;
		unos(z, q->br);
	}
	return 1;
}
int presj(poz p, poz q, poz z) {
	q = q->next;
	p = p->next;
	/*while (p->next != NULL && q->next != NULL) {
		if (p->br < q->br) {
			q = q->next;
		}
		else if(p->br > q->br) {
			p = p->next;
		}
		else {
			unos(z, p->br);
			q = q->next;
			p = p->next;
		}
	}*/
	while (p != NULL || q != NULL) {
		if (p->br < q->br) {
			q = q->next;
		}
		else if (p->br > q->br) {
			p = p->next;
		}
		else {
			unos(z, p->br);
			q = q->next;
			p = p->next;
		}
	}
	return 1;
}
