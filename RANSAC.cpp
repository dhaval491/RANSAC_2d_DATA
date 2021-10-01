#include<random>
#include<vector>
#include<iostream>
#include<algorithm>
#include<map>
#include<stack>
#include<queue>
#include</home/Dhaval/Documents/matplotlib-cpp/matplotlibcpp.h>
using namespace std;
namespace plt = matplotlibcpp;
// generate points around line y = slope*x and some outliers
vector<pair<int,int>>  generate_points(int inCount, int inTolerence, int outCount)
{
    int slope  = 2;
    vector<pair<int,int>> sol;
    for(int i = 0;i<inCount;i++)
    {
        pair<int,int> p = make_pair(i+(inTolerence*(float) rand()/RAND_MAX), slope*(i+(inTolerence*(float) rand()/RAND_MAX)));
        sol.push_back(p);
    }
    for(int i = 0; i< outCount;i++)
    {
        pair<int,int> p = make_pair(i+(outCount*(float) rand()/RAND_MAX), slope*(i+(outCount*(float) rand()/RAND_MAX)));
        sol.push_back(p);
    }

    return sol;
}

void plot_points(vector<pair<int,int>> points)
{
    vector<int> x_p,y_p;
    for(int i = 0;i< points.size();i++)
    {
        x_p.push_back(points[i].first);
        y_p.push_back(points[i].second);
    }
   
    plt::title("Randomly generated data of 2d points ");
    plt::xlim(0,40);
    plt::ylim(0,100);
    //plt::xlim(*min_element(x_p.begin(),x_p.end()),*max_element(x_p.begin(),x_p.end()));
    //plt::ylim(*min_element(y_p.begin(),y_p.end()),*max_element(y_p.begin(),y_p.end()));
    map<string, string> m;m["r"] = "o";
    plt::plot(x_p,y_p,"go");
    plt::show();
    return;
}
pair<int,int> generate_index(vector<pair<int,int>>points)
{
    int index1 = 0+(points.size()-1)*(float) rand()/RAND_MAX;
    int index2 = 0+(points.size()-1)*(float) rand()/RAND_MAX;
    while(index1 == index2)
    {
        index2 = 0+(points.size()-1)*(float) rand()/RAND_MAX;
    }
    return pair<int,int>(index1,index2);
}
int main()
{
    int numIterations = 100;
    float tolerence  = 1.0;
    int maxInliers =  0;
    int inTolerence = 2;
    int inCount = 20;
    int outCount = 20;
    int coeficients[3];
    vector<pair<int,int>> points = generate_points(inCount,inTolerence,outCount);
    plot_points(points);
    for(int i = 0;i<numIterations;i++)
    {
        pair<int,int> index = generate_index(points);
        int A = points[index.first].second - points[index.second].second;
        int B = points[index.second].first - points[index.first].first;
        int C =  points[index.second].second*points[index.first].first - points[index.first].second*points[index.second].first;
        int numInliers = 0;
        for(int i = 0;i<points.size();i++)
        {
            float d = abs(A*points[i].first + B*points[i].second + C)/sqrt(pow(A,2)+pow(B,2));
            if(d < tolerence) numInliers++;
        }
        if(numInliers>maxInliers) 
        {
            maxInliers = numInliers;
            coeficients[0] = A; coeficients[1] = B; coeficients[2] = C;
        }
        
    }


    int A = coeficients[0];
    int B = coeficients[1];
    int C =  coeficients[2];
    vector<int> xvalues,yvalues;
    for(int i=0;i<points.size();i++)
    {
        xvalues.push_back(points[i].first);
        yvalues.push_back(points[i].second);
    }
    pair<int,int> x_pair = make_pair(*min_element(xvalues.begin(),xvalues.end()),*max_element(xvalues.begin(),xvalues.end()));
    pair<float,float> y_pair = make_pair((-C-A*x_pair.first)/B, (-C-A*x_pair.second)/B);
    vector<int> x {x_pair.first,x_pair.second};
    cout<<x_pair.first<<" "<<x_pair.second<<endl;
     cout<<y_pair.first<<" "<<y_pair.second<<endl;
    vector<float> y {y_pair.first,y_pair.second};

    //plt::figure();
   // plt::xlim(*min_element(xvalues.begin(),xvalues.end()),*max_element(xvalues.begin(),xvalues.end()));
   // plt::ylim(*min_element(yvalues.begin(),yvalues.end()),*max_element(yvalues.begin(),yvalues.end()));
   plt::xlim(0,inCount+inTolerence);
   plt::ylim(0,100);
    vector<int> x_p,y_p;
    for(int i = 0;i< points.size();i++)
    {
        x_p.push_back(points[i].first);
        y_p.push_back(points[i].second);
    }
   
    //plt::figure();
    plt::title({"Fitted line"});
    plt::plot(x_p,y_p,"go");
    //plt::show();
    plt::plot(x, y);
    plt::show();



    return 0;
}
