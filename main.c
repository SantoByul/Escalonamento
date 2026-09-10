#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TOTAL 3

typedef struct{
    char nome[12];
    int periodo;
    int deadline;
    int burst;
    int complete;
    int lost;
    int killed;
}Escala;

int tempo;

void escala_edf(Escala *t){
    FILE *file = fopen("edf_dsob.out", "w");
    if(!file){
        fprintf(stderr,"Erro Envolvendo Arquivo");
        return;
    }

    for(int i = 0; i < TOTAL; i++){
        t[i].complete = 0;
        t[i].lost = 0;
        t[i].killed = 0;
    }

    int restante[TOTAL];
    int prazo[TOTAL];
    for(int i = 0; i < TOTAL; i++){
        restante[i] = 0;
        prazo[i] = 0;
    }
    int atual = -1;
    int inicio = 0;

    for(int i = 0; i < tempo; i++){
        for(int j = 0; j < TOTAL; j++){
            if(i % t[j].periodo == 0){
                if(restante[j] > 0){
                    t[j].lost++;
                }
                restante[j] = t[j].burst;
                prazo[j] = i + t[j].deadline;
            }
        }

        for(int z = 0; z < TOTAL; z++){
            if(restante[z] > 0 && i>= prazo[z]){
                t[z].lost++;
                restante[z] = 0;
                if(atual == z){
                    fprintf(file, "[%s] for %d units - L\n", t[atual].nome, i - inicio);
                    atual = -1;
                    inicio = i;
                }
            }
        }

        int proximo = -1;
        for(int z = 0; z < TOTAL; z++){
            if(restante[z] > 0){
                if(proximo == -1 || prazo[z] < prazo[proximo]){
                    proximo = z;
                }
            }
        }

        if(proximo != atual){
            if(atual == -1){
                if(i > inicio){
                    fprintf(file, "idle for %d units\n", i - inicio);
                }
            } else {
                fprintf(file, "[%s] for %d units - H\n", t[atual].nome, i - inicio);
            }
            atual = proximo;
            inicio = i;
        }

        if(atual != -1){
            restante[atual]--;
            if(restante[atual] == 0){
                t[atual].complete++;
                fprintf(file, "[%s] for %d units - F\n", t[atual].nome, i - inicio + 1);
                atual = -1;
                inicio = i + 1;
            }
        }
    }

    if(atual == -1){
        if(tempo > inicio){
            fprintf(file, "idle for %d units\n", tempo - inicio);
        }
    } else {
        fprintf(file, "[%s] for %d units - H\n", t[atual].nome, tempo - inicio);
    }

    fclose(file);
    return;
}

void escala_rate(Escala *t){
    FILE *file = fopen("rate_dsob.out", "w");
    fclose(file);
    return;
}

Escala *converter_val(FILE *file){
    if(fscanf(file, "%d", &tempo) != 1){
        fprintf(stderr,"Erro ao ler valor\n");
        return NULL;
    }
    Escala *t = malloc(TOTAL * sizeof(Escala));
    if(!t){
        fprintf(stderr,"Erro na Alocação de Memoria");
        return NULL;
    }
    int i=0;
    while(fscanf(file, "%s %d %d %d", t[i].nome, &t[i].periodo, &t[i].deadline, &t[i].burst) == 4) i++;

    return t;
}

int main(int argc, char **argv){
    if (argc != 3){
        fprintf(stderr, "Erro: Ocorreu uma falha critica!\n");
        return 1;
    }

    FILE *file = fopen("voo.txt","r");
    if(!file){
        fprintf(stderr,"Falha na Localização do Arquivo\n");
        return 1;
    }

    Escala *t = converter_val(file);
    if(!t){
        fclose(file);
        fprintf(stderr, "Falha na Alocação de Memoria");
        return 1;
    }
    if(strcmp(argv[1], "rate") == 0){
        escala_rate(t);
    }
    else if(strcmp(argv[1], "edf") == 0){
        escala_edf(t);
    }
    else{
        fprintf(stderr,"Formato de Escalonamento Incorreto\n");
        fclose(file);
        return 1;
    }
    fclose(file);
    return 0;
}