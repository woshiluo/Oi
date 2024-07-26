/*
 * b.cpp 2024-07-09
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

#include <set>
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

const int N = 1e6 * 1.8; 
const int K = 20;

bool vis[N];

struct Edge {
	i32 to, next;
} e[ N * 15 ];
int ehead[N], ecnt;
void add_edge( i32 from, i32 to ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[from];
	ehead[from] = ecnt;
}
int sub[N][K], pos[N];

std::vector<i32> primes;
bool not_prime[N];
void pre() {
	not_prime[1] = true;
	for( int i = 2; i < N; i ++ ) {
		if( !not_prime[i] ) {
			primes.push_back(i);
		}
		for( auto &p: primes ) {
			if( 1LL * p * i >= N ) 
				break;
			not_prime[ p * i ] = true;
			if( i % p == 0 )
				break;
		}
	}
}

int main() {
#ifdef woshiluo
	freopen( "b.in", "r", stdin );
	freopen( "b.out", "w", stdout );
#endif

	ci32 n = read<i32>();

	if( n == 1 ) {
		printf( "%d\n", 1 );
		return 0;
	}

	pre();
	for( auto &i: primes ) {
		for( int j = ( ( N  - 1 ) / i ) * i; j > 0; j -= i ) {
			add_edge( i, j );
			pos[j] ++;
			sub[j][ pos[j] ] = i;
		}
	}

	i32 cur = 2;
	vis[cur] = 1; vis[cur] = 2;
	for( int _ = 2; _ < n; _ ++ ) {
		int res = -1;
		for( int p = 1; p <= pos[cur]; p ++ ) {
			ci32 x = sub[cur][p];
			for( int &i = ehead[x]; i; i = e[i].next ) {
				ci32 to = e[i].to;
				if( vis[to] ) 
					continue;
				if( res == -1 ) 
					res = to;
				else
					chk_Min( res, to );
				break;
			}
		}
		vis[res] = true;
		cur = res;
	}

	printf( "%d\n", cur );
}
