// pragrams from Leetcode 
//
#include <iostream>     // cout
#include <vector>
#include <array>
#include <string>
#include <set>
#include <stack>
#include <algorithm>    // sort()
#include <limits>

using namespace std;

//
// 17, letter combination of phone numers
void letterRecursive(vector<string>& letters, string digits, string current, int index, const string* phone_letters)
{
    if (index == digits.length()) {
        letters.push_back(current);
        return;
    }
    string phone = phone_letters[digits[index] - '0'];
    for (int i = 0; i < phone.size(); ++i) {
         letterRecursive(letters, digits, current + phone[i], index + 1, phone_letters);
    }
}
vector<string> letterCombinations(string digits) 
{
    const string phone_letters[] = {"0", "1", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz" };
    vector<string> letters = {};
    int dlen = digits.length();

    // validate the input
    if (dlen == 0) {
        return letters;
    }
    for (int i = 0; i < dlen; ++i) {
        if ( digits[i] < '2' || digits[i] > '9') {
            return letters;
        }
    }

    letterRecursive(letters, digits, "", 0, phone_letters);

    return letters;
}
// Q21, C Merge Two Sorted Lists
//
struct ListNode {
    int val;
    struct ListNode *next;
};
struct ListNode* mergeTwoLists(struct ListNode* l1, struct ListNode* l2)
{
    struct ListNode *t1 = l1;
    struct ListNode *t2 = l2;
   
    if (l1 == NULL)
        return l2;
   
    if (l2 == NULL)
        return l1;
   
    /* setup the head of the returning list
     */
    struct ListNode *rhead;

    if (t1->val <= t2->val)
    {
        rhead = t1;
        t1 = t1->next;
    }
    else
    {
        rhead = t2;
        t2 = t2->next;
    }
   
    struct ListNode *rlist = rhead;
   
    while (t1 && t2)
    {
        if (t1->val <= t2->val)
        {
            rlist->next = t1;
            rlist = rlist->next;
            t1 = t1->next;
        }
        else
        {
            rlist->next = t2;
            rlist = rlist->next;
            t2 = t2->next;
        }
    }

    /* after one list runs to the end, just append the rest of the other list
     */
    if (t1 || t2)
    {
        rlist->next = t1 ? t1 : t2;
    }
   
    return rhead;
}
// Q23, Merge k sorted lists
// using the Q21 solutions
ListNode* mergeKLists(vector<ListNode*>& lists) {
    int list_size = lists.size();
    if (list_size == 0) {
        return NULL;
    }
    ListNode *head = lists[0];
    for (int i = 1; i < list_size; i++) {
        ListNode *head = mergeTwoLists(head, lists[i]);
    }
    return head;
}
// Q40
// this is factorial, need to combine every element, so
// the recursion includes loops for every element.
void sum2Target(vector<int>& candidates, int target, int index, vector<vector<int>>& results)
{
    vector<int> sum2;
    
    if (target == 0) {
        results.push_back(sum2);
        sum2.clear();
        return;
    }

    if (target < 0) {
        sum2.clear();
        return;
    }

    int sz = candidates.size();
    for (int i = index; i < sz; ++i) {
        if (i == index || candidates[i] != candidates[i - 1]) {
            sum2.push_back(candidates[i]);
            sum2Target(candidates, target - candidates[i], i + 1, sum2, results);
        }
    }
}
vector<vector<int>> combinationSum2(vector<int>& candidates, int target) 
{
    vector<int> current;
    vector<vector<int>> results;

    for (vector<int>::iterator it = candidates.begin(); it != candidates.end(); ++it) {
        if (*it > target) {
            candidates.erase(it);
        }
        else if (*it == target) {
            current.push_back(*it);
            results.push_back(current);
        }
    }
    sort(candidates.begin(), candidates.end());
    for (int e: candidates) { cout << e << ", "; }  cout << endl;

    current.clear();
    sum2Target(candidates, target, 0, current, results);
    return results;
}
// Q51, N-Queens
// Each row of the chessboard is a string with size n,
// print the 'Q' if a queen is on the location, else print '.'
void  printChessboard(vector<string>& chessboard)
{
    int size = chessboard.size();
    cout << "[";
    for (int i = 0; i < size; ++i) {
        cout << chessboard[i];
        if (i < size - 1) {
            cout << ", ";
        }
    }
    cout << "]";
}
void  printNQueens(vector<vector<string>>& solutions)
{
    int sz = solutions.size();
    for (int i = 0; i < sz; ++i) {
        cout.width(3);
        cout << i + 1 << ": ";
        printChessboard(solutions[i]);
        cout << ", " << endl;
    }
}
//
bool  isQueenSafe(vector<string>& chessboard, int row, int col) 
{
    int N = chessboard[0].size();
    int i, j;

    // check the row on the left
    for (j = 0; j < col; ++j) {
        if ( chessboard[row][j] == 'Q' ) {
            return false;
        }
    }

    // check the upper left diagonal
    for (i = row - 1, j = col - 1; i >= 0 && j >= 0; --i, j--) {
        if ( chessboard[i][j] == 'Q' ) {
            return false;
        }
    }

    // check the lower left diagonal
    for (i = row + 1, j = col - 1; i < N && j >= 0; ++i, --j ) {
        if ( chessboard[i][j] == 'Q' ) {
            return false;
        }
    }
    return true;
}

// start placing one Queen from the leftmost column (col = 0)
bool placeQueen(vector<string>& chessboard, int row, int col, vector<vector<string>>& sQ) 
{
    int N = chessboard[0].size();

    if ( col == N) {
        return true;
    }
    for (int i = row; i < N; ++i) {
        if ( isQueenSafe(chessboard, i, col) ) {
            chessboard[i][col] = 'Q';
            // cout << "set " << i << "-" << col << ": ";
            // printChessboard(chessboard);
            // cout << endl;

            if (placeQueen(chessboard, 0, col+1, sQ)) {
                sQ.push_back(chessboard);
                // return true;
            }

            chessboard[i][col] = '.';  // backtracking
            // cout << "clr: " << i << "-" << col;
            // printChessboard(chessboard);
            // cout << endl;
        }
    }
    return false;
}
//
vector<vector<string>> solveNQueens(int n) 
{
    vector<vector<string>>  solutionQ;
    string srow(n, '.');
    vector<string> chessboard(n, srow);
    placeQueen(chessboard, 0, 0, solutionQ);
    // printNQueens(solutionQ);
    return solutionQ;
}
// Q64 Minimum Path sum
// find the min path from grip[0][0] to grip[n-1][m-1];
// create a same size array, zero out the araay
// add the value in current position grip[i][j] with the
// min value of up and right, save it to grip[i][j];
// at the end the d[n-1][m-1] is the value of the min path.
int minPathSum(vector<vector<int>>& grid) {
    if (grid.size() == 0) {
        return 0;
    }
    
    vector<vector<int>> dp(grid.size(), vector<int>(grid[0].size(), 0));
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            dp[i][j] += grid[i][j];
            if (i > 0 && j > 0) {
                dp[i][j] += (dp[i - 1][j] < dp[i][j - 1] ? dp[i - 1][j] : dp[i][j - 1]);
            }
            else if (i > 0) {
                dp[i][j] += dp[i - 1][j];
            }
            else if (j > 0) {
                dp[i][j] += dp[i][j - 1];
            }
        }
    }
    return dp[dp.size() - 1][dp[0].size() - 1];
}
// 136, find the single number, 
// every number appear twice except one.
// not working when there are 3 identical numbers
#include <unordered_set>
int singleNumber(vector<int>& nums) 
{
    unordered_multiset<int> S;
    for (const int& i: nums) {
        if ( S.find(i) != S.end() ) {
            S.erase(i);
        }
        else {
            S.insert(i);
        }
    }
    return *S.begin();
}
// Q121: Best Time to Buy and Sell
int maxProfit(vector<int>& prices) 
{
    int sz = prices.size();
    int max_profit = 0;
    for (int i = 0; i < sz; i++) {
            for (int j = i + 1; j < sz; j++) {
                if (prices[j] - prices[i] > max_profit) {
                    max_profit = prices[j] - prices[i];
                }
            }
    }
    return max_profit;
}
#include <bits/stdc++.h>
int maxProfit(vector<int>& prices) 
{
    int sz = prices.size();
    int min_price = INT _MAX;
    int max_profit = 0;
    for (int i = 0; i < sz; i++) {
        if (prices[i] < min_price)
            min_price = prices[i];
        else if (prices[i] - min_price > max_profit)
            max_profit = prices[i] - min_price;
    }
    return max_profit;
}
// 231: C++, determine an integer is power of two
bool isPowerOfTwo(int n) 
{
    if (n <= 0 || n > 0x40000000) {
        return false;
    }
    int i = 1;
    while (i < n) {
        i <<= 1;
    }
    return (i == n);
}
// 235: lowest Common Ancestor of Binary Search Tree
 struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };
 TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (p->val < root->val && q->val < root->val) {
        return lowestCommonAncestor(root->left, p, q);
    }
    else if (p->val > root->val && q->val > root->val) {
        return lowestCommonAncestor(root->right, p, q);
    }
    else {
        return root;
    }
}
// 286: Walls and Gates
// start from a gate (0), run the DFS, update the count when the current one 
// is greater than the count. the wall (-1) is less than any count (>= 0).
void gate_dfs(int i, int j, int count, vector<vector<int>>& rooms) {
    if (i < 0 || i >= rooms.size() || j < 0 || j >= rooms[i].size() || rooms[i][j] < count) {
        return;
    }
    rooms[i][j] = count;
    gate_dfs(i + 1, j, count + 1, rooms);
    gate_dfs(i - 1, j, count + 1, rooms);
    gate_dfs(i, j + 1, count + 1, rooms);
    gate_dfs(i, j - 1, count + 1, rooms);
} 
//
void wallsAndGates(vector<vector<int>>& rooms) {
    for (int i = 0; i < rooms.size(); ++i) {
        for (int j = 0; j < rooms[i].size(); ++j) {
            if (rooms[i][j] == 0) {
                gate_dfs(i, j, 0, rooms);
            }
        }
    }
}
// 387: C, find the first unique character
#include <string.h>
int firstUniqChar(string s) 
{
    int n = s.size();
    int i, j;
    for (i = 0; i < n; ++i) {
        for (j = 0; j < n; j++) {
            if (j == i) {
                continue;
            }
            if (s[i] == s[j]) {
                break;
            }
        }
        if (j == n) {
            return i;
        }
    }
    return -1;
}
// 438: Frog Jumps

