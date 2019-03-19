/*

  let w[i][j][p] = shortest path using exactly 2^p edges from node i to node j
  
  we compute the answer using something like digit dp on K
  
  res[i][j][idx][0] is the min cost from node i to node j using exactly M edges.
  res[i][j][idx][1] is the min cost from node i to node j using strictly more than M edges.
  such that M is : K after converting the least significant (idx) bits to zeros
  
  for example let K = 11010101 (in base 2), idx = 4
  then, M = 11010000 (in base 2)
  
  so the final answer from node i to node j = min(res[i][j][0][0] , res[i][j][0][1])
  
  Thanks to OmarHashim, his solution helped my so much
  https://github.com/OmarHashim/Competitive-Programming/blob/master/SPOJ/PLHOP.cpp
  
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int in(){int a; scanf("%d", &a); return a;}
ll inll(){ll a; scanf("%lld", &a); return a;}

const int LOG = 32;
const ll MAX = 55;
const ll INF = 1e18;

ll w[MAX][MAX][LOG], res[MAX][MAX][LOG][2];

void init(){

    for(int i=0; i<MAX; i++){
        for(int j=0; j<MAX; j++){
            for(int k=0; k<LOG; k++) w[i][j][k] = res[i][j][k][0] = res[i][j][k][1] = INF;
        }
    }
}


int main()
{

  int T = in();
   for(int t=1; t<=T; t++){

        init();

        int K = in(), n = in();

        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                w[i][j][0] = in();
            }
        }

        for(int p=1; p<LOG; p++){
            for(int k=0; k<n; k++){
                for(int i=0; i<n; i++){
                    for(int j=0; j<n; j++){

                        w[i][j][p] = min(w[i][j][p] , w[i][k][p-1] + w[k][j][p-1]);

                    }
                }
            }
        }


        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){

                if(i==j) res[i][j][LOG-1][0] = 0;
                else res[i][j][LOG-1][1] = w[i][j][LOG-1];

            }
        }

        for(int idx=LOG-2; idx>=0; idx--){
            for(int i=0; i<n; i++){
                for(int j=0; j<n; j++){

                    if(K & (1<<idx)){
                        for(int k=0;  k<n; k++){
                            res[i][j][idx][0] = min(res[i][j][idx][0], res[i][k][idx+1][0] + w[k][j][idx]);
                        }

                        res[i][j][idx][1] = res[i][j][idx+1][1];
                    }

                    else{

                        res[i][j][idx][0] = res[i][j][idx+1][0];

                        for(int k=0; k<n; k++){
                            res[i][j][idx][1] = min(res[i][j][idx][1], res[i][k][idx+1][0] + w[k][j][idx]);
                        }

                        res[i][j][idx][1] = min(res[i][j][idx][1], res[i][j][idx+1][1]);
                    }

                }
            }
        }

        printf("Region #%d:\n", t);
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                printf("%lld", min(res[i][j][0][0],res[i][j][0][1]) );
                if(j != n-1) printf(" ");
            }
            puts("");
        }

        puts("");
    }

}



