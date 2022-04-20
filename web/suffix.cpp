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












/*
    s：元の文字列
    type:s[i]のタイプ(LS型) = type[i]
    LMS_index : sのlmsのindexを並べたもの
    charnum_max : 使われている文字の種類数
*/
template<class String_or_VectorInt>
vector<int> induced_sort(String_or_VectorInt &s , vector<char> &type , vector<int> &LMS_index , int charnum_max ){

    vector<int> res(s.size() , -1);
    
    vector<int> bin(charnum_max+1,0);//文字コードをindexとして、文字cはsuffixArrayの[ bin[c] , bin[c+1] )の場所に現れる
    vector<int> bin_cop;//binはcount変数としてよく使うので、使う際はコピーを使う





    for(int c : s){//必ずint !! 
        //各文字が現れる回数をカウント
        bin[c]++;
    }


       

    /*
        suffixの先頭の文字のみをソートした時、文字:cが現れる位置は、[ bin[c] , bin[c+1] ) である(半開区間なのに注意)
            例えば、bin[$] = 0 , bin[a] = 1 , bin[b] = 1 , bin[c] = 3 , bin[d] = 4の時、
            先頭の文字だけソートしたら { $ b b c ... } となる

    */ 


    int now_ind = 0;
    for(int i = 0 ; i < bin.size() ;i++){
        int next_ind = now_ind + bin[i];
        bin[i] = now_ind;
        now_ind = next_ind;
    }






    //induce sortのステップ１(LMSを、s[LMS]のbinの末尾(上限)の方から埋めていく(SufArrにはindexを入れていく))
    bin_cop = bin;//カウント用

    for(int i = (int)LMS_index.size()-1 ; i >= 0 ; i--){
        int lms = LMS_index[i];
        int c = s[lms];

        res[bin_cop[c+1]-1] = lms;
        bin_cop[c+1]--;
    }
    


    //ステップ２(SufArrを前から見て、SufArrに接尾辞のindex: i が入っていて、s[i-1]がL型の時、SufArrのbin[s[i-1]]の先頭の位置からi-1を入れていく
    bin_cop = bin;//カウント用
    for(int i = 0 ; i < res.size() ; i++){
        if(res[i] == -1)continue;//何も入っていない
        if(res[i] == 0)continue;//&なので、0-1はout of index
        if(type[res[i]-1] == 'S')continue;

        int c = s[res[i]-1];

        res[bin_cop[c]]=res[i]-1;
        bin_cop[c]++;
        
    }


    //ステップ３(SufArrを後ろから見て、SufArrに接尾辞のindex: i が入っていて、s[i-1]がS型の時、SufArrのbin[s[i-1]]の末尾(上限)の位置からi-1を入れていく
    bin_cop = bin;//カウント用
    for(int i = (int)res.size()-1 ; i >= 0 ; i--){
        if(res[i] == -1)continue;//何も入っていない
        if(res[i] == 0)continue;//&なので、0-1はout of index
        if(type[res[i]-1] == 'L')continue;
       
        int c = s[res[i]-1];

        res[bin_cop[c+1]-1]=res[i]-1;
        bin_cop[c+1]--;
        
    }


    return res;

}


