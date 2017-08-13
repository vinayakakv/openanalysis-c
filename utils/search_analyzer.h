/* 
	Analyzer module for Searching Algortithms 
	All Searching Algorithms must have following signature
		int fn(int* arr, int n, int key)
	They must return index on success else -1
*/

#ifndef SEARCH_ANALYZER
#define SEARCH_ANALYZER
#include "analyze_base.h"
#include <assert.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

void search_analyze(int (*searcher)(int*,int,int),int numpts,char* name) {
	// Searcher is an searchig algorithm
	// maxpts is number of sample points
	// name is the name of searching algorithm
	// on failure of searching algorithm, this function failss
	// analysis is done by numpts evenly spaced points starting from. 1000 in the steps of 1000
	SampleContainer* sc = init_sample_container(numpts);
	create_samples(sc,1);
	char* logname = malloc(sizeof(char)* (strlen(name) + 5));
	sprintf(logname,"%s.log",name);
	char* pltname = malloc(sizeof(char)* (strlen(name) + 5));
	sprintf(pltname,"%s.gpl",name);
	FILE* log = fopen(logname,"w");
	fprintf(log,"# Sample Size\tRunning Time(s)\n");
	for( int i = 0; i< sc->length; i++ ) {
		char infile_name[40];
		sprintf(infile_name,"samples/sorted%d",i);
		printf("%s\n",infile_name);
		int* sample_array = read_to_array(infile_name,sc->sample_sizes[i]);
		// Now invoke the function
		clock_t start,end;
		start = clock();
		//do stuff
		int result = searcher(sample_array,sc->sample_sizes[i],sample_array[sc->sample_sizes[i]-1]);
		end = clock();
		printf("%d\n",result );
		assert(result == sc->sample_sizes[i]-1);
		double time = ((double) (end - start)) / CLOCKS_PER_SEC;
		fprintf(log, "%d\t%lf\n", sc->sample_sizes[i], time);
	}
	fclose(log);
	run_gnuplot(logname,pltname,name,0);
}
#endif