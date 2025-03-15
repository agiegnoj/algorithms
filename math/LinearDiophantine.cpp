#include <vector>
#include <math.h>
using namespace std;

class LinearDiophantine{

    public:

    vector<pair<int, int>> solveLinearDiophantineEquation(int a, int b, int c, int minX, int maxX, int minY, int maxY){
        int x; int y;
        int gcd = extendedGCD(a, b, x, y);
        vector<pair<int, int>> solutions;

        if (c % gcd == 0){
            x *= c/gcd;
            y *= c/gcd;
  
            int xStep = b/gcd;
            int yStep = a/gcd;

            int kMin = ceil((minX - x) / (double)xStep);
            int kMax = floor((maxX - x) / (double)xStep);
            int kMinY = ceil((y - maxY) / (double)yStep);
            int kMaxY = floor((y - minY) / (double)yStep);
            kMin = max(kMin, kMinY);
            kMax = min(kMax, kMaxY);

            for (int k = kMin; k<= kMax; k++){
                int newX = x + k*xStep;
                int newY = y-k*yStep;
                solutions.push_back({newX, newY});
            }

        }
        return solutions;    
    }

    int extendedGCD(int a, int b, int& x, int& y){
 
        int r0 = a; int r1 = b;
        int x0 = 1; int x1 = 0;
        int y0 = 0; int y1 = 1;

        while (r0 % r1 != 0){
            int rn = r0%r1;
            int q = r0/r1;
            int xn = x0-q*x1;
            int yn = y0 - q*y1;

            r0 = r1;
            r1 = rn;
            x0 = x1;
            x1 = xn;
            y0 = y1;
            y1 = yn;
        }
        x = x1;
        y = y1;
        return r1;

    }
};

