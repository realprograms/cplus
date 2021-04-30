//   Search Algorithm
//     Linear Search
//     Partition Search
//     Binary Search
//     Interpolation Search
//     Fibonacci Search
//     Hash Search, see hash.cpp
//     Binary Tree Search, see tree.cpp
//

#include <iostream>
#include <chrono>
#include <algorithm>
// #include <climits>
// #include <random>
// #include <cstdlib>

using namespace std;
using namespace std::chrono;

/* Linear Search
 * algorithm: 
 *    search an array or linked list from the beginning, one by one
 *    until the end of the array or list.
 *    - pros: works on the unsorted list  
 *    - cons: must get to the end to know the element does not in.
 * implemetations: iterative
 *    - input:  
 *    - return: index if found; -1 if not found, 
 * time complexity: worst O(n), average On/2), best O(1) 
 * space complexity: O(1)
 * applications: 
 *    - unsorted array or linked list
 */
int linear_search(long *a, int sz, long x)
{
    int i;
    for (i = 0; i < sz; ++i) {
        if (a[i] == x) {
            return i;
        }
    }
    return -1;
}
/* partitional linear search:
 *   partition the array into k segments, then do the linear search
 *   in each segment in parallel.
 *   the searching starts from both ends towards to the middle.
 *   - pros: perform better when the array is large.
 *   - cons: 
 */ 
int partitional_linear_search(long *a, int sz, int k, long x)
{
    int i, j;
    int idx[k];
    long *arr[k];

    if (k <= 0) {
        return -1;
    }

    // save the beginning array index and address of each segment
    int sz1 = (sz + k - 1) / k ;
    for (i = 0, j = k - 1; i <= j; ++i, --j) {
        idx[i] = i * sz1;
        idx[j] = sz - 1 - i * sz1; 
        arr[i] = a + idx[i];
        arr[j] = a + idx[j];
    }

    for (int n = 0; n < sz1; ++n) {
        for (i = 0, j = k - 1; i <= j; ++i, --j) {
            if ( *(arr[i] + n) == x) {
                return idx[i] + n;
            }
            if ( *(arr[j] - n) == x) {
                return idx[j] - n;
            }
        }
    }
    return -1;
}
/*
long* linear_search_recursive(long *a, int sz, int k, long x)
{
    if (sz <= k) {
        cout << "sz= " << sz << ", k= " << k << ", &a= " << a << endl;
        for (int i = 0; i < sz; ++i) {
            if (a[i] == x) {
                cout << "return " << &a[i] << " " << a[i] << endl;
                return &a[i];
            }
        }
        return nullptr;
    }
    else {
        cout << "sz2= " << (sz >> 1) <<  ", k= " << k << ", &a= " << a << endl;
        linear_search_recursive(&a[0], sz >> 1, k, x);
        cout << "sz3= " << sz - (sz >> 1) << ", k= " << k << ", &a= " << a + (sz >> 1) << endl;
        linear_search_recursive(a + (sz >> 1), sz - (sz >> 1), k, x);
    }
    return nullptr;
}
*/
/* Binary Search
 *    search on a sorted list
 * algorithm: 
 *    cut the searching range by half after comparing the data at the middle.
 *    change the searching range to the first half or the back half.
 *    repeat the previous steps until find the key (first, last, middle are same)
 * implementations: iterative, recursive
 * time complexity: O(logn)
 * space complexity: O(1) for iterative
 */
int binary_search(long a[], int sz, long key)
{
    int first = 0;
    int last  = sz - 1;
    int middle;

    if ((key < a[0]) || (key > a[last])) {
        return -1;
    }

    int count = 0;
    while (first <= last) {
        // cout << first << " " << last << ", " << last - first << " " << ((last - first) >> 1) << " " << ((last - first) & 1) << endl;
        // cout << "step " << count++ << ": " << first << " " << last << endl;
        middle = first + ((last - first) >> 1) + ((last - first) & 1);
        if (key == a[middle]) {
            return middle;
        }
        else if ( key > a[middle]) {
            first = middle + 1;
        }
        else { // (key > a[middle])
            last = middle - 1;
        }
    }
    return -1;
}
/* Golden Search
 *    same as binary search, but instead cutting the list into two: 2/3 and 1/3.
 *    the performance is better when the data is close to the ends. The average
 *    speed is slower than the binary search.
 * time complexity: O(log3n)
 * space complexity: O(1)
 */
