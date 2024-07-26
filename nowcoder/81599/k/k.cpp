/*
 * k.cpp 2024-07-25
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

const i32 mod = 998244353;

struct ModInt {/*{{{*/
	int cur;
	ModInt( i32 _cur = 0 ) { cur = ( ( ( _cur % mod ) + mod ) % mod ); }

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

const int N = 5e5 + 1e4;

ModInt pow_10[N];

struct SegmentTree {
	struct Num {
		ModInt x;
		int len;

		Num() { len = 0, x = 0; }
		Num( i32 _x ) { len = 1, x = _x; }

		Num operator+ ( const Num &_b ) const {
			Num res = *this;
			res.x *= pow_10[_b.len];
			res.x += _b.x;
			res.len += _b.len;
			return res;
		}
	};
	enum OpType { op_add, op_mul };
	struct Segment {// {{{
		enum Type { sig, add } type;
		ModInt sum, lbuf, rbuf;

		Segment() {
			type = sig;
			sum = lbuf = rbuf = 0;
		}

		Segment( const Num &p ) {
			type = sig;
			lbuf = p.x;
			sum = rbuf = 0;
		}

		Segment merge( const OpType &op, const Segment &_b ) const {
			Segment res;

			res.type = add;
			res.sum = sum + _b.sum;

			if( type == sig && _b.type == sig ) {
				if( op == op_add ) {
					res.lbuf = lbuf;
					res.rbuf = _b.lbuf;
					res.type = add;
					res.sum = 0;
				}
				else {
					res.lbuf = lbuf * _b.lbuf;
					res.type = sig;
					res.sum = 0;
				}
			}
			else if( type == sig ) {
				res.rbuf = _b.rbuf;
				if( op == op_add ) {
					res.lbuf = lbuf;
					res.sum += _b.lbuf;
				}
				else 
					res.lbuf = lbuf * _b.lbuf;

				res.type = add;
			}
			else if( _b.type == sig ) {
				res.lbuf = lbuf;
				if( op == op_add ) {
					res.sum += rbuf;
					res.rbuf = _b.lbuf;
				}
				else 
					res.rbuf = rbuf * _b.lbuf;

				res.type = add;
			}
			else {
				if( op == op_add )
					res.sum += rbuf + _b.lbuf;
				else
					res.sum += rbuf * _b.lbuf;
				res.lbuf = lbuf;
				res.rbuf = _b.rbuf;
				res.type = add;
			}

			return res;
		}

		ModInt gen() const { return lbuf + sum + rbuf; }
	};// }}}
	
	struct Node {
		ci32 left, rig, mid;
		Node *son[2];
		struct NodeData {// {{{
			i32 opc;
			Num lpart, rpart;
			Segment seg;
			OpType lop, rop;
			NodeData() {
				opc = 0;
				lop = rop = op_add;
			}
			NodeData operator+ ( const NodeData &_b ) const {// {{{
				NodeData res;

				res.opc = opc + _b.opc;
				res.lpart = lpart;
				res.rpart = _b.rpart;
				res.lop = lop;
				res.rop = _b.rop;

				Num p = rpart + _b.lpart;

				if( opc == 0 && _b.opc == 0 ) {
					res.lpart = lpart + _b.lpart;
					res.seg = Segment();
				}
				else if( opc == 0 ) {
					res.lop = _b.lop;
					res.rop = _b.rop;
					res.seg = _b.seg;
					res.lpart = lpart + _b.lpart;
				}
				else if( _b.opc == 0 ) {
					res.lop = lop;
					res.rop = rop;
					res.seg = seg;
					res.rpart = rpart + _b.lpart;
				}
				else if( opc == 1 && _b.opc == 1 ) {
					res.lop = lop;
					res.rop = _b.lop;
					res.seg = p;
				}
				else if( opc == 1 ) {
					res.seg = p;
					res.seg = res.seg.merge( _b.lop, _b.seg );
				}
				else if( _b.opc == 1 ) {
					res.rop = _b.lop;
					res.seg = seg;
					res.seg = res.seg.merge( rop, p );
				}
				else {
					res.seg = seg;
					res.seg = res.seg.merge( rop, p );
					res.seg = res.seg.merge( _b.lop, _b.seg );
				}

				return res;
			}// }}}

