// Algorithms
//   FizzBuzz - 
//   Fabonacci -
//
// Sorting Algorithms:
//   Primary Key: an uniform key is used to compare the data objects for sorting.
//   Sorting techniques: key comparative sort, radix (digital) sort
//   sorting categorise: internal sorting (main memory), external sorting (disk)
// 
//   Simple Sort Methods:   worst       best
//     Bubble Sort          O(n*n)      O(n)
//     Insertion Sort       O(n*n)      O(n)
//     Selection Sort       O(n*n)      O(n*n)
//   Advanced Sort Methods
//     Quick Sort           O(n*n)      O(nlogn)
//     Merge Sort           O(nlogn)    O(nlogn)
//     Shell Sort           O(n(logn)^2)
//     Heap Sort            O(nlogn)    O(nlogn)
//     Radix Sort           O(m(n+r))
//     Binary Tree Sort (see play_with_tree.cpp)
//     Counting Sort
//     Bucket Sort
//
//   Search Algorithm
//     Linear Search
//     Binary Search
//     Interpolation Search
//     Fibonacci Search
//     
//   Hash Algorithm 
//
// Greedy Algorithm:
//    The greedy algorithm is a algorithmic paradigm that builds up
//    a solution piece by piece, always choosing the next piece that
//    offers the most obvious and immediate benefit.
//    it makes the optimal choice at each step as it attempts to find
//    the overall optimal way to solve the entire problem.
//    Relaxition techinque:
//
// Dynamic Algorithm
//   Both a mathematical optimization and a computer programming method. 
//   The method was developed by Richard Bellman in the 1950s.
//   Dynamic programming finds the optimal solution to subproblems and 
//   then makes an informed choice to combine the results of those 
//   subproblems to find the most optimum solution.
//   Dynamic programming works by using the memoization techique,
//   which stores the result of the subproblem.
//   Dynamic programming is mostly applied to recursive algorithms.
//   The subproblems are overlapping like the Fibonacci probblem.
//   If sub-problems can be nested recursively inside larger problems, 
//   so that dynamic programming methods are applicable, 
//
// BFS and DFS
//   BFS, Breadth First Search: Start from a vertex, explore all the
//        neighbor vertexes and push them into a queue, start exploring
//        the vextex from the queue one by one.
//   DFS, Depth First Search: Start from a vertex, if find a new neighbor
//        vertex, put the current vertext into stack, explore the new vertex.
// 
// Backtrack Algorithm
//   Find all the possible solutions 
//   (not the optimal solution as Greedy or dynamic methods)
//   Bruce Force Approch:
//   State Space Tree:
//   Bounding function:
//   Brand and Bound: a bruce force approch using BFS.
//   backtrack algorithm: a bruce force approch using DFS.
//
#include <iostream>
#include <chrono>
#include <climits>
// #include <random>
// #include <cstdlib>
// #include <algorithm>

using namespace std;
using namespace std::chrono;

/* FizzBuzz - given integer 1 to 100, 
 *            print Fizz for multiples of 3,
 *            print Buzz fpr multiples of 5,
 *            printf FizzBuzz for multiples of both 3 and 5.
 * time complexity:  O(n)
 * space complexity: 
 * input: n - max integer (starting from 1)
 * note:  must check the FizzBuzz (15) first
 */
void algorithm_fizz_buzz(int n)
{
    int i;
    for(i = 1; i <= n; ++i) {
        i % 15 == 0 ? cout << "FizzBuzz " : i % 3 == 0 ? cout << "Fizz " : i % 5 == 0 ? cout <<"Buzz " : cout << i << " ";
    }
    cout << endl;
    cout << "FizzBuzz: ";
    for(i = 1; i <= n; ++i) {
        if (i % 3 == 0) {
            cout << "Fizz";
            (i/3) % 5 == 0 ? cout << "Buzz " : cout << " ";
        } 
        else {
            i % 5 == 0 ? cout << "Buzz " : cout << i << " ";
        }
    }
    cout << endl;
}
/* Fabonacci Number
 *   get the n-th Fabonacci number, 
 *   Fabonacci number should start from 1, but the calculation start from 0.
 *   fibonacci(n) = fibonacci(n-1) + fibonacci(n-2)
 * input: the n-th 
 * implement: loop, recursive
 * note: 1) better to cache the previous number to spped up
 *          in c++, we can use set or map to remember previous results.
 *          in c, we only save the last two fibonacci numbners
 * note: 2) the max n is 93 for unsigned long long int
 * note: 3) the code could be modified to support the negtive Fabonacci numbers
 */
unsigned long long int algorithm_fibonacci_loop(unsigned int n)
{
    unsigned long long int fibonacci[2] = {0, 1};
    unsigned int i;
    for(i = 0; i < n; ++i) {
        fibonacci[i & 1] = fibonacci[(i - 1) & 1] + fibonacci[(i - 2) & 1];
        // cout << "n: " << i << " " << fibonacci[i & 1] << endl;
    }
    return fibonacci[i & 1];
}
// unsigned long long int fib_cache[1000] = { 0 }; // all 0s in C++

