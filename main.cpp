#include <iostream>
#include<bits/stdc++.h>
using namespace std;
class Question1{
public:
    vector<int> v; // global vector to save counted nodes
    void PrintGraph(vector<vector<int>> x){//to print the array if we want
        for (int i = 0; i < x.size(); i++) {
            for (int j = 0; j < x[i].size(); j++){
                cout<< x[i][j]<< " ";
            }
            cout<< "\n";
        }
    }
//create 2d array
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
    void Solve1(){
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
        cout<<"There are "<< connections<<" people with "<<k<< " connections away starting from "<<s ;
    }
};
class Question3{
public:
    typedef struct flight{
        int time;
        int pay;
        int from;
        int to;

    }Flight;//datatype for flights
    queue<queue<Flight>> bigQeue;
    queue<Flight> q;
    void PrintGraph(vector<vector<Flight>> x){//used to check that the 2d is correct // it is useless now in the program we can delete it
        for (int i = 0; i < x.size(); i++) {
            for (int j = 0; j < x[i].size(); j++){
                cout<< x[i][j].pay<< " ";
            }
            cout<<"\t";
            for (int j = 0; j < x[i].size(); j++){
                cout<< x[i][j].time<< " ";
            }
            cout<< "\n";
        }
    }
    vector<vector<Flight >> CreateFlight (int n,int e){
        vector<vector<Flight> > vec( n , vector<Flight> (n));
        int count = 0 ;
        int x , y,p,t; // vertex , edge , pay and time
        while(count!=e){
            cin>>x >>y >> t >> p;
            y=y-1;x=x-1;
            vec[x][y].from=x+1;
            vec[x][y].to=y+1;
            vec[x][y].time=t;
            vec[x][y].pay = p;
            count++;
        }
        return vec;
    }
//int x int y are the source and destination
    void possibilities (int x,int y ,vector<vector<Flight >> vec ,int k ){//k is the max passes it will take to achieve the destination

        if(x==y || k==1){ // here we achieve the destination or the max possible passes are all done
            if(x==y){
            bigQeue.push(q);
            }
            q=queue<Flight>();//clear small Queue
            return;
        }


        for(int i = 0;i<vec[0].size();i++){
            if(vec[x][i].pay!=0){//checking flight by payment
                q.push(vec[x][i]);//put flight to small queue
                possibilities(i,y,vec,k-1); //sending the function other source to check
            }//there is a flight in these coordinate
        }
    }
    void ShowQueue(queue<queue<Flight>> k){//unused function to check what is in queue
        while(!(k.empty())){
            queue <Flight> temp;
            temp = k.front();
            k.pop();
            while (!(temp.empty())){
                Flight t = temp.front();
                temp.pop();
                cout<<t.from<<"--> ";
                if(temp.empty())
                    cout<< t.to;
            }
            cout<<"\n";
//        k.push(temp);
        }
    }
    /*
     * The MinPrice Function simply works as i check all routes that are possible to achieve my destination
     * We will pop routes From 2D Queue
     * Each route is implemented as 1D Queue of type Flight
     * After check the price of each route if the price is smaller than the last route simply we will push this route again to 2D Queue
     * Otherwise if the price is bigger than last one it will not be pop again to the 2D Queue
     * This will take n+1 cycle to check the cheapest route
     */
    void MinPrice(queue<queue<Flight>> k,int M){
        int price =999999999;//a large number
        int price2=0;
        int totaltime=0;//time taken by flight
        queue <Flight> temp2;
        while(!(k.empty())){//all possible routes are saved in k queue of queue ** 2D Queue
            queue <Flight> temp;
            price2=0;//initializing the price that it will be calculated to next route
            temp = k.front();
            k.pop();
            int count = 0;
            while (!(temp.empty())){
                Flight t = temp.front();
                temp.pop();
                temp2.push(t);//pushing the flights to another  to save the flights from loss
                count++;
                price2 = price2 + (count*M)+(t.time*t.pay);

            }
            if(!(k.empty())){//checking if the 2D Queue is empty or not
                if(price2<price){
                    k.push(temp2);
                    price = price2;
                }
                temp2=queue<Flight>();
            } else{ break;}
        }
        cout<<" The min cost route is : ";
        while (!(temp2.empty())){
            Flight t = temp2.front();
            temp2.pop();
            if (totaltime==0)
                totaltime=totaltime+t.time;//the first flight it doesn't take layover time between connecting flights
            else
                totaltime=totaltime+t.time+1;// layover time between connecting flights is always one hour.
            cout<<t.from<<"-->";
            if(temp2.empty())
                cout<< t.to;
        }
        cout<<" and its price is: "<<price2<<" , and take time "<<totaltime<<" hours";
    }
    void Solve3(){
        int m , n,e , x,y;
        cout<<"Enter ammount of m:";
        cin>>m;
        cout<<"Enter number of cities:";
        cin>>n;
        cout<<"Enter number of routes :";
        cin>>e;
        cout<<"Please enter source city";
        cin>>x;
        cout<<"Please enter destination city";
        cin>>y;
        int k = y-1;//max route to destination
        vector<vector<Flight> > a = CreateFlight(n,e);
        possibilities(x-1,y-1,a,k);
        MinPrice(bigQeue,m);
    }
};
int main() {
    int choice;
    cout<<"\n1-Question 1 \t2-Question 2 \n3-Question 3 \t4-Exit\n";
    cout<<"Please Enter the number you want";
    cin>>choice;
    while (choice){
        if(choice == 1){
            Question1 q1;
            q1.Solve1();
            cout<<"\n---------------------------\n";
        }
        else if(choice == 2){

        }
        else if(choice == 3){
            Question3 q3;
            q3.Solve3();
            cout<<"\n---------------------------\n";
        }
        else if(choice == 4){
            cout<<"\nThanks for using";
            cout<<"\n---------------------------\n";
            break;
        }
        cout<<"\n1-Question 1 \t2-Question 2 \n3-Question 3 \t4-Exit\n";
        cout<<"Please Enter the number you want";
        cin>>choice;

    }

//Question3 q ;
//q.Solve3();


}