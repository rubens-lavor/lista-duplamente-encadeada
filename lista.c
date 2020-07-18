#include<stdio.h>
#include<stdlib.h>

#include "lista_privado.h"


typedef struct lista{
	
	celula_t *cabeca;
	celula_t *cauda;  
	int tamanho;
	void (*destruir)(void *);
	void (*imprime)(const void *); 
	int (*compara)(const void *, const void *);
	}lista_t;


typedef struct celula{	

	void *dado; 
	struct celula *prox; 
	struct celula *ant;
	}celula_t;
	

    
    
    
/*
 * Cria uma lista e a inicializa como lista vazia. 
 * "imp" eh um ponteiro para uma funcao de impressao dos dados armazenados dentro da lista. Deve ser usado em "lista_imprime". 
 * o argumento "libera" prove uma maneira de liberar dinamicamente os dados dentro da celula quando "lista_destroi" eh chamada. 
 * Para uma lista onde os dados nao devem ser liberados, libera deve ser NULL 
 * "comparar" eh um ponteiro para funcao de comparacao entre dois dados armazenados na lista. 
 * Deve retornar -1 se o primeiro eh menor que o segundo, 0 se forem iguais, ou 1 se o primeiro for maior que o segundo   
 * Pre: nenhuma
 * Pos: Retorna um ponteiro para uma lista vazia se houver memaria disponivel
 */
lista_t *lista_cria(void (*imp)(const void *), void (*libera)(void *), int (*comparar)(const void *, const void *)){
    
    
    lista_t *l=(lista_t*) malloc(sizeof(lista_t));
    
    if(l != NULL){
    l->cabeca=NULL;
    l->cauda=NULL;
    l->destruir=libera;
    l->compara=comparar;
    l->imprime=imp;
    l->tamanho=0;
    
    return l;
        
    }
    
    return NULL;
    
    //lista_t *l=(lista_t*) malloc(sizeof(lista_t));
    
    //if(l != NULL)
    //    *l = NULL; //o endere�o para onde l aponta recebe NULL
    //return l; // retorna o endere�o q o ponteiro quarda.
    
    
    
}



/*
 * Destroi a lista especificada em "l". Nenhuma operacao eh permitida apos a funcao, a nao ser que lista cria seja chamada novamente. 
 * Destroi todos os elementos armazenados na lista se o ponteiro "destruir" for valido
 * Pre: "l" deve ser uma lista valida criada previamente atraves da funcao lista cria
 * Pos: os recursos da lista foram liberados com sucesso e a lista "l" torna-se nula
 */
void lista_destroi(lista_t **l){
    if(l == NULL || *l == NULL) return; //veriifica se a lista n�o existe
    
    void *removido;
    
    while((*l)->tamanho != 0){
        lista_remove((*l),(*l)->cabeca,&removido);
        if((*l)->destruir != NULL){
            (*l)->destruir(removido);
        }
    }
    free(*l);
    *l = NULL;
    
    
    
    if(l != NULL){
        celula_t *no;
        while((*l) != NULL){
            no = *l;
            *l = (*l->prox;)
        }
        free(l);
        
    }
    
}

/*
 * Retorna 1 se a lista estiver vazia, 0 caso contrario
 * Pre: a lista deve existir
 * Pos: retorna 1 caso a lista estiver vazia, 0 se nao estiver. Retorna -1 caso a lista nao existir
 */
int lista_vazia(lista_t *l){
	if(l==NULL){
	return -1;}
	
	if(l->tamanho==0){
	return 1;}
	
	else{
		return 0;}
}



/*
 * Retorna o tamanho da lista
 * Pre: a lista deve existir
 * Pos: retorna o tamanho da lista. Retorna -1 caso a lista nao existir
 */
int lista_tamanho(lista_t *l){
	
	if(l==NULL){
	return -1;}
	
	return l->tamanho;

}



/*
 * Retorna a celula cabeca da lista
 * Pre: a lista deve existir
 * Pos: retorna a celula cabeca da lista. Retorna NULL caso a lista estiver vazia ou nao existir
 */
