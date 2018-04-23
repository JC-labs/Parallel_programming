#include "Solution.hpp"
int main() {
	std::string s;
	std::ifstream fn;
	fn.open("data\\n.txt");
	fn >> s;
	if (s == "testing") {
		int px, py, n;
		fn >> px >> py >> n;
		long long time;
		if (int id = solve<false, false, false, true, true>(px, py, n, &time); id == px * py - 1) {
			std::ofstream ft;
			ft.open("data\\testing.txt", std::fstream::app);
			ft << "Test with p = " << px << "x" << py << " and n = " << n << " took " << (time / 1000) << " microseconds.\n";
		}
	} else {
		fn.clear();
		fn.seekg(0, std::ios::beg);
		int px, py, n;
		fn >> px >> py >> n;
		solve<true, true, false, true, false>(px, py, n);
	}
	return 0;
}