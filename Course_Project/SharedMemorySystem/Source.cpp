#include <omp.h>
#include "Solution.hpp"
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
		fn.clear();
		fn.seekg(0, std::ios::beg);
		int p, n;
		fn >> p >> n;
		solve<true, true, false, false, true>(p, n);
	}
	return 0;
}