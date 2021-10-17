/*Purcareanu Corina
311CB*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "lib.h"

/*functie care afiseaza informatia din arbore in formatul dorit*/
void PrintTree(TArb tree, int i, FILE *f){
	TArb aux = tree;
	TArb sibling;
	TAttr l, o;
	int j;
	if(aux){	/*cat timp exista nodul din arbore*/
		/*se parcurg fratii*/
		for(sibling = aux; sibling != NULL;sibling = sibling->nextSibling){
			/*se afiseaza numarul de tab-uri corespunzatoare tag-ului html*/
			for(j = 0; j<i; j++){
				fprintf(f,"\t");
			}
			/*se afiseaza tipul tag-ului*/
			fprintf(f,"<%s",sibling->info->type);
			/*se afiseaza lista style*/
			if(sibling->info->style != NULL){
				fprintf(f," style=\"");
				for(l = sibling->info->style; l != NULL; l = l->next){
					fprintf(f,"%s: %s;", l->name, l->value);
					if(l->next != NULL){
						fprintf(f," ");
					}
					else{
						fprintf(f,"\"");
					}
				}
			}
			/*se afiseaza lista otherAttributes*/
			if(sibling->info->otherAttributes != NULL){
				for(o = sibling->info->otherAttributes; o != NULL; o = o->next){
					fprintf(f," %s=\"%s\"", o->name, o->value);
				}
			}
			if(sibling->info->isSelfClosing == 0){
				fprintf(f,">");
			}
			else{
				fprintf(f,"/>");
			}
			/*se afiseaza continutul*/
			if(strlen(sibling->info->contents)!=0){
				fprintf(f,"\n");
				for(j = 0; j<i+1; j++){
					fprintf(f,"\t");
				}
				fprintf(f,"%s", sibling->info->contents);
			}
			fprintf(f,"\n");
			/*se apeleaza functia recursiv*/
			PrintTree(sibling->firstChild, i+1, f);
			/*se se inchide tag-ul*/
			if(sibling->info->isSelfClosing == 0){
			for(j = 0; j<i; j++){
				fprintf(f,"\t");
			}
			fprintf(f,"</%s>\n", sibling->info->type);
			}
		 } 
	}
}

