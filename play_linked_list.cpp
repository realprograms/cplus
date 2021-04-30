// 
// study singly and dubly linked list in C/C++
//
// Pro:
// 1) dynamic size
// 2) ease of insertion and deletion
// Con:
// 1) random access is not allowed, no binary search.
// 2) extra space for the pointer in every element.
// 3) not cache friendly, memory is not continous.
//
// linked list types
//   1) singly linked list
//   2) doubly linked list
//   3) cirular linked list
//
// linked list sorting
//   - merge sort
//   - quick soer (doubly list)
//
// linked list searching
//   - linear search only, cannot do binart search
//   - create and use the skip list for a linked list with length of sqrt(n)
//     
// applications:
//   1) implementations of stack, queue, etc.
//   2) 


#include <iostream>
#include <array>
#include <list>

using namespace std;

// template <class T>
struct singlyNode {
    int data;
    singlyNode *next; 
};

struct doublyNode {
    int data;
    doublyNode *prev;
    doublyNode *next;
};

/* ****************************************************************************
 * Input:   (singlyNode *)list  - the head of the linked list
 *      :   (singlyNode *)entry - its memory should be allocated by the caller
 * Return:  the head of the linked list
 * note:    it is ok if the entry is null
 */
singlyNode* singly_linked_list_append(singlyNode *list, singlyNode *entry)
{
    singlyNode *head;

    if ( !(head = list) ) {
        return entry;
    }

    while (list->next) {
        list = list->next;
    }

    list->next = entry;

    return head;
}

/* ****************************************************************************
 * Input:   (singlyNode *)list  - the head of the linked list
 *      :   (singlyNode *)entry - its memory should be allocated by the caller
 * Return:  the head of the linked list
 * note:    1) one of two input parameters must be not nullptr
 *          2) entry->next may or may not be a good pointer for this list
 */
singlyNode *singly_linked_list_remove(singlyNode *list, singlyNode *entry)  
{
    if ( !(list) || !(entry) ) {
        return NULL;
    }

    // indirect method, assume: entry->next is good
    if (0) 
    {
        singlyNode **walk = &list;
        
        while ((*walk) != entry) {
            walk = &(*walk)->next;
        }

        *walk = entry->next;

        // change the head if removed the first entry
        if (list == entry) {
            list = *walk; 
        }
    }

    // if entry->next is null or invalid for this list
    else 
    {
        singlyNode *prev = NULL;
        singlyNode *walk = list;

        while ( (walk) && (walk != entry) ) {
            prev = walk;
            walk = walk->next;
        }

        if ( !(prev) ) {
            list = list->next;
        }
        else {
            prev->next = walk->next;
        }
    }
    return list;
}

int singly_linked_list_length(singlyNode *list)
{
    int count = 0;
    while (list) {
        ++count;
        list = list->next;
    }
    return count;
}

/* search the data (key) on the list
 */
singlyNode* singly_linked_list_search(singlyNode *list, int data)
{
    while (list) {
        if ( list->data == data) {
            return list;
        }
        list = list->next;
    }
    return NULL;
}

/* return:  true if entry is null
 *       :  false if list is null
 */
bool singly_linked_list_search(singlyNode *list, singlyNode *entry)
{
    if ( !(list) ) {
        return false;
    }

    while (list) {
        if ( list == entry) {
            return true;
        }
        list = list->next;
    }
    return false;
}

/* algorithm: swap the next pointer to reverse the list
 */
singlyNode* singly_linked_list_reverse_iterate(singlyNode *list)
{
    singlyNode *prev = NULL;
    singlyNode *next;

    while(list) {
        next = list->next;
        list->next = prev;
        prev = list;
        list = next;
    }

    return prev;
}
/* reverse the singly linked list using recursive
 */
singlyNode* singly_linked_list_reverse_recusive(singlyNode *list, singlyNode **head)
{
    if (list->next == nullptr) {
        *head = list;
        return list;
    }
    singlyNode *prev = singly_linked_list_reverse_recusive(list->next, head);
    prev->next = list;
    list->next = NULL;
    return list;
}
/* reverse the linked list using stack
 */
