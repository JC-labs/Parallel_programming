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
#include "../../Course_Project/SharedMemorySystem/Types.cpp"
#include <pthread.h>
#include "pthread_cr_sec.h"
#include "pthread_event.h"
#include <iostream>
#include <fstream>
#include <semaphore.h>
#include <vector>
struct Memory {
	int n, p, size;
	pthread_t t0, t1, t2, t3;

	number d;
	vector a, z, s, t;
	matrix mo, mk;

	number b;

	sem_t sem0, sem1;
	pthread_mutex_t mutex0, mutex1;
	pthread_cr_sec_t cr_sec;

	pthread_event_t ev0, ev2, ev3;
	pthread_mutex_t mutex2, mutex3, mutex4, mutex5;
	sem_t sem2;

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
		pthread_mutex_init(&mutex2, NULL);
		pthread_mutex_lock(&mutex2);
		pthread_mutex_init(&mutex3, NULL);
		pthread_mutex_lock(&mutex3);
		pthread_mutex_init(&mutex4, NULL);
		pthread_mutex_lock(&mutex4);
		pthread_mutex_init(&mutex5, NULL);
		pthread_mutex_lock(&mutex5);
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
		pthread_mutex_destroy(&mutex2);
		pthread_mutex_destroy(&mutex3);
		pthread_mutex_destroy(&mutex4);
		pthread_mutex_destroy(&mutex5);
	}
};

void sort(vector &v, int s, int e) {
	bool swapped;
	do {
		swapped = false;
		for (int i = s; i < e; i++)
			if (v[i] > v[i + 1]) {
				std::swap(v[i], v[i + 1]);
				swapped = true;
			}
	} while(swapped);
}
void merge(vector &v, int i, int ie, int j, int je) {
	int c = i;
	vector res;
	while (i < ie && j < je)
		if (v[i] < v[j])
			res.push_back(v[i++]);
		else
			res.push_back(v[j++]);
	while (i < ie)
		res.push_back(v[i++]);
	while (j < je)
		res.push_back(v[j++]);
	for (; c < je; c++)
		v[c] = res[c];
}

