//
// Hash Strategy
//
// Hash Table:
//    a data structure that stores the data in array format. Each data element
//    maps to a unique key which is the index of the array. multiple data
//    elements can be kept on the same bucket (index) as an array or linked list.
//    it makes the random search efficient in both performance and storage.
//
// Hashing Table Size:
//    the max size of the hash table, or the number of slots (or buckets).
//    it is usually chosen as a prime number of the form 4i + 3 for an integer
//    i = 0, 1, 2, ... and so on. 
// 
// Hashing Value (or Hashed Key):
//    the index of the hash table, it is produced by the hushing function.
//    the valid vluas are from 0 to (HASH_TABLE_SIZE - 1).
//
// Hashing Function:
//    maps (transforms) the (key) value of the data element to the hash key.
//    there is no standard hash function. most common implemtations include:
//    1) modulus for integers: key % HASH_TABLE_SIZE
//    2) modulus for character: (unsigned)key_ptr % 0xFF
//    3) Folding for integers: (key / 1000 + key % 1000) % HASH_TABLE_SIZE
//    4) folding for character: while(*key_ptr != '\0') { sum += *key_ptr; }
//    5) Digit Analysis-Based for Character String:
//         - Bit Extraction: 
//         - Digit Folding:  (key[0] ^ key[1]) % HASH_TABLE_SIZE
//         - Multiplication: (key * m), m is a rational value.
//    6) Bloom Filter for Rehashing: ((a * key) + b)/q)/n
//         q is large prime, n is a power of 2, 0 < a < q, 0 < b < q.
//
// Hashing Collision:
//    two different keys are hashed to the same hash value.
//    to resolve a hushing collision:
//    - Linear probing with single-slot bucket
//        if the bucket is already occupied, find the next empty bucket,
//        circular index may be needed, allso assumed the table has enough
//        empty buckets.
//    - Hashing with multi-slot bucket
//        also called hashing with buckets, each bucket has multiple slots.
//    - Rehashing
//    - Hashing with chaining
//        the data structure of the hash table is an array of pointers,
//        each pointer points to the head of a chain of records (or nodes).
//        * singly linked list
//        * doubly linked list 
//        * binary search tree
//
// Hashing Algorithm:
//    hasing can be used for checksum and cryptograph
//      - CRC (Cyclic Redundancy Check), eg. CRC-32
//      - MD5 (Merkle-Damgard construction) version 5 
//      - SHA-1 
//      - Blake2, Linux> b2sum
//      - HMAC
//      - many more ...
//
// implementations:
//   the most popular implementation is the hashing with chaining.
//   we could add  
//  

#include <iostream>
#include <cmath>

using namespace std;

class HashChain {
    typedef short    keyType;
    typedef int      dataType;
    typedef unsigned hashValue;

    struct chainNode {
        keyType   key;
        dataType  data;
        chainNode *prev;
        chainNode *next;
    };

    typedef struct chainNode* chainNodePtr;

    unsigned  *chain_table;
    chainNode **hash_table;
    int  hash_table_size;

public:
    HashChain(int table_size);
    ~HashChain();

    hashValue  hash_function(keyType key);
    chainNode* hash_create_chain_node(keyType key, dataType data);
    chainNode* hash_delete_chain_node(keyType key);
    chainNode* hash_insert_chain_node(keyType key, dataType data);
    chainNode* hash_search_chain_node(keyType key);
    void hash_print_table();

    unsigned hash_chain_length(hashValue index) { return chain_table[index]; }
};

HashChain::HashChain(int table_size)
{
    hash_table_size = table_size;
    hash_table = new chainNodePtr[hash_table_size];
    chain_table = new unsigned[hash_table_size];
 
    for (int i = 0; i < hash_table_size; ++i) {
        hash_table[i] = NULL;
        chain_table[i] = 0;
    }
}

HashChain::~HashChain()
{
    for (int i = 0; i < hash_table_size; ++i) {
        chainNode *chain_head = hash_table[i];
        while (chain_head) {
            chainNode *next = chain_head->next;
            delete chain_head;
            chain_head = next;
        }
    }
    delete [] hash_table;
}

