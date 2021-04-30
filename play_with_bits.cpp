// study the algoriths that deal with bits

#include <iostream>
// #include <algorithm>
// #include <bits>
// #include <bits/stdc++.h>
#include <bitset>

using namespace std;
  
static int steps = 0;  // counts the steps (loops) to calculate the bits

/* algorithm: iterate over the bits, 32 steps
 */
int bit_count_set_bits_for_loop(int bytes) 
{
    int count = 0;
    for (int i = 0; i < (sizeof(bytes) * 8); ++i) {
        ++steps;
        if ( (bytes & (1 << i)) ) {
            ++count;
        }
    }
    return count;
}
/* algorithm: steps is less than 32
 */
int bit_count_set_bits_while_loop(int bytes)
{
    int count = 0;
    while (bytes) {
        ++steps;
        count += bytes & 1;
        bytes = bytes >> 1;
    }
    return count;
}
/* algorithm: recursive
 */
int bit_count_set_bits_recursive(unsigned int number)
{
    ++steps;
    if (number == 0) {
        return 0;
    }
    return (number & 1) + bit_count_set_bits_recursive(number >> 1);
}
/* algorithm: Brian Kernighan's
 */
int bit_count_set_bits_kernighan(int bytes)
{
    int count = 0;
    while (bytes) {
        ++steps;
        bytes &= bytes - 1;
        ++count;
    }
    return count;
}

/* algorithm: lookup table
 */
int bit_count_set_bits_lookup_table(unsigned int number)
{
    // the table can be generated statically before this call 
    int bits_set_table[256];

    bits_set_table[0] = 0;  
    for (int i = 0; i < 256; i++) 
    {  
        bits_set_table[i] = (i & 1) +  bits_set_table[i >> 1];  
    }

    // int count = bits_set_table[number & 0xff] +  
    //             bits_set_table[(number >> 8) & 0xff] +  
    //             bits_set_table[(number >> 16) & 0xff] +  
    //             bits_set_table[(number >> 24)];

    char *bytes = (char *)&number; // don't use loop, don't care the endian
    int count = bits_set_table[ bytes[0] ] +  
                bits_set_table[ bytes[1] ] +  
                bits_set_table[ bytes[2] ] +  
                bits_set_table[ bytes[3] ];  

    steps = 3;  // fixed steps

    return count;
}
/* algorithm: pop count
 */
int bit_count_set_bits_pop_count(unsigned int n)
{   
    n = n - ((n >> 1) & 0x55555555);
    n = (n & 0x33333333) + ((n >> 2) & 0x33333333);
    n = (n + (n >> 4)) & 0x0F0F0F0F;
    n = n + (n >> 8);
    n = n + (n >> 16);
    n = n & 0x3F;
    return n;
}

/* C++ bitset<>::count()
 */
int bit_count_set_bits_cpp_bitset(unsigned int number)
{
    bitset<32> bs(number);
    return bs.count();
}

/* get the value of the most significant bit
 */
int bit_leftmost_set_bit_while_loop(unsigned int number)
{
    unsigned int shift_bit = 0x80000000;
    while ((number & shift_bit) == 0) {
        shift_bit >>= 1;
        ++steps;
    }
    return shift_bit;
}
/* algorithm: bit smearing, 
 *   1) shift 1 to 2^(half size of the number) to make the less significant bits as all 1s.
 *   2) shift 1 and xor the all 1 number or plus 1 and shift 1 to get the value of MSB.
 */
int bit_leftmost_set_bit_smearing(unsigned int number)
{
    number |= number >> 1;
    number |= number >> 2;
    number |= number >> 4;
    number |= number >> 8;
    number |= number >> 16;
    number ^= number >> 1;
    steps = 6;  // fixed
    return number;
}
/* algorithm: x = (int)log2() returns an integer, the pow(2,x) will get MSB value.
 */
// #include <math.h> for C
#include <cmath>
int bit_leftmost_set_bit_math(unsigned int number)
{
    return pow(2, (int)log2(number));
}

/* find the Kth significant bit
 */
unsigned int bit_kth_msb(unsigned int number, int k)
{
    return 0;
}
// first set bit from right

/* swaps two bits in an integer
 * input:   n:  unsigned integer, 32 bits
 *          p1: the position of bit 1, valid value: 0 - 31
 *          p2: the position of bit 2, valid value: 0 - 31
 * return:  n if p1 or p2 is invalid
 */
unsigned int bit_swap_two_bits(unsigned int n, int p1, int p2) 
{ 
    if ( (p1 | p2) & ~0x1F) {
        return n;
    }
    unsigned int bit1 =  (n >> p1) & 1; 
    unsigned int bit2 =  (n >> p2) & 1; 
    unsigned int x = (bit1 ^ bit2); 

    x = (x << p1) | (x << p2);
    x = x ^ n;

    return x;
} 

// generates bit masks

int main() 
{
    int bits_count = 0;
    unsigned int bytes = 0;

    cout << "Count Bits, Input an Hex Integer: ";
 //   cin >> hex >> bytes;
    bytes = 0x5555;

    // check signed integer, or only take unsigned integer

    cout.flags(ios::right | ios::hex | ios::showbase);
    cout << "number: " << bytes << endl;
    cout.setf(ios::dec, ios::basefield);

    steps = 0;
    bits_count = bit_count_set_bits_for_loop(bytes);
    cout << "for_loop:  \t count = " << bits_count << ", steps = " << steps << endl;

    steps = 0;
    bits_count = bit_count_set_bits_while_loop(bytes);
    cout << "while_loop: \t count = " << bits_count << ", steps = " << steps << endl;

    steps = 0;
    bits_count = bit_count_set_bits_kernighan(bytes);
    cout << "kernighan: \t count = " << bits_count << ", steps = " << steps << endl;

    steps = 0;
    bits_count = bit_count_set_bits_recursive(bytes);
    cout << "recursive: \t count = " << bits_count << ", steps = " << steps << endl;

    steps = 0;
    bits_count = bit_count_set_bits_lookup_table(bytes);
    cout << "lookup_table: \t count = " << bits_count << ", steps = " << steps << endl;

    steps = 0;
    bits_count = bit_count_set_bits_pop_count(bytes);
    cout << "pop_count:  \t count = " << bits_count << ", steps = " << steps << endl;

    bits_count = bit_count_set_bits_cpp_bitset(bytes);
    cout << "cpp_bitset: \t count = " << bits_count << endl;

    cout << "cpp_builtin: \t count = " << __builtin_popcount(bytes) << endl;

    steps = 0;
    unsigned msbit = bit_leftmost_set_bit_while_loop(bytes);
    cout << "MSB while_loop:\t msbit = " << hex << msbit << ", steps: " << steps << endl;
     
    steps = 0;
    msbit = bit_leftmost_set_bit_smearing(bytes);
    cout << "MSB smearing:\t msbit = " << hex << msbit << ", steps: " << steps << endl;

    msbit = bit_leftmost_set_bit_math(bytes);
    cout << "MSB math: \t msbit = " << hex << msbit << ", steps: " << 0 << endl;

    int p1 = 2, p2 = 11;
    unsigned int bits = bit_swap_two_bits(bytes, p1, p2);
    cout << "swap bit " << p1 << " with bit " << p2 << ", after swap: " << hex << bits << endl;

    return 0;
} 