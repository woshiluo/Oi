/*
 * e.cpp 2023-08-26
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

#include <map>
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

const int mod = 998244353;

struct ModInt {/*{{{*/
	int cur;
	ModInt( ll _cur = 0 ) { cur = ( ( ( _cur % mod ) + mod ) % mod ); }

	inline ModInt operator+ ( const ModInt &b ) const { return ( cur + b.cur ) % mod; }
	inline ModInt operator- ( const ModInt &b ) const { return ( ( ( cur - b.cur ) % mod ) + mod ) % mod; }
	inline ModInt operator* ( const ModInt &b ) const { return ( 1LL * cur * b.cur ) % mod; }
	inline ModInt operator/ ( const ModInt &b ) const { return ( 1LL * cur * pow( b, mod - 2 ).cur ) % mod; }

	inline void operator+= ( const ModInt &b ) { (*this) = (*this) + b; }
	inline void operator-= ( const ModInt &b ) { (*this) = (*this) - b; }
	inline void operator*= ( const ModInt &b ) { (*this) = (*this) * b; }
	inline void operator/= ( const ModInt &b ) { (*this) = (*this) / b; }

	inline void output( const char end = '\n' ) { printf( "%d%c", cur, end ); }
};/*}}}*/

bool chk_pos( cint x, cint pos ) { return ( x >> pos ) & 1; }

const int MAX_POS = 30;

struct Trie {/*{{{*/
	struct Node {
		int cnt, sum;
		Node *son[2];

		Node( cint _cnt = 0, cint _sum = 0 ) { 
			cnt = _cnt; sum = _sum; 
			son[0] = son[1] = 0;
		}
		Node* get_son( cint k ) {
			if( son[k] ) 
				return son[k];
			else {
				son[k] = new Node();
				return son[k];
			}
		}
		void push_up() { 
			sum = get_son(0) -> sum + get_son(1) -> sum + cnt; 
		}
	} *rt;

	Trie() {
		rt = new Node();
	}

	void destroy( Node *cur ) {
		if( cur -> son[0] )
			destroy( cur -> son[0] );
		if( cur -> son[1] )
			destroy( cur -> son[1] );
		delete cur;
	}
	~Trie() { destroy(rt); }

	// TODO: recheck
	ll insert( Node *cur, cint x, cint pos, cint vaild ) {
		if( pos == 0 ) {
			cur -> cnt ++;
			cur -> push_up();
			return 0;
		}
		bool k = chk_pos( x, pos - 1 );
		ll res = insert( cur -> get_son(k), x, pos - 1, vaild + k );
		cur -> push_up();
		res += 1LL * ( cur -> get_son( k ^ 1 ) -> sum ) * vaild;
		return res;
	}
	ll insert( cint cur ) { 
		return insert( rt, cur, MAX_POS, 0 ); 
	}
};/*}}}*/

int main() {
#ifdef woshiluo
	freopen( "e.in", "r", stdin );
	freopen( "e.out", "w", stdout );
#endif

	int T = read<int>();
	
	while( T -- ) {
		cint n = read<int>();
		Trie trie;
		std::map<int, int> mp;
		ModInt sum_p = 0;
		for( int i = 1; i <= n; i ++ ) {
			cint cur = read<int>();
			mp[cur] ++;
			sum_p += trie.insert(cur) * 2;
		}
		ModInt ans = sum_p;
		ll tot = 1LL * n * ( n - 1 ) / 2LL;
		for( auto &pair: mp ) {
			cint x = pair.first;
			cint y = pair.second;
			tot -= 1LL * y * ( y - 1 ) / 2LL;
			cint bit_len = __builtin_popcount(x);
			if( bit_len == 0 ) 
				ans += 1LL * y * y;
			else if( bit_len == 1 ) 
				ans += 2LL * y * y;
			else {
				ans += 1LL * bit_len * y * y;
				ans += 1LL * y * y;
			}
		}
		ans += 3LL * tot;
		ModInt p = 1LL * n * n;
		( ans / p ).output();
	}
}
