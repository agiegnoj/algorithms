#include <random>

using namespace std;


class MonteCarloIntegration{
    private:

    random_device rd;
    mt19937 gen;

    public:

    MonteCarloIntegration() : gen(rd()) {
        
    }

    double definiteIntegral1D(double(*f)(double), double lowBnd, double hiBnd, int samples){
        

        uniform_real_distribution<double> dis(lowBnd, hiBnd);

        double factor = (hiBnd-lowBnd)/(double)samples;

        double res = 0.0;


        for (int i = 0; i< samples; i++){
            double input = dis(gen);
            res += f(input);
        }

        return factor * res;

    }

    double definiteIntegral2D(double(*f)(double, double), double lowBndX, double hiBndX, double lowBndY, double hiBndY, int samples){
      
        uniform_real_distribution<double> dis(lowBndX, hiBndX);
        uniform_real_distribution<double> dis2(lowBndY, hiBndY);


        double factor = (hiBndX-lowBndX)*(hiBndY-lowBndY)/(double)samples;

        double res = 0.0;

        for (int i = 0; i< samples; i++){
            double inputX = dis(gen);
            double inputY = dis2(gen);
            res +=  f(inputX, inputY);
        }

        return factor*res;
        
    }
    

};

