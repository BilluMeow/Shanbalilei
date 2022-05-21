#include "DecisionTree.h"

using namespace std;


//19k-1050, Khubaib Alam
vector <vector <float>> DecisionTree::PredictIt(vector <float> Row, Tree_Node *Curr){
    if(Curr->Left == 0 && Curr->Right == 0)
        return Curr->Answer;

    if((Curr->BestQuestion).Match(Row[(Curr->BestQuestion).column]))
        return PredictIt(Row, Curr->Left);
    else
        return PredictIt(Row, Curr->Right);
}


//19k-1050, Khubaib Alam
void DecisionTree::Fit(void){
    Root = Build_Tree(TrainingSet);
}

//19k-1050, Khubaib Alam
float DecisionTree::Predict(vector <float> Row){
    vector <vector <float>> AnswerData = PredictIt(Row, Root);
    vector <pair <float, int>> Prediction = Get_Labels_Count(AnswerData);

    float BestAnswer = Prediction[0].first;
    int HighProbability = Prediction[0].second;

    for(int i=0;i<Prediction.size();i++){
        if(Prediction[i].second > HighProbability){
            HighProbability = Prediction[i].second;
            BestAnswer = Prediction[i].first;
        }
    }
    return BestAnswer;

}

//19k-1069, Syed Abeer Hussain
void DecisionTree::Set_Algorithm_Info(vector <float> Details){
    //Another Random Fuction
    //Just Chillin here Nothing to do
    //Wanna be Google Hacker
    //But Barack Obama refused to get in
    //So right Now trying to befriend with Zuckerberg
    //Thats all
    exit(12);
}

//19k-1069, Syed Abeer Hussain
void DecisionTree::Extract_Result(string FileName){
    
    ofstream FilePtr;
    FilePtr.open(FileName);

    FilePtr << "float Predict(vector <float> Row){" << endl;
    Print_Tree("", Root, FilePtr);
    FilePtr << "}" << endl;
    FilePtr.close();
    
}

/////////////////////////////////////////////////////////////////

//19k-1050, Khubaib Alam
Tree_Node* DecisionTree::Build_Tree(vector <vector <float>> GivenData){

    
    pair <float, Question> ToSplit = Best_Split(GivenData);

    Tree_Node *Node = new Tree_Node;
    Node->BestQuestion = ToSplit.second;
    

    if(ToSplit.first == 0){
        Node->Leaf = true;
        Node->Answer = GivenData;
        return Node;
    }
    
    vector <vector <vector <float>>> TrueFalseData;
    {
        vector <vector <float>> temp;
        TrueFalseData.push_back(temp);
        TrueFalseData.push_back(temp);
    }
    
    Partition(GivenData, ToSplit.second, TrueFalseData);
    
   

    Node->Left = Build_Tree(TrueFalseData[0]);
    Node->Right = Build_Tree(TrueFalseData[1]);

    return Node;
  
}


//19k-1069, Syed Abeer Hussain
int Find_in(vector<pair <float, int>> Record, float Label){
    for(int i=0;i<Record.size();i++){
        if(Record[i].first == Label)
            return i;
    }
    return -1;
}

//19k-1060, Wasif Khan
vector<pair <float, int>> DecisionTree::Get_Labels_Count(vector <vector <float>> TrainingSet){

    vector<pair <float, int>> Value_Record;

    for(int i=0;i<TrainingSet.size();i++){
        int pos = Find_in(Value_Record, TrainingSet[i][TrainingSet[i].size()-1]);
        if(pos != -1)
            Value_Record[pos].second++;
        else
            Value_Record.push_back(make_pair(TrainingSet[i][TrainingSet[i].size()-1], 1));
    }
    
    return Value_Record;
}

//19k-1069, Syed Abeer Hussain
void Copy_Into_TrueFalse_Rows(vector <vector <vector <float>>>& TrueFalseData, vector <vector <float>> GivenData, int row, bool TrueorFalse){

    TrueFalseData[(TrueorFalse ? 0 : 1)].push_back(GivenData[row]);

}

