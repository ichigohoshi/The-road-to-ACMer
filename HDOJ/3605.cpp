// Escape, HDU3605

/*Sample Input
1 1
1
1

2 2
1 0
1 0
1 1
*/

#include <bits/stdc++.h>
using namespace std;
#define clr(a,x) memset(a, x, sizeof(a))
#define mp(x,y) make_pair(x,y)
#define pb(x) push_back(x)
#define X first
#define Y second
#define fastin ios_base::sync_with_stdio(0);cin.tie(0);
typedef long long ll;
typedef long double ld;
typedef pair<int, int> PII;
typedef vector<int> VI;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
const double eps = 1e-6;

const int maxn = 1 << 11;

struct Edge
{
    int from, to, cap, flow;
    Edge(int u, int v, int c, int f): from(u), to(v), cap(c), flow(f) {}
};
struct EdmonsKarp           //时间复杂度O(v*E*E)
{
    int n, m;
    vector<Edge> edges;     //边数的两倍
    vector<int> G[maxn];    //邻接表，G[i][j]表示节点i的第j条边在e数组中的序号
    int a[maxn];            //起点到i的可改进量
    int p[maxn];            //最短路树上p的入弧编号
    void init(int n)
    {
        for (int i = 0; i < n; i++) G[i].clear();
        edges.clear();
    }
    void AddEdge(int from, int to, int cap)
    {
        edges.pb(Edge(from, to, cap, 0));
        edges.pb(Edge(to, from, 0, 0));  //反向弧
        m = edges.size();
        G[from].pb(m - 2);
        G[to].pb(m - 1);
    }
    int Maxflow(int s, int t)
    {
        int flow = 0;
        for (;;)
        {
            clr(a, 0);
            queue<int> q;
            q.push(s);
            a[s] = INF;
            while (!q.empty())
            {
                int x = q.front();
                q.pop();
                for (int i = 0; i < G[x].size(); i++)
                {
                    Edge& e = edges[G[x][i]];
                    if (!a[e.to] && e.cap > e.flow)
                    {
                        p[e.to] = G[x][i];
                        a[e.to] = min(a[x], e.cap - e.flow);
                        q.push(e.to);
                    }
                }
                if (a[t]) break;
            }
            if (!a[t]) break;
            for (int u = t; u != s; u = edges[p[u]].from)
            {
                edges[p[u]].flow += a[t];
                edges[p[u] ^ 1].flow -= a[t];
            }
            flow += a[t];
        }
        return flow;
    }
} csl;

int cnt[maxn];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("1.in", "r", stdin);
    freopen("1.out", "w", stdout);
#endif
    int n, m, tmp;
    while (~scanf("%d%d", &n, &m))
    {
        csl.init(1036);
        int s = 1034, t = 1035;
        clr(cnt, 0);
        for (int i = 0; i < n; i++)
        {
            int x = 0;
            for (int j = 0; j < m; j++)
            {
                scanf("%d", &tmp);
                x = (x << 1) | tmp;
            }
            cnt[x]++;
        }
        for (int i = 0; i < (1 << 10); i++)
        {
            if (cnt[i])
                csl.AddEdge(s, i, cnt[i]);
            for (int j = 0; j < m; j++)
                if ((i >> j) & 1)
                    csl.AddEdge(i, (1 << 10) + j, INF);
        }
        for (int i = 0; i < m; i++)
        {
            scanf("%d", &tmp);
            csl.AddEdge((1 << 10) + i, t, tmp);
        }
        puts(csl.Maxflow(s, t) == n ? "YES" : "NO");
    }
    return 0;
}
