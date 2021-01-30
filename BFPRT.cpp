#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <set>
#include <unordered_set>
#include <math.h>
using namespace std;



int BFPRT2(vector<int> &arr, int l, int r, int k, int bucket_size);
int partition1(vector<int> &v, int l, int h);
void print_vector(vector<int> & v);
int insert_sort(vector<int>& arr, int l, int r);
int partition(vector<int> &arr, int l, int r, int index);
int get_median_index2(vector<int>& arr, int l, int r);
int get_median_index2(vector<int>& arr, int l, int r);
int BFPRT2(vector<int> &arr, int l, int r, int k, int bucket_size);

/*the 1st element as the pivot*/
void print_vector(vector<int> & v){
    for (auto i = v.begin(); i != v.end(); ++i)
        std::cout << *i << ", ";
    std::cout<<endl;
}

/*the 1st element as the pivot*/
int partition1(vector<int> &v, int l, int h){
/* use the 1st element as pivot by default*/

    int i =l, j = h;

    int pivot = v[l];

    while( i < j ){
        while( v[j] >= pivot && i < j )
            j --;
        v[i] = v[j];

        while( v[i] <= pivot && i < j )
            i ++;
        v[j] = v[i];
    }
    
    v[i] = pivot;

    //print_vector(v);

    return i;
}

/*the last element as the pivot*/
int partition2(vector<int>& arr, int l, int r) 
{ 
    int x = arr[r], i = l; 
    for (int j = l; j <= r - 1; j++) { 
        if (arr[j] <= x) { 
            swap(arr[i], arr[j]); 
            i++; 
        } 
    } 
    swap(arr[i], arr[r]); 
    return i; 
}

/*the 1st element as the pivot*/
int partition3(vector<int> &arr, int l, int r){
    if( l < 0 || r < 0 || l > arr.size() || r > arr.size() || l > r)

        return -1;

    if( l == r){
        return l;
    } 
    else{
        int pivot = arr[r];

        int i = l;
        int j = l;

        while( j <= r - 1){
            if(arr[j] <= pivot){
                swap(arr[i], arr[j]);
                i ++ ;
            }

            j++;
        }

        swap(arr[i], arr[r]);
        return i;    
    }
}

/*use the customized pivot*/
int partition(vector<int> &arr, int l, int r, int index){
    if( index < l || index > r || l < 0 || r >= arr.size() || l > r ){
        return -1;
    }
    else{
        std::swap(arr[index], arr[l]);
        return partition1(arr, l, r);
    }
}

void quick_sort1(vector<int> &vec, int l, int h){
       
    if( l < h){
        int k = partition1(vec,l,h);
        quick_sort1(vec, l, k-1);
        quick_sort1(vec, k+1, h);
    }
}

void quick_sort2(vector<int> &vec, int l, int h){
       
    if( l < h){
        int k = partition2(vec,l,h);
        quick_sort2(vec, l, k-1);
        quick_sort2(vec, k+1, h);
    }
}

void quick_sort3(vector<int> &vec, int l, int h){
       
    if( l < h){
        int k = partition3(vec,l,h);
        quick_sort3(vec, l, k-1);
        quick_sort3(vec, k+1, h);
    }
}


int select(vector<int> &vec, int l, int r, int k){

    if( k < l || k > r)
        return -1;

    int p = partition3(vec, l, r);

    if ( p == k ){
        return vec[k];
    }
    else if( p < k ){
        return select(vec, p+1, r, k);
    }else{ 
        return select(vec, l, p -1, k);
    }
}

int insert_sort(vector<int>& arr, int l, int r){
    if( l > r || l < 0|| l >arr.size() - 1 || r > arr.size()-1 || r < 0)
        return -1;
    else if( l== r)
        return 0;
    else{
        
        for(int i = l + 1; i <= r; i ++ ){
            int j = i-1;
            int temp = arr[i];
            while( j >= l && temp < arr[j] ){
                arr[j+1] = arr[j];
                j --;
            }
            arr[j+1] = temp;
        }

        return 1;
    }
}

