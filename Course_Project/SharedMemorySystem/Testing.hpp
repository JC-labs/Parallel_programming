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
void testing(int p, int n, std::ostream &s = std::cout) {
	s << "Testing series #" << test_id++ << " (p = " << p << ", n = " << n << "):\n"
		<< "\tTest #0 (w/o copies, w/o temporary variables, w/o openMP-style for loops)\n"
		<< "\t\ttook " << test(solve<false, false, /**/ false, false, false>, p, n) << " microseconds.\n"
		<< "\tTest #1 (w/o copies, w/o temporary variables, w/ openMP-style for loops)\n"
		<< "\t\ttook " << test(solve<false, false, /**/ false, false, true>, p, n) << " microseconds.\n"
		<< "\tTest #2 (w/o copies, w/ temporary variables, w/o openMP-style for loops)\n"
		<< "\t\ttook " << test(solve<false, false, /**/ false, true, false>, p, n) << " microseconds.\n"
		<< "\tTest #3 (w/o copies, w/ temporary variables, w/ openMP-style for loops)\n"
		<< "\t\ttook " << test(solve<false, false, /**/ false, true, true>, p, n) << " microseconds.\n"
		<< "\tTest #4 (w/ copies, w/o temporary variables, w/o openMP-style for loops)\n"
		<< "\t\ttook " << test(solve<false, false, /**/ true, false, false>, p, n) << " microseconds.\n"
		<< "\tTest #5 (w/ copies, w/o temporary variables, w/ openMP-style for loops)\n"
		<< "\t\ttook " << test(solve<false, false, /**/ true, false, true>, p, n) << " microseconds.\n"
		<< "\tTest #6 (w/ copies, w/ temporary variables, w/o openMP-style for loops)\n"
		<< "\t\ttook " << test(solve<false, false, /**/ true, true, false>, p, n) << " microseconds.\n"
		<< "\tTest #7 (w/ copies, w/ temporary variables, w/ openMP-style for loops)\n"
		<< "\t\ttook " << test(solve<false, false, /**/ true, true, true>, p, n) << " microseconds.\n";
}