unsigned long long int algorithm_fibonacci_recursive(unsigned int n, unsigned long long int* fib_cache)
{
    if (n <= 0) {
        return 0;  // we could throw/raise an error for c++
    }
    else if (n == 1) {
        return 1;
    }
    // the fibonacci number hasn't been calculated yet if the cache value is 0
    if (fib_cache[n]) {
        return fib_cache[n];
    }
    // calculate the fibonacci number
    else {
        fib_cache[n] = algorithm_fibonacci_recursive(n - 1, fib_cache) + 
                       algorithm_fibonacci_recursive(n - 2, fib_cache);
        // cout << "N: " << n << " " << fib_cache[n] << endl;
        return fib_cache[n];
    }
}

/* tower of Hanoi
 * dynamic programming
 */
void algorithm_tower_hanoi(int n, char from_rod, char to_rod, char aux_rod)
{
    if (n == 1)  
    {  
        cout << "Move disk 1 from rod " << from_rod << " to rod " << to_rod << endl;  
        return;  
    }  
    algorithm_tower_hanoi(n - 1, from_rod, aux_rod, to_rod);  
    cout << "Move disk " << n << " from rod " << from_rod << " to rod " << to_rod << endl;  
    algorithm_tower_hanoi(n - 1, aux_rod, to_rod, from_rod); 
}

/* Bubble Sort
 * algorithm: compare the item with the next one in the array (or list)
 *            swap the two items if they are not in desired order
 *            loop the list a few of times until no item needs to be swapped.
 * implementation:  loop, recursive,
 * time complexity: average O(n*logn), worst O(n*n)
 * space complexity: O(1)
 */
void algorithm_bubble_sort(long *ay, int sz)
{   
    int count;
    do {
        count = 0;
        for (int i = 0; i < sz - 1; ++i) {
            if (ay[i] > ay[i + 1]) {
                long tmp = ay[i];
                ay[i] = ay[i + 1];
                ay[i + 1] = tmp;
                ++count;
            }
        }
    } while (count);
}
/* Insertion Sort
 * algorithm: start at the second from back, save the value
 *            compare the value with the next item:
 *            if the value is less (asending), move to the previous
 *            if the value is greater, insert the value by moving other items ahead
 *            repeat the compare and insert until get to the front
 * implementation: can be started from back or front.
 *            when sort linked list, must take care of the head and tail.     
 * time complexity: worst O(n*n)
 * space complexity: O(1)
 * applications:
 *    - number of elements in the array is small
 *    - the array is almost sorted, only a few of elements need to be sorted.
 */
void algorithm_insertion_sort(long *a, int sz)
{
    for (int k = sz - 2; k >= 0; --k) {
        int i = k + 1;
        long tmp = a[k];
        while ((i < sz) && (tmp > a[i])) {
            a[i - 1] = a[i];
            // cout << "k=" << k << " i=" << i << " tmp=" << tmp << " a[i]=" << a[i] << " a[i+1]=" << a[i+1] << endl;
            ++i;
        }
        a[i - 1] = tmp;
    }
}
/* Slection Sort
 * algorithm: start from the beginning (index 0),
 *            find the index of the least number, swap it to the front,
 *            work on the next item, find the least and swap, until the end.
 * implemetation: the simplest, could use binary search to find the least.
 * time complexity: O(n*n)
 * space complexity: O(1)
 * applications:
 */
void algorithm_selection_sort(long *a, int sz)
{
    for (int j = 0; j < sz; ++j) {
        int low = j;
        // find the index of the least number
        for (int i = j + 1; i < sz; ++i) {
            if (a[i] < a[low]) {
                low = i;
            }
        }
        // swap the least (to the front)
        long tmp = a[j];
        a[j] = a[low];
        a[low] = tmp;
    }
}
/* Quick Sort (Patition Exchange Sort)
 *    invented by C.A.R. Hoare to improve slection sort.
 *    the most efficient of the internal sorting methods.
 *    uses the hardware cache most effectively.
 * algorithm: one of divide-and-conquer methods
 *    choose the first as the pivot and start from both sides
 *    move the front pointer until find the item greater than the pivot
 *    move the back pointer until find the item less than the pivot
 *    swap the items in the two group (front and back). so
 *    all the items that less than the pivot to the front
 *    all the items that greater than the pivot to the back
 *    swap the first in the front with the first in the back
 *    recursively to quick-sort on the two groups.
 * implementations: recursive and iterative
 * time complexity: best O(nlogn), worst O(n*n)
 * space complexity: O(1)
 */
void algorithm_quick_sort(long *a, int first, int last)
{
    if (first >= last) {
        return;
    }
    long pivot = a[first];
    int i = first;
    int j = last;
    while(i < j) {
        while ((i < last) && (a[i] <= pivot)) { ++i; }
        while ((j > first) && (a[j] >= pivot)) { --j; }
        if (i < j) { 
            swap(a[i], a[j]);
        }
        // cout << "i=" << i << " j=" << j << " p=" << pivot << " ai=" << a[i] << " aj=" << a[j] << endl;
    }
    swap(a[j], a[first]);
    // cout << first << ":" << last << " p=" << pivot << " | i=" << i << " j=" << j << " \t";
    // for (int k = 0; k < 10; ++k) { cout << a[k] << " "; }  cout << endl;
    algorithm_quick_sort(a, first, j - 1);
    algorithm_quick_sort(a, j + 1, last);
}
/* Merge Sort
 *    efficient for external sorting, such as, data in a file.
 *    doesn't take advantage when the data is already in order.
 *    good for sorting linked list because no extra sub-arrays.
 * algorithm: one of the divide-and-conquer methods
 *    split the array into sub-array recursively until the arrays cannot be splited.
 *    merge sub-arrays, starting from the shortest array (one element).
 *    select the smaller (less) data and insert/replace it back to the orginal array.
 * implementations: iterative, recursive and linked merge sort
 * time complexity: always O(nlogn)
 * space complexity: O(n)
 * applications: 
 *    - sort the (huge) files on the disks.
 *    - sort the linked list, no extra memory needed.
 */
