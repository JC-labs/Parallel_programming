#include <omp.h>
#include "Problem.hpp"
#include "Testing.hpp"

int main() {
	std::string s;
	std::ifstream f;
	f.open("data\\n.txt");
	f >> s;
	if (s == "testing") {
		int k;
		f >> k;
		while (k-- > 0) {
			int p, n;
			f >> p >> n;
			testing(p, n);
		};
	} else {
		int p, n;
		f >> p >> n;
		solve(p, n);
	}
	return 0;
}