//19k-1069, Syed Abeer Hussain
void DecisionTree::Partition(vector <vector <float>> GivenData, Question CheckingQuestion, vector <vector <vector <float>>>& TrueFalseData){

    for(int i=0;i<GivenData.size();i++){
        
        bool flag = CheckingQuestion.Match(GivenData[i][CheckingQuestion.column]);
        Copy_Into_TrueFalse_Rows(TrueFalseData, GivenData, i, flag);
    }
}


//19k-1060, Wasif Khan
float DecisionTree::Information_Gain(vector <vector <float>> left, vector <vector <float>> right, float CurrentUncertainity){

    float p  = (float)left.size()/((float)left.size() + (float)right.size());
    return (CurrentUncertainity - p * Gini_Calculator(left) - (1-p) * Gini_Calculator(right));
}


//19k-1069, Syed Abeer Hussain
pair <float, Question> DecisionTree::Best_Split(vector <vector <float>> GivenData){

    float BestGain = 0;
    Question BestQuestion;
    float CurrentUncertainity = Gini_Calculator(GivenData);
    

    for(int i=0;i<GivenData[0].size()-1;i++){
        vector <float> UniqueValues = Get_Number_Of_Unique_Values(GivenData, i);
        
        
        for(int j=0;j<UniqueValues.size();j++){
              
              Question NewQuestion(FeatureComponents[i], UniqueValues[j], i);
              
              vector <vector <vector <float>>> TrueFalseData;
              {
                  vector <vector <float>> temp;
                  TrueFalseData.push_back(temp);
                  TrueFalseData.push_back(temp);
              }
              
              Partition(GivenData, NewQuestion, TrueFalseData);
               

              if(TrueFalseData[0].size() == 0 || TrueFalseData[1].size() == 0)
                  continue;
              
              float CurrentGain = Information_Gain(TrueFalseData[0], TrueFalseData[1], CurrentUncertainity);
             
              
              if(BestGain < CurrentGain){
                  
                  BestGain = CurrentGain;
                  BestQuestion = NewQuestion;
              }

        }
    }
   
    return make_pair(BestGain, BestQuestion);
}

//19k-1060, Wasif Khan
float DecisionTree::Gini_Calculator(vector <vector <float>> GivenData){
    float impurity = 1;
    vector<pair <float, int>> DiffLabels = Get_Labels_Count(GivenData);
    
    for(int i=0;i<DiffLabels.size();i++){
        float ProbabiltyOfLabel = (float)DiffLabels[i].second / ((float)GivenData.size());
        impurity -= ProbabiltyOfLabel * ProbabiltyOfLabel;
    }
    
    return impurity;
}

//19k-1069, Syed Abeer Hussain
void DecisionTree::Print_Tree(string space, Tree_Node *curr, ofstream &FilePtr){
    if(curr != 0){
        space += "\t";
        if(curr->Left == 0 && curr->Right == 0){
             vector <pair <float, int>> Prediction = Get_Labels_Count(curr->Answer);

              float BestAnswer = Prediction[0].first;
              int HighProbability = Prediction[0].second;

              for(int i=0;i<Prediction.size();i++){
                  if(Prediction[i].second > HighProbability){
                      HighProbability = Prediction[i].second;
                      BestAnswer = Prediction[i].first;
                  }
              }
              FilePtr << space << "return " << BestAnswer << ";" << endl;
        }
        else{
            FilePtr << space << "if(" << (curr->BestQuestion).CCCC() << "){" << endl;
            Print_Tree(space , curr->Left, FilePtr);
            FilePtr << space << "}" << endl << space << "else{" << endl;
            Print_Tree(space, curr->Right, FilePtr);
            FilePtr << space << "}" << endl;
        }
    }
}

