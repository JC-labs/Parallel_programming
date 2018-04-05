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
#include "pthread_event.h"
#include <iostream>
#include <fstream>
#include <semaphore.h>
#include <vector>
#include "../../Course_Project/SharedMemorySystem/Types.cpp"
struct Memory {
	int n, p, size;

	number d;
	vector a, z, s, t;
	matrix mo, mk;

	number b;

	sem_t sem0, sem1, sem2;
	pthread_mutex_t mutex0, mutex1;
	pthread_cr_sec_t cr_sec;
	pthread_event_t ev0, ev2, ev3;

	void clear(int n) {
		b = std::numeric_limits<number>::max();
		::resize(a, n);
		::resize(z, n);
		::resize(s, n);
		::resize(t, n);
		::resize(mo, n);
		::resize(mk, n);
	}
	Memory(int _n, int _p) {
		n = _n; p = _p; size = _n / _p;
		clear(_n);
		sem_init(&sem0, 0, 1);
		sem_init(&sem1, 0, 1);
		sem_init(&sem2, 0, -3);
		pthread_mutex_init(&mutex0, NULL);
		pthread_mutex_init(&mutex1, NULL);
		pthread_cr_sec_init(&cr_sec);
		pthread_event_init(&ev0, NULL);
		pthread_event_init(&ev2, NULL);
		pthread_event_init(&ev3, NULL);
	}
	~Memory() {
		sem_destroy(&sem0);
		sem_destroy(&sem1);
		sem_destroy(&sem2);
		pthread_mutex_destroy(&mutex0);
		pthread_mutex_destroy(&mutex1);
		pthread_cr_sec_destroy(&cr_sec);
		pthread_event_destroy(&ev0);
		pthread_event_destroy(&ev2);
		pthread_event_destroy(&ev3);
	}
};

int main() {
	int n;
	std::ifstream fn;
	fn.open("data/n.txt");
	fn >> n;
	Memory m(n, 4);
	pthread_t t0, t1, t2, t3;
	if (pthread_create(&t0, NULL, [](void *_m) -> void* {
		Memory &m = *(Memory*)_m;
        int t = 0;
		std::cout << "Thread #0 has been initialized\n";
		read_file("data/input_0.txt", m.z, m.mk);

		pthread_event_signal(&m.ev0);
		pthread_event_wait(&m.ev2);
		pthread_event_wait(&m.ev3);

		number b = std::numeric_limits<number>::max();
        for (int i = m.size * t; i < m.size * (t + 1); i++) 
            if (b > m.s[i]) b = m.s[i];
		pthread_cr_sec_start(&m.cr_sec);
		if (m.b > b) m.b = b;
		pthread_cr_sec_end(&m.cr_sec);

		sem_post(&m.sem2);
		sem_wait(&m.sem2);
		sem_post(&m.sem2);

		write_file("data/output.txt", m.a);
		std::cout << "Thread #0 has finished its execution\n";
	}, (void*)&m)) return -1;

	if (pthread_create(&t1, NULL, [](void *_m) -> void* {
		Memory &m = *(Memory*)_m;
        int t = 1;
		std::cout << "Thread #1 has been initialized\n";

		pthread_event_wait(&m.ev0);
		pthread_event_wait(&m.ev2);
		pthread_event_wait(&m.ev3);

		number b = std::numeric_limits<number>::max();
        for (int i = m.size * t; i < m.size * (t + 1); i++) 
            if (b > m.s[i]) b = m.s[i];
		pthread_cr_sec_start(&m.cr_sec);
		if (m.b > b) m.b = b;
		pthread_cr_sec_end(&m.cr_sec);

		sem_post(&m.sem2);
		sem_wait(&m.sem2);
		sem_post(&m.sem2);

		std::cout << "Thread #1 has finished its execution\n";
	}, (void*)&m)) return -1;

	if (pthread_create(&t2, NULL, [](void *_m) -> void* {
		Memory &m = *(Memory*)_m;
        int t = 2;
		std::cout << "Thread #2 has been initialized\n";
		read_file("data/input_2.txt", m.s, m.d);

		pthread_event_signal(&m.ev2);
		pthread_event_wait(&m.ev0);
		pthread_event_wait(&m.ev3);

		number b = std::numeric_limits<number>::max();
        for (int i = m.size * t; i < m.size * (t + 1); i++) 
            if (b > m.s[i]) b = m.s[i];
		pthread_cr_sec_start(&m.cr_sec);
		if (m.b > b) m.b = b;
		pthread_cr_sec_end(&m.cr_sec);

		sem_post(&m.sem2);
		sem_wait(&m.sem2);
		sem_post(&m.sem2);

		std::cout << "Thread #2 has finished its execution\n";
	}, (void*)&m)) return -1;

	if (pthread_create(&t3, NULL, [](void *_m) -> void* {
		Memory &m = *(Memory*)_m;
        int t = 3;
		std::cout << "Thread #3 has been initialized\n";
		read_file("data/input_3.txt", m.t, m.mo);

		pthread_event_signal(&m.ev3);
		pthread_event_wait(&m.ev0);
		pthread_event_wait(&m.ev2);

		number b = std::numeric_limits<number>::max();
        for (int i = m.size * t; i < m.size * (t + 1); i++) 
            if (b > m.s[i]) b = m.s[i];
		pthread_cr_sec_start(&m.cr_sec);
		if (m.b > b) m.b = b;
		pthread_cr_sec_end(&m.cr_sec);

		sem_post(&m.sem2);
		sem_wait(&m.sem2);
		sem_post(&m.sem2);

		std::cout << "Thread #3 has finished its execution\n";
	}, (void*)&m)) return -1;

	pthread_join(t0, NULL);
	return 0;
}
