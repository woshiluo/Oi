// Woshiluo Luo<woshiluo@woshiluo.site>  
// 2020/03/15 22:08:53 

#include <cmath>
#include <cstdio>
#include <cstring>

#include <queue>
#include <vector>
#include <algorithm>

template<class T>
T Min( T _a, T _b ) { return _a < _b? _a: _b; }
template<class T>
T Max( T _a, T _b ) { return _a > _b? _a: _b; }
template<class T>
T chk_Min( T &_a, T _b ) { return _a = (_a < _b? _a: _b); }
template<class T>
T chk_Max( T &_a, T _b ) { return _a = (_a > _b? _a: _b); }

const int N = 1e6 + 1e4;
const int M = 1100;
const int INF = 0x3f3f3f3f;

int n, ans = INF;
int dis[N], fa[N];
bool marked[N], pool[N];

// Edge Start 
struct edge {
	int cur, to, next;
} e[ N << 1 ];
int ehead[N], ecnt = 1;
inline void add_edge( int now, int to ) {
	ecnt ++;
	e[ecnt].cur = now;
	e[ecnt].to = to;
	e[ecnt].next = ehead[now];
	ehead[now] = ecnt;
}
// Edge End

int bfs( int st ) {
	memset( dis, INF, sizeof(dis) );
	memset( fa, 0, sizeof(fa) );
	std::queue<int> q;
	q.push(st); dis[st] = 0; 
	while( !q.empty() ) {
		int cur = q.front(); q.pop();
		for( int i = ehead[cur]; i; i = e[i].next ) {
			if( e[i].to == fa[cur] ) 
				continue;

			if( dis[ e[i].to ] >= INF ) {
				fa[ e[i].to ] = cur;
				dis[ e[i].to ] = dis[cur] + 1;
				q.push( e[i].to );
			}
			else {
				return dis[cur] + dis[ e[i].to ] + 1;
			}
		}
	}
	return INF;
}

int main() {
#ifdef woshiluo
	freopen( "e.in", "r", stdin );
	freopen( "e.out", "w", stdout );
#endif
	scanf( "%d", &n );
	for( int i = 1, x; i <= n; i ++ ) {
		scanf( "%d", &x );
		std::vector<int> a;
		int cnt = std::sqrt(x) + 1;
		while(cnt > 1) {
			int cnt_pow = cnt * cnt;
			while( x % cnt_pow == 0 ) 
				x /= cnt_pow;
			cnt --;
		}
		if( x == 1 )
			chk_Min( ans, 1 );
		if( pool[x] ) 
			chk_Min( ans, 2 );
		pool[x] = true;
		int tmp = std::sqrt(x);
		for( int j = 2; j <= tmp; j ++ ) {
			if( x % j == 0 ) {
				a.push_back(j);
				a.push_back( x / j );
				break;
			}
		}
		if( a.size() == 0 ) {
			add_edge( 1, x );
			add_edge( x, 1 );
		}
		else if( a.size() != 0 ) {
			add_edge( a[0], a[1] );
			add_edge( a[1], a[0] );
		}
	}

	if( ans != INF ) {
		printf( "%d\n", ans );
		return 0;
	}
	
	for( int i = 1; i <= 1000; i ++ ) {
		if( ehead[i] )
			chk_Min( ans, bfs(i) );
	}
	
	if( ans >= INF ) 
		ans = -1;

	printf( "%d\n", ans );
}
