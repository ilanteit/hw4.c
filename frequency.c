#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define NUM_LETTERS ((int)26)
typedef enum {FALSE=0, TRUE=1} boolean;
typedef struct node {
    char letter;
    long unsigned int count;
    boolean endWord ;
    struct node* children[NUM_LETTERS];
} node;
struct node* getnode()
{
    struct node* node = (struct node*)malloc(sizeof(struct node));
    // init all the children to NULL
    for (int i = 0; i < NUM_LETTERS; i++) {
        node->children[i] = NULL;
    }
    node ->endWord = FALSE;
    return node;
}

void insertWord (node **root, char *word ) {
if (word[0]==' '||word[0]=='\n'||word[0]=='\t')  return;    
int len = strlen(word);
    node* parentNode = *root;
    for (int i = 0; i < len; i++) {
        char c = word[i];
	if (c>='a' &&c<='z'){
        int index = c - 'a';

        if (parentNode->children[index] == NULL) {
            parentNode->children[index] = getnode();
            parentNode = parentNode->children[index];

        }
	 else { 
            parentNode = parentNode->children[index]; //go to the next Node
        } 
        parentNode->letter = c;

}

    }
    parentNode->endWord = TRUE;
	parentNode->count++;

}

void lowerCase (char* word){
    
    for (int i=0; i<strlen(word); i++){
        word[i] = tolower(word[i]);
    }

}


void printDefult ( node *parentNode, char *str, int level) {
    if (parentNode->endWord==TRUE) {
        str[level] = '\0';
        printf("%s \t %ld \n", str, parentNode->count);

    }
    for (int i = 0; i < NUM_LETTERS; i++) {
        if (parentNode->children[i] !=NULL) {
            str[level] = i + 'a';
            printDefult(parentNode->children[i], str, level + 1);
        }
    }
}



void printReverse( node *parentNode, char *str, int level) {

    for (int i = NUM_LETTERS-1; i > -1; i--) {
        if (parentNode->children[i]) {
            str[level] = i + 'a';
            printReverse(parentNode->children[i], str, level + 1);
        }
    }
   if (parentNode->endWord==TRUE) {
        str[level] = '\0';
        printf("%s \t %ld \n", str, parentNode->count);

    }



}
// returns True if given node has any children
int haveChildren(node* curr)
{
    for (int i = 0; i < NUM_LETTERS; i++)
        if (curr->children[i])
            return TRUE;	

    return FALSE;
}

// destroy the tree from the memory 

void delete (node *toDelete){


    for (int i=0; i<NUM_LETTERS; i++){
        if (toDelete->children[i])
            delete(toDelete->children[i]);
    }
    free(toDelete);
}





int main(int argc,char *argv[] )
{
    node* head = getnode(); 
    char c;
    size_t n;
    char *word;
    n = 0;
    word = (char *)malloc(sizeof(char));
    word[n++] = '\0';

    
    c = getchar();
    int i=0;
    while (c != EOF && i<1000000) {
        while ( (c != EOF && c!=' '&& c!='\t'&& c != '\n')&& i<10000000) {
            word = realloc(word, (n + 1)*sizeof(char));

            word[n-1] = c;
            word[n++] = '\0';
            c = getchar();
            i++;
        } // end while of word
        i++;
        lowerCase(word); 
        insertWord(&head, word); 
        free(word);
        c = getchar();
	    if (c==EOF) break;

        n=1;
        word = (char *)malloc(sizeof(char));

        word[0] = c;

    } 
    // end of  file
  

    char* str =(char *)malloc(sizeof(char));
    if (argc==1){
        printf("Defult \n");
        printDefult(head, str, 0);
}
    else if(argv[1][0]=='r'){
        printf("Reverse \n");
     	printReverse(head, str, 0);

}
    free (str);
    delete(head);
    
}
