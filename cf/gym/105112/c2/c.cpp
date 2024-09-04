/*
 * c.cpp 2024-09-04
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

i64 exgcd(i64 N,i64 M,i64&X,i64&Y)
{
    if(!M){X=1;Y=0;return N;}
    i64 gCd=exgcd(M,N%M,Y,X);
    Y-=N/M*X;
    return gCd;
}
i64 Inv(i64 N,i64 P,i64 k1=0,i64 k2=0)
{
    exgcd(N,P,k1,k2);
    return(k1%P+P)%P;
}

const int N = 5e5 + 1e4;

i64 gcd( i64 a, i64 b ) { return b? gcd( b, a % b ): a; }

int main() {
#ifdef woshiluo
	freopen( "c.in", "r", stdin );
	freopen( "c.out", "w", stdout );
#endif

	ci32 n = read<i32>();
	ci32 q = read<i32>();
	i32 offset = 0, mul = 1, mul_inv = 1;
	i32 cn = n;
	std::vector<i32> pos( n + 1 );
	for( int i = 1; i <= n; i ++ ) {
		pos[i] = i;
	}

	for( int _ = 1; _ <= q; _ ++ ) {
		static char buf[16];
		scanf( "%s", buf );
		ci32 k = read<i32>();
		if( buf[0] == '*' ) {
			offset *= k;
			if( gcd( cn, k ) == 1 ) {
				mul *= k;
				mul_inv *= Inv( k, cn );
				continue;
			}
			std::vector<i32> np = pos;
			for( int i = 1; i <= cn; i ++ ) {
				i32 nxt = ( ( 1LL * i * mul ) + offset ) % cn;
				if( nxt == 0 ) 
					nxt = cn;
				np[nxt] = pos[i];
			}
			pos = np;
			i32 cnt = 0;
			std::vector<i32> vis( cn + 1 );
			for( int i = 1; i <= cn; i ++ ) {
				i32 nxt = ( ( i * k ) + offset ) % cn;
				if( vis[nxt] ) 
					continue;
				cnt ++;
				vis[nxt] = true;
				if( nxt == 0 ) 
					nxt = cn;
				np[nxt] = pos[i];
			}
			pos = np;
			np.resize(0);
			np.push_back(0);
			for( int i = 1; i <= cnt; i ++ ) 
				if( vis[i] ) 
					np.push_back( pos[i] );
			cn = cnt;
			mul = 1, mul_inv = 1, offset = 0;
		}
		if( buf[0] == '+' ) {
			offset += k;
		}
		if( buf[0] == '?' ) {
			ci32 diff = offset % n;
			if( k % cn == diff ) {
			}
			else 
				printf( "-1\n" );
		}
	}
}
