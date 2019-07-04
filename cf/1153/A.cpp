#include <cstdio>

int n, t, s, d, fir, fir_id;

int main(){
	scanf("%d%d", &n, &t);
	fir = 0x7fffffff;
	for(int i = 1; i <= n; i++){
		scanf("%d%d", &s, &d);
		int tmp;
		if(s > t) 
			tmp = s;
		else 
			tmp = ((t - s) / d + ((t - s) % d != 0)) * ( d ) + s; 
		if(tmp < fir) {
			fir = tmp;
			fir_id = i;
		}
	}
	printf("%d\n", fir_id);
}