/*
    接尾辞配列(string or vector<int>)
    suffix arrayを返す。

    特に、得られたsuffix arrayを使って、sのsuffix(接尾辞)に関して
        lower_bound_SA  と  upper_bound_SAができる。

        lower_bound_SA(s , suffixarray , t) := sの接尾辞たちの内、t以下のものの個数を求める。
        upper_bound_SA(s , suffixarray , t) := sの接尾辞たちの内、t未満のものの個数を求める。

    charnum_max = sに現れる文字の個数(文字コードの最大値)
*/
template<class String_or_VectorInt>
vector<int> SuffixArray(String_or_VectorInt s , int charnum_max = 1100000){
    /*
        計算中はsの末尾に0を加える
        0を加えるので、sの中身を全て+1する
        末尾の0はsのどの文字よりも小さい
    */

    charnum_max++; 
    for(int i = 0 ; i < s.size() ; i++){
        //0を最小として追加するので、インクリメント
        s[i]++;
    }
    s.push_back(0);


    //sのindexの型(L型かS型か)
    vector<char> type(s.size(),'.');
    
    //LMSかどうか
    vector<bool> isLMS(s.size(),false);

    //sの前から、LMSであるようなindexを順に入れる
    vector<int>LMS_index;  

    //一度目のinduced_sortの結果を入れるやつ。メモリの節約のために,LMSに番号を割り振るときに再利用する
    vector<int> SA(s.size(),-1);

    //for文の外で変数が必要な時、これ使って
    int now_ind = 0;

    //LMSに番割り振った番号の最大値
    int max_num = -1;



    //一度目のソートの結果で、前からLMSである部分だけ順番に取り出す。そして、適切に並べ替える。
    vector<int>NewLMS_index;

    //NewLMS_indexのi番目に割り振る番号
    vector<int> num_for_LMS;





    /*
        sのindex:iが
                S型 := sのi文字目以降の接尾辞が、i+1文字目以降の接尾辞よりも辞書順で小さい。
                L型 := sのi文字目以降の接尾辞が、i+1文字目以降の接尾辞よりも辞書順で大きい。
    */

    type.back()='S';

    for(int i = (int)s.size()-2 ; i>= 0 ; i--){
        //i以降の接尾辞と、i+1以降の接尾辞の辞書順を比べる。(後ろから見れば、iとi+1文字目のみ見ればわかる)

        if(s[i] < s[i+1]){
            //s[i] < s[i+1]ならSタイプ(先頭の文字からの比較で辞書順は決まるから)
            type[i] = 'S';
        }else if(s[i]>s[i+1]){
            //s[i] > s[i+1]ならLタイプ(先頭の文字からの比較で辞書順は決まるから)
            type[i] = 'L';
        }else{
            //s[i]とs[i+1]が等しい時、i以降の接尾辞とi+1以降の接尾辞の先頭1文字を取ればいいので、i+1とi+2の場合と同じタイプ。
            type[i] = type[i+1];
        }

    }


       
    for(int i = 0 ; i < s.size()-1 ; i++){
        if(type[i] == 'L' && type[i+1] == 'S'){
            //LMSであるようなindexたちを入れる
            LMS_index.push_back(i+1);
        }
    }
    for(char c : type)cout << c << " ";
    ENDL;

    for(int ind : LMS_index)isLMS[ind]=true;

    vector<int>(LMS_index.size()).swap(NewLMS_index);//並べ替えたLMSも、個数は同じ
    vector<int>(LMS_index.size()).swap(num_for_LMS);//LMSに番号を割り振るので、LMS_indexのサイズと同じ


    /*
        LMS(Left-Most-S)とは、s[i-1]がL型で,s[i]がS型になるような index:i .
        LMS-substringとは、LMSであるようなindexに挟まれた文字列のこと。

        また、文字cのビンとは、求めるSuffixArrayにおいて、文字cで始まるsuffixが現れる場所の範囲のことである。
        文字:cが現れる位置は、[ bin[c] , bin[c+1] ) である(半開区間なのに注意)
            例えば、bin[$] = 0 , bin[a] = 1 , bin[b] = 1 , bin[c] = 3 , bin[d] = 4の時、
            先頭の文字だけソートしたら { $ b b c ... } となる

    */





    //一度目のinducedsort
    SA = induced_sort(s,type,LMS_index,charnum_max);



    now_ind = 0;
    for(int x : SA){
        if(isLMS[x]){
            NewLMS_index[now_ind] = x;
            now_ind++;
        }
    }

    
    


    now_ind = 0;
    //メモリがもったいないので、SAを再利用。LMSのindexに番号を割り振ります。
    SA[NewLMS_index[now_ind]]=0;
    
    now_ind++;

    
    
    for(int i = 1 ; i < NewLMS_index.size() ; i++){
        //Iは、i-1番目のLMSのindex ,　Jはi番目のLMSのindex
        int J = NewLMS_index[i-1];
        int I = NewLMS_index[i];
        bool is_same_I_and_J = true;

        for(int x = 0 ; x < s.size() ; x++){
            if(J+x>=s.size())break;
            if(s[I+x]!=s[J+x] || isLMS[I+x] != isLMS[J+x]){
                is_same_I_and_J = false;
                break;
            }
            else if(x > 0 && (isLMS[I+x] || isLMS[J+x]))break;
        }

        if(is_same_I_and_J){
            num_for_LMS[now_ind] = num_for_LMS[now_ind-1];
        }else{
            num_for_LMS[now_ind] = num_for_LMS[now_ind-1] + 1;
        }
        SA[NewLMS_index[now_ind]] = num_for_LMS[now_ind];
        
        now_ind++;
    }

    
    
    
    //num_for_LMSを再利用。元の列:sの前から、LMSを発見したら順にそのLMSに割り振った番号をnum_for_indの後ろに追加
    now_ind = 0;
    for(int i = 0 ; i < s.size() ; i++){
        if(isLMS[i]){
            num_for_LMS[now_ind] = SA[i];
            now_ind++;
            max_num = max(SA[i] , max_num);
        }
        
    }


    //先頭を空けておきたいので、+1
    SA.resize(LMS_index.size()+1);
    

    if(max_num +1 == num_for_LMS.size()){
        for(int i = 0 ; i < num_for_LMS.size() ; i++){
            SA[num_for_LMS[i]+1] = i;//先頭は空けておくので+1
            
        }
    }else{
        SA = SuffixArray(num_for_LMS , max_num+5);
        
    } 



    

    
    SA.erase(SA.begin());//先頭は邪魔


    for(int i = 0 ; i < SA.size(); i++){
        NewLMS_index[i] = LMS_index[SA[i]];
      
    }



    return induced_sort(s,type,NewLMS_index,charnum_max);


}


