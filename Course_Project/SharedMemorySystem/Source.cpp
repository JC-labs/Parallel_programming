#include <omp.h>
#include "Problem.hpp"

int main(int argc, char** argv) {
	if (argc && argv[0] == "t") {
		//testing is to be implemented here
	} else
		solve();
	return 0;
}