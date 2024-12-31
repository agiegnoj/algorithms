#include <iostream>
using namespace std;

class PowerModM{
    public: 
    long long powModM(long long base, long long exponent, int mod){
        
        long long factor = base %mod;
        long long res = 1;

        while (exponent > 0){
            if (exponent % 2 == 1)
            res = res * factor % mod;
            factor = factor*factor %mod;
            exponent /= 2;
        }
        return res;
    }
};



