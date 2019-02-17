#include <cstdio>
#include <algorithm>

const int N = 1e5 + 1e4;

int n, ans , mrig;
int a[N], b[N];

struct mount{
	int left, rig;
}mou[N];

bool cmp(mount a, mount b){
	return ((a.left==b.left)&&a.rig>b.rig) || a.left<b.left;
}

int main(){
	freopen("mountains.in", "r", stdin);
	freopen("mountains.out", "w", stdout);
	scanf("%d", &n);	
	for(int i = 1; i <= n; i++){
		scanf("%d%d", &a[i], &b[i]);
		mou[i].left = a[i] - b[i];
		mou[i].rig = a[i] + b[i];
	}
	std::sort(mou + 1, mou + n + 1, cmp);
	for(int i = 1; i <= n; i++){
		if(mou[i].rig > mrig) mrig = mou[i].rig;
		else ans++;
	}
	printf("%d",n - ans);
}
