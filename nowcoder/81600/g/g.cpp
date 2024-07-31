/*
 * g.cpp 2024-07-31
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

const int N = 2e5 + 1e4;

struct Edge {
	i32 to, next;
} e[ N << 1 ];
i32 ehead[N], ecnt;
void add_edge( ci32 from, ci32 to ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[from];
	ehead[from] = ecnt;
}

i32 size[N], mson[N], fa[N];// {{{
void dfs1( ci32 cur, ci32 la ) {
	size[cur] = 1; fa[cur] = la;
	for( int i = ehead[cur]; i; i = e[i].next ) {
		ci32 to = e[i].to;
		if( to == la ) 
			continue;
		dfs1( to, cur ); 
		size[cur] += size[to];
		if( size[to] >= size[ mson[cur] ] )
			mson[cur] = to;
	}
}

i32 t_idx = 0;
i32 top[N], id[N], rid[N];
void dfs2( ci32 cur, ci32 la ) {
	t_idx ++; id[cur] = t_idx; rid[t_idx] = cur;
	if( top[cur] == 0 )
		top[cur] = cur;
	if( mson[cur] ) {
		top[ mson[cur] ] = top[cur];
		dfs2( mson[cur], cur );
	}
	for( int i = ehead[cur]; i; i = e[i].next ) {
		ci32 to = e[i].to;
		if( to == la || to == mson[cur] ) 
			continue;
		dfs2( to, cur );
	}
}
 // }}}
 
struct SegmentTree {// {{{
	struct Node {
		ci32 left, rig, mid;

		bool lazy;
		ModInt<mod> prid, val;
		Node *son[2];

		Node(ci32 _left, ci32 _rig): left(_left), rig(_rig), mid( ( _left + _rig ) >> 1 ), lazy(false) {
			prid = val = 1;
			son[0] = son[1] = 0;
		}

		~Node() {
			if( son[0] ) 
				delete(son[0]);
			if( son[1] ) 
				delete(son[1]);
		}

		Node* get_son(int k) {
			if( son[k] ) 
				return son[k];
			if( k == 0 )
				son[0] = new Node( left, mid );
			else
				son[1] = new Node( mid + 1, rig );
			return son[k];
		}

		void set_lazy() {
			lazy = true;
			val = prid;
		}

		void push_up() {
			this -> prid = get_son(0) -> prid * get_son(1) -> prid;
			this -> val = get_son(0) -> val * get_son(1) -> val;
		}

		void push_down() {
			if( !lazy ) 
				return ;
			lazy = false;

			get_son(0) -> set_lazy();
			get_son(1) -> set_lazy();
		}

		void init() {
			if( left == rig ) {
				if( mson[ rid[left] ] ) {
					prid = size[ mson[ rid[left] ] ];
				}
				return ;
			}

			get_son(0) -> init();
			get_son(1) -> init();

			this -> push_up();
		}

		void clear( ci32 from, ci32 to ) {
			if( from <= left && rig <= to ) {
				this -> set_lazy();
				return ;
			}

			this -> push_down();
			if( from <= mid ) 
				get_son(0) -> clear( from, to );
			if( to > mid ) 
				get_son(1) -> clear( from, to );
			this -> push_up();
		}

		void upd( ci32 pos, ModInt<mod> nval ) {
			if( left == rig && left == pos ) {
				this -> lazy = false;
				this -> val = nval;
				return ;
			}

			this -> push_down();

			if( pos <= mid )
				get_son(0) -> upd( pos, nval );
			else 
				get_son(1) -> upd( pos, nval );

			this -> push_up();
		}
	};
	Node *rt;

	~SegmentTree() { delete(rt); }
	SegmentTree(int n) { rt = new Node( 1, n ); rt -> init(); }


	void clear( ci32 from, ci32 to ) { 
		if( to < from ) 
			return ;
		rt -> clear( from, to );
	}
	void upd( ci32 pos, ModInt<mod> val ) { rt -> upd( pos, val ); }
	ModInt<mod> query() { return rt -> val; }
};// }}}

 
int main() {
#ifdef woshiluo
	freopen( "g.in", "r", stdin );
	freopen( "g.out", "w", stdout );
#endif

	ci32 n = read<i32>();
	ci32 q = read<i32>();

	for( int i = 2; i <= n; i ++ ) {
		ci32 p = read<i32>();

		add_edge( p, i );
	}

	dfs1( 1, 0 );
	dfs2( 1, 0 );

	ModInt<mod> res = 1;
	for( int i = 1; i <= n; i ++ ) 
		res *= i;
	for( int i = 1; i <= n; i ++ ) 
		res /= size[i];

	SegmentTree sgt(n);

	for( int _ = 1; _ <= q; _ ++ ) {
		ci32 u = read<i32>();
		
		{
			i32 cur = u, la = 0;
			while( cur ) {
				sgt.clear( id[ top[cur] ], id[cur] - 1 );
				sgt.upd( id[cur], ( la == 0 )? 1: size[la] );
				la = top[cur];
				cur = fa[ top[cur] ];
			}
		}

		( res * sgt.query() ).output();
	}
}
