#include <iostream>
#include <algorithm>

using namespace std;

int KnapSackRecursive(int W, int wt[], int val[], int n){
    if( n == 0 || W == 0){
        return 0;
    }

    if(wt[n-1] > W){
        return KnapSackRecursive(W, wt, val, n-1);
    }
    else{ //wt[n-1] <= W
        return max(val[n-1] + KnapSackRecursive(W-wt[n-1], wt, val, n-1),
        KnapSackRecursive(W, wt, val, n-1));
    }
}

int KnapSack(int W, int wt[], int val[], int n){
    int i, w;
    int K[n+1][W+1];

    for(int i = 0 ; i <= n; i ++){
        for(int w = 0; w <= W; w++){
            if(i == 0 || w == 0){
                K[i][w] = 0;
            }
            else if(wt[i-1] <= w){
                K[i][w] = max(val[i-1] + K[i-1][w-wt[i-1]], K[i-1][w]);
            }else{ //wt[i-1] > w
                K[i][w] = K[i-1][w];
            }
        }
    }
    return K[n][W];
}




int main(){
    int val[] = { 1, 4 ,5, 7};
    int wt[] = {1,3,4,5};

    int W = 7;

    int n = sizeof(val)/sizeof(val[0]);

    std::cout<<KnapSackRecursive(W, wt, val, n)<<endl;
    
    std::cout<<KnapSack(W, wt, val, n)<<endl;
    
    return 0;


}
