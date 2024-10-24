/*
 * n.cpp 2024-10-20
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
#include <cinttypes>

#include <tuple>
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
	for (; isdigit(ch); ch = getchar()) sum = sum * 10 + ( ch - '0' );
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

const int N = 1024;

char buf[N];

enum Type { type_var, type_int };

struct Data {
	Type type;
	int data;
	bool is_neg;

	Data() {
		type = type_int;
		data = 0;
		is_neg = false;
	}
};

bool is_aplha( const char cur ) { return cur >= 'a' && cur <= 'z'; }

std::vector<Data> parse( const char str[] ) {
	std::vector<Data> data(3);
	ci32 len = strlen(str);
	int cur = 0;
	for( int i = 6; i < len; i ++ ) {
		if( str[i] == ',' ) {
			cur ++;
			continue;
		}
		if( str[i] == ')' ) {
			break;
		}
		if( str[i] == '-' ) {
			data[cur].is_neg = true;
			continue;
		}
		if( is_aplha( str[i] ) ) {
			data[cur].type = type_var;
			data[cur].data = str[i];
		}
		else {
			data[cur].type = type_int;
			data[cur].data *= 10;
			data[cur].data += ( str[i] - '0' );
		}
	}
	if( cur == 1 ) {
		data[2].type = type_int;
		data[2].data = 1;
	}
	for( int i = 0; i < 3; i ++ ) {
		if( data[i].is_neg && data[i].type == type_int ) {
			data[i].data *= -1;
		}
	}
	return data;
}

int var_data[512];

int main() {
#ifdef woshiluo
	freopen( "n.in", "r", stdin );
	freopen( "n.out", "w", stdout );
#endif

	fgets( buf, N, stdin );
	i32 var[2];
	std::vector<Data> range[2];
	{
		// readin for
		scanf("%s", buf );
		// readin loop var
		scanf("%s", buf );
		var[0] = buf[0];
		// readin in
		scanf("%s", buf );
		// readin range
		scanf("%s", buf );

		range[0] = parse(buf);
	}
	{
		// readin for
		scanf("%s", buf );
		// readin loop var
		scanf("%s", buf );
		var[1] = buf[0];
		// readin in
		scanf("%s", buf );
		// readin range
		scanf("%s", buf );

		range[1] = parse(buf);
	}
	
	const auto get = [&]( const auto &cur ) -> i32 {
		if( cur.type == type_int ) {
			return cur.data;
		}
		else {
			return var_data[cur.data];
		}
	};
	const auto init_get = [&]( ci32 current_var, const auto &cur ) -> i32 {
		var_data[current_var] = get(cur);
		return var_data[current_var];
	};

	const auto check = [&]( ci32 val, const auto &cur ) -> bool {
		if( get(cur[2]) > 0 ) 
			return val < get(cur[1]);
		else 
			return val > get(cur[1]);
	};

	const auto update = [&](const auto &cur, i32 &val, ci32 current_var) {
		val += get(cur[2]);
		var_data[current_var] = val;
	};


	i64 res = 0;
	for( int i = init_get(var[0], range[0][0]); check( i, range[0] ); update(range[0], i, var[0]) ) {
		i32 st = get( range[1][0] );
		i32 ed = get( range[1][1] );
		i32 c = get( range[1][2] );
		if( c < 0 ) {
			if( st <= ed )
				continue;
			ed ++;
			i32 len = ( ed - st ) / c + 1;
			i32 red = ( st + c * ( len - 1 ) );
			res += 1LL * ( st + red ) * len / 2LL;
		}
		else {
			if( st >= ed ) 
				continue;
			ed --;
			i32 len = ( ed - st ) / c + 1;
			i32 red = ( st + c * ( len - 1 ) );
			res += 1LL * ( st + red ) * len / 2LL;
		}
	}
	printf( "%" PRId64 "\n", res );
}
