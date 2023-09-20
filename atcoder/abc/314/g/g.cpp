/*
 * g.cpp 2023-08-20
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
#include <sys/types.h>
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
	freopen( "g.in", "r", stdin );
	freopen( "g.out", "w", stdout );
#endif

	cint n = read<int>();
	cint m = read<int>();
	cint h = read<int>();

	struct Monster { 
		ll type, attack; 
		bool operator< ( const Monster &_b ) const {
			if( attack == _b.attack ) 
				return type < _b.type;
			return attack < _b.attack;
		}
		bool operator== ( const Monster &_b ) const {
			return type == _b.type && attack == _b.attack;
		}
	};

	std::vector<Monster> monsters;

	for( int i = 1; i <= n; i ++ ) {
		cint a = read<int>();
		cint b = read<int>();
		monsters.push_back( (Monster) { b, a } );
	}

	ll sum[2] = { 0, 0 };
	std::vector<int> dropped( m + 1 ), res( m + 1 );
	std::vector<ll> cnt( m + 1 );
	std::multiset<Monster> set[2];

	auto remove = [&]( const int type ) {
		sum[dropped[type]] -= cnt[type];
		set[dropped[type]].erase( (Monster){ type, cnt[type] } );
	};
	auto insert = [&]( const int type ) {
		sum[dropped[type]] += cnt[type];
		set[dropped[type]].insert( (Monster){ type, cnt[type] } );
	};
	auto toggle = [&]( const int type ) {
		remove(type);
		dropped[type] ^= 1;
		insert(type);
	};

	for( int i = 1; i <= m; i ++ ) {
		insert(i);
	}
	for( int i = 0; i < n; i ++ ) {
		cint type = monsters[i].type;
		remove(type);
		cnt[type] += monsters[i].attack;
		insert(type);

		while( !set[0].empty() && !set[1].empty() &&
				set[0].rbegin() -> attack > set[1].begin() -> attack ) {
			cint type1 = set[0].rbegin() -> type;
			cint type2 = set[1].begin() -> type;
			toggle( type1 );
			toggle( type2 );
		}

		while( sum[0] >= h && !set[0].empty() ) {
			toggle( set[0].rbegin() -> type );
		}

		if( sum[0] >= h ) 
			break;
		res[ set[1].size() ] = i + 1;
	}

	for( int i = 1; i <= m; i ++ ) 
		chk_Max( res[i], res[ i - 1 ] );

	for( int i = 0; i <= m; i ++ ) {
		printf( "%d ", res[i] );
	}
	
}
