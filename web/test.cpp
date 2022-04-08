
//include
//------------------------------------------
#include<iostream>
#include<vector>
#include<queue>
#include<map>
using namespace std;

const long long INF = 1e18;




int main(){ 

    priority_queue<int , vector<int> , greater<int> > pq;

    int n , m ;cin >> n >> m;
    vector<vector<int> > G(n);
    vector<int> indegree(n,0);
    vector<map<int , int> > is_used(n);
    for(int i = 0 ; i < m ; i++){
        int a, b;cin >> a >> b;
        a--;//0-indexに直してる
        b--;
        if(is_used[b][a] != 0)continue;
        G[a].push_back(b);
        indegree[b]++;//入ってくる辺の本数
        is_used[b][a] = 1;
    }

    vector<int> A(n);
    size_t index_now = 0;

    for(int x = 0; x < n ; x++){
        if(indegree[x]==0){
            pq.push(x);
        }
    }

    if(pq.empty()){
        //初期段階でindegree = 0 の頂点が無いならば、ループが存在する(閉路がある)のでダメ。
        cout << -1 << endl;
        return 0;
    }

    while(pq.empty()==false){
        int x = pq.top();
        pq.pop();

        A[index_now] = x;
        index_now++;        
        for(int next : G[x]){
            if(indegree[next] == 0){
                //閉路があったらダメ
                cout << -1 << endl;
                return 0;
            }
            indegree[next]--;
            if(indegree[next] == 0){

                pq.push(next);
            }
        }
    }

    if(index_now<n){
        //Aに追加されていない頂点が残っている。(indegree >0 となる頂点があるかどうかでも判定可能)
        cout << -1 << endl;
        return 0;
    }


    for(int x : A){
        //1-indexに直しましょう
        cout << x+1 << " ";
    }
    cout << endl;



    return 0;
}
