#ifndef DECISIONTREE_H
#define DECISIONTREE_H

#include "MachineLearningModel.h"
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <fstream>

using namespace std;

class Question{
  public:
    string Feature_type;
    float value;
    int column;

    Question(void){}
    Question(string Feature_type, float value, int column){
        this->Feature_type = Feature_type;
        this->value = value;
        this->column = column;
    }

    string CCCC(void){
        
        string Ans = "Row[" + to_string(column) + "] " + (Feature_type == "string" ? "== " : ">= ") + to_string(value);
        
        return Ans;
    }

    bool Match(float value){
        if(Feature_type == "String")
            return (value == this->value);
        else
            return (value >= this->value);
    }
};

class Tree_Node{
    public:
        Tree_Node(void){Left = 0; Right = 0;Leaf = false;}
        Tree_Node *Left, *Right;
        bool Leaf;
        vector <vector <float>> Answer;
        Question BestQuestion;
};

class DecisionTree: public MachineLearningModel{
    public:

        void Fit(void);
        float Predict(vector <float>);
        void Extract_Result(string);
        void Set_Algorithm_Info(vector <float>);
        void Print_Tree(string, Tree_Node*, ofstream&);

    private:

        Tree_Node* Build_Tree(vector <vector <float>>);
        pair <float, Question> Best_Split(vector <vector <float>>);
        float Gini_Calculator(vector <vector <float>>);
        float Information_Gain(vector <vector <float>>, vector <vector <float>>, float);
        vector <pair <float, int>> Get_Labels_Count(vector <vector <float>>);
        void Partition(vector <vector <float>>, Question, vector <vector <vector <float>>>&);
        vector <vector <float>> PredictIt(vector <float>, Tree_Node*);

        string WholeTree;
        Tree_Node *Root;
};


#endif 