bool canCross(vector<int>& stones) 
{
    int last = stones.size() - 1;
    int jump = 1;
    int position = 1;
    stack<int> sPos;
    stack<int> sJmp;
    while (position < last) {
        int pos = stones[position];
        for (int j = jump - 1; j <= jump + 1; ++j) {
            if (j <= 0) {
                continue;
            }
            for (int i = position + 1; i <= last; ++i) {
                if (stones[position] + j == stones[i]) {
                    sPos.push(i);
                    sJmp.push(j);
                }
                if (pos >= stones[i]) {
                    break;
                }
            }
        }
        if (!sPos.empty()) {
            position = sPos.top();
            sPos.pop();
            jump = sJmp.top();
            sJmp.pop();
        }
        else {
            return false;
        }
    }
    return true;
}
// 657, Robot Return to origin
// robot start from (0, 0), moving on a 2D plane
// the movement is indicated by U=upper, D=down, L=left, R=right
// check if the robot is back to origin after the string of moves.
bool judgeCircle(string moves) 
{
    int UD = 0;
    int LR = 0;
    for (int i = 0; i < moves.size(); ++i) {
        switch (moves[i]) {
            case 'U': ++UD; break;
            case 'D': --UD; break;
            case 'L': ++LR; break;
            case 'R': --LR; break;
            default:;
        }
    }
    return (UD == 0 && LR == 0);
}
// 695 max area of Island
// 
vector<vector<int>> island_grid =
        {{0,0,1,0,0,0,0,1,0,0,0,0,0},
         {0,0,0,0,0,0,0,1,1,1,0,0,0},
         {0,1,1,0,1,0,0,0,0,0,0,0,0},
         {0,1,0,0,1,1,0,0,1,0,1,0,0},
         {0,1,0,0,1,1,0,0,1,1,1,0,0},
         {0,0,0,0,0,0,0,0,0,0,1,0,0},
         {0,0,0,0,0,0,0,1,1,1,0,0,0},
         {0,0,0,0,0,0,0,1,1,0,0,0,0}};
