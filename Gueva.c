#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

typedef struct {
    unsigned int clave; 
    char nombre[21],
         telefono[11];
    double sueldo;
} Empleado;

void swap(Empleado *a, Empleado *b) {
    Empleado temp = *a;
    *a = *b;
    *b = temp;
}

void bubbleSort(Empleado arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (strcmp(arr[j].nombre, arr[j+1].nombre) > 0) {
                swap(&arr[j], &arr[j+1]);
            }
        }
    }
}

int main() {
    Empleado empleados[] = {
            {1, "juan",    "210848",   8240.99  }, // registro 0
            {2, "aurora",  "710848",   3240.34  }, // registro 1
            {3, "roberto", "810848",   9240.23  }, // registro 2
            {4, "celia",   "910848", 103240.23  }, // registro 3
            {5, "cecilia", "310848",  13240.27  }, // registro 4
            {6, "ramon",   "450848",  32540.23  }, // registro 5
            {7, "jacinto", "830848",  32460.55  }, // registro 6
    };
    printf("record size = %ld\n", sizeof(Empleado));

    // Ordenar los empleados por nombre
    bubbleSort(empleados, 7);

    // Crear el archivo db.personas
    int fd = open("db.personas", O_WRONLY|O_CREAT|O_TRUNC, 0600);
    if (fd == -1) {
        perror("Error al abrir el archivo db.personas");
        return 1;
    }
    write(fd, (void *)empleados, 7*sizeof(Empleado));
    close(fd);

    // Crear el archivo índice
    FILE *fp_index = fopen("indice.txt", "w");
    if (fp_index == NULL) {
        perror("Error al abrir el archivo indice.txt");
        return 1;
    }
    for (int i = 0; i < 7; i++) {
        fprintf(fp_index, "%d\n", empleados[i].clave);
    }
    fclose(fp_index);

    
    printf("Tabla ordenada por nombre:\n");
    printf("Clave\tNombre\tTelefono\tSueldo\n");
    for (int i = 0; i < 7; i++) {
        printf("%u\t%s\t%s\t%.2f\n", empleados[i].clave, empleados[i].nombre, empleados[i].telefono, empleados[i].sueldo);
    }

    return 0;
}
