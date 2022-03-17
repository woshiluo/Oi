/*
 * f.cpp
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

const int N = 110;

std::map<int, int> mp[N];

int main() {
	int n = read<int>();
	for( int i = 1; i <= n; i ++ ) {
		for( int j = 1; j <= n; j ++ ) {
			mp[i][ read<int>() ] ++;
		}
	}

	std::vector<std::vector<int>> ans;
	// to dev
	for( int k = 1; ; k ++ ) {
		bool flag = false;
		std::vector<int> res;
		res.resize(n);
		int st = -1;
		for( int i = 1; i <= n; i ++ ) {
			for( auto &node: mp[i] ) {
				if( node.second > 1 ) {
					if( st == -1 ) 
						st = i;
					flag = true;
					mp[ (i + 1 > n)? 1: i + 1 ][ node.first ] ++;
					res[ i - 1 ] = ( node.first );
					node.second --;
					break;
				}
			}
		}
		for( int i = 1; i < st; i ++ ) {
			for( auto &node: mp[i] ) {
				if( node.second > 1 ) {
					if( st == -1 ) 
						st = i;
					flag = true;
					mp[ (i + 1 > n)? 1: i + 1 ][ node.first ] ++;
					res[ i - 1 ] = ( node.first );
					node.second --;
					break;
				}
			}
		}
		if( !flag )
			break;
		ans.push_back(res);
	}

	for( int j = 1; j < n; j ++ ) {
		for( int k = 0; k < j; k ++ ) {
			std::vector<int> res;
			for( int i = 1; i <= n; i ++ ) {
				int p = i + j - k;
				if( p > n ) 
					p -= n;
				res.push_back(p);
			}
			ans.push_back(res);
		}
	}

	printf( "%ld\n", ans.size() );
	for( auto res: ans ) {
		for( auto node: res ) {
			printf( "%d ", node );
		}
		printf( "\n" );
	}
}
