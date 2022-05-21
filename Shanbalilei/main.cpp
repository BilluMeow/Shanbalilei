#include "Shanbalilei.h"
#include <vector>
#include <iostream>


using namespace std;

//For Testing Pusposes
// To Run 
// g++ -o main DecisionTree.cpp  MachineLearningModel.cpp Shanbalilei.cpp LogisticRegression.cpp KNearestNeighbour.cpp  main.cpp

/*
    # Functionalities:
    
    ## ML Models:
          ### Decision Tree
          ### Logistic Regression
          ### Linear Regression
          ### K Nearest Neighbour

    ## Extracting Trained Model into a File
  
    ## Reading From csv
    ## Handling String data
    ## Partitioning Data
    
    ## Feature Manipulation & Things:
          ### Mean
          ### Standard Deviation
          ### Minimum
          ### Maximum
          ### Normalization
          ### Standardization
          ### Feature Removal

    ## Accuracy Checker
    ## Root Mean Square Calculator

    ## Generalized Artitechture
    ## Can Create and implement new Models very Easily
*/


int main(void){

//------------------------------------------------------------------------------
  
  
	// Demo to how to use the library
  
    Shanbalilei MyTree;
  
    vector <vector <float>> Features, Training_X, Testing_X;
    vector <float> Training_Y, Testing_Y;
    vector <vector <string>> StringHash;
    vector <string> FeatureComponent;
    
    Get_CSV("iris.csv", Features, StringHash, FeatureComponent, 100);
    
    
    Partition(60, Features, Training_X, Training_Y, Testing_X, Testing_Y);

    MyTree.Set_ML_Model("LogisticRegression");
    
    MyTree.fit(Training_X, Training_Y, FeatureComponent);

    vector <float> Ans = MyTree.Predict(Testing_X);

    for(int i=0;i<Ans.size();i++){
        cout << Testing_Y[i] << "    " << Ans[i] << endl;
    }
    
    float Accuracey = 100*Accuracy_Checker(Testing_Y, Ans);
    cout << "Accuracy is : " << Accuracey << endl;

    if(Accuracey > 90)
        MyTree.ExtractModel("DecisionTree.txt");
    //cout << "Root Mean Square Is : " << Root_Mean_Square(Testing_Y, Ans) << endl;

    return 0;
}