#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define m 10
#pragma warning(disable:4996)

typedef struct student {
	char ime[m];
	char prezime[m];
	int bodovi;
}stud;
int brojac(char []); //funkcija, prima naziv datoteke; daje broj redaka
int upis(char [], int, stud *); /*funkcija prima naziv datoteke, broj redaka i adresu prvog clana niza;
								upisuje svaki redak u svoju strukturu student*/
int ispis(stud*, int, int); //ispisuje sve studente
int main()
{
	int n, maxb; //maxb je maxmalni broj bodova
	char a[m];
	puts("Upisi naziv datoteke");
	scanf("%s", a);
	n = brojac(a);
	puts("Upiši broj maksimalnih bodova");
	scanf("%d", &maxb);
	stud *s; //niz studenata
	s = (stud *)malloc(n * sizeof(stud));
	upis(a, n, s);
	ispis(s, n, maxb);
	return 0;
}
int brojac(char a[]) {
	FILE *fp;
	fp = fopen(a, "r");
	int i=1;
	char c;
	if (fp == NULL)
	{
		puts("Datoteka nije otvorena");
	}
	for (c = getc(fp); c != EOF; c = getc(fp)) {
		if (c == '\n') {
			i++;
		}
	}
	fclose(fp);
	return i;
}
int upis(char a[], int n, stud *s) {
	FILE *fp;
	fp = fopen(a, "r");
	int i;
	for (i = 0; i < n; i++) {
		fscanf(fp, "%s %s %d", (s + i)->ime, (s + i)->prezime, &(s + i)->bodovi);
	}
	fclose(fp);
	return 1;
}
int ispis(stud *s, int n, int maxb) {
	int i;
	for (i = 0; i < n; i++) {
		printf("%s %s %d/%d %f\n", (s + i)->ime, (s + i)->prezime, (s + i)->bodovi, maxb, ((float)(s + i)->bodovi/(float)maxb * 100));
	}
	return 1;
}