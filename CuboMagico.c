#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

#ifdef _WIN32
    #include <windows.h>

    #define textcolor(cor) ({\
        int iColor;\
        \
        switch(cor) {\
            case 0:\
                iColor=14;\
                break;\
            case 1:\
                iColor=13;\
                break;\
            case 2:\
                iColor=10;\
                break;\
            case 3:\
                iColor=15;\
                break;\
            case 4:\
                iColor=11;\
                break;\
            case 5:\
                iColor=12;\
                break;\
        }\
        \
        HANDLE hl = GetStdHandle(STD_OUTPUT_HANDLE);\
        CONSOLE_SCREEN_BUFFER_INFO bufferInfo;\
        BOOL b = GetConsoleScreenBufferInfo(hl, &bufferInfo);\
        bufferInfo.wAttributes &= 0x00F0;\
        SetConsoleTextAttribute (hl, bufferInfo.wAttributes |= iColor);\
    })

    #define clear() ({\
        system("cls");\
    })

#elif _linux_
    #define textcolor(cor) ({\
        switch(cor) {\
            case 0:\
                printf("\033[01;33m");\
                break;\
            case 1:\
                printf("\033[01;35m");\
                break;\
            case 2:\
                printf("\033[01;32m");\
                break;\
            case 3:\
                printf("\033[01;37m");\
                break;\
            case 4:\
                printf("\033[01;34m");\
                break;\
            case 5:\
                printf("\033[22;31m");\
                break;\
        }\
    })

    #define clear() ({\
        printf("\033[H\033[J");\
    })
#endif

#define tam 3
#define movimentos 10

void imprimirComandos();
void caracteresParaNumeros(char *str);
void zerar(int faces[6][tam][tam]);
void embaralhar(int faces[6][tam][tam], int sequencia[movimentos]);
void imprimir(int faces[6][tam][tam]);
int movimento(int faces[6][tam][tam], int op);
void rotacaoFace(int face[tam][tam], int sentido);
void direita(int faces[6][tam][tam], int deslocamento);
void direitaLinha(int faces[6][tam][tam], int deslocamento);
void esquerda(int faces[6][tam][tam], int deslocamento);
void esquerdaLinha(int faces[6][tam][tam], int deslocamento);
void topo(int faces[6][tam][tam], int deslocamento);
void topoLinha(int faces[6][tam][tam], int deslocamento);
void base(int faces[6][tam][tam], int deslocamento);
void baseLinha(int faces[6][tam][tam], int deslocamento);
void frente(int faces[6][tam][tam], int deslocamento);
void frenteLinha(int faces[6][tam][tam], int deslocamento);
void tras(int faces[6][tam][tam], int deslocamento);
void trasLinha(int faces[6][tam][tam], int deslocamento);

int main() {
    srand((unsigned int)time(NULL));
    int faces[6][tam][tam], sequencia[movimentos];
    int sair;
    int op, i;

    imprimirComandos();
    scanf("%*c");
    clear();

    zerar(faces);
    embaralhar(faces, sequencia);

    for(i = 0; i < movimentos; i++)
        printf("%d ", sequencia[i]);

    sair = 1;
    do {
        printf("\n");
        imprimir(faces);
        textcolor(3);
        printf("\nopcao: ");
        scanf("%d%*c", &op);
        sair = movimento(faces, op);
        if(sair == 0 && op == -1) {
            imprimirComandos();
            scanf("%*c");
            sair = 1;
        }
        else {
            usleep(300000);
        }
        clear();
    } while(sair == 1);

    return 0;
}

void imprimirComandos() {
    int i, j;
    const char *comandos = "RLUDFB";

    printf("\t-1; Comandos\n");
    for(i = 0; i < (tam / 2); i++) {
        for(j = 0; j < 6; j++) {
            printf("\t%.2d: ", (i * 12) + (j * 2));
            if(i > 0) {
                if(i > 1) {
                    printf("%d", i + 1);
                }
                printf("%cw\n", *(comandos + j));
            }
            else {
                printf("%c\n", *(comandos + j));
            }

            printf("\t%.2d: ", (i * 12) + (j * 2) + 1);
            if(i > 0) {
                if(i > 1) {
                    printf("%d", i + 1);
                }
                printf("%cw'\n", *(comandos + j));
            }
            else {
                printf("%c'\n", *(comandos + j));
            }
        }
    }
    printf("\t%.2d: Sair\n", (((tam / 2) - 1) * 12) + 12);
    printf("\nPressione qualquer tecla para continuar...");
}

