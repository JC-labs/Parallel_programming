#pragma once
#define pthread_cr_sec_t pthread_mutex_t
#define pthread_cr_sec_init(name) pthread_mutex_init(name, NULL);
#define pthread_cr_sec_start(name) pthread_mutex_lock(name);
#define pthread_cr_sec_end(name) pthread_mutex_unlock(name);
#define pthread_cr_sec_destroy(name) pthread_mutex_destroy(name);