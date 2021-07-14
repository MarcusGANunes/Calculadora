#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct celula celula;
typedef celula* pont;
struct celula {
    int num;
    pont prox;
};
typedef pont numero;

numero LerArmazenar();
void Escrever(numero);
numero Soma(numero, numero);
numero Mult(numero, numero);


int main() {
    numero enc1, enc2, S, P;
    S = (numero) malloc(sizeof(celula));
    P = (numero) malloc(sizeof(celula));
    printf("SOMA E PRODUTO DE 2 NUMEROS");
    enc1 = LerArmazenar();
    printf("\n\tNumero lido: ");
    Escrever(enc1);
    printf("\n\n");
    enc2 = LerArmazenar();
    printf("\n\tNumero lido: ");
    Escrever(enc2);
    printf("\n\n\nRESULTADOS");
    printf("\n\n\tA soma eh: ");
    S = Soma(enc1, enc2);
    Escrever(S);
    printf("\n\n\tO produto eh: ");
    P = Mult(enc1, enc2);
    Escrever(P);
    printf("\n\n");
    system("pause");
    return 0;
}

numero LerArmazenar(){
    char A[110], B[25][5];
    int i, j, k, t, ver;
    numero enc, P;
    printf("\n\n\tDigite o numero: ");
    scanf("%s", A);
    ver = 1;
    for (i = 0; i < strlen(A); i++){
        if (!isdigit(A[i]))
            ver = 0;
    }
    if (ver == 0){
        enc = (celula *) malloc(sizeof(celula));
        enc->prox = (celula *) malloc(sizeof(celula));
        enc->prox->num = -1;
        enc->prox->prox = NULL;
    }
    else if (atoi(A) == 0){
        enc = (celula *) malloc(sizeof(celula));
        enc->prox = (celula *) malloc(sizeof(celula));
        enc->prox->num = 0;
        enc->prox->prox = NULL;
    }
    else{
        {
            char aux[110];
            i = 0;
            while (A[i] == '0'){
                i++;
            }
            for (t = i, j = 0; t < strlen(A); t++, j++){
                aux[j] = A[t];
            }
            aux[j] = '\0';
            strcpy(A, aux);
        }
        for (i = 0, k = strlen(A) - 4; i <= strlen(A)/4; i++, k = k-4){
            for (j = 0; j <= 4; j++){
                if (i != strlen(A)/4){
                    if (j != 4)
                        B[i][j] = A[k+j];
                    else
                        B[i][j] = '\0';
                }
                else{
                    if (j < strlen(A)%4)
                    B[i][j] = A[j];
                    else
                        B[i][j] = '\0';
                }
            }
        }
        if (strlen(A)%4 == 0)
        t = strlen(A)/4 - 1;
        else
            t = strlen(A)/4;
        enc = (numero) malloc(sizeof(celula));
        for (P = enc, i = 0; i <= t; i++){
            P->prox = (numero) malloc(sizeof(celula));
            P = P->prox;
            P->num = atoi(B[i]);
        }
        P->prox = NULL;
    }
    return enc;
}

void Escrever(numero P){
    int i, j = 0, C[24];
    char B[25][5], A[110]={'\0'};
    numero Q;
    if (P->prox->num == -1)
        printf("Numero irregular");
    else{
        for (Q = P->prox, i = 0; Q != NULL; Q = Q->prox, i++){
            C[i] = Q->num;
            if (C[i] == 0){
                strcpy(B[i], "0000");
                B[i][4] = '\0';
                j++;
            }
            else if (C[i] < 10){
                char aux[4];
                sprintf(aux, "%d", C[i]);
                strcpy(B[i], "000");
                strcat(B[i], aux);
                B[i][4] = '\0';
                j++;
            }
            else if (C[i] < 100){
                char aux[4];
                sprintf(aux, "%d", C[i]);
                strcpy(B[i], "00");
                strcat(B[i], aux);
                B[i][4] = '\0';
                j++;
            }
            else if (C[i] < 1000){
                char aux[4];
                sprintf(aux, "%d", C[i]);
                strcpy(B[i], "0");
                strcat(B[i], aux);
                B[i][4] = '\0';
                j++;
            }
            else if (C[i] < 10000){
                sprintf(B[i], "%d", C[i]);
                B[i][4] = '\0';
                j++;
            }
        }
        for (i = j - 1; i >= 0; i--){
            strcat(A, B[i]);
        }
        A[4*j] = '\0';
        if(atoi(A) == 0){
            printf("0");
        }
        else{
            char aux[110];
            int i = 0, j = 0, t;
            while (A[i] == '0'){
                i++;
            }
            for (t = i; t < strlen(A); t++, j++){
                aux[j] = A[t];
            }
            aux[j] = '\0';
            strcpy(A, aux);
            printf("%s", A);
        }
    }
    return;
}

