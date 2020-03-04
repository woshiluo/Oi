#include <cstdio>

int n;
int cnt_1, ans, cnt, last;

int main() {
#ifdef woshiluo
	freopen( "A.in", "r", stdin );
	freopen( "A.out", "w", stdout );
#endif
	scanf( "%d", &n );
	while( n -- ) {
		ans = cnt = cnt_1 = last = 0;
		bool flag = false;
		char tmp;
		while(1) {
			tmp = getchar();
			while( ( tmp < '0' || tmp > '1' ) && flag == false ) 
				tmp = getchar();
			if( tmp < '0' || tmp >'1' ) 
				 break;
			flag = true;
			tmp -= '0';
			cnt ++;
			if( tmp == 0 ) 
				continue;
			else {
				if( last == 0 ) {
					cnt_1 ++;
					last = cnt;
					continue;
				}
				ans += ( cnt - last ) - 1;
				if( cnt - last > 1 ) 
					cnt_1 ++;
				last = cnt;
			}
		}
		printf( "%d\n", ans );
	}
}
