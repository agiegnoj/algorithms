#include <random>
#include <cmath>

using namespace std;

class CarmichaelNumberTest {
public:
    bool isCarmichaelNumber(long long num) {
        if (num < 561) return false;

        if (primeFactorCheck(num)) {
            return littleFermatCheckRandomized(num);
        }

        return false;
    }

private:
    bool littleFermatCheckRandomized(long long num) {
        random_device rd;
        mt19937_64 gen(rd());
        uniform_int_distribution<long long> dis(2, num - 2);

        int testCount = 0;

        while (testCount < 30){
             long long base = dis(gen);

            if (gcd(base, num) != 1) {
                continue;
            }else{
                testCount++;
                if (powModM(base, num - 1, num) != 1) {
                return false;
            }
            }

            

        }

        for (int i = 0; i < 35; i++) {
           
        }

        return true;
    }

    long long powModM(long long base, long long exponent, long long mod) {
        long long factor = base % mod;
        long long res = 1;

        while (exponent > 0) {
            if (exponent % 2 == 1)
                res = res * factor % mod;
            factor = factor * factor % mod;
            exponent /= 2;
        }
        return res;
    }

    bool primeFactorCheck(long long num) {
        int count = 0;

    for (long long factor = 2; factor * factor <= num; factor++) {
        if (num % factor == 0) {
            count++;
            if (count >= 3) return true;
            while (num % factor == 0) {
                num /= factor;
            }
        }
    }

    if (num != 1)
    count++;

    return count >= 3;

    }
};



