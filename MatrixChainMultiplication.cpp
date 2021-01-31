# include<bits/stdc++.h>
using namespace std;

int dp[100][100];

int matrixChainMemoised(int *p, int l, int r)
{
    if( l == r ){
        dp[l][r] = 0;
        return 0;
    }

    if( dp[l][r] != -1){
        return dp[l][r];
    }

    dp[l][r] = INT_MAX;

    for(int k = l; k < r ; k ++ ){
        dp[l][r] = min(dp[l][r],
        matrixChainMemoised(p, l, k)+matrixChainMemoised(p, k+1, r)+p[l-1]*p[k]*p[r]);
    }

    return dp[l][r];
}

int MatrixChainOrder(int *p, int n){
    int l = 1, r = n - 1;
    return matrixChainMemoised(p,l,r);
}

int main(){
    // There are four matrices, A is 1*2, B is 2*3, C is 3*4
    // int arr[] = {1,2,3,4};

    // There are four matrices, A is 1*2, B is 2*3, C is 3*4
    int arr[] = {40,20,30,10,30};

    int n = sizeof(arr)/sizeof(arr[0]);

    memset(dp,-1, sizeof(dp));

    cout << "Minimum number of multiplications is "<< MatrixChainOrder(arr, n); 

}
