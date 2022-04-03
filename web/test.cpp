//include
//------------------------------------------
#include <vector>
#include<iostream>
#include<math.h>
#include<map>
#include<deque>
using namespace std;


#define debug(x) cerr << #x << " = " << (x) << " (L" << __LINE__ << ")" << " " << __FILE__ << endl;



int h , w;

bool isin(int i, int j){
    return (i>= 0 && i < h && j >= 0 && j < w);
}

int main(){
    
    cin >> h >> w;
    vector<string> S(h);
    for(int i = 0 ; i < h ; i++){
        cin >> S[i];
    }   

    vector<vector<pair<int , int> > > G(h*w);
    int st = 0*w+0;
    int gl = (h-1)*w+w-1;

    vector<pair<int,int> > dire = {make_pair(0,1),make_pair(1,0),make_pair(-1,0),make_pair(0,-1)};

    for(int i = 0 ; i < h ; i++){
        for(int j = 0 ; j < w ; j++){

            //コスト０の辺
            for(pair<int ,int > nx :dire ){
                int I = i+nx.first;
                int J = j+nx.second;
                if(isin(I,J) && S[I][J] == '.'){
                    G[i*w+j].push_back(make_pair(I*w+J , 0));
                }
            
            }

            //コスト1の辺,自分の位置から一度の破壊でたどり着ける範囲なら問答無用で張れる
            for(int p = -2; p <=2 ; p++){
                for(int q = -2 ; q<= 2 ; q++){
                    if(abs(p*q) == 4)continue;
                    int I = i + p;
                    int J = j + q;
                    if(isin(I,J)){
                        G[i*w+j].push_back(make_pair(I*w+J , 1));     
                    }
                }
            }



        }
    }



    vector<int> dist(h*w , -1);


    deque<pair<int,int>> Que;
    Que.push_front(make_pair(st,0));


    while(Que.empty() == false){
        int now = Que.front().first;
        int d = Que.front().second;
        Que.pop_front();

        if(dist[now] != -1)continue;
        dist[now] = d;
        

        for(pair<int ,int> nx :G[now]){
            if(dist[nx.first] == -1){
                
                if(nx.second != 0 ){
                    Que.push_back(make_pair(nx.first , d+nx.second));
                }else{
                    Que.push_front(make_pair(nx.first , d+nx.second));
                }
            }
        }

    }

    
    cout << dist[gl] << endl;


 
 
    return 0;
}
 
 
 



