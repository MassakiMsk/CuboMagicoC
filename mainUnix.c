#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

void textcolor (int cor);
void zerar(int faces[6][3][3]);
void embaralhar(int faces[6][3][3], int movimentos);
void imprimir(int faces[6][3][3]);
int movimento(int faces[6][3][3], char op);
void direita(int faces[6][3][3]);
void direitaLinha(int faces[6][3][3]);
void esquerda(int faces[6][3][3]);
void esquerdaLinha(int faces[6][3][3]);
void topo(int faces[6][3][3]);
void topoLinha(int faces[6][3][3]);
void base(int faces[6][3][3]);
void baseLinha(int faces[6][3][3]);
void frente(int faces[6][3][3]);
void frenteLinha(int faces[6][3][3]);
void tras(int faces[6][3][3]);
void trasLinha(int faces[6][3][3]);

int main() {
    srand(time(NULL));
    int faces[6][3][3];
    int sair;
    char op;

    zerar(faces);
    embaralhar(faces, 10);

    sair = 1;
    do {
        printf("\033[H\033[J");
        printf("\n");
        imprimir(faces);
        printf("\n");
        textcolor(3);
        scanf("%c%*c", &op);
        sair = movimento(faces, op);
        usleep(300000);
    } while(sair == 1);

    return 0;
}

void textcolor (int cor) {
    //http://www.linuxforums.org/forum/programming-scripting/88-color-console.html
    switch(cor) {
        case 0:
            printf("\033[01;33m");
            break;
        case 1:
            printf("\033[01;35m");
            break;
        case 2:
            printf("\033[01;32m");
            break;
        case 3:
            printf("\033[01;37m");
            break;
        case 4:
            printf("\033[01;34m");
            break;
        case 5:
            printf("\033[22;31m");
            break;
    }
}

void zerar(int faces[6][3][3]) {
    int i, j, k;

    for(i = 0; i < 6; i++) {
        for(j = 0; j < 3; j++) {
            for(k = 0; k < 3; k++)
                faces[i][j][k] = i;
        }
    }
}

void embaralhar(int faces[6][3][3], int movimentos) {
    int i, op, opAnterior;
    opAnterior = -10; //So pra nao dar ruim no rand

    for(i = 0; i < movimentos; i++) {
        op = rand() % 12;
        while((op % 2 == 0 && opAnterior - op == 1) || (op % 2 == 1 && op - opAnterior == 1)) {
            op = rand() % 12;
        }
        opAnterior = op;
        switch(op) {
        case 0:
            movimento(faces, 'R');
            break;
        case 1:
            movimento(faces, 'r');
            break;
        case 2:
            movimento(faces, 'L');
            break;
        case 3:
            movimento(faces, 'l');
            break;
        case 4:
            movimento(faces, 'U');
            break;
        case 5:
            movimento(faces, 'u');
            break;
        case 6:
            movimento(faces, 'D');
            break;
        case 7:
            movimento(faces, 'd');
            break;
        case 8:
            movimento(faces, 'F');
            break;
        case 9:
            movimento(faces, 'f');
            break;
        case 10:
            movimento(faces, 'B');
            break;
        case 11:
            movimento(faces, 'b');
            break;
        default:
            break;
        }
    }
}

void imprimir(int faces[6][3][3]) {
    int i, j, k;

    for(i = 0; i < 2; i++) {
        for(j = 0; j < 3; j++) {
            printf("        ");
            for(k = 0; k < 3; k++) {
                textcolor(faces[i][j][k]);
                printf("%d ", faces[i][j][k]);
            }
            printf("\n");
        }
        printf("\n");
    }

    for(i = 0; i < 3; i++) {
        for(j = 2; j < 5; j++) {
            for(k = 0; k < 3; k++) {
                textcolor(faces[j][i][k]);
                printf("%d ", faces[j][i][k]);
            }
            printf("  ");
        }
        for(k = 2; k >= 0; k--) {
            textcolor(faces[0][2 - i][k]);
            printf("%d ", faces[0][2 - i][k]);
        }
        printf("\n");
    }
    printf("\n");

    for(i = 5, j = 0; j < 3; j++) {
        printf("        ");
        for(k = 0; k < 3; k++) {
            textcolor(faces[i][j][k]);
            printf("%d ", faces[i][j][k]);
        }
        printf("\n");
    }
    printf("\n");
}

