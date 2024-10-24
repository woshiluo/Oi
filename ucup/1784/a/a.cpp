/*
 * a.cpp 2024-10-20
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
constexpr T pow( T a, i64 p ) {
	T res = 1;
	while( p ) {
		if( p & 1 ) 
			res = res * a;
		a = a * a;
		p >>= 1;
	}
	return res;
}/*}}}*/

const i64 mod = ( 1LL << 61LL ) - 1LL;
const i64 base = 1e9 + 7;

const int N = 2e5 + 1e4;
const int MIN_ADD = 2e8;
// const int MIN_ADD = 100;

template<i64 P>
struct ModInt {// {{{
    i64 x;
    constexpr ModInt() : x {0} {}
    constexpr ModInt(i64 _x) : x {norm(_x % get_mod())} {}
    
    static i64 mod;

    constexpr static i64 get_mod() { return P; }

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

    constexpr ModInt& operator*=(const ModInt &rhs) & { x = (((__int128)x) * rhs.x) % get_mod(); return *this; }
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
  
using ModInt1 = ModInt<mod>;

ModInt1 pow_base[N], pow_sum[N];

void pre() {
	pow_base[1] = pow_sum[1] = 1;
	for( int i = 2; i < N; i ++ ) {
		pow_base[i] = pow_base[ i - 1 ] * base;
		pow_sum[i] = pow_sum[ i - 1 ] + pow_base[i];
	}
}

struct Hash {
	i32 len;
	ModInt1 data;

	Hash(ci32 cur): len(1), data(cur) {};
	void add( ci32 val ) { 
		data += pow_sum[len] * val; 
	}
	Hash operator+ ( const Hash &_b ) const {
		Hash res = *this;
		res.len += _b.len;
		res.data = res.data * pow_base[_b.len + 1];
		res.data += _b.data;
		return res;
	}
	bool operator== ( const Hash &_b ) const { return len == _b.len && data == _b.data; }
	bool operator!= ( const Hash &_b ) const { return !(*this == _b); }
};

struct Data {
	Hash pre, suf;

	Data(ci32 cur = 0): pre(cur), suf(cur) {}
	void add( ci32 val ) {
		pre.add(val);
		suf.add(val);
	}
	Data operator+ ( const Data &_b ) const {
		Data res;
		res.pre = pre + _b.pre;
		res.suf = _b.suf + suf;
		return res;
	}
};

struct SegmentTree {
	struct Node {
		ci32 left, rig, mid;
		i32 lazy;
		Data data;
		Node *son[2];
		Node( ci32 _l, ci32 _r ): left(_l), rig(_r), mid( ( _l + _r ) >> 1 ) { lazy = 0; son[0] = son[1] = 0; }

		Node* get_son( ci32 k ) {
			if( son[k] )
				return son[k];
			if( k == 0 ) 
				son[k] = new Node( left, mid );
			else
				son[k] = new Node( mid + 1, rig );
			return son[k];
		}

		void add( ci32 val ) {
			this -> data.add(val);
			this -> lazy += val;
		}
		void push_up() {
			data = get_son(0) -> data + get_son(1) -> data;
		}
		void push_down() {
			if( lazy ) {
				get_son(0) -> add(lazy);
				get_son(1) -> add(lazy);
				lazy = 0;
			}
		}

		void add( ci32 from, ci32 to, ci32 val ) {
			if( from <= left && rig <= to ) {
				this -> add(val);
				return ;
			}
			this -> push_down();
			if( from <= mid ) 
				get_son(0) -> add( from, to, val );
			if( to > mid ) 
				get_son(1) -> add( from, to, val );
			this -> push_up();
		}

		Data query( ci32 from, ci32 to ) {
			if( from <= left && rig <= to ) {
				return this -> data;
			}
			this -> push_down();
			if( from <= mid && to > mid ) 
				return get_son(0) -> query( from, to ) + get_son(1) -> query( from, to );
			else if( from <= mid ) 
				return get_son(0) -> query( from, to );
			else 
				return get_son(1) -> query( from, to );
		}
	};

	Node *rt;

	SegmentTree( ci32 n ) { rt = new Node( 1, n ); }
	void add( ci32 from, ci32 to, ci32 val ) { rt -> add( from, to, val ); }
	Data query( ci32 from, ci32 to ) { return rt -> query( from, to ); }
};

int main() {
#ifdef woshiluo
	freopen( "a.in", "r", stdin );
	freopen( "a.out", "w", stdout );
#endif
	pre();

	
	ci32 n = read<i32>();
	ci32 q = read<i32>();
	ci32 k = read<i32>();
	ci32 b = read<i32>() * 2;

	SegmentTree sgt(n);
	std::vector<i32> a( n + 1 );
	for( int i = 1; i <= n; i ++ ) {
		a[i] = read<i32>() * 2 + ( n - i + 1 ) * k + MIN_ADD;
		sgt.add( i, i, a[i] );
	}
	for( int _ = 1; _ <= q; _ ++ ) {
		ci32 op = read<i32>();
		if( op == 1 ) {
			ci32 l = read<i32>();
			ci32 r = read<i32>();
			ci32 v = read<i32>() * 2;
			sgt.add( l, r, v );
		}
		else {
			ci32 p = read<i32>();
			if( p == 1 || p == n ) {
				printf( "0\n" );
				continue;
			}
			sgt.add( 1, p - 1, b );
			if( sgt.query( p - 1, p - 1 ).pre != sgt.query( p + 1, p + 1 ).suf ) {
				sgt.add( 1, p - 1, -b );
				printf( "0\n" );
				continue;
			}
			i32 left = 1, rig = Min( n - p, p - 1 ), res = 1;
			while( left <= rig ) {
				ci32 mid = ( left + rig ) >> 1;
				if( sgt.query( p - mid, p - 1 ).pre == sgt.query( p + 1, p + mid ).suf ) {
					res = mid;
					left = mid + 1;
				}
				else 
					rig = mid - 1;
			}
			sgt.add( 1, p - 1, -b );
			printf( "%d\n", res );
		}
	}
	return 0;
}
