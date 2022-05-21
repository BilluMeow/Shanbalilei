#include "MachineLearningModel.h"

vector <float> MachineLearningModel::Get_Number_Of_Unique_Values(vector <vector <float>> FeatureRow, int col){

    vector <float> val_record;
    for(int i=0;i<FeatureRow.size();i++){
      auto it = find(val_record.begin(), val_record.end(), FeatureRow[i][col]);
      if(it == val_record.end()){
          val_record.push_back(FeatureRow[i][col]);
      }
    }
   
    return val_record;
}


void MachineLearningModel::Set_Feature_Component(vector <string> FeatureComponents){
    this->FeatureComponents = FeatureComponents;
}

void MachineLearningModel::Set_TrainingSet(vector <vector <float>> TempTraining){
    TrainingSet = TempTraining;
}

float Accuracy_Checker(vector <float> Testing_Y, vector <float> Predict_Y){
    if(Testing_Y.size() != Predict_Y.size()){
        cout << "Real Label's Count Doesn't Match the Predicted Label's Count ..." << endl;
        exit(1);
    }

    int count = 0;
    for(int i=0;i<Testing_Y.size();i++){
        if(Testing_Y[i] == Predict_Y[i])
            count++;
    }
    return ((float)count/(float)Testing_Y.size());  
}

float Root_Mean_Square(vector <float> Testing_Y, vector <float> Predict_Y){
    if(Testing_Y.size() != Predict_Y.size()){
        cout << "Real Label's Count Doesn't Match the Predicted Label's Count ..." << endl;
        exit(1);
    }
    
    double sum = 0;
    for(int i=0;i<Testing_Y.size();i++){
        float error = Testing_Y[i] - Predict_Y[i];
        sum += error * error;
    }
    return (float)sqrt(sum/(float)Testing_Y.size());
}
