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
			int px, py, n;
			fn >> px >> py >> n;
			testing(px, py, n, ft);
			std::cout << k << '\n';
		};
	} else {
		fn.clear();
		fn.seekg(0, std::ios::beg);
		int px, py, n;
		fn >> px >> py >> n;
		solve<>(px, py, n);
	}
	return 0;
}