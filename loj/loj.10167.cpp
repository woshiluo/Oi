/*
 * loj.10167.cpp
 * Copyright (C) 2023 Woshiluo Luo <woshiluo.luo@outlook.com>
 *
 * 「Two roads diverged in a wood,and I—
 * I took the one less traveled by,
 * And that has made all the difference.」
 *
 * Distributed under terms of the GNU GNU AGPLv3+ license.
 */

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
T aabs( const T &a ) {
	return a < 0? -a: a;
}

std::vector<int> split_bit( int n ) {
	std::vector<int> res;
	while(n) {
		res.push_back( n % 10 );
		n /= 10;
	}
	res.push_back(0);
	std::reverse( res.begin(), res.end() );
	return res;
}

int f[11][11][2][2];
int dfs( cint pos, cint cur, const bool is_full, const bool all_zero, std::vector<int> &bits ) {
	if( pos == (int)bits.size() )
		return !all_zero;
	int &res = f[pos][cur][is_full][all_zero];
	if( res != -1 ) 
		return res;
	res = 0;

	for( int i = 0; i < 10; i ++ ) {
		if( is_full && i == bits[pos] ) {
			if( all_zero )
				res += dfs( pos + 1, i, is_full, i == 0, bits );
			else if( aabs( i - cur ) >= 2 ) 
				res += dfs( pos + 1, i, is_full, all_zero, bits );
		}
		else if( !is_full || i < bits[pos] ){
			if( all_zero ) 
				res += dfs( pos + 1, i, false, i == 0, bits );
			else if( aabs( i - cur ) >= 2 ) 
				res += dfs( pos + 1, i, false, all_zero, bits );
		}
	}

	return res;
}

int work( cint n ) {
	if( n == 0 ) 
		return 0;
	auto bits = split_bit(n);
	memset( f, -1, sizeof(f) );

	return dfs( 1, 0, true, true, bits );
}

int main() {
#ifdef woshiluo
	freopen( "loj.10167.in", "r", stdin );
	freopen( "loj.10167.out", "w", stdout );
#endif

	cint n = read<int>();
	cint m = read<int>();

	printf( "%d\n", work(m) - work( n - 1 ) );
}