void algorithm_merge(long a[], int left, int middle, int right)
{
    int i, j, k; 
    int n1 = middle - left + 1; 
    int n2 = right - middle;
  
    int L[n1], R[n2];
  
    // split the array at the middle into two sub-arrays
    for (i = 0; i < n1; i++) 
        L[i] = a[left + i]; 
    for (j = 0; j < n2; j++) 
        R[j] = a[middle + 1 + j]; 
  
    i = 0;      // Initial index of first subarray 
    j = 0;      // Initial index of second subarray 
    k = left;   // Initial index of merged subarray 

    // merge the two sub-arrays back into the orginal array by
    // inserting the smaller data at the heads of the two arrays.
    while (i < n1 && j < n2) { 
        if (L[i] <= R[j]) { 
            a[k] = L[i]; 
            i++; 
        } 
        else { 
            a[k] = R[j]; 
            j++; 
        } 
        k++; 
    } 
    // copy the remaining elements of L[], if any 
    while (i < n1) { 
        a[k] = L[i]; 
        i++; 
        k++; 
    } 
    // Copy the remaining elements of R[], if any
    while (j < n2) { 
        a[k] = R[j]; 
        j++; 
        k++; 
    }
} 
void algorithm_merge_sort(long a[], int left, int right)
{ 
    if (left >= right) { 
        return;
    }
    // same as (l+r)/2, but avoids overflow for 
    int middle = left + (right - left) / 2; 
  
    algorithm_merge_sort(a, left, middle); 
    algorithm_merge_sort(a, middle + 1, right); 
    algorithm_merge(a, left, middle, right); 
} 
/* Shell Sort
 */
void algorithm_shell_half_sort(long a[], int sz)
{
    // Start with a big gap, then reduce the gap 
    for (int gap = sz/2; gap > 0; gap /= 2) 
    { 
        // cout << "gap=" << gap << endl;
        // Do a gapped insertion sort for this gap size. 
        // The first gap elements a[0..gap-1] are already in gapped order 
        // keep adding one more element until the entire array is gap sorted  
        for (int i = gap; i < sz; ++i) 
        { 
            // add a[i] to the elements that have been gap sorted 
            // save a[i] in temp and make a hole at position i 
            int temp = a[i]; 
            
            // cout << "gap=" << gap << " i=" << i << " " << temp << " a[i]=" << a[i];
  
            // shift earlier gap-sorted elements up until the correct  
            // location for a[i] is found 
            int j;             
            for (j = i; j >= gap && a[j - gap] > temp; j -= gap) {
                a[j] = a[j - gap]; 
                // cout << " j=" << j << " " << a[j] << " j-gap=" << j - gap << " " << a[j-gap];
            }
            //  put temp (the original a[i]) in its correct location 
            a[j] = temp; 
            // cout << "  # j=" << j << " a[j]=" << a[j] << endl;
        } 
        // for (int k = 0; k < sz; k++) { cout << a[k] << " "; } cout << endl;
    }   
}
/* Shell Sort
 *    invented by D. L. Shell to inprove the insertion and bubble sort.
 *    efficiently select the gap (shell) sizes, eg. 40, 13, 4, 1, etc.
 * algorithm:
 */
void algorithm_shell_sort(long a[], int sz)
{
    int k2, k1, k;
    int shell_size = sz;
    int change = 0;

    while (shell_size > 1) {
        k2 = 0;
        k1 = 1;
        // cout << "shell=" << shell_size << " k=" << k1 * 4 - k2 * 3;
        while ((k = k1 * 4 - k2 * 3) < shell_size) {
            k2 = k1;
            k1 = k;
        }
        k = k1;
        // cout << " k2=" << k2 << " k1=" << k1 << " k=" << k << endl;
        for (int i = k; i < sz; i++) {
            long tmp = a[i];
            int s = i - k;
            while (s >= 0 && tmp < a[s]) {
                a[s + k] = a[s];
                ++change;
                // cout << "swap " << change << ": " << i << "-" << s << "-" << s + k << " " << tmp << " " << a[s] << endl;
                s -= k;
            }
            a[s + k] = tmp;
        }
        // for (int j = 0; j < sz; j++) { cout << a[j] << " "; } cout << endl;
        shell_size = k;
    }
}
/* Radix (Exchange) Sort
 * algorithm: similar to the quick sort, instead of comparing the data,
 *    radix compares the bits (from msb to lsb).
 * implementation: recursive, iterative
 * time complexity: 
 * application: 
 *    more suitable for hardware implementation.
 */
