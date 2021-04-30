// Trie
//   it is a variant of an m-ary tree data structure, also called prefix tree.
//   it is often used to represent a set of words in which each node stores
//   a letter, a branch is a complete words end with null node (or * node).
//   it has good compromise between running time and memory.
//   it was first recommended by René de la Briandais in 1959.
//
//   this implementation:
//     - support English words, 26 lower case letters
//     - the variable 'letter' in TrieNode can be omitted,
//       just use children's index: letter = index + 'a'.
//     - the variable 'complete' in TrieNode may also be omitted,
//       an 'END' child could be added to indicate the end of a word.
//     - may use the linked list to represent children to save memory.
//

#include <iostream>
#include <string>

using namespace std;

const int   DEFAULT_CHILDREN = 26;  // maximum of English letters
const int   BASE_LETTER = 'a';      //
const char  ROOT = '@';             // 0x0D, indicate the root of the trie    
const char  END  = '\0';            // 0x20, indicate the complete of a valid word

__inline__ static 
char lower_letter(char c) { if (c <= 'Z') return c + 32; }

typedef char  letterType;           // ASCII

struct TrieNode {
    TrieNode *children[DEFAULT_CHILDREN];
    letterType letter;
    bool complete;
    char pad[2];        // align to 4-byte
public:
    TrieNode() : letter(END), complete(false)  { for (int i = 0; i < DEFAULT_CHILDREN; i++) { children[i] = nullptr; } }
    TrieNode(char c) : letter(c), complete(false)  { for (int i = 0; i < DEFAULT_CHILDREN; i++) { children[i] = nullptr; } }
    // ~TrieNode();
};

class TrieTree {
    int number_children;
    TrieNode *trie_root;
    void  free(TrieNode **node);
public:
    TrieTree() : trie_root(new TrieNode(ROOT)), number_children(DEFAULT_CHILDREN) {}
    TrieTree(int n) : trie_root(new TrieNode(ROOT)), number_children(n) {}
    ~TrieTree() { free(&trie_root); number_children = 0; }

    void insert(TrieNode *node, string word);
    void insert(string word) { insert(trie_root, word); }
    bool remove(TrieNode **node, string word);
    bool remove(string word) { remove(&trie_root, word); }
    bool search(TrieNode *node, string word);
    bool search(string word) { search(trie_root, word); };

    int  children(TrieNode *node);
    bool empty();

    void print(TrieNode *root, int indent);
    void print() { print(trie_root, 0); }
};

/* free()
 * delete the node and all its children (every node below).
 */
void TrieTree::free(TrieNode **node)
{
    while (*node) {
        for (int i = 0; i < number_children; ++i) {
            free( &(*node)->children[i] );
            delete *node;
            *node = nullptr;
        }
    }
}
/* insert()
 * 
 */ 
void TrieTree::insert(TrieNode *node, string word)
{
    TrieNode **walk = &node;

    for (int i = 0; i < word.size(); i++)
    { 
        int index = lower_letter(word[i]) - BASE_LETTER;
        walk = &(*walk)->children[index];
        if (!*walk) {
            *walk = new TrieNode(word[i]);
        }
    } 
    (*walk)->complete = true;
}
/* search()
 *
 */
bool TrieTree::search(TrieNode *node, string word)
{
    TrieNode *walk = node;

    for (int i = 0; i < word.size(); ++i) {
        int index = lower_letter(word[i]) - BASE_LETTER;
        walk = walk->children[index];
        if ((walk == nullptr) || walk->letter != word[i]) {
            return false;
        }
    }
    return (walk) && walk->complete;
}
/* remove()
 *
 */
bool TrieTree::remove(TrieNode **node, string word)
{
    if (*node == nullptr) {
        return false;
    }
    if ( word.empty() ) 
    {
        if ( children(*node) == 0) {
            delete *node;
            *node = nullptr;
            return true;
        }
        else if ((*node)->complete) {
            (*node)->complete = false;
            return false;
        }
    }

    int index = lower_letter(word.front()) - BASE_LETTER;
    if ( node = &(*node)->children[index] ) {
        remove(node, &word[1]);
        if ( children(*node) == 0) {
            delete *node;
            *node = nullptr;
            return true;
        }
        else {
            return false;
        }
    }
    return false;
}
/* children()
 *   return return number of children, return 0 if no children
 */
int TrieTree::children(TrieNode *node)
{
    if (node == nullptr) {
        return 0;
    }
    int count = 0;
    for (int i = 0; i < number_children; ++i) {
        if (node->children[i]) {
            ++count;
        }
    }
    return count;
}
/* empty()
 *   return true if the trie is empty.
 */
bool TrieTree::empty()
{
    if (trie_root == nullptr) {
        return true;
    }
    for (int i = 0; i < number_children; ++i) {
        if (trie_root->children[i]) {
            return false;
        }
    }
    return true;
}
/* print the Trie tree branches in rows
 * "\" indicates the end of a completed word.
 */
void TrieTree::print(TrieNode *node, int indent = 0)
{
    if (node == nullptr) {
        return;
    }

    cout << node->letter;
    node->complete ? cout << "\\" : cout << "-";

    int c = 0;
    for (int i = 0; i < number_children; i++) {
        if (node->children[i]) {
            if (++c > 1) {
                cout << endl;
                for (int j = 0; j <= indent; j++) { cout << "  "; }
            }
            print(node->children[i], indent + 1);
        }
    }
}

/* testing main
 */
int main()
{
    TrieTree tt;
    tt.insert("word"); cout << "Add Word: word" << endl; tt.print(); cout << endl;
    tt.insert("abcd"); cout << "Add Word: abcd" << endl; tt.print(); cout << endl;
    tt.insert("abef"); cout << "Add Word: abef" << endl; tt.print(); cout << endl;
    tt.insert("abcdefg"); cout << "Add Word: abcdefg" << endl; tt.print(); cout << endl;
    tt.insert("abcdhij"); cout << "Add Word: abcdhij" << endl; tt.print(); cout << endl;

    tt.remove("word"); cout << "Remove Word: word" << endl;; tt.print(); cout << endl;
    tt.remove("abcd"); cout << "Remove Word: abcd" << endl; tt.print(); cout << endl;
    tt.remove("abcdef"); cout << "Remove Word: abcdef" << endl; tt.print(); cout << endl;
    tt.remove("abcdefg"); cout << "Remove Word: abcdefg" << endl; tt.print(); cout << endl;
    tt.remove("abcdhij"); cout << "Remove Word: abcdefg" << endl; tt.print(); cout << endl;
}
