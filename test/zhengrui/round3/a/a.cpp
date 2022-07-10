/*
 * a.cpp
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

#include <vector>
#include <algorithm>

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

ll full_pow( ll a ) { return 1LL << a; }

int main() {
#ifdef woshiluo
	freopen( "a.in", "r", stdin );
	freopen( "a.out", "w", stdout );
#endif
	int T = read<int>();
	while( T -- ) {
		ll a = read<ll>();
		std::vector<int> pos[2], bpos[2];
		int bit = 0;
		while( a ) {
			if( a & 1LL ) 
				pos[ bit & 1 ].push_back(bit);
			a >>= 1LL;
			bit ++;
		}
		std::vector<ll> ans;
		{
			ll res = 0;
			while( pos[0].size() >= 3 ) {
				for( int i = 0; i < 3; i ++ ) {
					res |= full_pow( pos[0].back() );
					bpos[0].push_back( pos[0].back() );
					pos[0].pop_back();
				}
			}
			while( pos[1].size() >= 3 ) {
				for( int i = 0; i < 3; i ++ ) {
					res |= full_pow( pos[1].back() );
					bpos[1].push_back( pos[1].back() );
					pos[1].pop_back();
				}
			}
			if( res != 0 )
				ans.push_back(res);
		}

		// brute for end
		if( pos[0].size() + pos[1].size() != 0 ) {
			if( pos[0].size() > pos[1].size() ) {
				std::swap( pos[0], pos[1] );
				std::swap( bpos[0], bpos[1] );
			}
			if( ( pos[0].size() == 0 && bpos[0].size() == 0 ) || ( pos[1].size() == 0 && bpos[1].size() == 0 ) ) {
				if( pos[1].size() + bpos[1].size() >= 3 ) {
					{
						ll res = 0;
						if( pos[1].size() == 2 ) 
							res = full_pow(pos[1][0]) | full_pow(pos[1][1]) | full_pow(bpos[1][0]);
						if( pos[1].size() == 1 ) 
							res = full_pow(pos[1][0]) | full_pow(bpos[1][0]) | full_pow(bpos[1][1]);
						ans.push_back(res);
					}
					printf( "%lu ", ans.size() );
					for( auto &res: ans ) 
						printf( "%lld ", res );
					printf( "\n" );
					continue;
				}
				printf( "-1\n" );
				continue;
			}
			bool fill = false;
			while( !bpos[0].empty() && pos[0].size() < pos[1].size() ) {
				fill = true;
				pos[0].push_back( bpos[0].back() );
				bpos[0].pop_back();
			}

			ll base = 0;
			for( auto &p: pos[0] ) 
				base |= full_pow(p);

			// fill pos[1] with circle
			// TODO: need?
			{
				int p = 0;
				while( pos[1].size() % pos[0].size() != 0 ) {
					pos[1].push_back( pos[1][p] );
					p ++;
				}
			}
			const int s0 = pos[0].size();
			const int s1 = pos[1].size();
			for( int from = 0; from < s1; from += s0 ) {
				ll res = base;
				for( int i = from; i < from + s0; i ++ ) {
					res |= full_pow(pos[1][i]);
				}
				if( ans.size() == 0 || fill ) {
					ans.push_back(res);
					fill = true;
				}
				else {
					ans[0] |= res;
					fill = true;
				}
			}
		}
		printf( "%lu ", ans.size() );
		for( auto &res: ans ) 
			printf( "%lld ", res );
		printf( "\n" );
	}
}
