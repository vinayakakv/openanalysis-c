#include <stdio.h>
#include "utils/string_matching_analyzer.h"

int binary_search(int* a, int n,int ele) {
	printf("%d,%d\n",n,ele);
	int low = 0;
	int high = n-1;
	while(low <= high) {
		int mid =  low + (high-low)/2;
		if ( a[mid] == ele)
			return mid;
		else if ( a[mid] < ele )
			low = mid + 1;
		else
			high = mid - 1;
	}
	return -1;
}	

int bruteForce(char *search, int slen, char *pattern, int plen) {
    int i, j, k;

    for (i = 0; i <= slen - plen; i++) {
            for (j = 0, k = i; (search[k] == pattern[j]) &&
                    (j < plen); j++, k++);
            if (j == plen)
                    return j;
    }
    return -1;
}

#define NO_OF_CHARS 256
 
// A utility function to get maximum of two integers
int max (int a, int b) { return (a > b)? a: b; }
 
// The preprocessing function for Boyer Moore's
// bad character heuristic
void badCharHeuristic( char *str, int size, 
                        int badchar[NO_OF_CHARS])
{
    int i;
 
    // Initialize all occurrences as -1
    for (i = 0; i < NO_OF_CHARS; i++)
         badchar[i] = -1;
 
    // Fill the actual value of last occurrence 
    // of a character
    for (i = 0; i < size; i++)
         badchar[(int) str[i]] = i;
}
 
/* A pattern searching function that uses Bad
   Character Heuristic of Boyer Moore Algorithm */
int search( char *txt, int n,  char *pat, int m)
{
 
    int badchar[NO_OF_CHARS];
 
    /* Fill the bad character array by calling 
       the preprocessing function badCharHeuristic() 
       for given pattern */
    badCharHeuristic(pat, m, badchar);
 
    int s = 0;  // s is shift of the pattern with 
                // respect to text
    while(s <= (n - m))
    {
        int j = m-1;
 
        /* Keep reducing index j of pattern while 
           characters of pattern and text are 
           matching at this shift s */
        while(j >= 0 && pat[j] == txt[s+j])
            j--;
 
        /* If the pattern is present at current
           shift, then index j will become -1 after
           the above loop */
        if (j < 0)
        {
            printf("\n pattern occurs at shift = %d", s);
 			return s;
            /* Shift the pattern so that the next 
               character in text aligns with the last 
               occurrence of it in pattern.
               The condition s+m < n is necessary for 
               the case when pattern occurs at the end 
               of text */
            //s += (s+m < n)? m-badchar[txt[s+m]] : 1;
 
        }
 
        else
            /* Shift the pattern so that the bad character
               in text aligns with the last occurrence of
               it in pattern. The max function is used to
               make sure that we get a positive shift. 
               We may get a negative shift if the last 
               occurrence  of bad character in pattern
               is on the right side of the current 
               character. */
            s += max(1, j - badchar[txt[s+j]]);
    }
    return -1;
}

int main() {
	string_matching_analyze(search,NULL,"HP",10000,1000);
}