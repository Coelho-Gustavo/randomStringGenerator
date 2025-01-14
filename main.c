#include <stdio.h>
#include <time.h>

#define ASCII_START 33
#define ASCII_STOP 94
#define FILENAME "charlist.txt"
#define QNT_CHAR 16
#define USARARQUIVO 1


int vClock() {
    time_t t, it;
    struct tm *tms;

    time(&t);
    tms = localtime(&t);
    tms->tm_hour = 0;
    tms->tm_min = 0;
    tms->tm_sec = 0;

    it = mktime(tms);
    return difftime(t, it);
}

int chars(int a, char **cL) { //Array de caracteres
    *cL = (char *)realloc(*cL, 93 * sizeof(char));
    if(!*cL){
        perror("Erro ao alocar memória");
        return 0;
    }

    if (a){
        FILE *fptr;
        fptr = fopen(FILENAME, "r");
        if(fptr == NULL){
            perror("Erro ao abrir arquivo");
            return 0;
        }

        fseek(fptr, 0, SEEK_END);
        long sizef = ftell(fptr);
        fseek(fptr, 0, SEEK_SET);

        *cL = (char *)realloc(*cL, sizef * sizeof(char));
        if(!*cL){
            perror("Erro ao realocar memoria");
            fclose(fptr);
            return 0;
        }

        fgets(*cL, sizef+1, fptr);
        fclose(fptr);
        return sizef;
    } else {
        for(int i = 0; i < ASCII_STOP; i++){ //Coletor de caracteres em ASCII, conferir tabela para visualizar
            (*cL)[i] = ASCII_START+i;
        }
        return ASCII_STOP-1;
    }
}

unsigned int random(unsigned int *seed) { //Algoritmo Xorshift
    *seed ^= *seed << 13;
    *seed ^= *seed >> 17;
    *seed ^= *seed << 6;

    return *seed;
}

int main() {
    char *cL = (char *)malloc(0);
    if(!cL){
        perror("Erro ao alocar memoria");
        free(cL);
        return 0;
    }
    int sizef = chars(USARARQUIVO, &cL); // Mude pra 1 se quer que os caracteres do charlist.txt sejam utilizados
    printf("%d\n", sizef);
    unsigned int seed = 0411144127712 * vClock(); //Numero da melhor pizzaria multiplicado pelo clock do processador
    
    for (int i = 0; i < QNT_CHAR; i++){
        unsigned int n = random(&seed) % (sizef);
        printf("%c", cL[n]);
    }

    free(cL);

    return 0;
}