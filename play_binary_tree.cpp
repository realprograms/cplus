// 
// Study Binary Tree Traversal and Search Algorithm
//
// Binary Tree Presentation using Array
//     node 0 is root node
//     node i index is i, value is A[i]
//     node i left child is (2*i - 1)
//     node i right child is (2*i)
//     node i parent is (i - 1)/2
//
// Full Binary Tree
//     Has (pow(2, h) - 1) of nodes, h is the height of the tree,
//     every level is full
//
// Completed Binary Tree
//     The binary tree is filled from far left, every level is full except
//     the bottom level on which the nodes at the left.
//     there is no empty node in the array.
//
// Balanced Tree
//   the difference between the height of left subtree and right subtree is 
//   not more than 1.
//
// Binary Tree Traversal
//   visit each node exactly once in an order
//   - Breadth First Traversal (BFT) 
//       - Level Order
//       + time complexity: O(n)
//       + space complexity: 
//   - Depth First Traversal (DFT)
//       - Preorder : root->left->right 
//       - Inorder  : left->root->right
//       - Postorder: left->right->root
//       + time complexity:  O(n)
//       + space complexity: O(h), h = tree height, between log2(n) and n-1.
//       applications: 
//       - traverse a tree using preorder is straight forward.
//       - binary search tree usually uses the inorder DFT.
//       - using postorder DFT when free/delete all tree nodes. 
//
// Binary Serach Tree
//   for each node, the values of the nodes in the left are less or equal, 
//   the values of the nodes in the right are greater.
//
// AVL Tree (Adelson, Velski & Landis)
//    a self-balancing binary search tree. the balance factor (the height difference 
//    between the left subtree and right subtree) is no more than 1. 
//    to balance a BST, the AVL does four kinds of rotations: left, right, left-right
//    and right-left, to make the BST balanced after insertion and deletion.
//    good for applications do not insert or delete frequently but read often.
//    + time complexity O(n)
//    + space complexity O(n)
//
// Trie
//    is also called prefix tree, it is a special and useful data structure, mostly
//    used for processing strings, each node presents a letter, has up to 26 children.
//    applications:
//    - word spell checker, word games
//    - word autocomplete in searching or writing
//    - IP address routing (longest prefix matching)
//
// Heap
//   it is a special completed binary tree. there are three types of heaps:
//      1) max heap, the node value is greater than the children, the root is the max.
//      2) min heap, the node value is less than the children, the root is the min.
//      3) min-max heap, the values are alternated on levels.
//   To insert an element to a max-heap, 
//      add the element to the end of the tree (or array), then check its parents
//      swap if needed to make the tree be a max-heap again.
//   To delete an element from a max-heap
//      we can only delete the root element from a heap tree
//      After remove the root node, bring the node at the tail to the root, then
//      swap with the child who has the greater value unti the tree become a heap tree.
//   To adjust a binary to be a heap
//      start from the last element, for each node, check its children to see if it
//      it is a heap, swap it and check its child if it is still a heap... 
//   To sort the heap
//      delete the root node and put it to the end, reduced the heap size by 1.
//      the heap will be sorted after delete every element in the heap.
//      the heap sort algorithm is first to insert elements to the heap, then delete
//      every element.
//    applications:
//    - maintaining of priority queues
// 
#include <iostream>
#include <cmath>
#include <queue>
#include <set>

using namespace std;

