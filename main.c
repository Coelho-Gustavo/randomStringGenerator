#include <stdio.h>
#include <time.h>

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

char *chars(int a) { //Array de caracteres
    char *cL = (char *)malloc(93 * sizeof(char));
    if(!cL){
        return 0;
    }

    if (a){
        FILE *fptr;
        fptr = fopen("charlist.txt", "r");

        fseek(fptr, 0, SEEK_END);
        long sizef = ftell(fptr);
        fseek(fptr, 0, SEEK_SET);

        cL = (char *)realloc(cL, sizef * sizeof(char));

        fgets(cL, sizef+1, fptr);
        fclose(fptr);
        return cL;
    } else {
        for(int i = 0; i < 94; i++){ //Coletor de caracteres em ASCII, conferir tabela para visualizar
            cL[i] = 33+i;
        }
        return cL;
    }
}

unsigned int random(unsigned int *seed) { //Algoritmo Xorshift
    *seed ^= *seed << 13;
    *seed ^= *seed >> 17;
    *seed ^= *seed << 6;

    return *seed;
}

int main() {
    char *cL = chars(0); // Mude pra 1 se quer que os caracteres do charlist.txt sejam utilizados
    unsigned int seed = 0411144127712 * vClock(); //Numero da melhor pizzaria multiplicado pelo clock do processador
    int qChar = 12;

    if (cL) {
        for (int i = 0; i < qChar; i++){
            unsigned int n = random(&seed) % (93);
            //printf("%c", cL[n]);
        }
        free(cL);
    }

    return 0;
}