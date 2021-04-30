// Bits Manipulate
//      bit_get(), bit_set(), bit_clear() and bit_toggle()
//      the implementations here are not automic.
// 
// The algorithms that count the set-bits in an integer
//      for-loop
//      while-loop
//      recursive
//      kernighan
//      lookup_table
//      pop_count
//      cpp-bitset
//      cpp-built-in
//
//  the following programs are:
//  couting how many bits that are set to 1 in a 32-bit integer.
//
#include <iostream>

using namespace std;

/* return the bit-i (1 or 0) of the number
 */
unsigned long bit_get(unsigned long n, int i)
{
    return (n >> i) & 1;
}
/* return the number with bit-i set
 */
unsigned long bit_set(unsigned long n, int i)
{
    return (n | (1 << i));
}
/* return the number with bit-i cleared
 */
unsigned long bit_clear(unsigned long n, int i)
{
    return (n & ~(1 << i));
}
/* the the number with the bit-i toggled
 */
unsigned long bit_toggle(unsigned long n, int i)
{
    return (n ^ (1 << i));
}

/* algorithm: iterate the bits one by one, 
 */
int bits_count_for_loop(unsigned long number) 
{
    int count = 0;
    for (int i = 0; i < (sizeof(number) * 8); ++i) {
        if ( (number & (1 << i)) ) {
            ++count;
        }
    }
    return count;
}
/* algorithm: check the bits one by one until the "bytes" is 0
 */
int bits_count_while_loop(unsigned long number)
{
    int count = 0;
    while (number) {
        count += number & 1;
        number = number >> 1;
    }
    return count;
}
/* algorithm: check the rightmost bit recursively
 * the total steps is less than 32.
 */
int bits_count_recursive(unsigned long number)
{
    if (number == 0) {
        return 0;
    }
    return (number & 1) + bits_count_recursive(number >> 1);
}
/* algorithm: Brian Kernighan's
 */
int bits_count_kernighan(unsigned long number)
{
    int count = 0;
    while (number) {
        number &= number - 1;
        ++count;
    }
    return count;
}

/* algorithm: lookup table
 * only takes 3 steps without building the table.
 * the fastest method if the table is built in advance.
 */
int bits_count_lookup_table(unsigned long number)
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

    return count;
}
/* algorithm: pop count
 * very fast and no extra memory
 */
int bits_count_pop_count(unsigned long n)
{   
    n = n - ((n >> 1) & 0x55555555);
    n = (n & 0x33333333) + ((n >> 2) & 0x33333333);
    n = ((n + (n >> 4) & 0x0F0F0F0F) * 0x1010101) >> 24;
    // the following code can replace the above line
    // n = (n + (n >> 4)) & 0x0F0F0F0F;
    // n = n + (n >> 8);
    // n = n + (n >> 16);
    // n = n & 0x3F;
    return n;
}

//
/* C++ bitset<>::count()
 * need to include the libary <bitset>
 */
#include <bitset>

int bits_count_cpp_bitset(unsigned long number)
{
    bitset<32> bs(number);
    return bs.count();
}

/* get the value of the most significant bit
 */
unsigned long bit_leftmost_set_bit_while_loop(unsigned long number)
{
    unsigned long shift_bit = 0x80000000;
    while ((number & shift_bit) == 0) {
        shift_bit >>= 1;
    }
    return shift_bit;
}
/* algorithm: bit smearing, 
 *   1) shift 1 to 2^(half size of the number) to make the less significant bits as all 1s.
 *   2) shift 1 and xor the all 1 number or plus 1 and shift 1 to get the value of MSB.
 */
unsigned long bit_leftmost_set_bit_smearing(unsigned long number)
{
    number |= number >> 1;
    number |= number >> 2;
    number |= number >> 4;
    number |= number >> 8;
    number |= number >> 16;
    number ^= number >> 1;
    return number;
}
/* algorithm: x = (int)log2() returns an integer, the pow(2,x) will get MSB value.
 */
