#include <cstdio>

inline int Min(int a,int b){return a<b?a:b;}

const int N=110;

int n;
int a[N],ei;

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%1d",&a[i]);
		ei+=(a[i]==8);
	}
	printf("%d",Min(n/11,ei));
}
