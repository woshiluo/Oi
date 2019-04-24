#include <cstdio>
#include <algorithm>

inline int lowbit(int now){return now & (-now);}

const int N = 110000;

int n, k;
int ans[N];

// Node Start
struct node{
	int a, b, c, val, ans;
	bool operator!= (node rig){
		return this -> a != rig.a || this -> b != rig.b || this -> c != rig.c;
	}
}a[N], b[N];

bool cmp(node left, node rig) { 
	if(left.a == rig.a) 
		if(left.b == rig.b)
			return left.c < rig.c;
		else 
			return left.b < rig.b;
	else 
		return left.a < rig.a; 
}
// Node End

// BIT Start
int bit[N];
void add(int now, int val){
	for(; now <= k; now += lowbit(now))
		bit[now] += val;
}

int sum(int now){
	int res = 0;
	for(; now; now -= lowbit(now))
		res += bit[now];
	return res;
}
// BIT End

void cdq(int left, int rig){
	if(left == rig) 
		return ;
	int mid = (left + rig) >> 1;
	cdq(left, mid); cdq(mid + 1, rig);
	int tp1 = left, tp2 = mid + 1;
	for(int i = left; i <= rig; i++){
		if((tp1 <= mid && a[tp1].b <= a[tp2].b) || tp2 > rig){
			add(a[tp1].c, a[tp1].val);
			b[i] = a[tp1++];
		}
		else {
			a[tp2].ans += sum(a[tp2].c);
			b[i] = a[tp2++];
		}
	}
	for(int i = left; i <= mid; i++) 
		add(a[i].c, -a[i].val);
	for(int i = left; i <= rig; i++)
		a[i] = b[i];
}

int main(){
#ifdef woshiluo
	freopen("luogu.3810.in", "r", stdin);
	freopen("luogu.3810.out", "w", stdout);
#endif
	int tmp;
	scanf("%d%d", &tmp, &k);
	for(int i = 1; i <= tmp; i++)
		scanf("%d%d%d", &b[i].a, &b[i].b, &b[i].c);	
	std::sort(b + 1, b + tmp + 1, cmp);
	for(int i = 1, cnt = 0; i <= tmp; i++){
		cnt ++;
		if(b[i] != b[i + 1]){
			a[ ++n ] = b[i];			
			a[n].val = cnt;
			cnt = 0;
		}
	}

	cdq(1, n);
	
	for(int i = 1; i <= n; i++) 
		ans[ a[i].ans + a[i].val - 1 ] += a[i].val;
	for(int i = 0; i < tmp; i++)
		printf("%d\n", ans[i]);

	fclose(stdin);
	fclose(stdout);
}
