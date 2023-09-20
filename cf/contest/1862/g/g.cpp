/*
 * g.cpp 2023-08-24
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

#include <set>
#include <vector>
#include <algorithm>

typedef const int cint;
typedef long long ll;
typedef unsigned long long ull;
typedef const long long cll;

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
	freopen( "g.in", "r", stdin );
	freopen( "g.out", "w", stdout );
#endif

	int T = read<int>();
	while( T -- ) {
		cint n = read<int>();
		std::vector<ll> a, b( n + 1 );
		std::multiset<ll> set, diff;
		a.push_back(-2e10);
		for( int i = 1; i <= n; i ++ ) {
			a.push_back( read<int>() );
			b[i] = a.back();
		}
		a.push_back(2e10);

		std::sort( a.begin(), a.end() );
		for( auto &x: a ) 
			set.insert(x);
		for( int i = 0; i <= n; i ++ ) {
			diff.insert( a[ i + 1 ] - a[i] );
		}

		auto remove = [&]( cll val ) {
			diff.erase( diff.find(val) );
		};
		auto add = [&]( cll val ) {
			diff.insert(val);
		};
		int q = read<int>();
		while( q -- ) {
			cint pos = read<int>();
			cll x = read<ll>();

			if( n == 1 ) {
				b[pos] = x;
				printf( "%lld ", b[1] );
				continue;
			}

			{
				auto it = set.find(b[pos]);
				auto cur = it;
				cll p2 = *cur;
				cur --;
				cll p1 = *cur;
				cur ++;
				cur ++;
				cll p3 = *cur;
				remove( p2 - p1 );
				remove( p3 - p2 );
				add( p3 - p1 );
				set.erase( set.find( b[pos] ) );
			}
			{
				auto cur = set.upper_bound(x);
				cll p2 = *cur;
				cur --;
				cll p1 = *cur;
				remove( p2 - p1 );
				add( p2 - x );
				add( x - p1 );
				set.insert(x);
			}
			{
				b[pos] = x;
			}

			{
				auto cur = set.rbegin();
				while( *cur > 1e10 ) {
					cur ++;
				}
				auto cur_diff = diff.rbegin();
				while( *cur_diff > 1e10 ) {
					cur_diff ++;
				}
				printf( "%lld ", *cur + *cur_diff );
			}
		}
		printf( "\n" );
	}
}