/*functie care citeste din fisierul html*/
TArb Read(FILE *html){
	char ch;
	TParseState x = PARSE_CONTENTS;
    char *name = (char*)calloc(1000,sizeof(char));
    char *value = (char*)calloc(1000,sizeof(char));
    int i = 0;
    TStiva stack = InitS();
    TArb tree = NULL, current_node;
    /*cat timp se citeste o litera din fisier*/
    while((ch = getc(html)) != EOF){
     	x = Interpret(x, ch);
     	/*daca starea este PARSE_CONTENTS si litera este diferita de 
     	caracterele mentionate se adauga litera la continutul nodului curent*/
     	if(x == PARSE_CONTENTS && ch!= '>' && ch!= '\n' && ch != '\t' && ch!= '\r' && ch!= '\0'){
     		strncat(current_node->info->contents, &ch,1);
     	}
     	/*daca starea este PARSE_TAG_TYPE*/
     	if(x == PARSE_TAG_TYPE){
     		i++;
     		/*prima data cand intra in aceasta stare se creeaza nodul*/
     		if(i == 1){
     			if(tree == NULL){
	     			tree = CreateNode();
	     			current_node = tree;
	     		}
	     		else{
	     			/*se adauga nodul curent in stiva pentru a putea fi scos
	     			cand se inchide un tag si astfel sa se intoarca la nodul parinte*/
	     			Push(stack, current_node);
	     			/*daca primul copil e null, se creeaza nodul si se adauga ID-ul
	     			avand ID-ul parintelui si "1" la final; daca parintele e "html", ID-ul
	     			copilului va fi 1*/
	     			if(current_node->firstChild == NULL){
	     				current_node->firstChild = CreateNode();
	     				if(strcmp(current_node->info->type, "html")==0){
							current_node->firstChild->info->id = (char*)calloc(30,sizeof(char));
	   	 					strcpy(current_node->firstChild->info->id,"1");
	     				}
	     				else{
	     					current_node->firstChild->info->id = (char*)calloc(30,sizeof(char));
	     					strcpy(current_node->firstChild->info->id, current_node->info->id);
	     					strcat(current_node->firstChild->info->id,".1");
	     				}
	     				current_node = current_node->firstChild;
	     			}
	     			/*daca primul copil nu e null, se parcurge lista copiilor pana la final 
	     			si se adauga nodul, avand ID-ul parintelui, iar la final nr la care se 
	     			afla in lista; daca parintele e "html", ID-ul copilului este 2*/
	     			else{
	     				TArb p, last;
	     				int j = 1;
	     				for(p = current_node->firstChild; p != NULL; p = p->nextSibling){
	     					j++;
	     				}
	     				for(p = current_node->firstChild, last = NULL; p != NULL; last = p, p = p->nextSibling);
	     				last->nextSibling = CreateNode();
	     				if(strcmp(current_node->info->type, "html")==0){
							last->nextSibling->info->id = (char*)calloc(30,sizeof(char));
	   	 					strcpy(last->nextSibling->info->id,"2");
	     				}
	     				else{
	     					last->nextSibling->info->id = (char*)calloc(30,sizeof(char));
	   	 					strcpy(last->nextSibling->info->id,current_node->info->id);
	   	 					strcat(last->nextSibling->info->id,".");
	   	 					char *id = (char*)calloc(30,sizeof(char));
	   	 					sprintf(id, "%d", j);
	   	 					strcat(last->nextSibling->info->id,id);
	   	 					free(id);
	     				}
	     				current_node = last->nextSibling;
	     			}
	     		}
     		}
     		/*se adauga litera la campul type al nodului curent*/
     		strncat(current_node->info->type, &ch,1);
     	}
     	/*se reseteaza contorul pentru cand se citeste tipul nodului*/
     	if(ch == '>'){
     		i = 0;
     	}
     	/*daca starea e PARSE_ATTRIBUTE_NAME, se adauga 
     	litera in variabila name*/
     	if(x == PARSE_ATTRIBUTE_NAME){
     		strncat(name, &ch,1);
     	}
     	/*daca starea e PARSE_ATTRIBUTE_VALUE, se adauga 
     	litera in variabila value*/
     	if(x == PARSE_ATTRIBUTE_VALUE && ch != '"'){
     		strncat(value, &ch,1);
     	}
     	/*daca starea e PARSE_REST_OF_TAG, se creeaza lista;daca name e style
     	se creeaza lista style, altfel se creeaza lista otherAttributes*/
     	if(x == PARSE_REST_OF_TAG){
     		if(strcmp(name,"style") == 0 && strlen(value) != 0){
     		 	createStyleList(value, current_node);
     		}
     		if(strcmp(name,"style") != 0 && strlen(value) != 0){
     			if(current_node->info->otherAttributes == NULL){
             		current_node->info->otherAttributes = createAttrNode(name, value);
             	}
             	else{
             		TAttr p, last;
             		for(p = current_node->info->otherAttributes , last = NULL; p != NULL; last = p, p = p->next);
             		last->next = createAttrNode(name, value);
                }

     		}
     		/*se reseteaza variabilele name si value*/  
     		free(name);
     		name = (char*)calloc(1000,sizeof(char));
     		free(value);
     		value = (char*)calloc(1000,sizeof(char)); 		
     	}
     	/*daca starea e PARSE_CLOSING_TAG, se scoate ultimul nod adaugat
     	in stiva si el devine nodul curent*/
     	if(ch == '/' && x == PARSE_CLOSING_TAG){
     		if(strcmp(current_node->info->type, "html") != 0){
     			current_node = Pop(stack);
     		}
	    }
	    /*daca starea e PARSE_SELF_CLOSING, se scoate ultimul nod adaugat
     	in stiva si el devine nodul curent*/
	    if(ch == '/' && x == PARSE_SELF_CLOSING){
     		current_node->info->isSelfClosing = 1;
     		if(strcmp(current_node->info->type, "html") != 0){
     			current_node = Pop(stack);
     		}
	    }
    }
    DistrS(stack);
    free(name);
    free(value);
    return tree;
}

