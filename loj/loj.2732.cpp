/*
 * loj.2732.cpp 2023-09-30
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

const int N = 1e6 + 1e5;

constexpr int lowbit( cint cur ) { return cur & ( -cur ); }
struct BinaryIndexTree {
	int n;
	int bit[N];
	void init( const int _n ) {
		n = _n;
		memset( bit, 0, sizeof( n + 1 ) );
	}
	void add( int cur, cint val ) {
		for( ; cur <= n; cur += lowbit(cur) ) 
			bit[cur] += val;
	}
	int query( int cur ) {
		if( cur == 0 ) 
			return 0;
		int res = 0;
		for( ; cur; cur -= lowbit(cur) ) 
			res += bit[cur];
		return res;
	}
	int sum( cint left, cint rig ) {
		return query(rig) - query( left - 1 );
	}
};

struct Op {
	int op;
	int x, y;
};

int main() {
#ifdef woshiluo
	freopen( "loj.2732.in", "r", stdin );
	freopen( "loj.2732.out", "w", stdout );
#endif
	cint n = read<int>();
	cint m = read<int>();
	
	BinaryIndexTree bit; bit.init( ( n + m ) * 2 );
	std::vector<int> a, nums;
	nums.push_back(0); nums.push_back(1); 
	a.push_back(0);
	for( int i = 1; i <= n; i ++ ) {
		a.push_back( read<int>() );
		nums.push_back( a.back() );
		nums.push_back( a.back() + 1 );
	}
	a.push_back(0);

	std::vector<Op> ops;
	for( int i = 1; i <= m; i ++) {
		cint op = read<int>();
		if( op == 1 ) {
			cint x = read<int>();
			ops.push_back( (Op) { op, x, 0 } );
		}
		else {
			cint x = read<int>();
			cint y = read<int>();
			ops.push_back( (Op) { op, x, y } );
			nums.push_back(y);
			nums.push_back( y + 1 );
		}
	}

	std::sort( nums.begin(), nums.end() );
	nums.erase( std::unique( nums.begin(), nums.end() ), nums.end() );
	auto find = [nums] ( cint cur ) { return std::lower_bound( nums.begin(), nums.end(), cur ) - nums.begin() + 1; }; 
	for( int i = 1; i <= n; i ++) 
		a[i] = find( a[i] );
	for( auto &op: ops ) 
		op.y = find( op.y );

	auto update = [&]( cint pos, cint val ) {
		cint left = a[pos - 1], rig = a[pos + 1];
		bit.add( Min(a[pos],rig) + 1, -1 );
		bit.add( Max(a[pos],rig) + 1, 1 );
		bit.add( Min(a[pos],left) + 1, -1 );
		bit.add( Max(a[pos],left) + 1, 1 );
		a[pos] = val;
		bit.add( Min(a[pos],rig) + 1, 1 );
		bit.add( Max(a[pos],rig) + 1, -1 );
		bit.add( Min(a[pos],left) + 1, 1 );
		bit.add( Max(a[pos],left) + 1, -1 );
	};

	for( int i = 1; i <= n + 1; i ++ ) {
		cint pos = i;
		cint left = a[pos - 1];
		bit.add( Min(a[pos],left) + 1, 1 );
		bit.add( Max(a[pos],left) + 1, -1 );
	}
	for( auto &op: ops ) {
		if( op.op == 1 ) {
			printf( "%d\n", bit.query( op.x ) >> 1 );
		}
		if( op.op == 2 ) {
			update( op.x, op.y );
		}
	}
}
