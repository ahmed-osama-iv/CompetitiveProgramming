#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int in(){int a; scanf("%d", &a); return a;}
ll inll(){ll a; scanf("%lld", &a); return a;}

const ll MOD = 1000000007;
const int MAX = 2e5 + 5;

ll factorial[MAX];

ll __pow(ll base, ll power, ll mod=MOD){
    base %= mod;
    ll result = 1;
    while(power > 0) {

        if(power & 1){ // power % 2 == 1
            result = (result*base) % mod;
        }
        base = (base * base) % mod;
        power >>= 1; // power = power / 2;
    }
    return result;
}

ll ncr(int n, int r){
    if(n < 0 || r < 0 || n-r < 0) return 0;
    return factorial[n] * __pow(factorial[r] * factorial[n-r], MOD-2) % MOD;
}

int main()
{


    factorial[0] = 1;
    for(int i=1; i<MAX; i++){
        factorial[i] = factorial[i-1] * i % MOD;
    }
    string s;
    cin >> s;

    int x = 0, y = 0;

    for(char c : s){
        if(c == ')') y++;
    }

    ll sum = 0;

    for(char c : s){
        if(c == '('){
            x++;
            sum += ncr(x+y-1, x);
            sum %= MOD;
        }else{
            y--;
        }
    }

    printf("%lld\n", sum);
}
