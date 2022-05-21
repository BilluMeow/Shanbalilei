#include "LogisticRegression.h"


void LogisticRegression::Fit(void){
    {
        vector <double> temp(TrainingSet[0].size(), 0);
        Weights = temp;
    }
    for(int i=0;i<Epoch;i++){
        for(int j=0;j<Weights.size()-1;j++){
            Weights[j] -= LearningRate * GradientDescent(j, 1);
        }
        Weights[Weights.size()-1] -= LearningRate * GradientDescent(0, 0);
    }
}

double LogisticRegression::Sigmoid(vector <float> Row){
    double Ans = 0;
    for(int i=0;i<Weights.size()-1;i++){
        Ans += Row[i]*Weights[i];
    }
    
    Ans += Weights[Weights.size()-1];
    return (1 / (1 + exp(-1*Ans)));
}

void LogisticRegression::Set_Algorithm_Info(vector <float> Details){
    if(Details.size() != 3 || Details[2] >= 1){
        cout << "Details are Incorrect ..." << endl;
        exit(12);
    }
    LearningRate = Details[0];
    Epoch = Details[1];
    Threshold = Details[2];
}

double LogisticRegression::GradientDescent(int j, bool flag){
    double Ans = 0;
    int Column = TrainingSet[0].size()-1;
    
    for(int i=0;i<TrainingSet.size();i++){
        vector <float> RowTemp(TrainingSet[i].begin(), --TrainingSet[i].end());
        Ans += (Predict(RowTemp) - TrainingSet[i][Column]) * (!flag ? (float)1 : TrainingSet[i][j]);
    }
    return (Ans / TrainingSet.size());
}

float LogisticRegression::Predict(vector<float> Row){
    float Ans = Sigmoid(Row);
    if(Ans < Threshold)
        return 0;
    else
        return 1;
}

void LogisticRegression::Extract_Result(string FileName){
    ofstream FilePtr;
    FilePtr.open(FileName);

    FilePtr << "//Last Weight is the Biased Weight & The Next Line is Threshold :)" << endl;
    FilePtr << Threshold << endl << "{ ";
    for(int i=0;i<Weights.size();i++){
        FilePtr << Weights[i] << (i == Weights.size()-1 ? "" : ", "); 
    }
    FilePtr << "}";
    FilePtr.close();
}