void caracteresParaNumeros(char *str) {
    int size = (int)strlen(str);
    int comandos[size];
    int quantidade;
    int i;

    quantidade = 0;
    for(i = 0; i < size; i++) {

    }
}

void zerar(int faces[6][tam][tam]) {
    int i, j, k;

    for(i = 0; i < 6; i++) {
        for(j = 0; j < tam; j++) {
            for(k = 0; k < tam; k++)
                faces[i][j][k]= i;
        }
    }
}

void embaralhar(int faces[6][tam][tam], int sequencia[movimentos]) {
    int i, op, opAnterior;
    opAnterior = -10; //So pra nao dar ruim no rand

    for(i = 0; i < movimentos; i++) {
        op = rand() % (12 * (tam / 2));
        while((op % 2 == 0 && opAnterior - op == 1) || (op % 2 == 1 && op - opAnterior == 1)) {
            op = rand() % (12 * (tam / 2));
        }
        sequencia[i] = op;
        opAnterior = op;
        movimento(faces, op);
        //usleep(300000);
        //imprimir(faces);
    }
}

void imprimir(int faces[6][tam][tam]) {
    int i, j, k, l;

    for(i = 0; i < 2; i++) {
        for(j = 0; j < tam; j++) {
            for(l = 0; l < (tam * 2) + 2; l++) {
                printf(" ");
            }
            for(k = 0; k < tam; k++) {
                textcolor(faces[i][j][k]);
                printf("%d ", faces[i][j][k]);
            }
            printf("\n");
        }
        printf("\n");
    }

    for(i = 0; i < tam; i++) {
        for(j = 2; j < 5; j++) {
            for(k = 0; k < tam; k++) {
                textcolor(faces[j][i][k]);
                printf("%d ", faces[j][i][k]);
            }
            printf("  ");
        }
        for(k = (tam - 1); k >= 0; k--) {
            textcolor(faces[0][tam - (i + 1)][k]);
            printf("%d ", faces[0][tam - (i + 1)][k]);
        }
        printf("\n");
    }
    printf("\n");

    for(i = 5, j = 0; j < tam; j++) {
        for(l = 0; l < (tam * 2) + 2; l++) {
            printf(" ");
        }
        for(k = 0; k < tam; k++) {
            textcolor(faces[i][j][k]);
            printf("%d ", faces[i][j][k]);
        }
        printf("\n");
    }
    printf("\n");
}

int movimento(int faces[6][tam][tam], int op) {
    if((op / 12) > ((tam / 2) - 1)) {
        return 0;
    }
    switch(op % 12) {
    case 0:
        direita(faces, op / 12);
        break;
    case 1:
        direitaLinha(faces, op / 12);
        break;
    case 2:
        esquerda(faces, op / 12);
        break;
    case 3:
        esquerdaLinha(faces, op / 12);
        break;
    case 4:
        topo(faces, op / 12);
        break;
    case 5:
        topoLinha(faces, op / 12);
        break;
    case 6:
        base(faces, op / 12);
        break;
    case 7:
        baseLinha(faces, op / 12);
        break;
    case 8:
        frente(faces, op / 12);
        break;
    case 9:
        frenteLinha(faces, op / 12);
        break;
    case 10:
        tras(faces, op / 12);
        break;
    case 11:
        trasLinha(faces, op / 12);
        break;
    default:
        return 0;
    }

    return 1;
}

void rotacaoFace(int face[tam][tam], int sentido) {
    int rot[tam][tam];
    int i, j;

    for(i = 0; i < tam; i++) {
        for(j = 0; j < tam; j++) {
            rot[i][j]= face[i][j];
        }
    }

    if(sentido == 1) {
        for(i = 0; i < tam; i++) {
            for(j = 0; j < tam; j++) {
                face[i][j]= rot[tam - (j + 1)][i];
            }
        }
    }
    else if(sentido == 0) {
        for(i = 0; i < tam; i++) {
            for(j = 0; j < tam; j++) {
                face[i][j]= rot[j][tam - (i + 1)];
            }
        }
    }
}

void direita(int faces[6][tam][tam], int deslocamento) {
    int i;
    int coluna[tam];

while(deslocamento >= 0) {
    for(i = 0; i < tam; i++) {
        coluna[i]= faces[0][i][tam - (1 + deslocamento)];
    }

    for(i = 0; i < tam; i++) {
        faces[0][i][tam - (1 + deslocamento)]= faces[1][i][tam - (1 + deslocamento)];
        faces[1][i][tam - (1 + deslocamento)]= faces[3][i][tam - (1 + deslocamento)];
        faces[3][i][tam - (1 + deslocamento)]= faces[5][i][tam - (1 + deslocamento)];
        faces[5][i][tam - (1 + deslocamento)]= coluna[i];
    }
    deslocamento--;
}
    rotacaoFace(faces[4], 1);
}

