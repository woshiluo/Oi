#include <bits/stdc++.h>
#include <cstdint>
using i64 = int64_t;
using u32 = uint32_t;
using u64 = uint64_t;

inline bool isdigit( const char cur ) { return cur >= '0' && cur <= '9'; }/*{{{*/
template <class T> 
T Max( T a, T b ) { return a > b? a: b; }
template <class T> 
T Min( T a, T b ) { return a < b? a: b; }
template <class T> 
void chk_Max( T &a, T b ) { if( b > a ) a = b; }
template <class T> 
void chk_Min( T &a, T b ) { if( b < a ) a = b; }
template <typename T>
T read() { 
	T sum = 0, fl = 1; 
	char ch = getchar();
	for (; isdigit(ch) == 0; ch = getchar())
		if (ch == '-') fl = -1;
	for (; isdigit(ch); ch = getchar()) sum = sum * 10 + ch - '0';
	return sum * fl;
}
template <class T> 
T pow( T a, int p ) {
	T res = 1;
	while( p ) {
		if( p & 1 ) 
			res = res * a;
		a = a * a;
		p >>= 1;
	}
	return res;
}/*}}}*/

namespace Flow {/*{{{*/
	int S, T;
	void Set(int _S, int _T) { S = _S, T = _T; }
	struct Edge_t {
		int v, nxt, w, cost;
		Edge_t(int V = 0, int Nxt = 0, int W = 0, int Cost = 0) {
			v = V, nxt = Nxt, w = W, cost = Cost;
		}
	};
	std::vector<Edge_t> e(2);
	std::vector<int16_t> head;
	void add(int16_t u, int16_t v, int w, int cost) {
		if (u >= (int)head.size()) {
			head.resize(u + 127);
		}
		e.emplace_back(v, head[u], w, cost);
		head[u] = (int)e.size() - 1;
	}
	void addedge(int16_t u, int16_t v, int w, int cost) {
		add(u, v, w, cost);
		add(v, u, 0, -cost);
	}
	constexpr int inf = 1e9;
	std::queue<int> q;
	std::vector<int16_t> dep;
	std::vector<int16_t> cur;
	std::vector<bool> inq;
	bool bfs() {
		dep.assign(head.size(), head.size());
		inq.assign(head.size(), false);
		cur = head;
		q.emplace(S), dep[S] = 0;
		while (!q.empty()) {
			int u = q.front(); q.pop(); inq[u] = false;
			for (int i = head[u]; i; i = e[i].nxt) {
				int v = e[i].v;
				if (e[i].w && dep[v] > dep[u] + e[i].cost) {
					dep[v] = dep[u] + e[i].cost;
					if (!inq[v]) {
						inq[v] = true;
						q.emplace(v);
					}
				}
			}
		}
		return (u32)dep[T] < head.size();
	}
	int dfs(int u, int flow) {
		if (!flow) {
			return 0;
		} else if (u == T) {
			return flow;
		} else {
			inq[u] = true;
			int f = 0;
			for (int16_t &i = cur[u], rf; i; i = e[i].nxt) {
				int v = e[i].v;
				if (!inq[v] && dep[v] == dep[u] + e[i].cost && (rf = dfs(v, std::min(flow, e[i].w)))) {
					flow -= rf, f += rf;
					e[i].w -= rf, e[i ^ 1].w += rf;
					if (flow == 0) {
						return f;
					}
				}
			}
			return f;
		}
	}
	std::pair<int, int> dinic() {
		int ans = 0, res = 0;
		while (bfs()) {
			int tmp = dfs(S, inf);
			ans += tmp;
			res += dep[T] * tmp;
		}
		return std::make_pair(ans, res);
	}
}/*}}}*/
 
int main() {
#ifdef woshiluo
	freopen( "h.in", "r", stdin );
	freopen( "h.out", "w", stdout );
#endif
	using namespace std;
	const int n = read<int>();
	int S = n * 2, T = n * 2 + 1;
	Flow::Set(S, T);
	std::vector<vector<int>> a(n, vector<int>(n, 0));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			a[i][j] = read<int>();
		}
	}
	for (int i = 0; i < n; i += 2) {
    Flow::addedge(S, i, 1, 0);
    Flow::addedge(i + n, T, 1, 0);
  }
  for (int i = 0; i < n; i += 2) {
    for (int j = 0; j < n; j += 2) {
      int l = j - 1;
      int r = j + 1;
      int v = 0;
      if (l >= 0) {
        v += a[i][l];
      }
      if (r < n) {
        v += a[i][r];
      }
      Flow::addedge(i, j + n, 1, v);
    }
  }
  auto tmp = Flow::dinic();
  // std::cout << tmp.first << " " << tmp.second << std::endl;
  // cout << tmp.second << "\n";
  printf( "%d\n", tmp.second );
  return 0;
}

