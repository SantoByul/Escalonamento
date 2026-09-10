#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
    int tempo;
    char nome[2];
    int periodo;
    int deadline;
    int burst;
}Escala;

void escala_rate(){
    FILE *file = fopen("rate_dsob.out", "w");
    printf("Funcional Rate\n");
    fprintf(file,"Funcional Ratez\n");
}

void escala_edf(){
    FILE *file = fopen("edf_dsob.out", "w");
    printf("Funcional EDF\n");
    fprintf(file,"Funcional EDF\n");
}

void converter_val(FILE *file, Escala *t){
    if(fscanf(file, "%d", &t->tempo) != 1){
        printf("Erro ao ler valor\n");
        return;
    }
    printf("Tempo total: %d\n", t->tempo);

    while(fscanf(file, "%s %d %d %d", t->nome, &t->periodo, &t->deadline, &t->burst) == 4){
        printf("%s %d %d %d são os especificos dessa atividade atual\n",t->nome, t->periodo, t->deadline, t->burst);
    }
    return;
}

int main(int argc, char **argv){
    if (argc != 3){
        printf("Quantidade de argumentos invalida\n");
        return 1;
    }

    FILE *file = fopen("voo.txt","r");
    if(!file){
        printf("Falha na Localização do Arquivo\n");
        return 1;
    }

    Escala t;
    converter_val(file, t);
    if(strcmp(argv[1], "rate") == 0){
        escala_rate();
    }
    else if(strcmp(argv[1], "edf") == 0){
        escala_edf();
    }
    else{
        printf("Formato de Escalonamento Incorreto\n");
        return 1;
    }

    return 0;
}