struct TreeNode {
    int data;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : data(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : data(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : data(x), left(left), right(right) {}
};

TreeNode* binary_tree_new_node(int value) {
    TreeNode* tNode = new TreeNode(value);
    return tNode;
 }

int binary_tree_add_children(TreeNode *tnode, int a[], int n)
{
    if (tnode == NULL) {
        return 0;
    }
    if ( a[n] ) {
        tnode->left = (TreeNode *)malloc(sizeof(TreeNode));
        tnode->left->data = a[n];
        tnode->left->left = NULL;
        tnode->left->right = NULL;
    }

    if ( a[n+1] ) {
        tnode->right = (TreeNode *)malloc(sizeof(TreeNode));
        tnode->right->data = a[n+1];
        tnode->right->left = NULL;
        tnode->right->right = NULL;
    }

    return 0;
}
/* function: build a binary tree from an array
 * note:    hard code the tree for now, will change to recursive
 */
TreeNode* binary_tree_build(int a[], int asize)
{
    TreeNode *root;

    if ( (a == NULL) || (asize == 0) ) {
        return NULL;
    }
 
    root = binary_tree_new_node(a[0]);
    // root = (TreeNode *)malloc(sizeof(TreeNode));
    // root->data = a[0];

    binary_tree_add_children(root, a, 1);
    if (root->left)  {
        binary_tree_add_children(root->left, a, 3);
        if (root->left->left) {
            binary_tree_add_children(root->left->left, a, 7);
        }
        if (root->left->right) {
            binary_tree_add_children(root->left->right, a, 9);
        }
    }
    if (root->right) {
        binary_tree_add_children(root->right, a, 5);
        if (root->right->left) {
            binary_tree_add_children(root->right->left, a, 11);
        }
        if (root->right->right) {
            binary_tree_add_children(root->right->right, a, 13);
        }
    }
    return root;
}
/* build a binary tree from multiset
 */
template <class T>
TreeNode* binary_tree_build(multiset<T> mset)
{
    auto it = mset.begin();
}
/* free memory of every node
 */
void binary_tree_free(TreeNode *root)
{
    if (root == NULL) {
        return;
    }
    if (root) {
        binary_tree_free(root->left);
        binary_tree_free(root->right);
    }
    free(root);
}
/* print the binary tree:
 *   each row includes the nodes in the same depth level
 * input:   root - the tree root
 */
void binary_tree_print(TreeNode *root, int asize)
{
    if ( root == NULL) {
        return;
    }
    int tree_depth = log2(asize);
    cout << "depth: " << tree_depth << endl;
    cout << root->data << endl;

    if (root->left)  { cout << root->left->data << " : "; } else { cout << "* : "; }
    if (root->right) { cout << root->right->data << endl; } else { cout << "*" << endl; }

    if ((root->left) && (root->left->left)) { cout << root->left->left->data << " : "; } else { cout << "* : "; }
    if ((root->left) && (root->left->right)) { cout << root->left->right->data << " | "; } else { cout << "* | " ; }
    if ((root->right) && (root->right->left)) { cout << root->right->left->data << " : "; } else { cout << "* : "; }
    if ((root->right) && (root->right->right)) { cout << root->right->right->data << endl; } else { cout << "* " << endl; }

    if ((root->left) && (root->left->left) && (root->left->left->left)) { cout << root->left->left->left->data << " : "; } else { cout << "* : "; }
    if ((root->left) && (root->left->left) && (root->left->left->right)) { cout << root->left->left->right->data << " || "; } else { cout << "* || "; }
    if ((root->left) && (root->left->right) && (root->left->right->left)) { cout << root->left->right->left->data << " : "; } else { cout << "* : "; }
    if ((root->left) && (root->left->right) && (root->left->right->right)) { cout << root->left->right->right->data << " | "; } else { cout << "* | "; }
    if ((root->right) && (root->right->left) && (root->right->left->left)) { cout << root->right->left->left->data << " : "; } else { cout << "* : "; }
    if ((root->right) && (root->right->left) && (root->right->left->right)) { cout << root->right->left->right->data << " || "; } else { cout << "* || "; }
    if ((root->right) && (root->right->right) && (root->right->right->left)) { cout << root->right->right->left->data << " : "; } else { cout << "* : "; }
    if ((root->right) && (root->right->right) && (root->right->right->right)) { cout << root->right->right->right->data << endl; } else { cout << "* " << endl; }

    // for (int i = 0; i < tree_depth; ++i) {
    //     for (int j = pow(2, i); j < pow(2, (i+1))/2; ++j) {
    //         cout << tree_node->left << " : " << tree_node->right << " | ";
    //     }
    //     cout << endl;
    // }
}
/* print the nodes in preorder: root->left->right
 */
void binary_tree_print_preorder(TreeNode *root)
{
    if (root == NULL) {
        return;
    }
    cout << root->data << ", ";
    binary_tree_print_preorder(root->left);
    binary_tree_print_preorder(root->right);
}
/* print the nodes in Inorder: left->root->right
 */
void binary_tree_print_inorder(TreeNode *root)
{
    if (root == NULL) {
        return;
    }
    binary_tree_print_inorder(root->left);
    cout << root->data << ", ";
    binary_tree_print_inorder(root->right);
}
/* print the nodes in Postorder: left->right->root
 */
void binary_tree_print_postorder(TreeNode *root)
{
    if (root == NULL) {
        return;
    }
    binary_tree_print_postorder(root->left);
    binary_tree_print_postorder(root->right);
    cout << root->data << ", ";
}
/* print the nodes in level (depth) order: left->right->next level
 * Breadth First Traversal: 
 */
void binary_tree_print_levelorder(TreeNode *root)
{
    if (root == NULL) {
        return;
    }
    queue<TreeNode *> Q;
    Q.push(root);
    while( !Q.empty() ) {
        TreeNode *current = Q.front();
        cout << current->data << ", ";
        if (current->left != NULL) {
            Q.push(current->left);
        }
        if (current->right != NULL) {
            Q.push(current->right);
        }
        Q.pop();
    }
}
/* counts the nodes in a binary tree
 */
int binary_tree_count_nodes(TreeNode *root)
{
    int count = 0;

    if (root == nullptr) {
        return 0;
    }
    ++count;
    count += binary_tree_count_nodes(root->left);
    count += binary_tree_count_nodes(root->right);
    return count;
}
/* get the height (depth) of a node in a binary tree
 * input:   root => to get the max height
 */
int binary_tree_get_height(TreeNode* root) 
{
    if (root == NULL) {
        return 0;
    }
    int leftDepth  = binary_tree_get_height(root->left);
    int rightDepth = binary_tree_get_height(root->right);

    if (leftDepth > rightDepth) {
        return leftDepth + 1;
    }
    else {
        return rightDepth + 1;
    }
}
/* store the tree nodes into a sorted set (multiset)
 */
void binary_tree_make_set(TreeNode *root, multiset<int>& mset)
{
    if (root == nullptr) {
        return;
    }
    mset.insert(root->data);
    binary_tree_make_set(root->left, mset);
    binary_tree_make_set(root->right, mset);
}
/* utility function for is_binary_search_ttree()
 */
bool is_binary_subtree_lesser(TreeNode *tnode, int value)
{
    if (tnode == NULL) {
        return true;
    }
    if (tnode->data > value) {
        return false;
    }
    return (is_binary_subtree_lesser(tnode->left, value) && 
            is_binary_subtree_lesser(tnode->right, value));
}
/* utility function for is_binary_search_ttree()
 */
bool is_binary_subtree_greater(TreeNode *tnode, int value)
{
    if (tnode == NULL) {
        return true;
    }
    if (tnode->data <= value) {
        return false;
    }
    return (is_binary_subtree_greater(tnode->left, value) && 
            is_binary_subtree_greater(tnode->right, value));
}
/* check if a binary tree is a binary search tree
 * input:   root
 */
bool is_binary_search_tree(TreeNode *root)
{
    if (root == NULL) {
        return true;
    }
    return (is_binary_subtree_lesser(root->left, root->data) && 
            is_binary_subtree_greater(root->right, root->data) &&
            is_binary_search_tree(root->left) &&
            is_binary_search_tree(root->right));
}
/* find a node in binary_search_tree
 * time complexity: O(h)
 */
TreeNode* binary_search_tree_find(TreeNode *root, int data)
{
    if (root == nullptr) {
        return NULL;
    }
    if (root->data == data) {
        return root;
    }
    if (data < root->data) {
        return binary_search_tree_find(root->left, data);
    }
    else {
        return binary_search_tree_find(root->right, data);
    }
}
/* find the minimum in a binary search tree
 */
TreeNode* binary_search_tree_min(TreeNode *root)
{
    if (root == nullptr) {
        return NULL;
    }
    while (root->left) {
        root = root->left;
    }
    return root;
}
/* find the maximum in a binary search tree
 */
TreeNode* binary_search_tree_max(TreeNode *root)
{
    if (root == nullptr) {
        return NULL;
    }
    while (root->right) {
        root = root->right;
    }
    return root;
}
/* convert a binary tree to a binary search tree and maintaining 
 */
void binary_search_tree_convert(TreeNode **root, multiset<int>::iterator &it)
{
    if (*root == nullptr) {
        return;
    }
    binary_search_tree_convert(&(*root)->left, it);
    (*root)->data = *it;
    ++it;
    binary_search_tree_convert(&(*root)->right, it);
}
/* convert a general binary tree to a binary search tree.
 * keep the same orginal tree structure.
 * algorithm: read every node of the binary tree, store the value of each node
 *            into a multiset, sorted with duplicated values, then rebuild the
 *            tree by replacing each node inorderly.
 */
TreeNode *binary_search_tree_convert(TreeNode *root)
{
    multiset<int> mset;
    binary_tree_make_set(root, mset);
    // for (auto e: mset) { cout << e << " "; } cout << endl;

    auto it = mset.begin();
    binary_search_tree_convert(&root, it);
    return root;
}
/* find the succeesor of a given node in binary search tree
 * algorithm: find the node, the min node on the right subtree will be the successor.
 *            if no right node,
 */
TreeNode* binary_search_tree_successor(TreeNode *root, int data)
{
    TreeNode *tnode = binary_search_tree_find(root, data);
    if (tnode) {
        // cout << "Found Node: " << tnode->data << endl;
        if (tnode->right) {
            return binary_search_tree_min(tnode->right);
        }
        else {
            TreeNode *ancessor  = root;
            TreeNode *successor = NULL;
            while (ancessor != tnode) {
                if (tnode->data < ancessor->data) {
                    successor = ancessor;
                    ancessor = ancessor->left;
                }
                else {
                    ancessor = ancessor->right;
                }
            }
            return successor;
        }
    }
    return tnode;
}
/* delete a node and keep the tree as binary search tree
 */
TreeNode* binary_search_tree_delete(TreeNode *root, int data)
{
    if (root == nullptr) {
        return NULL;
    }
    else if (data < root->data) {
        root->left = binary_search_tree_delete(root->left, data);
    }
    else if (data > root->data) {
        root->right = binary_search_tree_delete(root->right, data);
    }
    else {  // found the node
        if ((root->left == nullptr) && (root->right == nullptr)) {
            free(root);
            root = NULL;
        }
        else if (root->left == nullptr) {
            TreeNode *temp = root;
            root = root->right;
            free(temp);
        }
        else if (root->right == nullptr) {
            TreeNode *temp = root;
            root = root->left;
            free(temp);
        }
        else {
            TreeNode *temp = binary_search_tree_min(root->right);
            root->data = temp->data;
            root->right = binary_search_tree_delete(root->right, temp->data);
        }
    }
    return root;
}
/* check if the binary tree is balanced
 */
bool is_binary_tree_balanced(TreeNode *root)
{
    if (root == nullptr) {
        return true;
    }
    int left_height  = binary_tree_get_height(root->left);  
    int right_height = binary_tree_get_height(root->right);

    return ((abs(left_height - right_height) <= 1) &&
             is_binary_tree_balanced(root->left) &&
             is_binary_tree_balanced(root->right));
}
/* save the nodes of a bst into a vector, 
 * traverse the tree with inorder to keep the sorted order.
 */
void binary_search_tree_save(TreeNode *root, vector<TreeNode *>& vlist)
{
    if (root == nullptr) {
        return;
    }
    binary_search_tree_save(root->left, vlist);
    vlist.push_back(root);
    binary_search_tree_save(root->right, vlist);
}
/* build the avl tree
 */
TreeNode* avl_tree_build(vector<TreeNode *>& vlist, int start, int end)
{
    if (start > end) {
        return NULL;
    }
    int mid = (start + end) >> 1;
    TreeNode *tnode = vlist[mid];
    tnode->left = avl_tree_build(vlist, start, mid-1);
    tnode->right = avl_tree_build(vlist, mid+1, end);
    return tnode;
}
/* convert a bst to a avl tree,
 * algorithm: save the bst into a vector, keep the order.
 *            build the avl tree.
 */
TreeNode* bst_to_avl_tree(TreeNode *root) 
{
    vector<TreeNode *> vlist;
    binary_search_tree_save(root, vlist);
    // for (auto e: vlist) { cout << e->data << " "; } cout << endl;

    int sz = vlist.size();
    return avl_tree_build(vlist, 0, sz-1);
}
/* assumption: X != NULL; X->right != NULL
 */
TreeNode* avl_tree_left_rotate(TreeNode* X)
{
    TreeNode *Y = X->right;
    TreeNode *T2 = Y->left;
    Y->left = X;
    X->right = T2;
    return Y;
}
/* assume: X != NULL; X->left != NULL
 */
TreeNode* avl_tree_right_rotate(TreeNode* X)
{
    TreeNode *Y = X->left;
    TreeNode *T2 = Y->right;
    Y->right = X;
    X->left = T2;
    return Y;
}
//
int avl_tree_balance_factor(TreeNode *root) 
{
    int left_height  = binary_tree_get_height(root->left);
    int right_height = binary_tree_get_height(root->right);
    return (left_height - right_height);
}
/* insert a node into an AVL tree, rotate the nodes to make it balanced
 */
TreeNode* avl_tree_insert_node(TreeNode *root, int data)
{
    // Find the correct position to insert the node and insert it
    if (root == NULL) {
        root = binary_tree_new_node(data);
        return root;
    }
    if (data < root->data)
        root->left = avl_tree_insert_node(root->left, data);
    else if (data > root->data)
        root->right = avl_tree_insert_node(root->right, data);
    else
        return root;

    // Update the balance factor of each node and Balance the tree
    int left_height  = binary_tree_get_height(root->left);
    int right_height = binary_tree_get_height(root->right);
    int balance_factor = left_height - right_height;

    if (balance_factor > 1) {
        if (data < root->left->data) {
            return avl_tree_right_rotate(root);
        } else if (data > root->left->data) {
            root->left = avl_tree_left_rotate(root->left);
            return avl_tree_right_rotate(root);
        }
    }

    if (balance_factor < -1) {
        if (data > root->right->data) {
            return avl_tree_left_rotate(root);
        } else if (data < root->right->data) {
            root->right = avl_tree_right_rotate(root->right);
            return avl_tree_left_rotate(root);
        }
    }
    return root;
}
/* delete a node in a AVL tree, rotate nodes to make it balanced
 */
TreeNode* avl_tree_delete_node(TreeNode *root, int data)
{
    static TreeNode *n8;
    if (root->data == 4) {
        n8 = binary_search_tree_find(root, 8);
    }
    // Find the node and delete it
    if (root == NULL) {
        return NULL;
    }
    if (data < root->data) {
        root->left = avl_tree_delete_node(root->left, data);
    }
    else if (data > root->data) {
        root->right = avl_tree_delete_node(root->right, data);
    }
    else {
        // if ((root->left == NULL) || (root->right == NULL))
        // {
        //     TreeNode *temp = root->left ? root->left : root->right;
        //     if ( temp == NULL) {
        //         temp = root;
        //         root = NULL;
        //     }
        //     else {
        //         *root = *temp;
        //     }
        //     free(temp);
        // }
        if (root->left == NULL) {
            TreeNode *temp = root->right;
            free(root);
            root = temp;  
        }
        else if (root->right == NULL) {
            TreeNode *temp = root->left;
            free(root);
            root = temp;
        } 
        else {
            TreeNode *temp = binary_search_tree_min(root->right);
            root->data = temp->data;
            root->right = avl_tree_delete_node(root->right, temp->data);
        }
    }

    if (root == NULL) {
        return root;
    }

    // Update the balance factor of each node and balance the tree
    int balance_factor = avl_tree_balance_factor(root);

    if (balance_factor > 1) {
        if (avl_tree_balance_factor(root->left) >= 0) {
            return avl_tree_right_rotate(root);
        } else {
            root->left = avl_tree_left_rotate(root->left);
            return avl_tree_right_rotate(root);
        }
    }
    if (balance_factor < -1) {
        if (avl_tree_balance_factor(root->right) <= 0) {
            return avl_tree_left_rotate(root);
        } else {
            root->right = avl_tree_right_rotate(root->right);
            return avl_tree_left_rotate(root);
        }
    }
    return root;
}
// adjust a binary tree downward to be a max-heap
void heap_max_adjust_down(long a[], int sz, int i)
{
    int left = 2*i + 1;
    int right = 2*i + 2;
    int larger = i;

    if (left >= sz) {
        return;
    }
    else if (right >= sz) {
        larger = left;
    }
    else {
        larger = a[left] > a[right] ? left : right;
    }

    if (a[i] < a[larger]) {
        swap(a[i], a[larger]);
        heap_max_adjust_down(a, sz, larger);
    }
}
/* heapify (adjust to heap) bottom-up
 * used best for adding an element 
 */
void heap_max_adjust_up(long a[], int sz, int i) 
{ 
    int parent = (i - 1) >> 1; 
  
    if (parent >= 0) { 
        if (a[i] > a[parent]) { 
            swap(a[i], a[parent]); 
            heap_max_adjust_up(a, sz, parent); 
        } 
    } 
} 
/* make a binary tree to be a heap
 * must starting from bottom 
 * do not need to do anything for the bottom level
 */
void heap_max_adjust(long a[], int sz)
{
    if ( sz <= 1) {
        return;
    }
    for (int i = (sz >> 1) - 1; i >= 0; --i) {
        heap_max_adjust_down(a, sz, i);
    }
}
/* always delete the root (max) element, then 
 * move the last element to the root, and 
 * heapify from the root.
 */
int heap_max_delete(long a[], int sz)
{
    int root = a[0];
    a[0] = a[sz - 1];
    a[sz - 1] = 0;
    sz -= 1;
  
    heap_max_adjust_down(a, sz, 0);
    return root;
}
/* always added the new element at the end (last element)
 */
int heap_max_add(long a[], int sz, int data)
{
    a[sz - 1] = data;
    heap_max_adjust_up(a, sz + 1, sz - 1);
    // for (int i = sz -1; i >= 0; --i) heap_max_adjust(a, sz, i);
    return a[0];
}
/* driver code for testing
 */
int main()
{
    // need 15 elements to build 3-depth binary tree
    int a[] = {1, 2, 3, 4, 0, 5, 7, 8, 10, 0, 0, 0, 9, 0, 0};
    int size = sizeof(a)/sizeof(int);
    TreeNode *root;

    // root->left = newNode(3);
    // root->right = newNode(4);
    // root->right->left = newNode(15);
    // root->right->right = newNode(7);

    cout << "array[" << size << "] = {";
    for (int i = 0; i < size; ++i) {
        cout << a[i] << ", ";
    }
    cout << "}" << endl;

    root = binary_tree_build(a, size);
    binary_tree_print(root, size);

    cout << "Preorder:  ";
    binary_tree_print_preorder(root);
    cout << endl;

    cout << "Inorder:   ";
    binary_tree_print_inorder(root);
    cout << endl;

    cout << "Postorder: ";
    binary_tree_print_postorder(root);
    cout << endl;

    cout << "Levelorder: ";
    binary_tree_print_levelorder(root);
    cout << endl;

    cout << "Count nodes: " << binary_tree_count_nodes(root) << endl;
    cout << "Max heigth:  " << binary_tree_get_height(root) << endl;

    cout << "BST check: " << is_binary_search_tree(root) << endl;
    
    cout << "BST Convert: ";
    root = binary_search_tree_convert(root);
    binary_tree_print_inorder(root);
    cout << endl;

    cout << "root: " << root->data;
    cout << ",  max: " << (binary_search_tree_max(root))->data;
    cout << ",  min: " << (binary_search_tree_min(root))->data << endl;

    int  d = 3;
    cout << "BST Successor of node " << d << " is: " << (binary_search_tree_successor(root, d))->data << endl;

    root = binary_search_tree_delete(root, 7);
    cout << "BST Delete: ";
    binary_tree_print_inorder(root);
    cout << endl;
    binary_tree_print(root, size);

    cout << "Is balanced: " << is_binary_tree_balanced(root) << endl;
    cout << "Convert to AVL: ";
    root = bst_to_avl_tree(root);
    binary_tree_print_inorder(root);
    // binary_tree_print(root, 8);
    cout << "AVL root: " << root->data << endl;
    cout << "AVL height: " << binary_tree_get_height(root) << endl;
    cout << "Is balanced: " << is_binary_tree_balanced(root) << endl;

    d = 7;
    cout << "AVL insert: " << d << ",  Height: " << binary_tree_get_height(root) << endl;
    root = avl_tree_insert_node(root, d);
    binary_tree_print_inorder(root);
    cout << endl;
    binary_tree_print(root, 9);

    d = 6;
    cout << "AVL insert: " << d << ",  Height: " << binary_tree_get_height(root) << endl;
    root = avl_tree_insert_node(root, d);
    binary_tree_print_inorder(root);
    cout << endl;
    binary_tree_print(root, 10);

    d = 6;
    cout << "AVL delete: " << d << ",  Height: " << binary_tree_get_height(root) << endl;
    root = avl_tree_delete_node(root, d);
    binary_tree_print_inorder(root);
    cout << endl;
    binary_tree_print(root, 9);
    binary_tree_free(root);

    cout << "Heap Tree: " << endl;
    long A[] = {8, 6, 3, 10, 5, 4, 9, 2};
    int sz = sizeof(A)/sizeof(long);
    cout << "Original: A[] = "; for (int i = 0; i < sz; ++i) { cout << A[i] << ", "; } cout << endl;
    heap_max_adjust(A, sz);
    cout << "Heapify: A[] = "; for (int i = 0; i < sz; ++i) { cout << A[i] << ", "; } cout << endl;
    d = heap_max_delete(A, sz);
    cout << "Deleted " << d << ": A[] = "; for (int i = 0; i < sz; ++i) { cout << A[i] << ", "; } cout << endl;
    heap_max_add(A, sz, d);
    cout << "Aded " << d << ": A[] = "; for (int i = 0; i < sz; ++i) { cout << A[i] << ", "; } cout << endl;

   return 0;
}