#include <stdio.h>
#include <string.h>
#include "gravacomp.h"

struct t1
{
    char s1[15];
    int i;
    char s2[21];
}; typedef struct t1 T1;

struct t2
{
    int i;
    char s1[6];
    unsigned int u;
}; typedef struct t2 T2;

struct s{
    int i1, i2;
    char s1[4];
    unsigned int u1;
    char s2[10];
}; typedef struct s S;

struct t4
{
    int i;
    char s[4];
}; typedef struct t4 T4;



struct t5
{
    int i;
    char s[5];
};  typedef struct t5 T5;

struct t6
{
    int i;
    char s[6];
}; typedef struct t6 T6;

struct t7
{
    int i;
    char s[7];
}; typedef struct t7 T7;

struct t8
{
    int i;
    unsigned int u1, u2;
}; typedef struct t8 T8;

struct t9
{
    char s1[4], s2[5], s3[20];
}; typedef struct t9 T9;


int main(){
    // unsigned char testeSaida[] = {0x02, 0x21, 0xff, 0x43, 0x61, 0x62, 0x63, 0x82, 0x01, 0x02, 0x21, 0x01, 0x44, 0x41, 0x42, 0x43, 0x44, 0x82, 0xff, 0xff};
    
    printf("SOBA - Trab1\n");
    printf("Testes gravacomp mostra comp\n");
    
    // FILE* arqSaida = fopen("testeMostra.bin", "wb");
    // if(fwrite(testeSaida,  20, 1, arqSaida) == 0)
    //     printf("Erro ao escrever arquivo.\n");
    // fclose(arqSaida);
    
    // FILE* arqEnt = fopen("testeMostra.bin", "rb");
    // mostracomp(arqEnt);
    // fclose(arqEnt);

    // T1 n; n.i = 4; strcpy(n.s1, "teste"); strcpy(n.s2, "Teste2");
    // arqSaida = fopen("testeGrava.bin", "wb");
    // gravacomp(0x1, (void*)&n, "s06is06", arqSaida);
    // fclose(arqSaida);

    // TESTE 1
    printf("TESTE 1:\n");
    T1 teste1[4];
    teste1[0].i = -123; strcpy(teste1[0].s1, "teste1"); strcpy(teste1[0].s2, "pastel");
    teste1[1].i = -13; strcpy(teste1[1].s1, "columbia"); strcpy(teste1[1].s2, "porcada");
    teste1[2].i = 242353; strcpy(teste1[2].s1, "tony"); strcpy(teste1[2].s2, "mary");
    teste1[3].i = -232145; strcpy(teste1[3].s1, "marmelada"); strcpy(teste1[3].s2, "poste");

    FILE* arqSaida = fopen("teste1.bin", "wb");
    gravacomp(0x4, (void*)&teste1, "s15is21", arqSaida);
    fclose(arqSaida);

    FILE* arqEnt = fopen("teste1.bin", "rb");
    mostracomp(arqEnt);
    fclose(arqEnt);

    printf("\n----------------------------------------------------------------\n\n");

    // TESTE 2
    printf("TESTE 2:\n");
    T2 teste2[2];
    teste2[0].i = -1; strcpy(teste2[0].s1, "abc");  teste2[0].u = 258;
    teste2[1].i = 1;  strcpy(teste2[1].s1, "ABCD"); teste2[1].u = 65535;
    
    arqSaida = fopen("teste2.bin", "wb");
    gravacomp(0x2, (void*)&teste2, "is06u", arqSaida);
    fclose(arqSaida);

    arqEnt = fopen("teste2.bin", "rb");
    mostracomp(arqEnt);
    fclose(arqEnt);

    printf("\n----------------------------------------------------------------\n\n");

    // TESTE 3
    printf("TESTE 3:\n");
    S teste3; teste3.i1 = 0x00834500; teste3.i2 = -0x00834500; teste3.u1 = 0x00834500;
    strcpy(teste3.s1, "MA"); strcpy(teste3.s2, "mary tony");

    arqSaida = fopen("teste3.bin", "wb");
    gravacomp(0x1, (void*)&teste3, "iis03us10", arqSaida);
    fclose(arqSaida);

    arqEnt = fopen("teste3.bin", "rb");
    mostracomp(arqEnt);
    fclose(arqEnt);

    printf("\n----------------------------------------------------------------\n\n");

    // TESTE 4
    printf("TESTE 4:\n");
    T4 vt4[2];
    vt4[0].i = -12313; strcpy(vt4[0].s, "123");
    vt4[1].i = 2353; strcpy(vt4[1].s, "333");

    arqSaida = fopen("teste4.bin", "wb");
    gravacomp(0x2, (void*)&vt4, "is04", arqSaida);
    fclose(arqSaida);

    arqEnt = fopen("teste4.bin", "rb");
    mostracomp(arqEnt);
    fclose(arqEnt);

    printf("\n----------------------------------------------------------------\n\n");

    // TESTE 5
    printf("TESTE 5:\n");
    T5 vt5[2];
    vt5[0].i = 12; strcpy(vt5[0].s, "amor");
    vt5[1].i = 24; strcpy(vt5[1].s, "gaga");

    arqSaida = fopen("teste5.bin", "wb");
    gravacomp(0x2, (void*)&vt5, "is05", arqSaida);
    fclose(arqSaida);

    arqEnt = fopen("teste5.bin", "rb");
    mostracomp(arqEnt);
    fclose(arqEnt);

    printf("\n----------------------------------------------------------------\n\n");

    // TESTE 6
    printf("TESTE 6:\n");
    T6 vt6[2];
    vt6[0].i = 777; strcpy(vt6[0].s, "maryt");
    vt6[1].i = 333; strcpy(vt6[1].s, "onys");

    arqSaida = fopen("teste6.bin", "wb");
    gravacomp(0x2, (void*)&vt6, "is06", arqSaida);
    fclose(arqSaida);

    arqEnt = fopen("teste6.bin", "rb");
    mostracomp(arqEnt);
    fclose(arqEnt);

    printf("\n----------------------------------------------------------------\n\n");

    // TESTE 7
    printf("TESTE 7:\n");
    T7 vt7[2];
    vt7[0].i = 0x32; strcpy(vt7[0].s, "kkkkkk");
    vt7[1].i = 0x99; strcpy(vt7[1].s, "bomdia");

    arqSaida = fopen("teste7.bin", "wb");
    gravacomp(0x2, (void*)&vt7, "is07", arqSaida);
    fclose(arqSaida);

    arqEnt = fopen("teste7.bin", "rb");
    mostracomp(arqEnt);
    fclose(arqEnt);

    printf("\n----------------------------------------------------------------\n\n");

    // TESTE 8
    printf("TESTE 8:\n");
    T8 vt8[2];
    vt8[0].i = -12313; vt8[0].u1 = 12313; vt8[0].u2 = 0x12312312;
    vt8[1].i = 2353; vt8[1].u1 = 0xffffffff; vt8[1].u2 = 0;

    arqSaida = fopen("teste8.bin", "wb");
    gravacomp(0x2, (void*)&vt8, "iuu", arqSaida);
    fclose(arqSaida);

    arqEnt = fopen("teste8.bin", "rb");
    mostracomp(arqEnt);
    fclose(arqEnt);

    
    printf("\n----------------------------------------------------------------\n\n");

    // TESTE 9
    printf("TESTE 9:\n");
    T9 vt9[2];
    strcpy(vt9[0].s1, "rrr"); strcpy(vt9[0].s2, "mary"); strcpy(vt9[0].s3, "humberto");
    strcpy(vt9[1].s1, "bbb"); strcpy(vt9[1].s2, "tony"); strcpy(vt9[1].s3, "avenida");

    arqSaida = fopen("teste9.bin", "wb");
    gravacomp(0x2, (void*)&vt9, "s04s05s20", arqSaida);
    fclose(arqSaida);

    arqEnt = fopen("teste9.bin", "rb");
    mostracomp(arqEnt);
    fclose(arqEnt);  

    return 0;
}

/*
COMANDO PARA COMPILAR
gcc -Wall -o teste gravacomp.c teste.c
*/