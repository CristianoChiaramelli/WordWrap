#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN(a,b) (((a)<(b))?(a):(b))

char **getInput(int *n, int *lineSize){
	int i;
	ssize_t wordSize;
	scanf("%d", n);
	scanf("%d", lineSize);

	char **vector = (char**) malloc(sizeof(char*) * (*n));

	getchar();
    for (i=0; i<*n; i++){
    	vector[i] = (char*) malloc(sizeof(char)*(*lineSize+1));
		int pos = getline((&vector[i]), &wordSize, stdin);
	}
	return vector;
}

void printVector(char **vector, int n){
	int i;
	for (i=0; i<n; i++){
		printf ("%s", vector[i]);
	}
}

int main(int argc, char **argv){
	int n, lineSize;
	char **vector = getInput(&n, &lineSize);

	printVector(vector, n);
}
