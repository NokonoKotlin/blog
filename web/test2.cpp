//include
//------------------------------------------
#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cctype>
#include <string>
#include <cstring>
#include <ctime>
#include<queue>
#include<complex>
using namespace std;
//conversion
//------------------------------------------
inline long long toint(string s) {long long v; istringstream sin(s);sin>>v;return v;}
template<class T> inline string toString(T x) {ostringstream sout;sout<<x;return sout.str();}
//math
//-------------------------------------------
template<class T> inline T sqr(T x) {return x*x;}
//typedef
//------------------------------------------
typedef long long ll;
typedef long long LL;
typedef vector<int > vi;
typedef vector<long long > VLL;
typedef vector<long long > vll;
typedef vector<string > ves;
typedef vector<char > vech;

typedef pair<long long , long long> pll;
typedef pair<long long , long long> PLL;
typedef map<ll , ll >mll;
typedef map<int , int >mii;
typedef map<char , int >mci;
typedef map<char , ll >mcl;
typedef vector<pair<ll , ll> > vpll;

//container util
//------------------------------------------
#define ALL(a)  (a).begin(),(a).end()
#define RALL(a) (a).rbegin(), (a).rend()
#define VECMAX(x) *max_element(ALL(x))
#define VECMIN(x) *min_element(ALL(x))
#define PB push_back
#define MP make_pair
#define SZ(a) int((a).size())
#define EACH(i,c) for(typeof((c).begin()) i=(c).begin(); i!=(c).end(); ++i)
#define EXIST(s,e) ((s).find(e)!=(s).end())
#define SORT(c) sort((c).begin(),(c).end())
//repetition
//------------------------------------------
#define FOR(i,a,b) for(long long i=(a);i<(b);++i)
#define REP(i,n)  FOR(i,0,n)
//#define MULTIPLE(i,n,k) for(int i = (k) ; i<(n) ; i+=k+1)//倍数ループ
//constant
//------------------------------------------
const double EPS = 1e-10;
const double PI  = acos(-1.0);
//clear memory
#define CLR(a) memset((a), 0 ,sizeof(a))
//debug
#define dump(x)  cerr << #x << " = " << (x) << endl;
#define debug(x) cerr << #x << " = " << (x) << " (L" << __LINE__ << ")" << " " << __FILE__ << endl;
#define SIZEOF(x) sizeof(x)/sizeof(x[0])


const long long INF = 4e18;
const long long NINF = 1 - INF;

#define ENDL cout << endl;
#define CIN(a) REP(i,a.size())cin >> a[i];

//二次元座標の点を表す構造体。xとyをメンバに持つ
struct POINT{
    double x;
    double y;

};



ll gcd(ll x, ll y) { return y ? gcd(y, x % y) : x; }
ll lcm(ll a, ll b) { return (a / gcd(a, b)) * b; }

/*
    nCr , 値が大きいとオーバーフローする
    n<=kなら1 (0C1や1C5= 1)
*/
ll nCr(ll n,  ll r){
  if ( r * 2 > n ) r = n - r;
  ll dividend = 1;
  ll divisor  = 1;
  for ( unsigned int i = 1; i <= r; ++i ) {
    dividend *= (n-i+1);
    divisor  *= i;
  }
  return dividend / divisor;
}



//firstが最大値（最小値） , second が index
template<class T>
pair<T , ll> maxP(vector<T> a , ll size){
    pair <T , ll> p;
    ll ind = 0;
    T mx = NINF;
    REP(i,size){
        if(mx<a[i]){
            mx = a[i];
            ind = i;
        }
    }
    p.first = mx;
    p.second = ind;
    return p;
}


template<class T>
pair<T , ll> minP(vector<T> a , ll size){
    pair <T , ll> p;
    T mn = INF;
    ll ind = 0;
    REP(i,size){
        if(mn > a[i]){
            mn = a[i];
            ind = i;
        }
    }
    p.first = mn;
    p.second = ind;
    return p;
}

template<class T>
T sumL(vector<T> a , ll size){
    T sum = 0;
    REP(i,size){
        sum += a[i];

    }
    return sum;
}


 //sort済みのvll ; a のleft ~ rightにtがいくつあるか
ll counT(VLL a ,ll left , ll right ,  ll t ){
    //sort(a.begin(),a.end());
    return upper_bound(a.begin() + left , a.begin() + right,t)-lower_bound(a.begin() + left , a.begin() + right, t);
}

//切り上げ
ll kiriage(ll a , ll b){
    return a/b + (a%b!=0);
}

#define COUNT(a,b) counT((a),0,a.size(),(b))

#define MAX(x) maxP(x,x.size())
#define MIN(x) minP(x,x.size())
#define SUM(x) sumL(x,x.size())




//-------要素を見つける-----------
ll search(vll &a , ll n ){//a内のnのindexを返す
    std::vector<ll>::iterator iter = std::find(a.begin(), a.end(), n);
    size_t index = distance(a.begin(), iter);
    return index;
}


