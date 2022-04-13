//include
//------------------------------------------
#include<iostream>
#include<vector>
#include<queue>
#include<map>
#include<stack>
#include<string>
using namespace std;
const long long INF = 1e18;


long long MOD = 1000000007;
long long modpow(long long a, long long b , long long m){
    vector<int> bit;
    
    for(int i = 0 ; i <= 62;i++){
        if(b&(1ll<<i))bit.push_back(i);
    }
    vector<long long> power(63 , 0);
    power[0] = (a%m+m)%m;
    for(int x = 1 ; x <= 62 ; x++){
        power[x] = power[x-1]*power[x-1];
        power[x] %=m;
    }
    long long res = 1;
    for(int b : bit){
        res *= power[b];
        
        res%=m;
    }
    return res;
}
long long modinv(long long x, long long m){
    x = (x%m+m)%m;
    return modpow(x,m-2,m);
}
long long moddiv(long long a , long long b , long long m){
    a = (a%m+m)%m;
    return (a*modinv(b,m))%m;
}

/*
    O(k)アルゴリズム
*/
long long modcomb(long long n , long long k , long long M){
    long long res = 1;
    for(int N = n ; N > n-k ; N--){
        res *= moddiv(N,k-n+N,M);
        res %=M;
    }
    return res;
}

class ModComb{
    private:
    vector<long long> table;
    int Max;
    long long MOD;
    public:
    
    ModComb(long long MOD_ , int Max_ = 1000001){
        Max = Max_;
        MOD = MOD_;
       
        vector<long long>(Max , 1).swap(table); 
        table[0] = 1;
        for(int x = 1 ; x < Max ; x++){
            table[x] = (table[x-1]*x)%MOD;
        }
    }

    long long modcomb(int n , int k){
        long long res = 1;
        res*=table[n];
        res %=MOD;
        res = moddiv(res , table[n-k],MOD);
        res = moddiv(res ,table[k],MOD); 
        return res;
    }
   

};




int main(){
    ModComb M(MOD);
    while(true){
        long long n ,k;
        cout <<"input n & k ... if n is -1 , program will end" << endl; 
        cin >> n;
        if(n == -1)break;
        cin >> k;
        cout << "ModComb.modcomb(n,k) = ";
        if(n>=1000000){
            cout <<"large" << endl;
        }else{
            cout<<M.modcomb(n,k) << endl;
        }
        cout << "modcomb(n,k,MOD) = ";
        cout << modcomb(n,k,MOD) << endl;


    }
    
}