celula_t *lista_cabeca(lista_t *l){
	if(l==NULL){
	return NULL;
	}
	
	return l->cabe�a;


}

/*
 * Retorna a celula cauda da lista
 * Pre: a lista deve existir
 * Pos: retorna a celula cauda da lista. Retorna NULL caso a lista estiver vazia ou nao existir
 */
celula_t *lista_cauda(lista_t *l){
	if(l==NULL){
	return NULL;
	}
	
	return l->cauda;

}



/*
 * Retorna o dado armazenado dentro da celula "c".
 * Pre: a celula deve existir
 * Pos: retorna o dado armazenado dentro de "c" ou NULL caso "c" for invalido
 */
void *lista_dado(celula_t *c){
	if(c==NULL){
	return NULL;
	}
	
	return c->dado; 
}



/*
 * Retorna a celula que esta imediamente apos a celula recebida como parametro.
 * Pre: a celula deve existir
 * Pos: retorna a celula apos "c" ou NULL caso "c" for invalido
 */
 
celula_t *lista_proximo(celula_t *c){	

	if(c==NULL){
	return NULL;
	}
	
	return c->prox; 
	
}


/*
 * Retorna a celula que esta imediamente antes a celula recebida como parametro.
 * Pre: a celula deve existir
 * Pos: retorna a celula que esta antes de "c" ou NULL caso "c" for invalido
 */
celula_t *lista_anterior(celula_t *c){
	if(c==NULL){
	return NULL;
	}
	
	return c->ant;
}


int lista_eh_cabeca(lista_t *l, celula_t *c){

    if(l == NULL || c == NULL || l->tamanho == 0) return -1;
    
    if(c == l->cabeca) return 1;
    else return 0;
    
}


int lista_eh_cauda(lista_t *l, celula_t *c){
    
    if(l == NULL || c == NULL || l->tamanho == 0) return -1;
    
    if(c == l->cauda) return 1;
    else return 0;
}




/*
 * Insere um elemento na lista imeadiamente apos um elemento determinado e recebido como parametro da funcao (celula "c").
 * Caso esse parametro seja invalido, insere o novo elemento na cabeca da lista. 
 * Retorna 1 caso conseguir inserir, 0 caso contrario
 * Pre: A lista e o novo elemento a ser inserido devem ser validos
 * Pos: O elemento recebido como parametro eh inserido logo apos a celula "c" ou na cabeca da lista
 */
int lista_insere_proximo(lista_t *l, celula_t *c, const void *elem){

	if(l==NULL || elem == NULL){
	return 0;
	}
	
	celula_t *novo_no = (celula_t*) malloc(sizeof(celula_t));
	if(novo_no==NULL){
	return 0;
	}
	
	novo_no->dado=(void*)elem;
    
    
    
    if(c == NULL){ //Caso esse parametro seja invalido, insere o novo elemento na cabeca da lista.
        if(l->tamanho == 0){ //se estava vazia
            l->cabeca = novo;
            l->cauda = novo;
            novo->ant = NULL;
            novo->prox = NULL;
        }else{ //se nao vazia
            novo->ant = NULL;
            novo->prox = l->cabeca;
            l->cabeca->ant = novo;
            l->cabeca = novo;
        }
    }else{ //Insere um elemento na lista imeadiamente apos um elemento determinado e recebido como parametro da funcao (celula "c").
        if(l->tamanho == 0){ //se estava vazia
            l->cabeca = novo;
            l->cauda = novo;
            novo->ant = NULL;
            novo->prox = NULL;
        }else if (lista_eh_cauda(l,c)){
            novo->ant = c;
            novo->prox = NULL;
            c->prox = novo;
            l->cauda = novo;
        }else{	 	  	 	      	      	   	     	  	     	  	 	
            novo->ant = c;
            novo->prox = c->prox;
            c->prox = novo;
            novo->prox->ant = novo;   
        }
    }
    l->tamanho++;
    return 1;

}


