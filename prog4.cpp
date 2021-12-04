#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <limits>
#include<float.h>

using namespace std;

int main(int argc, char* argv[]){

    ifstream myFile(argv[1]);
    if(!myFile.is_open()) throw runtime_error("could not open file");

    string line;
    vector<pair<double, double>> points;

    while(getline(myFile,line)){
        pair<double, double> p;
        p.first = stod(line.substr(0, line.find(' ')));
        p.second = stod(line.substr(line.find(' ')+1));
        points.push_back(p);
    }

    double min = DBL_MAX;
    pair<double, double> answer;

    int ans1;
    int ans2;


    for(int i=1;i<=1000;i++){
        int ran1 = rand()%points.size();
        int ran2 = rand()%points.size();

        while(ran1==ran2) ran2 = rand()%points.size();

        pair<double, double> p1 = points[ran1];
        pair<double, double> p2 = points[ran2];

        double a = (p2.second - p1.second)/(p2.first-p1.first);
        double b = p1.second-(a*p1.first);
        //y=ax+b
        vector<double> distances;
        
        for(int i=0;i<points.size();i++){
            if(i==ran1||i==ran2) continue;
            else{
                double temp = abs((p2.first-p1.first)*(p1.second-points[i].second)-(p1.first-points[i].first)*(p2.second-p1.second))/
                              sqrt(pow(p2.first-p1.first,2)+pow(p2.second-p1.second,2));
                distances.push_back(temp);
                //cout << temp << endl;
            }
        }

        sort(distances.begin(),distances.end());

        if(distances[distances.size()/2]<min){
            answer = make_pair(a,b);
            min = distances[distances.size()/2];
            ans1=ran1;
            ans2=ran2;
        }

    }

    pair<double, double> p1 = points[ans1];
    pair<double, double> p2 = points[ans2];

    points.erase(points.begin()+ans1);
    points.erase(points.begin()+ans2);

    sort(points.begin(),points.end(),[p1,p2](pair<double,double>a1, pair<double, double>a2){
        return abs((p2.first-p1.first)*(p1.second-a1.second)-(p1.first-a1.first)*(p2.second-p1.second))/sqrt(pow(p2.first-p1.first,2)+pow(p2.second-p1.second,2))<
        abs((p2.first-p1.first)*(p1.second-a2.second)-(p1.first-a2.first)*(p2.second-p1.second))/sqrt(pow(p2.first-p1.first,2)+pow(p2.second-p1.second,2));
    });

    points.erase(points.begin()+points.size()/2,points.end());

    double xm=0;
    double ym=0;

    double numerator =0;
    double denominator = 0;

    for(int i=0;i<points.size();i++){
        xm+=points[i].first;
        ym+=points[i].second;
    }
    xm/=points.size();
    ym/=points.size();

    for(int i=0;i<points.size();i++){
        numerator+= (points[i].first-xm)*(points[i].second-ym);
        denominator+= pow((points[i].first-xm),2);
    }

    answer.first = numerator/denominator;
    answer.second = ym-answer.first*xm;

    cout<<answer.first<<" "<<answer.second<<endl;

    return 0;
}