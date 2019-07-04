#include <cstdio>
using namespace std;

int a[32];

int main(){
	int n;
	scanf("%d",&n);
	long long ans=0;
	for(int i=0;i<n;i++) scanf("%1d",&a[i]);
	for(int i=n-1;i>=0;i--){
		int x=1;
		int temp=n-1-i;
		for(int j=1;j<=temp;j++){
			x*=2;	
		}
		if(a[i]==1) ans+=x;
	}
	printf("%lld",ans);
}
