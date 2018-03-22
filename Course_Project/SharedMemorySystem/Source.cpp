#include <omp.h>
#include "Problem.hpp"

int main(int argc, char** argv) {
	if (!(argc && argv[0] == "t")) {
		//testing is to be implemented here
		solve<false, false, /**/ false, false, false>();
		solve<false, false, /**/ false, false, true>();
		solve<false, false, /**/ false, true, false>();
		solve<false, false, /**/ false, true, true>();
		solve<false, false, /**/ true, false, false>();
		solve<false, false, /**/ true, false, true>();
		solve<false, false, /**/ true, true, false>();
		solve<false, false, /**/ true, true, true>();
	} else
		solve();
	return 0;
}