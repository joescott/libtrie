#ifndef __TRIE_H__
#define __TRIE_H__

typedef char TRIE_NODE_KEY_T;
typedef void * TRIE_NODE_VALUE_T;

typedef struct trie_node {
    TRIE_NODE_KEY_T  key;
    TRIE_NODE_VALUE_T value;
    struct trie_node * next;
    struct trie_node * prev;
    struct trie_node * children;
    struct trie_node * parent;
}TRIE_NODE_ST;


/**
 * @brief Create trie
 */
TRIE_NODE_ST *trieCreate(void);

/**
 * @brief Search inside trie data structure
 */
TRIE_NODE_ST* trieSearch(TRIE_NODE_ST *root, const TRIE_NODE_KEY_T *key);

/**
 * @brief Add node to trie
 */
void trieAdd(TRIE_NODE_ST **root, TRIE_NODE_KEY_T *key, TRIE_NODE_VALUE_T value);

/**
 * @brief Remove node from trie
 */
void trieRemove(TRIE_NODE_ST **root, TRIE_NODE_KEY_T *key);

/**
 * @brief Destroy trie
 */
void trieDestroy(TRIE_NODE_ST  *root);

#endif
