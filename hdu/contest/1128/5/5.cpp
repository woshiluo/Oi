/*
 * 5.cpp 2024-08-03
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

#include <stack>
#include <vector>
#include <iostream>
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
	for (; isdigit(ch); ch = getchar()) sum = sum * 10 + ch - '0';
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

const int N = 1e6 + 5;

struct Set {
	int set[N];
	void init( ci32 n ) { for( int i = 0; i <= n; i ++ ) set[i] = i; }
	int get_fa( ci32 cur ) {
		if( set[cur] == cur )
			return cur;
		set[cur] = get_fa( set[cur] );
		return set[cur];
	}
	int& operator[]( const int cur ) { 
		return set[ get_fa(cur) ];
	}
} set;

struct Edge {
	i32 to, next;
} e[ N << 1 ];
int ehead[N], ecnt;
void add_edge( ci32 from, ci32 to ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[from];
	ehead[from] = ecnt;
}

int dep[N], fa[N];
void dfs( ci32 cur, ci32 la ) {
	dep[cur] = dep[la] + 1;
	fa[cur] = la;
	for( int i = ehead[cur]; i; i = e[i].next ) {
		ci32 to = e[i].to;
		if( to == la ) 
			continue;
		dfs( to, cur );
	}
}

int res[N];
std::pair<i32, i32> edges[N];

int main() {
#ifdef woshiluo
	freopen( "5.in", "r", stdin );
	freopen( "5.out", "w", stdout );
#endif

	std::ios::sync_with_stdio(false); std::cin.tie(0); std::cout.tie(0);
	int T;
	std::cin >> T;
	while( T -- ) {
		i32 n;
		std::cin >> n;
		ecnt = 0;
		memset( ehead, 0, sizeof(ehead[0]) * ( n + 2 ) );
		for( int i = 1; i < n; i ++ ) {
			i32 u, v;
			std::cin >> u >> v;
			add_edge( u, v );
			add_edge( v, u );

			edges[i] = std::make_pair( u, v );
		}
		
		dfs( 1, 0 );

		set.init(n);

		for( int d = n; d >= 1; d -- ) {
			std::stack<i32> list;
			for( int i = d; i <= n; i += d ) {
				list.push(i);
			}

			if( list.size() <= 1 ) 
				continue;

			ci32 size = list.size();
			for( int i = 1; i < size; i ++ ) {
				i32 u = list.top(); list.pop();
				i32 v = list.top(); list.pop();

				while( set[u] != set[v] ) {
					if( dep[ set[u] ] < dep[ set[v] ] ) 
						std::swap( u, v );
					ci32 fu = set[u];
					res[fu] = d;
					set[fu] = set[ fa[fu] ];
					u = fa[fu];
				}

				list.push(u);
			}
		}

		for( int i = 1; i < n; i ++ ) {
			auto [u,v] = edges[i];
			if( dep[u] < dep[v] )
				std::swap( u, v );
			std::cout << res[u] << " ";
		}
		std::cout << "\n";
	}

}