void direitaLinha(int faces[6][tam][tam], int deslocamento) {
    int i;
    int coluna[tam];

while(deslocamento >= 0) {
    for(i = 0; i < tam; i++) {
        coluna[i]= faces[5][i][tam - (1 + deslocamento)];
    }

    for(i = 0; i < tam; i++) {
        faces[5][i][tam - (1 + deslocamento)]= faces[3][i][tam - (1 + deslocamento)];
        faces[3][i][tam - (1 + deslocamento)]= faces[1][i][tam - (1 + deslocamento)];
        faces[1][i][tam - (1 + deslocamento)]= faces[0][i][tam - (1 + deslocamento)];
        faces[0][i][tam - (1 + deslocamento)]= coluna[i];
    }
    deslocamento--;
}
    rotacaoFace(faces[4], 0);
}

void esquerda(int faces[6][tam][tam], int deslocamento) {
    int i;
    int coluna[tam];

while(deslocamento >= 0) {
    for(i = 0; i < tam; i++) {
        coluna[i]= faces[5][i][deslocamento];
    }

    for(i = 0; i < tam; i++) {
        faces[5][i][deslocamento]= faces[3][i][deslocamento];
        faces[3][i][deslocamento]= faces[1][i][deslocamento];
        faces[1][i][deslocamento]= faces[0][i][deslocamento];
        faces[0][i][deslocamento]= coluna[i];
    }
    deslocamento--;
}
    rotacaoFace(faces[2], 1);
}

void esquerdaLinha(int faces[6][tam][tam], int deslocamento) {
    int i;
    int coluna[tam];

while(deslocamento >= 0) {
    for(i = 0; i < tam; i++) {
        coluna[i]= faces[0][i][deslocamento];
    }

    for(i = 0; i < tam; i++) {
        faces[0][i][deslocamento]= faces[1][i][deslocamento];
        faces[1][i][deslocamento]= faces[3][i][deslocamento];
        faces[3][i][deslocamento]= faces[5][i][deslocamento];
        faces[5][i][deslocamento]= coluna[i];
    }
    deslocamento--;
}
    rotacaoFace(faces[2], 0);
}

void topo(int faces[6][tam][tam], int deslocamento) {
    int i;
    int linha[tam];

while(deslocamento >= 0) {
    for(i = 0; i < tam; i++) {
        linha[i]= faces[2][deslocamento][i];
    }

    for(i = 0; i < tam; i++) {
        faces[2][deslocamento][i]= faces[3][deslocamento][i];
        faces[3][deslocamento][i]= faces[4][deslocamento][i];
        faces[4][deslocamento][i]= faces[0][tam - (1 + deslocamento)][tam - (i + 1)];
        faces[0][tam - (1 + deslocamento)][tam - (i + 1)]= linha[i];
    }
    deslocamento--;
}
    rotacaoFace(faces[1], 1);
}

void topoLinha(int faces[6][tam][tam], int deslocamento) {
    int i;
    int linha[tam];

while(deslocamento >= 0) {
    for(i = 0; i < tam; i++) {
        linha[i]= faces[2][deslocamento][i];
    }

    for(i = 0; i < tam; i++) {
        faces[2][deslocamento][i]= faces[0][tam - (1 + deslocamento)][tam - (i + 1)];
        faces[0][tam - (1 + deslocamento)][tam - (i + 1)]= faces[4][deslocamento][i];
        faces[4][deslocamento][i]= faces[3][deslocamento][i];
        faces[3][deslocamento][i]= linha[i];
    }
    deslocamento--;
}
    rotacaoFace(faces[1], 0);
}

void base(int faces[6][tam][tam], int deslocamento) {
    int i;
    int linha[tam];

while(deslocamento >= 0) {
    for(i = 0; i < tam; i++) {
        linha[i]= faces[2][tam - (1 + deslocamento)][i];
    }

    for(i = 0; i < tam; i++) {
        faces[2][tam - (1 + deslocamento)][i]= faces[0][deslocamento][tam - (i + 1)];
        faces[0][deslocamento][tam - (i + 1)]= faces[4][tam - (1 + deslocamento)][i];
        faces[4][tam - (1 + deslocamento)][i]= faces[3][tam - (1 + deslocamento)][i];
        faces[3][tam - (1 + deslocamento)][i]= linha[i];
    }
    deslocamento--;
}
    rotacaoFace(faces[5], 1);
}