void algorithm_radix_sort(long a[], int first, int last, int bitnum)
{
    if (first >= last || bitnum < 0 ) {
        return;
    }
    int i = first;
    int j = last;
    while (i != j) {
        while (i < j && !((a[i] >> bitnum) & 1)) {
            ++i;
        }
        while (j > i && ((a[j] >> bitnum) & 1)) {
            --j;
        }
        swap(a[i], a[j]);   // c++98 <algorithm>, c++11 <utility>
    }
    if ( !((a[last] >> bitnum) & 1) ) {
        ++j;
    }
    // cout << "bit=" << bitnum << " i=" << i << " j=" << j << " " << a[i] << " " << a[j] << endl;
    algorithm_radix_sort(a, first, j - 1, bitnum - 1);
    algorithm_radix_sort(a, j, last, bitnum - 1);
}
/* Heap Adjust
 * algorithm: for the node (element) that has the index i,
 *            its left child is at 2*i, its right child is at 2*i + 1. 
 *            compare these three values, put the largest at i.
 *            continue the adjust if the node at i has been changed.
 */
void algorithm_heap_adjust(long a[], int sz, int i)
{
    int left = 2*i;
    int right = 2*i +1;

    int largest = left <= sz && a[left] > a[i] ? left : i;

    if(right <= sz and a[right] > a[largest] ) {
        largest = right;
    }
    if(largest != i ) {
        swap(a[i] , a[largest]);
        algorithm_heap_adjust(a, sz, largest);
    }
}
/* Heap Sort
 * algorithm: to easily calculate the heap tree index, we need index stat from 1.
 *            so make a new array its size 1 bigger than the orignal array.
 *            convert (adjust) the array to a heap tree, start at the middle.
 *            copy the root node to the far right, reduce the array size by 1.
 *            adjust the heap tree make sure the element at 1 is the root (max).
 *            contine the last two steps until array size is 0.
 * applications: priority queues
 */
void algorithm_heap_sort(long a[], int sz)
{
    // build the heap tree, start at the middle
    for(int i = sz >> 1 ; i >= 1 ; i-- )
    {
        algorithm_heap_adjust(a, sz, i);
        // for(int j = 0; j <= sz; ++j) { cout.width(4); cout << a[j] << ", ";  if ((j + 1) % 20 == 0) { cout << endl; } } cout << endl;
    }
    // sort hte max heap in ascending order
    for (int i = sz; i >= 2; i--) {
        swap(a[i], a[1]);
        algorithm_heap_adjust(a, i - 1, 1);
        // for(int j = 0; j <= sz; ++j) { cout.width(4); cout << a[j] << ", ";  if ((j + 1) % 20 == 0) { cout << endl; } } cout << endl;
    }
}

/* Linear Search
 * algorithm: search an array or linked list from the beginning one byone
 *            until the end of the array or list.
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
int algorithm_linear_search(long *a, int sz, long key)
{
    int i;
    for (i = 0; i < sz; ++i) {
        if (a[i] == key)
        return i;
    }
    return -1;
}
/* Binary Search
 *    search on a sorted list
 *    
 * algorithm: 
 *    cut the searching range by half after comparing the data at the middle.
 *    change the searching range to the first half or the back half.
 *    repeat the previous steps until find the key (first, last, middle are same)
 * implementations: iterative, recursive
 * time complexity: O(logn)
 * space complexity: O(1) for iterative
 */
int algorithm_binary_search(long a[], int sz, long key)
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
int algorithm_golden_search(long a[], int sz, long key) 
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
int algorithm_interpolation_search(long a[], int sz, long key)
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
int algorithm_fibonacci_search(long a[], int sz, long key)
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
  
        // cout << "step " << ++step << ": " << fib2 << "+" << fib1 << "=" << fibM << " ofs " << offset << " i=" << i << " a[i]=" << a[i] << endl;
        if (a[i] < key) 
        { 
            fibM  = fib1; 
            fib1 = fib2; 
            fib2 = fibM - fib1; 
            offset = i; 
            // cout << "stepA " << step << ": " << fib2 << "+" << fib1 << "=" << fibM << " ofs " << offset << endl;
        } 
        else if (a[i] > key) 
        { 
            fibM  = fib2; 
            fib1 = fib1 - fib2; 
            fib2 = fibM - fib1;
            // cout << "stepB " << step << ": " << fib2 << "+" << fib1 << "=" << fibM << " ofs " << offset << endl;
        } 
        else {
            return i; 
        }
    } 
    if(fib1 && a[offset+1] == key) {
        return offset+1; 
    }
    /*element not found. return -1 */
    return -1; 
}
int algorithm_fibonacci_search_2(long a[], int sz, long key)
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
/* Greedy Problem: minimum number of coins
 * return the min number of coins for the money
 */
#include <map>
int algorithm_greedy_min_coins(int money)
{
    const vector<int> coins = {1, 2, 5, 10, 25, 50, 100};
    int save = money;
    int sz = coins.size();
    int n = 0;
    for (int i = sz - 1; i >= 0; --i) {
        int m = money / coins[i];
        money = money - m * coins[i];
        n += m;
    }

    money = save;
    map<int, int> pay = {};
    for (int i = sz -1; i >= 0; --i) {
        int count = 0;
        while (money >= coins[i]) {
            pay[coins[i]] = ++count;
            // pay.insert(pair<int, int>(coins[i], count));
            money -= coins[i];
        }
    }
    cout << endl;
    for (map<int, int>::iterator it = pay.begin(); it != pay.end(); ++it) {
        cout << it->first << "-" << it->second << ", ";
    }
    cout << endl;
    return n;
}
/* Greedy Method: Fractional Knapsack 
 */

/* Greedy Method: Job Sequencing with Deadlines
 * schedule the tasks to get the maximum profit,
 * each task takes one unit time and must be finsihed by deadline.
 */
