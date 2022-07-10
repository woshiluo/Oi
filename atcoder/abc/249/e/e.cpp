/*
 * e.cpp
 * Copyright (C) 2022 Woshiluo Luo <woshiluo.luo@outlook.com>
 *
 * 「Two roads diverged in a wood,and I—
 * I took the one less traveled by,
 * And that has made all the difference.」
 *
 * Distributed under terms of the GNU AGPLv3+ license.
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <queue>
#include <algorithm>

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

int mod = 1;

struct ModInt {/*{{{*/
	int cur;
	ModInt( ll _cur = 0 ) { cur = ( ( ( _cur % mod ) + mod ) % mod ); }

	inline ModInt operator+ ( const ModInt &b ) const { return ( cur + b.cur ) % mod; }
	inline ModInt operator- ( const ModInt &b ) const { return ( ( ( cur - b.cur ) % mod ) + mod ) % mod; }
	inline ModInt operator* ( const ModInt &b ) const { return ( 1LL * cur * b.cur ) % mod; }
	inline ModInt operator/ ( const ModInt &b ) const { return ( 1LL * cur * pow( b, mod - 2 ).cur ) % mod; }

	inline void operator+= ( const ModInt &b ) { (*this) = (*this) + b; }
	inline void operator-= ( const ModInt &b ) { (*this) = (*this) - b; }
	inline void operator*= ( const ModInt &b ) { (*this) = (*this) * b; }
	inline void operator/= ( const ModInt &b ) { (*this) = (*this) / b; }

	inline void output( const char end = '\n' ) { printf( "%d%c", cur, end ); }
};/*}}}*/

const int N = 3100;

ModInt f[N][N], pool[N];

struct Node { int i, j; }; 
std::queue<Node> wait[10];

int main() {
#ifdef woshiluo
	freopen( "e.in", "r", stdin );
	freopen( "e.out", "w", stdout );
#endif
	int n = read<int>();
	mod = read<int>();
	f[0][0] = 1;
	pool[2] = 26;
	wait[1].push( (Node) { 0, 0 } );
	for( int i = 1; i <= n; i ++ ) {
		// < 10 to < 100
		while( !wait[1].empty() && i - wait[1].front().i >= 10 ) {
			Node top = wait[1].front(); wait[1].pop();
			if( top.i == 0 ) {
				pool[ top.j + 2 ] -= 26;
				pool[ top.j + 3 ] += 26;
			}
			else {
				pool[ top.j + 2 ] -= f[ top.i ][ top.j ] * 25;
				pool[ top.j + 3 ] += f[ top.i ][ top.j ] * 25;
			}
			wait[2].push(top);
		}
		// < 100 to < 1000
		while( !wait[2].empty() && i - wait[2].front().i >= 100 ) {
			Node top = wait[2].front(); wait[2].pop();
			if( top.i == 0 ) {
				pool[ top.j + 3 ] -= 26;
				pool[ top.j + 4 ] += 26;
			}
			else {
				pool[ top.j + 3 ] -= f[ top.i ][ top.j ] * 25;
				pool[ top.j + 4 ] += f[ top.i ][ top.j ] * 25;
			}
			wait[3].push(top);
		}
		// < 1000 to >= 1000
		while( !wait[3].empty() && i - wait[3].front().i >= 1000 ) {
			Node top = wait[3].front(); wait[3].pop();
			if( top.i == 0 ) {
				pool[ top.j + 4 ] -= 26;
				pool[ top.j + 5 ] += 26;
			}
			else {
				pool[ top.j + 4 ] -= f[ top.i ][ top.j ] * 25;
				pool[ top.j + 5 ] += f[ top.i ][ top.j ] * 25;
			}
		}

		for( int j = 0; j <= n; j ++ ) {
			f[i][j] += pool[j];
			if( f[i][j].cur != 0 ) 
				wait[0].push( (Node) { i, j } );
		}

		// start
		while( !wait[0].empty() ) {
			Node top = wait[0].front(); wait[0].pop();
			pool[ top.j + 2 ] += f[ top.i ][ top.j ] * 25;
			wait[1].push(top);
		}
	}

	ModInt ans = 0;
	for( int i = 0; i < n; i ++ ) 
		ans += f[n][i];
	ans.output();
}
