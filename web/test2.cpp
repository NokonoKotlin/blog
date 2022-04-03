//include
//------------------------------------------
#include <vector>
#include<iostream>
#include<string>
using namespace std;

//modpow : O(logN) 
long long modpow(long long a, long long n, long long mod) {
    long long res = 1;
    while (n > 0) {
        if (n & 1) res = res * a % mod;
        a = a * a % mod;
        n >>= 1;
    }
    return res;
}


long long  MOD = 998244353;

int main(){
    long long n , l;
    cin >> n >> l;

    vector<string> s(n);
    for(int i = 0 ; i < n ; i++)cin >> s[i];


    long long ans = 0;
    for(int t = 1; t < (1ll<<n) ; t++){
        long long  bitsum = 0;
        for(int bit = 0 ; bit < n ; bit++ ){
            if(t&(1ll<<bit))bitsum++;
        }
        long long sign = 1;
        if(bitsum%2==0)sign = -1;
        vector<int> use(26,1);
        for(int bit = 0 ; bit < n ; bit++ ){
            if(t&(1ll<<bit)){
                vector<int> memo(26,0);
                for(char c: s[bit]){
                    memo[c-'a']=1;
                }
                for(int c = 0 ;c < 26 ; c++){
                    if(memo[c]==0)use[c] = 0;
                }
            }

        }
        
        long long sum = 0;
        for(int x : use)sum+=x;
        ans += sign*modpow(sum,l,MOD);

    }

    cout << (ans%MOD+MOD)%MOD << endl;

    return 0;
}