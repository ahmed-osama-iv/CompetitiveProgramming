#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pll;

const int MOD = 1e9 + 7;
const int MAX = 1e5 + 5;

ll fac[MAX];



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

pll add(pll a, pll b){
    ll p1 = a.first;
    ll p2 = b.first;

    ll q1 = a.second;
    ll q2 = b.second;

    ll P = (p1 * q2 + p2 * q1);
    ll Q = q1 * q2;

    ll g = __gcd(P, Q);

    return make_pair(P / g % MOD, Q / g % MOD);
}


pll mul(pll a, pll b){
    ll g = __gcd(a.first * b.first, a.second * b.second);
    return make_pair(a.first * b.first / g % MOD, a.second * b.second / g % MOD);
}



int main() {

    //cout << 15 * __pow(64ll, MOD-2) % MOD;

    fac[0] = 1;
    for(int i=1; i<MAX; i++){
        fac[i] = fac[i-1] * i % MOD;
    }

    int T;
    scanf("%d", &T);

    while(T--){

        int n, m;
        scanf("%d %d", &n, &m);
        m = abs(m);

        if(m > n){
            puts("0");
            continue;
        }

        pll sum = make_pair(0, 1);

        for(int l = 0; 2*l + m <= n; l++){
            ll _4 = __pow(4ll, 2*l + m);
            ll _2 = __pow(2ll, n - 2*l - m);
            ll f = fac[l] * fac[m + l] % MOD * fac[n - 2*l - m] % MOD;

            ll q = _2 * _4 % MOD * f % MOD;

            sum = add(sum, make_pair(1,q));
        }

        sum = mul(sum, make_pair(fac[n], 1));

        ll g = __gcd(sum.first, sum.second);
        sum.first /= g;
        sum.second /= g;

        ll res = sum.first * __pow(sum.second, MOD-2) % MOD;
        printf("%lld\n", res);
    }
}
