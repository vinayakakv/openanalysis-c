#include "rand_gen.h"

int main(int argc, char** argv) {
	// argv[1] shoud contain output file name
	if ( argc != 3) 
		fprintf(stderr,"Usage: rand_gen filename num\n");
	long n;
	sscanf(argv[2],"%ld",&n);
	return gen_rand(n, argv[1]);
}
