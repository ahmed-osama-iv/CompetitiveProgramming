/* AtCoder Regular Contest 083 (D - FT Robot) https://arc087.contest.atcoder.jp/tasks/arc087_b
*
* If number of turns that the robot made are:
* even --> he is walking on the x-axis now
* odd  --> he is walking on the y-axis now
*
* create dpx to know if it's possible to reach the required X-position
* create dpy to know if it's possible to reach the required Y-position
* If both are achievable then the answer is "Yes" else the answer is "No"
*
*/

#include <bits/stdc++.h>
#define F first
#define S second
#define SZ size()

using namespace std;
typedef long long ll;

int in(){int a; scanf("%d", &a); return a;}
ll inll(){ll a; scanf("%lld", &a); return a;}

//--------------------------------------------------

const int MAX = 8e3 + 5;
const int INF = 0x3f3f3f3f;

string s;
int X, Y;
vector <int> xsteps, ysteps;


int memx[MAX][MAX];

bool dpx(int i, int curX) {

    if(i == xsteps.SZ) return curX == X;
    int &res = memx[i][curX];
    if(res != -1) return res;
    res = 0;
    res = dpx(i+1, curX + xsteps[i]) || dpx(i+1, curX - xsteps[i]);
    return res;
}

int memy[MAX][MAX];

bool dpy(int i, int curY) {

    if(i == ysteps.SZ) return curY == Y;
    int &res = memy[i][curY];
    if(res != -1) return res;
    res = 0;
    res = dpy(i+1, curY + ysteps[i]) || dpy(i+1, curY - ysteps[i]);
    return res;
}


int main(){

    memset(memx, -1, sizeof memx);
    memset(memy, -1, sizeof memy);

    cin >> s;
    s = s + 'T';

    X = in(), Y = in();

    int steps = 0;
    int turns = 0;
    int xstart = 0;

    for(int i=0; i<s.SZ; i++){

        if(s[i] == 'F') steps++;

        else {

            if(turns == 0) {
                xstart = steps;
            }

            else if(steps > 0) {
                if(turns % 2 == 0) xsteps.push_back(steps);
                else ysteps.push_back(steps);
            }

            turns++;
            steps = 0;
        }
    }

    if(dpx(0, xstart) && dpy(0, 0)) printf("Yes\n");
    else printf("No\n");

}