//
// DFS recursive
int maxIsland_dfs(vector<vector<int>>& grid, int i, int j)
{
    if (i < 0 || i >= grid.size()) {
        return 0;
    }
    if (j < 0 || j >= grid[i].size()) {
        return 0;
    }
    if (grid[i][j] == 0) {
        return 0;
    }
    grid[i][j] = 0;
    int island = 1;
    island += maxIsland_dfs(grid, i + 1, j);
    island += maxIsland_dfs(grid, i - 1, j);
    island += maxIsland_dfs(grid, i, j + 1);
    island += maxIsland_dfs(grid, i, j - 1);
    return island;
}
//
int maxAreaOfIsland(vector<vector<int>>& grid) 
{
    int max_area = 0;
    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[i].size(); ++j) {
            if (grid[i][j] == 1) {
                int area = maxIsland_dfs(grid, i, j);
                if (max_area < area ) {
                    max_area = area;
                }
            }
        }
    }
    return max_area;
}
// 767 Reorganize String, greedy problem
// no same char next to each other
// 
string reorganizeString(string S) {
    int sz = S.size();
    for (int i = 0; i < sz; i++) {
        if (S[i] != S[i + 1]) {
            continue;
        }
        for (int j = i + 2; j < sz; j++) {
            if (S[i] != S[j]) {
                int tmp = S[i + 1];
                S[i + 1] = S[j];
                S[j] = tmp;
                break;
            }
        }
    }
    cout << S << endl;
    if (S[sz - 1] == S[sz - 2]) {
        for (int i = sz - 1; i > 0; i--) {
            if (S[i] != S[i - 1]) {
                continue;
            }
            for (int j = i - 2; j >= 0; j--) {
                if (S[i] != S[j]) {
                    int tmp = S[i - 1];
                    S[i - 1] = S[j];
                    S[j] = tmp;
                    break;
                }
            }
        }
    }
    cout << S << endl;
    return S[0] == S[1] ? "" : S;
}
// 905, Sort Array by Parity
vector<int> sortArrayByParity(vector<int>& A) {
    int index = 0;
    for (int i = 0; i < A.size(); i++) {
        if ((A[i] & 1) == 0) {
            int tmp = A[index];
            A[index++] = A[i];
            A[i] = tmp;
        }
    }
    
    return A;
}
// 1007, minimum domino rotations for equal rows
// should work for domino 1 to 6
int minDominoRotations(vector<int>& A, vector<int>& B) {
    int aCount[7] = {0};
    int bCount[7] = {0};
    int cCount[7] = {0};
    int sz = A.size();
    for (int i = 0; i < sz; ++i) {
        ++aCount[A[i]];
        ++bCount[B[i]];
        if (A[i] == B[i]) {
            ++cCount[B[i]];
        }
    }
    int min_count = 999999;
    for (int i = 1; i < 7; ++i) {
        // cout << aCount[i] << " : " << bCount[i] << " : " << cCount[i] << endl;
        if (aCount[i] + bCount[i] - cCount[i] < sz)
            continue;
        else {
            int minAB = aCount[i] > bCount[i] ? sz - aCount[i] : sz - bCount[i];
            if (min_count > minAB)
                min_count = minAB;
        }
    }
    return min_count = min_count == 999999 ? -1 : min_count;
}
//
// testing driver code
//
int main()
{
    int n;

    // Q17
    vector<string> result = letterCombinations("238");
    cout << "letterCombinations: ";
    for (auto e: result) { cout << e << ", "; }  cout << endl;

    // Q21, Q23
    // vector<int> a = [[1,4,5],[1,3,4],[2,6]];
    // vector<ListNode*> lists;
    
    // Q40
    int a[] = {10, 1, 2, 7, 6, 1, 5};
    vector<int> candidates(a, a + sizeof(a)/sizeof(int));
    int target = 8;
    vector<vector<int>> results = combinationSum2(candidates, target);
    for (int i = 0; i < results.size(); ++i) {
        cout << "[";
        for (int j = 0; j < results[i].size(); ++j) {
            cout << results[i][j] << ", ";
        }
        cout << "], ";
    }
    cout << endl;

    // Q51, N-Queens
    cout << "N-Queens: " << endl;
    n = 5;
    vector<vector<string>> q = solveNQueens(n);
    printNQueens(q);

    // 64. minimum path
    vector<vector<int>> grid = {{1,3,1},{1,5,1},{4,2,1}};
    cout << "minPathSum: " << minPathSum(grid) << endl;

    // Q136
    vector<int> nums = {2, 2, 5, 4, 4, 7};
    cout << "singleNumber: " << singleNumber(nums) << endl;

    // Q231
    n = 10243;
    cout << "isPowerOfTwo: " << isPowerOfTwo(n) << endl;

    // Q235
    cout << "lowestCommonAncestor: " << endl;

    // Q286
    cout << "wallsAndGates" << endl;

    // Q387
    string s = "ababcdefdef";
    int first = firstUniqChar(s);
    cout << "firstUniqChar: " << first << endl;

    // 438
    vector<int> stones = {0,1,3,5,6,8,12,17};
    bool r = canCross(stones);
    cout << "canCross: " << r << endl;

    // Q657
    cout << "judgeCircle" << endl;

    // Q695
    int max_island = maxAreaOfIsland(island_grid);
    cout << "Max Area of Island: " << max_island << endl;

    // 767 
    string S = "abaab";
    cout << "reorganizeString: " << reorganizeString(S) << endl;

    // 771 Jewels an Stones
     
    // Q905
    cout << "sortArrayByParity: " << endl;

    // Q1007
    cout << "minDominoRotations" << endl;
}