/*functie pentru adaugat un nou nod in arbore in functie
de ID-ul parintelui*/
void ADD(TArb tree, char *id, char *tag, FILE *f){
	TArb current_node;
	TArb root = tree;
	TArb p, last;
	TParseState x = PARSE_CONTENTS;
	int i = 0, count = 0;
	char *name = (char*)calloc(30,sizeof(char));
    char *value = (char*)calloc(1000,sizeof(char));
    	TCoada q = InitQ();
	Enqueue(q, root);
	/*se parcurge arborele pentru a gasi nodul cu ID-ul
	dat ca parametru*/
	while(!Vida(q)){
		TArb aux = Dequeue(q);
		if(aux->info->id != NULL && strcmp(aux->info->id, id) == 0){
			count++;
			 current_node = aux;
		}
		aux = aux->firstChild;
		for(p = aux; p != NULL; p = p->nextSibling){
			Enqueue(q, p);
		}
	}
	/*daca s-a gasit nodul se creeaza noul nod*/
	if(count != 0){
		/*daca primul copil al nodului parinte e null, noul
		nod va fi primul fiu si i se adauga ID-ul*/
		if(current_node->firstChild == NULL){
			current_node->firstChild = CreateNode();
			current_node->firstChild->info->id = (char*)calloc(100,sizeof(char));
		    strcpy(current_node->firstChild->info->id, current_node->info->id);
		    strcat(current_node->firstChild->info->id,".1");
			current_node = current_node->firstChild;
		}
		/*altfel se adauga la finalul listei de copiii si i se adauga
		ID-ul corespunzator*/
		else{
			int j = 1;
		    for(p = current_node->firstChild; p != NULL; p = p->nextSibling){
		    	j++;
		    }
			for(p = current_node->firstChild, last = NULL; p != NULL;last = p, p = p->nextSibling);
			last->nextSibling = CreateNode();
			last->nextSibling->info->id = (char*)calloc(30,sizeof(char));
		   	strcpy(last->nextSibling->info->id, current_node->info->id);
		   	strcat(last->nextSibling->info->id,".");
		   	char *id = (char*)calloc(30, sizeof(char));
		   	sprintf(id, "%d", j);
		   	strcat(last->nextSibling->info->id, id);
		   	free(id);
			current_node = last->nextSibling;
		}
		/*cat timp tag-ul dat ca parametru contine caractere,
		se adauga informatia in nod in acelasi mod ca la functia Read*/
		while(i < strlen(tag)){
			x = Interpret(x, tag[i]);
			if(x == PARSE_CONTENTS && tag[i] != '>' && tag[i] != '\n' && tag[i] != '\t'
			 && tag[i] != '\r' && tag[i] != '\0' && tag[i] != ' '){
	     		strncat(current_node->info->contents, &tag[i],1);
	     	}
	     	if(x == PARSE_TAG_TYPE){
	     		strncat(current_node->info->type, &tag[i],1);
	     	}
	     	if(x == PARSE_ATTRIBUTE_NAME){
	     		strncat(name, &tag[i], 1);
	     	}
	     	if(x == PARSE_ATTRIBUTE_VALUE && tag[i] != '"'){
	     		strncat(value, &tag[i], 1);
	     	}
	     	if(x == PARSE_REST_OF_TAG){
	     		if(strcmp(name, "style") == 0 && strlen(value) != 0){
	     		 	createStyleList(value, current_node);
	     		}
	     		if(strcmp(name, "style") != 0 && strlen(value) != 0){
	     			if(current_node->info->otherAttributes == NULL){
	             		current_node->info->otherAttributes = createAttrNode(name, value);
	             	}
	             	else{
	             		TAttr p, last;
	             		for(p = current_node->info->otherAttributes , last = NULL; p != NULL; last = p, p = p->next);
	             		last->next = createAttrNode(name, value);
	                }

	     		}  
	     		free(name);
	     		name = (char*)calloc(30,sizeof(char));
	     		free(value);
	     		value = (char*)calloc(1000,sizeof(char)); 		
	     	}
	     	i++;
		}
	}
	/*daca nu s-a gasit niciun nod cu ID-ul dat se afiseaza urmatorul mesaj:*/
	if(count == 0){
		fprintf(f, "Add tag failed: node with id %s not found!\n", id);
	}
	DistrQ(q);
	free(name);
	free(value);
}

