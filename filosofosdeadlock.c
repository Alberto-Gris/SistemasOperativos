#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <signal.h>

#define NUM_FILOSOFOS 5
#define TIMEOUT 3 // Tiempo de espera en segundos

pthread_mutex_t tenedores[NUM_FILOSOFOS];
sem_t sillas;
int deadlock_detectado = 0;

void *filosofo(void *arg) {
    int id = *(int *)arg;
    int tenedor_izq = id;
    int tenedor_der = (id + 1) % NUM_FILOSOFOS;

    while (1) {
        // Intentar tomar tenedores
        if (pthread_mutex_trylock(&tenedores[tenedor_izq]) == 0) {
            if (pthread_mutex_trylock(&tenedores[tenedor_der]) == 0) {
                printf("El filósofo %d está comiendo\n", id);
                usleep(1000000); // Simulación de comer

                // Liberar los tenedores
                pthread_mutex_unlock(&tenedores[tenedor_izq]);
                pthread_mutex_unlock(&tenedores[tenedor_der]);

                printf("El filósofo %d ha terminado de comer\n", id);
                usleep(1000000); // Simulación de pensar

                // Resetear el estado de deadlock si se detectó
                deadlock_detectado = 0;
            } else {
                pthread_mutex_unlock(&tenedores[tenedor_izq]);
            }
        }

        // Si no se pudieron tomar ambos tenedores, esperar un tiempo y volver a intentar
        if (!deadlock_detectado) {
            sleep(TIMEOUT);
            if (pthread_mutex_trylock(&tenedores[tenedor_izq]) == 0) {
                if (pthread_mutex_trylock(&tenedores[tenedor_der]) == 0) {
                    printf("El filósofo %d ha superado el deadlock y está comiendo\n", id);
                    usleep(1000000); // Simulación de comer

                    // Liberar los tenedores
                    pthread_mutex_unlock(&tenedores[tenedor_izq]);
                    pthread_mutex_unlock(&tenedores[tenedor_der]);

                    printf("El filósofo %d ha terminado de comer\n", id);
                    usleep(1000000); // Simulación de pensar

                    // Resetear el estado de deadlock si se detectó
                    deadlock_detectado = 0;
                } else {
                    pthread_mutex_unlock(&tenedores[tenedor_izq]);
                }
            }
        } else {
            printf("¡Deadlock detectado para el filósofo %d!\n", id);
        }
    }
}

void handle_signal(int sig) {
    if (sig == SIGINT) {
        printf("Terminando la ejecución.\n");
        exit(0);
    }
}

int main() {
    // Manejar señal SIGINT (Ctrl+C)
    signal(SIGINT, handle_signal);

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
