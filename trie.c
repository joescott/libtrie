
#include "trie.h"

#include <stdlib.h>

static TRIE_NODE_ST *trieNodeNew(void)
{
    TRIE_NODE_ST *node = (TRIE_NODE_ST *)malloc(TRIE_NODE_ST);

}

TRIE_NODE_ST *trieCreate(void)
{

    root->prev = NULL;
    root->next = NULL;
    root->parent = NULL;
    root->children = NULL;

    root->key = '\0';
    root->value = NULL;

    return root;
}


