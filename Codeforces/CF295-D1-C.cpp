#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int in(){int a; scanf("%d", &a); return a;}
ll inll(){ll a; scanf("%lld", &a); return a;}

const int MAX = 1e5 + 5;
const int MOD = 1e9 + 7;

ll comb[52][52];

int memo[51][51][2];
ll  memo2[51][51][2];

int N, M, K, steps;

void dp(){

    for(int i=0; i<51; i++)
        for(int j=0; j<51; j++)
            memo[i][j][0] = memo[i][j][1] = MAX;

    queue <vector<int> > q;
    memo[0][0][0] = 0;
    q.push({0,0,0});

    while(!q.empty()){
        vector <int> t = q.front(); q.pop();
        int x = t[0], y = t[1], left = t[2];
        if(left){  //left
            for(int i=0; i<=x; i++){
                for(int j=0; j<=y; j++){
                    if(i + j != 0 && 50*i + 100*j <= K && memo[x-i][y-j][0] == MAX){
                        memo[x-i][y-j][0] = memo[x][y][1] + 1;
                        q.push({x-i, y-j, 0});
                    }
                }
            }
        }else{  //right
            for(int i=0; i<=N-x; i++){
                for(int j=0; j<=M-y; j++){
                    if(i + j != 0 && 50*i + 100*j <= K && memo[x+i][y+j][1] == MAX){
                        memo[x+i][y+j][1] = memo[x][y][0] + 1;
                        q.push({x+i, y+j, 1});
                    }
                }
            }
        }
    }

}

int dp2(int n, int m, bool left, int depth){

    ll &res = memo2[n][m][left];
    if(res != -1) return res;
    if(n + m == 0) return 1;

    res = 0;

    if(left){
        for(int i=0; i<=n; i++){
            for(int j=0; j<=m; j++){
                if(i + j != 0 && 50*i + 100*j <= K){
                    if(depth + memo[n-i][m-j][0] == steps){
                        res += comb[n][i] * comb[m][j] % MOD * dp2(n-i, m-j, 0, depth+1) % MOD ;
                        res %= MOD;
                    }
                }
            }
        }

    }else{

        for(int i=0; i<=N-n; i++){
            for(int j=0; j<=M-m; j++){
                if(i + j != 0 && 50*i + 100*j <= K){
                    if(depth + memo[n+i][m+j][1] == steps){
                        res += comb[N-n][i] * comb[M-m][j] % MOD * dp2(n+i, m+j, 1, depth+1) % MOD ;
                        res %= MOD;
                    }
                }
            }
        }
    }

    return res;

}

void build_comb(){

    comb[0][0] = 1;

    for(int i=1; i<52; i++){
        comb[i][0] = 1;
        for(int j=1; j<=i; j++){
            comb[i][j] = comb[i-1][j] + comb[i-1][j-1];
            comb[i][j] %= MOD;
        }
    }
}


int main()
{

    int n = in();
    K = in();

    for(int i=0; i<n; i++){
        if(in() == 50) N++;
        else M++;
    }

    build_comb();

    dp();
    steps = memo[N][M][1];

    memset(memo2, -1, sizeof memo2);

    if(steps >= MAX){
        cout << -1 << endl;
        cout << 0 << endl;
    }else{
        cout << steps << endl;
        cout << dp2(N, M, 1, 1) << endl;
    }
}

