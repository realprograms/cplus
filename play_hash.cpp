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
//        the hashing performance degrades when the hashing table is above 
//        half full. it is better to rehashing, to increase the table size.
//        the limit of rehashing is when the load factor is about 0.75.
//        the load factor m/n: 
//              - n is the expected number of entries or 
//                the size of the array for each hash value;
//              - m is the average entries of each hash values.
//    - Hashing with chaining
//        the data structure of the hash table is an array of pointers,
//        each pointer points to the head of a chain of records (or nodes).
//        * singly linked list
//        * doubly linked list 
//        * binary search tree
//
// Hashing Algorithms:
//    generates the fixed length hashing values, and
//    are usually used for checksum and cryptograph.
//      - CRC (Cyclic Redundancy Check), e.g. CRC-32,  see checksum.cpp
//      - MD5 (Merkle-Damgard construction) version 5,
//      - SHA-1 
//      - Blake2, Linux> b2sum
//      - HMAC
//      - many more ...
//
// implementations:
//   - the most popular implementation is the hashing with chaining.
//   - this implementation does not handle any memory shortage.
//   - this implementation is not thread safe and not multi-core safe.
//  

#include <iostream>
#include <cmath>

using namespace std;

typedef short     keyType;
typedef long      dataType;
typedef unsigned  hashValue;

/* use doubly linked list for easy insertion and deletion.
 * + no null node is allowed
 */
struct ChainNode {
    keyType   key;
    dataType  data;
    ChainNode *prev;
    ChainNode *next;

    ChainNode(keyType k, dataType d) : key(k), data(d), prev(NULL), next(NULL) {}
};

typedef ChainNode* ChainNodePtr;

/* Hash Table with Chain
 * - use the doubly linked list for the chain (hash collisions)
 */
class HashChain {
    int  table_size;
    int  total_nodes;
    ChainNode **hash_table;
    // unsigned  *chain_table;
public:
    HashChain(int table_size);
    ~HashChain();

    hashValue  hash_function(keyType key);
    ChainNode* remove(keyType key);
    ChainNode* insert(keyType key, dataType data);
    ChainNode* search(keyType key);

    int size()  { return table_size; }
    int total() { return total_nodes; }
    int count(hashValue index);

    void  print_node(ChainNode* node);
    void  print_table();

    // int  chain_length(hashValue index) { return chain_table[index]; }
};

/* constructor:
 * allocated the memory for the hash table and 
 * intialize the hash table.
 */
HashChain::HashChain(int table_size)
{
    this->table_size = table_size;
    this->total_nodes = 0;
    hash_table = new ChainNodePtr[table_size];
    // chain_table = new unsigned[table_size];
 
    for (int i = 0; i < table_size; ++i) {
        hash_table[i] = NULL;
        // chain_table[i] = 0;
    }
}
/* deconstructos
 * free the memory of all the nodes, then the table itself.
 */
HashChain::~HashChain()
{
    for (int i = 0; i < table_size; ++i) {
        ChainNode *chain_head = hash_table[i];
        while (chain_head) {
            ChainNode *next = chain_head->next;
            delete chain_head;
            chain_head = next;
        }
    }
    delete [] hash_table;
}
/* calculate the hashing value from the key
 * - the simplest hashing: % (table_size)
 * - negitive hash value cannot be used as table index.
 */
hashValue HashChain::hash_function(keyType key)
{
    return (unsigned)key % table_size;
}
/* insert()
 * - add an ChainNode to the hash table base on its hash key
 * - add the new node at the head of the chain
 */
ChainNode* HashChain::insert(keyType key, dataType data)
{
    hashValue index = hash_function(key);
    ChainNode* chain_head = hash_table[index];
    ChainNode* new_node = new ChainNode(key, data);

    if (chain_head != NULL) {
        new_node->next = chain_head;
        chain_head->prev = new_node;
    }
    hash_table[index] = new_node;
    ++total_nodes;
    // chain_table[index] += 1;
}
/* remove()
 * - find the node by the key
 * - return NULL if the node is not found
 * - remove the node from the doubly linked list
 * - free the node memory
 * - return the head pointer of the chain
 */
