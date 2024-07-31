/*
 * 3803.cpp 2024-07-26
 * Copyright (C) 2024 Woshiluo Luo <woshiluo.luo@outlook.com>
 *
 * 「Two roads diverged in a wood,and I—
 * I took the one less traveled by,
 * And that has made all the difference.」
 *
 * Distributed under terms of the GNU GNU AGPLv3+ license.
 */

#include <cstdio>
#include <cassert>
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


template<i64 P>
struct ModInt {// {{{
    i64 x;
    constexpr ModInt() : x {0} {}
    constexpr ModInt(i64 _x) : x {norm(_x % get_mod())} {}
    
    static i64 mod;

    constexpr static i64 get_mod() { return P > 0? P: mod; }
    constexpr static void set_mod(i64 _mod) { mod = _mod; }

    static constexpr i64 norm(i64 x) {
        if (x < 0) {
            x += get_mod();
        }
        if (x >= get_mod()) {
            x -= get_mod();
        }
        return x;
    }
    constexpr i64 val() const { return x; }
    constexpr ModInt operator-() const {
        ModInt res;
        res.x = norm(get_mod() - x);
        return res;
    }

    constexpr ModInt inv() const { return pow(*this, get_mod() - 2); }

    constexpr ModInt& operator*=(const ModInt &rhs) & { x = (x * rhs.x) % int(get_mod()); return *this; }
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
	void output( const char end = '\n' ) { printf( "%" PRId64 "%c", x, end ); }
};// }}} 
  
constexpr i32 lowbit( ci32 cur ) { return cur & ( -cur ); }

template <i32 mod, i32 _G>
struct Poly {
	using PModInt = ModInt<mod>;
	static constexpr PModInt G = _G;

	enum Mode { point, coef } mode;
	i32 deg, nodes;
	std::vector<PModInt> a;

	Poly( ci32 _deg = 0, Mode _mode = coef ) : mode{_mode}, deg {_deg} { }

	void change() {// {{{
		ci32 size = a.size();
		std::vector<i32> rev(size);
		for( int i = 0; i < size; i ++ ) {
			rev[i] = rev[ i >> 1 ] >> 1;
			if( i & 1 ) 
				rev[i] |= ( size >> 1 );
		}

		for( int i = 0; i < size; i ++ ) 
			if( rev[i] < i ) 
				std::swap( a[ rev[i] ], a[i] );
	}// }}}

	void ntt( const Mode target_mode = point, ci32 target_point = 0 ) {// {{{
		if( this -> mode == target_mode ) 
			return ;
		this -> mode = target_mode;

		assert( target_mode == coef || target_point == lowbit(target_point) );

		if( target_mode == point ) {
			nodes = target_point;
			a.resize(target_point, 0);
		}

		this -> change();
		ci32 size = nodes;

		for( int h = 2; h <= size; h <<= 1 ) {
			ci32 half = ( h >> 1 );
			const PModInt gn = pow( G, ( mod - 1 ) / h );
			const PModInt step = ( target_mode == point )? gn: ( 1 / gn );
			const PModInt hg = pow( step, half );

			for( int i = 0; i < size; i += h ) {
				PModInt cg = 1;
				for( int j = 0; j < half; j ++ ) {
					PModInt p1 = a[ i + j ], p2 = cg * a[ i + j + half ];
					a[ i + j ] = p1 + p2;
					a[ i + j + half ] = p1 + hg * p2;
					cg *= step;
				}
			}
		}

		if( target_mode == coef ) {
			for( auto &x: a )
				x /= size;
			a.resize(deg + 1);
		}
	}// }}}
	 
	Poly& operator-() {// {{{
		for( auto &x: a )
			x = -x;
		return *this;
	}// }}}

	Poly operator* ( Poly &_b ) { // {{{
		ci32 n = deg;
		ci32 m = _b.deg;
		Poly c( n + m, point );

		i32 nm = n + m + 1;
		while( lowbit(nm) != nm ) 
			nm += lowbit(nm);
		this -> ntt(point, nm); _b.ntt(point, nm);

		c.a.resize(nm); c.nodes = nm;
		for( int i = 0; i < nm; i ++ ) 
			c.a[i] = a[i] * _b.a[i];
		
		c.ntt(coef);
		return c;
	}// }}}
	
	Poly inv() {
		if( this -> mode == point ) 
			this -> ntt(coef);
		if( this -> deg == 1 ) {
			Poly p1(1, coef);
			p1.a[0] = 1 / p1.a[0];
			return p1;
		}

		ci32 p_deg = ( deg >> 1 ) + ( deg & 1 );
		Poly p1(p_deg); p1.a.resize( p_deg );
		for( int i = 0; i < p_deg; i ++ ) 
			p1.a[i] = a[i];

		p1 = p1.inv();

		Poly p3 = - ( *this * p1 );

		p3.ntt(coef);
		p3.a[0] += 2;

		return p3 * p1;
	}

};

int main() {
#ifdef woshiluo
	freopen( "3803.in", "r", stdin );
	freopen( "3803.out", "w", stdout );
#endif

	ci32 n = read<i32>();
	ci32 m = read<i32>();

	Poly<998244353, 3> a( n - 1 );
	for( int i = 0; i < n; i ++ ) {
		a.a.push_back( read<i32>() );
	}

	Poly c = a.inv();

	for( auto &x: c.a )
		x.output( ' ' );
}
