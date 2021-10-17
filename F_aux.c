/*Purcareanu Corina
311CB*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "lib.h"

/*functie de Override in functie de ID*/
void OverrideById(TArb tree, char *id, char *style, FILE *f){
	TArb root = tree;
	TArb p;
	int i = 0;
	TCoada q = InitQ();
	Enqueue(q, root);
	/*parcurg arborele folosind o coada si caut elementul
	care are ID-ul egal cu cel dat ca parametru*/
	while(!Vida(q)){
		TArb aux = Dequeue(q);
		if(aux->info->id != NULL && strcmp(aux->info->id,id) == 0){
			i++;
			/*daca nodul gasit are deja o lista style o sterg
			si creez alta cu noile valori*/
			if(aux->info->style != NULL){
				DestroyAttr(&(aux->info->style));
				aux->info->style = NULL;
			}
			createStyleList(style, aux);
		}
		aux = aux->firstChild;
		for(p = aux; p != NULL; p = p->nextSibling){
			Enqueue(q, p);
		}
	}
	/*daca nu se gaseste niciun nod, se afiseaza urmatorul mesaj*/
	if(i == 0){
		fprintf(f,"Override style failed: no node found for selector %s!\n", id);
	}
	DistrQ(q);
}

/*functie de Override in functie de numele tag-ului*/
void OverrideByType(TArb tree, char *type, char *style, FILE *f){
	TArb root = tree;
	TArb p;
	int i = 0;
	TCoada q = InitQ();
	Enqueue(q, root);
	/*parcurg arborele folosind o coada si caut elementele
	care au numele egal cu cel dat ca parametru*/
	while(!Vida(q)){
		TArb aux = Dequeue(q);
		if(aux->info->type != NULL && strcmp(aux->info->type,type) == 0){
			i++;
			/*daca nodul gasit are deja o lista style o sterg
			si creez alta cu noile valori*/
			if(aux->info->style != NULL){
				DestroyAttr(&(aux->info->style));
				aux->info->style = NULL;
			}
			createStyleList(style, aux);
		}
		aux = aux->firstChild;
		for(p = aux; p != NULL; p = p->nextSibling){
			Enqueue(q, p);
		}
	}
	/*daca nu se gaseste niciun nod, se afiseaza urmatorul mesaj*/
	if(i == 0){
		fprintf(f,"Override style failed: no node found for selector %s!\n", type);
	}
	DistrQ(q);
}

/*functie de Override in functie de selectorul element.className*/
void OverrideByClassname(TArb tree, char *type, char *classname, char *style, FILE *f){
	TArb root = tree;
	TArb p;
	int i = 0;  
	TCoada q = InitQ();
	Enqueue(q, root);
	/*parcurg arborele folosind o coada si caut elementele
	care indeplinesc conditiile date*/
	while(!Vida(q)){
		TArb aux = Dequeue(q);
		if(strcmp(aux->info->type, type) == 0 && aux->info->otherAttributes != NULL){
			TAttr o;
			for(o = aux->info->otherAttributes; o != NULL; o = o->next){
				if(strcmp(o->name, "class") == 0 && strcmp(o->value, classname) == 0){
					i++;
					/*daca nodul gasit are deja o lista style o sterg
					si creez alta cu noile valori*/
					if(aux->info->style != NULL){
						DestroyAttr(&(aux->info->style));
						aux->info->style = NULL;
					}
					createStyleList(style, aux);
				}
			}
		}
		aux = aux->firstChild;
		for(p = aux; p != NULL; p = p->nextSibling){
			Enqueue(q, p);
		}
	}
	/*daca nu se gaseste niciun nod, se afiseaza urmatorul mesaj*/
	if(i == 0){
		fprintf(f,"Override style failed: no node found for selector %s.%s!\n", type, classname);
	}
	DistrQ(q);
}