ChainNode* HashChain::remove(keyType key)
{
    hashValue index = hash_function(key);
    ChainNode *chain_node = hash_table[index];

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
        if (hash_table[index] != NULL) {
            hash_table[index]->prev = NULL;
        }
    }
    else {
        chain_node->prev->next = chain_node->next;
        if (chain_node->next != NULL) {
            chain_node->next->prev = chain_node->prev;
        }
    }
    delete chain_node;
    // chain_table[index] -= 1;
    --total_nodes;

    return hash_table[index];
}
/* search()
 * - search a node by key, return the node
 * - return NULl if the node (key) is not found.
 */
ChainNode* HashChain::search(keyType key)
{
    hashValue index = hash_function(key);
    ChainNode* chain_node = hash_table[index];

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
/* count the nodes linked for the hash value
 */
int HashChain::count(hashValue index)
{
    int c = 0;
    ChainNode* node = hash_table[index];
    while (node) { 
        ++c; 
        node = node->next; 
    }
    return c;
}
/* print one node in one line, the column includes:
 *   hash value, key value, data value, prev pointer, next pointer
 */
void  HashChain::print_node(ChainNode* node)
{
    cout.width(4); cout << right << hash_function(node->key);   // chain_length()
    cout << "  key = "; cout.width(8); cout << left << node->key;
    cout << " data = "; cout.width(8); cout << left << node->data; 
    cout << " prev = "; cout.width(10); cout << left << node->prev;
    cout << " next = "; cout << left << node->next << endl;
}
/* print the hash table, each row is one hash entry, the columns are:
 *   hash value, key value, data value, prev pointer, next pointer
 */
void HashChain::print_table()
{
    for (int i = 0; i < table_size; ++i) {
        ChainNode *node = hash_table[i];
        while (node) {
            print_node(node);
            node = node->next;
        }
    }
}
/* testing driver code
 * + take one argument as i in:
 *   - pow(4, i) which is total number of nodes for testing.
 *   - 4i + 3 which the size of the hash table to be created.
 */
#include <algorithm>

int main(int argc, char* argv[])
{
    int i = 2;
    if ((argc > 1) && ((i = atoi(argv[1])) < 0)) {
            return -1;
    }
    int array_size = pow(4, i);
    int table_size = 4 * i + 3;
    long B[array_size];

    cout << "Generate Array: size = " << array_size << endl;
    for(int i = 0; i < array_size; ++i) { B[i] = rand() % (array_size * 10); }
    for(int i = 0; i < array_size; ++i) { cout.width(4); cout << B[i] << ", ";  if ((i + 1) % 20 == 0) { cout << endl; } } cout << endl;

    HashChain hc(table_size);
    cout << "Create Hash Table: size = " << hc.size() << endl;
    for (int i = 0; i < array_size; ++i) {
        hc.insert(B[i], B[i]);
    }
    hc.print_table();

    cout << "Chain Lengths: " << endl;
    int total = 0;
    for (int i = 0; i < hc.size(); ++i) {
        // cout.width(4); cout << right << i << ":  " << hc.count(i) << endl;
        total += hc.count(i);
    }
    cout << "counting total = " << total << ", hash table total: " << hc.total() << endl;

    long x = B[array_size/2];
    cout << "Search Nodes: " << x;
    hc.search(x) ? cout << " is found" : cout << " is not found"; cout << endl;
    x = -13;
    cout << "Search Nodes: " << x;
    hc.search(x) ? cout << " is found" : cout << " is not found"; cout << endl;

    sort(B, B + array_size);    // re-order the array
    cout << "Re-order (sort) Array: " << endl;
    for(int i = 0; i < array_size; ++i) { cout << B[i] << ", ";  if ((i + 1) % 20 == 0) { cout << endl; } } cout << endl;

    cout << "Remove Nodes (one at time): " << endl;;
    for (int i = 0; i < array_size; ++i) {
        hc.remove(B[i]);
        cout << B[i] << " (" << hc.count(hc.hash_function(B[i])) << "), ";
        if ((i + 1) % 10 == 0) { cout << endl; }
    }
    cout << endl;

    return 0;
}
