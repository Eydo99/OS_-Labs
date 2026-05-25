#include <pthread.h>

struct station {
    int waiting_passengers;
    int empty_seats;
    int passengers_boarding;
    pthread_mutex_t mutex;
    pthread_cond_t train_arrived;
    pthread_cond_t all_aboard;
};

void station_init(struct station *station);

void station_load_train(struct station *station, int count);

void station_wait_for_train(struct station *station);

void station_on_board(struct station *station);