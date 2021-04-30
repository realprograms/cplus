//
#include <iostream>
#include <string>
#include <regex>
//
using namespace std;
//
// String Matching Algorithm
//
// Brute_force
bool string_match_linear(string str_text, string str_pattern, vector<int>& results)
{
    int sz1 = str_text.size();
    int sz2 = str_pattern.size();
    int i, j;
    for (i = 0; i < sz1; ++i ) {
        for (j = 0; j < sz2; ++j) {
            if (str_text[i + j] != str_pattern[j]) {
                break;
            }
        }
        if (j == sz2) {
            results.push_back(i);
        }
    }
    return (results.size() != 0);
}
/* Rabin-Karp
 */
vector<int> string_match_rabin_karp(string str_text, string str_pattern)
{

}
/* Knuth-Morris-pratt
 * longest prefix surfix (LPS)
 * lps[] has the same size as the string str_pattern.
 */
void string_match_kmp_lps(string str_pattern, int* lps)
{
    int sz = str_pattern.size();
    if (sz <= 0) {
        return;
    }
    lps[0] = 0;
    int j = 0;
    int i = 1;
    while (i < sz) // one for double loops
    {
        if (str_pattern[i] == str_pattern[j]) {
            lps[i] = ++j;
            ++i;
        }
        else if (j == 0) {
            lps[i] = 0;
            ++i;
        }
        else {
            j = lps[j - 1]; // going backward
        }
    }
}
bool string_match_kmp(string str_text, string str_pattern, vector<int>& results)
{
    int sz_txt = str_text.size();
    int sz_pat = str_pattern.size();
    int lps[sz_pat];

    if (sz_txt < sz_pat) {
        return false;
    }

    string_match_kmp_lps(str_pattern, lps);

    int i = 0, j = 0;
    while (i < sz_txt) 
    {
        if (str_text[i] == str_pattern[j]) {
            ++i; ++j;
        }
        if (j == sz_pat) {
            results.push_back(i - j);
            j = lps[j - 1];
        }
        else if (i < sz_txt && str_pattern[j] != str_text[i]) {
            j == 0 ? ++i : j = lps[j - 1];
        }
    }
    return (results.size() != 0);
}
/* Rabin-Karp
 */
bool string_match_rabin_karp(string str_text, string str_pattern, vector<int>& results)
{
    const int d = 4;    // the number of alphabets
    const int q = 97;   // a prime number
    int i, j;
    int sz_txt = str_text.size();
    int sz_pat = str_pattern.size();
    if (sz_txt < sz_pat) {
        return false;
    }

    int h = 0;
    for (i = 0; i < sz_pat; ++i) {
        h = (h * d) % q;
    }

    int p = 0;
    int t = 0;
    for (i = 0; i < sz_pat; ++i) {
        p = (d * p + str_pattern[i]) % q;
        t = (d * t + str_text[i]) % q;
    }

    for (i = 0; i < sz_txt - sz_pat; ++i) {
        if (p == t) {
            for (j = 0; j < sz_pat; ++j) {
                if (str_text[i + j] != str_pattern[j]) {
                    break;
                }
            }
            if (j == sz_pat) {
                results.push_back(i);
            }
        }
    }

    if (i < sz_txt - sz_pat) {
        t = (d*(t - str_text[i]*h) + str_text[i + sz_pat]) % q;
        if ( t < 0) {
            t = t + q;
        }
    }
    return (results.size() != 0);

}
/* testing driver code
 */
int main()
{
    string txt = "aabaacaadaabaaba";
    string pat = "aaba";
    regex e("(aaba)(.*)");
    if (regex_match(txt, e)) {
        cout << "string matched" << endl;
    }

    vector<int> r;
    bool b = string_match_linear(txt, pat, r);
    cout << "linear: found " << r.size() << " matches = ";
    for (int i = 0; i < r.size(); ++i) { cout << r[i] << ", "; } cout << endl;

    r.clear();
    string p1 = "abcdabeabf";   // lps[0 0 0 0 1 2 0 1 2 0]
    string p2 = "abcdeabfabc";  // lps[0 0 0 0 0 1 2 0 1 2 3]
    string p3 = "aabcadaabe";   // lps[0 1 0 0 1 0 1 2 3 0]
    string p4 = "aaaabaacd";    // lps[0 1 2 3 0 1 2 0 0]
    string tx1 = "ababcabcabababd";
    string pt1 = "ababd";
    int sz2 = pat.size();
    int lps[sz2];
    cout << "KMP LPS: ";
    string_match_kmp_lps(pat, lps);
    for (int i = 0; i < sz2; ++i) { cout << lps[i] << ", "; } cout << endl;
    string_match_kmp(txt, pat, r);
    cout << "KMP found " << r.size() << " matches = ";
    for (int i = 0; i < r.size(); ++i) { cout << r[i] << ", "; } cout << endl;

    r.clear();
    cout << "Rabin Karp: ";
    string_match_rabin_karp(txt, pat, r);
    cout << "found " << r.size() << " matches = ";
    for (int i = 0; i < r.size(); ++i) { cout << r[i] << ", "; } cout << endl;
}