#include <stack>
singlyNode* singly_linked_list_reverse_stack(singlyNode *list)
{
    singlyNode *walk = list;
    stack<singlyNode *> sk;
    while(walk) {
        sk.push(walk);
        walk = walk->next;
    }

    singlyNode *rlist = sk.top();
    sk.pop();
    walk = rlist;
    while (!sk.empty()) {
        walk->next = sk.top();
        walk = walk->next;
        sk.pop();
    }
    walk->next = NULL;

    return rlist;
}
/* algorithm: use two pointers to traverse the list, one, the fast, advances two nodes
 *            at a time; the other, the slow, advances one node at a time. When the fast
 *            pointer reaches the end, the slow pointer is in the middle. split the list
 *            at the slow pointer. the extra one of odd number list goes to the frant.
 */
void singly_linked_list_split(singlyNode *list, singlyNode **ppFront, singlyNode **ppBack)
{
    if ( !(list) || !(list->next) ) {
        *ppFront = list;
        *ppBack  = NULL;
        return;
    }

    singlyNode *slow = list;
    singlyNode *fast = list->next;

    while (fast) {
        if ( (fast = fast->next) ) {
            fast = fast->next;
            slow = slow->next;
        }
    }

    *ppFront = list;
    *ppBack  = slow->next;
    slow->next = NULL;
}

/* algorithm: merge two sorted list (ascending) into one list (ascending)
 */
singlyNode* singly_linked_list_merge(singlyNode *list1, singlyNode *list2)
{
    if ( !(list1) ) {
        return list2;
    }
    else if ( !(list2) ) {
        return list1;
    }

    singlyNode *mlist = NULL;

    if ( list1->data < list2->data ) {
        mlist = list1;
        mlist->next = singly_linked_list_merge(list1->next, list2);
    }
    else {
        mlist = list2;
        mlist->next = singly_linked_list_merge(list1, list2->next);
    }

    return mlist;
}

/* algorithm: merge sort, divide and conquer
 */
void singly_linked_list_sort(singlyNode **list)
{
    if ( !(*list) || !((*list)->next) ) {
        return;
    }

    singlyNode *front;
    singlyNode *back;

    singly_linked_list_split(*list, &front, &back);
    singly_linked_list_sort( &front );
    singly_linked_list_sort( &back );

    *list = singly_linked_list_merge(front, back);
}

/* algorithm: traverse the list and check if we see the node again
 *            implementation in c++
 */
#include <set>

bool singly_linked_list_detect_loop(singlyNode *list)
{
    set<singlyNode *> S;

    while (list) {
        if ( S.find(list) != S.end() ) {
            return true;
        }
        S.insert(list);
        list = list->next;
    }
    return false;
}

/* algorithm:   use two pointers, fast and slow, to traverse the list,
 *              when two pointers are equal, loop is found.
 * notes:       take care the list that only has one or two nodes first.
 */
bool singly_linked_list_floyd_loop(singlyNode *list)
{
    if ( !(list) || !(list->next) ) {
        return false;
    }

    if ( (list->next == list) || (list->next->next == list)) {
        return true;
    }
    singlyNode *slow = list;
    singlyNode *fast = list;

    while (slow && fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (fast == slow ) {
            return true;
        }
    }

    return false;
}

/* build a singly linked list from an c++ array
 */
singlyNode* singly_linked_list_build(const array<int, 10>& a)  // must have size for C
{
    int size = a.size();
    singlyNode *slist = NULL;

    for (int i = 0; i < size; ++i) {
        singlyNode *entry = (singlyNode *)malloc( sizeof(singlyNode) );
        entry->data = a[i];
        entry->next = NULL;
        slist = singly_linked_list_append(slist, entry);
    }
    return slist;
}

/* free all the nodes on the linked list
 * must free the node backward
 */
void singly_linked_list_free(singlyNode **list)
{
    singlyNode *next;
    while (*list) {
        next = (*list)->next;
        free(*list);
        *list = next;
    }
}

/* algorithm: the nodeCount is used to display the list that may have a loop.
 */
// class nodeCount {
//     int count;
// public:
//     nodeCount() :count{0} {};
//     int countInc() { return ++count; }
//     singlyNode *walk;
// };

