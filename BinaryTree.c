//BinaryTree.c
/*
 * Binary Tree project for Operating Sytems.
 * @verion: 2/7/17
 * @authors: Brian Sherer, Anthony Ales, 
 *           Alex Jones, Logan Nagel
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct bstNode {
    int     count;
    char    *word;
    struct bstNode *left;
    struct bstNode *right;
} bstNode;

void displayInOrder(bstNode *);

/*
 * Function: createNode
 *-----------------------
 * Creates a node with a char array(string) and NULL
 * children(left and right pointers). Initializes the
 * count to 1 to siginify 1 occurance of this string in 
 * the tree.
 * 
 * string: address of the first char in the string
 *
 * returns: bstNode with variables initialized.
 */
bstNode * createNode(char * string) {
    bstNode* tempNode = (bstNode*) malloc(sizeof(bstNode));
    tempNode->word = (char *) malloc(sizeof(string));
    strcpy(tempNode->word, string);
    tempNode->count = 1;
    tempNode->left = NULL;
    tempNode->right = NULL;
    return tempNode;
}

/*
 * Function: insert
 *-----------------------
 * Inserts a char array(word) into a binary tree based
 * on lexographical value. Creates root of tree if the 
 * node passed in is NULL.
 * 
 * node: address of root of tree.
 * word: address of the first char in the string to be
 *       added
 *
 * returns: the bstNode that is the root of tree
 */
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

/*
 * Function: search
 *-----------------------
 * TODO (function not needed for final product)
 * 
 * root: root of binary tree to search
 *
 * word: address of first char in string
 */
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

/*
 * Function: freeTree
 *-----------------------
 * Frees the memory allocated to the tree.
 * 
 * root: root of three to free
 */
void freeTree(bstNode * root) {
    if (root != NULL) {
    	if (root->left) {
            free(root->left);
        }   
        if (root->right) {
            free(root->right);
        }
        free(root);
        free(root->word);
        printf("Tree freed from memory\n\n");
    }
    root = NULL;
}

/*
 * Reads words from a file and inserts them into a tree in
 * alphabetical order. 
 * Returns root node of the tree.
 */
bstNode * readWordsFromFile(const char *filename, bstNode * node) {
	FILE * file;
	if (node == NULL) {
    	char * wordRead = (char *) malloc(sizeof(char *));
    
    	if (filename != NULL) {
    		file = fopen(filename, "r");
    		// causes a segmentation fault @bug
    		// Read a word from the file
    		while(fscanf(file, "%s", wordRead) != EOF) {
    			if (wordRead == NULL) {
    				break;
    			}
    			node = insert(node, wordRead);
    		}
			fclose(file);
		}
		free(wordRead);
	} // else {Trying to add second file to tree. do nothing}
	return node;
}

FILE * makeOutputFile(bstNode *tree, char * inputfile) {
    
    FILE * output;
    char * index = (char *) malloc(sizeof(char *));
    index = strncat(index, &inputfile[5],2);
    char * outFilename = (char *) malloc(sizeof(char *));
    strcpy(outFilename, "output");
    outFilename = strncat(outFilename, index, 2);    
    outFilename = strncat(outFilename, ".txt", 4);
    
    printf("Output file name: %s\n", outFilename);

    output = fopen(outFilename, "w+");

    free(index);
    free(outFilename);
    return output;
}

void displayInOrderToFile(bstNode * root, FILE * file) {
    if (root->left != NULL) {
        displayInOrderToFile(root->left, file);
    }
    fprintf(file, "%s: %d\n", root->word, root->count);
    if (root->right != NULL) {
        displayInOrderToFile(root->right, file);
    }   	
}

int main(int argc, char **argv) {
    int i;
    bstNode *root = NULL;
    char * inputfile;
    FILE *outputF;

    // iterate over input file arguments
    for (i = 1; i < argc; i++) {

        char *index;
	inputfile = (char *) malloc(sizeof(char *));
        index     = (char *) malloc(sizeof(char *));
	inputfile = argv[i];
	
	if(fopen(inputfile,"r") == NULL){
	    printf("File Not Found\n\n");
            continue;
	}
	
	printf("Reading from File: %s\n", inputfile);

	root = readWordsFromFile(inputfile, root);
	outputF = makeOutputFile(root, inputfile);
	displayInOrderToFile(root, outputF);	
        freeTree(root);
	free(index);	
	root = NULL;
    } 
    exit(0);
}