int golden_search(long a[], int sz, long key) 
{
    int first = 0;
    int last  = sz - 1;

    if ((key < a[0]) || (key > a[last])) {
        return -1;
    }

    int count = 0;
    while (first <= last) {
        // cout << first << " " << last << ", " << last - first << " " << ((last - first) >> 1) << " " << ((last - first) & 1) << endl;
        // cout << "step " << count++ << ": " << first << " " << last << endl;
        int golden = first + ((last - first) >> 1) + ((last - first) >> 3);
        if (key == a[golden]) {
            return golden;
        }
        else if ( key > a[golden]) {
            first = golden + 1;
        }
        else { // (key > a[middle])
            last = golden - 1;
        }
    }
    return -1;
}
/* Interpolation Search
 *    works on a sorted array or list.
 *    improvement of the binary search.
 * algorithm: instead of the middle index, find the index based on the value of Key
 *            interpolation = (last - first) * (key - A[first]) / (A[last] - A[first])
 *            make sure no overflow when calculate interpolation location.
 * implemetation: iterative
 * time complexity: O(logn)
 * space compleexity: O(1)
 * note: 1) it is not efficient as binary search when the size of the list is small
 *       2) we may only need to do the calculation for the very first time.
 */
int interpolation_search(long a[], int sz, long key)
{
    int first = 0;
    int last  = sz - 1;
    int interpolation;
    // int count = 0;

    if ((key < a[0]) || (key > a[last])) {
        return -1;
    }

    // while (first <= last && key >= a[first] && key <= a[last]) {  // quickly find out if the key is in the list
    while (first <= last) {
        if (last == first || a[last] == a[first]) {  // denominator will be 0
            interpolation = last;
        }
        else {
            // int interpolation = first + (last - first) * (key - a[first]) / (a[last] - a[first]);
            // unsigned long long interpolation = (unsigned long long)(last - first) * (key - a[first]) / (a[last] - a[first]);
            interpolation = first + (((double)(last - first) / (a[last] - a[first])) * (key - a[first]));
        }
        // cout << "step " << ++count << ": " << first << " " << last << " " << a[first] << " " << a[last] << " " << key << " " << interpolation << endl;
        if (key == a[interpolation]) {
            return interpolation;
        }
        else if ( key > a[interpolation]) {
            first = interpolation + 1;
        }
        else { // (key > a[middle])
            last = interpolation - 1;
        }
    }
    return -1;
}
/* Fibonacci Search
 * algorithm:
 */
int fibonacci_search(long a[], int sz, long key)
{
    int fib2 = 0;
    int fib1 = 1;
    int fibM = fib2 + fib1;
  
    /* fibM is going to store the smallest Fibonacci 
       Number greater than or equal to n */
    while (fibM < sz) 
    { 
        fib2 = fib1; 
        fib1 = fibM; 
        fibM  = fib2 + fib1; 
    } 
  
    int offset = -1; 
  
    int step = 0; 
    /* while there are elements to be inspected. Note that 
       we compare arr[fibMm2] with x. When fibM becomes 1, 
       fibMm2 becomes 0 */
    while (fibM > 1) 
    { 
        // Check if fibMm2 is a valid location 
        int i = min(offset + fib2, sz - 1); 
  
        cout << "step " << ++step << ": " << fib2 << "+" << fib1 << "=" << fibM << " ofs " << offset << " i=" << i << " a[i]=" << a[i] << endl;
        if (a[i] < key) 
        { 
            fibM  = fib1; 
            fib1 = fib2; 
            fib2 = fibM - fib1; 
            offset = i; 
            cout << "stepA " << step << ": " << fib2 << "+" << fib1 << "=" << fibM << " ofs " << offset << endl;
        } 
        else if (a[i] > key) 
        { 
            fibM  = fib2; 
            fib1 = fib1 - fib2; 
            fib2 = fibM - fib1;
            cout << "stepB " << step << ": " << fib2 << "+" << fib1 << "=" << fibM << " ofs " << offset << endl;
        } 
        else {
            return i; 
        }
    } 

    // there could be one remained
    if(fib1 && a[offset+1] == key) {
        return offset+1; 
    }
    /*element not found. return -1 */
    return -1; 
}
int fibonacci_search_2(long a[], int sz, long key)
{
    int fib_low = 0, fib_high = 1;
    int offset = 0;
    int N = sz;
    int step = 0;

    while (fib_low != 1) {
        fib_low = 0; 
        fib_high = 1;
        // cout << "step " << ++step << ": " << fib_low << "+" << fib_high << " ofs " << offset << " N=" << N << " key=" << key << endl;
        // while (offset +(fib_low += fib_high) + (fib_high += fib_low) < N - 1);
        while (offset +(fib_low += fib_high) <= N - 1) {
            fib_high += fib_low;
            int location = offset + fib_low;
            // cout << "step " << step << ": " << fib_low << "+" << fib_high << " loc=" << location << " N=" << N << " ofs=" << offset << endl;
            if (key == a[location]) {
                return location;
            }
            else if (key < a[location]) {
                N = location;
            }
            else {
                offset = location;
            }
            // cout << "step " << step << ": " << fib_low << "+" << fib_high << " loc=" << location << " N=" << N << " ofs=" << offset << endl;
        }
    }
    while (offset <= N - 1) {
        if (key == a[offset]) {
            return offset;
        }
    }
    return -1;
}
/* Depth first Search
 * The DFS iterative algorithm traverses the nodes in a depthward motion,
 *    and uses a stack to remember to get the next vertex to start a search, 
 *    when a dead end occurs in any iteration
 * The DFS recursive algorithm uses the idea of backtracking. 
 *   It exhausts all the nodes by going ahead, if possible, else by backtracking.
 */
