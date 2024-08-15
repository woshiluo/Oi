/*
 * b.cpp 2024-08-15
 * Copyright (C) 2024 Woshiluo Luo <woshiluo.luo@outlook.com>
 *
 * 「Two roads diverged in a wood,and I—
 * I took the one less traveled by,
 * And that has made all the difference.」
 *
 * Distributed under terms of the GNU GNU AGPLv3+ license.
 */

#include <cstdio>
#include <cstdint>
#include <cstring>
#include <cstdlib>

#include <set>
#include <map>
#include <string>
#include <vector>
#include <algorithm>

using i32 = int32_t;
using u32 = uint32_t;
using ci32 = const int32_t;
using cu32 = const uint32_t;

using i64 = int64_t;
using u64 = uint64_t;
using ci64 = const int64_t;
using cu64 = const uint64_t;

inline bool isdigit( const char cur ) { return cur >= '0' && cur <= '9'; }/*{{{*/
template <class T> 
constexpr T Max( T a, T b ) { return a > b? a: b; }
template <class T> 
constexpr T Min( T a, T b ) { return a < b? a: b; }
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
constexpr T pow( T a, i32 p ) {
	T res = 1;
	while( p ) {
		if( p & 1 ) 
			res = res * a;
		a = a * a;
		p >>= 1;
	}
	return res;
}/*}}}*/

struct Type {
	enum BaseType {
		Pair,
		Int,
		Double
	} type;
	Type *son[2];

	void print() {
		if( type == Pair ) {
			printf( "pair<" );
			son[0] -> print();
			printf( "," );
			son[1] -> print();
			printf( ">" );
		}
		if( type == Int ) 
			printf( "int" );
		if( type == Double ) 
			printf( "double" );
	}
};




const int N = 8196;

int pre[N];
std::set<std::pair<i32, i32>> set;
std::map<std::string, Type*> mp;
void create_type( int l, int r, char *buf, Type *cur ) {
	if( buf[l] == 'p' ) {
		ci32 split_pos = set.lower_bound( std::make_pair( pre[l] + 1, l ) ) -> second;
		cur -> type = Type::Pair;
		cur -> son[0] = new Type;
		cur -> son[1] = new Type;
		// pair<i
		// 012345
		create_type( l + 5, split_pos - 1, buf, cur -> son[0] );
		create_type( split_pos + 1, r - 1, buf, cur -> son[1] );
	}
	else {
		if( buf[l] == 'i' ) 
			cur -> type = Type::Int;
		if( buf[l] == 'd' ) 
			cur -> type = Type::Double;
	}
}

Type* get_value( Type *cur, const char *buf, ci32 l, ci32 r ) {
	if( r < l ) 
		return cur;
	// first.
	// 012345
	// second.
	// 0123456
	if( buf[l] == 'f' )
		return get_value( cur -> son[0], buf, l + 6, r );
	else 
		return get_value( cur -> son[1], buf, l + 7, r );
}

int main() {
#ifdef woshiluo
	freopen( "b.in", "r", stdin );
	freopen( "b.out", "w", stdout );
#endif

	ci32 n = read<i32>(); 
	ci32 q = read<i32>();
	for( int i = 1; i <= n; i ++ ) {
		static char buf[N];
		scanf( "%s", buf + 1 );
		set.clear();

		ci32 len = strlen( buf + 1 );
		for( int j = 1; j <= len; j ++ ) {
			pre[j] = pre[ j - 1 ];
			if( buf[j] == '<' )
				pre[j] ++;
			if( buf[j] == '>' )
				pre[j] --;
			if( buf[j] == ',' ) 
				set.insert( std::make_pair( pre[j], j ) );
		}

		Type *cur = new Type;
		create_type( 1, len, buf, cur );


		scanf( "%s", buf );
		buf[ strlen(buf) - 1 ] = 0;
		std::string tmp_str = buf;
		mp[tmp_str] = cur;
	}

	for( int _ = 1; _ <= q; _ ++ ) {
		static char buf[N];
		scanf( "%s", buf + 1 );
		ci32 len = strlen( buf + 1 );

		i32 fir_dot = 0;
		for( int i = 1; i <= len; i ++ ) {
			if( buf[i] == '.' ) {
				fir_dot = i;
				break;
			}
		}

		buf[fir_dot] = 0;

		std::string tmp_str = buf + 1;
		Type *cur = fir_dot == 0? mp[tmp_str]: get_value( mp[tmp_str], buf, fir_dot + 1, len );

		cur -> print();
		printf( "\n" );
	}

	return 0;
}
