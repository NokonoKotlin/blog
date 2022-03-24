#include<iostream>
#include<vector>
#include<deque>
#include<queue>




const long long INF = 1e18;
using namespace std;



int N , M ;

struct Edge{
    long long first ,second ,third;
    Edge(long long u ,long long c,long long k){
        first = u;
        second = c;third = k;
    }
};

int main(){
    int X,Y;
    cin >> N >> M >> X >> Y;

    vector<vector<Edge> > G(N+1);

    for(int i = 0 ; i< M ; i++){
        long long c,k;
        int u , v ;
        cin >> u >> v >> c >> k;
        G[u].push_back(Edge(v,c,k));
        G[v].push_back(Edge(u,c,k));
        
        

    }

    int st = X;

    priority_queue<pair<long long , int > , vector<pair<long long , int > > , greater<pair<long long ,int> > > Q;
    Q.push(make_pair(0,st));
   
    vector<long long > dist(N+1, INF);     
    dist[st] = 0;
    
    while(Q.size()>0){
        int now = Q.top().second;
        long long now_dist = Q.top().first;
        Q.pop();    
        

        if(dist[now] < now_dist)continue;



        for(Edge next : G[now]){
            if(now_dist%next.third == 0){//待たなくて良い
                if(dist[next.first] > dist[now] + next.second){
                    dist[next.first] = dist[now] + next.second;
                    Q.push(make_pair(dist[next.first] , next.first));
                }
            }else{//待たないといけない
                if(dist[next.first] > dist[now] + next.second + next.third*((now_dist + next.third-1)/next.third ) - now_dist){
                    dist[next.first] = dist[now] + next.second+ next.third*((now_dist + next.third-1)/next.third ) - now_dist;
                    Q.push(make_pair(dist[next.first] , next.first));
                }
            }
            
        }


    }
    
    if(dist[Y]>=INF){
        cout <<-1 << endl;
        return 0;
    }
    cout << dist[Y] << endl;

    return 0;
}