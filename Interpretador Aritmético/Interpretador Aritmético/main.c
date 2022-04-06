#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(void)
{

    char url[] = "../RPN.txt";
    char ch;
    char texto_str[4];
    FILE *pont_arq;

    pont_arq = fopen(url, "r");
    if (pont_arq == NULL)
    {
        printf("Erro, nao foi possivel abrir o arquivo\n");
    }
    else
    {
        while (fgets(texto_str, 4, pont_arq) != NULL){
           // printf("%s",texto_str);
            int tamanho = strlen(texto_str);
            int i = 0;
            for( i= 0; i < tamanho ; i++){
                //Lógica
                printf("%c",texto_str[i]);
            }
        }
        
    }

    fclose(pont_arq);

    return (0);
}
