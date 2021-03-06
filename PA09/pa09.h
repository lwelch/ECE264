#ifndef PA09_H
#define PA09_H

typedef struct _huffnode {
    int value; 
    struct _huffnode * left;
    struct _huffnode * right;
} HuffNode;

typedef struct _stack {
    struct _stack * next; /* struct snode * below */
    HuffNode * node; /* TreeNode * tn*/
} Stack;

#endif

HuffNode * NodeCreate(int data);
Stack * Push(Stack *st, HuffNode * tree);
Stack * Pop(Stack * st);
HuffNode * TreeCreate(FILE *fh);
void HuffPrintToFile(HuffNode * base, FILE * savefile);
void TreeDelete(HuffNode *base);
HuffNode * bitCreate(FILE *fh);
