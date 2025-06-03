#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;
template<typename T>

class BerleykampMassey{
    public:

    vector<T> minRecurrence(const vector<T>& sequence){
        T epsilon = (T)1e-9;
        vector<T> poly = {(T)1};
        vector<T>prevPoly = poly;
        T lastDiscrepancy = (T)1;
        int errors = 0;
        int size = sequence.size();
        int stepsWithoutError = 0;

        for (int i = 0; i< size; i++){
            T discrepancy = sequence[i];
        
            for (int j = 1; j <= errors; j++){
                if (j < poly.size())
                discrepancy += poly[j]*sequence[i-j];
            }

            if (abs(discrepancy) <= epsilon){
                stepsWithoutError++;
            }else if (2*errors <= i){
                vector<T> temp = poly;
                adjust(poly, prevPoly, discrepancy, lastDiscrepancy, stepsWithoutError);
                errors = i+1-errors;
                prevPoly = temp;
                lastDiscrepancy = discrepancy;
                stepsWithoutError = 1;

            }else{
                adjust(poly, prevPoly, discrepancy, lastDiscrepancy, stepsWithoutError);
                stepsWithoutError++;
            }
        }

        poly[0] = 1;

        reverse(poly.begin(), poly.end());
        return poly;
    }
    private:

    void adjust(vector<T>& poly, vector<T>& prevPoly, T& discrepancy, T& lastDiscrepancy, int stepsWithoutError){
        T factor = discrepancy/ lastDiscrepancy;
        vector<T> paddedPrevPoly (stepsWithoutError, 0);

        for (int x = 0; x < prevPoly.size(); x++){
            paddedPrevPoly.push_back(prevPoly[x]* factor);
        }

        if (poly.size() < paddedPrevPoly.size()) poly.resize(paddedPrevPoly.size());

        for (int i = 0; i< poly.size(); i++){
            poly[i]-= paddedPrevPoly[i];
        }

    }
};

int main(){
    vector<double> fib = {2, 2, 4, 6, 10, 16};
    BerleykampMassey <double> bm;
    vector <double> rec = bm.minRecurrence(fib);
    
}