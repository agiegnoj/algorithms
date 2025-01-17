#include <vector>
#include <math.h>
#include <unordered_set>
#include <random>
#include <iostream>

using namespace std;

template <typename T>


class Primes{
    public :

    bool millerRabinPrimalityTest(long long num){
        if (num <2) return false;
        vector<long long> smallPrimes = {
            2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31
        };

        for (long long prime : smallPrimes){
            if (num == prime) return true;
            if (num % prime == 0) return false;
        }

        random_device rd;
        mt19937_64 gen(rd());
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

    vector<long> primeSieveErathosthenes(T max){
        vector<bool> isPrime (max+1, true);
        vector<T> primes;

        isPrime [0] = false;
        isPrime[1] = false;

        for (int i = 2; i<= sqrt(max); i++){
            for (int j = i*i;  j<= max; j+= i){
                isPrime[j] = false;
            }
        }

        for (int i = 2; i <= max; i++){
            if (isPrime[i])
            primes.push_back(i);

        }

        return primes;
    }


    vector<long long> getPrimeFactorization(long long num){
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

    long long nextPrime (long long start){
        if (start <  2) return 2;

        long long res = start % 2 == 0 ? start+1 : start+2;

        while (!millerRabinPrimalityTest(res)){
            res += 2;
        }

        return res;
    }


    vector<pair<long, long>> getGoldbachPairs(long num){
        if (num %2 ==1 || num < 2)return {};
        vector<pair<long, long>> goldbachPairs;

        vector<long> primes = primeSieveErathosthenes(num-2);
        unordered_set<long> used;

        for (int i = 0; i<= primes.size(); i++){
            if (used.find(primes[i]) != used.end()) continue;

            long diff = num-primes[i];
            if (binarySearch(primes, diff)){
                used.insert(diff);
                used.insert(primes[i]);
                goldbachPairs.push_back({primes[i], diff });
            }
        }

        return goldbachPairs;
    }


    private :

    bool binarySearch(const vector<long>& primes, long target){
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





