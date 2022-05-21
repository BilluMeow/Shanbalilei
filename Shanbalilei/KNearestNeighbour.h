#ifndef KNEARESTNEIGHBOUR_H
#define KNEARESTNEIGHBOUR_H

#include <iostream>
#include <vector>
#include <cmath>
#include <utility>
#include <climits>
#include "MachineLearningModel.h"

class KNearestNeighbour : public MachineLearningModel{

    public:

        KNearestNeighbour(void){K = 5;Classification = 1;}
        void Fit(void);
        float Predict(vector <float>);
        void Set_Algorithm_Info(vector <float>);
        void Extract_Result(string);

    private:
        bool Classification;
        int K;
        vector <pair <float, float>> Ans;

        float Classifier(void);
        float Regressor(void);

        double EuclideanDistance(vector <float>, vector <float>);
        void Add_Answer(float, float);
};


#endif
