/*
	Analyzer for all string matching algorithms
	Algorithms must have following signature
		int fn(char* text,int n,char* patt, int m)
	They must return -1 on failure
*/

#ifndef STRING_MATCHING_ANALYZER
#define STRING_MATCHING_ANALYZER

#define MIN_TEXT_LENGTH 5000
#define MIN_PATT_LENGTH 500
#define SAMPLE_LIST_SIZE 4

#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <limits.h>
#include <stdio.h>
#include "analyze_base.h"
#include <assert.h>
#include <errno.h>

char* sample_list[] = {"BG","US","rand64","rand32"};

char* read_full_file(char* filepath, int* length) {
	// Reads the whole text of file into memory and returns a pointer to it
	// filepath is the path of the file to be read
	// after reading the file, *length contains the size of file
	// In case of error, program is terminated
	FILE *f = fopen(filepath, "r");
	if (length == NULL)
		error("PARAM ERROR");
	if (f == NULL)
		error("FILE I/O ERROR");
	fseek(f, 0, SEEK_END);
	long fsize = ftell(f);
	fseek(f, 0, SEEK_SET);  //same as rewind(f);
	char *string = malloc(fsize + 1);
	if (string == NULL)
		error("MEMORY ALLOCATION ERROR");
	fread(string, fsize, 1, f);
	fclose(f);
	string[fsize] = 0;
	*length = fsize;
	return string;
}

char* read_text_from(char* file_contents, int flength, int from, int length) {
	assert(file_contents != NULL && flength > 0 && from >= 0 && length >= 0);
	if (from + length > flength)
		error("PARAM VAL ERROR");
	char* text = malloc(sizeof(char)*(length + 2));
	char* tptr = file_contents + from;
	memcpy(text,tptr,length);
	text[length] = '\0';
	return text;
}

void string_matching_analyze(
	int (*matcher)(char*,int,char*,int),
	char* ifile,
	char* name,
	int max_text_length,
	int max_patt_length) {
	// matcher - String Matching Algorithms
	// numpts - Number of points
	// ifile - Input file. If it is NULL, a file a chosen from inbuilt samples
	// max_*_legth - Max length of *s. If they are less than mins, they are defaulted to their original values
	if (ifile == NULL) {
		srand(time(NULL));
		ifile = malloc(sizeof(char) * 30);
		sprintf(ifile,"utils/sm_samples/%s",sample_list[rand() % SAMPLE_LIST_SIZE]); // HORRIBLE SOLUTION
		char actualpath [PATH_MAX+1];
		char *ptr = realpath(ifile, actualpath);
		if (ptr == NULL) {
			printf("%s\n%s\n%d",actualpath,ifile,errno);
			error("PATH ERROR");
		}
		free(ifile);
		ifile = actualpath;
	}
	FILE* sample = fopen(ifile,"r");
	if (sample == NULL)
		error("FILE I/O ERROR");
	if (max_text_length <=MIN_TEXT_LENGTH)
		error("max_text_length is less than MIN_TEXT_LENGTH");
	if (max_patt_length <= MIN_PATT_LENGTH)
		error("max_patt_length is less than MIN_PATT_LENGTH");
	if (max_text_length <= max_patt_length)
		error("max_text_length <= max_patt_length");
	//int max_text_length = 10000;
	//int max_patt_length = 1000;
	int flength;
	char* contents = read_full_file(ifile, &flength);
	if (max_text_length > flength)
		error("max_text_length > file length");
	char* logname = malloc(sizeof(char)* (strlen(name) + 5));
	sprintf(logname,"%s.log",name);
	char* pltname = malloc(sizeof(char)* (strlen(name) + 5));
	sprintf(pltname,"%s.gpl",name);
	FILE* log = fopen(logname,"w");
	fprintf(log,"# Text Size\tPattern Size\tRunning Time(s)\n");
	for (int n = MIN_TEXT_LENGTH; n < max_text_length ; n+=100) {
		for(int m = MIN_PATT_LENGTH; m < max_patt_length ; m+=5) {
			int pos = rand() % (flength - n);
			char* text = read_text_from(contents,flength,pos,n);
			pos = rand() % (n-m);
			char* patt = read_text_from(text,n,pos,m);
			clock_t start,end;
			start = clock();
			//do stuff
			int val = matcher(text,n,patt,m);
			assert(val != -1);
			end = clock();
			double time = ((double) (end - start)) / CLOCKS_PER_SEC;
			fprintf(log,"%d\t%d\t%lf\n",n,m,time);
		}
	}
	fclose(log);
	run_gnuplot(logname,pltname,name,1);
}

#endif