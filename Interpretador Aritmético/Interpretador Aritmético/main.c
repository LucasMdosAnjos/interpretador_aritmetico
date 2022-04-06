#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(void)
{

    char url[] = "../RPN.txt";
    char ch;
    char texto_str[5];
    FILE *pont_arq;

    pont_arq = fopen(url, "r");
    if (pont_arq == NULL)
    {
        printf("Erro, nao foi possivel abrir o arquivo\n");
    }
    else
    {
        while (fgets(texto_str, 5, pont_arq) != NULL)
        {
            // printf("%s",texto_str);
            int tamanho = strlen(texto_str);
            int i = 0;

            for (i = 0; i < tamanho; i++)
            {
                switch (texto_str[i])
                {
                case '+':
                    printf("soma\n");
                    break;
                case '*':
                    if (i + 1 < tamanho && texto_str[i + 1] == '*')
                    {
                        printf("POT\n");
                    }
                    else
                    {
                        if (texto_str[i - 1] != '*')
                        {
                            printf("multi\n");
                        }
                    }
                    break;
                case '-':
                    printf("sub\n");
                    break;
                case '/':
                    printf("div\n");
                    break;
                }
                // Lógica
            }
        }
    }

    fclose(pont_arq);

    return (0);
}
