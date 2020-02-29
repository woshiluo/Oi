#include <cstdio>
#include <cstring>

const int BASE = 10;

struct Bigint {
	int num[11000], cnt;
	Bigint() {
		cnt = 0;
		memset(num, 0, sizeof(num));
	}
	int& operator[] (int now) { return num[now]; }
	void operator*= (int now) {
		for(int i = 1; i <= cnt; i ++)
			num[i] *= now; 
		for(int i = 1; i <= cnt; i ++){
			if( num[i] >= BASE ) {
				num[i + 1] += num[i] / BASE;
				num[i] %= BASE;
			}
		}
		while(num[cnt + 1] != 0){
			cnt ++;
			if( num[cnt] >= BASE ) {
				num[cnt + 1] += num[cnt] / BASE;
				num[cnt] %= BASE;
			}
		}
	}
	void operator/= (int now){
		for(int i = cnt; i; i --){
			num[i - 1] += (num[i] % now * 10);
			num[i] /= now;
		}
		while( !num[ cnt ] )
			cnt --;
	}
	void to_bigint(int now) {
		while(now) {
			num[ ++ cnt ] = now % BASE;
			now /= BASE;
		}
	}
	void print(char end = 0) {
		for(int i = cnt; i; i --)
			printf("%d", num[i]);
		end && putchar(end);
	}
};

int main() {
#ifdef woshiluo
	freopen("luogu.2624.in", "r", stdin);
	freopen("luogu.2624.out", "w", stdout);
#endif
	int n, d[1100], cnt = 0, sum = 0;
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		scanf("%d", &d[i]);
		if(d[i] == -1)
			continue;
		cnt ++; sum += d[i] - 1;
	}
	Bigint ans; ans.to_bigint(1);
	for(int i = n - 1 - sum; i < n - 1; i++)
		ans *= i;
	for(int i = 1; i <= n - 2 - sum; i++)
		ans *= (n - cnt);
	for(int i = 1; i <= n; i++)
		for(int j = 1; j < d[i]; j++)
			ans /= j;
	ans.print();
}
