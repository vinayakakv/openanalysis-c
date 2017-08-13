/* 
	Analyzer module for Searching Algortithms 
	All Searching Algorithms must have following signature
		void fn(int* arr, int n)
*/
#ifndef SORT_ANALYZER
#define SORT_ANALYZER 
#include "analyze_base.h"
#include <stdio.h>
#include <time.h>
#include <string.h>

void sort_analyze(void (*sorter)(int*,int),int numpts,char* name) {
	// Sorter is an sorting algorithm
	// maxpts is number of sample points
	// name is the name of sorting algorithm
	// analysis is done by numpts evenly spaced points starting from. 1000 in the steps of 1000
	SampleContainer* sc = init_sample_container(numpts);
	create_samples(sc,0);
	char* logname = malloc(sizeof(char)* (strlen(name) + 5));
	sprintf(logname,"%s.log",name);
	char* pltname = malloc(sizeof(char)* (strlen(name) + 5));
	sprintf(pltname,"%s.gpl",name);
	FILE* log = fopen(logname,"w");
	fprintf(log,"# Sample Size\tRunning Time(s)\n");
	for( int i = 0; i< sc->length; i++ ) {
		char infile_name[40];
		sprintf(infile_name,"samples/sample%d",i);
		printf("%s\n",infile_name);
		int* sample_array = read_to_array(infile_name,sc->sample_sizes[i]);
		// Now invoke the function
		clock_t start,end;
		start = clock();
		//do stuff
		sorter(sample_array,sc->sample_sizes[i]);
		end = clock();
		char outfile_name[40];
		sprintf(outfile_name,"samples/sorted%d",i);
		double time = ((double) (end - start)) / CLOCKS_PER_SEC;
		write_array(sample_array,sc->sample_sizes[i],outfile_name);
		fprintf(log, "%d\t%lf\n", sc->sample_sizes[i], time);
	}
	fclose(log);
	run_gnuplot(logname,pltname,name,0);
}
#endif