/*functie pentru suprascris lista style*/
void overrideStyle(TArb tree, char *selector, char *style, FILE *f){
	char *style_list = (char*)calloc(1000,sizeof(char));
    strcpy(style_list, style);
    char *aux_selector = (char*)calloc(50,sizeof(char));
    char *s1 = (char*)calloc(50,sizeof(char));
    char *s2 = (char*)calloc(50,sizeof(char));
    char *a1, *a2;
    int i = 0, j;
    strcpy(aux_selector, selector);
    /*se apeleaza functia corespunzatoare selectorului dat*/
    if(aux_selector[0] == '#'){
    	for(j = 0; j <strlen(aux_selector); j++){
    		if(aux_selector[j] != '#'){
    			strncat(s1, &aux_selector[j], 1);
    		}
    	}
    	OverrideById(tree, s1, style_list, f);
    }
    else{
    	if(strstr(aux_selector, ".")){
    		i = 1;
    		if(aux_selector[0] == '.'){
    			a1 = strtok(aux_selector,".");
    			strcpy(s1, a1);
    			OverrideAllByClassname(tree, s1, style_list, f);
    		}
    		else{
	    		a1 = strtok(aux_selector, ".");
	    		a2 = strtok(NULL, ".");
	    		strcpy(s1 ,a1);
	    		strcpy(s2, a2);
	    		OverrideByClassname(tree, s1, s2, style_list, f);
	    	}
    	}
    	if(strstr(aux_selector, ">")){
    		i = 1;
    		a1 = strtok(aux_selector, ">");
    		a2 = strtok(NULL, ">");
     		strcpy(s1, a1);
    		strcpy(s2, a2);
    		OverrideByParent(tree, s1, s2, style_list, f);
    	}
    	if(strstr(aux_selector, " ")){
    		i = 1;
    		a1 = strtok(aux_selector," ");
    		a2 = strtok(NULL," ");
    		strcpy(s1, a1);
    		strcpy(s2, a2);
    		OverrideByAncestor(tree, s1, s2, style_list, f);
    	}

    }
    if(i == 0){
    	OverrideByType(tree, aux_selector, style_list, f);
    }
    free(style_list);
    free(aux_selector);
    free(s1);
    free(s2);
}

/*functie pentru actualizat lista style*/
void appendStyle(TArb tree, char *selector, char *style, FILE *f){
	char *style_list = (char*)calloc(1000,sizeof(char));
    strcpy(style_list, style);
    char *aux_selector = (char*)calloc(50,sizeof(char));
    char *s1 = (char*)calloc(50,sizeof(char));
    char *s2 = (char*)calloc(50,sizeof(char));
    char *a1, *a2;
    int i = 0, j;
    strcpy(aux_selector, selector);
    /*se apeleaza functia corespunzatoare selectorului dat*/
    if(aux_selector[0] == '#'){
    	i = 1;
    	for(j = 0; j <strlen(aux_selector); j++){
    		if(aux_selector[j] != '#'){
    			strncat(s1, &aux_selector[j], 1);
    		}
    	}
    	AppendById(tree, s1, style_list, f);
    }
    else{
    	if(strstr(aux_selector, ".")){
    		i = 1;
    		if(aux_selector[0] == '.'){
    			a1 = strtok(aux_selector, ".");
    			strcpy(s1, a1);
    			AppendAllByClassname(tree, s1, style_list, f);
    		}
    		else{
	    		a1 = strtok(aux_selector, ".");
	    		a2 = strtok(NULL, ".");
	    		strcpy(s1, a1);
	    		strcpy(s2, a2);
	    		AppendByClassname(tree, s1, s2, style_list, f);
	    	}
    	}
    	if(strstr(aux_selector, ">")){
    		i = 1;
    		a1 = strtok(aux_selector, ">");
    		a2 = strtok(NULL, ">");
    		strcpy(s1, a1);
    		strcpy(s2, a2);
    		AppendByParent(tree, s1, s2, style_list, f);
    	}
    	if(strstr(aux_selector, " ")){
    		i = 1;
    		a1 = strtok(aux_selector, " ");
    		a2 = strtok(NULL, " ");
    		strcpy(s1, a1);
    		strcpy(s2, a2);
    		AppendByAncestor(tree, s1, s2, style_list, f);
    	}

    }
    if(i == 0){
    	AppendByType(tree, aux_selector, style_list, f);
    }
    free(style_list);
    free(aux_selector);
    free(s1);
    free(s2);
}

