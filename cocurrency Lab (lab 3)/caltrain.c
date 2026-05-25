#include <pthread.h>
#include "caltrain.h"

void
station_init(struct station *station)
{
	station->waiting_passengers = 0;
    station->empty_seats = 0;
    station->passengers_boarding = 0;
    pthread_mutex_init(&station->mutex, NULL);
    pthread_cond_init(&station->all_aboard, NULL);
    pthread_cond_init(&station->train_arrived, NULL);
}

void
station_load_train(struct station *station, int count)
{
	pthread_mutex_lock(&station->mutex);
    station->empty_seats = count;
    pthread_cond_broadcast(&station->train_arrived);
    while ((station->empty_seats > 0 && station->waiting_passengers > 0) || station->passengers_boarding > 0) {
        pthread_cond_wait(&station->all_aboard, &station->mutex);
    }
    station->empty_seats = 0;
    pthread_mutex_unlock(&station->mutex);
}

void
station_wait_for_train(struct station *station)
{
    pthread_mutex_lock(&station->mutex);
    station->waiting_passengers++;
    while (station->empty_seats == 0) {
        pthread_cond_wait(&station->train_arrived, &station->mutex);
    }
    station->waiting_passengers--;
    station->empty_seats--;
    station->passengers_boarding++;
    pthread_mutex_unlock(&station->mutex);

}

void
station_on_board(struct station *station)
{
    pthread_mutex_lock(&station->mutex);
    station->passengers_boarding--;
    pthread_cond_signal(&station->all_aboard);
    pthread_mutex_unlock(&station->mutex);
}