#include <cmath>
int bit_leftmost_set_bit_math(unsigned long number)
{
    return pow(2, (int)log2(number));
}

/* swap the bit at p1 (from right) with the bit p2 (from right).
 * - do nothing if the two bits are the same.
 * - toggle the two bits when they are different.
 * - p1 and p2 must be less than sizeof(unsigned long)
 */
unsigned long bits_swap_two_bits(unsigned long n, int p1, int p2)
{
    if (((n >> p1) ^ (n >> p2)) & 1)
    {
        n ^= (1 << p1);
        n ^= (1 << p2);
    }
    return n;
}
/* swap the even bits with the odd bit of the number
 */
unsigned long bits_swap_even_odd_bits(unsigned long n)
{
    return ( ((n & 0xAAAAAAAA) >> 1) | ((n & 0x55555555) << 1) );
}

/* covert a fraction decimal (0.0 <> 1.0) to a string
 */
string bits_convert_to_string(double x)
{
    string sbits = "0.";

    while (x > 0) {
        if (sbits.size() >= 32) {
            cout << "error: " << x << endl;
            break;
        }
        double r = x * 2;
        if (r >= 1) {
            sbits.append("1");
            x = r - 1;
        }
        else{
            sbits.append("0");
            x = r;
        }
    }
    return sbits;
}

/* testing driver code
 */
int main() 
{
    int bits_count = 0;
    unsigned long bytes = 0x5555;

    cout << "Count Bits, Input an Hex Integer: ";
    // cin >> hex >> bytes;
    // check signed integer, or only take unsigned integer

    cout.flags(ios::right | ios::hex | ios::showbase);
    cout << "number: " << bytes << endl;
    cout.setf(ios::dec, ios::basefield);

    bits_count = bits_count_for_loop(bytes);
    cout << "for_loop:  \t count = " << bits_count << endl;

    bits_count = bits_count_while_loop(bytes);
    cout << "while_loop: \t count = " << bits_count << endl;

    bits_count = bits_count_kernighan(bytes);
    cout << "kernighan: \t count = " << bits_count << endl;

    bits_count = bits_count_recursive(bytes);
    cout << "recursive: \t count = " << bits_count << endl;

    bits_count = bits_count_lookup_table(bytes);
    cout << "lookup_table: \t count = " << bits_count << endl;

    bits_count = bits_count_pop_count(bytes);
    cout << "pop_count:  \t count = " << bits_count << endl;

    bits_count = bits_count_cpp_bitset(bytes);
    cout << "cpp_bitset: \t count = " << bits_count << endl;

    cout << "cpp_builtin: \t count = " << __builtin_popcount(bytes) << endl;

    unsigned long n = 0xFF005555;
    int i = 9;
    cout << "get bit " << dec << i << ": " << hex << bit_get(n, i) << endl;
    n = bit_set(n, i);
    cout << "set bit " << dec << i << ": " << hex << n << endl;
    i++;
    n = bit_clear(n, i);
    cout << "clear bit " << dec << i << ": " << hex << n << endl;
    n = bit_toggle(n, i);
    cout << "toggle bit " << dec << i << ": " << hex << n << endl;
    cout.setf(ios::dec, ios::basefield);
    n = bit_clear(n, i - 1);
    cout << hex << n << endl;

    int  p1 = 2, p2 = 9; 
    n = bits_swap_two_bits(n, p1, p2);
    cout << "swap bit-" << dec << p1 << " with bit-" << p2 << ": " << hex << n << endl;
    n = bits_swap_two_bits(n, p2, p1);
    cout << "swap bit-" << dec << p2 << " with bit-" << p1 << ": " << hex << n << endl;
    n = bits_swap_even_odd_bits(n);
    cout << "swap even-odd: " << hex << n << endl;
    n = bits_swap_even_odd_bits(n);
    cout << "swap even-odd: " << hex << n << endl;

    double x = 0.75;
    cout << "bits to string: " << hex << x << " to " << bits_convert_to_string(x) << endl;

    return 0;
} 