			ModInt gen() const {
				if( opc == 0 ) {
					return lpart.x;
				}

				if( opc == 1 ) {
					if( lop == op_add )
						return lpart.x + rpart.x;
					if( lop == op_mul )
						return lpart.x * rpart.x;
				}

				if( opc >= 2 ) {
					Segment p1 = lpart;
					Segment p2 = seg;
					Segment p3 = rpart;

					return p1.merge(lop, p2).merge(rop, p3).gen();
				}
				return 0;
			}
		};// }}}
		NodeData data;

		Node( ci32 _left, ci32 _rig ): left( _left ), rig( _rig ), mid( ( _left + _rig ) >> 1 ) {
			son[0] = son[1] = 0;
		}

		Node* get_son( ci32 k ) {
			if( son[k] ) 
				return son[k];
			if( k == 0 )
				son[k] = new Node( left, mid );
			else 
				son[k] = new Node( mid + 1, rig );
			return son[k];
		}

		 
		void update( ci32 pos, const char cur ) {
			if( left == rig && left == pos ) {
				data.lpart = Num(); data.rpart = Num();
				data.lop = data.rop = op_add;
				data.opc = 0;
				data.seg = Segment();
				if( cur == '+' ) {
					data.opc = 1;
					data.lop = data.rop = op_add;
				}
				else if( cur == '*' ){
					data.opc = 1;
					data.lop = data.rop = op_mul;
				}
				else {
					data.opc = 0;
					data.lpart = ( cur - '0' );
				}

				return ;
			}

			Node *p1 = get_son(0), *p2 = get_son(1);
			if( pos <= mid ) 
				p1 -> update( pos, cur );
			if( pos > mid ) 
				p2 -> update( pos, cur );

			this -> data = p1 -> data + p2 -> data;
			return ;
		}

		NodeData query( ci32 from, ci32 to ) {
			if( from <= left && rig <= to ) { return this -> data; }

			if( from <= mid && to > mid ) {
				return get_son(0) -> query(from, to) + get_son(1) -> query(from, to);
			}
			if( from <= mid ) 
				return get_son(0) -> query(from, to);
			if( to > mid ) 
				return get_son(1) -> query(from, to);

			return get_son(0) -> query(from, to);
		}
	};

	Node *rt;

	SegmentTree( ci32 n ) { rt = new Node( 1, n ); }

	void update( ci32 pos, const char cur ) { rt -> update( pos, cur ); }
	Node::NodeData query( ci32 from, ci32 to ) { return rt -> query( from, to ); }
};

int main() {
#ifdef woshiluo
	freopen( "k.in", "r", stdin );
	freopen( "k.out", "w", stdout );
#endif

	pow_10[0] = 1;
	for( int i = 1; i < N; i ++ ) 
		pow_10[i] = pow_10[ i - 1 ] * 10;

	i32 q = read<i32>();

	static char str[N];
	scanf( "%s", str + 1 );
	ci32 len = strlen( str + 1 );

	SegmentTree sgt(len);
	for( int i = 1; i <= len; i ++ ) 
		sgt.update( i, str[i] );

	for( int _ = 1; _ <= q; _ ++ ) {
		ci32 op = read<i32>();
		ci32 x = read<i32>();
		if( op == 1 ) {
			ci32 y = read<i32>();
			const auto data = sgt.query( x, y );
			data.gen().output( '\n' );
//			printf( "\n" );
//			printf( "%s %d %d\n", str + 1, x, y );
		}
		else {
			static char buf[8];
			scanf( "%s", buf );
			str[x] = buf[0];
			sgt.update( x, str[x] );
		}
	}
}
