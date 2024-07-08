/*
 * b.cpp 2024-03-03
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

const int N = 5e3;

i32 k, p;

struct Node {
	int ans, less;
	Node operator+ ( const Node &_b ) const {
		i32 tot = less + _b.less;
		return (Node) { ( ( ( ans + _b.ans + ( tot / k ) ) % p ) + p ) % p, tot % k  };
	}
	Node operator- ( const Node &_b ) const {
		i32 tot = less - _b.less;
		return (Node) { ( ( ( ans - _b.ans + ( tot / k ) ) % p ) + p ) % p, tot % k  };
	}
	Node operator* ( const Node &_b ) {
		i64 tot = 1LL * less * _b.less;
		return (Node) { (i32)(( ( ( 1LL * ans * _b.ans * k + 1LL * ans * _b.less + 1LL * _b.ans * less + ( tot / k ) ) % p ) + p ) % p), (i32)(tot % k)  };
	} 
	void operator+= ( const Node &_b ) { (*this) = (*this) + _b; }
};


int a[N];
Node f[N][N];

int main() {
#ifdef woshiluo
	freopen( "b.in", "r", stdin );
	freopen( "b.out", "w", stdout );
#endif

	ci32 n = read<i32>();
	k = read<i32>();
	p = read<i32>();


	for( int i = 1; i <= n; i ++ ) {
		a[i] = read<i32>();
	}
	f[0][0].less = 1;
	for( int i = 1; i <= n; i ++ ) {
		ci32 t = a[i] % k;
		for( int j = 0; j < k; j ++ ) {
			f[i][j] += f[ i - 1 ][j];
			f[i][ ( j + t ) % k ] += f[ i - 1 ][j];
		}
	}

	Node pow_2 = { 0, 1 };
	for( int i = 1; i < n; i ++ ) {
		pow_2 = pow_2 + pow_2;
	}

	Node res = { 0, 0 };
	for( int i = 1; i <= n; i ++ ) { 
		Node cur = { a[i] / k, a[i] % k };
		res += pow_2 * cur;
	}
	for( int i = 0; i < k; i ++ ) {
		Node cur = { i / k, i % k };
		res = res - cur * f[n][i];
	}

	if( res.less < 0 ) 
		printf( "%d\n", res.ans - 1 );
	else
		printf( "%d\n", res.ans );
	
}
