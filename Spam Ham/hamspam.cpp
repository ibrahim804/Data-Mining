#include <bits/stdc++.h>
using namespace std;

const int totallines = 4570;

vector <string> hamlines, spamlines;
vector <string> randomHamTrain, randomHamTest;
vector <string> randomSpamTrain, randomSpamTest;
map <string,int> w_ham_cnt, w_spam_cnt;
vector <double> accuracy;

int tp=0, tn=0, fp=0, fn=0;
double threshold = 0.4;

void readTheDataFile(){
	for(int i=0; i<totallines; i++){
		string line;
		getline(cin,line);
		
		if(line[0]=='s'){
			spamlines.push_back(line);
		} else {
			hamlines.push_back(line);
		}
	}
}

void randomHamSelection(){
	
	vector <int> v;
	
	int ham_size = hamlines.size();
	int n90persent = (9*ham_size)/10;

	for(int i=0; i<n90persent; i++){
		int value = rand()%ham_size;
		bool ok = false;
		for(int k=0; k<v.size(); k++){
			if(v[k]==value){
				ok = true;
				break;
			}
		}
		if(ok){
			i--;
		} else {
			v.push_back(value);
		}
	}

	sort(v.begin(),v.end());

	for(int i=0; i<n90persent; i++){
		int indx = v[i];
		randomHamTrain.push_back(hamlines[indx]);
	}

	int pos = 0;

	for(int i=0; i<ham_size; i++){
		if(i==v[pos]) pos++;
		else randomHamTest.push_back(hamlines[i]);
	}

}

void randomSpamSelection(){
	vector <int> v;
	
	int spam_size = spamlines.size();
	int n90persent = (9*spam_size)/10;

	for(int i=0; i<n90persent; i++){
		int value = rand()%spam_size;
		bool ok = false;
		for(int k=0; k<v.size(); k++){
			if(v[k]==value){
				ok = true;
				break;
			}
		}
		if(ok){
			i--;
		} else {
			v.push_back(value);
		}
	}

	sort(v.begin(),v.end());

	for(int i=0; i<n90persent; i++){
		int indx = v[i];
		randomSpamTrain.push_back(spamlines[indx]);
	}

	int pos = 0;

	for(int i=0; i<spam_size; i++){
		if(i==v[pos]) pos++;
		else randomSpamTest.push_back(spamlines[i]);
	}

}

void wordSmapHamCount(){

	for(int i=0; i<randomHamTrain.size(); i++){
		string line = randomHamTrain[i], word;
		istringstream iss (line);
		iss >> word;
		while(iss >> word){
			w_ham_cnt[word]++;
		}
	}

	for(int i=0; i<randomSpamTrain.size(); i++){
		string line = randomSpamTrain[i], word;
		istringstream iss (line);
		iss >> word;
		while(iss >> word){
			w_spam_cnt[word]++;
		}
	}

}

void probabilityCount(vector <string> temp){
	
	string line, word, firstword;

	for(int i=0; i<temp.size(); i++){
		
		double line_pos_pro = 1, line_neg_pro = 1;
		line = temp[i];
		istringstream iss (line);
		iss >> firstword;
		
		while(iss >> word){
			
			double w_ham_rate, w_spam_rate;
			
			if(w_ham_cnt[word]==0 and w_spam_cnt[word]==0){
				w_ham_rate = 0.6;
				w_spam_rate = 0.4;
			} else if(w_ham_cnt[word] > 0 and w_spam_cnt[word]==0){
				w_ham_rate = 0.8;
				w_spam_rate = 0.2;
			} else if(w_ham_cnt[word]==0 and w_spam_cnt[word] > 0){
				w_ham_rate = 0.2;
				w_spam_rate = 0.8;
			} else {
				w_ham_rate = (double) w_ham_cnt[word]/(w_ham_cnt[word]+w_spam_cnt[word]);
				w_spam_rate = (double) w_spam_cnt[word]/(w_ham_cnt[word]+w_spam_cnt[word]);
			}
			
			//double w_pos_pro = (double) w_ham_rate/(w_ham_rate+w_spam_rate);
			//double w_neg_pro = (double) w_spam_rate/(w_ham_rate+w_spam_rate);
			
			line_pos_pro *= w_ham_rate;
			line_neg_pro *= w_spam_rate;
		}
		
		double line_pro = line_pos_pro/(line_pos_pro+line_neg_pro);
		string myPrediction;

		if(line_pro >= threshold){
			myPrediction = "ham";
		} else myPrediction = "spam";

		if(myPrediction=="ham" and firstword=="ham") tn++;
		else if(myPrediction=="ham" and firstword=="spam") fp++;
		else if(myPrediction=="spam" and firstword=="ham") fn++;
		else if (myPrediction=="spam" and firstword=="spam") tp++;  

		accuracy.push_back((double)(tn+tp)/(fn+fp+tn+tp));

	}
}

void inputProcess(){
	
	probabilityCount(randomHamTest);
	probabilityCount(randomSpamTest);

}

void clearThem(){
	randomHamTrain.clear();
	randomSpamTrain.clear();
	randomHamTest.clear();
	randomSpamTest.clear();
	w_ham_cnt.clear();
	w_spam_cnt.clear();
	tp=tn=fp=fn=0;
}

int main(){

	srand(time(NULL));

	readTheDataFile();

	for(int i=0; i<10; i++){

		clearThem();

		randomHamSelection();
		randomSpamSelection();

		wordSmapHamCount();
		inputProcess();

	}

	double finalAccuracy=0, precision=0, recall=0, f1_score=0;

	for(int i=0; i<accuracy.size(); i++){
		finalAccuracy += accuracy[i];
	}

	finalAccuracy /= accuracy.size();
	precision = (double)tp/(tp+fp);
	recall = (double)tp/(tp+fn);
	f1_score = (double)2*(recall * precision) / (recall + precision);

	cout << "accuracy = " << finalAccuracy << endl;
	cout << "precision = " << precision << endl;
	cout << "recall = " << recall << endl;
	cout << "f1_score = " << f1_score << endl; 

	return 0;

}