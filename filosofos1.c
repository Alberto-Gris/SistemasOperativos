#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_FILOSOFOS 5

pthread_mutex_t tenedores[NUM_FILOSOFOS];
sem_t sillas;

void *filosofo(void *arg) {
    int id = *(int *)arg;
    int tenedor_izq = id;
    int tenedor_der = (id + 1) % NUM_FILOSOFOS;

    while (1) {
        // Esperar a que haya una silla disponible
        sem_wait(&sillas);

        // Tomar los tenedores
        pthread_mutex_lock(&tenedores[tenedor_izq]);
        pthread_mutex_lock(&tenedores[tenedor_der]);

        printf("El filósofo %d está comiendo\n", id);
        usleep(1000000); // Simulación de comer

        // Liberar los tenedores
        pthread_mutex_unlock(&tenedores[tenedor_izq]);
        pthread_mutex_unlock(&tenedores[tenedor_der]);

        printf("El filósofo %d ha terminado de comer\n", id);

        // Liberar la silla
        sem_post(&sillas);

        // Pensar un rato
        usleep(1000000); // Simulación de pensar
    }
}

int main() {
    pthread_t filosofos[NUM_FILOSOFOS];
    int ids[NUM_FILOSOFOS];

    // Inicializar los semáforos y mutexes
    sem_init(&sillas, 0, NUM_FILOSOFOS - 1); // Inicialmente, todas las sillas están disponibles excepto una
    for (int i = 0; i < NUM_FILOSOFOS; i++) {
        pthread_mutex_init(&tenedores[i], NULL);
    }

    // Crear hilos para cada filósofo
    for (int i = 0; i < NUM_FILOSOFOS; i++) {
        ids[i] = i;
        pthread_create(&filosofos[i], NULL, filosofo, &ids[i]);
    }

    // Esperar a que todos los hilos terminen
    for (int i = 0; i < NUM_FILOSOFOS; i++) {
        pthread_join(filosofos[i], NULL);
    }

    // Liberar recursos
    sem_destroy(&sillas);
    for (int i = 0; i < NUM_FILOSOFOS; i++) {
        pthread_mutex_destroy(&tenedores[i]);
    }

    return 0;
}
