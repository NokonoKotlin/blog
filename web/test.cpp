
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






//最小公倍数、最大公約数

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










/*
    永続UnionFind : コンストラクタにはSizeを渡す
    各uniteしたときに時刻が1進むとして、各時刻での連結情報が取れる、記憶力の良いUF
    unite(a,b) : a,bをマージ(一回処理するごとにnowが+1される)
    findRoot(a,t) : 時刻t時点でのaの根
    is_same(u,v,t) : 時刻tで、u,vが同じグループか
    size(a,t) : 時刻tで,aを含むグループのサイズ
*/
struct PersistentUnionFind{
    vector<ll> parent; // 親ID
    vector<ll> time; // 親が更新された時刻 (更新は1度きり)
    vector<ll> rank; // その頂点を根とする木の深さ (根ノードは深さ0)
    ll now; // 時刻（結合回数）//アクセス可能(書き換え不可)
    vector<vector<pair<ll,ll> > > num; // (時刻, 頂点数)を要素にもつvector
    
    PersistentUnionFind(ll sz){
        parent.resize(sz);
        REP(i,sz) parent[i]=i;
        now = 0;
        time.resize(sz, INF);
        rank.resize(sz, 0);
        
        num.resize(sz);
        REP(i,sz) num[i].push_back(MP(0,1));
        
    }

    // rankベースの統合
    void unite(ll a, ll b){
        now++;

        ll rootA = findRoot(a, now);
        ll rootB = findRoot(b, now);
        if(rootA==rootB) return;

        // AにBをつけるようにしたい
        if(rank[rootA]<rank[rootB]) swap(rootA, rootB);

        ll merged_size = size(rootA, now) + size(rootB, now);
        num[rootA].push_back(MP(now, merged_size));
        
        // AにBをつなげる (Bの親がA)
        parent[rootB] = rootA;
        time[rootB] = now;
        if(rank[rootA]==rank[rootB]){
            rank[rootA]++;
        }
    
    }

    // a : id
    // t : time
    /*
        時刻t自転のaの根(所属グループ)
    */
    ll findRoot(ll a, ll t){
        // tより後に子になっているならば
        if(time[a]>t){
            return a; // 今はまだaは親
        }
        else{
            // time[a]<=t つまり、tの時点で誰かの子
            // 親がいるので再帰で求める
            return findRoot(parent[a], t);
        }
    }

    // 時刻tにて同じ木に属するか
    bool is_same(ll u, ll v, ll t){
        return findRoot(u,t) == findRoot(v,t);
    }

        // 時刻tにおいて、頂点xを含む木の要素数を返す
    ll size(ll u, ll t){
        ll r = findRoot(u, t);
        // num[r]に(0,1), (10,5), ... というサイズ履歴が入っている
        // (例)
        // t = 3なら？サイズは1
        // t = 10なら？サイズは5
        // t = 15なら？サイズは5
        // 配列のどれかの要素の.secondに、返すべきサイズは入っている
        ll left = 0; // ありうる
        ll right = num[r].size(); // ng
        while(left+1!=right){
            ll center = (left+right)/2;
            if(num[r][center].first>t){
                right = center;
            }else{
                left = center;
            }
        }
        return num[r][left].second;
    }
};








//----UnionFind(n) , nは要素数-----
class UnionFind{
    private:
    vll par;

    public:
    int Size;
    vll rank;//rankが高いほど上の親である
    int setSize;
    
    //配列の中身は0 ~ N-1
    UnionFind() {}
    UnionFind( LL N):rank(N){
        Size = N;
        par.resize(N);
        setSize = N;
        REP(i,Size)par[i] = i;
        REP(i,N)rank[i] = 0;
    }
    ~UnionFind(){
        Release();
    }

    void Release()
    {
        if (par.size()==0) {
            return;
        }

        
        std::vector<ll>().swap(par);
    }



    void init(ll N ){
        Size = N;
        par = vll(N);
        rank = vll(N);
        REP(i,Size)par[i] = i;
        REP(i,Size)rank[i] = 0;
    }


    LL root(LL x){
        if(par[x] ==x)return x;
        else {
            par[x] = root(par[x]);
            return par[x];
        }
    }


    void unite(LL x, LL y){
        LL rx = root(x);
        LL ry = root(y);
        if(rx == ry)return;
        if(rank[rx] < rank[ry]){
            par[rx] = ry;//rankの高い方を親にする
        }else{
            par[ry] = rx;
            if(rank[rx] == rank[ry]){
                //rankがどちらも同じ時、どちらか好きな方を親にしてそのrankを1上げる(今回はxのランクをあげるよう実装)
                rank[rx]++;
            }
        }
        setSize--;
        
    }

    bool same(LL x, LL y){
        LL rx = root(x);
        LL ry = root(y);
        return rx == ry;
    }
};









ll n , h ,w;
bool isin(ll y , ll x){
    return (y>=0 && y<h && x >= 0 && x<w);
}

int main(){

    cin >>  h >> w >> n;

    vector<vll> S(h,vll(w));
    mll p;
    vll cand;
    map<ll,vpll> ind;

    REP(i,h){   
        REP(j,w){
            cin >> S[i][j];
            if(p[S[i][j]]==0){
                p[S[i][j]]=1;
                cand.push_back(S[i][j]);
               
            } ind[S[i][j]].push_back(MP(i,j));
        }
    }

    cand.PB(0);
    
    sort(RALL(cand));

    vpll d = {MP(0,1) ,MP(1,0),  MP(0,-1),MP(-1,0)};
    UnionFind T(h*w);
    
    ll sz = 0;
    ll fl = 0;
    ll f = INF;
    
    for(ll x : cand){
        
        sz += ind[x].size();
        
        for(pll now : ind[x]){
            ll i = now.first;
            ll j = now.second;
            
            for(pll nx:d){
                ll I = i+nx.first;
                ll J = j+nx.second;
                if(isin(I,J) && S[I][J]>=x){
                    if(T.same(i*w+j , I*w+J) == false){
                        sz--;
                    
                    }
                    T.unite(i*w + j , I*w+J);
                }
            }
        }
        
        if(sz == n){
            f = x;
        }

    }

    
    sort(ALL(cand));

    auto it = lower_bound(ALL(cand) , f);
    if(it == cand.begin()){
        cout << 0 << endl;
        return 0;
    }
    it--;
    cout <<(*it) << endl;






    return 0;
}