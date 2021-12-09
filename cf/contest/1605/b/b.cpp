/*
 * b.cpp
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

const int N = 1100;

int n;
int a[N];

bool check() {
	bool flag = true;
	for( int i = 1; i < n; i ++ ) {
		flag = ( flag && ( a[i] <= a[ i + 1 ] ) );
	}
	return flag;
}

void work() {
	n = read<int>();
	for( int i = 1; i <= n; i ++ ) {
		scanf( "%1d", &a[i] );
	}

	int cnt = 0;
	std::vector<int> ans[N];
	while( !check() ) {
		cnt ++;
		static int sum[N];
		sum[0] = 0;
		for( int i = 1; i <= n; i ++ ) {
			sum[i] = sum[ i - 1 ] + a[i];
		}
		auto query1 = []( const int left, const int rig ) { return sum[rig] - sum[ left - 1 ]; };
		auto query0 = [query1]( const int left, const int rig ) { return ( rig - left + 1 ) - query1( left, rig ); };
		int pos = 1;
		for( int i = 1; i <= n - 1; i ++ ) {
			if( query1( 1, i ) <= query0( i + 1, n ) )
				pos = i;
		}
		for( int i = 1; i <= pos; i ++ ) {
			if( a[i] ) {
				ans[cnt].push_back(i);
				a[i] = 0;
			}
		}
		int tmp = ans[cnt].size();
		for( int i = n; i >= pos - 1; i -- ) {
			if( tmp && a[i] == 0 ) {
				tmp --;
				ans[cnt].push_back(i);
				a[i] = 1;
			}
		}
		std::sort( ans[cnt].begin(), ans[cnt].end() );
	}

	printf( "%d\n", cnt );
	for( int i = 1; i <= cnt; i ++ ) {
		printf( "%ld ", ans[i].size() );
		for( auto &x: ans[i] ) 
			printf( "%d ", x );
		printf( "\n" );
	}
}

int main() {
#ifdef woshiluo
	freopen( "b.in", "r", stdin );
	freopen( "b.out", "w", stdout );
#endif
	int T = read<int>();
	while( T -- ) {
		work();
	}
}
