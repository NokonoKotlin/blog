//include
//------------------------------------------
#include<iostream>
#include<vector>
#include<queue>
#include<map>
#include<stack>
#include<string>
#include<complex>
using namespace std;
const long long INF = 1e18;
const double PI = 3.141592653589793;





/*
    高速フーリエ変換:
    fft(vector<double> a , bool f):=aをフーリエ変換したものを返す。bがtrueの時は逆変換.
    convolve(vector<double> a , vector<double> b ):=aとbを畳み込んだ数数列cを返す
    c をintとして扱う場合、誤差を消すために0.5を足してからintやll にキャストすると良い
*/
class FF{
    public:
    FF(){

    }
    ~FF(){

    }


    vector<complex<double> > fft(vector<complex<double>> a, bool inverse = false) {
        int n = a.size();
        int h = 0; // h = log_2(n)
        for (int i = 0; 1 << i < n; i++) h++;
        // バタフライ演算用の配置入れ替え
        for (int i = 0; i < n; i++) {
            int j = 0;
            for (int k = 0; k < h; k++) j |= (i >> k & 1) << (h - 1 - k);
            if (i < j) swap(a[i], a[j]);
        }
        // バタフライ演算
        for (int b = 1; b < n; b *= 2) {
            // 第 log_2(b) + 1 段
            // ブロックサイズ = b * 2
            for (int j = 0; j < b; j++) {
                // ブロック内 j 個目
                // 重み w = (1 の原始 2b 乗根の j 乗)
                complex<double> w = polar(1.0, (2 * PI) / (2 * b) * j * (inverse ? 1 : -1));
                for (int k = 0; k < n; k += b * 2) {
                    // k を先頭とするブロック
                    complex<double> s = a[j + k];         // 前
                    complex<double> t = a[j + k + b] * w; // 後
                    a[j + k] = s + t;                     // 前の更新
                    a[j + k + b] = s - t;                 // 後の更新
                }
            }
        }
        // 逆変換時にサイズで割る調整
        if (inverse)
            for (int i = 0; i < n; i++) a[i] /= n;
        return a;
    }
    // Cooley–Tukey FFT algorithm O(N log N)
    vector<complex<double>> fft(vector<double> a, bool inverse = false) {
        vector<complex<double>> a_complex(a.size());
        for (int i = 0; i < a.size(); i++) a_complex[i] = complex<double>(a[i], 0);
        return fft(a_complex, inverse);
    }
    
    // FFT による畳み込み O(N log N)
    vector<double> convolve(vector<double> a, vector<double> b) {
        int s = a.size() + b.size() - 1; // 畳み込み結果のサイズ
        int t = 1; // FFT に使う配列のサイズ（2 の累乗）
        while (t < s) t *= 2;
        a.resize(t); // FFT するためにリサイズ
        b.resize(t); // FFT するためにリサイズ
        vector<complex<double>> A = fft(a);
        vector<complex<double>> B = fft(b);
        for (int i = 0; i < t; i++) {
            //畳み込みの演算はここに記述
            A[i] *= B[i]; // 畳み込み結果の FFT 結果を得る
        }
        A = fft(A, true); // IFFT で畳み込み結果を得る
        a.resize(s);      // 畳み込み結果を入れるためにリサイズ
        for (int i = 0; i < s; i++) a[i] = A[i].real(); // 実部が答え
        return a;
    }
};












/*  
    aをフーリエ変換(逆変換)
    aのサイズは2の冪乗
*/
vector<complex<double>> FFT(vector<complex<double>> a , bool inv = 0){
    //aのサイズ(2の冪乗)
    int sz = a.size();
    //aのサイズのbitの高さ(ビット反転で使う)
    int bitsize = log2(sz);

    /*
        バタフライ演算のための並び替え : iに対して、iをビット反転した数値 : j を計算し、a の i,j の位置をスワップする。
    */
    for(int i = 0; i < sz ; i++){
        int j = 0;
        //aのサイズは2の冪乗なので、0-indexを考えたとき、2^bitsizeは範囲外,よってbit < bitsize
        for(int bit = 0 ; bit < bitsize ;bit++){
            //iのbit番目の桁が立っているなら、反転した位置のビットをjに立てる
            if(i&(1<<bit)) j |= (1<<(bitsize-1-bit)); 
        }
        //まだ見てない位置なら位置を入れ替える
        if(i<j)swap(a[i] , a[j]);


    }


    /*
        バタフライ演算を始めます(合計で約bitsize回の計算をする)。
        x回目のバタフライ演算では、演算の各グループのサイズは2^xになっている。
        x = 0 は初期状態のこと
    */
    for(int x = 1 ; x <= bitsize; x++){

        /*
            演算グループのサイズはGroupSizeだが、実際の計算ではその半分のGroupSize_Halfしか使わない
            なぜなら、後半半分の計算は前半半分の計算のついでにできるから
        */
        int GroupSize = (1<<x);
        int GroupSize_Half = GroupSize/2;


        /*
            係数がGroupSize_Half周期で同じになることに注目して、値を遷移させる。
            GroupSize_Half * K + j ... K >= 0 であるようなindexに対して、 係数:et が同じなので使いまわせる       
        */
        for(int j = 0 ; j < GroupSize_Half ; j++ ){ 

            complex<double> et;
            if(inv)et = polar(1.0 , (2*PI)/(GroupSize)*j);
            else et = polar(1.0 , (2*PI)/(GroupSize)*j*-1);
            
            /*  
                xステップ目のすべてのグループに対して、GroupSize_Half*k + j からの遷移を計算する
            */
            for(int k = 0 ; k < sz ; k+= GroupSize){
                complex<double> p , q;

                p = a[j+k];
                q = a[j+k+GroupSize_Half]*et;

                //前半の計算
                a[j+k] = p + q;
                //後半の計算
                a[j+k+GroupSize_Half] = p - q;

            }

        }   
        
    }
    if(inv){
        for(int i = 0 ;i < sz ; i++){
            a[i]/=sz;
        }
    }
    return a;
}








