#ifndef LOGISTICREGRESSION_H
#define LOGISTICREGRESSION_H


#include <iostream>
#include <vector>
#include <cmath>
#include "MachineLearningModel.h"

class LogisticRegression : public MachineLearningModel{
    public:

        LogisticRegression(void){
            LearningRate = 0.0001;
            Epoch = 200;
            Threshold = 0.5;
          }
        void Fit(void);
        float Predict(vector <float>);
        void Extract_Result(string);
        void Set_Algorithm_Info(vector <float> Details);

    private:
        double Sigmoid(vector <float>);
        double GradientDescent(int, bool);


        vector <double> Weights;
        float LearningRate;
        float Threshold;
        int Epoch;
};

#endif