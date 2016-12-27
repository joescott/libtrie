#include <stdlib.h>
#include <stdio.h>
#include "trie.h" 


int main(int argc, char **argv) 
{
    TRIE_NODE_ST *trie = trieCreate();
    trieAdd(&trie,"test",NULL);
    trieAdd(&trie,"testa",NULL);
    trieAdd(&trie,"fest",NULL);
	return EXIT_SUCCESS;
}