/*
    数列がvector<double>バージョンのFFT
*/
vector<complex<double>> FFT(vector<double> a , bool inv = 0){
    vector<complex<double>> a_(a.size());
    for(int i = 0 ; i < a.size() ; i++ )a_[i] = complex<double>(a[i],0);
    return FFT(a_ , inv); 
}









/*
    a,bを畳み込み
    　　-->  c[t] = Σ a[i]*b[t-i] .. (0<=i<=t) となるような数列：c を計算する
*/
vector<double> convolution(vector<double> a , vector<double> b ){
    //畳み込みの結果のサイズ
    int sz = a.size() + b.size() - 1;

    //計算に使うサイズ
    int t = 1;
    while(t < sz)t*=2;
    a.resize(t);
    b.resize(t);

    vector<complex<double>> A,B;
    vector<complex<double>> C(t);
    
    A = FFT(a,false);
    B = FFT(b,false);
    for(int i = 0 ; i < t ; i++){
        C[i] = A[i]*B[i];
    }
    C = FFT(C , true);
    //メモリがもったいないのでaをreturn用に使い回し
    vector<double>(sz).swap(a);
    for(int i = 0 ; i < sz ; i++){
        a[i] = C[i].real();
    }
    return a;
}




vector<int> sort_cyclic_shifts(string const& s) {
    int n = s.size();
    const int alphabet = 256;
    vector<int> p(n), c(n), cnt(max(alphabet, n), 0);

    //k=0のソート

    for (int i = 0; i < n; i++){
        cnt[s[i]]++;
    }
    for (int i = 1; i < alphabet; i++){
        cnt[i] += cnt[i-1];
    }
    for (int i = 0; i < n; i++){
        p[--cnt[s[i]]] = i;
    }
    c[p[0]] = 0;
    int classes = 1;
    for (int i = 1; i < n; i++) {
        if (s[p[i]] != s[p[i-1]]){
            classes++;
        }
        c[p[i]] = classes - 1;
    }


    //以下k=1…logn+1の反復をする
    vector<int> pn(n), cn(n);
    for (int k = 0; (1 << k) < n; ++k) {
        for (int i = 0; i < n; i++) {
            pn[i] = p[i] - (1 << k);
            if (pn[i] < 0){
                pn[i] += n;
            }
        }
        fill(cnt.begin(), cnt.begin() + classes, 0);
        for (int i = 0; i < n; i++){
            cnt[c[pn[i]]]++;
        }
        for (int i = 1; i < classes; i++){
            cnt[i] += cnt[i-1];
        }
        for (int i = n-1; i >= 0; i--){
            p[--cnt[c[pn[i]]]] = pn[i];
        }
        cn[p[0]] = 0;
        classes = 1;
        for (int i = 1; i < n; i++) {
            pair<int, int> cur = {c[p[i]], c[(p[i] + (1 << k)) % n]};
            pair<int, int> prev = {c[p[i-1]], c[(p[i-1] + (1 << k)) % n]};
            if (cur != prev){
                ++classes;
            }
            cn[p[i]] = classes - 1;
        }
        c.swap(cn);
    }
    return p;
}






#include<random>
int main(){
    string s;
    cin>> s;
    vector<int> p = sort_cyclic_shifts(s);
    while(1){
        string t;
        cin >> t;
        if(t == "Q"){
            break;
        }
        int lef = 0;
        int rig = p.size();
        
        while(rig - lef > 1){
            int mid = lef + (rig-lef)/2;
            int st = p[mid];
            bool fl = 1;

            for(int i = st ; i < min(s.size(),st+t.size()) ; i++){
                if(s[i] > t[i-st]){
                    fl = 0;
                }
            }
            if(fl)lef = mid;
            else rig = mid;
        }
        cerr << p[lef]<< endl;
    }

    
    
    return 0;
}
