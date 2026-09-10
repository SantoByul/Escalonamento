#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
    int tempo;
    char nome[12];
    int periodo;
    int deadline;
    int burst;
}Escala;

void escala_rate(){
    FILE *file = fopen("rate_dsob.out", "w");
    fclose(file);
    return;
}

void escala_edf(){
    FILE *file = fopen("edf_dsob.out", "w");
    fclose(file);
    return;
}

Escala *converter_val(FILE *file, int *total){
    if(fscanf(file, "%d", total) != 1){
        fprintf(stderr,"Erro ao ler valor\n");
        return NULL;
    }
    Escala *t = malloc(*total * sizeof(Escala));
    if(!t){
        fprintf(stderr,"Erro na Alocação de Memoria");
        return NULL;
    }
    int i=0;
    while(fscanf(file, "%s %d %d %d", t[i].nome, &t[i].periodo, &t[i].deadline, &t[i].burst) == 4){
        i++;
    }

    for(int j = 0; j < 2;j++){
        printf("%s %d %d %d são os especificos dessa atividade atual\n",t[j].nome, t[j].periodo, t[j].deadline, t[j].burst);
    }
    return t;
}

int main(int argc, char **argv){
    if (argc != 3){
        fprintf(stderr, "Erro: Ocorreu uma falha critica!\n");
        return 1;
    }
    int total = 3;

    FILE *file = fopen("voo.txt","r");
    if(!file){
        fprintf(stderr,"Falha na Localização do Arquivo\n");
        return 1;
    }

    Escala *t = converter_val(file,&total);
    if(!t){
        fclose(file);
        fprintf(stderr, "Falha na Alocação de Memoria");
        return 1;
    }
    if(strcmp(argv[1], "rate") == 0){
        escala_rate();
    }
    else if(strcmp(argv[1], "edf") == 0){
        escala_edf();
    }
    else{
        fprintf(stderr,"Formato de Escalonamento Incorreto\n");
        fclose(file);
        return 1;
    }
    fclose(file);
    return 0;
}