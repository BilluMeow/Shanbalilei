#include "Shanbalilei.h"


using namespace std;


void Shanbalilei::Set_ML_Model(string ModelName){

    this->ModelName = ModelName;
    if(ModelName == "DecisionTree")
        MLModel = new DecisionTree();
    else if(ModelName == "LinearRegression")
        MLModel = new LinearRegression();
    else if(ModelName == "KNN")
        MLModel = new KNearestNeighbour();
    else if(ModelName == "LogisticRegression")
        MLModel = new LogisticRegression();
}

void Shanbalilei::SetModelDetail(vector <float> Details){
    MLModel->Set_Algorithm_Info(Details);
}

void Shanbalilei::fit(vector <vector <float>> Training_X, vector <float> Training_Y, vector <string> feature_components){

    for(int i=0;i<Training_X.size();i++){
        Training_X[i].push_back(Training_Y[i]);
    }

    MLModel->Set_TrainingSet(Training_X);
    MLModel->Set_Feature_Component(feature_components);
    MLModel->Fit();
}

vector <float> Shanbalilei::Predict(vector <vector <float>> TestingSet){
    
    vector <float> Ans;
    for(int i=0;i<TestingSet.size();i++){
        Ans.push_back(MLModel->Predict(TestingSet[i]));
    }

    return Ans;
}

float Shanbalilei::Predict(vector <float> Row){
    return MLModel->Predict(Row);
}

void Shanbalilei::ExtractModel(string FileName){
    MLModel->Extract_Result(FileName);
}

//--------------------------------------------------------------
//--------------------------------------------------------------
//--------------------------------------------------------------


vector <string> feature_components_Shanbalilei;
vector <vector <string>> StringFeatureHash_Shanbalilei;
vector <int> StringHashHash_Shanbalilei;

//19k-1069, Syed Abeer Hussain
void Get_CSV(string file_name, vector <vector <float>> &Features, vector <vector <string>> &StringHash, vector <string> &feature_components, int lim){
    
    ifstream csv_input;
    csv_input.open(file_name);
    
    string line;
    getline(csv_input, line);
    
    Decipher_Feature_Type(line);
    int comma_occurence = 0;

    for(int i=0;i<line.size();i++){
        if(line[i] == ',')
            comma_occurence++;
    }
    
    csv_input.seekg(0, ios::beg);

    int count = 0;
    
    while(getline(csv_input, line)){
        if(count == lim)
            break;
        line = Purge_Line(line);
        line += ' ';
        int l = 0;
        int j = 0;
        vector <float> featuretemp;
        for(int i=0;i<line.size();i++){
            if(line[i] == ',' || i == (line.size()-1)){
                l++;
                featuretemp.push_back(Change_Feature(line.substr(l, i-l), j));
                j++;
                l = i;
            }
        }
        Features.push_back(featuretemp);
        count++;
    }
    feature_components = feature_components_Shanbalilei;
    StringHash = StringFeatureHash_Shanbalilei;
    
    StringHashHash_Shanbalilei.clear();
    StringFeatureHash_Shanbalilei.clear();
    feature_components_Shanbalilei.clear();
}

//19K-1060 Wasif Khan
void Partition(float Percentage, vector <vector <float>> Features, vector <vector <float>> &Training_X, vector <float> &Training_Y, vector <vector <float>> &Testing_X, vector <float> &Testing_Y){
    if(Percentage < 1 || Percentage > 99){
        cout << "Percentage is not in range (0, 100) exclusive ..." << endl;
        exit(1);
    }
    //size for testing data
    int size = Features.size() - Features.size() * Percentage / 100;

    vector <int> testing_random;

    srand(time(0));
    for(int i=0;i<size;i++){
        int rand_pos = rand() % Features.size();
        auto it = find(testing_random.begin(), testing_random.end(), rand_pos);
        if(it == testing_random.end()){
            vector <float> temp(Features[rand_pos].begin(), --(Features[rand_pos].end()));
            Testing_X.push_back(temp);
            Testing_Y.push_back(Features[rand_pos][Features[rand_pos].size()-1]);
            testing_random.push_back(rand_pos);
        }
        else{
            i--;
        }
    }

    for(int i=0;i<Features.size();i++){
        auto it = find(testing_random.begin(), testing_random.end(), i);
        if(it == testing_random.end()){
            vector <float> temp(Features[i].begin(), --(Features[i].end()));
            Training_X.push_back(temp);
            Training_Y.push_back(Features[i][Features[i].size()-1]); 
        }
    }
}

