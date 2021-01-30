#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <limits.h>
using namespace std;

string vector_str(vector<double> &v){
    string output = "[";
    
    for( int i = 0 ; i < v.size(); i ++ ){
        output = output +  to_string(v[i])+",";

        if( (i+1) % 10 == 0)
            output += "\n";
    }

    return output + "]";
}

int CutRoadOpt(vector<int> prices, int n){
    
    vector<int> opt(prices.size() + 1);
    
    for(int i = 1; i <= n ; i ++){
        int max_val = -1;
        for(int j = 0; j < i; j ++ ){
            max_val =max(max_val, prices[j] + opt[i-j-1]);
        }
        opt[i] = max_val;
    }

    return opt[n];
}


int CutRoadBruteForce(vector<int> prices, int n){
    if( n <= 0 ){
        return 0;
    }

    int max_val = -1;

    for( int i = 0 ; i < n ; i ++ ){
        max_val = max(max_val, prices[i] + CutRoadBruteForce(prices, n-i-1));
    }

    return max_val;
}


int main(){

    vector<int> prices = {1,5,8,9,10,17,17,20};

    std::cout<<"Max Prices: "<<CutRoadBruteForce(prices, 8)<<endl;
    std::cout<<"Max Prices: "<<CutRoadOpt(prices, 8)<<endl;
}
