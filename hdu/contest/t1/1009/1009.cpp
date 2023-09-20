/*
 * 1009.cpp
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

struct Node { 
	int x, y; 
	bool operator< ( const Node &_b ) const { 
		if( x == _b.x ) 
			return y < _b.y;
		return x < _b.x; 
	}
};
std::map<int, std::vector<Node>> mp[4];
std::map<int, int> size[4];
std::map<Node, int> has;

bool work() {
	mp[0].clear(); mp[1].clear(); mp[2].clear(); mp[3].clear();
	size[0].clear(); size[1].clear(); size[2].clear(); size[3].clear();
	has.clear();

	cint n = read<int>();

	auto check = [&]( cint x, cint y ) {
		const Node cur = (Node){ x, y };

		cint res = size[0][x]
			+ size[1][y] 
			+ size[2][ x + y ]
			+ size[3][ x - y ]
			- 3 * has[cur];

		return res == n;
	};

	auto check_x = [&] ( cint p, cint val ) {/*{{{*/
		auto nodes = mp[p][val];
		cint nsize = size[p][val];
		std::sort( nodes.begin(), nodes.end() );
		if( nsize == 2 ) {
			cint d = ( nodes[1].y - nodes[0].y );
			if( d % 2 == 0 ) {
				cint k = d / 2;
				cint y = nodes[0].y + k;
				if( check( nodes[0].x - k, y ) ||
						check( nodes[0].x + k, y ) ) 
					return true;
			}
			if( check( nodes[0].x + d, nodes[0].y ) || check( nodes[0].x - d, nodes[0].y ) ||
					check( nodes[1].x + d, nodes[1].y ) || check( nodes[1].x - d, nodes[1].y ) ) 
				return true;
		}
		if( nsize == 3 ) {
			cint d = ( nodes[2].y - nodes[0].y );
			if( d % 2 == 0 ) {
				cint k = d / 2;
				cint y = nodes[0].y + k;
				if( check( nodes[0].x - k, y ) ||
						check( nodes[0].x + k, y ) ) 
					return true;
			}
		}

		for( auto &pair: size[1] ) {
			if( check( val, pair.first ) ) 
				return true;
		}
		for( auto &pair: size[2] ) {
			if( check( val, pair.first - val ) ) 
				return true;
		}
		for( auto &pair: size[3] ) {
			if( check( val, val - pair.first ) ) 
				return true;
		}

		return false;
	};/*}}}*/

	auto check_y = [&] ( cint p, cint val ) {/*{{{*/
		auto nodes = mp[p][val];
		cint nsize = size[p][val];
		std::sort( nodes.begin(), nodes.end() );
		if( nsize == 2 ) {
			cint d = ( nodes[1].x - nodes[0].x );
			if( d % 2 == 0 ) {
				cint k = d / 2;
				cint x = nodes[0].x + k;
				if( check( x, nodes[0].y + k ) ||
						check( x, nodes[0].y - k ) ) 
					return true;
			}
			if( check( nodes[0].x, nodes[0].y + d ) || check( nodes[0].x, nodes[0].y - d ) ||
					check( nodes[1].x, nodes[1].y + d ) || check( nodes[1].x, nodes[1].y - d ) ) 
				return true;
		}
		if( nsize == 3 ) {
			cint d = ( nodes[2].x - nodes[0].x );
			if( d % 2 == 0 ) {
				cint k = d / 2;
				cint x = nodes[0].x + k;
				if( check( x, nodes[0].y + k ) ||
						check( x, nodes[0].y - k ) ) 
					return true;
			}
		}

		for( auto &pair: size[0] ) {
			if( check( pair.first, val ) ) 
				return true;
		}

		for( auto &pair: size[2] ) {
			if( check( pair.first - val, val ) ) 
				return true;
		}

		for( auto &pair: size[3] ) {
			if( check( val + pair.first, val ) ) 
				return true;
		}

		return false;
	};/*}}}*/

	auto check_xy1 = [&] ( cint p, cint val ) {/*{{{*/
		auto nodes = mp[p][val];
		cint nsize = size[p][val];
		std::sort( nodes.begin(), nodes.end() );

		if( nsize == 2 ) {
			cint minx = Min( nodes[0].x, nodes[1].x );
			cint maxx = Min( nodes[0].x, nodes[1].x );
			cint miny = Max( nodes[0].y, nodes[1].y );
			cint maxy = Max( nodes[0].y, nodes[1].y );

			if( check( minx, miny ) || check( maxx, maxy ) ) 
				return true;

			cint d = maxx - minx;
			if( check( minx - d, miny ) || check( minx, miny - d ) ||
				check( maxx + d, maxy ) || check( maxx, maxy + d ) ) 
				return true;
		}
		if( nsize == 3 ) {
			cint minx = Min( nodes[0].x, nodes[2].x );
			cint maxx = Min( nodes[0].x, nodes[2].x );
			cint miny = Max( nodes[0].y, nodes[2].y );
			cint maxy = Max( nodes[0].y, nodes[2].y );

			if( check( minx, miny ) || check( maxx, maxy ) ) 
				return true;
		}

		for( auto &pair: size[0] ) {
			if( check( pair.first, val - pair.first ) ) 
				return true;
		}

		for( auto &pair: size[1] ) {
			if( check( val - pair.first, pair.first ) ) 
				return true;
		}

		for( auto &pair: size[3] ) {
			cint sum = pair.first + val;
			if( sum & 1 ) {
				if( (int)( nsize + pair.second ) == n ) 
					return true;
			}
			else if( check( sum / 2, val - ( sum / 2 ) ) ) 
				return true;
		}

		return false;
	};/*}}}*/

	auto check_xy2 = [&] ( cint p, cint val ) {/*{{{*/
		auto nodes = mp[p][val];
		cint nsize = size[p][val];
		std::sort( nodes.begin(), nodes.end() );

		if( nsize == 2 ) {
			cint minx = Min( nodes[0].x, nodes[1].x );
			cint maxx = Min( nodes[0].x, nodes[1].x );
			cint miny = Max( nodes[0].y, nodes[1].y );
			cint maxy = Max( nodes[0].y, nodes[1].y );

			if( check( minx, maxy ) || check( maxx, miny ) ) 
				return true;

			cint d = maxx - minx;
			if( check( minx - d, maxy ) || check( minx, maxy + d ) ||
				check( maxx + d, miny ) || check( maxx, miny - d ) ) 
				return true;
		}
		if( nsize == 3 ) {
			cint minx = Min( nodes[0].x, nodes[2].x );
			cint maxx = Min( nodes[0].x, nodes[2].x );
			cint miny = Max( nodes[0].y, nodes[2].y );
			cint maxy = Max( nodes[0].y, nodes[2].y );

			if( check( minx, maxy ) || check( maxx, miny ) ) 
				return true;
		}

		for( auto &pair: size[0] ) {
			if( check( pair.first, pair.first - val ) ) 
				return true;
		}

		for( auto &pair: size[1] ) {
			if( check( val + pair.first, pair.first ) ) 
				return true;
		}

		for( auto &pair: size[2] ) {
			cint sum = pair.first + val;
			if( sum & 1 ) {
				if( (int)( nsize + pair.second ) == n ) 
					return true;
			}
			else if( check( sum / 2, pair.first - ( sum / 2 ) ) ) 
				return true;
		}

		return false;
	};/*}}}*/

	int p = -1, pos = -1, max = -1;

	for( int i = 1; i <= n; i ++ ) {
		cint x = read<int>();
		cint y = read<int>();

		const Node cur = (Node) { x, y };

		size[0][ cur.x ];
		size[1][ cur.y ];
		size[2][ cur.x + cur.y ];
		size[3][ cur.x - cur.y ];
		int &s0 = size[0][ cur.x ];
		int &s1 = size[1][ cur.y ];
		int &s2 = size[2][ cur.x + cur.y ];
		int &s3 = size[3][ cur.x - cur.y ];

		has[cur] ++;
		if( s0 < 3 )
			mp[0][cur.x].push_back(cur);
		if( s1 < 3 ) 
			mp[1][cur.y].push_back(cur);
		if( s2 < 3 )
			mp[2][ cur.x + cur.y ].push_back(cur);
		if( s3 < 3 )
			mp[3][ cur.x - cur.y ].push_back(cur);

		s0 ++; s1 ++; s2 ++; s3 ++;

		if( s0 > max ) {
			p = 0; pos = cur.x; max = s0;
		}
		if( s1 > max ) {
			p = 1; pos = cur.y; max = s1;
		}
		if( s2 > max ) {
			p = 2; pos = cur.x + cur.y; max = s2;
		}
		if( s3 > max ) {
			p = 3; pos = cur.y; max = s3;
		}
	}

	if( max >= 1 ) {
		if( p == 0 ) 
			return check_x( p, pos );
		if( p == 1 ) 
			return check_y( p, pos );
		if( p == 2 ) 
			return check_xy1( p, pos );
		if( p == 3 ) 
			return check_xy2( p, pos );
	}

	return false;
}

int main() {
#ifdef woshiluo
	freopen( "1009.in", "r", stdin );
	freopen( "1009.out", "w", stdout );
#endif
	int T = read<int>();
	while( T -- ) {
		printf( "%s\n", work()? "YES": "NO" );
	}
}
