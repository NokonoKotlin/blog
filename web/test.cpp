
//include
//------------------------------------------
#include<iostream>
#include<vector>
#include<queue>
#include<map>
#include<algorithm>
using namespace std;

const long long INF = 1e18;




int main(){ 

    queue<int> q;

    int n ;cin >> n ;
    vector<int> B(n),W(n);
    for(int i = 0; i < n ; i++)cin >>W[i];
    for(int i = 0; i < n ; i++)cin >>B[i];



    vector<vector<int> > G(150000);//Grundy数の状態遷移グラフ
    vector<int> indegree(150000,0);
    

    //十分大きく取る
    int identifer = 2600;//グリッドグラフを１次元で表現するとき、１次元目と２次元目の境目を用意する( 二次元の点(X、Y) <=> X*identifer + Y ) 


    
    for(int x = 0; x< 150000 ; x++){
        int X = x/identifer;
        int Y = x%identifer;
        if(X>=1){
            if(Y+X<identifer){
                G[x].push_back((X-1)*identifer + Y+X);
                indegree[(X-1)*identifer + Y+X]++;

                
            }
        }
    }


    for(int x = 0; x< 150000 ; x++){
        int X = x/identifer;
        int Y = x%identifer;
        if(Y>=2){
            int M = Y/2;
            for(int k = 1 ; k<=M ; k++){
                G[x].push_back(X*identifer + Y-k);
                indegree[X*identifer + Y-k]++;
            }
        }
    }




    
    


    for(int x = 0; x < 150000 ; x++){
        if(indegree[x]==0){
            q.push(x);
        }
    }

    vector<int> dfs;
    while(q.empty()==false){
        int x = q.front();
        q.pop();

        dfs.push_back(x);
           
        for(int next : G[x]){

            indegree[next]--;
            if(indegree[next] == 0){
                q.push(next);
            }
        }
    }

    vector<int> Grundy(150000 , -1);

    for(int i = (int)dfs.size()-1 ; i >= 0 ; i--){
        int now = dfs[i];
        vector<int> memo;//遷移先のGrundy数を保管
        for(int nx : G[now]){
            memo.push_back(Grundy[nx]);
        }
        sort(memo.begin() , memo.end());
        int mex = 0;
        for(int x : memo){
            if(mex == x)mex++;
        }
        Grundy[now] = mex;
    }

    int judge = 0;
    for(int i = 0 ; i < n ; i++){
        judge ^= Grundy[W[i]*identifer + B[i]];
    }

    if(judge){
        cout << "First" << endl;
    }else{
        cout <<"Second" << endl;
    }




    return 0;
}
