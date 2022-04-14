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


int main(){

    int n ;
    cin >> n;
    vector<double> a(n+1,0) , b(n+1,0);
    for(int i = 0 ; i< n ; i++){
        cin >> a[i+1] >> b[i+1];
    }
    vector<double> c = convolution(a,b);

    for(int i = 0 ; i < 2*n ; i++){
        cout << (long long )(c[i+1] + 0.5)<< endl; 
    }

    return 0;
}
