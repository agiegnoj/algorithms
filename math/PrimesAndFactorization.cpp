#include <vector>
#include <math.h>
#include <unordered_set>
#include <random>
#include <algorithm>

using namespace std;

class PrimesAndFactorization{

    private:

    random_device rd;
    mt19937 gen;

    public:

    PrimesAndFactorization() : gen(rd()) {
        
    }

    bool millerRabinPrimalityTest(long long num){
        if (num <2) return false;
        vector<long long> smallPrimes = {
            2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31
        };

        for (long long prime : smallPrimes){
            if (num == prime) return true;
            if (num % prime == 0) return false;
        }

        uniform_int_distribution<long long> dis(2, num - 2);

        long long temp = num -1;
        long long exp = 1;
        while (temp % 2 == 0){
            temp /= 2;
            exp++;
        }


        for (int i = 0; i < 5; i++){
            long long base = dis(gen);

            long long res = powModM(base, temp, num);
            if (res == 1 ||res == num-1)continue;

            bool composite = true;

            for (int j = 0; j < exp; j++){
                res = powModM(res, 2, num);
                if (res  == num-1){
                    composite = false;
                    break;
                }         
            }
            if (composite)
            return false;
        }

        return true;

    }

    bool littleFermatPrimalityTest(long long num, int tests){

        if (num < 4)
        return num == 2 || num == 3;

        uniform_int_distribution<long long> dis(2, num - 2);

        for (int i = 0; i< tests; i++){
            long long base = dis(gen);

            if (powModM(base, num-1, num) != 1){
                return false;
            }
        }

        return true;
    }

    vector<long long> primeSieveErathosthenes(long long max){
        vector<bool> isPrime (max+1, true);
        vector<long long> primes;

        isPrime [0] = false;
        isPrime[1] = false;

        for (long long i = 2; i*i<= max; i++){
            if (!isPrime[i])continue;

            for (long long j = i*i;  j<= max; j+= i){
                isPrime[j] = false;
            }
        }

        for (long long i = 2; i <= max; i++){
            if (isPrime[i])
            primes.push_back(i);

        }

        return primes;
    }

    vector<long long> linearSieve(long long max){
        vector<long long> smallestFactor(max+1, 0);
        vector<long long> primes;

        for (long long x = 2; x <= max; x++){
            if (smallestFactor[x] == 0){
                primes.push_back(x);
                smallestFactor[x] = x;       
            }
            for (int y= 0; y < primes.size()  && primes[y] * x <= max; y++){
                smallestFactor[x*primes[y]] = primes[y];
                if (x % primes[y] == 0) break;
            }
        }
        return primes;
    }

    vector<long long> factorizationPollard(long long num){
        
        int retries = 0;
        vector<long long> factors;
        if (num <= 1) return factors;

        vector<long long> smallPrimes = {
            2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31
        };

        for (long long prime : smallPrimes){
            while (num % prime == 0){
                factors.push_back(prime);
                num /= prime;
            }
        }

        uniform_int_distribution<long long> dis(1, num);
    
        while (num != 1 && retries < 5){
            long long x = dis(gen);
            long long y = x;
            long long d = 1;

            while (d == 1){
                x = (x*x+1)%num;
                y = (y*y+1)%num;
                y = (y*y+1)%num;

                d = gcd(abs(x-y), num);
            }

            if (d != num && millerRabinPrimalityTest(d)){
                factors.push_back(d);
                num /= d;
                retries = 0;
            }else{
                retries++;
            }
      
        }

        if (num > 1)
        factors.push_back(num);

        return factors;
    }

    vector<long long> factorizationSlow(long long num){
        vector <long long> factors;

        for (long long i = 2; i*i <= num; i++){
            while (num % i == 0){
                factors.push_back(i);
                num /= i;
            }
        }

        if (num != 1){
            factors.push_back(num);
        }

        return factors;
    }


    vector<pair<long, long>> goldbachPairs(long long  num){
        if (num %2 ==1 || num < 2)return {};
        vector<pair<long, long>> goldbachPairs;

        vector<long long> primes = primeSieveErathosthenes(num-2);
        unordered_set<long long > used;

        for (int i = 0; i< primes.size(); i++){
            if (used.find(primes[i]) != used.end()) continue;

            long long diff = num-primes[i];
            if (binarySearch(primes, diff)){
                used.insert(diff);
                used.insert(primes[i]);
                goldbachPairs.push_back({primes[i], diff });
            }
        }

        return goldbachPairs;
    }


    private :

    bool binarySearch(const vector<long long>& primes, long long target){
        int left = 0; 
        int right = primes.size()-1;

        while (left <= right){
            int mid = left + (right-left)/2;
            if (primes[mid] == target)
            return true;

            else if (primes[mid] < target)
            left = mid+1;

            else right = mid-1;
        }

        return false;
    }


    long long powModM(long long base, long long exp, long long mod){
        base = base%mod;

        long long res = 1;
        long long factor = base;
        
        while (exp > 0){
            if (exp % 2 == 1){
                res =res * factor % mod;
            }

            factor = factor*factor %mod;
            exp /= 2;
        }
        return res;
    }
};