HashChain::hashValue
HashChain::hash_function(keyType key)
{
    return (key % hash_table_size);
}

HashChain::chainNode* HashChain::hash_create_chain_node(keyType key, dataType data)
{
    chainNode *node = new chainNode;
    if (node == nullptr) {
        return NULL;    // throw an error
    }

    node->key = key;
    node->data = data;
    node->prev = NULL; 
    node->next = NULL;

    return node;
}

HashChain::chainNode* HashChain::hash_delete_chain_node(keyType key)
{
    hashValue index = hash_function(key);
    chainNode *chain_node = hash_table[index];

    while (chain_node) {
        if (chain_node->key == key) {
            break;
        }
        chain_node = chain_node->next;
    }
    if (chain_node == NULL) {
        return NULL;
    }

    if (chain_node == hash_table[index]) {
        hash_table[index] = hash_table[index]->next;
    }
    else {
        chain_node->prev->next = chain_node->next;
    }
    delete chain_node;
    chain_table[index] -= 1;

    return hash_table[index];
}

HashChain::chainNode* HashChain::hash_insert_chain_node(keyType key, dataType data)
{
    hashValue index = hash_function(key);
    chainNode* chain_head = hash_table[index];

    chainNode* new_node = hash_create_chain_node(key, data);
    if (new_node == NULL) {
        return NULL;    // throw an error
        // exit (-1);
    }

    if (chain_head != NULL) {
        new_node->next = chain_head;
        chain_head->prev = new_node;
    }
    hash_table[index] = new_node;
    chain_table[index] += 1;
}

HashChain::chainNode* HashChain::hash_search_chain_node(keyType key)
{
    hashValue index = hash_function(key);
    chainNode* chain_node = hash_table[index];

    if (chain_node == NULL) {
        return NULL;
    }

    while (chain_node) {
        if (chain_node->key == key) {
            return chain_node;
        }
        chain_node = chain_node->next;
    }
    return NULL;
}

void HashChain::hash_print_table()
{
    for (int i = 0; i < hash_table_size; ++i) {
        chainNode *node = hash_table[i];
        while (node) {
            cout.width(4); cout << HashChain::hash_function(node->key) << ": \t" << HashChain::hash_chain_length(HashChain::hash_function(node->key));
            cout << "  key = " << node->key << " \t"<< "data = " << node->data << "\t" << " prev = " << node->prev << "\t next = " << node->next << endl;
            node = node->next;
        }
    }
}

int main()
{
    int i = 2;
    int array_size = pow(4, i);
    int table_size = 4 * i + 3;
    long B[array_size];

    cout << "Generate Array: size = " << array_size << endl;
    for(int i = 0; i < array_size; ++i) { B[i] = rand() % (array_size * 10); }
    for(int i = 0; i < array_size; ++i) { cout.width(4); cout << B[i] << ", ";  if ((i + 1) % 20 == 0) { cout << endl; } } cout << endl;

    cout << "Create Hash Table: size = " << table_size << endl;
    HashChain hc(table_size);

    for (int i = 0; i < array_size; ++i) {
        hc.hash_insert_chain_node(B[i], B[i]);
    }
    hc.hash_print_table();

    for (int i = 0; i < array_size; ++i) {
        if ( hc.hash_search_chain_node(B[i]) == NULL ) {
            cout << "Element " << B[i] << " is not found" << endl;
        }
        cout << i << " ptr " << hc.hash_search_chain_node(B[i]) << " +2 " << hc.hash_search_chain_node(B[i]) + 2 << endl;
    }

    for (int i = 0; i < array_size; ++i) {
        if ( hc.hash_delete_chain_node(B[i]) == NULL ) {
            cout << "Delete Element " << B[i] << ", this bucket is empty" << endl;
        }
        else {
            cout << "Delete Element " << B[i] << ": " << endl;
        }
        // hc.hash_print_table();
        // cout << endl;
    }

     return 0;
}
