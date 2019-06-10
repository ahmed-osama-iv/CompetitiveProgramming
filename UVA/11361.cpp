#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int in(){int a; scanf("%d", &a); return a;}
ll inll(){ll a; scanf("%lld", &a); return a;}

const int MAX = 1e5 + 5;
const int MOD = 1e9 + 7;

int memo1[100][11][2][10004];
int memo2[100][11][2][10004];

int A, B, K;

int digit(int A, int idx){
    return (int)(A / pow(10, 9 - idx)) % 10;
}

int dp1(int sum, int idx, bool isSmaller, int mod = 0){

    if(sum < 0) return 0;
    if(sum == 0 && idx == 10 && mod == 0) return 1;
    if(idx == 10) return 0;

    int &res = memo1[sum][idx][isSmaller][mod];

    if(res != -1) return res;

    res = 0;

    if(isSmaller){
        for(int i=0; i<=9; i++){
            res += dp1(sum-i, idx+1, 1, (10*mod+i) % K);
        }
    }else{
        for(int i=0; i <= digit(B, idx); i++){
            res += dp1(sum-i, idx+1, i < digit(B, idx), (10*mod+i) % K);
        }
    }

    return res;
}

int dp2(int sum, int idx, bool isSmaller, int mod = 0){

    if(sum < 0) return 0;
    if(sum == 0 && idx == 10 && mod == 0) return 1;
    if(idx == 10) return 0;

    int &res = memo2[sum][idx][isSmaller][mod];

    if(res != -1) return res;

    res = 0;

    if(isSmaller){
        for(int i=0; i<=9; i++){
            res += dp2(sum-i, idx+1, 1, (10*mod+i) % K);
        }
    }else{
        for(int i=0; i <= digit(A, idx); i++){
            res += dp2(sum-i, idx+1, i < digit(A, idx), (10*mod+i) % K);
        }
    }

    return res;
}

int main()
{

    int T = in();
    while(T--){
        memset(memo1, -1, sizeof memo1);
        memset(memo2, -1, sizeof memo2);

        A = in() - 1, B = in(), K = in();
        
        int res = 0;
        for(int sum = K; sum <= 90; sum += K){
            res += dp1(sum, 0, 0) - dp2(sum, 0, 0);
        }

        printf("%d\n", res);
    }

}

