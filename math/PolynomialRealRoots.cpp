#include <vector>
#include <iostream>
#include <random>

using namespace std;

template <typename T>

class PolynomialRealRoots{

    public:
 
    vector<T> rootsProbabilistic(vector <T>& p){
        if (p.size() == 1) return{};
        vector <T> roots;
        T epsilon = 1e-11;

        vector<T> pCopy = p;

        if (p[0] == 0){
            roots.push_back(0);
            reduce(pCopy, 0);
        }

        if (p.size()-1 == 1) {  
            roots.push_back(-pCopy[0] / pCopy[1]);
            return roots;
        }

        int maxAttempts = p.size()*4;


        while (roots.size()<p.size()-1 && maxAttempts > 0){

        if (pCopy.size()-1 == 2) {  
            T a = pCopy[2], b = pCopy[1], c = pCopy[0];
            T discriminant = b * b - 4 * a * c;

            if (discriminant >= 0) {
                T sqrtDisc = sqrt(discriminant);
                roots.push_back((-b + sqrtDisc) / (2 * a));
                roots.push_back((-b - sqrtDisc) / (2 * a));
            }
            break; 
        }

            T root = rootNewton(pCopy);
            if (!isnan(root) && abs(evaluate(p, root))< epsilon){
                roots.push_back(root);
                reduce(pCopy, root);
            }
            maxAttempts--;
        }
        return roots;
    }

    T rootLaGuerre (const vector <T>& p){

        random_device rd;
        mt19937 gen(rd());
        const T epsilon = 1e-7;
        const int depth = 100;
       
        T bound = cauchyBound(p);

        uniform_real_distribution<T> dis(-bound, bound);

        vector<T> guesses;

        int degree = p.size()-1;

        for (int i = 0; i < 10; i++){
            guesses.push_back(dis(gen));
        }

        vector<T> firstDer = derivative(p);
        vector<T> secDer = derivative(firstDer);

        for (T x : guesses){
            for (int i = 0; i < depth; i++){
                if (abs((evaluate(p, x)))<epsilon){
                    return x;
                }

                T eval = evaluate (p, x);

                T G = evaluate(firstDer, x)/eval;
                T H = G*G - (evaluate(secDer, x))/eval;

                T radicand = (degree-1)*(degree*H-G*G);

                if (radicand < 0) break;

                T d = max (abs(G+sqrt(radicand)), abs(G-sqrt(radicand)));

                if (abs(d) > epsilon){
                    T a = degree / d;
                    x = x-a;
                }else{
                    break;
                }
            } 
        }
        return numeric_limits<T>::quiet_NaN(); 
    }

    T rootNewton(const vector<T>& p){
        const T epsilon = 1e-11;
        const int depth = 100;
        vector<T> guesses;

        vector<T> der = derivative(p);

        int degree = p.size()-1;

        for (int i = 0; i < 5; i++){
            T guess = rootLaGuerre(p);
            if (!isnan(guess))
            guesses.push_back(guess);
        }

        for (T x : guesses){
            for (int i = 0; i< depth; i++){
                if (abs(evaluate(p, x)) < epsilon)
                return x;

            T den = evaluate(der, x);
            if (den != 0){
                x = x - evaluate(p, x)/ den;
            }else{
                break;
            } 
            }
        }
        return numeric_limits<T>::quiet_NaN();   
    }


    T evaluate(const vector<T>& coeff, T x){ 
        T res = 0;

        for (int i = coeff.size()-1; i >= 0; i--){
            res = coeff[i]+res*x;
        }

        return res;
    }


    void reduce(vector<T>& p, T r) {     
       for (int i = p.size() - 2; i >= 0; i--) {
        p[i] += p[i + 1] * r;
     }
       if (!p.empty()){
        p.erase(p.begin());
     }
     }

  
    vector<T> derivative(const vector<T>& coeff){

        vector<T> d = coeff;
          
        for (int i = 1; i < d.size(); i++){
            d[i] *= i;
        }

        if (!d.empty())
        d.erase(d.begin());

        return d;
    }

    vector<T> primitive(const vector<T>& coeff){
        vector<T> prim = coeff;
        prim.insert(prim.begin(), 0);

        for (int i = 1; i < prim.size(); i++){
            prim[i] /= (T)(i);
        }
        return prim;
    }

    T cauchyBound(const vector<T>& p){
        T cauchyBound = 0;
        T den = abs(p[p.size()-1]) != 0 ? abs(p[p.size()-1]) : 1;

        for (T coeff : p){
            cauchyBound = max(cauchyBound, 1+ abs(coeff/den));
        }

        return cauchyBound;
    }
    };
    


    int main() {
        PolynomialRealRoots<double> poly;
    
        // Define several polynomials for testing
        vector<double> p = 
            {-2, 0, 1, 1.5};    
    
        vector<double> res = poly.rootsProbabilistic(p);
         
        // Print the roots
        cout << "Found roots: ";
        for (double r : res){
            cout << r;
            cout<< "(eval:) ";
            cout<< poly.evaluate(p, r);
            cout << ", ";

        }

        cout << endl << endl;
     
        return 0;
    }