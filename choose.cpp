#include <iostream>
#include <vector>
#include <string.h>
#include <boost/dynamic_bitset.hpp>

using namespace std;

class Combination {
    public:
        vector < vector < bool > >  patterns;       /* Bit patterns used for finding subsets        */
        vector < vector < int > >   choices;        /* Sub sets of the set created from patterns    */
        vector < int >              o_set;          /* Original set of numbers                      */
        unsigned long               setsize;        /* Size of the original set                     */
        
        Combination(vector< int > input);           /* Constructor                                  */
        void findPatterns(int k);                   /* Identify the bit patterns with k 1 bits in
                                                     a set of n bits                                */
        int countOnes(unsigned int u);              /* Count the number of 1 bits in a bitset       */
};


Combination::Combination(vector< int > input) {
    
    for (int i = 0; i < input.size(); i++) {        /* Fill the o_set                               */
        o_set.push_back(input.at(i));
    }
    
    setsize = o_set.size();                         /* Set the setsize                              */
    
}

void Combination::findPatterns(int k) {
    
    int difference = setsize - k;
    boost::dynamic_bitset<> maximum(setsize, 0), minimum(setsize, 0);
    for (int i = difference; i < setsize; i++) { maximum[i] = 1; }
    for (int i = 0; i < setsize - difference; i++) { minimum[i] = 1; }
    
    unsigned long min = minimum.to_ulong();
    unsigned long max = maximum.to_ulong();
    
    while (min < max){
        int ones = countOnes(min);
        if (ones == 6) {
            vector < bool > pattern;
            boost::dynamic_bitset<> bits(setsize, min);
            for (size_t i = 0; i < setsize; i++) { pattern.push_back(bits[i]); }
            patterns.push_back(pattern);
        }
        min++;
    }
    
}

int Combination::countOnes(unsigned int u) {
    unsigned int uCount;
    
    uCount = u - ((u >> 1) & 033333333333) - ((u >> 2) & 011111111111);
    return ((uCount + (uCount >> 3)) & 030707070707) % 63;
}


/* Examples */
int main()
{
    Combination pulls({5, 10, 15, 20, 25, 30, 35, 40, 45});
    pulls.findPatterns(6);

    
    return 0;
}