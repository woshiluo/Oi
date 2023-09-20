/*
 * luogu.8252.cpp
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

#include <map>
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

int main() {
#ifdef woshiluo
	freopen( "luogu.8252.in", "r", stdin );
	freopen( "luogu.8252.out", "w", stdout );
#endif
	int T = read<int>();
	while( T -- ) {
		const int n = read<int>();
		std::vector<std::pair<int, std::vector<int>>> a;
		for( int i = 1; i <= n; i ++ ) {
			std::vector<int> b;
			int k = read<int>();
			while( k -- ) 
				b.push_back( read<int>() );
			std::sort( b.begin(), b.end() );
			b.erase( std::unique( b.begin(), b.end() ), b.end() );
			a.push_back( std::make_pair( i, b ) );
		}
		std::sort( a.begin(), a.end(), []( auto &_a, auto &_b ) { return _a.second.size() < _b.second.size(); } );
		std::map<int, int> mp;
		for( int i = 0; i < n; i ++ ) {
			mp[ a[i].first ] = i;
		}
		std::vector<int> reps( n + 1, -1 );
		bool flag = false;
		for( int i = 0; i < n; i ++ ) {
			std::map<int, int> pool;
			for( auto &x: a[i].second ) {
				if( reps[x] != -1 )
					pool[ reps[x] ] ++;
				reps[x] = a[i].first;
			}
			for( auto &pair: pool ) {
				if( pair.second != (int)a[ mp[ pair.first ] ].second.size() ) {
					flag = true;
					printf( "YES\n%d %d\n", a[i].first, pair.first );
					break;
				}
			}
			if( flag ) 
				break;
		}
		if( !flag ) 
			printf( "NO\n" );
	}
}
