/*
 * c.cpp 2024-05-31
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
T pow( T a, i32 p ) {
	T res = 1;
	while( p ) {
		if( p & 1 ) 
			res = res * a;
		a = a * a;
		p >>= 1;
	}
	return res;
}/*}}}*/

template <class T> 
T aabs( T cur ) { return cur < 0? -cur: cur; }

int main() {
#ifdef woshiluo
	freopen( "c.in", "r", stdin );
	freopen( "c.out", "w", stdout );
#endif

	i32 T = read<i32>();
	while( T -- ) {
		ci32 n = read<i32>();
		std::vector<i32> a(n), b(n, -1);
		for( auto &x: a ) {
			x = read<i32>();
		}
		int la = -1, la_pos = -1;
		bool flag = true;
		auto hi_bit = [&]( const int cur ) {
			for( int k = 30; k >= 0; k -- ) {
				if( ( cur >> k ) & 1 ) {
					return k + 1;
				}
			}
			return 0;
		};
		for( int i = 0; i < n; i ++ ) {
			if( la == -1 ) {
				if( a[i] == -1 ) 
					continue;
				else  {
					la = a[i];
					b[i] = a[i];
					la_pos = i;
				}
			}
			else {
				if( a[i] == -1 ) {
					continue;
				}
				else if( la_pos == i - 1 ) {
					if( a[i] == ( a[ i - 1 ] >> 1 ) || a[ i - 1 ] == ( a[i] >> 1 ) ) {
						b[i] = a[i];
						la = a[i];
						la_pos = i;
						continue;
					}

					flag = false;
					break;
				}
				else {
					b[i] = a[i];

					ci32 cur_len = hi_bit( a[i] );
					ci32 la_len = hi_bit( la );
					i32 times = i - la_pos;
					i32 cur = a[i], tmp = la;
					ci32 k = aabs( cur_len - la_len );
					times -= k;
					if( cur_len < la_len ) 
						tmp >>= k;
					else 
						cur >>= k;

					ci32 min_rewrite = hi_bit( cur ^ tmp );
					times -= min_rewrite * 2;

					if( min_rewrite == Min( cur_len, la_len ) ) {
						flag = false;
						break;
					}
					if( times < 0 ) {
						flag = false;
						break;
					}
					if( times & 1 ) {
						flag = false;
						break;
					}

					int cur_pos = la_pos + 1;
					if( cur_len < la_len ) {
						for( int j = 1; j <= k; j ++ ) {
							b[ cur_pos ] = b[ cur_pos - 1 ] >> 1;
							cur_pos ++;
						}
					}
					for( int j = 1; j <= min_rewrite; j ++ ) {
						b[ cur_pos ] = b[ cur_pos - 1 ] >> 1;
						cur_pos ++;
					}
					for( int j = 1; j <= times; j ++ ) {
						if( j & 1 ) 
							b[ cur_pos ] = b[ cur_pos - 1 ] << 1;
						else 
							b[ cur_pos ] = b[ cur_pos - 1 ] >> 1;
						cur_pos ++;
					}

					// rewind
					cur_pos = i - 1;
					for( int j = 1; j <= min_rewrite; j ++ ) {
						b[ cur_pos ] = b[ cur_pos + 1 ] >> 1;
						cur_pos --;
					}

					if( la_len < cur_len ) {
						for( int j = 1; j <= k; j ++ ) {
							b[ cur_pos ] = b[ cur_pos + 1 ] >> 1;
							cur_pos --;
						}
					}

					la = a[i];
					la_pos = i;
				}
			}
		}

		{
			int cur = -1;
			bool state = true;
			for( int i = 0; i < n; i ++ ) {
				if( b[i] == -1 && cur == -1 ) 
					continue;
				if( b[i] == -1 ) {
					if( state )
						b[i] = cur << 1;
					else 
						b[i] = cur >> 1;
					state ^= 1;
					cur = b[i];
				}
				else
					cur = b[i];
			}
		}
		{
			int cur = -1;
			bool state = true;
			for( int i = n - 1; i >= 0; i -- ) {
				if( b[i] == -1 && cur == -1 ) 
					continue;
				if( b[i] == -1 ) {
					if( state )
						b[i] = cur << 1;
					else 
						b[i] = cur >> 1;
					state ^= 1;
					cur = b[i];
				}
				else 
					cur = b[i];
			}
		}
		if( la == -1 ) {
			for( int i = 0; i < n; i ++ ) {
				if( i & 1 ) 
					b[i] = 1;
				else
					b[i] = 2;
			}
		}

		if( !flag ) 
			printf( "-1\n" );
		else  {
			for( auto &x: b ) 
				printf( "%d ", x );
			printf( "\n" );
		}
	}
}
