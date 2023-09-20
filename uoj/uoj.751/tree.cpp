/*
 * tree.cpp
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

#include <array>
#include <queue>
#include <vector>
#include <algorithm>

#include "tree.h"

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

int lowbit( cint cur ) { return cur & ( -cur ); }
int full_pow( cint cur ) { return 1 << cur; }
bool chk_pos( cint cur, cint k ) { return full_pow(k) & cur; }

const int N = 2e5 + 1e4;
const int Q = 22;

std::vector<std::pair<int, int>> solve( cint n ) {
	cint q = ( n <= 2000 )? 14: 20;

	std::vector<int> masks;

	{
		std::vector<int> size( full_pow(q) );
		for( int i = 1; i < full_pow(q); i ++ ) {
			size[i] = size[ i - lowbit(i) ] + 1;
			if( size[i] == ( q >> 1 ) ) {
				masks.push_back(i);
			}
		}
	}

	std::vector<std::vector<int>> res[Q];
	std::vector<int> size[Q], la[Q];
	std::vector<int> cnt(n);
	static int id[Q][N]; memset( id, 0, sizeof(id) );
	for( int i = 0; i < q; i ++ ) {
		std::vector<int> ask;
		for( int j = 0; j < n - 1; j ++ ) {
			if( chk_pos( masks[j], i ) ) 
				ask.push_back(1);
			else
				ask.push_back(0);

		}
		res[i] = query(ask);
		la[i].resize( res[i].size() );
		for( auto &x: res[i] ) {
			if( x.size() == 1 ) 
				cnt[ x[0] ] ++;
			size[i].push_back( x.size() );

			cint cur = size[i].size() - 1;
			for( auto &y: x ) {
				id[i][y] = cur;
			}
		}
	}

	std::queue<int> cq;
	for( int i = 0; i < n; i ++ ) {
		if( cnt[i] == ( q >> 1 ) )
			cq.push(i);
	}

	std::vector<int> idx( n + 1 );
	{/*{{{*/
		int tot = 1;
		while( !cq.empty() ) {
			cint cur = cq.front(); cq.pop();
			idx[cur] = tot;	/* mp[tot] = cur; */ tot ++;
			for( int i = 0; i < q; i ++ ) {
				int &csize = size[i][ id[i][cur] ];
				csize --;
				if( csize == 1 ) {
					for( auto &x: res[i][ id[i][cur] ] ) {
						if( idx[x] == 0 ) {
							cnt[x] ++;
							if( cnt[x] == ( q >> 1 ) )
								cq.push(x);
							break;
						}
					}
				}
				if( csize == 0 ) 
					la[i][ id[i][cur] ] = cur;
			}
		}
	}/*}}}*/

	std::vector<std::pair<int,int>> ans;
	for( int i = 0; i < n; i ++ ) {
		int cur = -1;
		for( int j = 0; j < q; j ++ ) {
			if( la[j][ id[j][i] ] == i ) 
				continue;
			if( cur == -1 || idx[cur] > idx[ la[j][ id[j][i] ] ] )
				cur = la[j][ id[j][i] ];
		}
		if( cur != -1 )
			ans.push_back( std::make_pair( cur, i ) );
	}

	return ans;
}