/*functie pentru sters un nod si copii lui*/
void deleteRecursively(TArb tree, char *selector, FILE *f){
    char *aux_selector = (char*)calloc(50, sizeof(char));
    char *s1 = (char*)calloc(50,sizeof(char));
    char *s2 = (char*)calloc(50,sizeof(char));
    char *a1, *a2;
    int i = 0, j;
    strcpy(aux_selector, selector);
    /*se apeleaza functia corespunzatoare selectorului dat*/
    if(aux_selector[0] == '#'){
    	i = 1;
    	 for(j = 0; j < strlen(aux_selector); j++){
            if(aux_selector[j] != '#'){
                strncat(s1, &aux_selector[j], 1);
            }
        }
        int count = 0;
    	int n = DeleteById(&tree, s1, f, &count);
    	if(n == 0){
    		fprintf(f,"Delete recursively failed: no node found for selector %s!\n", selector);
    	}
    }
    else{
    	if(strstr(aux_selector, ".")){
    		i = 1;
    		if(aux_selector[0] == '.'){
    			a1 = strtok(aux_selector, ".");
    			strcpy(s1, a1);
    			int count = 0;
    			int n = DeleteAllByClassname(&tree, s1, f, &count);
    			if(n == 0){
    				fprintf(f,"Delete recursively failed: no node found for selector %s!\n", selector);
    			}
    		}
    		else{
	    		a1 = strtok(aux_selector, ".");
	    		a2 = strtok(NULL, ".");
	    		strcpy(s1, a1);
	    		strcpy(s2, a2);
	    		int count = 0;
	    		int n = DeleteByClassname(&tree, s1, s2, f, &count);
	    		if(n == 0){
    				fprintf(f,"Delete recursively failed: no node found for selector %s!\n", selector);
    			}
	    	}
    	}
    	if(strstr(aux_selector, ">")){
    		i = 1;
    		a1 = strtok(aux_selector, ">");
    		a2 = strtok(NULL,">");
    		strcpy(s1, a1);
    		strcpy(s2, a2);
    		int count = 0;
    		int n = DeleteByParent(&tree, s1, s2, f, &count);
    		if(n == 0){
    			fprintf(f,"Delete recursively failed: no node found for selector %s!\n", selector);
    		}
    	}
    	if(strstr(aux_selector, " ")){
    		i = 1;
    		a1 = strtok(aux_selector, " ");
    		a2 = strtok(NULL, " ");
    		strcpy(s1, a1);
    		strcpy(s2, a2);
    		int count = 0;
    		int n = DeleteByAncestor(&tree, s1, s2, f, &count);
    		if(n == 0){
    			fprintf(f,"Delete recursively failed: no node found for selector %s!\n", selector);
    		}
    	}

    }
    if(i == 0){
    	int count = 0;
    	int n = DeleteByType(&tree, aux_selector, f, &count);
    	if(n == 0){
    		fprintf(f,"Delete recursively failed: no node found for selector %s!\n", selector);
    	}
    }
    free(aux_selector);
    free(s1);
    free(s2);
}

