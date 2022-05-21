#include "KNearestNeighbour.h"

      
void KNearestNeighbour::Fit(void){
    /*
        Cheems is my BFF.
        Donald Trump was trying to hack my Laptop.
        Mr.Dickson got stuck in his plan.
        35th Anti Magic Platoon wiped everyone.
        Aalu mia is trying to get rid of his Ex ""Ali"".
        I want to raid Storm Area 51.
        Where is my Array = {"Bhai", "Bhai", "Bhai"};
        Please send wasif to Mr. Banana.
        I want to watch "watch people die inside".
    */
}

float KNearestNeighbour::Predict(vector <float> row){
    double BestDistance = INT_MAX;
    float Label;
    if(!Ans.empty())
        Ans.clear();
        
    for(int i=0;i<TrainingSet.size();i++){
        double distance = EuclideanDistance(row, TrainingSet[i]);
        if(distance < BestDistance){
              BestDistance = distance;
              Label = TrainingSet[i][TrainingSet[i].size()-1];
        }
        Add_Answer(TrainingSet[i][TrainingSet[i].size()-1], distance);
    }
    
    if(Classification)
        return Classifier();
    else
        return Regressor();
}

void KNearestNeighbour::Set_Algorithm_Info(vector <float> Details){
    if(Details.size() != 2 || (Details[1] != 0 && Details[1] != 1)){
        cout << "Details are Incorrect ..." << endl;
        exit(12);
    }
    K = (int)Details[0];
    Classification = (Details[1] == 1 ? 1 : 0);
}


void KNearestNeighbour::Extract_Result(string Filname){
    // Not part of the Scope
}

float KNearestNeighbour::Classifier(void){
    vector <pair <float, int>> AnswerCount;
    for(int i=0;i<Ans.size();i++){
        bool flag = false;
        for(int j=0;j<AnswerCount.size();j++){
            if(AnswerCount[j].first == Ans[i].first){
                flag = true;
                AnswerCount[j].second++;
            }
        }
        if(!flag){
            AnswerCount.push_back(make_pair(Ans[i].first, 0));
        }
    }
    pair <float, int> BestAns = AnswerCount[0];
    for(int i=0;i<AnswerCount.size();i++){
        if(BestAns.second < AnswerCount[i].second)
            BestAns = AnswerCount[i];
    }
    return BestAns.first;
}

float KNearestNeighbour::Regressor(void){
    float Mean = 0;

    for(int i=0;i<Ans.size();i++){
        Mean += Ans[i].first;
    }

    return (Mean/(float)Ans.size());
}


double KNearestNeighbour::EuclideanDistance(vector<float> Row1, vector<float> Row2){
    double distance = 0;
    for(int i=0;i<Row1.size();i++){
        distance += pow((Row1[i]-Row2[i]), 2);
    }
    return sqrt(distance);
}

void KNearestNeighbour::Add_Answer(float Label, float distance){
    if(Ans.size() < K || Ans.empty())
        Ans.push_back(make_pair(Label, distance));
    else if(distance < Ans[Ans.size()-1].second){
        for(int i=0;i<Ans.size();i++){
            if(distance < Ans[i].second){
                for(int j=Ans.size()-1;j>i;j--)
                    Ans[j] = Ans[j-1];
                Ans[i] = make_pair(Label, distance);
                break;
            }
        }
    }
}