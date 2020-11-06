#include <stdint.h>
#include <stdlib.h>
typedef struct clan cl;
typedef struct clan * poz;
struct clan{
	int ke;
	int ex;
	poz next;
};

int unos(poz);
poz clan(int, int, poz);
int ispis(poz);

int main(){
	cl pl1, pl2;
	pl1.next=NULL;
	pl2.next=NULL;
	unos(&pl1); //2 fajla, svaki fajl jedan polinom
	unos(&pl2);
}

int unos(poz p){
	FILE *fp;
	int bk, be; //bk-buffer keoficijenta, be-buffer exponenta
	fp=fopen("polinom.txt", "r");
	while(feof(fp)){
		fscanf(fp, "%d %d", &bk, &be);
		p=clan(bk, be, p);
	}
}

poz clan(int bk, int be, poz p){
	poz q;
	q=(poz)malloc(sizeof(cl));
	p->ex=be;
	p->ke=bk;
	p->next=q;
	q->next=NULL;
	return q;
}

int ispis(poz p){
	while(p!=NULL){
		p=p->next;
		printf("%dx^%d", p->ke, p->ex);
	}
}