int lista_insere_anterior(lista_t *l, celula_t *c, const void *elem){
    
    if(l == NULL || elem == NULL) return 0;
    
    if(c == NULL){ //Caso esse parametro seja invalido, insere o novo elemento na cabeca da lista.
        lista_insere_proximo(l,NULL,elem);
    }else{ //Insere um elemento na lista imediatamente ANTES de um elemento determinado e recebido como parametro da funcao (celula "c").
        if(l->tamanho == 0){ //se estava vazia
            lista_insere_proximo(l,NULL,elem);
        }else{
            if(lista_eh_cabeca(l,c)){//insere na cabeca se C eh cabeca
                lista_insere_proximo(l,NULL,elem);
            }else{//insere no proximo do anterior
                lista_insere_proximo(l,c->ant,elem);
            }
        }
    }

    return 1;
    
    
}


int lista_insere_posicao(lista_t *l, const unsigned int posicao, const void *elem){
    
     if(l == NULL || elem == NULL || posicao < 0) return 0;
    //Caso "posicao" seja maior que o tamanho da lista, insere o elemento na cauda da lista.
    if(posicao >= l->tamanho){
        lista_insere_proximo(l,l->cauda,elem); //insere elem apos cauda
    }else if(l->tamanho == 0){	 	  	 	      	      	   	     	  	     	  	 	
      lista_insere_proximo(l, NULL, elem);
    }else{ //Insere um elemento na lista na posicao especificada por "posicao"
        if (posicao == 0) {
            lista_insere_proximo(l,NULL,elem);
            return 1;
        }
        celula_t *extra = l->cabeca;
        for(int i = 0; i < posicao; i++){
            extra = extra->prox;
        }
        lista_insere_proximo(l,extra,elem);
    }
    return 1;
}



/* 
 * Remove o elemento conhecido e recebido como parametro. Retorna o conteudo do elemento removido em uma variavel recebida como parametro. 
 * Retorna 1 caso conseguir remover, 0 caso contrario.
 * Pre: a lista deve existir e nao deve estar vazia, a celula a ser removida e a variavel recebida para armazenar o conteudo removido devem ser validas
 * Pos: a lista tera um elemento a menos e seu conteudo sera retornado dentro de uma variavel recebida como parametro
 * Retorna 1 caso conseguir remover, 0 caso contrario
 */
int lista_remove(lista_t *l, celula_t *c, void **elem){
    
     if(l == NULL || elem == NULL || l->tamanho <= 0) return 0;
    
    *elem = c->dado; //passa o dado para elem
    //4 CASOS
    //CASO 1 - C esta na cabeca
    if(l->tamanho == 1){//CASO 3 lista com 1 elem apenas
        l->cabeca = NULL;
        l->cauda = NULL;
    }else{
    
        if(c == l->cabeca){
            l->cabeca = c->prox;
            l->cabeca->ant = NULL;
        }else if(c == l->cauda){//CASO 2 - C esta na cauda
            l->cauda =  l->cauda->ant;
            l->cauda->prox = NULL;
        }else{//CASO 4 - C no meio da lista
            c->ant->prox = c->prox;
            c->prox->ant = c->ant;
        }
        }
    
    free(c); //destroi a celula
    l->tamanho--;
    return 1;//op sucedida
} 

void lista_imprime(lista_t *l){
    
     if (l==NULL || l->imprime == NULL) return;

    for(celula_t *cont = l->cabeca; cont != NULL; cont=cont->prox){
        l->imprime(cont->dado);
    }
    
}

int lista_insere_ordenado(lista_t *l, const void *elem){
    
    if(l == NULL || elem == NULL) return 0;
    
    if(l->tamanho == 0){
        lista_insere_proximo(l,NULL,elem);
        return 1;
    }
    
    if(l->compara == NULL){//Caso o ponteiro de funcao "compara" for NULL, a insercao de "elem" deve ser feita na cauda da lista.
        lista_insere_proximo(l,l->cauda,elem);
        return 1;
    }else{
        
        for(celula_t *aux = l->cabeca; aux != NULL; aux = aux->prox){
            if((l)->compara(aux->dado,elem) == 0){
                lista_insere_proximo(l,aux,elem);
                return 1;
            }else if((l)->compara(aux->dado,elem) == 1){
                lista_insere_anterior(l,aux,elem);
                return 1;
            }	 	  	 	      	      	   	     	  	     	  	 	
        }
        lista_insere_proximo(l,l->cauda,elem);
        return 1;
    }
}


