#include <bits/stdc++.h>
using namespace std;
#define clr(a, x) memset(a, x, sizeof(a))
#define mp(x, y) make_pair(x, y)
#define pb(x) push_back(x)
#define X first
#define Y second
#define fastin                    \
    ios_base::sync_with_stdio(0); \
    cin.tie(0);
typedef long long ll;
typedef long double ld;
typedef pair<int, int> PII;
typedef vector<int> VI;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
const double eps = 1e-6;

const int N = 1005;
vector<int> G[N];
int dp[N];

void dfs(int u)
{
    dp[u] = 1;
    for (auto v : G[u])
    {
        dfs(v);
        dp[u] += dp[v];
    }
}

bool solve(int n)
{
    for (int i = 1; i <= n; i++)
    {
        if (G[i].size() == 0) continue;
        int cnt = 0;
        for (auto v : G[i])
            if (dp[v] == 1) cnt++;
        if (cnt < 3) return false;
    }
    return true;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("1.in", "r", stdin);
    freopen("1.out", "w", stdout);
#endif
    int n, fa;
    scanf("%d", &n);
    for (int i = 2; i <= n; i++)
    {
        scanf("%d", &fa);
        G[fa].pb(i);
    }
    clr(dp, 0);
    dfs(1);
    puts(solve(n) ? "Yes" : "No");
    return 0;
}
