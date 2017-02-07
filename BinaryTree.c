#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct bstNode {
    int     count;
    char    *word;
    struct bstNode *left;
    struct bstNode *right;
} bstNode;

bstNode* createNode(char * string) {
        bstNode* tempNode = (bstNode*) malloc(sizeof(bstNode));
    tempNode->word = (char *) malloc(sizeof(string));
    strcpy(tempNode->word, string);
        tempNode->count = 1;
        tempNode->left = NULL;
        tempNode->right = NULL;
        return tempNode;
}

bstNode * insert(bstNode *node, char* word) {
    if (node == NULL) {
        node = createNode(word);
    } else if (strcmp(word, node->word) < 0) {
        node->left = insert(node->left, word);
    } else if (strcmp(word, node->word) > 0) {
        node->right = insert(node->right, word);
    } else {
        node->count++;
    }
    return node;
} 

void displayInOrder(bstNode* root) {
    if (root->left != NULL) { 
        displayInOrder(root->left);
    }
    printf("[Word: %s, count: %d]\n", root->word, root->count);
    if (root->right != NULL) {
        displayInOrder(root->right);
    }   
}

void search(bstNode* root, char* word) {
    if (root != NULL) {
        if (strcmp(word, root->word) == 0) {
            printf("Word found: %s\n", root->word); 
        } else if (strcmp(word, root->word) < 0) {
            search(root->left, word);
        } else if (strcmp(word, root->word) >0) {
            search(root->right, word);
        } 
    } else {
        printf("Word NOT found:\n");
    }
}

void obliterateTree(bstNode * root) {
        if (root->left) {
            obliterateTree(root->left);
        }
        if (root->right) {
            obliterateTree(root->right);
        }
        free(root);
        //free(root->word);
}

void readWords(const char *filename, bstNode *root, int max_number_of_words)
{
    FILE *f = fopen(filename, "rt");
    int i;
    char temp[100]; // assumption words are not longer than 100

    for (i = 0; i < max_number_of_words; ++i)
    {
        // Read a word from the file
        if (fscanf(f, "%s", temp) != 1)
            break;
        // "!=1" checks for end-of-file

        // Allocate memory for the word and add to tree
        insert(root, strdup(temp));
    }
    fclose(f);
}

void outputFile(bstNode *tree) {
  
}
int main() {
    bstNode *root = NULL;
    char userword[50];

    while (1) {
        printf("Enter word to add to tree: ");
        scanf("%s", userword);
        if (strcmp("esc", userword) == 0) {break;}
        root = insert(root, userword);
        displayInOrder(root);
    }
    
    while(1) {
        printf("Lookup word: ");
        scanf("%s", userword);
        if(strcmp("esc", userword) == 0) {break;}
        search(root, userword);
    }
    
    printf("Obliterating tree");

    printf("Address before free: %X\n", (int) root);
    obliterateTree(root);
    
    printf("Address after free: %X\n", (int) root);
    return 1;
}

