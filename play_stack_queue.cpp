//
// Stack - Abstract Data Structure
//   the inseartion and deletion can only be performed at the top
//   LIFO: last in first out
//   operations: push(), pop(), top(), isempty()
//   applications:
//     - function calls and recursion
//     - undo in an editor
//     - balanced parenthese
//   solutions:
//     - reverse singly linked list
//     - depth first travesal of tree
//
#include <iostream>
#include <stack>

using namespace std;

/* inplement a integer stack using a singly linked list
 */
struct Node {
    int data;
    struct Node* next;
};

Node *top = NULL;

void stack_push(int data)
{
    Node *new_node = (Node *)malloc(sizeof(struct Node));
    new_node->data = data;
    new_node->next = top;
    top = new_node;
}
void stack_pop()
{
    if (top == NULL) {
        return;
    }
    Node *top_node = top;
    top = top->next;
    free(top_node);
}
int stack_top()
{
    return top->data;
}
bool stack_empty()
{
    return (top == NULL);
}
void stack_print()
{
    const Node* walk = top;
    while (walk) {
        cout << walk->data << ", ";
        walk = walk->next;
    }
    cout << endl;
}
/* check for balanced parenthese
 * algorithm: push the opening parenthese/bracket into the stack.
 *            when have a closing parenthese/bracket, check if it
 *            match the top parenthese on the stack. if it doesn't
 *            match, return false; if match, pop out the opening 
 *            parenthese. At the end, the parentheses are balanced
 *            if the stack is empty.
 * input: string includes only '(',')', '[', ']', '{', '}' 
 */
bool stack_check_parenthese(string s)
{
    stack<char> cStack;
    for (int i = 0; i < s.size(); ++i) {
        if ((s[i] == '(') || (s[i] == '[') || (s[i] == '{')) {
            cStack.push(s[i]);
        }
        else {
            if (cStack.empty())
                return false;
            if (s[i] == ')') {
                if (cStack.top() != '(')
                    return false;
            }
            else if (s[i] == ']') {
                if (cStack.top() != '[')
                    return false;
            }
            else if (s[i] == '}') {
                if (cStack.top() != '{')
                    return false;
            }
            cStack.pop();
        }
    }
    return cStack.empty();
}

/******************************************************************************
 * Queue, Abstract Data Type
 *   1) a list with insertion at one end and deletion at other end.
 *   2) FIFO, first in first out
 *   applications:
 *     1) device IO queues, the devices are often shared, e.g. printer, disk drives
 *     2) process sheduling, waiting queue for a job
 *     3)
 */

Node* head = NULL;
Node* tail = NULL;

bool queue_empty()
{

}
bool queue_full()
{

}
Node* queue_enqueue()
{

}
Node* queue_dequeue()
{

}
Node* queue_front()
{

}
Node* queue_back()
{

}

/* driver code for testing
 */
int main()
{
    int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (int i = 0; i < 9; ++i) {
        stack_push(a[i]);
    }
    cout << "stack: ";
    stack_print();

    cout << "stack pop: " << stack_top() << endl;
    stack_pop();
    cout << "stack: ";
    stack_print();

    return 0;
}

