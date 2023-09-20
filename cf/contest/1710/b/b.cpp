/*
 * b.cpp
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
#include <queue>
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

const ll INF = (1e18);

struct Op { 
	ll id, p, x; 
	bool operator< ( const Op &_b ) const {
		return p + x > _b.p + _b.x;
	}
};

struct ROp { 
	ll id, p, x; 
	bool operator< ( const ROp &_b ) const {
		return x - p < _b.x - _b.p;
	}
};

int main() {
#ifdef woshiluo
	freopen( "b.in", "r", stdin );
	freopen( "b.out", "w", stdout );
#endif
	int T = read<int>();
	while( T -- ) {
		cint n = read<int>();
		cint m = read<int>();

		std::vector<Op> ops;
		std::vector<ROp> rops;
		std::map<int, ll> mp;
		for( int i = 1; i <= n; i ++ ) {
			cint x = read<int>();
			cint p = read<int>();
			ops.push_back( (Op) { i, p, x } );
			rops.push_back( (ROp) { i, p, x } );
			mp[x] += p;
		}

		std::sort( ops.begin(), ops.end(), []( const Op &_a, const Op &_b ) { return _a.x < _b.x; } );
		std::sort( rops.begin(), rops.end(), []( const ROp &_a, const ROp &_b ) { return _a.x > _b.x; } );

		{
			ll la = ops.front().p;
			ll cur = 0;
			std::vector<Op> wait_list;
			std::priority_queue<Op> q;
			for( auto &op: ops ) {
				if( wait_list.size() != 0 && wait_list.front().x != op.x ) {
					for( auto &cop: wait_list ) {
						cur += cop.p;
						q.push(cop);
					}
					wait_list.clear();
				}
				while( !q.empty() ) {
					auto top = q.top(); 
					if( top.x + top.p - 1 < op.x ) {
						q.pop();
						cur -= top.p - ( la - top.x );
					}
					else
						break;
				}
				cur -= 1LL * q.size() * ( op.x - la );

				if( op.x != la )
					mp[op.x] += cur;

				la = op.x;
				wait_list.push_back(op);
			}
		}
		{
			ll la = rops.front().p;
			ll cur = 0;
			std::vector<ROp> wait_list;
			std::priority_queue<ROp> q;
			for( auto &op: rops ) {
				if( wait_list.size() != 0 && wait_list.front().x != op.x ) {
					for( auto &cop: wait_list ) {
						cur += cop.p;
						q.push(cop);
					}
					wait_list.clear();
				}
				while( !q.empty() ) {
					auto top = q.top(); 
					if( top.x - top.p + 1 > op.x ) {
						q.pop();
						cur -= top.p - ( top.x - la );
					}
					else
						break;
				}
				cur -= 1LL * q.size() * ( la - op.x );

				if( op.x != la )
					mp[op.x] += cur;

				la = op.x;
				wait_list.push_back(op);
			}
		}


		cint minx = mp.begin() -> first;
		cint maxx = mp.rbegin() -> first;
		std::map<int, ll> minls, minrs;
		{
			ll minl = -INF, minr = -INF;
			std::vector<std::pair<int, ll>> list;
			for( auto &pair: mp ) {
				// printf( "%d %lld\n", pair.first, pair.second );
				list.push_back(pair);
			}

			cint size = list.size();
			for( int i = 0; i < size; i ++ ) {
				if( list[i].second > m ) {
					ll res = ( list[i].second - m - ( list[i].first - minx ) );
					chk_Max( minl, res );
				}
				minls[ list[i].first ] = minl;
			}
			for( int i = size - 1; i >= 0; i -- ) {
				if( list[i].second > m ) {
					ll res = ( list[i].second - m - ( maxx - list[i].first ) );
					chk_Max( minr, res );
				}
				minrs[ list[i].first ] = minr;
			}
		}

		std::sort( ops.begin(), ops.end(), []( const Op &_a, const Op &_b ) { return _a.id < _b.id; } );
		for( auto &op: ops ) {
			const ll cl = ( op.p - ( op.x - minx ) );
			const ll cr = ( op.p - ( maxx - op.x ) );
			if( cl >= minls[ op.x ] && cr >= minrs[ op.x ] ) 
				printf( "1" );
			else
				printf( "0" );
		}

		printf( "\n" );
	}
}
