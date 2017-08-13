#include <stdio.h>
#include "utils/sort_analyzer.h"

void bubble_sort(int* a, int n) {
	for (int i = 0; i < n ; i++) {
		for(int j = 0; j< n - i -1 ; j++) {
			if (a[j] > a[j+1]) {
				int temp = a[j];
				a[j] = a[j + 1];
				a[j+1] = temp;
			}
		}
	}
}


int main() {
	sort_analyze(bubble_sort,10,"Bubble Sort");
}