#include "fila_sp.h"

fila_sp* (criar_fila_sp)(){
    fila_sp* f;
    f = (fila_sp*) malloc(sizeof(fila_sp));

    if(f == NULL){
        return NULL;
    }

    f->capacidade = MAX_SIZE;
    f->tamanho = 0;
    f->inicio = 0;

    f->fim = MAX_SIZE - 1;
    f->valores = (int*) malloc(f->capacidade * sizeof(int));

    return f;

}

int (inserir_fila_sp)(fila_sp* f, int rbr, uint8_t status){
    int i = !(status & INSERT_QUEUE);  //data está disponível

    if(i){
        colocar_fila_sp(f, rbr);
        return 0;
    }

    return 1;
}


void (limpar_fila_sp)(fila_sp* f){
    free(f->valores);
}

int (pop_fila_sp)(fila_sp* f){
    if(f->tamanho == 0){
        return 0;
    }
    int res = f->valores[f->inicio];
    f->inicio = (f->inicio + 1) % f->capacidade;        //circular buffer effect
    f->tamanho = f->tamanho - 1;
    
    return res;
}