//桁数
int getdigit(ll n){
    return log10(n)+1;
}



// toBinary[i]は,binaを二進数で表したときの下からi桁目のbitが入ってる
vll toBinary(ll bina){
    vll ans;
    for (ll i = 0; bina>0 ; i++)
    {
        ans.push_back(bina%2);
        bina = bina/2;
    }
    return ans;
}



//-----------MAIN:困った時メモ------------//
//    
//    Sqrは２乗 sqrtはルート , 二次元座標の点は struct POINT でも表せる(メンバはx , y)
//    小さい順ならpriority_queue<ll, vll, greater<ll> > と書く
//    ゲーム:grundy数 , グラフ:LCA,eulerTour,　
//    最大流がScalingMaxFlow , 最小費用流がPrimalDual<flow_t , cost_t>
//    めぐる式二分探索 , 半分前列挙
//    bitDP , 最小全域木でコストやグラフを求める , オイラーツアー , 0-1BFS 
//    オイラーツアーはDFS , 全域木はDFS , 三分探索
//    区間スケジューリング問題(右端が小さい順にソート)
//    定数倍(log)を落とすことで通ることもたまにある(setやmapに注意)
//    度数　＝ ラジアン × 180 ÷ 円周率
//    競技プログラミングでは「数が少ない方を考えると考察が進む場合がある」という典型テクニックがあります。
//    std::mapをループするときは、for(pair<type,type> x(要素): MAP)
//    期待値の線形性, 平均値は期待値の特殊な場合 

//    二次元累積和の計算 : s[i+1][j+1] = s[i][j+1] + s[i+1][j] - s[i][j] + a[i][j];
//    (a,b) -> (c,d)の二次元累積和 : s[c][d] - s[a][d] - s[b][c] + s[a][b]

//    multisetは便利 , 値の重複、upperbound、追加削除がlogN , *rbeginで最大値,*beginで最小値

#define ENDL cout << endl;


ll n , m;
ll h , w , k; 
string s;
vll A ,B;    
map<ll , ll>p;
ll v , e;

bool isin(ll i , ll j){
    return i>= 0 && i < n && j>= 0 && j < n;
}


bool isin2(ll i , ll j){
    return i>= n*n+5 && i< n*n+5+n && j>= n*n+5 && j < n*n+5+n;
}



bool isin3(ll i , ll j){
    return i>= 2*n*n+15 && i< 2*n*n+15+n && j>= 2*n*n+15 && j < 2*n*n+15+n;
}


int main(){
    
    
    
    cin >> n;

    ll sx,sy,gx,gy;
    cin >> sx >> sy;
    cin >> gx >> gy;
    sx--;
    sy--;
    gx--;
    gy--;
    vector<vpll> G(n*n*4 + 100 );

    /*
    元の座標 : i*n+j  
    一段上の座標　n*n+5 + i*n+j
    2段上の座標　2*n*n+15 + i*n+j
    */    

    vpll d = { MP(1,1) , MP(1,-1) , MP(-1,1) , MP(-1,-1) };
    vector<string> S(n);
    REP(i,n){
        cin >> S[i];
    }

    REP(i,n){
        REP(j,n){
            if(S[i][j] == '#')continue;
            G[i*n+j].push_back(MP(n*n+5 + i*n+j , 1 ) );
            G[i*n+j].push_back(MP(2*n*n+15 + i*n+j , 1 ) ); 

            G[n*n+5 + i*n+j ].push_back(MP( i*n + j, 0 ) );
            G[2*n*n+15 + i*n+j ].push_back(MP(i*n+j , 0 ) );

            for(pll nx : d){
                ll Y = i+nx.first;
                ll X = j+nx.second;
                if(isin(Y,X) && S[Y][X] != '#'){
                    if((nx.first == 1 && nx.second == 1) || (nx.first == -1 && nx.second == -1) ){
                        G[n*n+5+i*n+j].push_back(MP(n*n+5+Y*n+X,0));
                    }else{
                        G[2*n*n+15+i*n+j].push_back(MP(2*n*n+15+Y*n+X,0));
                    }
                }

            }
        }
    }

    vll dist(n*n*5 + 100 , INF);

    deque<ll> Q;
    Q.push_back(sx*n+sy);
    dist[sx*n+sy] = 0;
    while (!Q.empty()){
        ll now = Q.front();
        Q.pop_front();
        

        for(pll nx : G[now]){
            if(dist[nx.first] > dist[now] + nx.second){
                dist[nx.first] = dist[now] + nx.second;
                if(nx.second == 1){
                    Q.push_back(nx.first);
                }else{
                    Q.push_front(nx.first);
                }
            }
        }

    }
    
        /* code */
    if(dist[gy*n+gx] == INF){
        cout << -1 << endl;
        return 0;
    }
    cout << dist[gx*n + gy] << endl;

    return 0;   
}


