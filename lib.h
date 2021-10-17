/*Purcareanu Corina
311CB*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#ifndef _TREE_
#define _TREE_	

typedef struct TNodAttr {
	char *name;
	char *value;
	struct TNodAttr *next;
} TNodAttr, *TAttr;

typedef struct TNodInfo {
	char *type;
	char *id;
	TAttr style;
	TAttr otherAttributes;
	int isSelfClosing;
	char *contents;
} TNodInfo, *TInfo;

typedef struct TNodArb {
	TInfo info;
	struct TNodArb *nextSibling;
	struct TNodArb *firstChild;
} TNodArb, *TArb;

TArb CreateNode();
TAttr createAttrNode(char *n, char *v);
void createStyleList(char *v, TArb node);
void DestroyAttr(TAttr *list);
void DestroyNode(TArb *node);
void Delete(TArb *node);

#endif /*_TREE_*/

#ifndef _STATE_
#define _STATE_
typedef enum
{
    PARSE_ERROR             = 0,
    PARSE_CONTENTS          = 1,
    PARSE_OPENING_BRACKET   = 2,
    PARSE_TAG_TYPE          = 3,
    PARSE_CLOSING_TAG       = 4,
    PARSE_REST_OF_TAG       = 5,
    PARSE_ATTRIBUTE_NAME    = 6,
    PARSE_ATTRIBUTE_EQ      = 7,
    PARSE_ATTRIBUTE_VALUE   = 8,
    PARSE_SELF_CLOSING      = 9,
} TParseState;

TParseState Interpret(TParseState currentState, char c);

#endif /*_STATE_*/

#ifndef _STACK_QUEUE_
#define _STACK_QUEUE_

/*indica faptul ca Stiva/Coada nu contine elemente*/
#define Vida(T) ((*T) == NULL)
/*tipul functiei de comparare folosita pentru sortari*/
typedef int (*TFCmp)(void*, void*);

typedef struct celula
{
	void* info;							
	struct celula *urm;				
} TCelula, *TElem, **TStiva, **TCoada;

TStiva InitS();
TCoada InitQ();
void Push(TStiva s, void *x);
void Enqueue(TCoada q, void *x);
void *Pop(TStiva s);
void *Dequeue(TCoada q);
void DistrS(TStiva s);
void DistrQ(TCoada q);

#endif /*_STACK_QUEUE_*/

#ifndef _FUNCTIONS_
#define _FUNCTIONS_

void OverrideById(TArb tree, char *id, char *style, FILE *f);
void OverrideByType(TArb tree, char *type, char *style, FILE *f);
void OverrideByClassname(TArb tree, char *type, char *classname, char *style, FILE *f);
void OverrideAllByClassname(TArb tree, char *classname, char *style, FILE *f);
void OverrideByParent(TArb tree, char *parent_name, char *child_name, char *style, FILE *f);
int OverrideByAncestorAux(TArb tree, char *child_name, char *style, int *i);
void OverrideByAncestor(TArb tree, char *ancestor_name, char *child_name, char *style, FILE *f);
void AppendById(TArb tree, char *id, char *style, FILE *f);
void AppendByType(TArb tree, char *type, char *style, FILE *f);
void AppendByClassname(TArb tree, char *type, char *classname, char *style, FILE *f);
void AppendAllByClassname(TArb tree, char *classname, char *style, FILE *f);
void AppendByParent(TArb tree, char *parent_name, char *child_name, char *style, FILE *f);
int AppendByAncestorAux(TArb tree, char *child_name, char *style, int *i);
void AppendByAncestor(TArb tree, char *parent_name, char *child_name, char *style, FILE *f);
int DeleteById(TArb *tree, char *id, FILE *f, int *i);
int DeleteByType(TArb *tree, char *type, FILE *f, int *i);
int DeleteByClassname(TArb *tree, char *type, char *classname, FILE *f, int *i);
int DeleteAllByClassname(TArb *tree, char *classname, FILE *f, int *i);
int DeleteByParentAux(TArb *tree, char *child, int *i);
int  DeleteByParent(TArb *tree, char *parent, char *child, FILE *f, int *i);
int DeleteByAncestorAux(TArb *tree, char *child, int *i);
int DeleteByAncestor(TArb *tree, char *ancestor, char *child, FILE *f, int *i);

#endif /*_FUNCTIONS_*/