#include <stdio.h>
#include "utils/search_analyzer.h"

int binary_search(int* a, int n,int ele) {
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

int linear_search(int* a, int n, int ele) {
	for (int i=0 ; i < n ; i++)
		if (a[i] == ele)
			return i;
	return -1;
}

int main() {
	search_analyze(binary_search,100,"Binary Search");
}