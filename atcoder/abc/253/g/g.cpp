/*
 * g.cpp
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

#include <ext/pb_ds/tag_and_trait.hpp>
#include <algorithm>

#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>

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

const int N = 2e5 + 1e4;

__gnu_pbds::tree<std::pair<ll, int>, __gnu_pbds::null_type, std::less<std::pair<ll, int>>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update> set;

int main() {
#ifdef woshiluo
	freopen( "g.in", "r", stdin );
	freopen( "g.out", "w", stdout );
#endif
	cint n = read<int>();
	const ll l = read<ll>();
	const ll r = read<ll>();

	for( int i = 1; i <= n; i ++ ) {
		set.insert( std::make_pair( 1LL * i * N * N, i ) );
	}

	ll cur_l = 1, cur_r = n - 1;
	for( int p = 1; p < n; p ++ ) {
		if( l <= cur_l && cur_r <= r ) {
			auto ed = *set.find_by_order( n - 1 );
			auto st = *set.find_by_order( p - 1 );
			set.erase(ed);
			ed.first = st.first - ( n - p );
			set.insert(ed);
		}
		else if( cur_l <= l && l <= cur_r ) {
			cint x = p; int y = x + ( l - cur_l + 1 );
			for( ll i = l; i <= Min( cur_r, r ); i ++, y ++ ) {
				auto b = *set.find_by_order( y - 1 );
				auto a = *set.find_by_order( x - 1 );
				set.erase(a); set.erase(b);
				std::swap( a.first, b.first );
				set.insert(a); set.insert(b);

			}
		}
		else if( cur_l <= r && r <= cur_r ) {
			cint x = p; int y = p + 1;
			for( ll i = cur_l; i <= r; i ++, y ++ ) {
				auto b = *set.find_by_order( y - 1 ); 
				auto a = *set.find_by_order( x - 1 ); 
				set.erase(a); set.erase(b);
				std::swap( a.first, b.first );
				set.insert(a); set.insert(b);
			}
		}

		cur_l = cur_r + 1;
		cur_r = cur_r + ( n - p - 1 );
	}

	for( auto &pair: set ) {
		printf( "%d ", pair.second );
	}
	printf( "\n" );
}
