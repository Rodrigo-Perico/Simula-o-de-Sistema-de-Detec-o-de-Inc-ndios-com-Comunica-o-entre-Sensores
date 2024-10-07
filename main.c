#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#define INTERVALO_INCENDIO 3
#define TAMANHO_FLORA 30

void* monitorar_sensor(void* arg);
void* gerar_incendios(void* arg);
void imprimir_matriz();
void propagar_mensagem(int i, int j);

char matriz[TAMANHO_FLORA][TAMANHO_FLORA];

int main() {
    pthread_t sensores[TAMANHO_FLORA][TAMANHO_FLORA];
    pthread_t gerador_incendios;

    for (int i = 0; i < TAMANHO_FLORA; i++)
    {
        for (int j = 0; j < TAMANHO_FLORA; j++)
        {
            matriz[i][j] = 'A';
        }
    }

    for (int i = 0; i < TAMANHO_FLORA; i++)
    {
        for (int j = 0; j < TAMANHO_FLORA; j++)
        {
            int* pos = malloc(2 * sizeof(int));
            pos[0] = i;
            pos[1] = j;
            pthread_create(&sensores[i][j], NULL, monitorar_sensor, (void*)pos);
        }
    }

    pthread_create(&gerador_incendios, NULL, gerar_incendios, NULL);

    pthread_join(gerador_incendios, NULL);

    for (int i = 0; i < TAMANHO_FLORA; i++)
    {
        for (int j = 0; j < TAMANHO_FLORA; j++)
        {
            pthread_join(sensores[i][j], NULL);
        }
    }
    return 0;
}
