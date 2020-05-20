#include <iostream>
#include<bits/stdc++.h>
using namespace std;
vector<int> v; // global vector to save counted nodes
//create 2d array
void PrintGraph(vector<vector<int>> x){
    for (int i = 0; i < x.size(); i++) {
        for (int j = 0; j < x[i].size(); j++){
            cout<< x[i][j]<< " ";
        }
        cout<< "\n";
    }
}
vector<vector<int >> CreateGraph (int n,int e){
    vector<vector<int> > vec( n , vector<int> (n, 0)); // NxN matrix with zeros
    int count = 0 ;
    int x , y; // vertex and edge
    cout<<"please enter edges in the form (u  v):";
    while(count!=e){
       cin>>x >>y;
       y=y-1;x=x-1;
       vec[x][y]=1;
       vec[y][x] = 1;
       count++;
    }
    return vec;
}
int connectionNumber(vector<vector<int>> vec,int k ,int x,int count){// vec is the graph , k , v connections has counted ,x starting from
    if(!(find(v.begin(),v.end(),x)!=v.end()))
        v.push_back(x); // add the node to prevented vector
    if(k==1){
        int z =0;
        for(int i = 0;i<vec[x].size();i++) {
            if ((vec[x][i] == 1)) {
                if (!(find(v.begin(),v.end(),i)!=v.end())) {
                   z++;
                    v.push_back(i);
                }
            }
        }
        return z;

    }
    else {
        for (int i = 0; i < vec[x].size(); i++) {
            if ((vec[x][i] == 1)) {
                if (!(find(v.begin(), v.end(), i) != v.end())) {
                    v.push_back(i);
                }

            }
        }
        for (int i = 0; i < vec[x].size(); i++) {
            if ((vec[x][i] == 1)) {
                count= count + connectionNumber(vec, k - 1, i, count);
            }
        }
    }
    return count;
}
void Question1(){
    int n ;//number of vertex
    int e; // number of edges
    int k;
    int s;
    int count =0;


    cout<<"please enter number of vertices:";
    cin>> n;
    cout<<"please enter number of edges:";
    cin>> e;
    vector<vector<int> > x = CreateGraph(n,e);
    cout<<"please enter k:";
    cin>>k;
    cout<<endl;
    cout<<"please enter the starting vertex";
    cin>>s;


//    PrintGraph(x);
    int connections = connectionNumber(x,k,s-1,count);
    cout<<"NUmber of connections starting from "<<s<<" is equal "<<connections<<" with k = "<< k ;
}
int main() {
    Question1();


}