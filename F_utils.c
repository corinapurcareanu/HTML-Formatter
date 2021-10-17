/*Purcareanu Corina
311CB*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "lib.h"
   

/*functie pentru creat un nod dintr-un arbore*/
TArb CreateNode(){
	TArb aux = (TArb)calloc(1,sizeof(TNodArb));
	aux->nextSibling = NULL;
	aux->firstChild = NULL;
	aux->info = (TInfo)calloc(1,sizeof(TNodInfo));
	aux->info->type = (char*)calloc(20,sizeof(char));;
	aux->info->id = NULL;
	aux->info->style = NULL;
	aux->info->otherAttributes = NULL;
	aux->info->isSelfClosing = 0;
	aux->info->contents = (char*)calloc(100,sizeof(char));
	return aux;
}

/*functie pentru creat un atribut al unui nod*/
TAttr createAttrNode(char *n, char *v){
	TAttr aux = (TAttr)calloc(1,sizeof(TNodAttr));
	if(aux){
		aux->name = (char*)calloc(30,sizeof(char));
		strcpy(aux->name, n);
		aux->value = (char*)calloc(100,sizeof(char));
		strcpy(aux->value, v);
		aux->next = NULL;
	}
	return aux;
}

/*functie pentru creat lista style a unui nod*/
void createStyleList(char *v, TArb node){
    char *aux_v = (char*)calloc(1000,sizeof(char));
    strcpy(aux_v, v);
	char *attr = strtok(aux_v, ";");
	int i,j, k = 0;
	char **array = calloc(100,sizeof(char*));
    for(i = 0; i < 100; i++){
    	array[i] = calloc(100,sizeof(char));
  	}
    /*se memoreaza atributele intr-un vector de string-uri*/
	while(attr){
		strcpy(array[k], attr);
        k++;
		attr = strtok(NULL, ";");
	}
    /*fiecare atribut este impartit in nume si valoare*/
	for(i = 0; i < k; i++){
        char *x = (char*)calloc(100,sizeof(char));
        strcpy(x, array[i]);
		char *a = strtok(x, " :");
		char *b = strtok(NULL, ":;");
        char *name = (char*)calloc(30,sizeof(char));
        char *value = (char*)calloc(100,sizeof(char));
        strcpy(name, a);
        for(j = 0; j < strlen(b); j++){
            if(!isspace(b[j])){
                strncat(value, &b[j], 1);
            }
        }
        /*daca lista style a atributului este nula, se creeaza lista*/
		if(node->info->style == NULL){
			node->info->style = (TAttr)calloc(1,sizeof(TNodAttr));
			node->info->style->name = (char*)calloc(30,sizeof(char));
			strcpy(node->info->style->name, name);
			node->info->style->value = (char*)calloc(100,sizeof(char));
			strcpy(node->info->style->value, value);
		}
        /*altfel se adauga atributul la finalul listei*/
		else{
			TAttr aux, last;
			for(aux = node->info->style, last = NULL; aux != NULL; last = aux, aux = aux->next);
			last->next = (TAttr)calloc(1,sizeof(TNodAttr));
			last->next->name = (char*)calloc(30,sizeof(char));
			strcpy(last->next->name, name);
			last->next->value = (char*)calloc(100,sizeof(char));
			strcpy(last->next->value, value);
		}
        free(x);
        free(name);
        free(value);
	}
    for(i = 0; i < 100; i++){
        free(array[i]);
    }
    free(array);
    free(aux_v);
}

/*functie pentru distrus o lista de atribute*/
void DestroyAttr(TAttr *list){
    while(*list != NULL){
        TAttr aux = *list;     
        if (!aux)
            return;
        free(aux->name); 
        free(aux->value);
        *list = aux->next;   
        free(aux);   
    }
}

/*functie pentru sters un nod dintr-un arbore*/
void DestroyNode(TArb *node){
    if((*node)->info->type != NULL) free((*node)->info->type);
    if((*node)->info->id != NULL) free((*node)->info->id);
    if((*node)->info->contents != NULL) free((*node)->info->contents);
    if((*node)->info->style != NULL) DestroyAttr(&(*node)->info->style);
    if((*node)->info->otherAttributes != NULL) DestroyAttr(&((*node)->info)->otherAttributes);
    free((*node)->info);
    free(*node);
}

/*functie pentru distrus arborele*/
void Delete(TArb *node){
	if((*node)){
		if((*node)->nextSibling){
			Delete(&(*node)->nextSibling);
		}
		if((*node)->firstChild){
			Delete(&(*node)->firstChild);
		}
		if((*node)->info->type != NULL) free((*node)->info->type);
		if((*node)->info->id != NULL) free((*node)->info->id);
		if((*node)->info->contents != NULL) free((*node)->info->contents);
		if((*node)->info->style != NULL) DestroyAttr(&((*node)->info)->style);
		if((*node)->info->otherAttributes != NULL) DestroyAttr(&((*node)->info)->otherAttributes);
		free((*node)->info);
		free(*node);
	}
    *node = NULL;
} 


/*functie pentru initializat o stiva goala*/
TStiva InitS() {
    TStiva new = (TStiva)malloc(sizeof(TElem));
    if (!new) return NULL;
    *new = NULL;

    return new;
}

/*functie de adaugat elemtul x in varful stivei */
void Push(TStiva s, void *x) {
    TElem new = (TElem)malloc(sizeof(TCelula));
    if (!new) return; 
    new->info = x;
    new->urm = NULL;

    if(Vida(s)) {
        *s = new;
        return;
    }

    new->urm = *s;
    *s = new;
}

/*functie de scos un element din varful stivei*/
void *Pop(TStiva s) {
    if(Vida(s))
        return NULL;
    
    void *result = (*s)->info;
    TElem aux = *s;
    *s = (*s)->urm;
    free(aux);

    return result;
}

/*functie de sters stiva*/
void DistrS(TStiva s) {
    while (!Vida(s))
        free(Pop(s));

    free(s);
    s = NULL;
}
/*functie pentru initializat o coada goala*/
TCoada InitQ() {
    TCoada new = (TCoada)malloc(sizeof(TElem));
    if (!new) return NULL;
    *new = NULL;

    return new;
}

/*functie de adaugat elemtul x la sfarsitul cozii */
void Enqueue(TCoada q, void* x) {
    TElem new = (TElem)malloc(sizeof(TCelula));
    if (!new) return;
    new->info = x;
    new->urm = NULL;

    if(Vida(q)) {
        *q = new;
        return;
    }

    TElem aux = *q;

    while(aux->urm != NULL)
        aux = aux->urm;

    aux->urm = new;
}

/* functie de scos un element din varful cozii*/
void *Dequeue(TCoada q) {
    if(Vida(q))
        return NULL;
    
    void *result = (*q)->info;
    TElem aux = *q;
    *q = (*q)->urm;
    free(aux);

    return result;
}

/*functie de sters coada*/
void DistrQ(TCoada q) {
    while (!Vida(q)){
       free(Dequeue(q));
    }

    free(q);
    q = NULL;
}