/*functie pentru actualizat ID-urile nodurilor dupa ce au fost sterse noduri*/
void ChangeID(TArb tree){
	TArb aux = tree; 
	TArb sibling, p;
	if(aux){
		for(sibling = aux; sibling != NULL; sibling = sibling->nextSibling){
			int j = 0;
			if(sibling->firstChild && sibling->info->id != NULL){
				for(p = sibling->firstChild; p != NULL; p = p->nextSibling){
					j++;
					strcpy(p->info->id, sibling->info->id);
					strcat(p->info->id, ".");
					char *count = (char*)calloc(30,sizeof(char));
					sprintf(count, "%d", j);
					strcat(p->info->id, count);
					free(count);
				}

			}
			ChangeID(sibling->firstChild);
		}
	}
}


int main(int argc, char *argv[]){
	/*primul argument este fisierul input.html*/
	FILE *in_html = fopen(argv[1], "rt");
	/*al doilea argument este fisierul input*/
	FILE *in = fopen(argv[2], "r");
	/*al treilea argument este fisierul output*/
	FILE *out = fopen(argv[3], "wt");
	char *command = (char*)calloc(1000,sizeof(char));
	if(in_html == NULL){
	  	return -1;
	} 	
	if(in == NULL){
	 	return -1;
	}
	 if(out == NULL){
	 	return -1;
	}

	TArb tree;
	tree = Read(in_html);

	/*cat timp se citesc comenzi din fisierul input se 
	apeleaza functia corespunzatoare comenzii primite*/
	while(fgets(command, 1000, in)){
		char *aux = strtok(command, " =\"\n");
		if(strcmp(aux, "format") == 0){
			PrintTree(tree,0, out);
		}
		if(strcmp(aux, "add") == 0){
			char *id = (char*)calloc(30,sizeof(char));
			char *tag = (char*)calloc(200,sizeof(char));
			char *a = strtok(NULL, " =\"\n");
			char *b = strtok(NULL, " =\"\n");
			strcpy(id, b);
			char *c = strtok(NULL, " =\"\n");
			char *d = strtok(NULL, "\"\n");
			strcpy(tag,d);
			if(a && b && c && d){
				ADD(tree, id, tag, out);
			}
			free(id);
			free(tag);
		}
		if(strcmp(aux, "deleteRecursively") == 0){
			char *selector = (char*)calloc(50,sizeof(char));
			char *a = strtok(NULL, " =\"\n");
			char *b = strtok(NULL, "\"\n");
			strcpy(selector, b);
			if(a && b){
				deleteRecursively(tree, selector, out);
				ChangeID(tree);
			}
			free(selector);
		}
		if(strcmp(aux, "overrideStyle") == 0){
			char *selector = (char*)calloc(50,sizeof(char));
			char *style = (char*)calloc(1000, sizeof(char));
			char *a = strtok(NULL, " =\"\n");
			char *b = strtok(NULL, "=\"\n");
			strcpy(selector, b);
			char *c = strtok(NULL, " =\"\n");
			char *d = strtok(NULL, "\"\n");
			int j;
			for(j = 0; j < strlen(d); j++){
           	 	if(!isspace(d[j]) && d[j] != '\t' && d[j] != '\r'){
                	strncat(style, &d[j], 1);
            	}
        	}
			if(a && b && c && d){
				overrideStyle(tree, selector, style, out);
			}
			free(selector);
			free(style);
		}
		if(strcmp(aux, "appendStyle") == 0){
			char *selector = (char*)calloc(50,sizeof(char));
			char *style = (char*)calloc(1000, sizeof(char));
			char *a = strtok(NULL, " =\"\n");
			char *b = strtok(NULL, "=\"\n");
			strcpy(selector, b);
			char *c = strtok(NULL, " =\"\n");
			char *d = strtok(NULL, "\"\n");
			int j;
			for(j = 0; j < strlen(d); j++){
           	 	if(!isspace(d[j]) && d[j] != '\t' && d[j] != '\r'){
                	strncat(style, &d[j], 1);
            	}
        	}
			if(a && b && c && d){
				appendStyle(tree, selector, style, out);
			}
			free(selector);
			free(style);

		}
	} 

	free(command); 
	fclose(in_html);
	fclose(in);
	fclose(out); 
	Delete(&tree);
	return 0;
}
