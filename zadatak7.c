#include <stdio.h>
#include <stdlib.h>
#include <string>
#define m 10


typedef 
float racun(char *);
int main(){
	char s[m];
}

float racun(char* s){
	int i, n; //i = je li sscanf dobia vrijednost, n=broj bitvoa koji je sscanf procitao
	float br, a, b;
	char o; //operacija
	while(strlen(s)){
		i = sscanf(s, "%f %n", &br, &n);
		if(i)
			push(br);
		else
		{
			a=pop();
			b=pop();
			
		}
	}
}
