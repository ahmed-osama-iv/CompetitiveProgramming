/*

use the destroyed towers in reversed order as intermediate nodes in floyd
to construct all pairs shortes path graphs step by step for every node

*/


#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int in(){int a; scanf("%d", &a); return a;}

const int MAX = 505;
const int INF = 0x3f3f3f3f;

int w[MAX][MAX];
int d[MAX][MAX];
bool added[MAX];
stack <int> stk;

void add(int k){
    for(int i=0; i<MAX; i++){
        if(added[i]){
            d[k][i] = w[k][i];
            d[i][k] = w[i][k];
        }
    }

    added[k] = 1;
}

int main()
{

    int T = in();

    while(T--){
        int n = in();
        memset(d, INF, sizeof d);
        memset(added, 0, sizeof added);

        for(int i=0; i<MAX; i++) d[i][i] = 0;

        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                w[i][j] = in();
            }
        }

        for(int i=0; i<n; i++){
            stk.push(in());
        }

        ll sum = 0;

        int u = stk.top(); stk.pop();
        added[u] = 1;

        while(!stk.empty()){
            int v = stk.top(); stk.pop();
            add(v);

            for(int k=0; k<n; k++){
                for(int i=0; i<n; i++){
                    d[i][v] = min(d[i][v] , d[i][k] + d[k][v]);
                }
            }

            for(int k=0; k<n; k++){
                for(int i=0; i<n; i++){
                    d[v][i] = min(d[v][i] , d[v][k] + d[k][i]);
                }
            }

            for(int i=0; i<n; i++){
                for(int j=0; j<n; j++){
                    d[i][j] = min(d[i][j], d[i][v] + d[v][j]);
                    if(added[i] && added[j])sum += d[i][j];
                }
            }
        }

        printf("%lld\n", sum);
    }

}

