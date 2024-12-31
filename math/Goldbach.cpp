#include <vector>
#include <math.h>
#include <unordered_set>

using namespace std;

class Goldbach{
    public :

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

    vector<vector<long>> getGoldbachTriplets(long num){
        if (num%2 == 0 || num <= 5)return{};

        vector<vector<long>> goldbachTriplets;
        vector<long> primes = primeSieveErathosthenes(num-2);
        vector<long> triplet;

        findTriplets(primes, triplet, goldbachTriplets, 0, 0L, num, 0);

        return goldbachTriplets;

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

    void findTriplets(const vector<long>& primes, vector<long>& triplet, vector<vector<long>>& triplets, int index, long sum, long target, int count){

        if (count == 3){
            if (sum == target)
            triplets.push_back(triplet);
            return;
            }

        for (int i = index; i < primes.size(); i++){
            if (sum + primes[i] > target)break;
            triplet.push_back(primes[i]);
            findTriplets(primes, triplet, triplets, i, sum+primes[i], target, count+1 );
            triplet.pop_back();
        }
    }

    vector<long> primeSieveErathosthenes(long max){
        vector<bool> isPrime (max+1, true);
        vector<long> primes;

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
};