//19K-1060 Wasif Khan
void Display_Features(vector <vector <float>> TrainingSet, vector <vector <float>> TestingSet){
    
    cout << "Training Data of Size : " << TrainingSet.size() << endl;
    for(int i=0;i<TrainingSet.size();i++){  
        for(int j=0;j<TrainingSet[0].size();j++)
            cout << TrainingSet[i][j] << (j < TrainingSet[0].size()-1 ? " , " : "");
        cout << endl;
    }

    cout << "Testing Data of Size : " << TestingSet.size() << endl;
    for(int i=0;i<TestingSet.size();i++){  
        for(int j=0;j<TestingSet[0].size();j++)
            cout << TestingSet[i][j] << (j < TestingSet[0].size()-1 ? " , " : "");
        cout << endl;
    }
}

//19k-1069, Syed Abeer Hussain
string Get_Type(string block){
        try{
            float p = stof(block);
            return "float";
        }
        catch(...){
            return "string"; 
        }
}

//19k-1069, Syed Abeer Hussain
void Decipher_Feature_Type(string line){
    int l = 0;
    line = Purge_Line(line);
    line += ' ';
    for(int i=0;i<line.size();i++){
        if(line[i] == ',' || i == (line.size()-1)){
            l++;
            feature_components_Shanbalilei.push_back(Get_Type(line.substr(l, i-l)));
            l = i;
        }
    }
}

//19k-1069, Syed Abeer Hussain
float String_Feature_Handler(string feature_val, int column){
    
    int pos = find_in <int>(StringHashHash_Shanbalilei, column);
    if(pos != -1){
        int pos2 = find_in <string>(StringFeatureHash_Shanbalilei[pos], feature_val);
        if(pos2 != -1){
            return (float)(pos2);
        }
        else{
            StringFeatureHash_Shanbalilei[pos].push_back(feature_val);
            return (StringFeatureHash_Shanbalilei[pos].size() - 1);
        }
    }
    else{
        StringHashHash_Shanbalilei.push_back(column);
        vector <string> temp;
        temp.push_back(feature_val);
        StringFeatureHash_Shanbalilei.push_back(temp);
        return 0;
    }
}

//19k-1069, Syed Abeer Hussain
string Purge_Line(string block){
    string PurgedLine = " ";
    for(int i=0;i<block.size();i++){
        if(block[i] != ' ')
            PurgedLine += block[i];
    }
    return PurgedLine;
}

//19k-1069, Syed Abeer Hussain
float Change_Feature(string feature_val, int column){
    if(feature_components_Shanbalilei[column] == "string")
        return String_Feature_Handler(feature_val, column);
    else
        return stof(feature_val);
}

//19K-1060 Wasif Khan
template <typename T>
int find_in(vector <T> To_Find_In, T value){
    for(int i=0;i<To_Find_In.size();i++){
        if(To_Find_In[i] == value)
            return i;
    }
    return -1;
}

//19K-1060 Wasif Khan
void MinMaxNormalization(vector <vector <float>> &Features, int Column){
    float MinVal = Minimum(Features, Column);
    float MaxVal = Maximum(Features, Column);

    //formula for normalization
    for(int i=0;i<Features.size();i++){
        Features[i][Column] = (Features[i][Column] - MinVal) / (MaxVal - MinVal);
    }

}

//19K-1050 Khubaib Alam
float Minimum(vector <vector <float>> Features, int Column){
    float MinVal = Features[0][Column];
    for(int i=0;i<Features.size();i++){
        if(Features[i][Column] < MinVal)
            MinVal = Features[i][Column];
    }
    return MinVal;
}

//19K-1050 Khubaib Alam
float Maximum(vector <vector <float>> Features, int Column){
    float MaxVal = Features[0][Column];
    for(int i=0;i<Features.size();i++){
        if(Features[i][Column] > MaxVal)
            MaxVal = Features[i][Column];
    }
    return MaxVal;
}

//19K-1050 Khubaib Alam
float Mean(vector <vector <float>> Features, int Column){
    float mean = 0;
    for(int i=0;i<Features.size();i++){
        mean += Features[i][Column];
    }
    return (mean/(float)Features.size());
}

//19K-1050 Khubaib Alam
float StandardDeviation(vector <vector <float>> Features, int Column, float mean){
    int Deviation = 0;
    for(int i=0;i<Features.size();i++){
        float temp = mean - Features[i][Column];
        Deviation +=  temp * temp;
    }
    return (float)sqrt(Deviation/(float)Features.size());
}

//19K-1050 Khubaib Alam
void Standardization(vector <vector <float>> &Features, int Column){

    float mean = Mean(Features, Column);
    float Mun = StandardDeviation(Features, Column, mean);

    for(int i=0;i<Features.size();i++){
        Features[i][Column] = (Features[i][Column] - mean) / Mun;
    }
}

//19K-1060 Wasif Khan
void DeleteFeature(vector <vector <float>> &Features, int Column){
    for(int i=0;i<Features.size();i++){
        Features[i].erase(Features[i].begin()+Column);
    }
}