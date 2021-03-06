/*
 *  SRC: POJ 2983
 * PROB: Is the Information Reliable?
 * ALGO: SPFA
 * DATE: Apr 12, 2012
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cstring>
#include <queue>

using std::queue;

const int MAX_V = 1010;
const int MAX_E = 300010;

int dist[MAX_V];
int cnt[MAX_V];
bool vis[MAX_V];

struct Edge {
    int v, d;
    Edge *next;
};
Edge e_buf[MAX_E],
     *e_head[MAX_V],
     *e_tail = e_buf;

void add_edge(int u, int v, int d)
{
    *e_tail = (Edge){v, d, e_head[u]};
    e_head[u] = e_tail++;
}

bool spfa(int n, int src)
{
    memset(dist, 0x3f, sizeof(dist));
    memset(cnt, 0, sizeof(cnt));
    memset(vis, false, sizeof(vis));
    dist[src] = 0;

    queue<int> Q;
    Q.push(src);
    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();

        vis[u] = false;
        for (Edge *e = e_head[u]; e; e = e->next) {
            int v = e->v;
            int d = e->d;
            if (d + dist[u] < dist[v]) {
                cnt[v]++;
                if (cnt[v] >= n) return false;
                dist[v] = d + dist[u];
                if (!vis[v]) {
                    vis[v] = true;
                    Q.push(v);
                }
            }
        }
    }

    return true;
}

int main()
{
    int n, m;
    while (~scanf("%d%d", &n, &m)) {
        memset(e_head, 0, sizeof(e_head));
        memset(e_tail, 0, sizeof(e_tail));
        e_tail = e_buf;

        // some points may be isolate, so add a super source 0
        for (int i = 1; i <= n; i++) {
            add_edge(0, i, 0);
        }
        for (int i = 0; i < m; i++) {
            char c;
            int u, v;
            scanf(" %c%d%d", &c, &u, &v);
            if (c == 'P') {
                int x;
                scanf("%d", &x);
                add_edge(u, v, -x);
                add_edge(v, u, x);
            } else {
                add_edge(u, v, -1);
            }
        }

        // n points plus a super souce, the 0
        puts(spfa(n + 1, 0) ? "Reliable" : "Unreliable");
    }

    return 0;
}

