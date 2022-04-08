#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char assemblyCommand[255];
char firstNumber[2];
char secondNumber[2];

char* rpnSumToAssembly(char* firstNumber, char* secondNumber);
char* rpnSubToAssembly(char* firstNumber, char* secondNumber);
char* rpnDivToAssembly(char* firstNumber, char* secondNumber);
char* rpnMulToAssembly(char* firstNumber, char* secondNumber);
char* rpnPotToAssembly(char* firstNumber, char* secondNumber);

char* prefix = "#define __SFR_OFFSET 0\n#include \"avr/io.h\"\n\n.global main\n\nmain:\n\n";
char* sufix = "\nret";

int main(void)
{

    char url[] = "../RPN.txt";
    char urlSum[] = "../SUM.txt";
    char urlSub[] = "../SUB.txt";
    char urlMul[] = "../MUL.txt";
    char urlDiv[] = "../DIV.txt";
    char urlPow[] = "../POW.txt";
    char ch;
    char texto_str[5];
    FILE *pont_arq;
    FILE *pont_arqSum;
    FILE *pont_arqSub;
    FILE *pont_arqMul;
    FILE *pont_arqDiv;
    FILE *pont_arqPow;

    pont_arq = fopen(url, "r");
    if (pont_arq == NULL)
    {
        printf("Erro, nao foi possivel abrir o arquivo\n");
    }
    else
    {
        while (fgets(texto_str, 5, pont_arq) != NULL)
        {
            int tamanho = strlen(texto_str);
            int i = 0;

            for (i = 0; i < tamanho; i++)
            {
                switch (texto_str[i])
                {
                case '+':
                    pont_arqSum = fopen(urlSum, "w");
                    firstNumber[0] = texto_str[0];
                    secondNumber[0] = texto_str[1];
                    fprintf(pont_arqSum,"%s", rpnSumToAssembly(firstNumber, secondNumber));
                    fclose(pont_arqSum);
                    break;
                case '*':
                    if (i + 1 < tamanho && texto_str[i + 1] == '*')
                    {
                        //pont_arqPow = fopen(urlPow, "w");
                        //firstNumber[0] = texto_str[0];
                        //secondNumber[0] = texto_str[1];
                        //fprintf(pont_arqPow,"%s", rpnPowToAssembly(firstNumber, secondNumber));
                        //fclose(pont_arqPow);
                    }
                    else
                    {
                        if (texto_str[i - 1] != '*')
                        {
                            pont_arqMul = fopen(urlMul, "w");
                            firstNumber[0] = texto_str[0];
                            secondNumber[0] = texto_str[1];
                            fprintf(pont_arqMul,"%s", rpnMulToAssembly(firstNumber, secondNumber));
                            fclose(pont_arqMul);
                        }
                    }
                    break;
                case '-':
                    pont_arqSub = fopen(urlSub, "w");
                    firstNumber[0] = texto_str[0];
                    secondNumber[0] = texto_str[1];
                    fprintf(pont_arqSub,"%s", rpnSubToAssembly(firstNumber, secondNumber));
                    fclose(pont_arqSub);
                    break;
                case '/':
                    pont_arqDiv = fopen(urlDiv, "w");
                    firstNumber[0] = texto_str[0];
                    secondNumber[0] = texto_str[1];
                    fprintf(pont_arqDiv,"%s", rpnDivToAssembly(firstNumber, secondNumber));
                    fclose(pont_arqDiv);
                    break;
                }

            }
        }
    }

    fclose(pont_arq);

    return (0);

}

char* rpnSumToAssembly(char* firstNumber, char* secondNumber) {
    memset(assemblyCommand, 0, 255);
    char* mov = "mov ax,";
    char* add = "add ax,";
    strcat(assemblyCommand, prefix);
    strcat(assemblyCommand, mov);
    strcat(assemblyCommand, firstNumber);
    strcat(assemblyCommand, "\n");
    strcat(assemblyCommand, add);
    strcat(assemblyCommand, secondNumber);
    strcat(assemblyCommand, "\n");
    strcat(assemblyCommand, sufix);

    return assemblyCommand; //resultado em ax
}

char* rpnSubToAssembly(char firstNumber[], char secondNumber[]) {
    memset(assemblyCommand, 0, 255);
    char* mov = "mov bx,";
    char* sub = "sub bx,";
    strcat(assemblyCommand, prefix);
    strcat(assemblyCommand, mov);
    strcat(assemblyCommand, firstNumber);
    strcat(assemblyCommand, "\n");
    strcat(assemblyCommand, sub);
    strcat(assemblyCommand, secondNumber);
    strcat(assemblyCommand, "\n");
    strcat(assemblyCommand, sufix);

    return assemblyCommand; //resultado em bx
}

char* rpnDivToAssembly(char firstNumber[], char secondNumber[]) {
    memset(assemblyCommand, 0, 255);
    char* movFirst = "mov al,";
    char* movSecond = "mov bl,";
    char* div = "div bl";
    char* result = "add ax, 0";
    strcat(assemblyCommand, prefix);
    strcat(assemblyCommand, movFirst);
    strcat(assemblyCommand, firstNumber);
    strcat(assemblyCommand, "\n");
    strcat(assemblyCommand, movSecond);
    strcat(assemblyCommand, secondNumber);
    strcat(assemblyCommand, "\n");
    strcat(assemblyCommand, div);
    strcat(assemblyCommand, "\n");
    strcat(assemblyCommand, result);
    strcat(assemblyCommand, "\n");
    strcat(assemblyCommand, sufix);

    return assemblyCommand; //resultado em ax
}

char* rpnMulToAssembly(char firstNumber[], char secondNumber[]) {
    memset(assemblyCommand, 0, 255);
    char* movFirst = "mov al,";
    char* movSecond = "mov bl,";
    char* mul = "imul bl";
    char* result = "add ax, 0";
    strcat(assemblyCommand, prefix);
    strcat(assemblyCommand, movFirst);
    strcat(assemblyCommand, firstNumber);
    strcat(assemblyCommand, "\n");
    strcat(assemblyCommand, movSecond);
    strcat(assemblyCommand, secondNumber);
    strcat(assemblyCommand, "\n");
    strcat(assemblyCommand, mul);
    strcat(assemblyCommand, "\n");
    strcat(assemblyCommand, result);
    strcat(assemblyCommand, "\n");
    strcat(assemblyCommand, sufix);

    return assemblyCommand; //resultado em ax
}

// char* rpnPowToAssembly(char firstNumber[], char secondNumber[]) {
//     memset(assemblyCommand, 0, 255);
//     strcat(assemblyCommand, prefix);
//     strcat(assemblyCommand, sufix);
//     return assemblyCommand;
// }
