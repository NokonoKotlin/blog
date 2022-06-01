#include<iostream>
#include<vector>
#include<string>
#include<set>
#include<algorithm>
using namespace std;
int INF = 500000000;



struct query{
    int l , r , id;
    query(){}
};

bool cp_r(query a , query b){
    return a.r < b.r;
}

int main(){
    int N ,Q;
    cin >> N >> Q;
    vector<int> c(N);
    vector<int> place(N+1,-1);
    vector<query> Queries(Q);
    MyMultiSet<int> S;
    
    for(int i = 0 ; i < N ; i++){
        cin >> c[i];
    }

    for(int i = 0 ; i < Q ; i++){
        cin >> Queries[i].l >> Queries[i].r;
        Queries[i].id = i;
    }
    sort(Queries.begin() , Queries.end() , cp_r);    
    int R = 0;
    vector<int> ans(Q);

    for(query qr : Queries){
        while(R < qr.r){
            if(place[c[R]] == -1){
                
            }else{
                S.erase(place[c[R]]);
            }
            
            place[c[R]] = R;
            S.insert(place[c[R]]);

            R++;
        }
        
        int res = S.Size - S.lower_bound(qr.l-1);
        ans[qr.id] = res;//元の順番で出力
        

    }

    for(int res : ans){
        printf("%d\n" , res);
    }
}

















