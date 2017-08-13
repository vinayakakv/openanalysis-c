#ifndef RAND_GEN
#define RAND_GEN
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
/*
Utility to generate random number array of given size
Complie with gcc -std=c99 rand_gen.h file.c
*/
int gen_rand(int n, char* outfile_name) {
	// n - Number of elements in Random File
	// outfile_name - Name of file name in witch the generated numbers have to be stored
	// returns 0 on success else 1
	srand(time(NULL));
	FILE* outfile = fopen(outfile_name, "w");
	if ( outfile == NULL || n < 0 ) return 1;
	for (int i = 0; i < n ; i++)
		fprintf(outfile,"%d\n",rand());
	fclose(outfile);
	return 0;
}

int gen_sorted(int n, char* outfile_name) {
	// n - Number of elements in Random File
	// outfile_name - Name of file name in witch the generated numbers have to be stored
	// returns 0 on success else 1
	FILE* outfile = fopen(outfile_name, "w");
	if ( outfile == NULL || n < 0 ) return 1;
	for (int i = 0; i < n ; i++)
		fprintf(outfile,"%d\n",i);
	fclose(outfile);
	return 0;
}
#endif
