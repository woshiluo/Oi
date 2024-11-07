/*
 * k.cpp 2024-11-06
 * Copyright (C) 2024 Woshiluo Luo <woshiluo.luo@outlook.com>
 *
 * 「Two roads diverged in a wood,and I—
 * I took the one less traveled by,
 * And that has made all the difference.」
 *
 * Distributed under terms of the GNU GNU AGPLv3+ license.
 */

#include <cstdio>
#include <cstdint>
#include <cstring>
#include <cstdlib>

#include <queue>
#include <vector>
#include <algorithm>

using i32 = int32_t;
using u32 = uint32_t;
using ci32 = const int32_t;
using cu32 = const uint32_t;

using i64 = int64_t;
using u64 = uint64_t;
using ci64 = const int64_t;
using cu64 = const uint64_t;

inline bool isdigit( const char cur ) { return cur >= '0' && cur <= '9'; }/*{{{*/
template <class T> 
constexpr T Max( T a, T b ) { return a > b? a: b; }
template <class T> 
constexpr T Min( T a, T b ) { return a < b? a: b; }
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
	for (; isdigit(ch); ch = getchar()) sum = sum * 10 + ( ch - '0' );
	return sum * fl;
}
template <class T> 
constexpr T pow( T a, i32 p ) {
	T res = 1;
	while( p ) {
		if( p & 1 ) 
			res = res * a;
		a = a * a;
		p >>= 1;
	}
	return res;
}/*}}}*/

const int N = 310 * 1000;

struct edge {
	double val;
	int next, to, flow;
} e[ N << 1 ];
int ehead[N], ecnt = 1;
inline void add_edge( int cur, int to, int flow, int val ) {
	ecnt ++;
	e[ecnt].val = val;
	e[ecnt].to = to;
	e[ecnt].next = ehead[cur];
	e[ecnt].flow = flow;
	ehead[cur] = ecnt;
}
// Edge End

const int INF = 0x3f3f3f3f;

i32 choosen_edge[N], pre[N], flow[N], dis[N];
bool spfa( ci32 st, ci32 ed, ci32 max_node ) {
	static bool vis[N];
	std::queue<int> q;
	memset( vis, 0, sizeof(vis[0]) * max_node );
	memset( dis, INF, sizeof(dis[0]) * max_node );
	memset( flow, INF, sizeof(flow[0]) * max_node );
	q.push(st); vis[st] = true; dis[st] = 0;
	while( !q.empty() ) {
		int cur = q.front(); q.pop();
		for( int i = ehead[cur]; i; i = e[i].next ) {
			if( e[i].flow && 
					dis[ e[i].to ] > dis[cur] + e[i].val ) {
				chk_Min( flow[cur], e[i].flow );
				chk_Min( flow[ e[i].to ], flow[cur] );
				dis[ e[i].to ] = dis[cur] + e[i].val;
				choosen_edge[ e[i].to ] = i; pre[ e[i].to ] = cur;
				if( ! vis[ e[i].to ] ) {
					vis[ e[i].to ] = true;
					q.push( e[i].to );
				}
			}
		}
		vis[cur] = false;
	}
	return dis[ed] != INF;
}

i32 mcmf( ci32 st, ci32 ed, ci32 max_node ) {
	i32 res = 0;
	while( spfa(st, ed, max_node) ) {
		res += flow[ed] * dis[ed];
		int cur = ed;
		while( cur != st ) {
			ci32 o = choosen_edge[cur];
			e[o].flow -= flow[ed];
			e[ o ^ 1 ].flow += flow[ed];
			cur = pre[cur];
		}
	}
	return res;
}

const int HALF = 4e4 + 1;

i32 cnt_half[HALF];

int main() {
#ifdef woshiluo
	freopen( "k.in", "r", stdin );
	freopen( "k.out", "w", stdout );
#endif

	ci32 n = read<i32>();
	std::vector<i32> a( n + 1 ), b, cnt_a( n + 1 );
	for( int i = 1; i <= n; i ++ ) {
		a[i] = read<i32>();
		for( int j = 1; 1LL * j * j <= a[i]; j ++ ) {
			if( a[i] % j == 0 ) {
				b.push_back(j);
				b.push_back( a[i] / j );
			}
		}
	}

	std::vector<i32> cnt_b( b.size() );

	for( int i = 1; i <= n; i ++ ) {
		i32 cur = a[i];
		for( int j = 2; 1LL * j * j <= a[i] && cur != 1; j ++ ) {
			while( cur % j == 0 ) {
				cur /= j;
				cnt_a[i] ++;
			}
		}
		if( cur != 1 ) 
			cnt_a[i] ++;
	}
	for( int i = 1; i < HALF; i ++ ) {
		i32 cur = i;
		for( int j = 2; 1LL * j * j <= i && cur != 1; j ++ ) {
			while( cur % j == 0 ) {
				cur /= j;
				cnt_half[i] ++;
			}
		}
		if( cur != 1 ) 
			cnt_half[i] ++;
	}

	const auto calc = [&]( ci32 ori, ci32 nxt ) {
		if( b[nxt] < a[ori] / b[nxt] ) {
			ci32 tot = cnt_a[ori];
			return tot - cnt_half[ b[nxt] ];
		}
		else {
			return cnt_half[ a[ori] / b[nxt] ];
		}
	};

	std::sort( b.begin(), b.end() );
	b.erase( std::unique( b.begin(), b.end() ), b.end() );
	ci32 size_a = n + 1;
	i32 size_b = b.size();
	for( int i = 1; i <= n; i ++ ) {
		for( int j = 0; j < size_b; j ++ ) {
			if( a[i] % b[j] == 0 ) {
				cnt_b[j] = cnt_a[i] - calc( i, j );
			}
		}
	}

	{
		std::vector<i32> list;
		for( int i = 0; i < size_b; i ++ ) 
			list.push_back(i);
		std::sort( list.begin(), list.end(), [&]( const auto &_a, const auto &_b ) { return cnt_b[_a] < cnt_b[_b]; } );
		std::vector<i32> nb;
		for( int i = 0; i < Min( size_b, 610 ); i ++ ) 
			nb.push_back( b[ list[i] ] );
		b = nb;
	}
	size_b = b.size();
	for( int i = 1; i <= n; i ++ ) {
		for( int j = 0; j < size_b; j ++ ) {
			if( a[i] % b[j] == 0 ) {
				add_edge( i, size_a + j, INF, -calc( i, j ) );
				add_edge( size_a + j, i, 0, calc( i, j ) );
			}
		}
	}
	for( int i = 1; i <= n; i ++ ) {
		add_edge( size_a + size_b + 1, i, 1, 0 );
		add_edge( i, size_a + size_b + 1, 0, 0 );
	}
	for( int i = 0; i < size_b; i ++ ) {
		add_edge( size_a + i, size_a + size_b + 2, 1, 0 );
		add_edge( size_a + size_b + 2, size_a + i, 0, 0 );
	}

	ci32 result = mcmf( size_a + size_b + 1, size_a + size_b + 2, size_a + size_b + 3 );

	printf( "%d\n", -result );

	return 0;
}
