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
#include "../../Course_Project/SharedMemorySystem/FileReader.hpp"
#include <pthread.h>
#include "pthread_cr_sec.h"
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <semaphore.h>
#include <vector>
#include "../../Course_Project/SharedMemorySystem/Types.cpp"
struct Memory {
	number d;
	vector a, z, s, t;
	matrix mo, mk;

	void resize(int n) {
		::resize(a, n);
		::resize(z, n);
		::resize(s, n);
		::resize(t, n);
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
	sem_init(&sem2, 0, 3);

	pthread_mutex_t mutex0, mutex1;
	pthread_mutex_init(&mutex0, NULL);
	pthread_mutex_init(&mutex1, NULL);

	pthread_cr_sec_t cr_sec;
	pthread_cr_sec_init(&cr_sec);

	pthread_cond_t ev0, ev1, ev2, ev3;
	pthread_cond_init(&ev0, NULL);
	pthread_cond_init(&ev1, NULL);
	pthread_cond_init(&ev2, NULL);
	pthread_cond_init(&ev3, NULL);

	if (pthread_create(&t0, NULL, [](void *_m) -> void* {
		Memory &m = *(Memory*)_m;
		std::cout << "Thread #0 has been initialized\n";
		read("data/input_0.txt", m.z, m.mk);


		write("data/output.txt", m.a);
		std::cout << "Thread #0 has finished its execution\n";
	}, (void*)&m)) return -1;
	if (pthread_create(&t1, NULL, [](void *_m) -> void* {
		std::cout << "Thread #1 has been initialized\n";



		std::cout << "Thread #1 has finished its execution\n";
	}, (void*)&m)) return -1;
	if (pthread_create(&t2, NULL, [](void *_m) -> void* {
		std::cout << "Thread #2 has been initialized\n";
		//read("data/input_2.txt", m.d, m.s);



		std::cout << "Thread #2 has finished its execution\n";
	}, (void*)&m)) return -1;
	if (pthread_create(&t3, NULL, [](void *_m) -> void* {
		std::cout << "Thread #3 has been initialized\n";
		//read("data/input_3.txt", m.t, m.mo);



		std::cout << "Thread #3 has finished its execution\n";
	}, (void*)&m)) return -1;
	pthread_join(t0, NULL);

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