#include <vector>
#include <algorithm>
struct Job {
    int task, deadline, profit;
};
vector<Job> jobs {
    {1, 9, 15},
    {2, 2, 2},
    {3, 5, 18},
    {4, 7, 1},
    {5, 4, 25},
    {6, 2, 20},
    {7, 5, 8},
    {8, 7, 10},
    {9, 4, 12},
    {10, 3, 5}
};
int algorithm_greedy_job_sequencing(vector<Job>& jobs)
{
    sort(jobs.begin(), jobs.end(), 
        [](Job &a, Job &b) { return a.profit > b.profit; });

    // for (auto job: jobs) {
    //     cout << "job " << job.task << ",\tdeadline " << job.deadline << ",  profit " << job.profit << endl;
    // }

    int max_deadline  = 0;
    for (int i = 0; i < jobs.size(); i++) {
        if ( max_deadline < jobs[i].deadline) {
            max_deadline = jobs[i].deadline;
        }
    }
    int total_profit = 0;
    vector<int> schedule(max_deadline, -1);

    for (const Job &job: jobs) {
        for (int j = job.deadline - 1; j >= 0; j--) {
            if (j < max_deadline && schedule[j] == -1) {
                schedule[j] = job.task;
                total_profit += job.profit;
                break;
            }
        }
    }

    for (int j = 0; j < max_deadline; ++j) {
        cout << j << ":" << schedule[j] << ", ";
    }
    cout << endl;

    return total_profit;
}
/* Greedy Method: Huffman Coding*/

/* Greedy Method: Prims and Kruskals Spin Tree
 */

/* Dijkstra Algorithm (single source shortest Path)
 *   find the sortest path (respect to the cost) from the start node 
 *   to every node in the graph.
 * Algorithm: 
 *   cost[][] is the same as G[][] except changing the 0 to INFINITY.
 *   distance[] will include the results of all the nodes.
 *     initialize to INFINITY except the starting node [0].
 *   pred[] remembers the previous node that leads to the shortest distance.
 *   the outside while loop make sure every node is visited.
 *   the first for loop finds the shortest path in unvisited nodes
 *   the second for loop does the relaxation, 
 *   Relaxation:
 * Note: writen in C.
 */
#define INFINITY   999
#define MAX_VEC    10
void algorithm_greedy_dijkstra(const long g[MAX_VEC][MAX_VEC], int sz, long start)
{
    int i, j, next;
    long distance[sz];
    long cost[sz][sz];
    int  pred[sz] = {start};
    bool visited[sz] = {false};

    // replace the 0 in g[][] with INFINITY
    for (i = 0; i < sz; i++) {
        for (j = 0; j < sz; j++) {
            cost[i][j] = g[i][j] == 0 ? INFINITY : g[i][j];
        }
    }

    for (i = 0; i < sz; i++) {
        distance[i] = cost[start][i];
    }
    for (i = 0; i < sz; i++) { cout << distance[i] << " "; } cout << endl;

    distance[start] = 0;
    visited[start] = 1;
    int count = 1;

    while (count < sz - 1) {
        long minDistance = INFINITY;
        for (i = 0; i < sz; ++i) {
            if (distance[i] < minDistance && !visited[i]) {
                minDistance = distance[i];
                next = i;
            }
        }
        visited[next] = 1;
        // for (i = 0; i < sz; i++) { cout << distance[i] << " "; } cout << endl;
        for (i = 0; i < sz; ++i) {
            if (!visited[i]) {
                if (minDistance + cost[next][i] < distance[i]) {
                    distance[i] = minDistance + cost[next][i];
                    pred[i] = next;
                }
            }
        }
        // for (i = 0; i < sz; i++) { cout << distance[i] << " "; } cout << endl;
        // for (i = 0; i < sz; i++) { cout << pred[i] << " "; } cout << endl;
        ++count;
    }
    for (i = 0; i < sz; ++i) {
        cout << "distance to " << i << ": " << distance[i] << endl;
    }
}

/* Dynamic Programming
 */
// a structure to represent a weighted edge in graph 
struct Edge { 
    int src, dest, weight; 
}; 
// a structure to represent a connected, directed and 
// weighted graph 
struct Graph { 
    // V-> Number of vertices, E-> Number of edges 
    int V, E; 
  
    // graph is represented as an array of edges. 
    struct Edge* edge; 
}; 
// Creates a graph with V vertices and E edges 
struct Graph* createGraph(int V, int E) 
{ 
    struct Graph* graph = new Graph; 
    graph->V = V; 
    graph->E = E; 
    graph->edge = new Edge[E]; 
    return graph; 
} 
void algorithm_dynamic_bellman_ford(struct Graph* graph, int src) 
{ 
    int V = graph->V; 
    int E = graph->E; 
    int dist[V]; 
  
    // Step 1: Initialize distances from src to all other vertices 
    // as INFINITE 
    for (int i = 0; i < V; i++) 
        dist[i] = INT_MAX; 
    dist[src] = 0; 
  
    // Step 2: Relax all edges |V| - 1 times. A simple shortest 
    // path from src to any other vertex can have at-most |V| - 1 
    // edges 
    for (int i = 1; i <= V - 1; i++) { 
        for (int j = 0; j < E; j++) { 
            int u = graph->edge[j].src; 
            int v = graph->edge[j].dest; 
            int weight = graph->edge[j].weight; 
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) 
                dist[v] = dist[u] + weight; 
        } 
    } 
  
    // Step 3: check for negative-weight cycles.  The above step 
    // guarantees shortest distances if graph doesn't contain 
    // negative weight cycle.  If we get a shorter path, then there 
    // is a cycle. 
    for (int i = 0; i < E; i++) { 
        int u = graph->edge[i].src; 
        int v = graph->edge[i].dest; 
        int weight = graph->edge[i].weight; 
        if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) { 
            printf("Graph contains negative weight cycle"); 
            return; // If negative cycle is detected, simply return 
        } 
    } 
  
    return; 
} 
/* Matrix Chain Multiplication
 * give the dimentions of n(number) of matrixes, 
 * find the minimum number of the multiplications
 */
