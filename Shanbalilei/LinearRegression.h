#ifndef LINEARREGRESSION_H
#define LINEARREGRESSION_H

#include <iostream>
#include <vector>
#include <cmath>
#include <climits>
#include "MachineLearningModel.h"

class LinearRegression : public MachineLearningModel{
    public:

        LinearRegression(void){
            LearningRate = 0.001;
            Epoch = 200;
        }
        void Fit(void);
        float Predict(vector <float>);
        void Extract_Result(string);
        void Set_Algorithm_Info(vector <float>);

    private:
        double GradientDescent(int, bool);

        vector <double> Weights;
        float LearningRate;
        int Epoch;
};


#endif