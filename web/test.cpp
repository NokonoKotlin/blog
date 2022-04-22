#include<iostream>
#include<vector>
#include<string>
using namespace std;






int flow[300][300];


bool dfs(int src , int snk , vector<int>& used){
    if(src == snk)return true;
    bool res = false;
    used[src] = 1;
    for(int v = 0 ; v < 300 ; v++){
        if(used[v] == 0){
            if(flow[src][v] >= 1){
                flow[src][v]--;
                flow[v][src]++;//逆辺
                if(dfs(v,snk,used)){
                    return true;
                }else{
                    flow[src][v]++;
                    flow[v][src]--;
                }
            }
        }
    }
    return false;

}




int main(){ 

    int n ; cin >> n;
    vector<int> a(n) ,b(n) , c(n), d(n);
    for(int i = 0 ; i < n ; i++){
        cin >> a[i] >> b[i];
    }

    for(int i = 0 ; i < n ; i++){
        cin >> c[i] >> d[i];
    }

    for(int i = 1; i < n+1 ; i++){
        for(int j = 1 ; j < n+1 ; j++){
            if(a[i-1] < c[j-1] && b[i-1] < d[j-1]){
                flow[i][n+j]=1;
            }
        }
    }
    

    for(int i = 1 ; i < n + 1 ; i++){
        flow[0][i] = 1;
    }

    for(int j = n+1;j < n+1+n ; j++){
        flow[j][n*2+15] = 1;
    }
    

    int ans = 0;
    vector<int>used(300,0);
    while (dfs(0,n*2+15 , used)){
        ans++;
        for(int &x:used)x = 0;
    }
    cout << ans << endl;
    







    return 0;
}








