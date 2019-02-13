/*
  Greedy solution
  keep with you the element that you will use soon
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int in(){int a; scanf("%d", &a); return a;}
ll inll(){ll a; scanf("%lld", &a); return a;}

const ll MAX = 1e5 + 5;
const ll INF = 0x3f3f3f3f;


map <int, int> temp_next;
map <int, bool> added;

int nxt[MAX], a[MAX];//, prv[MAX], temp_prev[MAX];
set <int> mySet;
set < pair<int,int> > pq;


int main()
{

    int T = in();

    while(T--){

        mySet.clear();
        pq.clear();

        temp_next.clear();
        added.clear();

        int n = in(), k = in();
        for(int i=0; i<n; i++){
            a[i] = in();
        }

        for(int i=n-1; i>=0; i--){
            if(temp_next.find(a[i]) == temp_next.end()){
                nxt[i] = INF;
            }else{
                nxt[i] = temp_next[a[i]];
            }
            temp_next[a[i]] = i;
        }

        int ii = 0;
        while(ii < n && mySet.size() < k){
            mySet.insert(a[ii]);
            ii++;
        }

        for(int i=ii-1; i>=0; i--){
            if(!added[a[i]]){
                added[a[i]] = 1;
                pq.insert({nxt[i], a[i]});
            }
        }

        int cnt = mySet.size();

        for(int i=ii; i<n; i++){
            if(mySet.count(a[i])){
                auto x = pq.lower_bound({i, 0});
                pq.erase(x);
                pq.insert({nxt[i] , a[i]});
            }else{
                auto x = pq.end();
                x--;
                int t = (*x).second;

                pq.erase(x);
                pq.insert({nxt[i], a[i]});

                mySet.erase(t);
                mySet.insert(a[i]);

                cnt++;

            }

        }

        printf("%d\n", cnt);
    }

}

