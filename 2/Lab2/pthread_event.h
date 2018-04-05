#pragma once
#include <pthread.h>
struct pthread_event_t {
    bool s;
    pthread_mutex_t m;
    pthread_cond_t c;
};
void pthread_event_init(pthread_event_t *ev, pthread_condattr_t *attr) {
    ev->s = false;
    pthread_mutex_init(&ev->m, NULL);
    pthread_cond_init(&ev->c, attr);
}
void pthread_event_destroy(pthread_event_t *ev) {
    pthread_mutex_destroy(&ev->m);
    pthread_cond_destroy(&ev->c);
}
void pthread_event_wait(pthread_event_t *ev) {
    pthread_mutex_lock(&ev->m);
    while (!ev->s) {
        pthread_cond_wait(&ev->c, &ev->m);
    }
    //ev->s = false;
    pthread_mutex_unlock(&ev->m);
}
void pthread_event_signal(pthread_event_t *ev) {
        pthread_mutex_lock(&ev->m);
        ev->s = true;
        pthread_mutex_unlock(&ev->m);
        pthread_cond_broadcast(&ev->c);
}