/*functie de Override in functie de selectorul .className*/
void OverrideAllByClassname(TArb tree, char *classname, char *style, FILE *f){
	TArb root = tree;
	TArb p;
	int i = 0;  
	TCoada q = InitQ();
	Enqueue(q, root);
	/*parcurg arborele folosind o coada si caut elementele
	care indeplinesc conditiile date*/
	while(!Vida(q)){
		TArb aux = Dequeue(q);
		if(aux->info->otherAttributes != NULL){
			TAttr o;
			for(o = aux->info->otherAttributes; o != NULL; o = o->next){
				if(strcmp(o->name, "class") == 0 && strcmp(o->value, classname) == 0){
					i++;
					/*daca nodul gasit are deja o lista style o sterg
					si creez alta cu noile valori*/
					if(aux->info->style != NULL){
						DestroyAttr(&(aux->info->style));
						aux->info->style = NULL;
					}
					createStyleList(style, aux);
				}
			}
		}
		aux = aux->firstChild;
		for(p = aux; p != NULL; p = p->nextSibling){
			Enqueue(q, p);
		}
	}
	/*daca nu se gaseste niciun nod, se afiseaza urmatorul mesaj*/
	if(i == 0){
		fprintf(f,"Override style failed: no node found for selector .%s!\n", classname);
	}
	DistrQ(q);
}

/*functie de Override in functie de selectorul element1>element2*/
void OverrideByParent(TArb tree, char *parent_name, char *child_name, char *style, FILE *f){
	TArb root = tree;
	TArb p;
	int i = 0;
	TCoada q = InitQ();
	Enqueue(q, root);
	/*parcurg arborele folosind o coada si caut elementele
	care indeplinesc conditiile date*/
	while(!Vida(q)){
		TArb aux = Dequeue(q);
		if(aux->info->type != NULL && strcmp(aux->info->type,parent_name) == 0 && aux->firstChild != NULL){
			TArb child;
			for(child = aux->firstChild; child != NULL; child = child->nextSibling){
				if(child->info->type != NULL && strcmp(child->info->type, child_name) == 0){
					i++;
					/*daca nodul gasit are deja o lista style o sterg
					si creez alta cu noile valori*/
					if(child->info->style != NULL){
						DestroyAttr(&(child->info)->style);
						child->info->style = NULL;
					}
					createStyleList(style, child);
				}
			}

		}
		aux = aux->firstChild;
		for(p = aux; p != NULL; p = p->nextSibling){
			Enqueue(q, p);
		}
	}
	/*daca nu se gaseste niciun nod, se afiseaza urmatorul mesaj*/
	if(i == 0){
		fprintf(f,"Override style failed: no node found for selector %s>%s!\n", parent_name, child_name);
	}
	DistrQ(q);
}

/*functie auxiliara de Override in functie de selectorul element1 element2;
cauta daca in nodurile din subarborele element1 se afla noduri cu tipul element2*/
int OverrideByAncestorAux(TArb tree, char *child_name, char *style, int *i){
	TArb aux = tree; 
	TArb sibling;
	if(aux){
		for(sibling = aux; sibling != NULL; sibling = sibling->nextSibling){
			if(sibling->info->type != NULL && strcmp(sibling->info->type,child_name) == 0){
				(*i)++;
				/*daca nodul gasit are deja o lista style o sterg
				si creez alta cu noile valori*/
				if(sibling->info->style != NULL){
					DestroyAttr(&(sibling->info)->style);
					sibling->info->style = NULL;
				}
				createStyleList(style, sibling);
			}
			OverrideByAncestorAux(sibling->firstChild, child_name, style, i);
		}
	}
	return (*i);
}

/*functie de Override in functie de selectorul element1 element2*/
void OverrideByAncestor(TArb tree, char *ancestor_name, char *child_name, char *style, FILE *f){
	TArb root = tree;
	TArb p;
	int i = 0;
	int n = 0;
	TCoada q = InitQ();
	Enqueue(q, root);
	/*parcurg arborele folosind o coada si caut elementele
	care indeplinesc conditiile date*/
	while(!Vida(q)){
		TArb aux = Dequeue(q);
		if(aux->info->type != NULL && strcmp(aux->info->type, ancestor_name) == 0 && aux->firstChild != NULL){
			n = n + OverrideByAncestorAux(aux->firstChild, child_name, style, &i);
		}
		aux = aux->firstChild;
		for(p = aux; p != NULL; p = p->nextSibling){
			Enqueue(q, p);
		}
	}
	/*daca nu se gaseste niciun nod, se afiseaza urmatorul mesaj*/
	if(n == 0){
    	fprintf(f,"Override style failed: no node found for selector %s %s!\n", ancestor_name, child_name);
    }
	DistrQ(q);
}

