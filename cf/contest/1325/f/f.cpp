// Woshiluo Luo<woshiluo@woshiluo.site>  
// 2020/03/15 15:49:32 
#include <cstdio>
#include <cstring>

#include <stack>
#include <algorithm>

template<class T>
T Min( T _a, T _b ) { return _a < _b? _a: _b; }
template<class T>
T Max( T _a, T _b ) { return _a > _b? _a: _b; }
template<class T>
T chk_Min( T &_a, T _b ) { return _a = (_a < _b? _a: _b); }
template<class T>
T chk_Max( T &_a, T _b ) { return _a = (_a > _b? _a: _b); }

const int N = 1e5 + 1e4;
const int M = 2e5 + 1e4;

int n, m, need;

int dep[N];
bool vis[N];
std::stack<int> st;

// Edge Start
struct edge { int to, next; } e[ M << 1 ];
int ehead[N], ecnt;
inline void add_edge( int now, int to ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[now];
	ehead[now] = ecnt;
}
// Edge End


void dfs( int now ) {
	st.push(now);
	dep[now] = st.size();
	for( int i = ehead[now]; i; i = e[i].next ) {
		if( dep[ e[i].to ] == 0 ) 
			dfs( e[i].to );
		else if( dep[now] - dep[ e[i].to ] + 1 >= need ) {
			int size = dep[now] - dep[ e[i].to ] + 1;
			printf( "%d\n%d\n", 2, size );
			for( int i = 1; i <= size; i ++ ) {
				printf( "%d ", st.top() );
				st.pop();
			}
			exit(0);
		}
	}
	if( !vis[now] ) {
		for( int i = ehead[now]; i; i = e[i].next ) {
			vis[ e[i].to ] = true;
		}
	}
	st.pop();
}

int main() {
#ifdef woshiluo
	freopen( "f.in", "r", stdin );
	freopen( "f.out", "w", stdout );
#endif
	scanf( "%d%d", &n, &m );
	while( need * need < n ) 
		need ++;

	while( m -- ) {
		int u, v;
		scanf( "%d%d", &u, &v );
		add_edge( u, v ); add_edge( v, u );
	}

	dfs(1);

	printf( "%d\n", 1 );
	int cnt = 0;
	for( int i = 1; i <= n; i ++ ) {
		if( vis[i] == false ) {
			printf( "%d ", i );
			cnt ++;
		}
		if( cnt == need ) 
			break;
	}
}
