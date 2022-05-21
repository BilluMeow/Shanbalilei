#ifndef MACHINELEARNINGMODEL_H
#define MACHINELEARNINGMODEL_H

#include <vector>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;

float Accuracy_Checker(vector <float>, vector <float>);
float Root_Mean_Square(vector <float>, vector <float>);

class MachineLearningModel{
    public:
        virtual void Fit(void) = 0;
        virtual float Predict(vector <float>) = 0;
        virtual void Extract_Result(string) = 0;
        virtual void Set_Algorithm_Info(vector <float>) = 0;

        void Set_TrainingSet(vector <vector <float>>);
        void Set_Feature_Component(vector <string>);

    protected:
        vector <vector <float>> TrainingSet;
        vector <string> FeatureComponents;

        vector <float> Get_Number_Of_Unique_Values(vector <vector <float>>, int);
};

#endif