// template <class T>
void printLinkedList(singlyNode *list)
{
    set<singlyNode *> S;
    singlyNode *walk = list;

    int first = -1;
    int count = 0;
    cout << "[";
    while (walk) {
        cout << walk->data << ", ";
        if ( S.find(walk) != S.end() ) {
            if ( first == -1 ) {
                first = walk->data;
                ++count;
            }
            else if ( (first == walk->data) && (++count > 1) ) {
                break;
            }
        }
        S.insert(walk);
        walk = walk->next;
    }
    cout << "]" << endl;
    if (count) {
        cout << "this list includes loop!" << endl;
    }
}

int main()
{
    array<int, 10> myArray = {1, 3, 5, 7, 9, 8, 6, 4, 2};

    // singlyNode slist = { 0, (singlyNode *)NULL }; 
    singlyNode *slist = singly_linked_list_build(myArray); 

    cout << "slist append: " << slist << endl;
    printLinkedList( slist );
    
    slist = singly_linked_list_reverse_iterate(slist);
    cout << "reverse iterate: " << slist << endl;
    printLinkedList( slist );

    singlyNode *rlist = NULL;
    slist = singly_linked_list_reverse_recusive(slist, &rlist);
    cout << "reverse recursive: " << rlist << endl;
    printLinkedList( rlist );
    slist = rlist;

    slist = singly_linked_list_reverse_stack(slist);
    cout << "reverse stack: " << slist << endl;
    printLinkedList( slist );

    singlyNode *entry = slist;
    for (int i = 0; i < 0; ++i) {
        entry = entry->next;
    }
    slist = singly_linked_list_remove(slist, entry);
    free(entry);
    cout << "slist remove: " << slist << endl;
       printLinkedList( slist );

    singlyNode *pFront;
    singlyNode *pBack;
    singly_linked_list_split(slist, &pFront, &pBack);
    cout << "front split: " << slist << endl;
    printLinkedList( pFront );
    cout << "back split:  " << slist << endl;
    printLinkedList( pBack );
    singlyNode *mlist = singly_linked_list_merge(pFront, pBack);
    cout << "slist merge: " << mlist << endl;
    printLinkedList( mlist );
    singly_linked_list_sort(&mlist);
    cout << "slist sort:  " << mlist << endl;
    printLinkedList( mlist );

    cout << "list length: " << singly_linked_list_length(slist) << endl;

    // create a loop
    singlyNode *e5 = singly_linked_list_search(mlist, 6);
    singlyNode *tail = mlist; while (tail->next) { tail = tail->next; }
    tail->next = e5;
    cout << "mlist loop: " << mlist << endl;
    printLinkedList( mlist );

    // bool b = singly_linked_list_detect_loop(slist);
    // cout << "detect loop: " << b << endl;
    
    bool b = singly_linked_list_floyd_loop(slist);
    cout << "floyd loop: " << b << endl;
    
    tail->next = NULL;
    cout << "fixed loop: " << mlist << endl;
    printLinkedList( mlist );

    singly_linked_list_free(&slist);
    cout << "slist free: " << slist << endl;

    // c++ has two template list classes: list and forward list.
    // c++ forward_list is the singly linked list in C.
    cout << "\n" << "------------------------------------------------------" << endl;

    // array<int, 10> myArray = {1, 3, 5, 7, 9, 8, 6, 4, 2};
    list<int> clist;

    for (int i = 0; i < 10; ++i) {
        clist.push_back(myArray[i]);
    }
    
    cout << "C++ list: [";  for (auto& e: clist) { cout << e << ", "; }  cout << "]" << endl;

    cout << "clist reverse: " << clist.size() << endl;
    clist.reverse();
    cout << "C++ list: [";  for (auto& e: clist) { cout << e << ", "; }  cout << "]" << endl;

    cout << "clist remove/erase: " << clist.size() << endl;
    clist.erase( clist.begin() ); 
    cout << "C++ list: [";  for (auto& e: clist) { cout << e << ", "; }  cout << "]" << endl;

    cout << "clist sort: " << clist.size() << endl;
    clist.sort(); 
    cout << "C++ list: [";  for (auto& e: clist) { cout << e << ", "; }  cout << "]" << endl;

    list<int>::iterator it = clist.begin();
    it = std::next(it, 5);  //c++11
    cout << "element with iterator.begin() + 5: " << *it << ",  tail: " << clist.back() << endl;
    
    return 0;
}