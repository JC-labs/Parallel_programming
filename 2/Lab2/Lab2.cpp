/*
    Parallel and Allotted Calculations.
    Lab #2: POSIX: semaphores, mutexes, events and critical sections.

    The code was written by
        Krisak Ivan,
        student of IO-53, KPI.
    April 5, 2018.

    Function:
	A = sort(d * Z + min(S) * T * (MO * MK))
*/
#include "..\..\Course_Project\SharedMemorySystem\FileReader.hpp"
#include <pthread.h>
#include "pthread_cr_sec.h"
#include <unistd.h>
#include <iostream>
#include <fstream>
using number = float;
using vector = std::vector<number>;
using matrix = std::vector<vector>;

void fill(vector &v, number value) {
	for (auto &it : v)
		it = value;
}
void fill(matrix &m, number value) {
	for (auto &v : m)
		for (auto &it : v)
			it = value;
}
void get(vector &v, std::istream &s) {
	for (auto &it : v)
		s >> it;
}
void get(matrix &m, std::istream &s) {
	for (auto &v : m)
		for (auto &it : v)
			s >> it;
}
void resize(vector &v, size_t n) { v.resize(n); }
void resize(matrix &m, size_t n) {
	m.resize(n);
	for (auto &it : m)
		it.resize(n);
}
void write(matrix const& m, std::ostream &s) {
	s << "Output of a matrix (" << m.size() << "x" << m.size() << "):\n";
	for (auto v : m) {
		for (auto it : v)
			s << it << ' ';
		s << '\n';
	}
}
struct Memory {
	number d;
	vector a, z, s, t;
	matrix mo, mk;

	void resize(int n) {
		::resize(a, n);
		::resize(z, n);
		::resize(s, n);
		::resize(r, n);
		::resize(mo, n);
		::resize(mk, n);
	}
	Memory(int n) { resize(n); }
};

int main() {
	int p = 4;
	int n;

	std::ifstream fn;
	fn.open("data/n.txt");
	fn >> n;

	int size = n / p;

	Memory m(n);
	number b = std::numeric_limits<number>::max();

	pthread_t t0, t1, t2, t3;

	sem_t sem0, sem1, sem2;
	sem_init(&sem0, 0, 1);
	sem_init(&sem1, 0, 1);
	sen_init(&sem2, 0, 3);

	pthread_mutex_t mutex0, mutex1;
	pthread_mutex_init(&mutex0, NULL);
	pthread_mutex_init(&mutex1, NULL);

	pthread_cr_sec_t cr_sec;
	pthread_cr_sec_init(&cr_sec);

	pthread_cond_t ev0, ev1, ev2, ev3;
	pthread_cond_init(&ev0);
	pthread_cond_init(&ev1);
	pthread_cond_init(&ev2);
	pthread_cond_init(&ev3);

	if (pthread_create(&t0, NULL, []() {
		std::cout << "Thread #0 has been initialized\n";
		std::cout << "Thread #0 has finished its execution\n";
	});
	if (pthread_create(&t1, NULL, []() {
		std::cout << "Thread #1 has been initialized\n";
		std::cout << "Thread #1 has finished its execution\n";
	});
	if (pthread_create(&t2, NULL, []() {
		std::cout << "Thread #2 has been initialized\n";
		std::cout << "Thread #2 has finished its execution\n";
	});
	if (pthread_create(&t3, NULL, []() {
		std::cout << "Thread #3 has been initialized\n";
		std::cout << "Thread #3 has finished its execution\n";
	});
	pthread_join(&t0);

	sem_destroy(&sem0);
	sem_destroy(&sem1);
	sem_destroy(&sem2);
	pthread_mutex_destroy(&mutex0);
	pthread_mutex_destroy(&mutex1);
	pthread_cr_sec_destroy(&cr_sec);
	pthread_cond_destroy(&ev0);
	pthread_cond_destroy(&ev1);
	pthread_cond_destroy(&ev2);
	pthread_cond_destroy(&ev3);

	return 0;
}