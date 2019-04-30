#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main (int argc, char ** argv) {

	if (argc == 2) {

		srand(time(NULL));

		FILE * saida = fopen(strcat(argv[1], "testFile.txt"), "w");

		int limite = rand() % 100;
		int numVizinhos = rand() % limite;

		limite = rand() % 1000;
		int tamTabu = rand() % limite;

		fprintf(saida, "100 0.5 10 %d %d", numVizinhos, tamTabu);

		fclose(saida);

	}

	return 0;

}