/*
 * e.cpp
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

const int N = 3e5 + 1e4;

int a[N];

std::map<ll, int> mp;

int main() {
#ifdef woshiluo
	freopen( "e.in", "r", stdin );
	freopen( "e.out", "w", stdout );
#endif
	int T = read<int>();
	auto erase_big = [] ( const ll &cur ) {
		while( !mp.empty() ) {
			auto p = mp.end(); --p;
			if( p -> first > cur ) 
				mp.erase(p);
			else
				break;
		}
	};
	auto erase_less = [] ( const ll &cur ) {
		while( !mp.empty() ) {
			auto p = mp.begin(); 
			if( p -> first < cur ) 
				mp.erase(p);
			else
				break;
		}
	};
	while( T -- ) {
		mp.clear();

		int n = read<int>();
		ll sum = 0, ans = 0; mp[0] = 1;
		for( int i = 1; i <= n; i ++ ) {
			a[i] = read<int>();
		}
		for( int i = 1; i <= n; i ++ ) {
			if( i & 1 ) 
				sum += a[i];
			else 
				sum -= a[i];
			ans += mp[sum];

			if( i >= n ) 
				continue;
			if( i & 1 ) 
				erase_less( sum - a[ i + 1 ] );
			else
				erase_big( sum + a[ i + 1 ] );

			mp[sum] ++;
		}
		printf( "%lld\n", ans );
	}
}
