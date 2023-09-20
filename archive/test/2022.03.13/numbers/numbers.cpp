/*
 * numbers.cpp
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

#include <vector>
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

ll f[30][30][30][2][2];
std::vector<int> bit;
ll dfs( int depth, int la, int cur, bool max, bool has ) {
	ll &res = f[depth][la][cur][max][has];
	if( depth == 0 ) 
		return 1;
	if( res != -1 ) 
		return res;
	res = 0;
	for( int i = 0; i < 10; i ++ ) {
		if( max && i > bit[depth] )
			break;
		if( i == la || i == cur )
			continue;
		if( i != 0 || has ) 
			res += dfs( depth - 1, cur, i, max && ( i == bit[depth] ), 1 );
		else if( i == 0 && !has ) 
			res += dfs( depth - 1, cur, 10, max && ( i == bit[depth] ), has );
	}
	return res;
};

ll work( ll cur ) {
	if( cur == -1 ) 
		return 0;
	bit.resize(0);
	bit.push_back(0);
	while( cur ) {
		bit.push_back( cur % 10 );
		cur /= 10;
	}
	memset( f, -1, sizeof(f) );

	return dfs( bit.size() - 1, 10, 10, 1, 0 );
}

int main() {
	freopen( "numbers.in", "r", stdin );
	freopen( "numbers.out", "w", stdout );

	ll a, b;
	a = read<ll>(); b = read<ll>();

	printf( "%lld\n", work(b) - work( a - 1 ) );

	fclose( stdin );
	fclose( stdout );
	return 0;
}
