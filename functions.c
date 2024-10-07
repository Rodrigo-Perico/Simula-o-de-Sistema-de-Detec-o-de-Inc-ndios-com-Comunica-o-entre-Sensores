#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#define INTERVALO_INCENDIO 3
#define TAMANHO_FLORA 30

extern char matriz[TAMANHO_FLORA][TAMANHO_FLORA];

void* monitorar_sensor(void* arg)
{
    int i = *((int*)arg);
    int j = *((int*)arg + 1);

    while (1)
    {
        int incendio = rand() % 100;
        if (incendio < 10)
        {
            printf("Incêndio detectado no sensor (%d, %d)!\n", i, j);
            matriz[i][j] = 'F';
            propagar_mensagem(i, j);
        }
        sleep(1);
    }
}

void* gerar_incendios(void* arg)
{
    while (1)
    {
        int i = rand() % TAMANHO_FLORA;
        int j = rand() % TAMANHO_FLORA;

        printf("Incêndio gerado na célula (%d, %d)!\n", i, j);
        matriz[i][j] = 'F';
        
        sleep(INTERVALO_INCENDIO);
    }
}

void propagar_mensagem(int i, int j) {
    
    printf("Propagando mensagem do sensor (%d, %d) para seus vizinhos...\n", i, j);
    for (int x = i - 1; x <= i + 1; x++)
    {
        for (int y = j - 1; y <= j + 1; y++)
        {
            if (x >= 0 && x < TAMANHO_FLORA && y >= 0 && y < TAMANHO_FLORA)
            {
                if (matriz[x][y] != 'F')
                {
                    matriz[x][y] = 'F';
                    printf("Célula (%d, %d) agora está em chamas!\n", x, y);
                }
            }
        }
    }
}
