/*
 * d.cpp 2024-07-28
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

const int N = 1e6;

std::vector<i32> primes;
bool not_prime[N];

void pre() {
	not_prime[0] = 1;
	for( int i = 2; i < N; i ++ ) {
		if( !not_prime[i] ) {
			primes.push_back(i);
		}
		for( auto &x: primes ) {
			if( 1LL * x * i >= N )
				break;

			not_prime[ x * i ] = true;

			if( i % x == 0 ) 
				break;
		}
	}
}

int lowbit( ci32 cur ) { return cur & ( -cur ); }

int main() {
#ifdef woshiluo
	freopen( "d.in", "r", stdin );
	freopen( "d.out", "w", stdout );
#endif

	pre();

	i32 T = read<i32>();
	while( T -- ) {
		ci32 n = read<i32>();

		int res = 0;
		std::vector<i32> col( n + 1 );
		for( int i = 1; i <= n; i ++ ) {
			std::vector<i32> list;
			for( auto &x: primes ) {
				if( ( x ^ i ) > i ) 
					continue;
				if( ( x ^ i ) == 0 )
					continue;
				list.push_back( col[ x ^ i ] );
			}

			list.push_back(0);
			std::sort( list.begin(), list.end() );
			list.erase( std::unique( list.begin(), list.end() ), list.end() );

			col[i] = -1;
			ci32 size = list.size();
			for( int j = 0; j < size; j ++ ) {
				if( list[j] != j ) {
					col[i] = j;
					break;
				}
			}
			if( col[i] == -1 ) {
				col[i] = size;
			}
			chk_Max( res, col[i] );
		}
		printf( "%d\n", res );
		for( int i = 1; i <= n; i ++ ) {
			printf( "%d ", col[i] );
			if( i % 16 == 0 ) 
				printf( "\n" );
		}

		printf( "\n" );
	}
}