/*
    比較でバグらせたら目も当てられないので、うしさんのブログからパクってきました。
*/
template<class String_or_VectorInt>
bool cp_with_suffix(String_or_VectorInt &s , int si , String_or_VectorInt t){
    int ti = 0;
    while(si < s.size() && ti < t.size()) {
      if(s[si] < t[ti]) return true;
      if(s[si] > t[ti]) return false;
      si++;
      ti++;
    }
    return si >= s.size() && ti < t.size();   
}


/*
    文字列(vector<int>) s のsuffixうち、suffix_arrayをもとに、辞書順で t 未満のものの個数を求める
    元の列 s , sのsuffix_array , 検索する列 t
*/
template<class String_or_VectorInt>
int lower_bound_SA(String_or_VectorInt &s , vector<int> &suffix_array , String_or_VectorInt t){
    int lef = -1;
    int rig = suffix_array.size();
    while(rig-lef>1){
        int mid = lef + (rig-lef)/2;
        if(cp_with_suffix(s , suffix_array[mid],t)){
            lef = mid;
        }else{
            rig = mid;
        }
    }
    return rig;
}


/*
    文字列(vector<int>) s のsuffixうち、suffix_arrayをもとに、辞書順で t 以下のものの個数を求める
    元の列 s , sのsuffix_array , 検索する列 t
    うしさんのブログ参照
*/
template<class String_or_VectorInt>
int upper_bound_SA(String_or_VectorInt &s , vector<int> &suffix_array , String_or_VectorInt t){
    int lef = lower_bound_SA(s,suffix_array,t) - 1;
    int rig = suffix_array.size();
    t.back()++;
    while(rig-lef>1){
        int mid = lef + (rig-lef)/2;
        if(cp_with_suffix(s , suffix_array[mid],t)){
            lef = mid;
        }else{
            rig = mid;
        }
    }
    t.back()--;
    return rig;
}















int main(){
    string s;
    cin >> s;
    
    auto v = SuffixArray(s);
    v.erase(v.begin());
    
    for(int x : v)cout << x << " ";
    ENDL;

    return 0;   
}

