#include <vector>
#include <type_traits>
#include <stdexcept>
using namespace std;

template <typename T>
class EvaluatePolynomial {
public:
    using ReturnType = typename common_type<T, T>::type;

    ReturnType evaluate(const vector<T>& coefficients, T x) {
        static_assert(is_arithmetic<T>::value, "Type must be arithmetic.");

        ReturnType res = 0;
        
        for (int i = coefficients.size() - 1; i >= 0; --i) {
            res = coefficients[i] + x * res;
        }
        
        return res;
    
    }
};






