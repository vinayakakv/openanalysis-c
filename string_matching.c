#include <stdio.h>
#include "utils/string_matching_analyzer.h"
/*
  Code containing implementation of several String Matching Algorithms
*/

//Brute Force String Matching Algorithm
int brute_force(char *search, int slen, char *pattern, int plen) {
  int i, j, k;
  for (i = 0; i <= slen - plen; i++) {
    for (j = 0, k = i; (search[k] == pattern[j]) && (j < plen); j++, k++);
    if (j == plen)
      return j;
  }
  return -1;   
}

//Horspool String Matching Algorithm
#define NO_OF_CHARS 256 // ASCII max
 
int* generate_shift_table(char* pattern, int m) {
  int* shift_table = malloc(sizeof(int)*NO_OF_CHARS);
  for (int i =0 ; i< NO_OF_CHARS ; i++)
    shift_table[i] = m;
  for (int i = 0; i < m ; i++)
    shift_table[(int)pattern[i]] = m - i - 1;
  return shift_table;
}
 
int horspool( char *y, int n,  char *x, int m) {
  int* bmBc = generate_shift_table(x,m);
  int i = m - 1;
  int j = 0;
  char c;
  while (j <= n - m) {
    c = y[j + m - 1];
    if (x[m - 1] == c && memcmp(x, y + j, m - 1) == 0)
      return j;
    j += bmBc[c];
  }
  return -1;
}

int main() {
	string_matching_analyze(horspool,NULL,"HP",10000,1000);
}