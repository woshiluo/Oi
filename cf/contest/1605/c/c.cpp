/*
 * c.cpp
 * Copyright (C) 2021 Woshiluo Luo <woshiluo.luo@outlook.com>
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

const int N = 1e6 + 1e5;

int n;
char str[N];
int b[N], c[N];
int sum_b[N], sum_c[N];

int query_b( const int left, const int rig ) { return sum_b[rig] - sum_b[ left - 1 ]; }
int query_c( const int left, const int rig ) { return sum_c[rig] - sum_c[ left - 1 ]; }

void check( int cur, int &ans ) {
	int left = 1, rig = cur, res = rig;
	while( left <= rig ) {
		int mid = ( left + rig ) >> 1;
		if( query_b( mid, cur ) > 0 && query_c( mid, cur ) > 0 ) {
			res = mid;
			left = mid + 1;
		}
		else 
			rig = mid - 1;
	}
	if( cur - res + 1 >= 2 )
		chk_Min( ans, cur - res + 1 );
}

void work() {
	n = read<int>();
	scanf( "%s", str + 1 );

	std::vector<int> pos;
	sum_b[0] = sum_c[0] = 0;
	for( int i = 1; i <= n; i ++ ) {
		b[i] = c[i] = 0;
		if( str[i] == 'a' ) 
			b[i] = c[i] = 1;
		if( str[i] == 'b' ) 
			b[i] = -1;
		if( str[i] == 'c' )
			c[i] = -1;
		sum_b[i] = sum_b[ i - 1 ] + b[i];
		sum_c[i] = sum_c[ i - 1 ] + c[i];

		if( str[i] == 'a' ) 
			pos.push_back(i);
	}

	auto qb = [pos]( const int left, const int rig ) { return sum_b[ pos[rig] ] - sum_b[ pos[left] - 1 ]; };
	auto qc = [pos]( const int left, const int rig ) { return sum_c[ pos[rig] ] - sum_c[ pos[left] - 1 ]; };
	int size = pos.size(), res = n + n;
	for( int i = 1; i < size; i ++ ) {
		for( int p1 = Max( i - 3, 0 ); p1 <= i; p1 ++ ) {
			if( qb( p1, i ) > 0 && qc( p1, i ) > 0 ) {
				int len = pos[i] - pos[p1] + 1;
				if( len >= 2 ) 
					chk_Min( res, len );
			}
		}
	}
	printf( "%d\n", res > n? -1: res );
}

int main() {
#ifdef woshiluo
	freopen( "c.in", "r", stdin );
	freopen( "c.out", "w", stdout );
#endif
	int T = read<int>();
	while( T -- ) {
		work();
	}
}
