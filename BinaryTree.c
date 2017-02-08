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

<<<<<<< HEAD
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
=======
>>>>>>> arales
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
<<<<<<< HEAD
        if (root->left) {
            free(root->left);
        }   
        if (root->right) {
            free(root->right);
        }
        free(root);
        free(root->word);
        printf("Tree freed from memory\n");
    }
}

/*
 * Function: readWords
 *-----------------------
 * TODO (Function might change/obsolete)
 */
=======
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


>>>>>>> arales
void readWords(const char *filename, bstNode *root, int max_number_of_words) {
    
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

<<<<<<< HEAD
/*
 * Function:readWordsFromFile
 *------------------------
 * Reads words from a file and inserts them into a tree in
 * alphabetical order.
 *
 * filename: file of words you want to convert
 * node: root of binary tree
 * 
 * returns: root node of the tree.
 */
bstNode * readWordsFromFile(const char *filename, bstNode * node) {
    if (node == NULL) {
        char * wordRead = (char *) malloc(sizeof(char *));
        
        if (filename != NULL) {
            FILE *file = fopen(filename, "rt");
            
            // Read a word from the file
            while(fscanf(file, "%s", wordRead) != EOF) {
                if (wordRead == NULL) {
                    break;
                }
            node = insert(node, wordRead);
            }
            free(wordRead);
            fclose(file);
        }
    } // else {Trying to add second file to tree. do nothing}
    
    return node;
}

void outputFile(bstNode *tree) {
  
}

int main(int argc, char *argv[]) {
  int i;
 
  for (i = 1; i < argc; i++) {
=======
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
        free(index);
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

		if (file != NULL) { // causes a segmentation fault @bug

    			// Read a word from the file
    			while(fscanf(file, "%s", wordRead) != EOF) {
				if (wordRead == NULL) {break;}

					node = insert(node, wordRead);
    			}
			//free(wordRead);
    			//fclose(file);
		} else if (file == NULL) { // {file doesn't exist}
			printf("HEY I SHOULD BE HERE");
		}

		fclose(file);

    	}

	free(wordRead);

    } // else {Trying to add second file to tree. do nothing}

    return node;
}

void outputFile(bstNode *tree, int index) {
  
}

int main(int argc, char **argv) {
>>>>>>> arales
    bstNode *root = NULL;
    char userword[50];
    char * wordFromFile = (char *) malloc(sizeof(char *));

    /*
    while (1) {
        printf("Enter word to add to tree ('esc' to stop): ");
        scanf("%s", userword);
        if (strcmp("esc", userword) == 0) {break;}
        root = insert(root, userword);
        displayInOrder(root);
    }
<<<<<<< HEAD
    */
 
    printf("Reading from file...\n");
    root = readWordsFromFile(argv[i], root);
=======
 
    printf("Reading from file...\n");
    root = readWordsFromFile("input04.txt", root);
>>>>>>> arales

    displayInOrder(root);
    free(wordFromFile);
    freeTree(root);
<<<<<<< HEAD
  }
  exit(0);
=======
    //free(root);
    	
    root = NULL;
    printf("READING SECOND FILE....\n");
    root = readWordsFromFile("input04.txt", root);
    displayInOrder(root);
    freeTree(root);
    */

    char * inputfile;
    char * index;

    // iterate over input file arguments
    for (int i = 1; i < argc; i++) {

	inputfile = (char *) malloc(sizeof(char *));
        index = (char *) malloc(sizeof(char *));
	inputfile = argv[i];
	printf("argument %d: %s\n", i, inputfile);
	index = getIndexOf(inputfile);	

	printf("Index %d: %s\n", i, index);
	
	printf("Reading from File: %s\n", inputfile);

	root = readWordsFromFile(inputfile, root);
	displayInOrder(root);
	freeTree(root);
	
	root = NULL;
    } 

    exit(0);
>>>>>>> arales
}



































