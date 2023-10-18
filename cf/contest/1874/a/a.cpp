/*
 * a.cpp 2023-09-30
 * Copyright (C) 2023 Woshiluo Luo <woshiluo.luo@outlook.com>
 *
 * 「Two roads diverged in a wood,and I—
 * I took the one less traveled by,
 * And that has made all the difference.」
 *
 * Distributed under terms of the GNU GNU AGPLv3+ license.
 */

#include <cstdio>
#include <cstdint>
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

uint32_t hash( std::vector<int> &a ) {
	uint32_t res = 0;
	constexpr uint32_t BASE = 1e9 + 7;
	for( auto &x: a )
		res = ( res * BASE + (uint32_t)x );
	return res;
}

std::map< std::tuple<uint32_t, uint32_t, int>, int> mp;

void make_swap( std::vector<int> &a, std::vector<int> &b ) {
	std::sort( a.begin(), a.end() );
	std::sort( b.begin(), b.end() );

	if( a[0] < b.back() )
		std::swap( a[0], b[ b.size() - 1 ] );
}

int main() {
#ifdef woshiluo
	freopen( "a.in", "r", stdin );
	freopen( "a.out", "w", stdout );
#endif

	int T = read<int>();
	while( T -- ) {
		cint n = read<int>();
		cint m = read<int>();
		cint k = read<int>();
		mp.clear();
		std::vector<int> a(n), b(m);

		for( auto &x: a ) 
			x = read<int>();
		for( auto &x: b )
			x = read<int>();

		bool flag = true;
		for( int i = k; i >= 1; i -- ) {
			std::tuple<uint32_t, uint32_t, int> cp;
			if(flag)
				cp = std::make_tuple( hash(a), hash(b), flag );
			else
				cp = std::make_tuple( hash(b), hash(a), flag );

			if( mp.count(cp) ) {
				cint lst = mp[cp];
				cint diff = lst - i;
				flag ^= ( ( i / diff ) * diff ) & 1;
				i %= diff;
				if( i == 0 ) 
					break;
			}
			else
				mp[cp] = i;

			flag ^= 1;
			make_swap( a, b );
			std::swap( a, b );
		}

		ll res = 0;
		if( flag ) 
			for( auto &x: a ) 
				res += x;
		else
			for( auto &x: b ) 
				res += x;

		printf( "%lld\n", res );

	}
}
