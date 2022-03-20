#include<iostream>
#include<vector>
#include<deque>

const long long INF = 1e18;
using namespace std;

long long X[20] , Y[20] , Z[20];


long long max(long long a,long long b){
    if(a>b)return a;else return b;
}

long long min(long long a,long long b){
    if(a<b)return a;else return b;
}

long long abs(long long a, long long b){
    return max(a,b) - min(a,b);
}


/*
    i->jのdist
*/
long long dist(int i , int j){
    return abs(X[j]-X[i])+abs(Y[j]-Y[i]) + max(0ll , Z[j]-Z[i]);
}

int main(){
    int N ;
    cin >> N ;

    

    for(int i = 0 ; i < N ; i++){
        cin >> X[i] >> Y[i] >> Z[i];
    } 

    vector<vector<long long > > dp((1<<N) , vector<long long >(N,INF));

    dp[0][0] = 0;
    for( int S = 0 ; S < (1<<N) ; S++){
        
        for(int v = 0 ; v < N ; v++){
            if((S&(1<<v))==0)continue;

            int S_ = S-(1<<v);
            
            for(int x = 0 ; x < N ; x++){
                //xがS_に含まれてなくても,その場合dp[S_][x]=INFなので問題ない
                dp[S][v] = min(dp[S][v] , dp[S_][x] + dist(x,v));  
            }   
            
        }

    }
    
    
    cout << dp[(1<<N)-1][0] << endl;

    return 0;
}