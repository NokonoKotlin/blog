#include<iostream>
#include<vector>
#include<deque>
#include<queue>
#include<algorithm>
#include<map>




const long long INF = 1e18;
using namespace std;

class UnionFind{
    vector<int> par;
    vector<int> rank;
    int Size;
    public:
    UnionFind(int Size_){
        Size = Size_+10;
        vector<int>(Size).swap(par);
        vector<int>(Size,1).swap(rank);
        for(int i = 0 ; i < Size ; i++){
            par[i] = i;
        }
    }

    int root(int x){
        if(par[x] == x){
            return x;
        }else{
            return root(par[x]);
        }
    }


    void unite(int a, int b){
        if(root(a) == root(b))return;
        int ra = root(a);
        int rb = root(b);
        if(rank[ra] > rank[rb]){
            par[rb] = ra;
        }else if(rank[rb] > rank[ra]){
            par[ra] = rb;
        }else{
            par[ra] = rb;
            rank[rb]++;
        }
    }

    bool same(int a, int b){
        return root(a) == root(b);
    }

};



int N , M ,Q;

struct edge{
    public:
    long long  u , v , weight , index;

    edge(){}
    
    edge(long long a , long long b , long long c ,long long d){
        u = a ;
        v = b;
        weight = c;
        index = d;
    }

};


bool sort_compare(edge a, edge b){
    return a.weight < b.weight;
}

int main(){
    cin >> N >> M >> Q;




    vector<edge> E(M+Q);

    //edge.index は、何番目のクエリの辺か(0なら元々グラフにある辺　、x(>=1)ならx番目のクエリの辺)
    //辺を重みが小さい順に順に見ているとする。
    //辺eを見ている時、kruskal法に基づいて採用する場合、eが元々グラフ上にあった辺なら頂点同士を連結する。
    //eがクエリ由来の辺なら、ans[e.index]="Yes"として、辺eは使わない(これ以降に見る元のグラフ由来の辺の採用に影響するから)。


    for(int i = 0 ; i<M;i++){
        long long a , b , c;
        cin >> a >> b >> c;
        E[i] = edge(a,b,c,0);
    }

    for(int i = 0 ; i < Q ; i++){
        long long a , b , c;
        cin >> a >> b >> c;
        E[M+i] = edge(a,b,c,i+1);
 
        
        
    }

    //重みが小さい順にソート
    sort(E.begin(),E.end(),sort_compare);

    UnionFind T(N);

    vector<string> ans(Q,"No");

    for(edge e:E){   
        //前から見ていく

        //非連結成分同士を繋ぐ辺の場合
        if(T.same(e.u,e.v) == 0){
             
           
            if(e.index == 0){ 
                //元々存在する辺の場合、連結する。
                T.unite(e.u,e.v);
            }else{
                //後から追加する辺の場合、判定だけして連結はしない
                ans[e.index-1] = "Yes" ;
            }
        }
    }

    for(string s:ans)cout << s << endl;



    return 0;
}