/*Guilherme Melo Gratz 2211068 3WA*/

#include "gravacomp.h"
#include <string.h>

// extende o sinal de um inteiro int a partir do bit mais significativo 
// considera que este int é representado pelos tam primeiros bytes
int extendeSinal(int i, unsigned char tam){
    unsigned char *p = (unsigned char*)&i;
    
    for(unsigned char j = tam - 1; j--; p++){}
    if((*p&0x80) == 0x80)
        for(p++; 4 - tam++;p++)
            *p = 0xff;

    return i;
}

// inverte os tam primeiros bytes do tipo inteiro (seja int ou unsigned int)
int inverteByte(int i, unsigned char tam){
    unsigned char *p = (unsigned char*)&i;    
    
    // para não adicionar stdlib.h, aux foi criado com o maior tamanho possível
    unsigned char aux[4] = {0,0,0,0}; 

    for(unsigned char j = 0; j < tam; j++, p++)
        aux[tam-j-1] = *p;
    
    p = (unsigned char*)&i;
    for(unsigned char j = 0; j < tam; j++, p++)
        *p = aux[j];
    
    return i;
}

// retorna a quantidade de bytes necessários para representar o valor `n`
// parametro char tipo pode ser 'u' ou 'i' (unsigned int ou int)
unsigned char bytesNecessarios(unsigned int n, char tipo){
    // caso unsigned
    if(tipo == 'u'){
        for(int i = 0; i < 32; i++, n<<=1){
            if(0x80000000 & n){
                return (unsigned char)(4 - i/8);
            }
        }

        // caso: numero = 0x00
        return 1;
    }

    // caso signed int
    else if(tipo == 'i'){
        // caso: negativo
        if(0x80000000 & n){
            for(int i = 0; i < 32; i++, n<<=1){
                if(!(0x80000000 & n)){
                    return (unsigned char)(4 - (i-1)/8);
                }
            }

            // caso: numero = -1
            return 1;
        } 

        // caso: positivo
        else{
            for(int i = 0; i < 32; i++, n<<=1){
                if(0x80000000 & n){
                    // como é inteiro, 1 bit a mais deve ser contado
                    return (unsigned char)(4 - (i-1)/8);
                }
            }

            // caso: numero = 0x00
            return 1;
        }
    }


    return 1;
}

// recebe uma string começando no caractere que representa o elemento cujo cabeçalho será criado
// recebe um ponteiro para o valor atual
// retorna o byte cabecalho
unsigned char criaCabecalho(char* campo, void* valor){
    unsigned char cabecalho = 0;
    
    // caso: string
    if(campo[0] == 's'){
        // bit 6 tipo string
        cabecalho += 0x40;

        // caso: último campo da estrutura
        if(campo[3] == '\0'){
            cabecalho += 0x80;
        }
        
        unsigned char tamS = strlen((char*)valor);
        
        // escreve tam nos bytes 4-0
        cabecalho += tamS & 0x3f;
    }
    
    // caso: int ou u int
    else{
        // caso: último campo da estrutura 
        if(campo[1] == '\0'){
            cabecalho += 0x80;
        }
    
        // caso: unsigned int
        if(campo[0] == 'u'){
            // não adiciona nada ao campo 'tipo' do cabeçalho pois é 00
            
            unsigned int *p = (unsigned int*)valor;
            unsigned char tamU = bytesNecessarios(*p, 'u');

            // escreve o tamanho nos bytes 5-0
            cabecalho += tamU & 0x1f;
        }

        // caso: int
        if(campo[0] == 'i'){
            // escreve o tipo
            cabecalho += 0x20;

            int *p = (int*)valor;
            unsigned char tamI = bytesNecessarios(*p, 'i');

            // escreve tam nos bytes 5-0
            cabecalho += tamI & 0x1f;
        }
    }
    
    return cabecalho;
}

// retorna 1 se existe int ou u int no struct
//         0 caso contrário
int temInteiro(char* campos){
    for(int tam = strlen(campos); tam--; campos++)
        if(*campos == 'i' || *campos == 'u')
            return 1;
    
    return 0;
}

// retorna 1 se existe string no struct
//         0 caso contrário
int temString(char* campos){
    for(int tam = strlen(campos); tam--; campos++)
        if(*campos == 's')
            return 1;
    
    return 0;
}

// calcula o tamanho do padding para o elemento desejado no meio de uma struct
unsigned char paddingMeio(char* campo, void* valor){
    
    // caso: valor atual é string
    if(campo[0] !='\0' && campo[0] == 's' && campo[3] != '\0'){
        // caso próximo elemento for string, não precisará de padding
        if(campo[3] == 's')
            return 0;
        
        // p começa no endereço logo após o último elemento da string
        unsigned char tamS = (((unsigned char)campo[1]) - (unsigned char)0x30)*10 + (((unsigned char)campo[2]) - (unsigned char)0x30);
        unsigned char *p = (unsigned char*)((unsigned long)valor + (unsigned long)tamS);
        
        // calcula efetivamente padding
        int i;
        for(i = 0; (int)(((unsigned long)p)%4) != 0; i++, p++){}
        return i;
    } 

    // caso o valor atual seja int ou u. int padding será sempre 0
    return 0;
}

