#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ALFABETO "abcdefghijklmnopqrstuvwxyz "
#define CONVERSAO "0123456789-@#$%&amp;*()_+=.,;/!"

char *decriptografar_rec(char *p_texto, char *resultado) {
    if (*p_texto == '\0') {
        return resultado;
    }

    char *str_pos = strchr(CONVERSAO, *p_texto);
    if (str_pos) {
        int pos = str_pos - CONVERSAO;
        char temp[2];
        temp[0] = ALFABETO[pos];
        temp[1] = '\0';
        strncat(resultado, temp, 1);
        return decriptografar_rec(p_texto + 1, resultado);
    } else {
        strncat(resultado, p_texto, 1);
        return decriptografar_rec(p_texto + 1, resultado);
    }
}

char *decriptografar(char *p_texto) {
    clock_t inicio, fim;
    double tempoDecorrido;

    inicio = clock();

    char *resultado = (char*)malloc(sizeof(char) * (strlen(p_texto) * 2 + 1));

    if (!resultado) {
        printf("\nErro de memória!!\n");
        return NULL;
    }

    memset(resultado, '\0', sizeof(char) * (strlen(p_texto) * 2 + 1));

    resultado = decriptografar_rec(p_texto, resultado);

    fim = clock();
    tempoDecorrido = ((double) (fim - inicio)) / CLOCKS_PER_SEC;
    printf("Tempo de decriptografia: %f segundos\n", tempoDecorrido);

    return resultado;
}

char *criptografar(char *p_texto) {
    clock_t inicio, fim;
    double tempoDecorrido;

    inicio = clock();

    char *temp = p_texto;
    char *resultado = (char*)malloc(sizeof(char) * (strlen(p_texto) * 2 + 1));

    if (!resultado) {
        printf("\nErro de memória!!\n");
        return NULL;
    }

    memset(resultado, '\0', sizeof(char) * (strlen(p_texto) * 2 + 1));

    for (; *temp; temp++) {
        char *str_pos = strchr(ALFABETO, *temp);
        if (str_pos) {
            int pos = str_pos - ALFABETO;
            char temp[2];
            temp[0] = CONVERSAO[pos];
            temp[1] = '\0';
            strncat(resultado, temp, 1);
        } else {
            strncat(resultado, temp, 1);
        }
    }

    fim = clock();
    tempoDecorrido = ((double) (fim - inicio)) / CLOCKS_PER_SEC;
    printf("Tempo de criptografia: %f segundos\n", tempoDecorrido);

    return resultado;
}

int main() {
    char mensagem[] = "abc";
    char *mensagemCriptografada = criptografar(mensagem);
    printf("Mensagem criptografada: %s\n", mensagemCriptografada);

    char *mensagemDecriptografada = decriptografar(mensagemCriptografada);
    printf("Mensagem decriptografada: %s\n", mensagemDecriptografada);

    free(mensagemCriptografada);
    free(mensagemDecriptografada);

    return 0;
}
