#include <cstdio>
using namespace std;

int a[30],b[30];

int main(){
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<=n;i++) b[i]=1;
	for(int i=2;i<=n;i++){
		for (int j=1;j<=i-1;j++){
			if(a[i]<=a[j]&&b[i]<b[j]+1) b[i]=b[j]+1;
		}
	}
	int max=0;
	for(int i=1;i<=n;i++){
		if(b[i]>max)max=b[i];
	}
	printf("%d",max);
}
