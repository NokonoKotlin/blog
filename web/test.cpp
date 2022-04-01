//include
//------------------------------------------
#include <vector>
#include<iostream>
#include<math.h>
#include<map>
using namespace std;


#define debug(x) cerr << #x << " = " << (x) << " (L" << __LINE__ << ")" << " " << __FILE__ << endl;


template<class T>
class SegTree{
    private:

    vector<T> node;
    

    public:
    int Size;//葉のサイズ
    
    
    SegTree(int Size_){
        
        init(Size_);

    }

    void init(int S){
        
        int k = log2(S) + 2;

        vector<T>((1<<k),0).swap(node);
        Size = (1<<(k-1));//葉のサイズ
    }

    /*
        区間に対する演算 ... + , xor や maxなどができる
    */
    T merge(T a, T b){
        //自分で指定..他にも変更すべき場所があるので注意
        return max(a,b);
    }


    /*
        葉から根に登りながら更新
        mergeの種類によって編集しないといけない
    */
    void update(int index , T val){
        if(index < 0 || index >=Size)return;

        index += Size;
        T prev = node[index];
        node[index] = val;
        T dif = val - prev;
        while(index/2 > 0){
            node[index/2] = merge(node[(index/2*2)] , node[(index/2)*2+1]);
            
            
            index/=2;
        }

    }

    /*
        [lef,rig)の半開区間について,木の頂点:SubRootが覆う区間について調べる。

    */
    T query(int lef , int rig , int SubRoot = 1 , int SubTreeLeft = 0 , int SubTreeRight = -1){
        if(SubRoot == 1)SubTreeRight = Size;

        
        if(rig <= SubTreeLeft){
            return 0;
        }else if(lef >=SubTreeRight){
            return 0;
        }else if(  lef <= SubTreeLeft &&  SubTreeRight <= rig ){
            return node[SubRoot];
        }else{
            int border = (SubTreeLeft+SubTreeRight)/2;
            return merge( query(lef,rig,SubRoot*2,SubTreeLeft,border) , query(lef,rig,SubRoot*2+1,border,SubTreeRight) );
        }
    }



};



int main(){
    long long  n , m , k , A , B;    string s;    map<long long  , long long >p;
    vector<pair<long long ,long long >> Pairs;
    pair<long long , long long> Ap;
    cin >> n >> k;
 
    vector<long long> a(1005000,0);
    
    for(int i = 0 ; i < n ; i++)cin>> a[i];
    long long INF = -1e18;
    for(long long x:a)INF = max(x,INF);
    SegTree<long long> S(n);

    vector<long long> dp(n+10,0);

    for(int i = 0 ; i < n ; i++){
        long long maxi = max(a[i] - k, (long long)0);
        dp[i] = S.query( maxi , min(a[i] + k + 1 , INF + 1 ) ) + 1;
       
        S.update(a[i] , dp[i]);
        //debug(dp[i])
    }
    
    long long ans = -1e18;
    for(long long x:dp)ans = max(ans,x);
    cout << ans << endl;
 
 
 
 
 
 
    return 0;
}
 
 
 



