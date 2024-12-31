#include <vector>
#include <math.h>
using namespace std;

class GrayCode{

    vector<int> getGrayCode(int n){
         vector <int> grayCode;
         int totalPower = pow (2, n);

    for (int i = 0; i < totalPower; i++){
        int current = i ^ (i >>1);
        grayCode.push_back(current);

    }

    return grayCode;

    }

  
};