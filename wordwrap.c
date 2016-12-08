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
	}
	return vector;
}

int *getWordSizes(char **vector, int n){
	int i, *wordSizes = (int*) malloc (sizeof(int)*n);
	for (i=0; i<n; i++){
		wordSizes[i] = strlen(vector[i])-1;
	}
	return wordSizes;
}

void printVector(char **vector, int n){
	int i;
	for (i=0; i<n; i++){
		printf ("%s", vector[i]);
	}
}

int **allocateIntMatrix(int n){
	int i, **M = (int**) malloc (sizeof(int*) * n);
	for (i=0; i<n; i++){
		M[i] = (int*) malloc (sizeof(int) * n);
	}
	return M;
}

void wordWrap(char **vector, int *wordSizes, int n, int lineSize){
	int i, j;
	//extraSpace[a][b] possui os espacos extra se palavras entre a e b
	//forem colocadas na mesma linha
	int **extraSpace = allocateIntMatrix(n+1);
	printf ("Calcula extraSpace\n");
	for (i=1; i<=n; i++){
		//Colocando apenas a palavra[i], o espaco restante sera o tamanhoMaximo - tamanhoPalavra
		extraSpace[i][i] = lineSize - wordSizes[i-1];
		
		for (j=i+1; j<=n; j++){
			//Para cada palavra adicionada, vou subtraindo o espaco restante pelo
			//tamanho dessa palavra, e tambem contando +1(espaco)
			extraSpace[i][j] = extraSpace[i][j-1] - wordSizes[j-1] - 1;
		}
	}

	//lineCost[a][b] representa o custo em colocar as palavras
	//de 'a' a 'b' na mesma linha (Custo = espacos livres^2)
	int **lineCost = allocateIntMatrix(n+1);
	printf ("Calcula lineCost\n");
	for (i=1; i<=n; i++){
		for (j=i; j<=n; j++){
			if (extraSpace[i][j]<0){
				//Nesse caso, as palavras de i a j nao cabem
				//recebe infinito para mostrar que nao pode existir essa combinacao
				lineCost[i][j] = INT_MAX;
			} else {
				//Nesse caso, cabem as palavras de i a j, entao eu
				//calculo o quadrado
				lineCost[i][j] = extraSpace[i][j] * extraSpace[i][j];
			}
		}
	}

	//Calculo o custo:
	//C[n] representa o custo minimo de colocar as palavras de 1 a n
	int *c = (int*) malloc (sizeof(int) * (n+1));
	printf ("Calcula custo minimo\n");
	c[0] = 0;
	for (j=1; j<=n; j++){
		c[j] = INT_MAX;
		for(i=1; i<=j; i++){
			if (c[i-1] != INT_MAX && lineCost[i][j] != INT_MAX){
				c[j] = MIN(c[j], lineCost[i][j]+c[i-1]);
				printf ("Custo min[%d] = %d\n", j, c[j]);
			}
		}
	}

	printf ("Custo minimo:\n");
	printf ("C[%d] = %d\n", n, c[n]);
}

int main(int argc, char **argv){
	int n, lineSize;
	char **vector = getInput(&n, &lineSize);
	int *wordSizes = getWordSizes(vector, n);

	wordWrap(vector, wordSizes, n, lineSize);

	printVector(vector, n);
}