int algorithm_dynamic_matrix_chain_recursive(int dims[], int i, int j)
{
    if (j == i) {
        return 0;
    }
    int min_cost = INT_MAX;
    for (int k = i; k < j; k++) {
        int cost = algorithm_dynamic_matrix_chain_recursive(dims, i, k);
        cost += algorithm_dynamic_matrix_chain_recursive(dims, k + 1, j);
        cost += dims[i - 1] * dims[k] * dims[j];
        if (cost < min_cost) {
            min_cost = cost;
        }
    }
    return min_cost;
}
/* Longest Common Sequence (LCS)
 * find the chars that are in both strings and in same order.
 */
int algorithm_lcs_recursive(string s1, int i, string s2, int j)
{
    if (s1[i] == '\0' || s2[j] == '\0') {
        return 0;
    }
    if (s1[i] == s2[j]) {
        return 1 + algorithm_lcs_recursive(s1, i + 1, s2, j + 1);
    }
    else {
        return max(algorithm_lcs_recursive(s1, i + 1, s2, j), 
                   algorithm_lcs_recursive(s1, i, s2, j + 1));
    }
}
/* time complexity: O(m*n)
 */
int algorithm_dynamic_lcs(string s1, string s2)
{
    int z1 = s1.size() + 1;
    int z2 = s2.size() + 1;
    int lcs[z1][z2] = {0}; // not working for two demension
    int m = 0;
    for (int i = 0; i < z1; i++) {
        for (int j = 0; j < z2; j++) {
            lcs[i][j] = 0;
        }
    }
    for (int i = 1; i < z1 ; ++i) {
        for (int j = 1; j < z2; ++j) {
            if (s1[i - 1] == s2[j - 1]) {
                lcs[i][j] = 1 + lcs[i - 1][j - 1];
            }
            else {
                lcs[i][j] = max(lcs[i - 1][j], lcs[i][j - 1]);
                if (m < lcs[i][j]) {
                    m = lcs[i][j];
                }
            }
        }
    }
    // for (int i = 0; i < z1; i++) {
    //     for (int j = 0; j < z2; j++) {
    //         cout << lcs[i][j] << ", ";
    //     }
    //     cout << endl;
    // }
    return m;
}
/* Reliability Design
 * choose the number of parts to get the highest reliability under the budget.
 */
#include <map> 
int algorithm_dynamic_reliability_design(map<int, float>& parts, int budget)
{
    return 0;
}
// DFS & BFS
// Articulation Point
//
/* testing driver code
 */
