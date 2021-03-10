#include <bits/stdc++.h>
using namespace std;

const int datasetsize=1372;
const int knn=3;

struct custome_type{
	double a;
	double b;
	double c;
	double d;
	double decision;
};

vector <custome_type> dataset;
vector <custome_type> trainset;
vector <custome_type> testset;

vector <double> accuracySet;

void clearLine(string &s){
	for(int i=0; i<s.length(); i++){
		if(s[i]==',') s[i]=' ';
	}
}

custome_type getCustomType(string s){
	
	istringstream iss(s);
	custome_type TEMP;

	iss >> TEMP.a;
	iss >> TEMP.b;
	iss >> TEMP.c;
	iss >> TEMP.d;
	iss >> TEMP.decision;

	return TEMP;
}


void readFromFile(){
	for(int i=0; i<datasetsize; i++){
		string s;
		getline(cin,s);
		clearLine(s);
		dataset.push_back(getCustomType(s));
	}
}

void splitData(){
	
	int n90percent = (9*datasetsize)/10;
	vector <int> v;

	for(int i=0; i<n90percent; i++){
		int randValue=rand()%datasetsize;
		bool ok=false;
		for(int k=0; k<v.size(); k++){
			if(v[k]==randValue){
				ok=true;
				break;
			}
		}
		if(ok){
			i--;
		} else {
			v.push_back(randValue);
		}
	}

	sort(v.begin(),v.end());

	for(int i=0; i<v.size(); i++){
		trainset.push_back(dataset[v[i]]);
	}

	int pos=0;

	for(int i=0; i<datasetsize; i++){
		if(v[pos]==i) pos++;
		else {
			testset.push_back(dataset[i]);
		}
	}

}

double calculateDistance(custome_type test, custome_type train){
	double distance=0;
	distance+=(test.a-train.a)*(test.a-train.a);
	distance+=(test.b-train.b)*(test.b-train.b);
	distance+=(test.c-train.c)*(test.c-train.c);
	distance+=(test.d-train.d)*(test.d-train.d);
	return distance;
}

double getMyPrediction(vector < pair <double,double> > distance){
	
	sort(distance.begin(),distance.end());
	int cnt0=0, cnt1=0;
	
	for(int i=0; i<knn; i++){
		if(distance[i].second>0) cnt1++;
		else cnt0++;
	}
	
	return (cnt1>cnt0) ? 1.0 : 0.0;
}

void inputProcess(){

	int myRightPrediction=0;
	int myWrongPrediction=0;

	for(int i=0; i<testset.size(); i++){
		
		vector < pair <double,double> > distance;
		
		for(int k=0; k<trainset.size(); k++){
			double temp=calculateDistance(testset[i],trainset[k]);
			distance.push_back(make_pair(temp,(double)trainset[k].decision));
		}
		
		double prediction=getMyPrediction(distance);
		
		if(prediction==(double)testset[i].decision){
			myRightPrediction++;
		} else {
			myWrongPrediction++;
		}
	}

	accuracySet.push_back((double)myRightPrediction/(myRightPrediction+myWrongPrediction));
}

void clearGlobalThings(){
	trainset.clear();
	testset.clear();
}

int main(){

	srand(time(NULL));
	
	readFromFile();

	for(int i=1; i<=10; i++){
		clearGlobalThings();
		splitData();
		inputProcess();	
	}

	double finaleAccuracy=0;

	for(int i=0; i<accuracySet.size(); i++){
		finaleAccuracy+=accuracySet[i];
		//cout << "Test " << i+1 << ", Accuracy = " << accuracySet[i] << endl;
	}

	finaleAccuracy/=accuracySet.size();
	cout << "finaleAccuracy = " << finaleAccuracy << endl;

	return 0;

}
