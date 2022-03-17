/*
 * calc.cpp
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

const int N = 1e6 + 1e4;

int a[N], b[N];
int sum_a[N], sum_b[N];

int main() {
	freopen( "calc.in", "r", stdin );
	freopen( "calc.out", "w", stdout );

	int n = read<int>();
	std::vector<int> nums;
	for( int i = 1;  i <= n; i++ ) {
		a[i] = read<int>();
		nums.push_back( a[i] );
	}
	for( int i = 1;  i <= n; i++ ) {
		b[i] = read<int>();
		nums.push_back( b[i] );
	}
	nums.push_back( (int)(1e9) );
	std::sort( nums.begin(), nums.end() );
	nums.erase( std::unique( nums.begin(), nums.end() ), nums.end() );
	for( int i = 1; i <= n; i ++ ) {
		const int pa = std::lower_bound( nums.begin(), nums.end(), a[i] ) - nums.begin() + 1;
		const int pb = std::lower_bound( nums.begin(), nums.end(), b[i] ) - nums.begin() + 1;
		sum_a[pa] ++;
		sum_b[pb] ++;
	}

	int tot = nums.size();
	for( int i = 1; i <= tot; i ++ ) {
		sum_a[i] += sum_a[ i - 1 ];
		sum_b[i] += sum_b[ i - 1 ];
	}


	ll res = 0;
	auto get_sum = []( int sum[], int left, int rig ) { 
		if( left < 0 ) 
			return sum[rig];
		return sum[rig] - sum[ left - 1 ]; 
	};
	for( int j = 1; j <= tot; j ++ ) {
		const int num = nums[ j - 1 ];
		for( int i = 0; 1LL * i * i <= (int)(1e7); i ++ ) {
			const int from = i * i;
			const int to = pow( i + 1, 2 ) - 1;
			{
				const int st = std::lower_bound( nums.begin(), nums.end(), from + num ) - nums.begin() + 1;
				const int ed = std::upper_bound( nums.begin(), nums.end(), to + num ) - nums.begin() + 1 - 1;
				res += 1LL * get_sum( sum_a, st, ed ) * get_sum( sum_b, j, j ) * i;
				res += 1LL * get_sum( sum_b, st, ed ) * get_sum( sum_a, j, j ) * i;
			}
			{
				const int st = std::lower_bound( nums.begin(), nums.end(), from + num ) - nums.begin() + 1;
				const int ed = std::upper_bound( nums.begin(), nums.end(), to + num ) - nums.begin() + 1 - 1;
				res += 1LL * get_sum( sum_a, st, ed ) * get_sum( sum_b, j, j ) * i;
				res += 1LL * get_sum( sum_b, st, ed ) * get_sum( sum_a, j, j ) * i;
			}
		}
	}

	printf( "%lld\n", res >> 1LL );

	fclose( stdin );
	fclose( stdout );
	return 0;
}
