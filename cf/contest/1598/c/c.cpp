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

struct Node { int val, cnt; };

int main() {
#ifdef woshiluo
	freopen( "c.in", "r", stdin );
	freopen( "c.out", "w", stdout );
#endif
	int T = read<int>();
	while( T -- ) {
		ll sum = 0;
		int n = read<int>();
		std::vector<int> a;
		std::vector<Node> b;

		for( int i = 1; i <= n; i ++ ) {
			int tmp = read<int>();
			a.push_back(tmp);
			sum += tmp;
		}
		std::sort( a.begin(), a.end() );
		int size = a.size();
		for( int i = 0, p = 0; i < size; i = p + 1 ) {
			p = i;
			while( p + 1 < size && a[i] == a[ p + 1 ] ) 
				p ++;
			b.push_back( (Node) { a[i], p - i + 1 } );
		}
		if( ( sum * 2LL ) % n != 0 ) {
			printf( "0\n" );
			continue;
		}

		ll base = ( sum * 2 ) / n, ans = 0;
		int p2 = b.size() - 1; size = b.size();
		for( int i = 0; i < size; i ++ ) {
			while( p2 > 0 && b[p2].val + b[i].val > base ) 
				p2 --;
			if( p2 < i ) 
				break;
			if( b[p2].val + b[i].val == base ) {
				if( p2 == i )
					ans += ( 1LL * ( b[p2].cnt - 1 ) * b[i].cnt ) / 2LL;
				else
					ans += 1LL * b[p2].cnt * b[i].cnt;
			}
		}
		printf( "%lld\n", ans );
	}
}
