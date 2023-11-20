/*
 * a1.cpp 2023-10-22
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

// 1 5 
// 3 8

ll work( std::vector<int> &a, std::vector<int> &b, std::vector<int> &nums ) {
	cint n = a.size();
	int res = 0, paired = 0;
	std::vector<int> nxt(n);
	std::vector<bool> vis(n, true);
	{
		int p1 = 0, p2 = 0;
		int mn = n;
		while( p1 < mn && p2 < n ) {
			if( a[p1] < b[p2] ) {
				p1 ++;
				p2 ++;
			}
			else {
				p2 ++;
				mn --;
				res ++;
			}
		}
		res += Min( ( mn - p1 ), ( n - p2 ) );
	}
	{
		int p1 = 1, p2 = 0;
		while( p1 < n && p2 < n ) {
			if( a[p1] < b[p2] ) {
				nxt[p1] = p2;
				vis[p2] = false;
				paired ++;
				p1 ++;
				p2 ++;
			}
			else {
				p2 ++;
			}
		}
	}
	std::vector<bool> avi = vis;
	for( int i = n - 2; i >= 0; i -- ) {
		avi[i] = ( avi[ i + 1 ] || avi[i] );
	}
	cint size = nums.size();
	ll ans = 0;
	for( int i = 1; i < size - 1; i ++ ) {
		cint left = std::upper_bound( b.begin(), b.end(), nums[i] ) - b.begin();
		if( left < n && avi[left] ) 
			ans += 1LL * ( nums[ i + 1 ] - nums[i] ) * ( n - paired - 1 );
		else
			ans += 1LL * ( nums[ i + 1 ] - nums[i] ) * ( n - paired );
	}
	return ans;
}

int main() {
#ifdef woshiluo
	freopen( "a2.in", "r", stdin );
	freopen( "a2.out", "w", stdout );
#endif

	int T = read<int>();
	while( T -- ) {
		cint n = read<int>();
		cint m = read<int>();

		std::vector<int> a( n - 1 ), b ( n ), nums;
		nums.push_back(0);
		nums.push_back(1);
		nums.push_back( m + 1 );
		for( auto &x: a ) {
			x = read<int>();
			nums.push_back(x);
		}
		for( auto &x: b ) {
			x = read<int>();
			nums.push_back(x);
		}
		std::sort( nums.begin(), nums.end() );
		nums.erase( std::unique( nums.begin(), nums.end() ), nums.end() );
		while( nums.back() > m + 1 ) 
			nums.pop_back();
		std::sort( a.begin(), a.end() );
		a.insert( a.begin(), 1 );
		std::sort( b.begin(), b.end() );
		const ll ans = work( a, b, nums );
		printf( "%lld\n", ans );
	}
}
