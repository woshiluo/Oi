/*
 * d.cpp 2024-05-31
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

const int N = 1e6 + 1e5;

const int M = 1500;

std::vector<i32> primes;
bool is_prime[N];

void init() {/*{{{*/
	memset( is_prime, true, sizeof(is_prime) );
	is_prime[0] = is_prime[1] = false;
	for( int i = 2; i < N; i ++ ) {
		if( is_prime[i] ) {
			primes.push_back(i);
		}
		for( auto &p: primes ) {
			if( 1LL * p * i >= N )
				break;
			is_prime[ p * i ] = false;
			if( i % p == 0 ) 
				break;
		}
	}
}/*}}}*/

void dfs( ci32 cur, std::map<i32, bool> mp[], std::vector<bool> &vis, std::vector<std::pair<i32, i32>> &a ) {
	while( !mp[cur].empty() ) {
		ci32 nxt = mp[cur].begin() -> first;
		mp[cur].erase(nxt);
		mp[nxt].erase(cur);
		dfs(nxt, mp, vis, a);
		a.push_back(std::make_pair(cur, nxt));
	}
}

int main() {
#ifdef woshiluo
	freopen( "d.in", "r", stdin );
	freopen( "d.out", "w", stdout );
#endif

	init();
	i32 T = read<i32>();
	while( T -- ) {
		ci32 n = read<i32>();
		if( n == 2 ) {
			printf( "2 2\n" );
			continue;
		}
		i32 target = 0;
		for( int i = 1; i <= n; i ++ ) {
			ci32 res = i * ( i - 1 ) / 2 + i + 1;
			if( i & 1 ) {
				if( n <= res ) {
					target = i;
					break;
				}
			}
			else {
				if( n <= res - i / 2 + 1 ) {
					target = i;
					break;
				}
			}
		}

		std::map<i32, bool> mp[M];
		for( int i = 0; i < target; i ++ ) {
			for( int j = 0; j < target; j ++ ) {
				if( i == j ) 
					continue;
				mp[i][j] = mp[j][i] = true;
			}
		}
		if( target % 2 == 0 ) {
			for( int i = 0; i < target - 2; i += 2 ) {
				mp[i].erase( i + 1 );
				mp[ i + 1 ].erase(i);
			}
		}
		std::vector<std::pair<i32, i32>> a;
		std::vector<i32> b;
		std::vector<bool> vis(target + 1, false);
		dfs( target - 1, mp, vis, a );
		std::reverse( a.begin(), a.end() );
		b.push_back( a[0].first );
		b.push_back( a[0].first );
		vis[ a[0].first ] = true;
		for( auto &[_, x]: a ) {
			if( !vis[x] ) {
				b.push_back(x);
				vis[x] = true;
			}
			b.push_back(x);
		}
		for( int i = 0; i < n; i ++ ) {
			printf( "%d ", primes[ b[i] ] );
		}
		printf( "\n" );
	}
}
