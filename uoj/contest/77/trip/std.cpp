// This Code was made by Chinese_zjc_.
#include <bits/stdc++.h>
int n, m, k, u[200005], v[200005], w[200005], d[21];
long long dis[21][100005], ans = LLONG_MAX;
std::vector<int> to[100005];
void dij(long long *dis, int S)
{
    std::fill(dis + 1, dis + 1 + n, LLONG_MAX / 2);
    std::priority_queue<std::pair<long long, int>> que;
    que.push({dis[S] = 0, S});
    while (!que.empty())
    {
        std::pair<long long, int> now = que.top();
        que.pop();
        if (now.first + dis[now.second])
            continue;
        for (auto i : to[now.second])
        {
            int t = u[i] ^ v[i] ^ now.second;
            if (dis[t] > dis[now.second] + w[i])
                que.push({-(dis[t] = dis[now.second] + w[i]), t});
        }
    }
}
long long get(long long A, long long B, int len)
{
    if (A > B)
        std::swap(A, B);
    return A + len < B ? B << 1 : A + B + len;
}
signed main()
{
	freopen( "trip.in", "r", stdin );
	freopen( "trip.ans", "w", stdout );
    std::ios::sync_with_stdio(false);
    std::cin >> n >> m;
    for (int i = 1; i <= m; ++i)
    {
        std::cin >> u[i] >> v[i] >> w[i];
        to[u[i]].push_back(i);
        to[v[i]].push_back(i);
    }
    std::cin >> k;
    d[0] = 1;
    for (int i = 1; i <= k; ++i)
        std::cin >> d[i];
    for (int i = 0; i <= k; ++i)
        dij(dis[i], d[i]);
    for (int i = 1; i <= m; ++i)
    {
        std::priority_queue<std::pair<long long, long long>> que;
        for (int j = 0; j <= k; ++j)
            que.push({dis[j][u[i]], dis[j][v[i]]});
        long long R = 0;
        ans = std::min(ans, que.top().first << 1);
        while (!que.empty())
        {
            R = std::max(R, que.top().second);
            que.pop();
            if (que.empty())
                ans = std::min(ans, R << 1);
            else
                ans = std::min(ans, get(que.top().first, R, w[i]));
        }
    }
    std::cout << ans << std::endl;
    return 0;
}

