#include <cmath>
#include <cstdio>
#include <cstdlib>

#include <algorithm>

const int N = 2e6 + 1e5;
const double PI = acos( -1.0 );

int n, m, bit2_length;
int ori_a[N], ori_b[N];

struct Complex {
	double x, y;
	Complex( double _x = 0, double _y = 0 ) {
		x = _x; y = _y;
	}
	Complex operator+( const Complex &b ) const {
		return Complex( x + b.x, y + b.y  );
	}
	Complex operator-( const Complex &b ) const {
		return Complex( x - b.x, y - b.y  );
	}
	Complex operator*( const Complex &b ) const {
		return Complex( x * b.x - y * b.y, x * b.y + y * b.x  );
	}
};

struct Poly {
	Complex a[N];
	int length;
	Poly( int f[], int _length ) {
		length = _length;
		for( int i = 0; i < length; i ++ ) {
			a[i] = Complex( f[i], 0 );
		}
	}
	Poly( Complex f[], int _length ) {
		length = _length;
		for( int i = 0; i < length; i ++ ) {
			a[i] = f[i];
		}
	}
	void change() {
		static int r[N];
		for( int i = 0; i < length; i ++ ) {
			r[i] = r[ i >> 1 ] >> 1;
			if( i & 1 ) 
				r[i] |= length >> 1;
		}
		for( int i = 0; i < length; i ++ ) {
			if( i < r[i] ) 
				std::swap( a[i], a[ r[i] ] );
		}
	}

	void fft( int on = 1 ) {
		this -> change();
		for( int h = 2; h <= length; h <<= 1 ) {
			Complex wn( cos( 2 * PI / h ), sin( on * 2 * PI / h ) );
			for( int i = 0; i < length; i += h ) {
				Complex w( 1, 0 );
				int mid = ( h >> 1 );
				for( int j = i; j < i + mid; j ++ ) {
					Complex u = a[j];
					Complex t = w * a[ j + mid ];

					a[j] = u + t;
					a[ j + mid ] = u - t;

					w = w * wn;
				}
			}
		}

		if( on == -1 ) {
			for( int i = 0; i < length; i ++ ) {
				a[i].x /= length;
			}
		}
	}

	void operator*= ( Poly b ) {
		if( this -> length != b.length )
			exit(-1);
		this -> fft(); b.fft();
		for( int i = 0; i < length; i ++ ) 
			a[i] = a[i] * b.a[i];
		this -> fft(-1); 
		// b.fft(-1); // restore b
	}
};

int main() {
#ifdef woshiluo
	freopen( "luogu.3803.in", "r", stdin );
	freopen( "luogu.3803.out", "w", stdout );
#endif

	scanf( "%d%d", &n, &m );
	for( int i = 0; i <= n; i ++ ) {
		scanf( "%d", &ori_a[i] );
	}
	for( int i = 0; i <= m; i ++ ) {
		scanf( "%d", &ori_b[i] );
	}

	for( bit2_length = 1; bit2_length < n + m + 1; bit2_length <<= 1 );
	Poly a( ori_a, bit2_length ), b( ori_b, bit2_length );
	a *= b;

	for( int i = 0; i < n + m + 1; i ++ ) 
		printf( "%d ", (int)( a.a[i].x + 0.5 ) );
}