/*functie de Append in functie de ID*/
void AppendById(TArb tree, char *id, char *style, FILE *f){
	TArb root = tree;
	TArb p;
	int i = 0, j, k = 0, l;
	char *aux_v = (char*)calloc(1000,sizeof(char));
    strcpy(aux_v, style);
	char *attr = strtok(aux_v, ";");
	char **array = calloc(100,sizeof(char*));
	for(l = 0; l < 100; l++){
    	array[l] = calloc(100,sizeof(char));
  	}
  	/*se memoreaza atributele intr-un vector de string-uri*/
	while(attr){
		strcpy(array[k], attr);
		k++;
		attr = strtok(NULL, ";");
	}
	TCoada q = InitQ();
	Enqueue(q, root);
	/*parcurg arborele folosind o coada si caut elementul
	care indeplineste conditia data*/
	while(!Vida(q)){
		TArb aux = Dequeue(q);
		if(aux->info->id != NULL && strcmp(aux->info->id, id) == 0){
			i++;
			/*daca lista style a nodului este nula, se 
			creeaza lista cu valorile date ca parametru*/
			if(aux->info->style == NULL){
				createStyleList(style, aux);
			}
			
			else{
				/*fiecare atribut este impartit in nume si valoare*/
				for(l = 0; l < k; l++){
					char *x = (char*)calloc(100,sizeof(char));
					strcpy(x, array[l]);
					int count = 0;
					char *a = strtok(x, " :");
					char *b = strtok(NULL, ";");
        			char *name = (char*)calloc(30,sizeof(char));
        			char *value = (char*)calloc(100,sizeof(char));
        			strcpy(name, a);
        			 for(j = 0; j < strlen(b); j++){
            			if(!isspace(b[j])){
              				strncat(value, &b[j], 1);
            			}
        			}
        			/*daca se gaseste un atribut cu numele respectiv
        			i se actualizeaza valoarea*/
					TAttr p, last;
					for(p = aux->info->style; p != NULL; p = p->next){
						if(strcmp(p->name, name) == 0){
							count = 1;
							strcpy(p->value, value);
						}
					}
					/*altfel se adauga atributul la finalul listei style*/
					if(count == 0){
						for(p = aux->info->style, last = NULL; p != NULL; last = p, p = p->next);
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
			}
		}
		aux = aux->firstChild;
		for(p = aux; p != NULL; p = p->nextSibling){
			Enqueue(q, p);
		}
	}
	/*daca nu se gaseste niciun nod, se afiseaza urmatorul mesaj*/
	if(i == 0){
		fprintf(f,"Append to style failed: no node found for selector %s!\n", id);
	}
	for(l = 0; l < 100; l++){
        free(array[l]);
    }
    free(array);
    free(aux_v);
	DistrQ(q);
}

/*functie de Append in functie de numele tag-ului*/
void AppendByType(TArb tree, char *type, char *style, FILE *f){
	TArb root = tree;
	TArb p;
	int i = 0, j, k = 0, l;
	char *aux_v = (char*)calloc(1000,sizeof(char));
    strcpy(aux_v, style);
	char *attr = strtok(aux_v, ";");
	char **array = calloc(100,sizeof(char*));
	for(l = 0; l < 100; l++){
    	array[l] = calloc(100,sizeof(char));
  	}
  	/*se memoreaza atributele intr-un vector de string-uri*/
	while(attr){
		strcpy(array[k], attr);
		k++;
		attr = strtok(NULL, ";");
	}
	TCoada q = InitQ();
	Enqueue(q, root);
	/*parcurg arborele folosind o coada si caut elementul
	care indeplineste conditia data*/
	while(!Vida(q)){
		TArb aux = Dequeue(q);
		if(aux->info->type != NULL && strcmp(aux->info->type, type)==0){
			i++;
			/*daca lista style a nodului este nula, se 
			creeaza lista cu valorile date ca parametru*/
			if(aux->info->style == NULL){
				createStyleList(style, aux);
			}
			else{
				/*fiecare atribut este impartit in nume si valoare*/
				for(l = 0; l < k; l++){
					char *x = (char*)calloc(100,sizeof(char));
					strcpy(x, array[l]);
					int count = 0;
					char *a = strtok(x, " :");
					char *b = strtok(NULL, ";");
        			char *name = (char*)calloc(30,sizeof(char));
        			char *value = (char*)calloc(100,sizeof(char));
        			strcpy(name, a);
        			for(j = 0; j < strlen(b); j++){
            			if(!isspace(b[j])){
                			strncat(value, &b[j], 1);
            			}
       				}
       				/*daca se gaseste un atribut cu numele respectiv
        			i se actualizeaza valoarea*/
					TAttr p, last;
					for(p = aux->info->style; p != NULL; p = p->next){
						if(strcmp(p->name,name) == 0){
							count = 1;
							strcpy(p->value, value);
						}
					}
					/*altfel se adauga atributul la finalul listei style*/
					if(count == 0){
						for(p = aux->info->style, last = NULL; p != NULL; last = p, p = p->next);
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
			}
		}
		aux = aux->firstChild;
		for(p = aux; p != NULL; p = p->nextSibling){
			Enqueue(q, p);
		}
	}
	/*daca nu se gaseste niciun nod, se afiseaza urmatorul mesaj*/
	if(i == 0){
		fprintf(f,"Append to style failed: no node found for selector %s!\n", type);
	}
	for(l = 0; l < 100; l++){
        free(array[l]);
    }
    free(array);
    free(aux_v);
	DistrQ(q);
}

/*functie de Append in functie de selectorul element.className*/
void AppendByClassname(TArb tree, char *type, char *classname, char *style, FILE *f){
	TArb root = tree;
	TArb p;
	int i = 0, j, k = 0, l;
	char *aux_v = (char*)calloc(1000,sizeof(char));
    strcpy(aux_v, style);
	char *attr = strtok(aux_v, ";");
	char **array = calloc(100,sizeof(char*));
	for(l = 0; l < 100; l++){
    	array[l] = calloc(100,sizeof(char));
  	}
  	/*se memoreaza atributele intr-un vector de string-uri*/
	while(attr){
		strcpy(array[k], attr);
		k++;
		attr = strtok(NULL, ";");
	}
	TCoada q = InitQ();
	Enqueue(q, root);
	/*parcurg arborele folosind o coada si caut elementul
	care indeplineste conditia data*/
	while(!Vida(q)){
		TArb aux = Dequeue(q);
		if(strcmp(aux->info->type, type) == 0 && aux->info->otherAttributes != NULL){
			TAttr o;
			for(o = aux->info->otherAttributes; o != NULL; o = o->next){
				if(strcmp(o->name,"class") == 0 && strcmp(o->value,classname) == 0){
					i++;
					/*daca lista style a nodului este nula, se 
					creeaza lista cu valorile date ca parametru*/
					if(aux->info->style == NULL){
						createStyleList(style, aux);
					}
					else{
						/*fiecare atribut este impartit in nume si valoare*/
						for(l = 0; l < k; l++){
							char *x = (char*)calloc(100,sizeof(char));
							strcpy(x, array[l]);
							int count = 0;
							char *a = strtok(x, " :");
							char *b = strtok(NULL, ";");
        					char *name = (char*)calloc(30,sizeof(char));
        					char *value = (char*)calloc(100,sizeof(char));
        					strcpy(name, a);
        					for(j = 0; j < strlen(b); j++){
            					if(!isspace(b[j])){
                					strncat(value, &b[j], 1);
            					}
        					}
        					/*daca se gaseste un atribut cu numele respectiv
        					i se actualizeaza valoarea*/
							TAttr p, last;
							for(p = aux->info->style; p != NULL; p = p->next){
								if(strcmp(p->name,name) == 0){
									count = 1;
									strcpy(p->value, value);
								}
							}
							/*altfel se adauga atributul la finalul listei style*/
							if(count == 0){
								for(p = aux->info->style, last = NULL; p != NULL; last = p, p = p->next);
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
					}
				}
			}
		}
		aux = aux->firstChild;
		for(p = aux; p != NULL; p = p->nextSibling){
			Enqueue(q, p);
		}
	}
	/*daca nu se gaseste niciun nod, se afiseaza urmatorul mesaj*/
	if(i == 0){
		fprintf(f,"Append to style failed: no node found for selector %s.%s!\n", type, classname);
	}
	for(l = 0; l < 100; l++){
        free(array[l]);
    }
    free(array);
    free(aux_v);
	DistrQ(q);
}

/*functie de Append in functie de selectorul .className*/
void AppendAllByClassname(TArb tree, char *classname, char *style, FILE *f){
	TArb root = tree;
	TArb p;
	int i = 0,j, k = 0, l;
	char *aux_v = (char*)calloc(1000,sizeof(char));
    strcpy(aux_v, style);
	char *attr = strtok(aux_v, ";");
	char **array = calloc(100,sizeof(char*));
	for(l = 0; l < 100; l++){
    	array[l] = calloc(100,sizeof(char));
  	}
  	/*se memoreaza atributele intr-un vector de string-uri*/
	while(attr){
		strcpy(array[k], attr);
		k++;
		attr = strtok(NULL, ";");
	}
	TCoada q = InitQ();
	Enqueue(q, root);
	/*parcurg arborele folosind o coada si caut elementul
	care indeplineste conditia data*/
	while(!Vida(q)){
		TArb aux = Dequeue(q);
		if(aux->info->otherAttributes != NULL){
			TAttr o;
			for(o = aux->info->otherAttributes; o != NULL; o = o->next){
				if(strcmp(o->name, "class") == 0 && strcmp(o->value, classname) == 0){
					i++;
					/*daca lista style a nodului este nula, se 
					creeaza lista cu valorile date ca parametru*/
					if(aux->info->style == NULL){
						createStyleList(style, aux);
					}
					else{
						/*fiecare atribut este impartit in nume si valoare*/
						for(l = 0; l < k; l++){
							char *x = (char*)calloc(100,sizeof(char));
							strcpy(x, array[l]);
							int count = 0;
							char *a = strtok(x, " :");
							char *b = strtok(NULL, " :;");
        					char *name = (char*)calloc(30,sizeof(char));
        					char *value = (char*)calloc(100,sizeof(char));
        					strcpy(name, a);
        					for(j = 0; j < strlen(b); j++){
            					if(!isspace(b[j])){
                					strncat(value, &b[j], 1);
            					}
        					}
        					/*daca se gaseste un atribut cu numele respectiv
        					i se actualizeaza valoarea*/
							TAttr p, last;
							for(p = aux->info->style; p != NULL; p = p->next){
								if(strcmp(p->name,name) == 0){
									count = 1;
									strcpy(p->value, value);
								}
							}
							/*altfel se adauga atributul la finalul listei style*/
							if(count == 0){
								for(p = aux->info->style, last = NULL; p != NULL; last = p, p = p->next);
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
					}
				}
			}
		}
		aux = aux->firstChild;
		for(p = aux; p != NULL; p = p->nextSibling){
			Enqueue(q, p);
		}
	}
	/*daca nu se gaseste niciun nod, se afiseaza urmatorul mesaj*/
	if(i == 0){
		fprintf(f,"Append to style failed: no node found for selector .%s!\n", classname);
	}
	for(l = 0; l < 100; l++){
        free(array[l]);
    }
    free(array);
    free(aux_v);
	DistrQ(q);
}

/*functie de Append in functie de selectorul element1>element2*/
void AppendByParent(TArb tree, char *parent_name, char *child_name, char *style, FILE *f){
	TArb root = tree;
	TArb p;
	int i = 0, j, k = 0, l;
	char *aux_v = (char*)calloc(1000,sizeof(char));
    strcpy(aux_v, style);
	char *attr = strtok(aux_v, ";");
	char **array = calloc(100,sizeof(char*));
	for(l = 0; l < 100; l++){
    	array[l] = calloc(100,sizeof(char));
  	}
  	/*se memoreaza atributele intr-un vector de string-uri*/
	while(attr){
		strcpy(array[k], attr);
		k++;
		attr = strtok(NULL, ";");
	}
	TCoada q = InitQ();
	Enqueue(q, root);
	/*parcurg arborele folosind o coada si caut elementul
	care indeplineste conditia data*/
	while(!Vida(q)){
		TArb aux = Dequeue(q);
		if(aux->info->type != NULL && strcmp(aux->info->type,parent_name)==0 && aux->firstChild != NULL){
			TArb child;
			for(child = aux->firstChild; child != NULL; child = child->nextSibling){
				if(child->info->type != NULL && strcmp(child->info->type, child_name) == 0){
					i++;
					/*daca lista style a nodului este nula, se 
					creeaza lista cu valorile date ca parametru*/
					if(child->info->style == NULL){
						createStyleList(style, child);
					}
					else{
						/*fiecare atribut este impartit in nume si valoare*/
						for(l = 0; l < k; l++){
							char *x = (char*)calloc(100,sizeof(char));
							strcpy(x, array[l]);
							int count = 0;
							char *a = strtok(x, " :");
							char *b = strtok(NULL, ";");
        					char *name = (char*)calloc(30,sizeof(char));
        					char *value = (char*)calloc(100,sizeof(char));
        					strcpy(name, a);
        					for(j = 0; j < strlen(b); j++){
            					if(!isspace(b[j])){
                					strncat(value, &b[j], 1);
            					}
        					}
        					/*daca se gaseste un atribut cu numele respectiv
        					i se actualizeaza valoarea*/
							TAttr p, last;
							for(p = child->info->style; p != NULL; p = p->next){
								if(strcmp(p->name,name) == 0){
									count = 1;
									strcpy(p->value, value);
								}
							}
							/*altfel se adauga atributul la finalul listei style*/
							if(count == 0){
								for(p = child->info->style, last = NULL; p != NULL; last = p, p = p->next);
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
					}
				}
			}
		}
		aux = aux->firstChild;
		for(p = aux; p != NULL; p = p->nextSibling){
			Enqueue(q,p);
		}
	}
	/*daca nu se gaseste niciun nod, se afiseaza urmatorul mesaj*/
	if(i == 0){
		fprintf(f,"Append to style failed: no node found for selector %s>%s!\n", parent_name, child_name);
	}
	for(l = 0; l < 100; l++){
        free(array[l]);
    }
    free(array);
    free(aux_v);
	DistrQ(q);
}

/*functie auxiliara de Append in functie de selectorul element1 element2;
cauta daca in nodurile din subarborele element1 se afla noduri cu tipul element2*/
int AppendByAncestorAux(TArb tree, char *child_name, char *style, int *i){ 
	TArb aux = tree; 
	TArb sibling;
	int j, k = 0, l;
	char *aux_v = (char*)calloc(1000,sizeof(char));
    strcpy(aux_v, style);
	char *attr = strtok(aux_v, ";");
	char **array = calloc(100,sizeof(char*));
	for(l = 0; l < 100; l++){
    	array[l] = calloc(100,sizeof(char));
  	}
  	/*se memoreaza atributele intr-un vector de string-uri*/
	while(attr){
		strcpy(array[k], attr);
		k++;
		attr = strtok(NULL, ";");
	}
	/*parcurg arborele recursiv si caut elementul
	care indeplineste conditia data*/
	if(aux){
		for(sibling = aux; sibling != NULL; sibling = sibling->nextSibling){
			if(sibling->info->type != NULL && strcmp(sibling->info->type,child_name)==0){
				(*i)++;
				TArb child = sibling;
				/*daca lista style a nodului este nula, se 
				creeaza lista cu valorile date ca parametru*/
				if(child->info->style == NULL){
					createStyleList(style, child);
				}
				else{
					/*fiecare atribut este impartit in nume si valoare*/
					for(l = 0; l < k; l++){
						char *x = (char*)calloc(100,sizeof(char));
						strcpy(x, array[l]);
						int count = 0;
						char *a = strtok(x, " :");
						char *b = strtok(NULL, ";");
	        			char *name = (char*)calloc(30,sizeof(char));
	        			char *value = (char*)calloc(100,sizeof(char));
	        			strcpy(name, a);
	        			for(j = 0; j < strlen(b); j++){
	            			if(!isspace(b[j])){
	                			strncat(value, &b[j], 1);
	            			}
	        			}
	        			/*daca se gaseste un atribut cu numele respectiv
        				i se actualizeaza valoarea*/
						TAttr p, last;
						for(p = child->info->style; p != NULL; p = p->next){
							if(strcmp(p->name,name) == 0){
								count = 1;
								strcpy(p->value, value);
							}
						}
						/*altfel se adauga atributul la finalul listei style*/
						if(count == 0){
							for(p = child->info->style, last = NULL; p != NULL; last = p, p = p->next);
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
				}
			}
			AppendByAncestorAux(sibling->firstChild, child_name, style, i);
		}
	}
	for(l = 0; l < 100; l++){
        free(array[l]);
    }
    free(array);
    free(aux_v);
    return (*i);
}

/*functie de Append in functie de selectorul element1 element2*/
void AppendByAncestor(TArb tree, char *parent_name, char *child_name, char *style, FILE *f){
	TArb root = tree;
	TArb p;
	int i = 0;
	int n = 0;
	TCoada q = InitQ();
	Enqueue(q, root);
	/*parcurg arborele folosind o coada si caut elementul
	care indeplineste conditia data*/
	while(!Vida(q)){
		TArb aux = Dequeue(q);
		if(aux->info->type != NULL && strcmp(aux->info->type,parent_name) == 0 && aux->firstChild != NULL){
			n = n + AppendByAncestorAux(aux->firstChild, child_name, style, &i);
		}
		aux = aux->firstChild;
		for(p = aux; p != NULL; p = p->nextSibling){
			Enqueue(q,p);
		}
	}
	/*daca nu se gaseste niciun nod, se afiseaza urmatorul mesaj*/
	if(n == 0){
    	fprintf(f,"Append to style failed: no node found for selector %s %s!\n", parent_name, child_name);
    }
	DistrQ(q);
}

/*functie recursiva de sters un nod, in functie de ID*/
int DeleteById(TArb *tree, char *id, FILE *f, int *i){
	TArb aux, ant, found;
    for(aux = *tree, ant = NULL; aux != NULL; ){
    	/*daca se gaseste nodul cu ID-ul dat*/
        if(aux->info->id != NULL && strcmp(aux->info->id, id) == 0){
        	(*i)++;
        	found = aux;
        	aux = aux->nextSibling;
        	/*se elimina si se refac legaturile*/
        	if(ant){
           		ant->nextSibling = aux;
          	}
          	else{
            	*tree = aux;
          	}
          	/*se sterg copiii elementului gasit*/
          	if(found->firstChild){
            	Delete(&(found->firstChild));
            }
            /*se sterge nodul gasit*/
            DestroyNode(&found);
        }
        /*se apeleaza functia recursiv*/
        else{
        	if(aux->firstChild){
        		DeleteById(&(aux->firstChild), id, f, i);
        	}
        	ant = aux;
        	aux = aux->nextSibling;

        }
    }
   return *i;
}

/*functie recursiva de sters un nod, in functie de numele tag-ului*/
int DeleteByType(TArb *tree, char *type, FILE *f, int *i){
	TArb aux, ant, found;
    for(aux = *tree, ant = NULL; aux != NULL; ){
    	/*daca se gaseste nodul cu numele dat ca parametru*/
        if(strcmp(aux->info->type, type) == 0){
        	(*i)++;
        	found = aux;
        	aux = aux->nextSibling;
        	/*se elimina si se refac legaturile*/
        	if(ant){
           		ant->nextSibling = aux;
          	}
          	else{
            	*tree = aux;
          	}
          	/*se sterg copiii elementului gasit*/
          	if(found->firstChild){
            	Delete(&found->firstChild);
            }
            /*se sterge nodul gasit*/
            DestroyNode(&found);
        }
        /*se apeleaza functia recursiv*/
        else{
        	if(aux->firstChild){
        		DeleteByType(&(aux->firstChild), type, f, i);
        	}
        	ant = aux;
        	aux = aux->nextSibling;

        }
    }
  return *i;
}

/*functie recursiva de sters un nod, in functie de selectorul element.className*/
int DeleteByClassname(TArb *tree, char *type, char *classname, FILE *f, int *i){
	TArb aux, ant, found;  
    for(aux = *tree, ant = NULL; aux != NULL; ){
        if(strcmp(aux->info->type, type) == 0 && aux->info->otherAttributes){
        	TAttr o;
			for(o = aux->info->otherAttributes; o != NULL; o = o->next){
				/*daca se gaseste nodul element cu clasa .className*/
				if(strcmp(o->name, "class") == 0 && strcmp(o->value, classname) == 0){
	        		(*i)++;
		        	found = aux;
		        	aux = aux->nextSibling;
		        	/*se elimina si se refac legaturile*/
		        	if(ant){
		           		ant->nextSibling = aux;
		          	}
		          	else{
		            	*tree = aux;
		          	}
		          	/*se sterg copiii elementului gasit*/
		          	if(found->firstChild){
		            	Delete(&(found->firstChild));
		            }
		            /*se sterge nodul gasit*/
		            DestroyNode(&found);
		        }
		    }
	    }
	    /*se apeleaza functia recursiv*/
        else{
        	if(aux->firstChild){
        		DeleteByClassname(&(aux->firstChild), type, classname, f, i);
        	}
        	ant = aux;
        	aux = aux->nextSibling;

        }
    }
   return *i;
}

/*functie recursiva de sters un nod, in functie de selectorul .className*/
int DeleteAllByClassname(TArb *tree, char *classname, FILE *f, int *i){
	TArb aux, ant, found;
    for(aux = *tree, ant = NULL; aux != NULL; ){
        if(aux->info->otherAttributes != NULL){
        	TAttr o;
			for(o = aux->info->otherAttributes; o != NULL; o = o->next){
				/*daca se gaseste nodul cu clasa .className*/
				if(strcmp(o->name, "class") == 0 && strcmp(o->value, classname) == 0){
	        		(*i)++;
		        	found = aux;
		        	aux = aux->nextSibling;
		        	/*se elimina si se refac legaturile*/
		        	if(ant){
		           		ant->nextSibling = aux;
		          	}
		          	else{
		            	*tree = aux;
		          	}
		          	/*se sterg copiii elementului gasit*/
		          	if(found->firstChild){
		            	Delete(&(found->firstChild));
		            }
		            /*se sterge nodul gasit*/
		            DestroyNode(&found);
		        }
		    }
	    }
	    /*se apeleaza functia recursiv*/
        else{
        	if(aux->firstChild){
        		DeleteAllByClassname(&(aux->firstChild), classname, f, i);
        	}
        	ant = aux;
        	aux = aux->nextSibling;

        }
    }
   return (*i);
}

/*functie auxiliara de sters un nod, in functie de selectorul element1>element2;
cauta daca nodul element1 are un copil element2*/
int DeleteByParentAux(TArb *tree, char *child, int *i){
	TArb aux, ant, found;
    for(aux = *tree, ant = NULL; aux != NULL; ){
    	/*daca se gaseste nodul element2*/
        if(strcmp(aux->info->type, child) == 0){
        	(*i)++;
        	found = aux;
        	aux = aux->nextSibling;
        	/*se elimina si se refac legaturile*/
        	if(ant){
           		ant->nextSibling = aux;
          	}
          	else{
            	*tree = aux;
          	}
          	/*se sterg copiii elementului gasit*/
          	if(found->firstChild){
            	Delete(&(found->firstChild));
            }
            /*se sterge nodul gasit*/
            DestroyNode(&found);
        }
        else{
	        ant = aux;
	        aux = aux->nextSibling;
        }
    }
    return (*i);
}

/*functie recursiva de sters un nod, in functie de selectorul element1>element2*/
int  DeleteByParent(TArb *tree, char *parent, char *child, FILE *f, int *i){
	TArb root = *tree;
	TArb p;
	TCoada q = InitQ();
	Enqueue(q, root);
	/*se parcurge arborele folosind o coada pentru a gasi nodul element1*/
	while(!Vida(q)){
		TArb aux = Dequeue(q);
		if(aux->info->type != NULL && strcmp(aux->info->type, parent)==0){
			/*se cauta nodul element2 in copiii sai*/
			if(aux->firstChild != NULL){
				*i = DeleteByParentAux(&(aux->firstChild), child, i);
			}
		}
		aux = aux->firstChild;
		for(p = aux; p != NULL; p = p->nextSibling){
			Enqueue(q, p);
		}
	}
	DistrQ(q);
	return *i;
}

/*functie auxiliara de sters un nod, in functie de selectorul element1 element2;
cauta daca in subarborele element1 se afla element2*/
int DeleteByAncestorAux(TArb *tree, char *child, int *i){
	TArb aux, ant, found;
    for(aux = *tree, ant = NULL; aux != NULL; ){
    	/*daca se gaseste nodul element2*/
        if(strcmp(aux->info->type, child) == 0){
        	(*i)++;
        	found = aux;
        	aux = aux->nextSibling;
        	/*se elimina si se refac legaturile*/
        	if(ant){
           		ant->nextSibling = aux;
           		if(aux == NULL){
            		ant->nextSibling = NULL;
            	}
          	}
          	else{
            	*tree = aux;
            	if(aux == NULL){
            		*tree = NULL;
            	}
          	}
          	/*se sterg copiii elementului gasit*/
          	if(found->firstChild){
            	Delete(&(found->firstChild));
            }
            /*se sterge nodul gasit*/
            DestroyNode(&found);
        }
        /*se apeleaza functia recursiv*/
        else{
        	if(aux->firstChild){
        		DeleteByAncestorAux(&(aux->firstChild), child, i);
        	}
	        ant = aux;
	        aux = aux->nextSibling;
        }
    }
    return (*i);
}

/*functie recursiva de sters un nod, in functie de selectorul element1 element2*/
int DeleteByAncestor(TArb *tree, char *ancestor, char *child, FILE *f, int *i){
	TArb root = *tree;
	TArb p;
	TCoada q = InitQ();
	Enqueue(q, root);
	/*se parcurge arborele folosind o coada pentru a gasi nodul element1*/
	while(!Vida(q)){
		TArb aux = Dequeue(q);
		/*se cauta in subarborele sau nodul element2*/
		if(aux->info->type != NULL && strcmp(aux->info->type, ancestor)==0 && aux->firstChild != NULL){
			*i = DeleteByAncestorAux(&(aux->firstChild), child, i);
		}
		aux = aux->firstChild;
		for(p = aux; p != NULL; p = p->nextSibling){
			Enqueue(q, p);
		}
	}
	DistrQ(q);
	return *i;
}
