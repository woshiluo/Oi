/*
 * b.cpp 2024-07-18
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

#include <map>
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
T pow( T a, i32 p ) {
	T res = 1;
	while( p ) {
		if( p & 1 ) 
			res = res * a;
		a = a * a;
		p >>= 1;
	}
	return res;
}/*}}}*/

const int N = 1e5 + 1e4;

const int INF = 0x3f3f3f3f;

const int BASE = 128;

struct RawEdge { int from, to, val; };

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

bool vis[N];
std::map<std::pair<i32, i32>, i32> mp;

int main() {
#ifdef woshiluo
	freopen( "b.in", "r", stdin );
	freopen( "b.out", "w", stdout );
#endif

	ci32 n = read<i32>();
	ci32 m = read<i32>();
	ci32 q = read<i32>();

	std::vector<RawEdge> edges;
	for( int i = 1; i <= m; i ++ ) {
		i32 u = read<i32>();
		i32 v = read<i32>();
		ci32 w = read<i32>();

		edges.push_back( (RawEdge) { u, v, w } );

		const auto e1 = std::make_pair( u, v );
		const auto e2 = std::make_pair( v, u );

		if( mp.count(e1) ) 
			chk_Min( mp[e1], w );
		else
			mp[e1] = w;

		if( mp.count(e2) ) 
			chk_Min( mp[e2], w );
		else
			mp[e2] = w;
	}
	std::sort( edges.begin(), edges.end(), [&]( const auto &_a, const auto &_b ) { return _a.val < _b.val; } );

	for( int _ = 1; _ <= q; _ ++ ) {
		const int k = read<i32>();
		std::vector<i32> list(k);
		for( auto &x: list ) {
			x = read<i32>();
		}
		if( k >= BASE ) {
			for( auto &x: list ) {
				vis[x] = true;
			}
			set.init(n);
			i32 cnt = 0;
			i64 res = 0;
			for( auto &[ u, v, w ]: edges ) {
				if( !vis[u] || !vis[v] ) 
					continue;
				if( set[u] == set[v] ) 
					continue;
				set[u] = set[v];
				cnt ++;
				res += w;
			}
			for( auto &x: list )
				vis[x] = false;
			if( cnt == k - 1 ) 
				printf( "%lld\n", res );
			else
				printf( "-1\n" );

			continue;
		}
		else {
			// set.init(n);
			i32 cnt = 0;
			i64 res = 0;
			std::vector<i32> curv, points( k + 1, INF );
			curv.push_back( list[0] );
			points[0] = 0;
			for( int i = 0; i < k; i ++ ) {
				vis[ curv[i] ] = true;
				for( int j = 0; j < k; j ++ ) {
					if( vis[ list[j] ] ) 
						continue;
					auto nxt = std::make_pair( curv[i], list[j] );
					if( mp.count(nxt) ) 
						chk_Min( points[j], mp[nxt] );
				}
				i32 min = -1;
				for( int j = 0; j < k; j ++ ) {
					if( vis[ list[j] ] ) 
						continue;
					if( min == -1 && points[j] != INF ) {
						min = j;
					}
					if( min != -1 && points[j] < points[min] ) 
						min = j;
				}
				if( min == -1 ) 
					break;

				cnt ++;
				res += points[min];
				curv.push_back( list[min] );
			}
		
			for( auto &x: list ) {
				vis[x] = false;
			}

			if( cnt == k - 1 ) {
				printf( "%lld\n", res );
			}
			else
				printf( "-1\n" );

			continue;
		}
	}
}
