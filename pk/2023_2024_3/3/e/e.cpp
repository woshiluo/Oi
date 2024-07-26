/*
 * e.cpp 2024-07-09
 * Copyright (C) 2024 Woshiluo Luo <woshiluo.luo@outlook.com>
 *
 * 「Two roads diverged in a wood,and I—
 * I took the one less traveled by,
 * And that has made all the difference.」
 *
 * Distributed under terms of the GNU GNU AGPLv3+ license.
 */

#include <cstdio>
#include <cstdint>
#include <cstring>
#include <cstdlib>

#include <queue>
#include <vector>
#include <algorithm>

using i32 = int32_t;
using u32 = uint32_t;
using ci32 = const int32_t;
using cu32 = const uint32_t;

using i64 = int64_t;
using u64 = uint64_t;
using ci64 = const int64_t;
using cu64 = const uint64_t;

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
T pow( T a, i32 p ) {
	T res = 1;
	while( p ) {
		if( p & 1 ) 
			res = res * a;
		a = a * a;
		p >>= 1;
	}
	return res;
}/*}}}*/

const int N = 512;

i32 id[N][N];
i64 res[N][N];
bool has[N * N];

std::pair<i32, i32> node[N * N];


int main() {
#ifdef woshiluo
	freopen( "e.in", "r", stdin );
	freopen( "e.out", "w", stdout );
#endif
	ci32 n = read<i32>();
	{// {{{
		std::vector<i32> relo;
		std::vector<std::vector<i32>> p( n * n );
		for( int i = 0; i < n * n; i ++ ) {
			ci32 v = read<i32>();
			has[i] = v;
			ci32 k = read<i32>();
			p[i].resize(k);
			for( auto &x: p[i] ) {
				x = read<i32>() - 1;
			}
			relo.push_back(i);
			node[i] = std::make_pair( -1, -1 );
		}
		// TODO: cmp & opti
		std::sort( relo.begin(), relo.end(), [&]( const auto &_a, const auto &_b ) { return p[_a].size() < p[_b].size(); } );

		std::queue<std::pair<i32, i32>> q;
		int st = relo[0];
		node[st] = std::make_pair( 0, 0 );
		node[ p[st][0] ] = std::make_pair( 0, 1 );
		node[ p[st][1] ] = std::make_pair( 1, 0 );
		q.push( std::make_pair( p[st][0], st ) );
		q.push( std::make_pair( p[st][1], st ) );

		while( !q.empty() ) {
			auto [cur, pre] = q.front(); q.pop();
			ci32 dx = node[cur].first - node[pre].first;
			ci32 dy = node[cur].second - node[pre].second;
			if( p[cur].size() == 2 ) {
				if( node[cur].first == n - 1 && node[cur].second == n - 1  )
					continue;
				for( auto &x: p[cur] ) {
					if( x == pre ) 
						continue;
					if( node[x].first != -1 ) 
						continue;
					node[x] = std::make_pair( node[cur].first + ( dx ^ 1 ), node[cur].second + ( dy ^ 1 ) );
					q.push( std::make_pair( x, cur ) );
				}
				continue;
			}
			for( auto &x: p[cur] ) {
				if( p[x].size() == 4 ) 
					continue;
				if( x == pre ) 
					continue;
				if( node[x].first != -1 ) 
					continue;
				node[x] = std::make_pair( node[cur].first + dx, node[cur].second + dy );
				q.push( std::make_pair( x, cur ) );
			}
		}

		for( auto &x: relo ) {
			if( p[x].size() == 2 ) 
				continue;
			if( p[x].size() == 4 ) 
				break;
			ci32 dx = ( node[x].first == 0 ) || ( node[x].first == n - 1 );
			ci32 dy = ( node[x].second == 0 ) || ( node[x].second == n - 1 );
			for( auto &y: p[x] ) {
				if( p[y].size() == 4 ) {
					if( node[y].first != -1 ) 
						continue;
					node[y] = std::make_pair( node[x].first + ( dx * ( ( node[x].first == 0 )? 1: -1 ) ), 
							node[x].second + dy * ( ( node[x].second == 0 )? 1: -1 ) );
					q.push( std::make_pair( y, x ) );
					break;
				}
			}
		}

		while( !q.empty() ) {
			auto [cur, pre] = q.front(); q.pop();
			ci32 dx = node[cur].first - node[pre].first;
			ci32 dy = node[cur].second - node[pre].second;
			for( auto &x: p[cur] ) {
				if( node[x].first != -1 ) 
					continue;
				node[x] = std::make_pair( node[cur].first + dx, node[cur].second + dy );
				q.push( std::make_pair( x, cur ) );
			}
		}

	}// }}}

	{// {{{
		std::vector<i32> xs[N], ys[N];
		for( int i = 0; i < n * n; i ++ ) {
			//printf( "%d %d %d\n", i + 1, node[i].first, node[i].second );
			id[ node[i].first ][ node[i].second ] = i;
			if( has[i] ) {
				xs[ node[i].first ].push_back(node[i].second);
				ys[ node[i].second ].push_back(node[i].first);
			}
		}

		for( int i = 0; i < n; i ++ ) {
			{
				std::sort( xs[i].begin(), xs[i].end() );
				i32 p0 = 0;
				i32 s0 = xs[i].size();
				i64 tot = 0;
				i64 pre1 = 0, suf1 = 0;
				i64 pre0 = 0, suf0 = 0;
				for( auto &p: xs[i] ) {
					tot += p * p;
					suf1 += p;
					suf0 ++;
				}
				for( int j = 0; j < n; j ++ ) {
					res[i][j] += tot;
					while( s0 < p0 && xs[i][s0] <= j ) {
						suf0 --;
						pre0 ++;
					}
					tot += 2LL * pre1 - pre0;
					tot -= 2LL * suf1 - suf0;
					pre1 += pre0; suf1 -= suf0;
				}
			}
		}
		for( int i = 0; i < n; i ++ ) {
			{
				std::sort( ys[i].begin(), ys[i].end() );
				i32 p0 = 0;
				i32 s0 = ys[i].size();
				i64 tot = 0;
				i64 pre1 = 0, suf1 = 0;
				i64 pre0 = 0, suf0 = 0;
				for( auto &p: ys[i] ) {
					tot += p * p;
					suf1 += p;
					suf0 ++;
				}
				for( int j = 0; j < n; j ++ ) {
					res[j][i] += tot;
					while( s0 < p0 && ys[i][s0] <= j ) {
						suf0 --;
						pre0 ++;
					}
					tot += 2LL * pre1 - pre0;
					tot -= 2LL * suf1 - suf0;
					pre1 += pre0; suf1 -= suf0;
				}
			}
		}

		bool flag = false;
		i64 max = 0, min = ( 1LL << 62 );
		for( int i = 0; i < n; i ++ ) {
			for( int j = 0; j < n; j ++ ) {
				if( has[ id[i][j] ] ) {
					//printf( "%d ", res[i][j] );
					flag = true;
					chk_Min( min, res[i][j] );
					chk_Max( max, res[i][j] );
				}
			}
			// printf( "\n" );
		}
		if( !flag ) 
			printf( "0 0\n" );
		else
			printf( "%lld %lld\n", min, max );
	}// }}}
}
