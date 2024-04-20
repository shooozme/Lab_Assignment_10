#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie
{	
    int isWord; //0/1
    struct trie* next[26];
};

struct Trie *createTrie();

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{ 
    //find the length of the passed word
    int len = strlen(word);
    //iterate through the word, and find the indivdual indexes
    for(int i = 0; i < len; i++) {
        int nextWord = word[i] - 'a';

        //if at the last index of the string increase isWord, and return
        if (i == len) {
            pTrie->isWord++;
            return;
        }

        //if the index has no data, a new node must be created
        if(pTrie->next[nextWord] == NULL)  {
            pTrie->next[nextWord] = createTrie();
        }

        insert(pTrie->next[nextWord], word);
    }

}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
    int len = strlen(word);

    for(int i = 0; i < len; i++) {
        int nextWord = word[i] - 'a';

        if (i == len) {
            i = i - 1;
            return pTrie->isWord;
        }

    }

}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
    //if the whole tree is NULL return
    if(pTrie == NULL) {
        return NULL;
    }

    //iterate through each node and call the function on any valid nodes
    for (int i = 0; i < 26; i++) {
        if(pTrie->next[i] != NULL)
        {
            deallocateTrie(pTrie->next[i]);
        }
    }
    //free the whole struct;
    free(pTrie);
    //required to prevent an error from being thrown
    pTrie = NULL;
    return pTrie;      
}

// Initializes a trie structure
struct Trie *createTrie()
{   
    //creates a struct, and sets the flag to false
    struct Trie* newNode = malloc(sizeof(struct Trie));
     
    newNode->isWord = 0;

    //sets each pointer to NULL
    for (int i = 0; i < 26; i++) {
        newNode->next[i] = NULL;
    }

    //returns the new node
    return newNode;
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{   
    //handles file input
    FILE *inputFile = fopen("dictionary-1.txt", "r");
    int n;
    fscanf(inputFile, "%d", &n);
    char word[21];

    //iterate through the entire file and save each word an array
    for(int i; i < n; i++) {
        fscanf(inputFile, "%s", word);
        pInWords[i] = (char*)malloc(sizeof(char*));
        strcpy(pInWords[i], word);
    }

    return n;
}

int main(void)
{
	char *inWords[256];
	
	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary-1.txt", inWords);
	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
	}
	
	struct Trie *pTrie = createTrie();
	for (int i=0;i<numWords;i++)
	{
		insert(pTrie, inWords[i]);
	}
	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i=0;i<5;i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");
	return 0;
}