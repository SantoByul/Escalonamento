#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void escala_rate(){
    FILE *file = fopen("rate_dsob.out", "w");
    printf("Funcional Rate\n");
    fprintf(file,"Funcional Rate");
}

void escala_edf(){
    FILE *file = fopen("edf_dsob.out", "w");
    printf("Funcional EDF\n");
    fprintf(file,"Funcional EDF");
}

int main(int argc, char **argv){
    if (argc != 3){
        printf("Quantidade de argumentos invalida\n");
        return 1;
    }

    if(strcmp(argv[1], "rate") == 0){
        escala_rate();
    }
    else if(strcmp(argv[1], "edf") == 0){
        escala_edf();
    }

    return 0;
}