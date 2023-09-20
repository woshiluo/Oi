/*
 * i.cpp
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

template <class T>
T aabs( T cur ) { return cur < 0? -cur: cur; }

const int N = 110;

struct Node { int x, y; };
struct CheckerBoard {
	int n, m, k;
	ll total_score;
	int col[N][N];
	int kind[N][N];
	// This array should only noticed that is one block was cleard by 3-combo
	bool vis[N][N];
	bool cleard[N][N];
	bool block_vis[N][N];

	std::vector<std::vector<int>> col_list;
	
	void try_clear( cint cx, cint cy, std::queue<Node> &q ) {/*{{{*/
		if( cx < 1 || cy < 1 || cx > n || cy > m ) 
			return ;
		if( col[cx][cy] != -1 && cleard[cx][cy] == false ) {
			q.push( (Node){ cx, cy } );
			cleard[cx][cy] = true;
		}
	}/*}}}*/

	void speical_clear( Node &cur, std::queue<Node> &q ) {/*{{{*/
		cint cur_kind = kind[ cur.x ][ cur.y ];
		cint cx = cur.x, cy = cur.y;
		if( cur_kind == 1 ) {
			for( int i = 1; i <= m; i ++ ) {
				try_clear( cx, i, q );
			}
		}
		if( cur_kind == 2 ) {
			for( int i = 1; i <= n; i ++ ) {
				try_clear( i, cy, q );
			}
		}
		if( cur_kind == 3 ) {
			for( int i = 1; i <= n; i ++ ) {
				try_clear( i, cy, q );
			}
			for( int i = 1; i <= m; i ++ ) {
				try_clear( cx, i, q );
			}
		}
		if( cur_kind == 4 ) {
			for( int i = cx - 1; i <= cx + 1; i ++ ) {
				for( int j = cy - 1; j <= cy + 1; j ++ ) {
					try_clear( i, j, q );
				}
			}
		}
		if( cur_kind == 5 ) {
			for( int i = cx - 2; i <= cx + 2; i ++ ) {
				for( int j = cy - 2; j <= cy + 2; j ++ ) {
					try_clear( i, j, q );
				}
			}
		}
		if( cur_kind == 6 ) {
			for( int i = 1; i <= n; i ++ ) {
				for( int j = 1; j <= m; j ++ ) {
					if( col[i][j] == col[cx][cy] ) 
						try_clear( i, j, q );
				}
			}
		}
	}/*}}}*/

	void make_down() {/*{{{*/
		for( int j = 1; j <= m; j ++ ) {
			int cx = n;
			for( int i = n; i >= 1; i -- ) {
				if( !cleard[i][j] && col[i][j] != -1 ) {
					col[cx][j] = col[i][j];
					kind[cx][j] = kind[i][j];
					cx --;
				}
			}
			for( int i = cx; i >= 1; i -- ) {
				col[i][j] = -1;
				kind[i][j] = 0;
			}
		}
	}/*}}}*/

	cint dx[4] = { 0, 0, +1, -1 };
	cint dy[4] = { +1, -1, 0, 0 };
	int dfs( cint x, cint y ) {/*{{{*/
		if( !vis[x][y] ) 
			return 0;
		if( block_vis[x][y] ) 
			return 0;
		block_vis[x][y] = true;
		int res = 1;
		for( int i = 0; i < 4; i ++ ) {
			cint nx = x + dx[i];
			cint ny = y + dy[i];
			if( nx < 1 || ny < 1 || nx > n || ny > m || col[nx][ny] != col[x][y] ) 
				continue;
			res += dfs( nx, ny );
		}

		return res;
	}/*}}}*/
	// Return destroy-score and compose-score
	ll iter( cint iter_time ) {/*{{{*/
		// init ( make down & clear the array )
		memset( vis, 0, sizeof(vis) );
		memset( cleard, 0, sizeof(cleard) );
		memset( block_vis, 0, sizeof(block_vis) );

		// scan for 3-combo
		for( int i = 1; i <= n; i ++ ) {
			for( int j = 1; j <= m; j ++ ) {
				if( col[i][j] == -1 ) 
					continue;
				if( j + 2 <= m && col[i][j] == col[i][ j + 1 ] && col[i][j] == col[i][ j + 2 ] )
					vis[i][j] = vis[i][ j + 1 ] = vis[i][ j + 2 ] = true;
				if( i + 2 <= n && col[i][j] == col[ i + 1 ][j] && col[i][j] == col[ i + 2 ][j] )
					vis[i][j] = vis[ i + 1 ][j] = vis[ i + 2 ][j] = true;
			}
		}

		// Scan for speical node
		std::queue<Node> q;
		for( int i = 1; i <= n; i ++ ) {
			for( int j = 1; j <= m; j ++ ) {
				if( vis[i][j] ) 
					 q.push( (Node) { i, j } );
				cleard[i][j] = vis[i][j];
			}
		}
		while( !q.empty() ) {
			Node cur = q.front(); q.pop();
			if( kind[ cur.x ][ cur.y ] ) {
				speical_clear( cur, q );
			}
		}

		// calc score
		ll ans = 0;
		for( int i = 1; i <= n; i ++ ) {
			for( int j = 1; j <= m; j ++ ) {
				if( cleard[i][j] )
					ans += 1LL * col[i][j] * iter_time;
				if( !block_vis[i][j] && vis[i][j] ) 
					ans += 1LL * 50 * pow( 1LL * ( dfs( i, j ) - 3 ), 2 );
			}
		}

		return ans;
	}/*}}}*/

	void swap( cint x1, cint y1, cint x2, cint y2 ) {/*{{{*/
		if( col[x1][y1] == -1 || col[x2][y2] == -1 ) 
			return ;
		std::swap( col[x1][y1], col[x2][y2] );
		std::swap( kind[x1][y1], kind[x2][y2] );
		int time = 1;
		std::vector<int> main_col;
		while(1) {
			ll res = iter(time);
			if( res == 0 )
				break;

			if( time == 1 ) {
				if( vis[x1][y1] ) 
					main_col.push_back( col[x1][y1] );
				if( vis[x2][y2] ) 
					main_col.push_back( col[x2][y2] );
			}
			make_down();

			total_score += res;
			time ++;
		}

		if( main_col.size() == 0 ) {
			std::swap( col[x1][y1], col[x2][y2] );
			std::swap( kind[x1][y1], kind[x2][y2] );
			return ;
		}

		total_score += 1LL * 80 * pow( time - 2, 2 );

		col_list.push_back(main_col);
	}/*}}}*/

	ll get_card_type( std::vector<int> &list ) {/*{{{*/
		std::map<int, int> mp;
		for( auto &x: list )
			mp[x] ++;
		std::vector<int> col2;
		int col3, col4, diff = mp.size();
		col3 = 0; col4 = 0;
		for( auto &pair: mp ) {
			if( pair.second == 2 )
				col2.push_back( pair.first );
			if( pair.second == 3 ) 
				col3 = pair.first;
			if( pair.second == 4 ) 
				col4 = pair.first;
		}

		ll res = 0;
		if( diff == 5 ) 
			res += 50 + ( mp.rbegin() -> first );
		if( col2.size() == 1 && diff == 4 ) 
			res += 100 + col2[0] * 2;
		if( col2.size() == 2 && diff == 3 ) 
			res += 200 + Max( col2[0], col2[1] ) * 2 + Min( col2[0], col2[1] );
		if( col3 != 0 && diff == 3 ) 
			res += 300 + col3 * 3;
		if( diff == 2 && col3 != 0 && col2.size() == 1 ) 
			res += 500 + col3 * 3 + col2[0];
		if( diff == 2 && col4 != 0 ) 
			res += 750 + col4 * 5;
		if( diff == 1 )
			res += 1000 + list[0] * 10;

		return res;
	}/*}}}*/

	int full_pow( cint cur ) { return 1 << cur; }
	bool chk_pos( cint cur, cint p ) { return cur & full_pow(p); }
	void end( cint q ) {/*{{{*/
		// card-type score
		{
			cint size = col_list.size();
			for( int i = 0; i + 4 < size; i += 5 ) {
				ll res = 0;
				for( int st = 0; st < full_pow(5); st ++ ) {
					std::vector<int> list;
					for( int j = 0; j < 5; j ++ ) {
						if( chk_pos( st, j ) && col_list[ i + j ].size() == 2 ) 
							list.push_back( col_list[ i + j ][1] );
						else
							list.push_back( col_list[ i + j ][0] );
					}
					chk_Max( res, get_card_type(list) );
				}
				total_score += res;
			}
		}
		// final-score
		
		// all valid
		if( (int)col_list.size() == q ) {
			total_score += 1000;
		}

		// all cleard
		bool flag = true;
		for( int i = 1; i <= n; i ++ ) {
			for( int j = 1; j <= m; j ++ ) {
				if( col[i][j] != -1 ) 
					flag = false;
			}
		}
		if( flag ) 
			total_score += 10000;

		printf( "%lld\n", total_score );
	}/*}}}*/
} cb;

int main() {
#ifdef woshiluo
	freopen( "i.in", "r", stdin );
	freopen( "i.out", "w", stdout );
#endif
	cint n = read<int>();
	cint m = read<int>();
	cint k = read<int>();
	cint q = read<int>();

	cb.n = n; cb.m = m; cb.k = k;
	for( int i = 1; i <= n; i ++ ) {
		for( int j = 1; j <= m; j ++ ) {
			cb.col[i][j] = read<int>();
		}
	}
	for( int i = 1; i <= n; i ++ ) {
		for( int j = 1; j <= m; j ++ ) {
			cb.kind[i][j] = read<int>();
		}
	}

	for( int i = 1; i <= q; i ++ ) {
		cint x1 = read<int>();
		cint y1 = read<int>();
		cint x2 = read<int>();
		cint y2 = read<int>();
		if( aabs( x1 - x2 ) + aabs( y1 - y2 ) != 1 ) 
			continue;
		cb.swap( x1, y1, x2, y2 );
	}

	cb.end(q);
}
