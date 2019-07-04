#include <cstdio>

inline int Aabs(int a){return a < 0? (0 - a): a;}
inline int Min(int a, int b){return a < b? a: b;}
inline int Max(int a, int b){return a > b? a: b;}

const int N = 5100;

struct art{
	int x, y;
}a[N];

bool cmp(art a, art b){
	if(a.x == b.x) return a.y > b.y;
	else return a.x > b.x;
}
int n;
int cnt[5];
int fir_cnt[5];

int main(){
#ifdef woshiluo
	freopen("B.in", "r", stdin);
	freopen("B.out", "w" ,stdout);
#endif
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		scanf("%1d", &a[i].x);
	}
	for(int i = 1; i <= n; i++){
		scanf("%1d", &a[i].y);
	}

	for(int i = 1; i <= n; i++){
		if(a[i].x == 1 && a[i].y == 1) cnt[1]++;
		else if(a[i].x == 1 && a[i].y == 0) cnt[2]++;
		else if(a[i].x == 0 && a[i].y == 1) cnt[3]++;
		else if(a[i].x == 0 && a[i].y == 0) cnt[4]++;
	}

	for(int i = 0; i <= cnt[2]; i++){
		for(int j = 0, less_a = (n >> 1), less_b = (n >> 1), val_a = 0, val_b = 0; j <= cnt[3]; j++){
			less_a -= i + j; val_a = i;
			less_b -= (cnt[2] + cnt[3]) - (i + j); val_b = cnt[3] - j;
			if(val_a == val_b){
				if(cnt[1] % 2 == 0){
					if(Min(less_a, less_b) >= (cnt[1] >> 1)){
						less_a -= (cnt[1] >> 1);
						less_b -= (cnt[1] >> 1);
						if(less_a <= cnt[4]){ 
							cnt[1] >>= 1;
							fir_cnt[1] = cnt[1];
							fir_cnt[2] = i;
							fir_cnt[3] = j;
							fir_cnt[4] = less_a;
							for(int k = n; k >= 1; k--){
								if(a[k].x == 1 && a[k].y == 1 && fir_cnt[1]) {
									fir_cnt[1]--;
									printf("%d ", k);
								}
								else if(a[k].x == 1 && a[k].y == 0 && fir_cnt[2]){
									fir_cnt[2]--;
									printf("%d ", k);
								}
								else if(a[k].x == 0 && a[k].y == 1 && fir_cnt[3]){
									fir_cnt[3]--;
									printf("%d ", k);
								}
								else if(a[k].x == 0 && a[k].y == 0 && fir_cnt[4]) {
									fir_cnt[4]--;
									printf("%d ", k);
								}

							}
							return 0;
						}
					}
				}	
			}
			else if(val_a > val_b){
				if(less_b >= val_a - val_b && cnt[1] <= (val_a - val_b)){
					if( (cnt[1] - (val_a - val_b)) % 2 == 0){
						less_b -= val_a - val_b;
						if(Min(less_a, less_b) >= ((cnt[1] - (val_a - val_b)) >> 1)){
							less_a -= ((cnt[1] - (val_a - val_b)) >> 1);
							less_b -= ((cnt[1] - (val_a - val_b)) >> 1);
							if(less_a <= cnt[4]){ 
								cnt[1] -= (val_a - val_b);
								cnt[1] >>= 1;
								fir_cnt[1] = cnt[1];
								fir_cnt[2] = i;
								fir_cnt[3] = j;
								fir_cnt[4] = less_a;
								for(int k = n; k >= 1; k--){
									if(a[k].x == 1 && a[k].y == 1 && fir_cnt[1]) {
										fir_cnt[1]--;
										printf("%d ", k);
									}
									else if(a[k].x == 1 && a[k].y == 0 && fir_cnt[2]){
										fir_cnt[2]--;
										printf("%d ", k);
									}
									else if(a[k].x == 0 && a[k].y == 1 && fir_cnt[3]){
										fir_cnt[3]--;
										printf("%d ", k);
									}
									else if(a[k].x == 0 && a[k].y == 0 && fir_cnt[4]) {
										fir_cnt[4]--;
										printf("%d ", k);
									}
								}
								return 0;
							}
						}
					}		
				}	
			}
			else if(val_a < val_b){
				if(less_a >= val_b - val_a && cnt[1] <= (val_b - val_a)){
					if( (cnt[1] - (val_b - val_a)) % 2 == 0){
						less_a -= val_b - val_a;
						if(Min(less_a, less_b) >= ((cnt[1] - (val_b - val_a)) >> 1)){
							less_a -= ((cnt[1] - (val_b - val_a)) >> 1);
							less_b -= ((cnt[1] - (val_b - val_a)) >> 1);
							if(less_a <= cnt[4]){ 
								cnt[1] -= (val_b - val_a);
								cnt[1] >>= 1;
								fir_cnt[1] = cnt[1] + (val_b - val_a);
								fir_cnt[2] = i;
								fir_cnt[3] = j;
								fir_cnt[4] = less_a;
								for(int k = n; k >= 1; k--){
									if(a[k].x == 1 && a[k].y == 1 && fir_cnt[1]) {
										fir_cnt[1]--;
										printf("%d ", k);
									}
									else if(a[k].x == 1 && a[k].y == 0 && fir_cnt[2]){
										fir_cnt[2]--;
										printf("%d ", k);
									}
									else if(a[k].x == 0 && a[k].y == 1 && fir_cnt[3]){
										fir_cnt[3]--;
										printf("%d ", k);
									}
									else if(a[k].x == 0 && a[k].y == 0 && fir_cnt[4]) {
										fir_cnt[4]--;
										printf("%d ", k);
									}
								}
								return 0;
							}
						}
					}		
				}	
			}
		}
	}
	printf("-1");
}