// calcula padding no fim da struct
unsigned char paddingFim(char* campos, void* valores){
    int tam = strlen(campos);
    
    // caso não haja inteiros, não há padding entre elementos do array
    if(!temInteiro(campos))
        return 0;

    // caso não haja strings, todos inteiros estão automaticamente alinhados
    if(!temString(campos))
        return 0;

    if(campos[tam-3] == 's'){

        // percorre a memória até o fim da struct
        unsigned char* p = (unsigned char*)valores;
        for(; campos[0] != '\0'; campos++){
            if(campos[0] == 'i' || campos[0] == 'u'){
                p += 4;
            }

            else {
                // conversão de tamanho em caractere para numero de fato
                unsigned int tamS = (((unsigned char)campos[1]) - (unsigned char)0x30)*10 + (((unsigned char)campos[2]) - (unsigned char)0x30);
                // atenção: adicionar padding
                p += tamS + (unsigned int)paddingMeio(campos, p);

                campos += 2;
            }
        }

        int i;
        for(i = 0; (int)(((unsigned long)p)%4) != 0; i++, p++){}
        return i;
    }


    // caso último elem seja int ou u int, padding é 0 
    return 0;
}

int gravacomp (int nstructs, void* valores, char* campos, FILE* arquivo){
    
    // qtd de structs no primeiro byte do arq
    unsigned char qtdStructs = (unsigned char)nstructs;
    if(!fwrite(&qtdStructs, 1, 1, arquivo))
        return -1;
    
    unsigned char* p = (unsigned char*)valores;
    for(int j = 0; j < nstructs; j++){
        int ppFim = paddingFim(campos, p);
        for(char* c = campos; c[0] != '\0'; c++){        
            // cabecalho do elemento atual
            unsigned char cabecalho = criaCabecalho(c, p);
            if(!fwrite(&cabecalho, 1, 1, arquivo))
                return -1;

            // caso: int
            if(c[0] == 'i'){
                int i = *((int*)p);
                unsigned char t = bytesNecessarios((unsigned int)i, c[0]);
                // converte para big endian os bytes necessários
                i = inverteByte(i, t);
                
                unsigned char* p1 = (unsigned char*)&i;
                // escreve em big endian (bytes invertidos) apenas bytes necessários
                for(unsigned char k = t; k--; p1++){
                    if(!fwrite(p1, 1, 1, arquivo))
                        return -1;
                }

                p += 4;
            }

            // caso é unsigned int
            else if(c[0] == 'u'){
                unsigned int i = *((unsigned int*)p);
                unsigned char t = bytesNecessarios((unsigned int)i, c[0]);
                // converte para big endian os bytes necessários
                i = inverteByte(i, t);
                
                unsigned char* p1 = (unsigned char*)&i;
                // escreve em big endian (bytes invertidos) apenas bytes necessários
                for(unsigned char k = t; k--; p1++){
                    if(!fwrite(p1, 1, 1, arquivo))
                        return -1;
                }

                p += 4;
            }

            // caso é string
            else {
                unsigned int tamS = (((unsigned char)c[1]) - (unsigned char)0x30)*10 + (((unsigned char)c[2]) - (unsigned char)0x30);

                // escreve string
                char* p1 = (char*)p;
                for(int k = (int)strlen((char*)p); k--; p1++){
                    if(!fwrite(p1, 1, 1, arquivo))
                        return -1;
                }

                p += tamS + (unsigned int)paddingMeio(c, p);

                c += 2;
            }
        }
        
        // adiciona padding final
        p += ppFim;
    }
    
    return 0;
}


void mostracomp (FILE* arquivo){
    unsigned char qtd, cabecalho, tam;
    char c;
    int i;
    unsigned int ui;

    // leitura da qtd de estruturas
    fread(&qtd, 1, 1, arquivo);
    printf("Estruturas: %d\n", qtd);
    
    // ler cada struct
    for(unsigned char j = 0; j < qtd; j++){
        printf("\n");
        do
        {
            fread(&cabecalho, 1, 1, arquivo);

            // caso: dado atual é uma string
            if((cabecalho & 0x40) == 0x40){
                printf("(str) ");

                // imprime caractere por caractere 
                tam = (cabecalho & 0x3f);
                for(unsigned char i = 0; i < tam; i++){
                    fread(&c, 1, 1, arquivo);
                    printf("%c", c);
                }

                printf("\n");
            }

            // caso: dado atual é int
            else if((cabecalho & 0x20) == 0x20){
                printf("(int) ");
                
                tam = cabecalho & 0x1f; // = qtd de bytes que representam este int
                
                i = 0;
                fread(&i, 1, tam, arquivo);

                // como minha máquina é little endian e o int é salvo no arquivo como big endian, 
                // é necessário inverter os bytes
                i = inverteByte(i, tam);
                // como o inteiro pode ser salvo em menos de 4 bytes, 
                // o sinal tem que ser extendido para os outros bytes que não foram salvos no arquivo
                i = extendeSinal(i, tam);
                
                printf("%d (%08x)", i, i);

                printf("\n");
            }

            // caso: dado atual é unsigned int
            else if((cabecalho & 0x20) == 0){
                printf("(uns) ");

                tam = cabecalho & 0x1f; // = qtd de bytes que representam este unsigned int

                ui = 0;
                fread(&ui, 1, tam, arquivo);
                // como minha máquina é little endian e os dados são salvos em big endian,
                // temos que inverter os bytes (APENAS OS SALVOS NO ARQUIVO!)
                ui = inverteByte(ui, tam);

                printf("%u (%08x)", ui, ui);

                printf("\n");

            }
        } while ((cabecalho & 0x80) != 0x80); // enquanto não chegamos ao último elemento do struct
        
    }
}