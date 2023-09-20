/*
 * c.cpp 2023-08-26
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

#include <map>
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

int main() {
#ifdef woshiluo
	freopen( "c.in", "r", stdin );
	freopen( "c.out", "w", stdout );
#endif

	int T = read<int>();
	while( T -- ) {
		cint n = read<int>();
		cint c = read<int>();
		cint d = read<int>();
		std::vector<int> a;
		std::map<int, bool> mp;
		ll base = 0;
		for( int i = 1; i <= n; i ++ ) {
			cint cur = read<int>();
			if( mp[cur] ) {
				base += c;
				continue;
			}
			mp[cur] = true;
			a.push_back(cur);
		}
		std::sort( a.begin(), a.end() );

		ll ans = base + 1LL * a.size() * c + d; // delete all, then add `1`
		cint size = a.size();
		for( int i = 0; i < size; i ++ ) {
			chk_Min( ans, base + 1LL * ( size - i - 1 ) * c + 1LL * ( a[i] - i - 1 ) * d );
		}
		printf( "%lld\n", ans );

	}
}
