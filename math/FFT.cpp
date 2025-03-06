#include <vector>
#include <complex>
#include <cmath>
#include <iostream>
using namespace std;

class FFT {
    using cd = complex<double>;

public:

void fft(vector<cd>& p, bool inverse) {
    const double PI = acos(-1);
    const complex<double> i(0, 1);

    int n = p.size();
    int logN = 0;

    while ((1 << logN) < n) {
        logN++;
    }

    bitReversalPerm(p, logN);

    for (int s = 1; s <= logN; s++) {
        int m = 1 << s;  
        cd w_m = exp(i * (2.0 * PI / m) * (inverse ? -1.0 : 1.0)); 

        for (int k = 0; k < n; k += m) {
            cd w = 1; 

            for (int j = 0; j < m / 2; j++) {
                cd t = w * p[k + j + m / 2];
                cd u = p[k + j];

                p[k + j] = u + t;
                p[k + j + m / 2] = u - t;

                w *= w_m; 
            }
        }
    }

    if (inverse) {
        for (cd &x : p) {
            x /= n;
        }
    }
}


    vector<long long> multiply(vector<long long>& p1, vector<long long>& p2) {
        vector<cd> a(p1.begin(), p1.end()), b(p2.begin(), p2.end());

        int size = 1;
        while (size < a.size() + b.size()) {
            size *= 2;
        }

        a.resize(size);
        b.resize(size);

        fft(a, false);
        fft(b, false);

        vector<cd> temp(size);

        for (int i = 0; i < size; i++) {
            temp[i] = a[i] * b[i];
        }

        fft(temp, true);

        vector<long long> result(size);

        for (int i = 0; i < size; i++) {
            result[i] = round(temp[i].real());
        }

        while (!result.empty() && result.back() == 0){
            result.pop_back();
        }

        return result;
    }

    vector<int> multiply(vector<int>& p1, vector<int>& p2) {
        vector<cd> a(p1.begin(), p1.end()), b(p2.begin(), p2.end());

        int size = 1;
        while (size < a.size() + b.size()) {
            size *= 2;
        }

        a.resize(size);
        b.resize(size);

        fft(a, false);
        fft(b, false);

        vector<cd> temp(size);

        for (int i = 0; i < size; i++) {
            temp[i] = a[i] * b[i];
        }

        fft(temp, true);

        vector<int> result(size);

        for (int i = 0; i < size; i++) {
            result[i] = round(temp[i].real());
        }

        while (!result.empty() && result.back() == 0){
            result.pop_back();
        }

        return result;
    }

    vector<double> multiply(vector<double>& p1, vector<double>& p2) {
        if (p1.empty() || p2.empty()) return {0};

        vector<cd> a(p1.begin(), p1.end()), b(p2.begin(), p2.end());

        int size = 1;
        while (size < a.size() + b.size()) {
            size *= 2;
        }

        a.resize(size);
        b.resize(size);

        fft(a, false);
        fft(b, false);

        vector<cd> temp(size);

        for (int i = 0; i < size; i++) {
            temp[i] = a[i] * b[i];
        }

        fft(temp, true);

        vector<double> result(size);

        for (int i = 0; i < size; i++) {
            result[i] = temp[i].real();
        }

        while (!result.empty() && fabs(result.back()) < 1e-9){
            result.pop_back();
        }

        return result;
    }




private:

void bitReversalPerm(vector<cd>& p, int logN) {
    int n = p.size();
    for (int i = 0; i < n; i++) {
        int rev = reverse(i, logN);
        if (i < rev) {
            swap(p[i], p[rev]);
        }
    }
}

    int reverse(int num, int logN) {
        int res = 0;
        for (int i = 0; i < logN; i++) {
            if (num & (1 << i))
                res |= 1 << (logN - 1 - i);
        }
        return res;
    }
};



