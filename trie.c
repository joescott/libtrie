
#include "trie.h"

#include <stdlib.h>
#include <stdio.h>

static TRIE_NODE_ST *trieNodeNew(TRIE_NODE_ST *parent, 
        const TRIE_NODE_KEY_T key)
{
    TRIE_NODE_ST *node = (TRIE_NODE_ST *)malloc(sizeof(TRIE_NODE_ST));

    node->parent = parent;
    node->key = key;

    return node;
}

TRIE_NODE_ST *trieCreate(void)
{
    TRIE_NODE_ST *root = trieNodeNew(NULL,'\0');

    root->prev = NULL;
    root->next = NULL;
    root->children = NULL;

    root->value = NULL;

    return root;
}

void trieDestroy(TRIE_NODE_ST  *root)
{
    free(root);
}

TRIE_NODE_ST* trieSearch(TRIE_NODE_ST *root, const TRIE_NODE_KEY_T *key)
{
	TRIE_NODE_ST *level = root;
	TRIE_NODE_ST *pPtr = NULL;


	int lvl=0;
	while(1)
	{
		TRIE_NODE_ST *found = NULL;
		TRIE_NODE_ST *curr;

		for (curr = level; curr != NULL; curr = curr->next)
		{
			if (curr->key == *key)
			{
				found = curr;
				lvl++;
				break;
			}
		}

		if (found == NULL)
			return NULL;

		if (*key == '\0')
		{
			pPtr = curr;
			return pPtr;
		}

		level = found->children;
		key++;
	}
}

void trieAdd(TRIE_NODE_ST **root, TRIE_NODE_KEY_T *key, TRIE_NODE_VALUE_T value)
{
	TRIE_NODE_ST *node;
	if(*root == NULL)
		return;
	node = (*root)->children;

	if(node == NULL) /** First Node */
	{
		for(node = *root;; node = node->children, key++)
		{
			node->children = trieNodeNew(node, *key);
			printf("Inserting: [%c]\n",node->children->key);
			if(*key == '\0')
				break;
		}
		return;
	}

	if(trieSearch(node, key))
	{
		printf("Duplicate!\n");
		return;
	}


	while(*key != '\0')
	{
		if(*key == node->key)
		{
			key++;
			printf("Traversing child: [%c]\n",node->children->key);
			node = node->children;
		}
		else
			break;
	}

	while(node->next)
	{
		if(*key == node->next->key)
		{
			key++;
			trieAdd(&(node->next), key, value);
			return;
		}
		node = node->next;
	}

	if(*key == '\0')
	{
		node->next = trieNodeNew(node->parent, *key);
	}
	else
	{
		node->next = trieNodeNew(node->parent, *key);
	}

	node->next->prev = node;
	printf("Inserting [%c] as neighbour of [%c] \n",node->next->key, node->key);

	if(!(*key))
		return;

	key++;

	for(node = node->next; ; node = node->children, key++)
	{
		node->children = trieNodeNew(node, *key);
		printf("Inserting: [%c]\n",node->children->key);
		if(*key == '\0')
			break;
		node->children = trieNodeNew(node, *key);
	}

	return;
}
