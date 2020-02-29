#include <cstdio>
#include <algorithm>
using namespace std;

int w,n,l,r,temp=0,cnt=0;

int cmp(int a,int b){
	return a>b;
}

int main(){
	scanf("%d%d",&w,&n);
	int a[n];
	for(int i=0;i<n;i++) scanf("%d",&a[i]);
	sort(a,a+n);
	r=n-1;
	while(l<=r){
		if(a[l]+a[r]<=w) {
			cnt++;
			l++;
			r--;
		}
		else {
			cnt++;
			r--;
		}
	}
	if(temp>0) cnt++;
	printf("%d",cnt);
}
