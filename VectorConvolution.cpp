#include <iostream>
#include <vector>
#include <climits>
#include <string>
using namespace std;

double VectorConvolution(vector<double>& v1, vector<double>& v2, int k){

    int m = v1.size();
    int n = v2.size();

    if( k >= m + n - 1 || k < 0 ){
        return INT_MIN;
    }

    double poly = 0;

    for(int s = 0; s <= k; s++){
        int t = k - s;
        // std::cout<<"k: "<<k<<";s: "<<s<<";t: "<<t<<endl;
        if( 0 <= t && t <= n-1 && 0<= s && s <= m-1){
            poly += v1[s] * v2[t];
        }
    }

    return poly;
}

vector<double> VectorConvolution(vector<double>& v1, vector<double>& v2){
    vector<double> conv(v1.size() + v2.size()-1);

    for(int i = 0; i < conv.size(); i ++){
        conv[i] = VectorConvolution(v1,v2,i);
    }

    return conv;
}

string vector_str(vector<double> &v){
    string output = "[";
    
    for( int i = 0 ; i < v.size(); i ++ ){
        output = output +  to_string(v[i])+",";

        if( (i+1) % 10 == 0)
            output += "\n";
    }

    return output + "]";
}

int main(){
    vector<double> v1 = {-7,6,3};
    vector<double> v2 = {4,-5,2};

    std::cout<<"k = 0, poly is "<<VectorConvolution(v1,v2,0)<<endl;
    std::cout<<"k = 1, poly is "<<VectorConvolution(v1,v2,1)<<endl;
    std::cout<<"k = 2, poly is "<<VectorConvolution(v1,v2,2)<<endl;
    std::cout<<"k = 3, poly is "<<VectorConvolution(v1,v2,3)<<endl;
    std::cout<<"k = 4, poly is "<<VectorConvolution(v1,v2,4)<<endl;
    std::cout<<"k = 5, poly is "<<VectorConvolution(v1,v2,5)<<endl;

    std::vector<double> conv = VectorConvolution(v1,v2);
    std::cout<<vector_str(conv)<<endl;

    return 0;
}
