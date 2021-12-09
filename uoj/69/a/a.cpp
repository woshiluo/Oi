/*
 * a.cpp
 * Copyright (C) 2021 Woshiluo Luo <woshiluo.luo@outlook.com>
 *
 * 「Two roads diverged in a wood,and I—
 * I took the one less traveled by,
 * And that has made all the difference.」
 *
 * Distributed under terms of the GNU AGPLv3+ license.
 */

#include <cstdio>

#include <map>
#include <vector>
#include <algorithm>

typedef long long ll;
typedef unsigned long long ull;

const int N = 5e5 + 1e4;

inline bool is_digit( const char cur ) { return cur >= '0' && cur <= '9'; }
template<class T>
T read() {
	T res = 0, k = 1; char x = getchar();
	for( ; !is_digit(x); x = getchar() ) 
		if( x == '-' ) 
			k = -1;
	for( ; is_digit(x); x = getchar() ) 
		res = res * 10 + ( x - '0' );
	return res * k;
}

int n, m;

struct Name {
	int val[2], len;
	ll hash;
	bool rev;
	Name() { val[0] = val[1] = len = 0; rev = false; }

	inline void swap() {
		std::swap( val[0], val[1] );
		rev ^= 1;
	}
	inline void sort() {
		if( len == 1 ) 
			return ;
		if( val[1] < val[0] ) 
			this -> swap();
	}
	inline long long gen_hash() {
		this -> sort();
		if( len == 1 ) 
			return val[0];
		return 1LL * val[0] * ( m + 1 ) + val[1];
	}
	inline void update() {
		hash = this -> gen_hash();
	}

	inline bool operator= ( const Name &_b ) const { return this -> hash == _b.hash; }
};
bool cmp( const Name _a, const Name _b ) { return _a.hash < _b.hash; }

Name name[N];
int pos[N];
int str[ N << 1 ];
int id[ N << 1 ], nxt[ N << 1 ];
bool vis[ N << 1 ];

void check() {
	int len = 1;
	for( int i = 0; i < n; i ++ ) {
		int cur = pos[i];
		if( name[cur].len == 1 ) {
			str[len] = name[cur].val[0];
			nxt[len] = 0;
			id[len] = cur;
			len ++;
		}
		else {
			str[len] = name[cur].val[0]; len ++; 
			str[len] = name[cur].val[1]; len ++;
			nxt[len - 2] = len - 1; nxt[len - 1] = len - 2;
			id[ len - 1 ] = id[ len - 2 ] = cur;
		}
	}
	int p1 = 1, p2 = len - 1;
	while( p1 < p2 ) {
		if( str[p1] == str[p2] ) {
			p1 ++; p2 --;
			nxt[p1] = nxt[p2] = nxt[ nxt[p1] ] = nxt[ nxt[p2] ] = 0;
			continue;
		}
		if( nxt[p1] && str[ nxt[p1] ] == str[p2] ) {
			name[ id[p1] ].swap();
			std::swap( str[p1], str[ nxt[p1] ] );
		}
		else if( nxt[p2] && str[p1] == str[ nxt[p2] ] ) {
			name[ id[p2] ].swap();
			std::swap( str[p2], str[ nxt[p2] ] );
		}
		else if( nxt[p1] && nxt[p2] && str[ nxt[p1] ] == str[ nxt[p2] ] ) {
			name[ id[p1] ].swap();
			name[ id[p2] ].swap();
			std::swap( str[p1], str[ nxt[p1] ] );
			std::swap( str[p2], str[ nxt[p2] ] );
		}

		if( str[p1] != str[p2] ) 
			return ;
		p1 ++; p2 --;
		nxt[p1] = nxt[p2] = nxt[ nxt[p1] ] = nxt[ nxt[p2] ] = 0;
	}

	for( int i = 0; i < n; i ++ ) {
		printf( "%d ", pos[i] );
	}
	printf( "\n" );
	for( int i = 0; i < n; i ++ ) {
		printf( "%d ", (int)name[ pos[i] ].rev );
	}
	std::exit(0);
}

void dfs( int depth ) {
	if( depth == n ) {
		check();
		return ;
	}
	for( int i = 1; i <= n; i ++ ) {
		if( vis[i] ) 
			continue;
		vis[i] = true;
		pos[depth] = i;
		dfs( depth + 1 );
		vis[i] = false;
	}
}

namespace sub_bf {
	void calc() {
		std::map<ll, std::vector<int>> mp;
		std::vector<int> a[2];
		int gol = -1;
		for( int i = 1; i <= n; i ++ ) 
			mp[ name[i].hash ].push_back(i);
		for( auto &pair: mp ) {
			int size = pair.second.size();
			if( size & 1 ) {
				gol = pair.second.back();
				size --;
			}
			for( int i = 0; i < size; i += 2 ) {
				a[0].push_back( pair.second[i] );
				a[1].push_back( pair.second[ i + 1 ] );
			}
		}
		for( auto cur: a[0] ) 
			printf( "%d ", cur );
		if( gol != -1 ) 
			printf( "%d ", gol );
		for( auto cur: a[1] ) 
			printf( "%d ", cur );

		printf( "\n" );
		for( auto cur: a[0] ) 
			printf( "%d ", name[cur].rev );
		if( gol != -1 ) 
			printf( "%d ", 0 );
		for( auto cur: a[1] ) 
			printf( "%d ", name[cur].rev ^ 1 );
	}
}

int main() {
#ifdef woshiluo
	freopen( "a.in", "r", stdin );
	freopen( "a.out", "w", stdout );
#endif
	n = read<int>(); m = read<int>();
	int len = 2;
	for( int i = 1; i <= n; i ++ ) {
		int k = read<int>();
		for( int j = 0; j < k; j ++ ) 
			name[i].val[j] = read<int>();
		len = std::min( len, k );
		name[i].len = k;
		name[i].update();
	}

	if( len == 2 ) 
		sub_bf::calc();
	else 
		dfs(0);
}
