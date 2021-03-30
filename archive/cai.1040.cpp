#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;

int n,a[110],cnt;// a[] 储存顺序 cnt 临时储存和
bool x[110];//x[] 判重

bool zs(int x){
	for(int i=2;i<=sqrt(x)+1;i++){
		if(x%i==0) return false;
	}
	return true;
}

void dfs(int k){
	if(k==n+1){// 到达最终步骤
		if(!zs(a[n]+a[1])) return ;// 如果不是质数，那么下地狱吧

		for(int i=1;i<=n;i++){
			printf("%d ",a[i]);
		}
		printf("\n");
	}
	else{
		for(int i=2;i<=n;i++){
			if(!x[i]){
				cnt=a[k-1]+i; //求这个数与上个数的和
					if(zs(cnt)){// 求质数
						a[k]=i;
						x[i]=true;
						dfs(k+1);
						x[i]=false;
						a[k]=0;
					}
			}
		}
	}
}


int main(){
	scanf("%d",&n);
	a[1]=1;
	x[1]=true;
	dfs(2);//　目前已经确定第一个数为１（不然会重复）
}
