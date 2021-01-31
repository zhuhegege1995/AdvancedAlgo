#include <iostream>
# define V 4
# define INF 99999

using namespace std;

void printSolution(int dist[][V]) ;

void floyWarshall(int graph[][V]){
    // create a matrix dist[][], it will be the 
    // final output
    int dist[V][V];

    // copy graph to dist for initialization
    for (int i = 0 ; i < V; i ++ ){
        for(int j = 0; j <  V; j ++ ){
            dist[i][j] = graph[i][j];
        }
    }

    // work on iterations to update matrix[][] by
    // taking different cells as intermediate cells

    for( int k = 0; k < V; k ++){
        for( int i = 0; i < V; i ++ ){
            for( int j = 0 ; j < V; j ++){
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }

    printSolution(dist);
}


void printSolution(int dist[][V]) 
{ 
    cout<<"The following matrix shows the shortest distances"
            " between every pair of vertices \n"; 
    for (int i = 0; i < V; i++) 
    { 
        for (int j = 0; j < V; j++) 
        { 
            if (dist[i][j] == INF) 
                cout<<"INF"<<"     "; 
            else
                cout<<dist[i][j]<<"     "; 
        } 
        cout<<endl; 
    } 
}

int main(){

    int graph[V][V] = {{0,5,INF,10},
                        {INF,0,3,INF},
                        {INF,INF,0,1},
                        {INF,INF,INF,0}};

    floyWarshall(graph);

    return 0;
}
