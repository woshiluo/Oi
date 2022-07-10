/*
 * d.cpp
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

#include <stack>
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

const int N = 3e5 + 1e4;

int a[N], pos[N], fmin[N], fmax[N], to[N];

int main() {
#ifdef woshiluo
	freopen( "d.in", "r", stdin );
	freopen( "d.out", "w", stdout );
#endif
	int T = read<int>();
	while( T -- ) {
		cint n = read<int>();
		for( int i = 1; i <= n; i ++ ) {
			to[i] = i + 1;
			fmin[i] = fmax[i] = n;

			a[i] = read<int>();
			pos[ a[i] ] = i;
		}

		{/*{{{*/
			std::stack<int> st;
			for( int i = 1; i <= n; i ++ ) {
				while( !st.empty() && a[ st.top() ] < a[i] ) {
					fmax[ st.top() ] = i - 1; st.pop();
				}
				st.push(i);
			}
		}/*}}}*/
		{/*{{{*/
			std::stack<int> st;
			for( int i = 1; i <= n; i ++ ) {
				while( !st.empty() && a[ st.top() ] > a[i] ) {
					fmin[ st.top() ] = i - 1; st.pop();
				}
				st.push(i);
			}
		}/*}}}*/

		{
			std::vector<int> st;
			for( int i = n; i >= 1; i -- ) {
				while( !st.empty() && a[i] > a[ st.back() ] ) {
					st.pop_back();
				}
				st.push_back(i);

				cint gol = fmin[i];
				int left = 0, rig = st.size() - 1, res = 0;
				while( left <= rig ) {
					cint mid = ( left + rig ) >> 1;
					if( st[mid] <= gol ) {
						res = st[mid];
						rig = mid - 1;
					}
					else 
						left = mid + 1;
				}
				chk_Max( to[i], res );
			}
		}
		{
			std::vector<int> st;
			for( int i = n; i >= 1; i -- ) {
				while( !st.empty() && a[i] < a[ st.back() ] ) {
					st.pop_back();
				}
				st.push_back(i);

				cint gol = fmax[i];
				int left = 0, rig = st.size() - 1, res = 0;
				while( left <= rig ) {
					cint mid = ( left + rig ) >> 1;
					if( st[mid] <= gol ) {
						res = st[mid];
						rig = mid - 1;
					}
					else 
						left = mid + 1;
				}
				chk_Max( to[i], res );
			}
		}
		int cur = 1, res = 0;
		while( cur != n ) {
			cur = to[cur];
			res ++;
		}
		printf( "%d\n", res );
	}
}
