/*
 * 1007.cpp
 * Copyright (C) 2022 Woshiluo Luo <woshiluo.luo@outlook.com>
 *
 * 「Two roads diverged in a wood,and I—
 * I took the one less traveled by,
 * And that has made all the difference.」
 *
 * Distributed under terms of the GNU AGPLv3+ license.
 */

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <vector>
#include <algorithm>

typedef const int cint;
typedef long long ll;
typedef unsigned long long ull;

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

template <class T>
T aabs( const T cur ) { return cur < 0? -cur: cur; }

const int N = 5e4 + 1e3;

struct Set {/*{{{*/
	int set[N];
	void init( cint n ) { for( int i = 0; i <= n; i ++ ) set[i] = i; }
	int get_fa( cint cur ) {
		if( set[cur] == cur )
			return cur;
		set[cur] = get_fa( set[cur] );
		return set[cur];
	}
	int& operator[]( const int cur ) { 
		return set[ get_fa(cur) ];
	}
} set;/*}}}*/

int p[N], rp[N], fa[N];

int main() {
#ifdef woshiluo
	freopen( "1007.in", "r", stdin );
	freopen( "1007.out", "w", stdout );
#endif
	int T = read<int>();
	while( T -- ) {
		static std::vector<std::pair<int, int>> list[N];
		cint n = read<int>();
		for( int i = 1; i <= n; i ++ ) {
			p[i] = read<int>();
			rp[ p[i] ] = i;
			list[i].clear();
		}

		set.init(n);
		cint sqrt = std::sqrt(n) + 1;;

		for( int i = 1; i <= n; i ++ ) {
			for( int j = 1; j <= sqrt; j ++ ) {
			//	if( i - j >= 1 ) {
			//		const ll len = 1LL * j  * aabs( p[i] - p[ i - j ] );
			//		if( len <= n ) 
			//			list[len].push_back( std::make_pair( i, i - j ) );
			//	}
				if( i + j <= n ) {
					const ll len = 1LL * j  * aabs( p[i] - p[ i + j ] );
					if( len <= n ) 
						list[len].push_back( std::make_pair( i, i + j ) );
				}
			//	if( p[i] - j >= 1 ) {
			//		const ll len = 1LL * j * aabs( i - rp[ p[i] - j ] );
			//		if( len <= n ) 
			//			list[len].push_back( std::make_pair( i, rp[ p[i] - j ] ) );
			//	}
				if( p[i] + j <= n ) {
					const ll len = 1LL * j * aabs( i - rp[ p[i] + j ] );
					if( len <= n ) 
						list[len].push_back( std::make_pair( i, rp[ p[i] + j ] ) );
				}
			}
		}

		ll res = 0;
		for( int i = 1; i <= n; i ++ ) {
			for( auto &pair: list[i] ) {
				if( set[ pair.first ] == set[ pair.second ] )
					continue;

				res += i;
				set[ pair.first ] = set[ pair.second ];
			}
		}

		printf( "%lld\n", res );
	}
}
