// C++ program to find groups of unknown
// Points using K nearest neighbour algorithm.
#include <bits/stdc++.h>
using namespace std;
#define MAX 10

struct Point
{
    int val;     // Group of point
    double x, y;     // Co-ordinate of point
    double distance; // Distance from test point
};

struct data
{
    double column[MAX];
    double distance=0.0;
};

vector <data> dataset;
vector <data> testData;
int N;

// Used to sort an array of points by increasing
// order of distance
bool comparison(data a, data b)
{
    return (a.distance < b.distance);
}

// This function finds classification of point p using
// k nearest neighbour algorithm. It assumes only two
// groups and returns 0 if p belongs to group 0, else
// 1 (belongs to group 1).

void clearString(string &s){
    for(int i = 0; i < s.size(); i++){
        if(s[i] == ',')s[i] = ' ';
    }
}

vector <string> columns;

void readFile(){

    srand(time(NULL));
    ifstream f("bank.txt");
    string s;
    getline(f, s);
    clearString(s);
    istringstream iss(s);
    while(iss >> s){
        columns.push_back(s);
    }

    N = columns.size();

    while(getline(f, s)){
        clearString(s);
        istringstream iss(s);
        int cnt = 0;
        double d;
        data dd;

        while(iss >> d){
          //  total[cnt] += d;
            dd.column[cnt++] = d;

        }

        //deci[ (int)dd.col[N - 1]]++;

        dataset.push_back(dd);
    }


}

double dist(data a, data b)
{
    double distance = 0.0;
    for (int i = 0; i < N; ++i)
    {
        distance+= (a.column[i]-b.column[i])*(a.column[i]-b.column[i]);
    }

    return distance;
}

void divide(){
    int testDataSize = dataset.size() / 10;

    srand(time(NULL));

    while(testDataSize){
        int val = (rand() * rand()) % dataset.size();
        //cout << val << " " << spamMsg.size() << endl;
        testData.push_back(dataset[val]);
        dataset.erase(dataset.begin() + val);
        testDataSize--;
    }

}

void printData()
{
    for (int i = 0; i < dataset.size(); ++i)
    {
        //for (int j = 0; j < N; ++j)
        //{
            cout << dataset[i].distance << " ";
        //}
        cout << "\n";
    }

}


int classify(int k, data testdata)
{
    // Fill distances of all points from p
    for (int i = 0; i < dataset.size(); i++)
        dataset[i].distance = dist(dataset[i], testdata);

    // Sort the Points by distance from p
    sort(dataset.begin(), dataset.end(), comparison);
    //printData();

    // Now consider the first k elements and only
    // two groups
    int freq1 = 0;     // Frequency of group 0
    int freq2 = 0;     // Frequency of group 1
    for (int i = 0; i < k; i++)
    {
        //cout << dataset[i].column[N-1] << endl;
        if (dataset[i].column[N-1] == 0.0)
            freq1++;
        else if (dataset[i].column[N-1] == 1.00)
            freq2++;
    }

    //cout << freq1 << " " << freq2 << endl;

    return (freq1 > freq2 ? 0 : 1);
}



// Driver code
int main()
{
    readFile();
    divide();
    //printData();



    cout << "Total: " << dataset.size() << endl;
    cout << "Test: " << testData.size()<< endl;

    for (int i = 0; i < testData.size(); ++i)
    {
        //printData();
        cout << "Real Decision: " << testData[i].column[N-1] << endl;
        cout << "My Decision: " << classify(5,testData[i]) << endl;
    }

    return 0;
}