void baseLinha(int faces[6][tam][tam], int deslocamento) {
    int i;
    int linha[tam];

while(deslocamento >= 0) {
    for(i = 0; i < tam; i++) {
        linha[i]= faces[2][tam - (1 + deslocamento)][i];
    }

    for(i = 0; i < tam; i++) {
        faces[2][tam - (1 + deslocamento)][i]= faces[3][tam - (1 + deslocamento)][i];
        faces[3][tam - (1 + deslocamento)][i]= faces[4][tam - (1 + deslocamento)][i];
        faces[4][tam - (1 + deslocamento)][i]= faces[0][deslocamento][tam - (i + 1)];
        faces[0][deslocamento][tam - (i + 1)]= linha[i];
    }
    deslocamento--;
}
    rotacaoFace(faces[5], 0);
}

void frente(int faces[6][tam][tam], int deslocamento) {
    int i;
    int coluna[tam];

while(deslocamento >= 0) {
    for(i = 0; i < tam; i++) {
        coluna[i]= faces[1][tam - (1 + deslocamento)][i];
    }

    for(i = 0; i < tam; i++) {
        faces[1][tam - (1 + deslocamento)][i]= faces[2][tam - (i + 1)][tam - (1 + deslocamento)];
        faces[2][tam - (i + 1)][tam - (1 + deslocamento)]= faces[5][deslocamento][tam - (i + 1)];
        faces[5][deslocamento][tam - (i + 1)]= faces[4][i][deslocamento];
        faces[4][i][deslocamento]= coluna[i];
    }
    deslocamento--;
}
    rotacaoFace(faces[3], 1);
}

void frenteLinha(int faces[6][tam][tam], int deslocamento) {
    int i;
    int coluna[tam];

while(deslocamento >= 0) {
    for(i = 0; i < tam; i++) {
        coluna[i]= faces[1][tam - (1 + deslocamento)][i];
    }

    for(i = 0; i < tam; i++) {
        faces[1][tam - (1 + deslocamento)][i]= faces[4][i][deslocamento];
        faces[4][i][deslocamento]= faces[5][deslocamento][tam - (i + 1)];
        faces[5][deslocamento][tam - (i + 1)]= faces[2][tam - (i + 1)][tam - (1 + deslocamento)];
        faces[2][tam - (i + 1)][tam - (1 + deslocamento)]= coluna[i];
    }
    deslocamento--;
}
    rotacaoFace(faces[3], 0);
}

void tras(int faces[6][tam][tam], int deslocamento) {
    int i;
    int coluna[tam];

while(deslocamento >= 0) {
    for(i = 0; i < tam; i++) {
        coluna[i]= faces[1][deslocamento][i];
    }

    for(i = 0; i < tam; i++) {
        faces[1][deslocamento][i]= faces[4][i][tam - (1 + deslocamento)];
        faces[4][i][tam - (1 + deslocamento)]= faces[5][tam - (1 + deslocamento)][tam - (i + 1)];
        faces[5][tam - (1 + deslocamento)][tam - (i + 1)]= faces[2][tam - (i + 1)][deslocamento];
        faces[2][tam - (i + 1)][deslocamento]= coluna[i];
    }
    deslocamento--;
}
    rotacaoFace(faces[0], 1);
}

void trasLinha(int faces[6][tam][tam], int deslocamento) {
    int i;
    int coluna[tam];

while(deslocamento >= 0) {
    for(i = 0; i < tam; i++) {
        coluna[i]= faces[1][deslocamento][i];
    }

    for(i = 0; i < tam; i++) {
        faces[1][deslocamento][i]= faces[2][tam - (i + 1)][deslocamento];
        faces[2][tam - (i + 1)][deslocamento]= faces[5][tam - (1 + deslocamento)][tam - (i + 1)];
        faces[5][tam - (1 + deslocamento)][tam - (i + 1)]= faces[4][i][tam - (1 + deslocamento)];
        faces[4][i][tam - (1 + deslocamento)]= coluna[i];
    }
    deslocamento--;
}
    rotacaoFace(faces[0], 0);
}


/*
//http://www.linuxforums.org/forum/programming-scripting/88-color-console.html
gcc -Wall main.c -o main
./main

        0 0 0
        0 0 0
        0 0 0

        1 1 1
        1 1 1
        1 1 1

2 2 2   3 3 3   4 4 4   0 0 0
2 2 2   3 3 3   4 4 4   0 0 0
2 2 2   3 3 3   4 4 4   0 0 0

        5 5 5
        5 5 5
        5 5 5

        fer.rap
*/
