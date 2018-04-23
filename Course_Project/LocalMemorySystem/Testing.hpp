#pragma once
#include <functional>
#include <chrono>

template<class function, typename...args>
size_t test(function f, args...a) {
	auto start_time = std::chrono::high_resolution_clock::now();
	f(a...);
	return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start_time).count();
}

int test_id = 0;
void testing(int px, int py, int n, std::ostream &s = std::cout) {
	s << "Testing series #" << test_id++ << " (p = " << px << "x" << py << ", n = " << n << "):\n"
		<< "\tTest took " << test(solve<>, px, py, n) << " microseconds.\n";
}