int get_median_index(vector<int>& arr, int l, int r){
    // based on STL sort() algorithm
    if( l > r || l < 0|| l >arr.size() - 1 || r > arr.size()-1 || r < 0)
        return -1;
    else if( l == r )
        return l;
    else{
        std::sort(arr.begin() + l, arr.begin() + r + 1);
        return (l + (r-l)/2);
    }
}

int get_median_index2(vector<int>& arr, int l, int r){

    if( l > r || l < 0|| l >arr.size() - 1 || r > arr.size()-1 || r < 0)
        return -1;
    else if( l == r )
        return l;
    else{
        if (insert_sort(arr,l,r) != -1 )
            return (l + (r-l)/2);
        return -2;
    }
}

int get_medianOfMedian_index2(vector<int>& arr, int l, int r, int bucket_size){
    if( r - l < bucket_size ) // if the bucket size is less than the expected size
        return get_median_index2(arr,l,r);
    
    int j = l-1 ; //right border of medians

    for( int i = l; i + bucket_size-1 <= r; i += bucket_size){
        int med_index = get_median_index2(arr,i,i+bucket_size-1);
        std::swap(arr[med_index], arr[++j]); // put all medians to the head part of the array 
    }

    return BFPRT2(arr, l, j, ((j-l+1)/2)+1, bucket_size); 
}

int BFPRT2(vector<int> &arr, int l, int r, int k, int bucket_size){
    if(l>=r)
        return l;
    
    int med_index = get_medianOfMedian_index2(arr, l, r, bucket_size);

    med_index = partition(arr,l,r,med_index);

    int med_rank = med_index; // the rank of the median

    if(k == med_rank)
        return med_index;
    else if( k < med_rank )
        return BFPRT2(arr, l, med_index - 1, k, bucket_size);
    else
        return BFPRT2(arr, med_index+1, r,k , bucket_size);
}

int getSmallestKey(vector<int> &arr, int l, int r, int k, int bucket_size, int target, int temp_sum){
    if(l>=r)
        return l;
    
    int med_index = get_medianOfMedian_index2(arr, l, r, bucket_size);

    med_index = partition(arr,l,r,med_index);

    int med_rank = med_index; // the rank of the median
    std::cout<<"temp_sum: "<<temp_sum<<endl;
    std::cout<<"med_rank: "<<med_rank<<endl;
    std::cout<<"k: "<<k<<endl;
    std::cout<<"target: "<<target<<endl;
    if(k == med_rank){
        temp_sum = temp_sum + arr[k];
        std::cout<<"med_rank: "<<med_rank<<"; temp_sum"<<temp_sum<<endl;
        if(temp_sum >= target)
            return med_index;
        else
            return getSmallestKey(arr,l, r, k+1, bucket_size, target, temp_sum);
    }
    else if( k < med_rank )
        return getSmallestKey(arr,l, med_index-1, k, bucket_size, target, temp_sum);
    else
        return getSmallestKey(arr,med_index+1,r, k, bucket_size, target, temp_sum);
}


int main(){
    std::srand(unsigned(std::time(nullptr)));
    std::vector<int> v_rand;

    std::unordered_set<int> randset;
    while(randset.size() <= 500 ){
        int randv = rand()% 2000;
        randset.insert(randv);
    }

    v_rand.insert(v_rand.begin(), randset.begin(), randset.end());
    std::cout<<"BFPRT: "<<BFPRT2(v_rand,0,v_rand.size()-1,5,5)<<endl;
    std::cout<<"Samllest Key: "<<getSmallestKey(v_rand,0,v_rand.size()-1,0,5,10000,0)<<endl;
    // std::sort(v_rand.begin(), v_rand.end());
    print_vector(v_rand);
    

}
