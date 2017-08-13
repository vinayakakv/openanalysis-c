#ifndef ANALYSIS_BASE
#define ANALYSIS_BASE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "rand_gen.h"

typedef struct {
	int length;
	int* sample_sizes;
}SampleContainer;

void error(char* msg) {
	fprintf(stderr, "%s\n", msg);
	exit(1);
}

SampleContainer* init_sample_container(int numpts) {
	SampleContainer* sc = malloc(sizeof(SampleContainer));
	if (sc == NULL) 
		error("MEMORY ALLOCATION ERROR");
	sc->length = numpts;
	sc->sample_sizes = malloc(sizeof(int)* sc->length);
	if (sc->sample_sizes == NULL) {
		free(sc);
		error("MEMORY ALLOCATION ERROR");
	}
	for (int i = 0; i<numpts ; i++)
		sc->sample_sizes[i] = (i+1) * 1000;
	return sc;
}
 
int create_samples(SampleContainer* sc, int sorted){
	int (*generator)(int,char*) = sorted == 0 ? gen_rand : gen_sorted;
	char* prefix = sorted == 0 ? "sample" : "sorted";
	if (sc == NULL)
		return 1;
	int new_files = 0; // Don't create new samples
	if (fopen("samples/test","r") == NULL) { // Implies file does not exsist
		//Create log
		FILE* test = fopen("samples/test","w");
		fprintf(test, "%d\n", sc->length);
		fprintf(test, "%d\n", sorted);
		fclose(test);
		new_files = 1; // New samples have to be created
	}
	else {
		FILE* test = fopen("samples/test","r");
		int old_test_length;
		int old_type;
		fscanf(test,"%d",&old_test_length);
		fscanf(test,"%d",&old_type);
		if(old_test_length!=sc->length || old_type!= sorted) {
			new_files = 1;
			fclose(test);
			test = fopen("samples/test","w");
			fprintf(test, "%d\n", sc->length);
			fprintf(test, "%d\n", sorted);
		}
		fclose(test);
	}
	if (new_files == 1) {
		system("shopt -s extglob");
		system("rm -rf -- !(samples/test)");
		for (int i = 0; i< sc->length ; i++) {
			char outfile_name[40];
			sprintf(outfile_name,"samples/%s%d",prefix,i);
			generator(sc->sample_sizes[i],outfile_name);
		}
	}
	return 0;
}

int* read_to_array(char* sample_file_name, int n) {
	// sample_file : File in whitch the samples are stored
	// n : Number of elements to read
	// returns the sample array
	int* arr = malloc(sizeof(int) * n);
	FILE* sample_file = fopen(sample_file_name, "r");
	if ( arr == NULL || sample_file == NULL ) {
		 fprintf(stderr,"FAILED TO READ THE FILE %s INTO MEMORY\n",sample_file_name);
		 exit(1);
	}
	rewind(sample_file);
	for ( int i = 0; i <n ; i++ ) {
		fscanf(sample_file,"%d",&arr[i]);
	}
	fclose(sample_file);
	return arr;
}

void write_array (int* arr, int n, char* outfile_name) {
	FILE* outfile = fopen(outfile_name,"w");
	if (outfile == NULL)
		error("FILE I/O error");
	for (int i=0 ; i<n ; i++)
		fprintf(outfile, "%d\n", arr[i]);
	fclose(outfile);
}

void run_gnuplot(char* log_file_name,char* outfile_name,char* alg_name,int is3d) {
	FILE* plt = fopen(outfile_name,"w");
	if ( log_file_name == NULL || plt == NULL )
		error("FILE I/O ERROR");
	char* plt_type = is3d == 0? "plot" : "splot";
	fprintf(plt,"set title \"%s Analysis\" font \",20\"\n",alg_name);
	fprintf(plt,"set key left box\n");
	fprintf(plt,"%s \"%s\" pt 7 ps 1\n",plt_type,log_file_name);
	fprintf(plt,"pause -1");
	fclose (plt);
	// system("gnuplot -c plot_sort");
	execlp("gnuplot","-c",outfile_name, (char*) 0);
}

#endif