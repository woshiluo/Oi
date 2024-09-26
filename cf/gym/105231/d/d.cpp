/*
 * d.cpp 2024-09-13
 * Copyright (C) 2024 Woshiluo Luo <woshiluo.luo@outlook.com>
 *
 * 「Two roads diverged in a wood,and I—
 * I took the one less traveled by,
 * And that has made all the difference.」
 *
 * Distributed under terms of the GNU GNU AGPLv3+ license.
 */

#include <cmath>
#include <cstdio>
#include <cstdint>
#include <cstring>
#include <cstdlib>
#include <cinttypes>

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

const int N = 1e6 + 1e5;

std::vector<i32> primes;
bool not_primes[N];

void init() {
	not_primes[0] = not_primes[1] = true;
	for( int i = 2; i < N; i ++ ) {
		if( !not_primes[i] ) {
			primes.push_back(i);
		}
		for( auto &p: primes ) {
			if( 1LL * p * i >= N )
				break;
			not_primes[ p * i ] = true;
			if( i % p == 0 ) 
				break;
		}
	}
}

const int K = 21;

const i32 mod = 998244353;

template<i32 P>
struct ModInt {// {{{
    i32 x;
    constexpr ModInt() : x {0} {}
    constexpr ModInt(i64 _x) : x {norm(_x % get_mod())} {}
    
    static i32 mod;

    constexpr static i32 get_mod() { return P > 0? P: mod; }
    constexpr static void set_mod(i32 _mod) { mod = _mod; }

    static constexpr i32 norm(i32 x) {
        if (x < 0) {
            x += get_mod();
        }
        if (x >= get_mod()) {
            x -= get_mod();
        }
        return x;
    }
    constexpr i32 val() const { return x; }
    constexpr ModInt operator-() const {
        ModInt res;
        res.x = norm(get_mod() - x);
        return res;
    }

    constexpr ModInt inv() const { return pow(*this, get_mod() - 2); }

    constexpr ModInt& operator*=(const ModInt &rhs) & { x = (((i64)x) * rhs.x) % get_mod(); return *this; }
    constexpr ModInt& operator+=(const ModInt &rhs) & { x = norm(x + rhs.x); return *this; }
    constexpr ModInt& operator-=(const ModInt rhs) & { x = norm(x - rhs.x); return *this; }
    constexpr ModInt& operator/=(const ModInt rhs) & { return *this *= rhs.inv(); }

    friend constexpr ModInt operator*(const ModInt& lhs, const ModInt& rhs) { ModInt res = lhs; res *= rhs; return res; }
    friend constexpr ModInt operator+(const ModInt& lhs, const ModInt& rhs) { ModInt res = lhs; res += rhs; return res; }
    friend constexpr ModInt operator-(const ModInt& lhs, const ModInt& rhs) { ModInt res = lhs; res -= rhs; return res; }
    friend constexpr ModInt operator/(const ModInt& lhs, const ModInt& rhs) { ModInt res = lhs; res /= rhs; return res; }

    friend constexpr bool operator==(const ModInt& lhs, const ModInt& rhs) { return lhs.val() == rhs.val(); }
    friend constexpr bool operator!=(const ModInt& lhs, const ModInt& rhs) { return lhs.val() != rhs.val(); }
//    friend constexpr bool operator<(const ModInt& lhs, const ModInt& rhs) { return lhs.val() < rhs.val(); }
	void output( const char end = '\n' ) { printf( "%" PRId32 "%c", x, end ); }
};// }}} 

int main() {
#ifdef woshiluo
	freopen( "d.in", "r", stdin );
	freopen( "d.out", "w", stdout );
#endif

	init();
	ci32 psize = primes.size();
	i32 T = read<i32>();
	while( T -- ) {
		ci32 n = read<i32>();
		std::vector<std::pair<i32, i32>> list;
		for( int o = 1; o <= n; o ++ ) {
			i32 cur = read<i32>();
			ci32 sqrt = std::sqrt(cur) + 1;
			for( int i = 0; i < psize && cur != 1; i ++ ) {
				ci32 p = primes[i];
				if( p > sqrt ) 
					break;
				if( cur % p != 0 ) 
					continue;
				i32 cnt = 0;
				while( cur % p == 0 ) {
					cur /= p;
					cnt ++;
				}
				list.emplace_back( p, cnt );
			}
			if( cur != 1 ) 
				list.emplace_back( cur, 1 );
		}
		std::sort( list.begin(), list.end() );
		std::vector<ModInt<mod>> res( n + 1, 1 );
		i32 p1 = 0;
		i32 size = list.size();
		while( p1 < size ) {
			ci32 p = list[p1].first;
			std::vector<i32> l2;
			while( p1 < size && list[p1].first == p ) {
				l2.push_back(list[p1].second);
				p1 ++;
			}
			ci32 max_p = l2.back();
			std::vector<i32> pow_a( max_p + 1 );
			pow_a[0] = 1;
			for( int i = 1; i <= max_p; i ++ ) {
				pow_a[i] = pow_a[ i - 1 ] * p;
			}
			std::reverse( l2.begin(), l2.end() );
			l2.push_back(0);
			i32 pos = n + 1, lp = -1;
			for( auto &cp: l2 ) {
				pos --;
				if( lp != cp ) {
					if( lp != -1 )
						res[ pos + 1 ] *= pow_a[ lp - cp ];
					lp = cp;
				}
			}
		}
		ModInt<mod> sum = 0;
		for( int i = 1; i <= n; i ++ ) {
			res[i] *= res[ i - 1 ];
			sum += res[i];
		}
		sum.output();
	}

	return 0;
}
