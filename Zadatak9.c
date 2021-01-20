#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

struct CVOR;
typedef struct CVOR* pos;
typedef struct CVOR {
	int br;
	pos left;
	pos right;
}cvor;

pos createnode(int);
pos findMax(pos);
pos findMin(pos);

pos createnode(int i) {
	pos p = (pos)malloc(sizeof(cvor));

	if (NULL == p) {
		puts("Aloacija memorije nije uspjela");
		return NULL;
	}

	p->br = i;
	p->left = NULL;
	p->right = NULL;
	return p;
}

pos insert(pos curr, pos el) {
	if (curr == NULL) {
		return el;
	}
	if (curr->br > el->br) {
		curr->left = insert(curr->left, el);
	}
	else if (curr->br < el->br) {
		curr->right = insert(curr->right, el);
	}
	else {
		free(el);
	}

	return curr;
}

void printInOrder(pos curr) {
	if (curr == NULL) return;
	printInOrder(curr->left);
	printf("%d ", curr->br);
	printInOrder(curr->right);
}

pos find(pos curr, int x) {
	if (NULL == curr) return NULL;

	if (curr->br = x) {
		return curr;
	}
	else if (curr->br > x) {
		return find(curr->left, x);
	}
	else {
		return find(curr->right, x);
	}
}

pos deleteNode(pos curr, int x) {
	if (NULL == curr) {
		return NULL;
	}
	if (curr->br == x) {
		if (curr->left != NULL) {
			pos tmp = findMax(curr->left);
			curr->br = tmp->br;
			curr->left = deleteNode(curr->left, tmp->br);
		}
		else if (curr->right != NULL) {
			pos tmp = findMin(curr->right);
			curr->br = tmp->br;
			curr->right = deleteNode(curr->right, tmp->br);
		}
		else {
			free(curr);
			return NULL;
		}
	}
	else if (curr->br > x) {
		curr->left = deleteNode(curr->left, x);
	}
	else {
		curr->right = deleteNode(curr->right, x);
	}
	return curr;
}

pos findMin(pos curr) {
	if (NULL == curr) return NULL;

	while (curr->left != NULL) curr = curr->left;

	return curr;
}

pos findMax(pos curr) {
	if (NULL == curr) return NULL;

	while (curr->right != NULL) curr = curr->right;

	return curr;
}

int main() {
	pos glava = createnode(2);
	pos a = createnode(1);
	pos b = createnode(3);
	pos c = createnode(4);
	insert(glava, a);
	insert(glava, b);
	insert(glava, c);
	printInOrder(glava);
	deleteNode(glava, 3);
	printInOrder(glava);
	return 1;
}
