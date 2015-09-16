//
//  main.cpp
//  Permute
//
//  Created by Winning Algorithms on 9/9/15.
//  Copyright (c) 2015 Winning Algorithms. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string.h>
#include <boost/dynamic_bitset.hpp>

using namespace std;

int countOnes(unsigned int u)
{
    unsigned int uCount;
    
    uCount = u - ((u >> 1) & 033333333333) - ((u >> 2) & 011111111111);
    return ((uCount + (uCount >> 3)) & 030707070707) % 63;
}

int choose(int larger_vector, int smaller_vector){
    
    int difference = larger_vector - smaller_vector;
    boost::dynamic_bitset<> maximum(larger_vector, 0);
    boost::dynamic_bitset<> minimum(larger_vector, 1);
    for (int i = difference; i < larger_vector; i++) { maximum[i] = 1; }

    cout << maximum << endl;
    cout << minimum << endl;
    
    int min = 0b000111111;
    int max = 0b111111000;
    
    while (min < max){
        int ones = countOnes(min);
        if (ones == 6) {
            vector < bool > pattern;
            boost::dynamic_bitset<> bits(larger_vector, min);
            for (size_t i = 0; i < larger_vector; i++) { pattern.push_back(bits[i]); }
            patterns.push_back(pattern);
        }
        min++;
    }
    
}


/* Examples */
int main()
{
    choose(9, 6);
   
    return 0;
}