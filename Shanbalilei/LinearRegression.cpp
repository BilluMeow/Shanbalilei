#include "LinearRegression.h"


void LinearRegression::Fit(void){
    LearningRate = 0.0001;
    Epoch = 200;
    {
        vector <double> temp(TrainingSet[0].size(), 0);
        Weights = temp;
    }
    for(int i=0;i<Epoch;i++){
        
        for(int j=0;j<Weights.size();j++){
            
            float Residual = 0;
            for(int k=0;k<TrainingSet.size();k++){
                Residual += (TrainingSet[k][TrainingSet[k].size()-1] - Predict(TrainingSet[k])) *(j == Weights.size()-1 ? 1 : TrainingSet[k][j]);
            }
            
            Weights[j] += ((float)(j == Weights.size()-1 ? 0.25 : 2.0) / (float)TrainingSet.size()) *  LearningRate * Residual;
        }
    }
}

void LinearRegression::Set_Algorithm_Info(vector <float> Details){
    if(Details.size() != 2){
        cout << "Details are Incorrect ..." << endl;
        exit(12);
    }
    LearningRate = Details[0];
    Epoch = Details[1];
}


float LinearRegression::Predict(vector<float> Row){
    float Ans = 0;
    for(int i=0;i<Weights.size()-1;i++){
        Ans += Row[i]*Weights[i];
    }
    Ans += Weights[Weights.size()-1];
    return Ans;
}

void LinearRegression::Extract_Result(string FileName){
    ofstream FilePtr;
    FilePtr.open(FileName);

    FilePtr << "//Last Weight is the Biased Weight :)" << endl << "{ ";
    for(int i=0;i<Weights.size();i++){
        FilePtr << Weights[i] << (i == Weights.size()-1 ? "" : ", "); 
    }
    FilePtr << "}";
    FilePtr.close();
}