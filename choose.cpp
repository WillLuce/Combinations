#include <iostream>
#include <vector>
#include <string.h>
#include <boost/dynamic_bitset.hpp>             /* STD has no way of building bit sets          */

using namespace std;

class Combination {
public:
    vector < vector < bool > >  patterns;       /* Bit patterns used for finding subsets        */
    vector < vector < int > >   choices;        /* Sub sets of the set; created from patterns   */
    vector < int >              orig_set;       /* Original set of numbers                      */
    unsigned long               setsize;        /* Size of the original set                     */
    
    Combination(vector< int > input);           /* Constructor                                  */
    
    void findPatternsOf(int k);                 /* Identify the bit patterns with k set bits    */
    void findCombinationsOf(int k);             /* Use the bit patterns to pick out subsets     */
    int  countOnes(unsigned int u);             /* Count the number of 1 bits in a bitset       */
};


Combination::Combination(vector< int > input) {
    
    for (const auto& number : input) {          /* Fill the orig_set                            */
        orig_set.push_back(number);
    }
    
    setsize = orig_set.size();
    
}

void Combination::findPatternsOf(int k) {
    
    int difference = setsize - k;
    boost::dynamic_bitset<> maximum(setsize, 0), minimum(setsize, 0);
    for (int i = difference; i < setsize; i++) { maximum[i] = 1; }
    for (int i = 0; i < setsize - difference; i++) { minimum[i] = 1; }
    
    unsigned long min = minimum.to_ulong();
    unsigned long max = maximum.to_ulong();
    
    while (min <= max){
        int ones = countOnes(min);
        if (ones == k) {
            vector < bool > pattern;
            boost::dynamic_bitset<> bits(setsize, min);
            for (size_t i = 0; i < setsize; i++) { pattern.push_back(bits[i]); }
            patterns.push_back(pattern);
        }
        min++;
    }
    
}

void Combination::findCombinationsOf(int k) {
    
    findPatternsOf(k);
    
    for (const auto& pattern : patterns) {
        vector< int > choice;
        for (int index = 0; index < setsize; index++) {
            if (pattern[index]) { choice.push_back(orig_set[index]); };
        }
        choices.push_back(choice);
        for (const auto& x : choice) { cout << x << " "; };
        cout << endl;
    }
}

/* Hamming Weight: http://stackoverflow.com/questions/109023/how-to-count-the-number-of-set-bits-in-a-32-bit-integer */
int Combination::countOnes(unsigned int u) {
    unsigned int uCount;
    
    uCount = u - ((u >> 1) & 033333333333) - ((u >> 2) & 011111111111);
    return ((uCount + (uCount >> 3)) & 030707070707) % 63;
}


/* Examples */
int main()
{
    Combination pulls({5, 10, 15, 20, 25, 30, 35, 40, 45});
    pulls.findCombinationsOf(6);
    cout << pulls.choices.size() << endl;
    
    
    return 0;
}