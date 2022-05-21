#pragma once
#ifndef SHANBALILEI_H
#define SHANBALILEI_H

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include "MachineLearningModel.h"
#include "LinearRegression.h"
#include "DecisionTree.h"
#include "KNearestNeighbour.h"
#include "LogisticRegression.h"

using namespace std;


void Get_CSV(string, vector <vector <float>>&, vector <vector <string>>&, vector <string>&, int=-1);
string Get_Type(string);
void Decipher_Feature_Type(string);
float String_Feature_Handler(string, int);
string Purge_Line(string);
float Change_Feature(string, int);

void Display_Features(vector <vector <float>>, vector <vector <float>>);
void Partition(float, vector <vector <float>>, vector <vector <float>>&, vector <float>&, vector <vector <float>>&, vector <float>&);

template <typename T>
int find_in(vector <T>, T);

float Maximum(vector <vector <float>>, int);
float Minimum(vector <vector <float>>, int);
void MinMaxNormalization(vector <vector <float>>&, int);
float Mean(vector <vector <float>>, int);
float StandardDeviation(vector <vector <float>>, int, float);
void Standardization(vector <vector <float>>&, int);
void DeleteFeature(vector <vector <float>>&, int);

class Shanbalilei{
    public:

        void Set_ML_Model(string);
        void fit(vector <vector <float>>, vector <float>, vector <string>);
        float Predict(vector <float>);
        vector <float> Predict(vector <vector <float>>);
        void ExtractModel(string);
        void SetModelDetail(vector <float>);

    private:
        MachineLearningModel *MLModel;
        string ModelName;
};

#endif

