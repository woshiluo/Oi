#include <cstdio>

inline int Min(int a, int b){return a < b? a: b;}
inline int Max(int a, int b){return a > b? a: b;}

int n;
bool flag = false;
int now, la, now_cnt, la_cnt, max;

int main(){
	scanf("%d", &n);	
	while(n--){
		scanf("%d", &now);
		if(now != la){
			flag = true;
			max = Max(max, Min(now_cnt, la_cnt)); 
			la = now;
			la_cnt = now_cnt;
			now_cnt = 1;
		}
		else now_cnt++;
	}	
	max = Max(max, Min(now_cnt, la_cnt)); 
	if(!flag) printf("0");
	else printf("%d", max << 1);
}
