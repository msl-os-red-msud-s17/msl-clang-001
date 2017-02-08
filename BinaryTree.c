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
 * Function: displayInOrder
 *-----------------------
 * TODO (Function might change)
 * 
 * root: address of the root of the binary tree
 */
void displayInOrder(bstNode* root) {
    if (root->left != NULL) { 
        displayInOrder(root->left);
    }
    printf("[Word: %s, count: %d]\n", root->word, root->count);
    if (root->right != NULL) {
        displayInOrder(root->right);
    }   
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

// get index of filename
char * getIndexOf(char * filename) {
    
    char * index;
    index = (char *) malloc(sizeof(char));
    int i = 0;
    
    if (filename != NULL) {
        while(filename[i] != '\0') {
            if (filename[i] >= 48 && filename[i] <= 57) {
            	index = strncat(index, &filename[i], 1);
            }
            i++;
        }      
    }
    //free(index);
    return index;
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

void outputFile(bstNode *tree, char *index, FILE *output) {
  fprintf(output,"The fucking output file");
  //Needs to be changed to correct format
  //Return file for main?

       
}

FILE * makeOutputFile(bstNode *tree, char * inputfile) {
    
    FILE * output;
    //char * index = getIndexOf(inputfile);
    char * index = (char *) malloc(sizeof(char *));
    char * outFilename = (char *) malloc(sizeof(char *));
    strcpy(outFilename, "myoutput");
    outFilename = strncat(outFilename, index, 2);    
    //outFilename = strncat(outFilename, ".txt", 4);
    
    printf("index: %s\n", index);
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
    char * index;
    FILE *outputF;

    // iterate over input file arguments
    for (i = 1; i < argc; i++) {

	inputfile = (char *) malloc(sizeof(char *));
        index = (char *) malloc(sizeof(char *));
	inputfile = argv[i];
	
	if(fopen(inputfile,"r") == NULL){
		printf("File Not Found\n");
		exit(0);
	}

        //******Needs to be put in func? Combine the two?
	//outputF = fopen("Test01.txt","w+");
	//outputFile(root,index,outputF);
        //SHould look like ThisV
        //outputF = outputFile(root,index);
        //*******************************

	printf("argument %d: %s\n", i, inputfile);
	index = strncat(index,&inputfile[5],2);

	printf("Index %d: %s\n", i, index);
	
	printf("Reading from File: %s\n", inputfile);

	root = readWordsFromFile(inputfile, root);
	displayInOrder(root);

	outputF = makeOutputFile(root, inputfile);

	//format output file
	displayInOrderToFile(root, outputF);	

	freeTree(root);
	//free(index);	
	root = NULL;
    } 

    exit(0);
}