numero Soma(numero P, numero Q){
    int i, carry[25] = {0};
    numero soma, X, Y, Z;
    if(P->prox->num != -1 && Q->prox->num != -1){
        soma = (numero) malloc(sizeof(celula));
        for (i = 0, Z = soma, X = P->prox, Y = Q->prox; X != NULL || Y != NULL; i++){
            Z->prox = (numero) malloc(sizeof(celula));
            Z = Z->prox;
            if (X != NULL && Y != NULL){
                if (X->num + Y->num + carry[i] >= 10000){
                    carry[i+1] = 1;
                    Z->num = (X->num + Y->num + carry[i])%10000;
                }
                else
                    Z->num = X->num + Y->num + carry[i];
                X = X->prox;
                Y = Y->prox;
            }
            else if (X == NULL){
                if (Y->num + carry[i] >= 10000){
                    carry[i+1] = 1;
                    Z->num = (Y->num + carry[i])%10000;
                }
                else
                    Z->num = Y->num + carry[i];
                Y = Y->prox;
            }
            else{
                if (X->num + carry[i] >= 10000){
                    carry[i+1] = 1;
                    Z->num = (X->num + carry[i])%10000;
                }
                else
                    Z->num = X->num + carry[i];
                X = X->prox;
            }
        }
        if (carry[i] != 0){
            Z->prox = (numero) malloc(sizeof(celula));
            Z = Z->prox;
            Z->num = carry[i];
            Z->prox = NULL;
        }
        else
            Z->prox = NULL;
    }
    else{
        soma = (celula *) malloc(sizeof(celula));
        soma->prox = (celula *) malloc(sizeof(celula));
        soma->prox->num = -1;
        soma->prox->prox = NULL;
    }
    return soma;
}

numero Mult(numero P, numero Q){
    int i = 0, j = 0, carry[30] = {0};
    numero prod, X, Y, Z, W, aux, m;
    m = (numero) malloc(sizeof(celula));
    m->prox = (numero) malloc(sizeof(celula));
    m->prox->num = 10000;
    m->prox->prox = NULL;
    if(P->prox->num != -1 && Q->prox->num != -1){
        prod = (numero) malloc(sizeof(celula));
        prod->prox = (numero) malloc(sizeof(celula));
        prod->prox->num = 0;
        prod->prox->prox = NULL;
        for (X = Q->prox; X != NULL; X = X->prox, j++){
            aux = (numero) malloc(sizeof(celula));
            for (i = 0; i < 30; i++)
                carry[i] = 0;
            i = 0;
            for (Z = aux, Y = P->prox; Y != NULL; Y = Y->prox, i++){
                Z->prox = (numero) malloc(sizeof(celula));
                Z = Z->prox;
                if (X->num == 0)
                    Z->num = carry[i];
                else if ((X->num * Y->num + carry[i]) >= 10000){
                    carry[i+1] = (X->num * Y->num + carry[i])/10000;
                    Z->num = (X->num * Y->num + carry[i])%10000;
                }
                else
                    Z->num = X->num * Y->num + carry[i];
            }
            if (carry[i] != 0){
                Z->prox = (numero) malloc(sizeof(celula));
                Z = Z->prox;
                Z->num = carry[i];
                Z->prox = NULL;
            }
            else
                Z->prox = NULL;
            for (i = 0; i < j; i++)
                aux = Mult(aux, m);
            prod = Soma(prod, aux);
            for (Z = aux; Z->prox != NULL; Z = (Z->prox != NULL) ? Z->prox : Z){
                W = Z->prox;
                Z->prox = W->prox;
                free(W);
            }
            free(Z);
        }
    }
    else{
        prod = (numero) malloc(sizeof(celula));
        prod->prox = (numero) malloc(sizeof(celula));
        prod->prox->num = -1;
        prod->prox->prox = NULL;
    }
    return prod;
}