celula_t *lista_busca_recursiva(lista_t *l, const void *elem, celula_t *c){
    
    if(l == NULL || elem == NULL || c == NULL || l->tamanho <= 0) return NULL;
    //C e a condicao de parada, logo ao evocar a recursiva para percorrer toda a lista PASSAMOS l->cabeca
    //condicao de parada ja posta acima com C == NULL return NULL
    if(c->dado == elem){
        return c;
    }else{
        lista_busca_recursiva(l,elem,c->prox);
    }
}


lista_t *lista_separa(lista_t *l, const void *elem){
    
     if(l == NULL || elem == NULL) return 0;
    
    int TAM1=l->tamanho, TAM2=0;
    
    celula_t *novo = lista_busca_recursiva(l,elem,l->cabeca); //obtemos a celula que sera a ultima da primeira divisao
    
    lista_t *lista_2 = lista_cria(l->imprime,l->destruir,l->compara);
    
    novo->prox->ant = NULL; //primeiro da segunda divisao tem o anterior apontando p NULL
    lista_2->cabeca = novo->prox; //cabeca da lista2 com & da primeira celula da segunda divisao
    lista_2->cauda = l->cauda; //lista2 recebe cauda de lista1
    l->cauda = novo; //cauda de lista1 atualizada
    l->cauda->prox = NULL; //nulo na cauda
    
    //fazendo TAM 2
    for(celula_t *cont = lista_2->cabeca; cont != NULL; cont = cont->prox){
        TAM2++;
    }	 	  	 	      	      	   	     	  	     	  	 	
    //atualizar tamanhos
    l->tamanho = l->tamanho - TAM2;
    lista_2->tamanho = TAM2;
    
    //atualizar tamanho das duas listas, ponteiros;
    return lista_2;
}


lista_t *lista_concatena_e_destroi(lista_t **l1, lista_t **l2){
    
     if(l1 == NULL || l2 == NULL || *l1 == NULL || *l1 == NULL || ((*l1)->tamanho == 0 && (*l2)->tamanho == 0)) return NULL;
    
    lista_t *lista_nova;
    if((*l1)->tamanho > 0){ //A nova lista deve ter os mesmos ponteiros internos (imprime, compara e destruir) da lista "l1" ou da lista "l2" se a "l1" for vazia
        lista_nova = lista_cria((*l1)->imprime,(*l1)->destruir,(*l1)->compara);
    }else{
        lista_nova = lista_cria((*l2)->imprime,(*l2)->destruir,(*l2)->compara);
    }
    
    int TAM = (*l1)->tamanho + (*l2)->tamanho; //Tamanho novo
    if ((*l1)->tamanho == 0){
        lista_nova->tamanho=TAM;
        lista_nova->cabeca=(*l2)->cabeca;
        lista_nova->cauda=(*l2)->cauda;
    }else if ((*l2)->tamanho == 0){
        lista_nova->tamanho=TAM;
        lista_nova->cabeca=(*l1)->cabeca;
        lista_nova->cauda=(*l1)->cauda;
    }else if ((*l1)->tamanho > 0 && (*l2)->tamanho > 0){
        lista_nova->tamanho=TAM;
        lista_nova->cabeca=(*l1)->cabeca;
        lista_nova->cauda=(*l2)->cauda;
        (*l1)->cauda->prox=(*l2)->cabeca;
        (*l2)->cabeca->ant=(*l1)->cauda;
    }
    (*l1)->cabeca = NULL; (*l1)->cauda = NULL; (*l1)->tamanho = 0;
    (*l2)->cabeca = NULL; (*l2)->cauda = NULL; (*l2)->tamanho = 0;
    
    lista_destroi(l1); lista_destroi(l2);
    
    return lista_nova;
}





