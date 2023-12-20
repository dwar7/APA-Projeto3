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


/*
    1. O código implementa funções de criptografia e decriptografia, proporcionando uma visão prática do funcionamento do algoritmo;
A medição do tempo de execução nas operações de criptografia e decriptografia fornece uma indicação inicial do desempenho do algoritmo;
A análise de complexidade será crucial para orientar futuras melhorias e otimizações no algoritmo, garantindo sua eficiência em diferentes 
contextos de uso.
    2 e 3. Função de Criptografia (criptografar):
Complexidade Temporal:  A complexidade é linear em relação ao tamanho da mensagem (O(n)), onde "n" é o comprimento da mensagem.
Função de Decriptografia (decriptografar_rec e decriptografar):
Complexidade Temporal: A função decriptografar chama a função recursiva decriptografar_rec. A complexidade é linear em 
relação ao tamanho da mensagem (O(n)), onde "n" é o comprimento da mensagem.
Em relação ao comportamento, o algoritmo apresenta uma complexidade linear em ambas as operações de criptografia e decriptografia.
    4. O algoritmo de criptografia implementa uma substituição simples de caracteres usando conjuntos ALFABETO e CONVERSAO.
A função de criptografia percorre a mensagem, substituindo caracteres, e a decriptografia usa recursão. A complexidade 
temporal é linear em relação ao comprimento da mensagem. O desempenho é medido em segundos usando time.h, com alocação 
dinâmica de memória.
    5. A implementação mede o desempenho por meio da biblioteca time.h, registrando o tempo de execução das funções de 
criptografia e decriptografia. Testes práticos com a mensagem "abc" são realizados, fornecendo uma avaliação empírica do 
    algoritmo.
        6. O código apresenta um algoritmo de criptografia com uma função de decriptografia que utiliza recursão. 
    A função decriptografar_rec mostra um exemplo onde a recursão é aplicada para processar 
cada caractere da mensagem. A análise revela uma relação de recorrência linear.
    7.  No contexto da análise de algoritmos iterativos e recursivos, aqui temos a função decriptografar_rec, que utiliza 
recursão para processar cada caractere da mensagem. A comparação de desempenho entre abordagens iterativas e recursivas no 
contexto da criptografia revela que, embora a recursão seja eficaz, ela pode introduzir uma sobrecarga computacional devido
à pilha de chamadas. A eficiência de cada abordagem é essencialmente determinada pelo equilíbrio entre a clareza do código 
e a otimização de recursos computacionais.
    11. Durante o desenvolvimento e análise do algoritmo de criptografia, observamos uma implementação funcional que utiliza
substituição de caracteres para cifrar e decifrar mensagens. A medição de desempenho revelou tempos de execução, proporcionando 
    uma base para avaliação. A importância das técnicas de projeto eficiente na otimização do desempenho e segurança torna-se 
    evidente ao analisar o código. Estratégias como iterações e gestão eficiente de memória são fundamentais para garantir que 
o algoritmo seja eficaz em termos de desempenho. Em resumo, a busca por técnicas eficientes é crucial para aprimorar algoritmos,
    tornando-os mais rápidos e seguros.
    */
