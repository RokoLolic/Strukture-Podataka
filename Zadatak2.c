#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)
typedef struct osoba oso;
typedef struct osoba * poz;
struct osoba {
	char ime[10];
	char prezime[10];
	int god;
	poz next;
};
int upisp(poz);
int upisk(poz);
int ispis(poz);
int meni(poz);
int trazi(poz);
int brisi(poz);
poz trazipret(poz, char []);
int main() {
	struct osoba head;
	head.next = NULL;
	meni(&head);
	return 0;
}
int meni(poz p) {
	puts("Sto zelite uciniti");
	puts("P za upis na prvo mijesto, K za upis na kraj, I za ispis, Z za ugasiti program, B za brisati");
	int Z = 0;
	char a[1];
	while (Z==0) 
	{
		scanf("%s", a);
		switch(*a) {
			case 'P':
				upisp(p);
				break;
			case 'K':
				upisk(p);
				break;
			case 'I':
				ispis(p);
				break;
			case 'Z':
				Z = 1;
				break;
			case 'T':
				trazi(p);
				break;
			case 'B':
				brisi(p);
				break;
			default:
				puts("P za upis na prvo mijesto, K za upis na kraj, I za ispis, Z za ugasiti program, B za brisati");
		}
	}
	return 0;
}
int upisp(poz p) {
	poz q;
	q = (poz)malloc(sizeof(oso));
	q->next = p->next;
	p->next = q;
	char b[10];
	puts("Prvo upiši ime, prezime i na kraju godinu, sve u svojem retku");
	scanf("%s", b);
	strcpy(q->ime, b);
	scanf("%s", b);
	strcpy(q->prezime, b);
	scanf("%d", &(q->god));
	return 1;
}
int upisk(poz p) {
	poz q;
	q = (poz)malloc(sizeof(oso));
	while (p->next != NULL) {
		p = p->next;
	}
	q->next = NULL;
	p->next = q;
	char b[10];
	puts("Prvo upiši ime, prezime i na kraju godinu, sve u svojem retku");
	scanf("%s", b);
	strcpy(q->ime, b);
	scanf("%s", b);
	strcpy(q->prezime, b);
	scanf("%d", &(q->god));
	return 1;
}
int ispis(poz p) {
	while (p->next != NULL) {
		p = p->next;
		printf("%s %s %d\n", p->ime, p->prezime, p->god);
	}
	return 1;
}
int trazi(poz p) {
	char b[10];
	int i=0;
	puts("Upisi prezime koje trazis");
	scanf("%s", b);
	while ((p->next != NULL) && (p->prezime != b)) {
		p = p->next;
		i++;
	}
	printf("%d", i);
	return i;
}
int brisi(poz p) {
	char b[10];
	poz temp, prev;
	puts("Upisi prezime clana koje brises");
	scanf("%s", b);
	prev=trazipret(p, b);
	temp = prev->next;
	prev->next = temp->next;
	free(temp);
	return 1;
}
poz trazipret(poz q, char b[]) {
	while ((q->next != NULL) && (strcmp(q->next->prezime, b)!=0)) {
		q = q->next;
	}
	printf("prethodni je %s\n", q->prezime);
	return q;
}
