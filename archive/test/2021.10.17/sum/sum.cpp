/*
 * sum.cpp
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

#include <map>
#include <vector>
#include <algorithm>

typedef long long ll; typedef unsigned long long ull;

const int N = 310 * 310;

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

int p[N];
ll a[N];
int n, nn;

std::vector<int> solve( ll s1, ll s2, ll s3, bool output ) {
	std::map<ll, int> mp;
	std::vector<int> ori;
	ori.resize( n + 1 );

	ori[0] = 1;
	ori[1] = ( s1 + s2 - s3 ) / 2LL;
	ori[2] = s1 - ori[1];
	ori[3] = s2 - ori[1];
	for( int i = 1; i <= nn; i ++ ) {
		mp[ a[i] ] ++;
	}
	for( int i = 1; i <= 3; i ++ ) {
		for( int j = i + 1; j <= 3; j ++ ) {
			ll sum = ori[i] + ori[j];
			if( mp.count(sum) == 0 ) {
				ori[0] = 0;
				return ori;
			}

			mp[sum] --;
			if( mp[sum] == 0 ) 
				mp.erase(sum);
		}
	}
	for( int k = 3; k < n; k ++ ) {
		ori[ k + 1 ] = mp.begin() -> first - ori[1];
		for( int i = 1; i <= k; i ++ ) {
			ll sum = ori[i] + ori[ k + 1 ];
			if( mp.count(sum) == 0 ) {
				ori[0] = 0;
				return ori;
			}

			mp[sum] --;
			if( mp[sum] == 0 ) 
				mp.erase(sum);
		}
	}
	for( int i = 1; i <= n; i ++ ) {
		if( ori[i] <= 0 ) {
			ori[0] = 0;
			return ori;
		}
	}
	if( ori[0] && output ) {
		for( int i = 1; i <= n; i ++ ) {
			printf( "%d ", ori[i] );
		}
		printf( "\n" );
		ori[0] = 1;
	}
	return ori;
}

int main() {
	freopen( "sum.in", "r", stdin );
	freopen( "sum.out", "w", stdout );

	n = read<int>();
	nn = n * ( n - 1 ) / 2;
	for( int i = 1; i <= nn; i ++ ) {
		a[i] = read<ll>();
	}
	std::sort( a + 1, a + nn + 1 );

	int cnt = 0;
	std::vector<int> ori[N];
	for( int i = 1; i <= n + 5; i ++ ) {
		ori[i].push_back(0);
		ori[i].push_back(0);
		p[i] = i;
	}
	for( int i = 3; i <= n + 5; i ++ ) {
		if( a[i] != a[ i - 1 ] || i == 1 ) 
			ori[ i - 2 ] = solve( a[1], a[2], a[i], false );
		cnt += ori[ i - 2 ][0];
	}
	
	printf( "%d\n", cnt );
	std::sort( p + 1, p + n + 5 + 1, [ori]( const int &_a, const int &_b ) { return ori[_a][1] > ori[_b][1]; } );
	for( int i = 1; i <= n + 5; i ++ ) {
		if( ori[ p[i] ][0] ) {
			for( int j = 1; j <= n; j ++ ) {
				printf( "%d ", ori[ p[i] ][j] );
			}
			printf( "\n" );
		}
	}

	fclose( stdin );
	fclose( stdout );
	return 0;
}