int main()
{
    cout << "long long: " << sizeof(long long int) << ", long: " << sizeof(long int) << ", int: " << sizeof(int);
    cout << ", short: " << sizeof(short) << ", char: " << sizeof(char) << ", bool: " << sizeof(bool);
    cout << ", unsigned: " << sizeof(unsigned) << ", long: " << sizeof(long) << endl;

    cout << "FizzBuzz: ";
    algorithm_fizz_buzz(25);

    int n = 93;
    // cout << "Input an integer: ";
    // cin >> n;
	auto start = chrono::steady_clock::now();
    unsigned long long int afl = algorithm_fibonacci_loop(n);
	auto end = chrono::steady_clock::now();
    cout << "Fabonacci loop: (" << n << ") = " << afl << " " << hex << afl << ", " << dec;
    cout << "Elapsed time in nanoseconds : " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << " us" << endl;

    n = 93;
    unsigned long long int fib_cache[n+1] = { 0 };
    for (int i = 0; i < n+1; ++i) { fib_cache[i] = 0; }
	start = chrono::steady_clock::now();
    unsigned long long int afr = algorithm_fibonacci_recursive(n, fib_cache);
	end = chrono::steady_clock::now();
    cout << "Fabonacci recursive: (" << n << ") = " << afr << " " << hex << afr << ", " << dec;
    cout << "Elapsed time in nanoseconds : " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << " us" << endl;

	start = chrono::steady_clock::now();
    unsigned long long int fib_last = 0;
    for(int i = 0; i < 100; ++i) {
        // if (algorithm_fibonacci_recursive(i, fib_cache) > UINT_FAST64_MAX/2) {
        //     break;
        // }
        unsigned long long int x = algorithm_fibonacci_loop(i);
        if (x < fib_last) {
            break;
        }
        fib_last = x;
        // cout << i << ": " << x << " " << hex << x << dec << endl;
        n = i;
    }
	end = chrono::steady_clock::now();
    cout << "Max Fabonacci number for long long int: (" << n << ") " << fib_last << ", ";
	cout << "Elapsed time in microseconds : " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " us" << endl;

    n = 4;
    algorithm_tower_hanoi(n, 'A', 'B', 'C');

    n = 18;
    long A[n];
    long B[n];        // int interpolation = first + (last - first) * (key - a[first]) / (a[last] - a[first]);
        // unsigned long long interpolation = (unsigned long long)(last - first) * (key - a[first]) / (a[last] - a[first]);

    cout << "---- generate " << n << " random numbers ----" << endl;
    for(int i = 0; i < n; ++i) { B[i] = rand() % (n * 10); }
    cout << "Original Array: " << endl;
    for(int i = 0; i < n; ++i) { cout.width(4); cout << B[i] << ", ";  if ((i + 1) % 20 == 0) { cout << endl; } } cout << endl;

    cout << "Bubble Sort: ";
    for(int i = 0; i < n; ++i) { A[i] = B[i]; }
	start = steady_clock::now();
    algorithm_bubble_sort(A, n);
	end = steady_clock::now();
    cout << "Elapsed time: " << duration_cast<microseconds>(end - start).count() << " us" << endl;
    for(int i = 0; i < n; ++i) { cout.width(4); cout << A[i] << ", ";  if ((i + 1) % 20 == 0) { cout << endl; } } cout << endl;

    cout << "Insertion Sort: ";
    for(int i = 0; i < n; ++i) { A[i] = B[i]; }
	start = chrono::steady_clock::now();
    algorithm_insertion_sort(A, n);
	end = chrono::steady_clock::now();
    cout << "Elapsed time: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " us" << endl;
    for(int i = 0; i < n; ++i) { cout.width(4); cout << A[i] << ", ";  if ((i + 1) % 20 == 0) { cout << endl; } } cout << endl;

    cout << "Selection Sort: ";
    for(int i = 0; i < n; ++i) { A[i] = B[i]; }
	start = chrono::steady_clock::now();
    algorithm_selection_sort(A, n);
	end = chrono::steady_clock::now();
    cout << "Elapsed time: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " us" << endl;
    for(int i = 0; i < n; ++i) { cout.width(4); cout << A[i] << ", ";  if ((i + 1) % 20 == 0) { cout << endl; } } cout << endl;

    cout << "Quick Sort: ";
    for(int i = 0; i < n; ++i) { A[i] = B[i]; }
    // long C[] = {33, 60, 5, 15, 25, 12, 45, 70, 35, 7};
	start = chrono::steady_clock::now();
    algorithm_quick_sort(A, 0, n - 1);
	end = chrono::steady_clock::now();
    cout << "Elapsed time: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " us" << endl;
    for(int i = 0; i < n; ++i) { cout.width(4); cout << A[i] << ", ";  if ((i + 1) % 20 == 0) { cout << endl; } } cout << endl;

    cout << "Merge Sort: ";
    for(int i = 0; i < n; ++i) { A[i] = B[i]; }
	start = chrono::steady_clock::now();
    algorithm_merge_sort(A, 0, n - 1);
	end = chrono::steady_clock::now();
    cout << "Elapsed time: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " us" << endl;
    for(int i = 0; i < n; ++i) { cout.width(4); cout << A[i] << ", ";  if ((i + 1) % 20 == 0) { cout << endl; } } cout << endl;

    cout << "Shell Half: ";
    for(int i = 0; i < n; ++i) { A[i] = B[i]; }
	start = chrono::steady_clock::now();
    algorithm_shell_half_sort(A, n);
	end = chrono::steady_clock::now();
    cout << "Elapsed time: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " us" << endl;
    for(int i = 0; i < n; ++i) { cout.width(4); cout << A[i] << ", ";  if ((i + 1) % 20 == 0) { cout << endl; } } cout << endl;

    cout << "Shell Sort: ";
    for(int i = 0; i < n; ++i) { A[i] = B[i]; }
	start = steady_clock::now();
    algorithm_shell_sort(A, n);
	end = steady_clock::now();
    microseconds duration(duration_cast<microseconds>(end - start));
    cout << "Elapsed time: " << duration.count() << " us" << endl;
    for(int i = 0; i < n; ++i) { cout.width(4); cout << A[i] << ", ";  if ((i + 1) % 20 == 0) { cout << endl; } } cout << endl;

    cout << "Radix Sort: ";
    for(int i = 0; i < n; ++i) { A[i] = B[i]; }
	start = steady_clock::now();
    algorithm_radix_sort(A, 0, n - 1, sizeof(A[0]) * 4 - 1);    // max_bits = 31 (sizeof(long) * 4 - 1))
	end = steady_clock::now();
    cout << "Elapsed time: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " us" << endl;
    for(int i = 0; i < n; ++i) { cout.width(4); cout << A[i] << ", ";  if ((i + 1) % 20 == 0) { cout << endl; } } cout << endl;

    cout << "Heap Sort: ";
    long D[n+1] = {0};
    for(int i = 0; i < n; ++i) { D[i+1] = B[i]; }
	start = steady_clock::now();
    algorithm_heap_sort(D, n); 
	end = steady_clock::now();
    cout << "Elapsed time: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " us" << endl;
    for(int i = 0; i < n + 1; ++i) { cout.width(4); cout << D[i] << ", ";  if ((i + 1) % 20 == 0) { cout << endl; } } cout << endl;

    /* save the sorted array for later tests
     */
    long C[n];
    for(int i = 0; i < n; ++i) { C[i] = A[i]; }
    long key = 5002;
    int result;

    cout << "Linear Search: ";
    for(int i = 0; i < n; ++i) { A[i] = B[i]; }
	start = steady_clock::now();
    result = algorithm_linear_search(A, n, key);
	end = steady_clock::now();
    cout << "Elapsed time: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " us" << endl;
    // for(int i = 0; i < n; ++i) { cout.width(4); cout << A[i] << ", ";  if ((i + 1) % 20 == 0) { cout << endl; } } cout << endl;
    if (result < 0) { cout << key << " is not found" << endl; } else {  cout << key << " is found" << endl; }

    cout << "Binary Search: ";
    for(int i = 0; i < n; ++i) { A[i] = C[i]; }
	start = steady_clock::now();
    for (int i = 0; i < n; ++i) {
        result = algorithm_binary_search(A, n, A[i]);
    }
	end = steady_clock::now();
    cout << "Elapsed time: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " us" << endl;
    // for(int i = 0; i < n; ++i) { cout.width(4); cout << A[i] << ", ";  if ((i + 1) % 20 == 0) { cout << endl; } } cout << endl;
    if (result < 0) { cout << key << " is not found" << endl; } else {  cout << key << " is found" << endl; }

    cout << "Golden Search: ";
    for(int i = 0; i < n; ++i) { A[i] = C[i]; }
	start = steady_clock::now();
    for (int i = 0; i < n; ++i) {
        result = algorithm_golden_search(A, n, A[i]);
    }
	end = steady_clock::now();
    cout << "Elapsed time: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " us" << endl;
    // for(int i = 0; i < n; ++i) { cout.width(4); cout << A[i] << ", ";  if ((i + 1) % 20 == 0) { cout << endl; } } cout << endl;
    if (result < 0) { cout << key << " is not found" << endl; } else {  cout << key << " is found" << endl; }

    cout << "Interpolation Search: ";
    for(int i = 0; i < n; ++i) { A[i] = C[i]; }
	start = steady_clock::now();
    for (int i = 0; i < n; ++i) {
        result = algorithm_interpolation_search(A, n, A[i]);
    }
	end = steady_clock::now();
    cout << "Elapsed time: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " us" << endl;
    // for(int i = 0; i < n; ++i) { cout.width(4); cout << A[i] << ", ";  if ((i + 1) % 20 == 0) { cout << endl; } } cout << endl;
    if (result < 0) { cout << key << " is not found" << endl; } else {  cout << key << " is found at " << result << endl; }

    cout << "Fibonacci Search: ";
    for(int i = 0; i < n; ++i) { A[i] = C[i]; }
	start = steady_clock::now();
    for (int i = 0; i < n; ++i) {
        result = algorithm_fibonacci_search(A, n, A[i]);
    }
	end = steady_clock::now();
    cout << "Elapsed time: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " us" << endl;
    // for(int i = 0; i < n; ++i) { cout.width(4); cout << A[i] << ", ";  if ((i + 1) % 20 == 0) { cout << endl; } } cout << endl;
    if (result < 0) { cout << key << " is not found" << endl; } else {  cout << key << " is found at " << result << endl; }

    cout << "Fibonacci Search 2: ";
    for(int i = 0; i < n; ++i) { A[i] = C[i]; }
	start = steady_clock::now();
    for (int i = 0; i < n; ++i) {
        // result = algorithm_fibonacci_search_2(A, n, A[i]);
    }
	end = steady_clock::now();
    cout << "Elapsed time: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " us" << endl;
    // for(int i = 0; i < n; ++i) { cout.width(4); cout << A[i] << ", ";  if ((i + 1) % 20 == 0) { cout << endl; } } cout << endl;
    if (result < 0) { cout << key << " is not found" << endl; } else {  cout << key << " is found at " << result << endl; }

    cout << "Greedy Problem - min_coins: ";
    n = algorithm_greedy_min_coins(94);
    cout << "number of coins: " << n << endl;

    cout << "Greedy Problem - job sequencing with deadline: " << endl;
    n = algorithm_greedy_job_sequencing(jobs);
    cout << "profit: " << n << endl;

    cout << "Greedy Method - Dijkstra Shortest Path: " << endl;
    n = 7;
    const long G[MAX_VEC][MAX_VEC] = {
        {0, 0, 1, 2, 0, 0, 0}, 
        {0, 0, 2, 0, 0, 3, 0}, 
        {1, 2, 0, 1, 3, 0, 0}, 
        {2, 0, 1, 0, 0, 0, 1}, 
        {0, 0, 3, 0, 0, 2, 0},
        {0, 3, 0, 0, 2, 0, 1},
        {0, 0, 0, 1, 0, 1, 0}
    };
    algorithm_greedy_dijkstra(G, n, 0);

    // Matrix Chain Multiplication
    int dims[] = {10, 30, 5, 60};
    // int dims[] = {5, 4, 6, 2, 7};
    n = sizeof(dims) / sizeof(dims[0]);
    cout << "min cost of matrix chain multiplication: ";
    cout << algorithm_dynamic_matrix_chain_recursive(dims, 1, n - 1) << endl;

    cout << "Longest Common Sequence: ";
    string s1 = "stone";
    string s2 = "longest";
    n = algorithm_lcs_recursive(s1, 0, s2, 0);
    cout << "recursive: " << n << ", ";
    n = algorithm_dynamic_lcs(s1, s2);
    cout << "dynamic: " << n << endl;
} 

