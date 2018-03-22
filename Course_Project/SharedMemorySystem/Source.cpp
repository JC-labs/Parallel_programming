#include <omp.h>
#include "Problem.hpp"
#include "Testing.hpp"

int main() {
	std::string s;
	std::ifstream fn;
	fn.open("data\\n.txt");
	std::ofstream ft;
	ft.open("data\\testing.txt");
	fn >> s;
	if (s == "testing") {
		int k;
		fn >> k;
		while (k-- > 0) {
			int p, n;
			fn >> p >> n;
			testing(p, n, ft);
		};
	} else {
		int p, n;
		f >> p >> n;
		solve(p, n);
	}
	return 0;
}