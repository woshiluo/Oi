// Woshiluo<woshiluo@woshiluo.site>
// 2021/02/19 00:04:40 
// Blog: https://blog.woshiluo.com

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <iostream>
#include <algorithm>

typedef long long ll;
typedef unsigned long long ull;

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
	for (; !isdigit(ch); ch = getchar())
		if (ch == '-') fl = -1;
	for (; isdigit(ch); ch = getchar()) sum = sum * 10 + ch - '0';
	return sum * fl;
}

int n;

void print_ans( int res ) {
	printf( "! %d\n", res ); fflush(stdout);
	exit(0);
}

int ask( int left, int rig ) {
	if( left == rig ) 
		print_ans(left);
	printf( "? %d %d\n", left, rig ); fflush(stdout);
	int tmp; scanf( "%d", &tmp );
	return tmp;
}

void get_ans_to( int left, int rig, int st_rig, int val ) {
	int res = 0;
	while( left <= rig ) {
		int mid = ( left + rig ) >> 1;
		if( ask( mid, st_rig ) == val ) {
			chk_Max( res, mid );
			left = mid + 1;
		}
		else 
			rig = mid - 1;
	}
	print_ans( res );
}

void get_ans_from( int left, int rig, int st_left, int val ) {
	int res = n + 1;
	while( left <= rig ) {
		int mid = ( left + rig ) >> 1;
		if( ask( st_left, mid ) == val ) {
			chk_Min( res, mid );
			rig = mid - 1;
		}
		else 
			left = mid + 1;
	}
	print_ans( res );
}

void spj( int left, int rig, int val ) {
	int mid = left + 1;
	if( left == val ) {
		if( ask( left, mid ) == val )
			print_ans( mid ) ;
		else
			print_ans( rig );
	}
	if( mid == val ) {
		if( ask( left, mid ) == val )
			print_ans( left ) ;
		else
			print_ans( rig );
	}
	if( rig == val ) {
		if( ask( mid, rig ) == val ) 
			print_ans( mid ) ;
		else
			print_ans( left );
	}
}

void f( int left, int rig, int val ) {
	if( left == rig ) 
		print_ans( left );
	if( rig - left + 1 <= 3 ) 
		spj( left, rig, val );
	int mid = ( left + rig ) >> 1;
	if( mid < val ) {
		int tmp = ask( mid + 1, rig );
		if( tmp == val ) 
			f( mid + 1, rig, val );
		else 
			get_ans_to( left, mid, rig, val );
	}
	else {
		int tmp = ask( left, mid );
		if( tmp == val ) 
			f( left, mid, val );
		else 
			get_ans_from( mid, rig, left, val );
	}
}

int main() {
	scanf( "%d", &n );
	int tmp = ask( 1, n );
	f( 1, n, tmp );
}
