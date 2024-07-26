/*
 * e1.cpp 2024-07-21
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

#include <random>
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

std::random_device seed;
std::mt19937 rnd(seed());

const int N = 8196;
const int MINTRY = 50;

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

i32 max[N], size[N], dep[N], fa[N], son[N];

int mole = 0, st_mole = 0;

int qcnt = 0;
int query( ci32 x ) {
	printf( "? %d\n", x );
	fflush(stdout);
	ci32 res = read<i32>();
	return res;
//	qcnt ++;
//	if( qcnt > 300 ) {
//		std::exit(-1);
//	}
//	i32 cur = mole;
//	while(1) {
//		if( cur == x ) 
//			return 1;
//		if( cur == 1 ) 
//			break;
//		cur = fa[cur];
//	}
//	mole = fa[mole];
//	return 0;
}

bool ans_flag = false;
void answer( ci32 x ) {
	ans_flag = true;
	if( x != mole ) {
		printf( "!!!: %d, st: %d\n\n", mole, st_mole );
		std::exit(-1);
	}
	printf( "! %d\n", x );
	fflush(stdout);
}

bool vis[N];

void dfs( ci32 cur, ci32 la ) {
	size[cur] = 1; fa[cur] = la;
	max[cur] = 1; dep[cur] = dep[la] + 1;
	son[cur] = 0;
	for( int i = ehead[cur]; i; i = e[i].next ) {
		ci32 to = e[i].to;
		if( to == la ) 
			continue;
		dfs( to, cur );
		son[cur] ++;
		size[cur] += size[to];
		chk_Max( max[cur], max[to] + 1 );
	}
}

void work() {
	ecnt = 0;
	memset( ehead, 0, sizeof(ehead) );
	memset( vis, 0, sizeof(vis) );
	// ci32 n = read<i32>();
	ci32 n = 5000;
	st_mole = mole = ( rnd() % n ) + 1;
	ans_flag = false;
	qcnt = 0;
	// st_mole = mole = 3272;

	for( int i = 2; i <= n; i ++ ) {
//		ci32 u = read<i32>();
//		ci32 v = read<i32>();
// 		ci32 u = ( rnd() % ( i - 1 ) ) + 1 , v = i;
		ci32 u = i - 1 , v = i;
		add_edge( u, v );
		add_edge( v, u );
	}

	dfs( 1, 0 );

	for( int i = 1; i <= n; i ++) {
		if( size[i] == 1 ) {
			for( int k = 0; k <= MINTRY; k ++ ) {
				if( query(i) ) {
					answer(i);
					return ;
				}
			}
			break;
		}
	}

	std::vector<i32> list;
	list.push_back(1);
	for( int i = 2; i <= n; i ++ ) {
		if( max[i] >= MINTRY && son[i] > 1 ) 
			list.push_back(i);
	}
	std::sort( list.begin(), list.end(), []( const auto &_a, const auto &_b ) { return dep[_b] > dep[_a]; } );
	fa[1] = 1;
	for( auto &x: list ) {
		if( query(x) ) {
			int p = -1;
			for( int i = ehead[x]; i; i = e[i].next ) {
				ci32 to = e[i].to;
				if( max[to] >= MINTRY && dep[to] == dep[x] + 1 ) {
					if( query(to) ) {
						p = to;
						break;
					}
					if( query(x) == false ) {
						answer( fa[ fa[x] ] );
						return ;
					}
				}
			}
			std::vector<i32> l2;
			if( p == -1 ) {
				answer(x);
				return ;
			}
			l2.push_back(p);
			while( !vis[ l2.back() ] ) {
				ci32 cur = l2.back();
				bool flag = false;
				for( int i = ehead[cur]; i; i = e[i].next ) {
					ci32 to = e[i].to;
					if( dep[to] != dep[cur] + 1 ) 
						continue;
					if( max[to] < MINTRY ) 
						continue;
					l2.push_back(to);
					flag = true;
				}
				if( !flag ) 
					break;
			}
			i32 left = 0, rig = l2.size() - 1, res = 0;
			while( left <= rig ) {
				ci32 mid = ( left + rig ) >> 1;
				if( query( l2[mid] ) ) {
					res = mid;
					left = mid + 1;
				}
				else {
					rig = mid - 1;
					if( !query( l2[res] ) ) {
						answer( fa[ fa[ l2[res] ] ] );
						return ;
					}
				}
			}
			answer( l2[res] );
			return ;
		}
		else {
			vis[x] = true;
		}
	}
	answer(1);
}

int main() {
#ifdef woshiluo
//	freopen( "e1.in", "r", stdin );
//	freopen( "e1.out", "w", stdout );
#endif
	
	i32 T = read<i32>();
	while( T -- ) {
		work();
	}
}
