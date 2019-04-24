#include <cstdio>

inline int Aabs(int a) {return a < 0? (0 - a): a;}

const int N = 510000;

struct node{
	int x, y;
	bool operator< (node b){
		return Aabs(x) <= Aabs(b.x);
	}
}a[N << 1], b[N << 1];

int n, m;
int sum[N], ans[N], scnt, acnt;

void cdq(int left, int rig){
	if(left == rig) 
		return ;
	int mid = (left + rig) >> 1;
	cdq(left, mid); cdq(mid + 1, rig);
	int tp1 = left, tp2 = mid + 1, sum = 0;
	for(int i = left; i <= rig; i++){
		if((tp1 <= mid && a[tp1] < a[tp2]) || tp2 > rig){
			if(a[tp1].x < 0) 
				sum += a[tp1].y;
			b[i] = a[tp1++];
		}
		else {
			if(a[tp2].x > 0) 
				ans[ a[tp2].y ] += sum;
			b[i] = a[tp2++];
		}
	}
	for(int i = left; i <= rig; i++)
		a[i] = b[i];
}

int main(){
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++){
		scanf("%d", &sum[i]);
		sum[i] += sum[i - 1];
	}
	for(int i = 1, op, x, y; i <= m; i++){
		scanf("%d%d%d", &op, &x, &y);
		if(op == 1){
			a[ ++acnt ] = (node){-x, y};
		}
		else {
			a[ ++acnt ] = (node){x - 1, ++scnt};
			ans[ scnt ] = sum[x - 1];
			a[ ++acnt ] = (node){y, ++scnt};
			ans[ scnt ] = sum[y];
		}
	}

	cdq(1, acnt);

	for(int i = 1; i <= scnt; i += 2){
		printf("%d\n", ans[i + 1] - ans[i]);
	}
}
