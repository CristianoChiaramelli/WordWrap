#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MIN(a,b) (((a)<(b))?(a):(b))


int getInput(char ***vector, int *lineSize){
	int n;
	ssize_t wordSize;
	scanf("%d", &n);
	scanf("%d", lineSize);
	getchar();
	*vector = malloc(sizeof(char**)*(n+1));
       	while(n > 0){
		getline(*vector+n, &wordSize, stdin);
		n--;
	}	
}

int main(int argc, char **argv){
	int n, &lineSize;
	char **vector = NULL;
	n = getInput(&vector, &lineSize);
	printf("%d\n", opt(vector, n);
}