int movimento(int faces[6][3][3], char op) {
    switch(op) {
    case 'R':
        direita(faces);
        break;
    case 'r':
        direitaLinha(faces);
        break;
    case 'L':
        esquerda(faces);
        break;
    case 'l':
        esquerdaLinha(faces);
        break;
    case 'U':
        topo(faces);
        break;
    case 'u':
        topoLinha(faces);
        break;
    case 'D':
        base(faces);
        break;
    case 'd':
        baseLinha(faces);
        break;
    case 'F':
        frente(faces);
        break;
    case 'f':
        frenteLinha(faces);
        break;
    case 'B':
        tras(faces);
        break;
    case 'b':
        trasLinha(faces);
        break;
    default:
        return 0;
    }

    return 1;
}

void horario(int face[3][3]) {
    int auxiliar;

    auxiliar = face[0][0];
    face[0][0] = face[2][0];
    face[2][0] = face[2][2];
    face[2][2] = face[0][2];
    face[0][2] = auxiliar;

    auxiliar = face[0][1];
    face[0][1] = face[1][0];
    face[1][0] = face[2][1];
    face[2][1] = face[1][2];
    face[1][2] = auxiliar;
}

void antiHorario(int face[3][3]) {
    int auxiliar;

    auxiliar = face[0][0];
    face[0][0] = face[0][2];
    face[0][2] = face[2][2];
    face[2][2] = face[2][0];
    face[2][0] = auxiliar;

    auxiliar = face[0][1];
    face[0][1] = face[1][2];
    face[1][2] = face[2][1];
    face[2][1] = face[1][0];
    face[1][0] = auxiliar;
}

void direita(int faces[6][3][3]) {
    int i;
    int coluna[3];

    for(i = 0; i < 3; i++) {
        coluna[i] = faces[0][i][2];
    }

    for(i = 0; i < 3; i++) {
        faces[0][i][2] = faces[1][i][2];
        faces[1][i][2] = faces[3][i][2];
        faces[3][i][2] = faces[5][i][2];
        faces[5][i][2] = coluna[i];
    }

    horario(faces[4]);
}

void direitaLinha(int faces[6][3][3]) {
    int i;
    int coluna[3];

    for(i = 0; i < 3; i++) {
        coluna[i] = faces[5][i][2];
    }

    for(i = 0; i < 3; i++) {
        faces[5][i][2] = faces[3][i][2];
        faces[3][i][2] = faces[1][i][2];
        faces[1][i][2] = faces[0][i][2];
        faces[0][i][2] = coluna[i];
    }

    antiHorario(faces[4]);
}

void esquerda(int faces[6][3][3]) {
    int i;
    int coluna[3];

    for(i = 0; i < 3; i++) {
        coluna[i] = faces[5][i][0];
    }

    for(i = 0; i < 3; i++) {
        faces[5][i][0] = faces[3][i][0];
        faces[3][i][0] = faces[1][i][0];
        faces[1][i][0] = faces[0][i][0];
        faces[0][i][0] = coluna[i];
    }

    horario(faces[2]);
}

void esquerdaLinha(int faces[6][3][3]) {
    int i;
    int coluna[3];

    for(i = 0; i < 3; i++) {
        coluna[i] = faces[0][i][0];
    }

    for(i = 0; i < 3; i++) {
        faces[0][i][0] = faces[1][i][0];
        faces[1][i][0] = faces[3][i][0];
        faces[3][i][0] = faces[5][i][0];
        faces[5][i][0] = coluna[i];
    }

    antiHorario(faces[2]);
}

