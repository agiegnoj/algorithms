#include <math.h>
#include <iostream>

using namespace std;


class BinaryExponantiation{
    public: 
    
    double pow(int basis, int exponent){
        
        if (exponent == 0 || (basis == 0 && exponent == 0))
        return 1;

        bool nExp = false;
        double res = 1;
        double factor = basis;
        long n = exponent;

        if (exponent < 0){
            nExp = true;
            n = abs(n);
        }


        while (n > 0){
            if (n % 2 == 1)
            res *= factor;

            factor *= factor;
            n /= 2;

        }

        if (nExp)
        return 1/res;

        return res;

    }


};