int main() {
	int n;
	std::ifstream fn;
	fn.open("data/n.txt");
	fn >> n;
	Memory m(n, 4);
	if (pthread_create(&m.t0, NULL, [](void *_m) -> void* {
		Memory &m = *(Memory*)_m;
        int id = 0;
		std::cout << "Thread #0 has been initialized\n";
		read_file("data/input_0.txt", m.z, m.mk);

		pthread_event_signal(&m.ev0);
		pthread_event_wait(&m.ev2);
		pthread_event_wait(&m.ev3);

		number b = std::numeric_limits<number>::max();
        for (int i = m.size * id; i < m.size * (id + 1); i++) 
            if (b > m.s[i]) b = m.s[i];
		pthread_cr_sec_start(&m.cr_sec);
		if (m.b > b) m.b = b;
		pthread_cr_sec_end(&m.cr_sec);

		pthread_mutex_unlock(&m.mutex2);
		pthread_mutex_lock(&m.mutex3);
		pthread_mutex_unlock(&m.mutex3);
		pthread_mutex_lock(&m.mutex4);
		pthread_mutex_unlock(&m.mutex4);
		pthread_mutex_lock(&m.mutex5);
		pthread_mutex_unlock(&m.mutex5);

		sem_wait(&m.sem0);
		b = m.b;
		sem_post(&m.sem0);
		pthread_mutex_lock(&m.mutex0);
		number d = m.d;
		pthread_mutex_unlock(&m.mutex0);
		pthread_mutex_lock(&m.mutex1);
		vector t = m.t;
		pthread_mutex_unlock(&m.mutex1);
		sem_wait(&m.sem1);
		matrix mk = m.mk;
		sem_post(&m.sem1);
		
		number temp;
		for (int i = m.size * id; i < m.size * (id + 1); i++) {
			for (int j = 0; j < m.n; j++) {
				temp = 0;
				for (int k = 0; k < m.n; k++)
					temp += m.mo[i][k] * mk[k][j];
				m.a[i] += temp * t[j];
			}
			m.a[i] = m.a[i] * b + d * m.z[i];
		}

		sem_post(&m.sem2);
		sem_wait(&m.sem2);
		sem_post(&m.sem2);

		sort(m.a, m.size * id, m.size * (id + 1) - 1);
		pthread_join(m.t1, NULL);
		merge(m.a, m.size * id, m.size * (id + 1) - 1, m.size * (id + 1), m.size * (id + 2) - 1);
		pthread_join(m.t2, NULL);
		merge(m.a, m.size * id, m.n % 2 - 1, m.n % 2, m.n);

		write_file("data/output.txt", m.a);
		std::cout << "Thread #0 has finished its execution\n";
	}, (void*)&m)) return -1;

	if (pthread_create(&m.t1, NULL, [](void *_m) -> void* {
		Memory &m = *(Memory*)_m;
        int id = 1;
		std::cout << "Thread #1 has been initialized\n";

		pthread_event_wait(&m.ev0);
		pthread_event_wait(&m.ev2);
		pthread_event_wait(&m.ev3);

		number b = std::numeric_limits<number>::max();
        for (int i = m.size * id; i < m.size * (id + 1); i++) 
            if (b > m.s[i]) b = m.s[i];
		pthread_cr_sec_start(&m.cr_sec);
		if (m.b > b) m.b = b;
		pthread_cr_sec_end(&m.cr_sec);

		pthread_mutex_unlock(&m.mutex3);
		pthread_mutex_lock(&m.mutex2);
		pthread_mutex_unlock(&m.mutex2);
		pthread_mutex_lock(&m.mutex4);
		pthread_mutex_unlock(&m.mutex4);
		pthread_mutex_lock(&m.mutex5);
		pthread_mutex_unlock(&m.mutex5);

		sem_wait(&m.sem0);
		b = m.b;
		sem_post(&m.sem0);
		pthread_mutex_lock(&m.mutex0);
		number d = m.d;
		pthread_mutex_unlock(&m.mutex0);
		pthread_mutex_lock(&m.mutex1);
		vector t = m.t;
		pthread_mutex_unlock(&m.mutex1);
		sem_wait(&m.sem1);
		matrix mk = m.mk;
		sem_post(&m.sem1);
		
		number temp;
		for (int i = m.size * id; i < m.size * (id + 1); i++) {
			for (int j = 0; j < m.n; j++) {
				temp = 0;
				for (int k = 0; k < m.n; k++)
					temp += m.mo[i][k] * mk[k][j];
				m.a[i] += temp * t[j];
			}
			m.a[i] = m.a[i] * b + d * m.z[i];
		}

		sem_post(&m.sem2);
		sem_wait(&m.sem2);
		sem_post(&m.sem2);

		sort(m.a, m.size * id, m.size * (id + 1) - 1);

		std::cout << "Thread #1 has finished its execution\n";
	}, (void*)&m)) return -1;

	if (pthread_create(&m.t2, NULL, [](void *_m) -> void* {
		Memory &m = *(Memory*)_m;
        int id = 2;
		std::cout << "Thread #2 has been initialized\n";
		read_file("data/input_2.txt", m.s, m.d);

		pthread_event_signal(&m.ev2);
		pthread_event_wait(&m.ev0);
		pthread_event_wait(&m.ev3);

		number b = std::numeric_limits<number>::max();
		for (int i = m.size * id; i < m.size * (id + 1); i++)
            if (b > m.s[i]) b = m.s[i];
		pthread_cr_sec_start(&m.cr_sec);
		if (m.b > b) m.b = b;
		pthread_cr_sec_end(&m.cr_sec);

		pthread_mutex_unlock(&m.mutex4);
		pthread_mutex_lock(&m.mutex3);
		pthread_mutex_unlock(&m.mutex3);
		pthread_mutex_lock(&m.mutex2);
		pthread_mutex_unlock(&m.mutex2);
		pthread_mutex_lock(&m.mutex5);
		pthread_mutex_unlock(&m.mutex5);

		sem_wait(&m.sem0);
		b = m.b;
		sem_post(&m.sem0);
		pthread_mutex_lock(&m.mutex0);
		number d = m.d;
		pthread_mutex_unlock(&m.mutex0);
		pthread_mutex_lock(&m.mutex1);
		vector t = m.t;
		pthread_mutex_unlock(&m.mutex1);
		sem_wait(&m.sem1);
		matrix mk = m.mk;
		sem_post(&m.sem1);
		
		number temp;
		for (int i = m.size * id; i < m.size * (id + 1); i++) {
			for (int j = 0; j < m.n; j++) {
				temp = 0;
				for (int k = 0; k < m.n; k++)
					temp += m.mo[i][k] * mk[k][j];
				m.a[i] += temp * t[j];
			}
			m.a[i] = m.a[i] * b + d * m.z[i];
		}

		sem_post(&m.sem2);
		sem_wait(&m.sem2);
		sem_post(&m.sem2);

		sort(m.a, m.size * id, m.size * (id + 1) - 1);
		pthread_join(m.t3, NULL);
		merge(m.a, m.size * id, m.size * (id + 1) - 1, m.size * (id + 1), m.n);

		std::cout << "Thread #2 has finished its execution\n";
	}, (void*)&m)) return -1;

	if (pthread_create(&m.t3, NULL, [](void *_m) -> void* {
		Memory &m = *(Memory*)_m;
        int id = 3;
		std::cout << "Thread #3 has been initialized\n";
		read_file("data/input_3.txt", m.t, m.mo);

		pthread_event_signal(&m.ev3);
		pthread_event_wait(&m.ev0);
		pthread_event_wait(&m.ev2);

		number b = std::numeric_limits<number>::max();
		for (int i = m.size * id; i < m.size * (id + 1); i++)
            if (b > m.s[i]) b = m.s[i];
		pthread_cr_sec_start(&m.cr_sec);
		if (m.b > b) m.b = b;
		pthread_cr_sec_end(&m.cr_sec);

		pthread_mutex_unlock(&m.mutex5);
		pthread_mutex_lock(&m.mutex3);
		pthread_mutex_unlock(&m.mutex3);
		pthread_mutex_lock(&m.mutex4);
		pthread_mutex_unlock(&m.mutex4);
		pthread_mutex_lock(&m.mutex2);
		pthread_mutex_unlock(&m.mutex2);

		sem_wait(&m.sem0);
		b = m.b;
		sem_post(&m.sem0);
		pthread_mutex_lock(&m.mutex0);
		number d = m.d;
		pthread_mutex_unlock(&m.mutex0);
		pthread_mutex_lock(&m.mutex1);
		vector t = m.t;
		pthread_mutex_unlock(&m.mutex1);
		sem_wait(&m.sem1);
		matrix mk = m.mk;
		sem_post(&m.sem1);
		
		number temp;
		for (int i = m.size * id; i < m.n; i++) {
			for (int j = 0; j < m.n; j++) {
				temp = 0;
				for (int k = 0; k < m.n; k++)
					temp += m.mo[i][k] * mk[k][j];
				m.a[i] += temp * t[j];
			}
			m.a[i] = m.a[i] * b + d * m.z[i];
		}

		sem_post(&m.sem2);
		sem_wait(&m.sem2);
		sem_post(&m.sem2);

		sort(m.a, m.size * id, m.n - 1);

		std::cout << "Thread #3 has finished its execution\n";
	}, (void*)&m)) return -1;

	pthread_join(m.t0, NULL);
	return 0;
}
