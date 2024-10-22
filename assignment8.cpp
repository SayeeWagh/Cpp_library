#include <iostream>

using namespace std;

const int INF = 99999;

void dijkstra(int source, int adjMatrix[10][10], int n){
    int distance[10];
    bool visited[10];

    for(int i=0; i<n; i++)
    {
        distance[i] = INF;
        visited[i] = false;
    }
    distance[source] = 0;

    for(int count = 0; count<n-1; count++)
    {
        int minDist = INF, u=-1 ;

        for(int i=0; i<n; i++)
        {
            if(!visited[i] && distance[i]<minDist)
            {
                minDist = distance[i];
                u = i;
            }
        }
        visited[u] = true;

        for(int v=0; v<n; v++)
        {
            if(!visited[v] && adjMatrix[u][v]!=INF && distance[u]+adjMatrix[u][v]<distance[v])
            {
                distance[v] = distance[u] + adjMatrix[u][v];
            }
        }
    }
    cout<<"Shortest distances from the source landmark "<<source <<endl;

    for(int i=0; i<n; i++)
    {
        if(distance[i] == INF)
        {
            cout<<"Landmark "<<i<<": Unreachable"<<endl;
        }
        else{
            cout<<"Landmark "<<i<<": "<<distance[i]<<" units"<<endl;
        }
    }
}

int main()
{
    int n;
    int adjMatrix[10][10];

    cout<<"Enter the Number of Landmarks: ";
    cin>>n;
    cout<<endl;

    cout<< "Enter the adjacency matrix (use 0 if no direct path): "<<endl;
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++)
        {
            cin>>adjMatrix[i][j];
            if(adjMatrix[i][j] == 0 && i != j) {
                adjMatrix[i][j] = INF;
            }
        }
    }
    cout<<endl;

    int source;
    cout<<"Enter the source landmark (0 to " <<n-1<< "): ";
    cin>>source;

    dijkstra(source, adjMatrix, n);
    return 0;
}