void topo(int faces[6][3][3]) {
    int i;
    int linha[3];

    for(i = 0; i < 3; i++) {
        linha[i] = faces[2][0][i];
    }

    for(i = 0; i < 3; i++) {
        faces[2][0][i] = faces[3][0][i];
        faces[3][0][i] = faces[4][0][i];
        faces[4][0][i] = faces[0][2][2 - i];
        faces[0][2][2 - i] = linha[i];
    }

    horario(faces[1]);
}

void topoLinha(int faces[6][3][3]) {
    int i;
    int linha[3];

    for(i = 0; i < 3; i++) {
        linha[i] = faces[2][0][i];
    }

    for(i = 0; i < 3; i++) {
        faces[2][0][i] = faces[0][2][2 - i];
        faces[0][2][2 - i] = faces[4][0][i];
        faces[4][0][i] = faces[3][0][i];
        faces[3][0][i] = linha[i];
    }

    antiHorario(faces[1]);
}

void base(int faces[6][3][3]) {
    int i;
    int linha[3];

    for(i = 0; i < 3; i++) {
        linha[i] = faces[2][2][i];
    }

    for(i = 0; i < 3; i++) {
        faces[2][2][i] = faces[0][0][2 - i];
        faces[0][0][2 - i] = faces[4][2][i];
        faces[4][2][i] = faces[3][2][i];
        faces[3][2][i] = linha[i];
    }

    horario(faces[5]);
}

void baseLinha(int faces[6][3][3]) {
    int i;
    int linha[3];

    for(i = 0; i < 3; i++) {
        linha[i] = faces[2][2][i];
    }

    for(i = 0; i < 3; i++) {
        faces[2][2][i] = faces[3][2][i];
        faces[3][2][i] = faces[4][2][i];
        faces[4][2][i] = faces[0][0][2 - i];
        faces[0][0][2 - i] = linha[i];
    }

    antiHorario(faces[5]);
}

void frente(int faces[6][3][3]) {
    int i;
    int coluna[3];

    for(i = 0; i < 3; i++) {
        coluna[i] = faces[1][2][i];
    }

    for(i = 0; i < 3; i++) {
        faces[1][2][i] = faces[2][2 - i][2];
        faces[2][2 - i][2] = faces[5][0][2 - i];
        faces[5][0][2 - i] = faces[4][i][0];
        faces[4][i][0] = coluna[i];
    }

    horario(faces[3]);
}

void frenteLinha(int faces[6][3][3]) {
    int i;
    int coluna[3];

    for(i = 0; i < 3; i++) {
        coluna[i] = faces[1][2][i];
    }

    for(i = 0; i < 3; i++) {
        faces[1][2][i] = faces[4][i][0];
        faces[4][i][0] = faces[5][0][2 - i];
        faces[5][0][2 - i] = faces[2][2 - i][2];
        faces[2][2 - i][2] = coluna[i];
    }

    antiHorario(faces[3]);
}

void tras(int faces[6][3][3]) {
    int i;
    int coluna[3];

    for(i = 0; i < 3; i++) {
        coluna[i] = faces[1][0][i];
    }

    for(i = 0; i < 3; i++) {
        faces[1][0][i] = faces[4][i][2];
        faces[4][i][2] = faces[5][2][2 - i];
        faces[5][2][2 - i] = faces[2][2 - i][0];
        faces[2][2 - i][0] = coluna[i];
    }

    horario(faces[0]);
}

void trasLinha(int faces[6][3][3]) {
    int i;
    int coluna[3];

    for(i = 0; i < 3; i++) {
        coluna[i] = faces[1][0][i];
    }

    for(i = 0; i < 3; i++) {
        faces[1][0][i] = faces[2][2 - i][0];
        faces[2][2 - i][0] = faces[5][2][2 - i];
        faces[5][2][2 - i] = faces[4][i][2];
        faces[4][i][2] = coluna[i];
    }

    antiHorario(faces[0]);
}

/*
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
