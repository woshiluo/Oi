/*
 * a.cpp
 * Copyright (C) 2021 Woshiluo Luo <woshiluo.luo@outlook.com>
 *
 * 「Two roads diverged in a wood,and I—
 * I took the one less traveled by,
 * And that has made all the difference.」
 *
 * Distributed under terms of the GNU AGPLv3+ license.
 */

#include <cstdio>
#include <cstdlib>

#include <map>
#include <vector>

typedef long long ll;

inline bool is_digit( const char cur ) { return cur >= '0' && cur <= '9'; }/*{{{*/
template <class T>
T read() {
	T res = 0, k = 1; char x = getchar();
	for( ; !is_digit(x); x = getchar() )
		if( x == '-' ) 
			k = -1;
	for( ; is_digit(x); x = getchar() ) 
		res = res * 10 + ( x - '0' );
	return res * k;
}/*}}}*/

ll gcd( ll a, ll b ) { return b? gcd( b, a % b ): a; }
ll lcm( ll a, ll b ) { return a / gcd( a, b ) * b; }

namespace sub1 {
	inline void check( std::vector<int> &a, int n ) {
		if( a.size() != n ) 
			return ;
		ll res = 1, sum = 0;
		for( auto &x: a ) {
			res = lcm( res, x );
			sum += x;
		}
		if( res != sum ) 
			std::exit(-1);
		printf( "%d\n", n );
	}
	void calc( int n ) {
		if( n == 1 ) {
			printf( "%d", 1 );
			return ;
		}
		if( n == 2 ) {
			printf( "%d", -1 );
			return ;
		}
		int tn = n - ( ( n % 2 ) == 0 );
		std::vector<int> a;
		for( int i = 1; i <= tn - 2; i ++ ) 
			a.push_back(1);
		a.push_back(2); a.push_back(tn);
		if( !( n & 1 ) ) {
			for( auto &x: a ) 
				x *= 4;
			a[0] = 2; a.push_back(2);
		}
		for( auto x: a ) 
			printf( "%d ", x );
	}
}

namespace sub2 {
	const int LIM = 3100;
	struct Node {
		int depth, st;
		ll sum, res;

		Node operator+ ( const int &b ) const { 
			Node ans;
			ans.sum = sum + b; ans.res = lcm( res, b );
			ans.depth = depth + 1; ans.st = b + 1;
			return ans;
		}
		void operator+= ( const int &b ) { 
			sum += b; res = lcm( res, b );
			depth += 1; st = b + 1;
		}
		std::vector<ll> to_array() const { return { depth, st, sum, res }; }
		bool operator< ( const Node &b ) const {
			std::vector<ll> aa = this -> to_array(), ba = b.to_array();
			for( int i = 0; i < 4; i ++ ) {
				if( aa[i] == ba[i] ) 
					continue;
				return aa[i] < ba[i];
			}
			return aa[3] < ba[3];
		} 
	};

	const int N = 60;
	int n, ans[N];
	std::map<Node, bool> mp;
	void print() {
		for( int i = 0; i < n; i ++ ) 
			printf( "%d ", ans[i] );
		std::exit(0);
		return ;
	}
	void dfs( Node cur ) {
		if( cur.depth == n ) {
			if( cur.res == cur.sum )
				print();
			return ;
		} 
		if( mp.count(cur) ) 
			return ;
		mp[cur] = true;
		for( int i = cur.st; i < LIM; i ++ ) {
			ans[ cur.depth ] = i;
			dfs( cur + i );
		}
	}
	void calc( int _n ) {
		n = _n;
		if( n == 1 ) {
			printf( "%d", 1 );
			return ;
		}
		if( n == 2 ) {
			printf( "%d", -1 );
			return ;
		}
		dfs( (Node) { 0, 1, 0, 1 } );
		printf( "%d", -1 );
	}
}

int main() {
#ifdef woshiluo
	freopen( "a.in", "r", stdin );
	freopen( "a.out", "w", stdout );
#endif
	int n, t;
	n = read<int>(); t = read<int>();
	if( t == 1 ) 
		sub1::calc(n);
	else 
		sub2::calc(n);
}
