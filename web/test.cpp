#include<iostream>
#include<vector>

/*
    のこのこくんはN個の魔法のステッキを持っている。
    i番目のステッキを使うと、x[i]メートルだけ前に飛べる。
    ステッキは何度でも使える。
    ちょうどyメートル前に飛べるか.
    n <= 100
    x[i] <= 1000
    Y <= 10000
*/

int N , Y;
int x[1001];


int main(){

    std::cin >> N >> Y;
    for(int i = 0 ; i < N ; i++){
        std::cin>> x[i];
    }
    std::vector<long long > dp(Y+1,0);
    dp[0] = 1;
    for(int i = 0 ; i < N ; i++){
        for(int X = 0; X<=Y;X++){
            if(X - x[i] >= 0 && dp[X-x[i]]){
                dp[X] = 1;
            }
        }
    }
    
    if(dp[Y]){
        printf("Yes\n");
    }else{
        printf("No\n");
    }
    
    


    return 0;
}

