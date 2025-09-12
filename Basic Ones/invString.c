#include <stdio.h>

char *invString(char *str)
{
    int tamanho = 0;
    int inicio, fim;
    char temp;

    while (str[tamanho] != '\0') tamanho++;

    fim = tamanho - 1; // Subtrai 1 devido ao caractere nulo

    //Faz a inversão das strings
    for (inicio = 0, fim; inicio < fim; inicio++, fim--){
        temp = str[fim];
        str[fim] = str[inicio];
        str[inicio] = temp;
    }

    return str;
}

int main()
{

    char str[] = "Exemplo de string";
    printf("String original: %s\n", str);
    printf("String invertida: %s\n", invString(str));

    return 0;
}