#include <vector>
#include <stack>
vector<vector<int>> adj;  // adjacent table
vector<bool> visited;     // to remember a vertice has been visited
//
void dfs_iterative(int s)
{
    visited[s] = false; 
    stack<int> Stack;   
    Stack.push(s); 

    while (!Stack.empty()) 
    { 
        s = Stack.top(); 
        Stack.pop(); 
  
        if (!visited[s]) 
        { 
            // cout << s << " "; 
            visited[s] = true; 
        } 
  
        for (auto i = adj[s].begin(); i != adj[s].end(); ++i) {
            if (!visited[*i]) {
                Stack.push(*i);
            } 
        }
    } 
}
//
void dfs_recursive(int s)
{
    visited[s] = true;
    for(int i = 0;i < adj[s].size();++i) {
        if(visited[adj[s][i]] == false) {
            dfs_recursive(adj[s][i]);
        }
    }
}

// int interpolation = first + (last - first) * (key - a[first]) / (a[last] - a[first]);
// unsigned long long interpolation = (unsigned long long)(last - first) * (key - a[first]) / (a[last] - a[first]);

int main()
{
    int n = 18;
    int result;
    long A[n];
    long B[n];

    cout << "---- generate " << n << " random numbers ----" << endl;
    for(int i = 0; i < n; ++i) { B[i] = rand() % (n * 10); }
    cout << "Original Array: " << endl;
    int k = 9;
    cout << "B[" << k - min(8, n) << "] = ";
    for(int i = 0; i < n; ++i) { cout.width(4); cout << B[i] << ", ";  if ((i + 1) % 20 == 0) { cout << endl; } } cout << endl;
    // for(int i = k - min(8, n); i < min(n, k + 8); ++i) { cout.width(4); cout << B[i] << ", "; } cout << endl;

    long key = B[k];
    cout << "search key = " << key << " at " << k << " in array B[]" << endl;

    cout << "Linear Search: ";
    copy(B, B + n, A);
	auto start = steady_clock::now();
    // for (int i = 0; i < n; ++i) {
    //     result = linear_search(A, n, A[i]);
    // }
    result = linear_search(A, n, key);
	auto end = steady_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
    cout << "Elapsed time: " << duration << " us, " << "Average time: " << double(duration) / n << endl;
    // for(int i = 0; i < n; ++i) { cout.width(4); cout << A[i] << ", ";  if ((i + 1) % 20 == 0) { cout << endl; } } cout << endl;
    if (result < 0) { cout << key << " is not found" << endl; } else {  cout << key << " is found at " << result << endl; }

    cout << "Partitional Linear Search: ";
	start = steady_clock::now();
    // for (int i = 0; i < n; ++i) {
    //     result = partitional_linear_search(A, n, 22, A[i]);
    // }
    result = partitional_linear_search(A, n, 22, key);
	end = steady_clock::now();
    duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
    cout << "Elapsed time: " << duration << " us, " << "Average time: " << double(duration) / n << endl;
    // for(int i = 0; i < n; ++i) { cout.width(4); cout << A[i] << ", ";  if ((i + 1) % 20 == 0) { cout << endl; } } cout << endl;
    if (result < 0) { cout << key << " is not found"<< endl; } else { cout << key << " is found at " << result << endl; }
    
    // cout << "Linear Search Recursive: ";
    // copy(B, B + n, A);
	// start = steady_clock::now();
    // long *r = linear_search_recursive(A, n, 5, key);
	// end = steady_clock::now();
    // cout << "Elapsed time: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " us" << endl;
    // // for(int i = 0; i < n; ++i) { cout.width(4); cout << A[i] << ", ";  if ((i + 1) % 20 == 0) { cout << endl; } } cout << endl;
    // if (r == 0) { cout << key << " is not found"<< endl; } else { cout << key << " is found at " << (*r)/4 << endl; }

    copy(B, B + n, A);
	start = steady_clock::now();
    sort(A, A + n);
	end = steady_clock::now();
    cout << "Sorted Array: " << endl;
    cout << "A[" << k << "] = ";
    for(int i = 0; i < n; ++i) { cout.width(4); cout << A[i] << ", ";  if ((i + 1) % 20 == 0) { cout << endl; } } cout << endl;
    // cout << "C[" << k - min(8, n) << "] = ";
    // for(int i = k - min(8, n); i < min(n, k + 8); ++i) { cout.width(4); cout << A[i] << ", "; } cout << endl;

    cout << "Binary Search: ";
	start = steady_clock::now();
    // for (int i = 0; i < n; ++i) {
    //     result = binary_search(A, n, A[i]);
    // }
    result = binary_search(A, n, key);
	end = steady_clock::now();
    duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
    cout << "Elapsed time: " << duration << " us, " << "Average time: " << double(duration) / n << endl;
    // for(int i = 0; i < n; ++i) { cout.width(4); cout << A[i] << ", ";  if ((i + 1) % 20 == 0) { cout << endl; } } cout << endl;
    if (result < 0) { cout << key << " is not found" << endl; } else {  cout << key << " is found at " << result << endl; }

    cout << "Golden Search: ";
	start = steady_clock::now();
    // for (int i = 0; i < n; ++i) {
    //     result = golden_search(A, n, A[i]);
    // }
    result = golden_search(A, n, key);
	end = steady_clock::now();
    duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
    cout << "Elapsed time: " << duration << " us, " << "Average time: " << double(duration) / n << endl;
    // for(int i = 0; i < n; ++i) { cout.width(4); cout << A[i] << ", ";  if ((i + 1) % 20 == 0) { cout << endl; } } cout << endl;
    if (result < 0) { cout << key << " is not found" << endl; } else {  cout << key << " is found at " << result << endl; }

    cout << "Interpolation Search: ";
	start = steady_clock::now();
    // for (int i = 0; i < n; ++i) {
    //     result = interpolation_search(A, n, A[i]);
    // }
    result = interpolation_search(A, n, key);
	end = steady_clock::now();
    duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
    cout << "Elapsed time: " << duration << " us, " << "Average time: " << double(duration) / n << endl;
    // for(int i = 0; i < n; ++i) { cout.width(4); cout << A[i] << ", ";  if ((i + 1) % 20 == 0) { cout << endl; } } cout << endl;
    if (result < 0) { cout << key << " is not found" << endl; } else {  cout << key << " is found at " << result << endl; }

    cout << "Fibonacci Search: ";
	start = steady_clock::now();
    // for (int i = 0; i < n; ++i) {
    //     result = fibonacci_search(A, n, key);
    // }
    result = fibonacci_search(A, n, key);
	end = steady_clock::now();
    duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
    cout << "Elapsed time: " << duration << " us, " << "Average time: " << double(duration) / n << endl;
    // for(int i = 0; i < n; ++i) { cout.width(4); cout << A[i] << ", ";  if ((i + 1) % 20 == 0) { cout << endl; } } cout << endl;
    if (result < 0) { cout << key << " is not found" << endl; } else {  cout << key << " is found at " << result << endl; }

    cout << "Fibonacci Search 2: ";
	start = steady_clock::now();
    // for (int i = 0; i < n; ++i) {
    //     result = fibonacci_search_2(A, n, A[i]);
    // }
    result = fibonacci_search_2(A, n, key);
	end = steady_clock::now();
    duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
    cout << "Elapsed time: " << duration << " us, " << "Average time: " << double(duration) / n << endl;
    // for(int i = 0; i < n; ++i) { cout.width(4); cout << A[i] << ", ";  if ((i + 1) % 20 == 0) { cout << endl; } } cout << endl;
    if (result < 0) { cout << key << " is not found" << endl; } else {  cout << key << " is found at " << result << endl; }
}