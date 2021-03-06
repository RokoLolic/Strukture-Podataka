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
poz trazipret(poz, char[]);
poz trazinakon(poz, char[]);
int upisprije(poz);
int upisnakon(poz);
int sort(poz);
int datci(poz);
int datup(poz);
int main() {
	struct osoba head;
	head.next = NULL;
	meni(&head);
	return 0;
}
int meni(poz p) {
	puts("Sto zelite uciniti");
	puts("P za upis na prvo mijesto, K za upis na kraj, I za ispis, Z za ugasiti program, B za brisati, N za unos nakon elementa, S za unos ispred nekog elementa, O za sortirati, C za citati iz datoteke, U za upisati u datoteku");
	int Z = 0;
	char a[1];
	while (Z == 0)
	{
		scanf("%s", a);
		switch (*a) {
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
		case 'N':
			upisnakon(p);
			break;
		case 'S':
			upisprije(p);
			break;
		case 'O':
			sort(p);
			break;
		case 'C':
			datci(p);
			break;
		case 'U':
			datup(p);
			break;
		default:
			puts("P za upis na prvo mijesto, K za upis na kraj, I za ispis, Z za ugasiti program, B za brisati, N za unos nakon elementa, S za unos ispred nekog elementa, O za sortirati, C za citati iz datoteke, U za upisati u datoteku");
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
	char b[10];
	q = (poz)malloc(sizeof(oso));
	while (p->next != NULL) {
		p = p->next;
	}
	q->next = NULL;
	p->next = q;
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
	int i = 0;
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
	prev = trazipret(p, b);
	temp = prev->next;
	prev->next = temp->next;
	free(temp);
	return 1;
}
poz trazinakon(poz q, char b[]) {
	while ((q->next != NULL) && (strcmp(q->prezime, b) != 0)) {
		q = q->next;
	}
	if (q->next != NULL)
		q = q->next;
	printf("sljedeci je %s\n", q->prezime);
	return q;
}
poz trazipret(poz q, char b[]) {
	while ((q->next != NULL) && (strcmp(q->next->prezime, b) != 0)) {
		q = q->next;
	}
	printf("prethodni je %s\n", q->prezime);
	return q;
}
int upisprije(poz p) {
	poz q, prev;
	char b[10];
	q = (poz)malloc(sizeof(oso));
	puts("Upisi prije kojeg prezimena upisujes");
	scanf("%s", b);
	prev = trazipret(p, b);
	q->next = prev->next;
	prev->next = q;
	puts("Prvo upiši ime, prezime i na kraju godinu, sve u svojem retku");
	scanf("%s", b);
	strcpy(q->ime, b);
	scanf("%s", b);
	strcpy(q->prezime, b);
	scanf("%d", &(q->god));
	return 1;
}
int upisnakon(poz p) {
	poz q;
	char b[10];
	q = (poz)malloc(sizeof(oso));
	puts("Nakon kojeg upisujes?");
	scanf("%s", b);
	while ((p->next != NULL) && (p->prezime != b)) {
		p = p->next;
	}
	q->next = p->next;
	p->next = q;
	puts("Prvo upiši ime, prezime i na kraju godinu, sve u svojem retku");
	scanf("%s", b);
	strcpy(q->ime, b);
	scanf("%s", b);
	strcpy(q->prezime, b);
	scanf("%d", &(q->god));
	return 1;
}
int datci(poz p){
	FILE *fp;
	fp = fopen("student.txt", "r");
	if (fp == NULL) {
		puts("Datoteka nije otvorena");
	}
	while (feof(fp) == 0) {
		poz q;
		q = (poz)malloc(sizeof(oso));
		fscanf(fp, "%s", q->ime);
		fscanf(fp, "%s", q->prezime);
		fscanf(fp, "%d", &q->god);
		q->next = p->next;
		p->next = q;
	}
	return 1;
}
int datup(poz p) {
	FILE *fp;
	fp = fopen("meta.txt", "w+");
	if (fp == NULL) {
		puts("Datoteka nije otvorena");
	}
	while (p->next!=NULL){
		p = p->next;
		fprintf(fp, "%s\n", p->ime);
		fprintf(fp, "%s\n", p->prezime);
		fprintf(fp, "%d\n", p->god);
	}
	return 1;
}
int sort(poz p) {
	poz prev, i, t, kr;
	kr = NULL;
	while (p->next != kr) {
		prev = p;
		i = p->next;
		while (i->next != kr) {
			if (strcmp(i->prezime, i->next->prezime)>0) {
				t = i->next;
				prev->next = t;
				i->next = t->next;
				t->next = i;

				i = t;
			}
			prev = i;
			i = i->next;
		}
		kr = i;
	}
	return 0;
}

