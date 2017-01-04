
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

TRIE_NODE_ST* trieSearch(TRIE_NODE_ST *root, const TRIE_NODE_KEY_T *key)
{
	TRIE_NODE_ST *level = root;

	int lvl=0;
	while(1)
	{
		TRIE_NODE_ST *found = NULL;
		TRIE_NODE_ST *curr;

		for(curr = level; curr != NULL; curr = curr->next)
			if(curr->key == *key)
			{
				found = curr;
				lvl++;
				break;
			}

		if(found == NULL)
			return NULL;
	
        printf("Search [%c]\n",*key);

		if(*key == '\0')
		{
		    printf("Found! at level %d\n",lvl);
			return curr;
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

    /** If First Node */
    if(node == NULL) 
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

    /** If Duplicate */
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
        printf("A\n");
    }
    else
    {
        node->next = trieNodeNew(node->parent, *key);
        printf("B\n");
    }

    node->next->prev = node;
    printf("Inserting [%c] as neighbour of [%c] \n",node->next->key, node->key);

    if(*key == '\0')
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


void trieRemove(TRIE_NODE_ST **root, TRIE_NODE_KEY_T *key)
{
    TRIE_NODE_ST *tPtr = NULL;
    TRIE_NODE_ST *tmp = NULL;

    if(NULL == *root || NULL == key)
        return;

    tPtr = trieSearch((*root)->children, key);

    if(NULL == tPtr)
    {
        printf("Key [%s] not found in trie\n", key);
        return;
    }

    printf("Deleting key [%s] from trie\n", key);

    while(1)
    {
        if( tPtr->prev && tPtr->next)
        {
            tmp = tPtr;
            tPtr->next->prev = tPtr->prev;
            tPtr->prev->next = tPtr->next;
            printf("Deleted [%c] \n", tmp->key);
            free(tmp);
            break;
        }
        else if(tPtr->prev && !(tPtr->next))
        {
            tmp = tPtr;
            tPtr->prev->next = NULL;
            printf("Deleted [%c] \n", tmp->key);
            free(tmp);
            break;
        }
        else if(!(tPtr->prev) && tPtr->next)
        {
            tmp = tPtr;
            tPtr->parent->children = tPtr->next;
            printf("Deleted [%c] \n", tmp->key);
            free(tmp);
            break;
        }
        else
        {
            tmp = tPtr;
            tPtr = tPtr->parent;
            tPtr->children = NULL;
            printf("Deleted [%c] \n", tmp->key);
            free(tmp);
        }
    }

    printf("Deleted key [%s] from trie\n", key);
}
 
 
void trieDestroy(TRIE_NODE_ST  *root)
{
    TRIE_NODE_ST *tPtr = root;
    TRIE_NODE_ST *tmp = root;

    while(tPtr)
    {
        while(tPtr->children)
            tPtr = tPtr->children;

        if( tPtr->prev && tPtr->next)
        {
            tmp = tPtr;
            tPtr->next->prev = tPtr->prev;
            tPtr->prev->next = tPtr->next;
            printf("Deleted [%c] \n", tmp->key);
            free(tmp);
        }
        else if(tPtr->prev && !(tPtr->next))
        {
            tmp = tPtr;
            tPtr->prev->next = NULL;
            printf("Deleted [%c] \n", tmp->key);
            free(tmp);
        }
        else if(!(tPtr->prev) && tPtr->next)
        {
            tmp = tPtr;
            tPtr->parent->children = tPtr->next;
            tPtr->next->prev = NULL;
            tPtr = tPtr->next;
            printf("Deleted [%c] \n", tmp->key);
            free(tmp);
        }
        else
        {
            tmp = tPtr;
            if(tPtr->parent == NULL)
            {
                /*Root*/
                free(tmp);
                return;
            }
            tPtr = tPtr->parent;
            tPtr->children = NULL;
            printf("Deleted [%c] \n", tmp->key);
            free(tmp);
        }
    }
}
