#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

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

		vector[i][pos-1] = '\0';
	}
	return vector;
}

int *getWordSizes(char **vector, int n){
	int i, *wordSizes = (int*) malloc (sizeof(int)*n);
	for (i=0; i<n; i++){
		wordSizes[i] = strlen(vector[i]);
	}
	return wordSizes;
}

int *wordWrap(char **vector, int *wordSizes, int n, int lineSize){
	int i, j, k;

	//Calculo o custo:
	//C[n] representa o custo minimo de colocar as palavras de 1 a n
	int *c = (int*) malloc (sizeof(int) * (n+1));
	int *p = (int*) malloc (sizeof(int) * (n+1));

	c[0] = 0;
	for (j=1; j<=n; j++){
		c[j] = INT_MAX;
		for(i=1; i<=j; i++){
			if (c[i-1] != INT_MAX){

				int extraSpace = lineSize - wordSizes[i-1];
				for (k=i+1; k<=j; k++){
					//Para cada palavra adicionada, vou subtraindo o espaco restante pelo
					//tamanho dessa palavra, e tambem contando +1(espaco)
					extraSpace -= wordSizes[k-1] + 1;

					if (extraSpace<0) break;
				}

				if (extraSpace >= 0 && (extraSpace*extraSpace + c[i-1] < c[j])){
					c[j] = extraSpace*extraSpace + c[i-1];
					p[j] = i;
				}
			}
		}
	}

	return p;
}

void printSolution (char **vector, int *p, int n){
    int i;
    if (p[n] != 1) printSolution (vector, p, p[n]-1);

    for (i=p[n]; i<=n; i++){
    	printf ("%s ", vector[i-1]);
	}
	printf ("\n");
}

int main(int argc, char **argv){
	int n, lineSize;
	char **vector = getInput(&n, &lineSize);
	int *wordSizes = getWordSizes(vector, n);

	int *p = wordWrap(vector, wordSizes, n, lineSize);

	printSolution(vector, p, n);
}