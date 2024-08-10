/*
 * 10.cpp 2024-08-07
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

#include <queue>
#include <list>
#include <vector>
#include <iostream>
#include <algorithm>

using i32 = int32_t;
using u32 = uint32_t;
using ci32 = const i32;
using cu32 = const u32;

using i64 = int_fast64_t;
using u64 = uint_fast64_t;
using ci64 = const i64;
using cu64 = const u64;

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

constexpr i32 mod = 998244353;
constexpr i32 G = 3;

template<i64 P>
struct ModInt {// {{{
    i64 x;
    constexpr ModInt() : x {0} {}
    constexpr ModInt(i64 _x) : x {norm(_x % P)} {}

    static constexpr i64 norm(i64 x) {
        if (x < 0) {
            x += P;
        }
        if (x >= P) {
            x -= P;
        }
        return x;
    }
    constexpr i64 val() const { return x; }
    constexpr ModInt operator-() const {
        ModInt res;
        res.x = norm(P - x);
        return res;
    }

    constexpr ModInt inv() const { return pow(*this, P - 2); }

    constexpr ModInt& operator*=(const ModInt &rhs) & { x = (x * rhs.x) % P; return *this; }
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
    void output() { std::cout << x << " "; }
};// }}} 
  
constexpr i32 lowbit( ci32 cur ) { return cur & ( -cur ); }

std::vector<ModInt<mod>> gen_gns(bool inv) {
	std::vector<ModInt<mod>> list;
	for( int k = 0; k < 22; k ++ ) {
		if( !inv )
			list.push_back( pow( (ModInt<mod>)G, ( mod - 1 ) / ( 1 << k ) ) );
		else
			list.push_back( 1 / pow( (ModInt<mod>)G, ( mod - 1 ) / ( 1 << k ) ) );
	}
	return list;
}

const std::vector<ModInt<mod>> gns = gen_gns(false);
const std::vector<ModInt<mod>> gns_inv = gen_gns(true);

template <i32 mod, i32 _G>
struct Poly {// {{{
    using PModInt = ModInt<mod>;
    static constexpr PModInt G = _G;

    enum Mode { point, coef } mode;
    i32 deg, nodes;
    std::vector<PModInt> a;

    constexpr Poly( ci32 x = 0 ): mode{ coef }, deg{0}, nodes{0}, a(1, x) { }
    constexpr Poly( ci32 _deg, Mode _mode ) : mode{_mode}, deg {_deg}, nodes{0}, a(_deg + 1) { }

    constexpr static Poly get_x() {
        Poly res = Poly(1, coef);
        res.a[1] = 1;
        return res;
    }
	constexpr Poly& mul_one() {
		this -> ntt(coef);
		deg ++;
		a.insert( a.begin(), 0 );
		return *this;
	}

    void change() {// {{{
        static i32 rev[ 1 << 22 ];

        ci32 size = a.size();

        for( int i = 0; i < size; i ++ ) {
            rev[i] = rev[ i >> 1 ] >> 1;
            if( i & 1 ) 
                rev[i] |= ( size >> 1 );
        }

        for( int i = 0; i < size; i ++ ) 
            if( rev[i] < i ) 
                std::swap( a[ rev[i] ], a[i] );
    }// }}}
     
    constexpr Poly mod_x( ci32 n ) {// {{{
        this -> ntt(coef);
        deg = n - 1; a.resize(n);

        return *this;
    }// }}}

    void ntt( const Mode target_mode = point, ci32 target_point = 0 ) {// {{{
        if( this -> mode == target_mode ) {
			if( target_mode == coef || nodes == target_point )  
				return ;
			else
				this -> ntt(coef);
		}

        this -> mode = target_mode;

        if( target_mode == point ) {
            nodes = target_point;
            a.resize(target_point, 0);
        }

        this -> change();
        ci32 size = nodes;

        for( int h = 2, k = 1; h <= size; h <<= 1, k ++ ) {
            ci32 half = ( h >> 1 );
            const PModInt step = ( target_mode == point )? gns[k]: gns_inv[k];

            for( int i = 0; i < size; i += h ) {
                PModInt cg = 1;
				auto *it1 = &a[i], *it2 = &a[ i + half ];
                for( int j = 0; j < half; j ++, it1 ++, it2 ++ ) {
                    const PModInt p1 = *it1, p2 = cg * *it2;
                    *it1 = p1 + p2;
                    *it2 = p1 - p2;
                    cg *= step;
                }
            }
        }

        if( target_mode == coef ) {
            a.resize(deg + 1);
            const PModInt size_inv = (PModInt)1 / size;
            for( auto &x: a )
                x *= size_inv;
        }
    }// }}}
     
    Poly operator-() & {// {{{
        Poly res = *this;
        for( auto &x: res.a )
            x = -x;
        return res;
    }// }}}
    Poly& operator-() && {// {{{
        for( auto &x: a )
            x = -x;
        return *this;
    }// }}}
     //
    Poly& operator+= ( Poly &_b ) & { // {{{
        ci32 n = deg; ci32 m = _b.deg;
        this -> ntt(coef); _b.ntt(coef);

        deg = Max( n, m ); a.resize( deg + 1 );
        for( int i = 0; i <= m; i ++ ) 
            a[i] += _b.a[i];
        
        return *this;
    }// }}}
    Poly& operator-= ( Poly &_b ) & { // {{{
        ci32 n = deg; ci32 m = _b.deg;
        this -> ntt(coef); _b.ntt(coef);

        deg = Max( n, m ); a.resize( deg + 1 );
        for( int i = 0; i <= m; i ++ ) 
            a[i] -= _b.a[i];
        
        return *this;
    }// }}}
    Poly& operator*= ( Poly &_b ) & { // {{{
        ci32 n = deg;
        ci32 m = _b.deg;

        i32 nm = n + m + 1;
        while( lowbit(nm) != nm ) 
            nm += lowbit(nm);

        this -> ntt(point, nm); _b.ntt(point, nm);

        for( int i = 0; i < nm; i ++ ) 
            a[i] *= _b.a[i];
        
        deg = n + m;

        return *this;
    }// }}}
    Poly& operator/= ( Poly &_b ) & { *this *= _b.inv(); return *this; }

    Poly& operator+= ( Poly &&_b ) & { (*this) += _b; return (*this); }
     
    friend Poly operator+ ( const Poly &_a, Poly &_b ) { Poly res = _a; res += _b; return res; }
    friend Poly operator- ( const Poly &_a, Poly &_b ) { Poly res = _a; res -= _b; return res; }
    friend Poly operator* ( const Poly &_a, Poly &_b ) { Poly res = _a; res *= _b; return res; }
    friend Poly operator/ ( const Poly &_a, Poly &_b ) { Poly res = _a; res /= _b; return res; }
    friend Poly operator+ ( const Poly &_a, Poly &&_b ) { return _a + _b; }
    friend Poly operator- ( const Poly &_a, Poly &&_b ) { return _a - _b; }
    friend Poly operator* ( const Poly &_a, Poly &&_b ) { return _a * _b; }
    friend Poly operator/ ( const Poly &_a, Poly &&_b ) { return _a / _b; }
    
    Poly inv() {// {{{
		this -> ntt(coef);
        if( this -> deg == 0 ) {
            Poly p1(0, coef);
            p1.a.resize(1);
            p1.a[0] = 1 / a[0];
            return p1;
        }

        ci32 mdeg = ( deg >> 1 ) + 1;
        Poly p1( mdeg - 1, coef ); p1.a.resize(mdeg);

        for( int i = 0; i < mdeg; i ++ ) 
            p1.a[i] = a[i];

        p1 = p1.inv();

        return ( p1 * ( ( 2 - ( *this * p1 ) ).mod_x( deg + 1 ) ) ).mod_x( deg + 1 );
    }// }}}

    Poly integ() {// {{{
        Poly res = *this;

        res.ntt(coef);
        res.a.insert( res.a.begin(), 0 ); // assume c = 0
        res.deg ++;
        for( int i = 1; i <= res.deg; i ++ ) {
            res.a[i] /= i;
        }

        return res;
    }// }}}
    Poly deriv() {// {{{
        Poly res = *this;

        if( res.deg == 0 ) {
            res.a[0] = 0;
            return res;
        }

        res.ntt(coef);
        for( int i = 1; i <= res.deg; i ++ ) {
            res.a[i] *= i;
        }
        res.a.erase( res.a.begin() );
        res.deg --;

        return res;
    }// }}}
     
    Poly ln( ci32 mx ) {
        Poly df = this -> deriv();
        Poly res = ( this -> inv() * df ).integ();
        res.mod_x(mx);
        return res;
    }
    Poly ln() { return this -> ln( deg + 1 ); }
};// }}}

const int N = 1e5 + 1e4;

struct Edge {
    i32 to, next;
} e[N];
int ehead[N], ecnt;
void add_edge( ci32 from, ci32 to ) {
    ecnt ++;
    e[ecnt].to = to;
    e[ecnt].next = ehead[from];
    ehead[from] = ecnt;
}

int size[N], mson[N], top[N];
std::vector<i32> links[N];

void dfs( ci32 cur ) {
    mson[cur] = 0; size[cur] = 1;
    for( int i = ehead[cur]; i; i = e[i].next ) {
        ci32 to = e[i].to;
        dfs( to );
        size[cur] += size[to];
        if( size[to] > size[ mson[cur] ] )
            mson[cur] = to;
    }
}


void dfs1( ci32 cur ) {
    if( top[cur] == 0 ) {
        top[cur] = cur;
        links[cur].resize(0);
    }
    links[ top[cur] ].push_back(cur);
    if( mson[cur] ) {
        top[ mson[cur] ] = top[cur];
        dfs1( mson[cur] );
    }
    for( int i = ehead[cur]; i; i = e[i].next ) {
        ci32 to = e[i].to;
        if( to == mson[cur] ) 
            continue;
        dfs1( to );
    }
}

template<typename T>
struct Matrix {
    T a[3][3];
    Matrix() {
		a[0][1] = 1;
		a[1][1] = 1;
		a[2][0] = 1;
		a[2][2] = 1;
	}

    Matrix operator* ( Matrix &_b ) {
        Matrix res;
		res.a[0][1] = 0; res.a[2][0] = 0;
        for( int i = 0; i < 3; i ++ ) {
            for( int j = 0; j < 3; j ++ ) {
				if( i == 1 || j == 2 ) 
					continue;
                for( int k = 0; k < 3; k ++ ) {
                    res.a[i][j] += ( a[i][k] * _b.a[k][j] );
                }
            }
        }
        return res;
    }
    Matrix operator* ( Matrix &&_b ) { return (*this) * _b; }
    
};

Poly<mod, G> f[N], g[N], sum[N], dp[N];
Poly<mod, G> one = Poly<mod, G>::get_x();
Poly<mod, G> one_1 = one + 1;
Matrix<Poly<mod, G>> mat[N];
Matrix<Poly<mod, G>> solve( ci32 left, ci32 rig, ci32 cur ) {
    if( left == rig ) 
        return mat[ links[cur][left] ];

    ci32 mid = ( left + rig ) >> 1;
    return solve( left, mid, cur ) * solve( mid + 1, rig, cur );
}

Matrix<Poly<mod, G>> end;
void work(ci32 cur) {
    std::priority_queue<std::pair<i32, i32>> q;
    f[cur] = 0; g[cur] = 0;
    for( int i = ehead[cur]; i; i = e[i].next ) {
        ci32 to = e[i].to;
        work( to );
        if( to != mson[cur] ) {
            q.push( std::make_pair( -size[to], to ) );
            f[cur] += dp[to];
        }
    }
    while( q.size() > 1 ) {
        auto [s1, p1] = q.top(); q.pop();
        auto [s2, p2] = q.top(); q.pop();

        sum[p1] += sum[p2];
        dp[p1] *= dp[p2];

        q.push( std::make_pair( s1 + s2, p1 ) );
    }

    if( !q.empty() ) {
        auto [_, p1] = q.top(); q.pop();
        f[cur] += sum[p1];
        g[cur] += dp[p1];
    }
    else {
        f[cur] = 0;
        g[cur] = 1;
    }
    
    mat[cur].a[0][0] = g[cur];
	mat[cur].a[0][0].mul_one();
    mat[cur].a[2][1] = f[cur];

    if( top[cur] == cur ) {
        if( links[cur].size() == 1 ) {
            dp[cur] = one_1;
            sum[cur] = 0;
            return ;
        }

		end.a[0][0] = one_1;
		end.a[1][0] = 1;
		end.a[2][0] = 0;
        const auto p = solve( 0, links[cur].size() - 2, cur ) * end;

        dp[cur] = p.a[0][0];
        sum[cur] = p.a[2][0];
    }
}

int main() {
#ifdef woshiluo
    freopen( "10.in", "r", stdin );
    freopen( "10.out", "w", stdout );
#endif

	for( int i = 0; i < 2; i ++ )
		for( int j = 0; j < 2; j ++ ) 
			end.a[i][j] = 0;

	std::ios::sync_with_stdio(false); std::cin.tie(0); std::cout.tie(0);
    int size = 256 << 20; // 512M
    __asm__("movq %0, %%rsp\n" :: "r"((char *)malloc(size) + size));
	i32 T;
	std::cin >> T;
    while( T -- ) {
		i32 n;
		std::cin >> n;
        ecnt = 0;
        memset( ehead, 0, sizeof(ehead[0]) * ( n + 2 ) );
        memset( top, 0, sizeof(top[0]) * ( n + 2 ) );
        for( int i = 2; i <= n; i ++ ) {
			i32 u;
			std::cin >> u;
            add_edge( u, i );
        }
        dfs( 1 );
        dfs1( 1 );
        work( 1 );

        auto res = dp[1] + sum[1];
        for( int i = 1; i <= n; i ++ ) {
            res.a[i].output();
        }
		std::cout << "\n";
    }
    std::exit(0);
}
