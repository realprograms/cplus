// TOPIC: 
//  STL Study:  std::set<T>
//  LeetCode:   string multiply_two_string_numbers(string num1, string num2)
//  Study Tree: 
//  git token: feabb300631cc33695eeec3bc990d330dadc04e7 


#include <iostream>
#include <set>
#include <string>
#include <functional>

using namespace std;

/* study_cout_properties()
 */
void study_cout_properties()
{
    cout.setf(ios::hex, ios::basefield);
    cout.setf(ios::showbase);
    cout << 1000 << endl;
    cout.setf(ios::dec, ios::basefield);
    cout << 0x400 << endl;
    // system("Color 1A");  // not really work
    cout << "\t\t\t color" << endl;
}

/* testing
 */
class Person{
    public:
    float age;
    string name;
    bool operator < (const Person& rhs) const { return age < rhs.age;}
    bool operator > (const Person& rhs) const { return age > rhs.age;}
};

/* display set element
 */
void display_set_elements(const set<int>& Set) 
{
    for (auto e: Set) {
        cout << e << ", ";
    }
    cout << endl;
}

/* the production of two string numbers
 */
string multiply_two_string_numbers(string num1, string num2) 
{
    string product;
    int i, j, ii, jj;

    for(i = num1.length() - 1, ii = 0; i >= 0; i--, ii++) {
        int n1 = num1[i] - '0';
        int ov = 0;
        for(j = num2.length() - 1, jj = 0; j >= 0; j--, jj++) {
            int n2 = num2[j] - '0';
            int nx = n1 * n2 + ov;
            int sz = product.size();
            int np = sz - 1 - (ii + jj);
            // cout << i << " " << j << " " << n1 << " " << n2 << " " << nx << " " << ii + jj << " " << sz << " " << np << endl;
            if (sz > ii + jj) {
                nx += product[np] - '0';
                // cout << "addtion: " << sz - 1 - (ii + jj) << " " << product[np] - '0' << " " << nx << " " << endl;
            }
            ov = nx / 10;
            char nc = (nx % 10) + '0';
            if (sz > ii + jj) {
                // cout << "replace: " << ii << " " << jj << " " << np << " " << nc << " " << ov << endl;
                product.replace(np, 1, 1, nc);
            }
            else {
                // cout << "insert: " << ii << " " << jj << " " << nc << " " << ov << endl;
                product.insert(0, 1, nc);
            }
            // cout << "product: " << i << " " << j << " " << sz - 1 - ii << " " << product << endl;
        }
        if (ov) {
            product.insert(0, 1, char(ov + '0'));
            // cout << ov << ' ' << product << endl;
        }
    }
    return product;
}

/* find the max depth of a binary tree
 */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 };



/* get the maximum sum in a path of a binary tree
 */
// #include <limits>

// int max_sum = INT_MIN;  // FIXME
int max_sum = -99999999;   // FIXME

int maxPath(TreeNode* root) {
    if (root == NULL) {
        return 0;
    }

    int left_path_sum  = maxPath(root->left);
    int right_path_sum = maxPath(root->right);
    
    int max1 = max(root->val, root->val + left_path_sum);
    int max2 = max(max1, root->val + right_path_sum);
    int max3 = max(max2, root->val + left_path_sum + right_path_sum);
    max_sum  = max(max3, max_sum);
    
    // cout << "node=" << root->val << ", left=" << left_path_sum << ", right=" << right_path_sum << ", ";
    // cout << "max=" << max_sum << ", return=" << max3 << endl;
    
    return max(root->val, root->val + max(left_path_sum, right_path_sum));
}

int maxPathSum(TreeNode* root) {
    maxPath(root);
    return max_sum;
}

/* Recursion: word square
 */
#include <vector>

vector<string> backtracking(int step, vector<string>& words) {
    int w_size = sizeof(words);
    if (step == w_size) {
        return words;
    }

    string prefix = words[step].substr(0, step);
    for (string s: words[step] ) {

    }
    return ;
} 

/* main program to generate .\a.exe
 */
int main() {

    /* change the basefield
     */
    study_cout_properties();

    /* elements in set are unique
     */
    set<int> Set = {1, 2, 5, 4, 3, 2, 3, 4, 5};
    display_set_elements(Set);

    /* testing multiply_two_string_numbers()
     */
    string num1 = "2468";
    string num2 = "97531";
    cout << num1 << " x " << num2 << " = " << multiply_two_string_numbers(num1, num2) << endl;

        /* word square using backtracking
     */
    vector<string> words = {"area","lead","wall","lady","ball"};

    // change for testing git
    
    return 0;
}