#include <cstdio>
using namespace std;

int main(){
	int n;
	scanf("%d",&n);
	int a[n+1];
	for(int i=0;i<=n;i++) scanf("%d",&a[i]);
	int temp=n;
	if(a[0]!=0&&a[0]!=1&&a[0]!=-1)printf("%dx^%d",a[0],n);
	if(a[0]==-1) printf("-x^%d",n);
	if(a[0]==1) printf("x^%d",n);
	n--;
	int i=1;
	while(n!=0){
		if(a[i]==0){
			n--;
			i++;
			continue;
		}
		else if(a[i]>0){
			if(a[i]!=1)printf("+%d",a[i]);
			if(a[i]==1)printf("+");
			if(n!=1)printf("x^%d",n);
			if(n==1)printf("x");
			n--;
			i++;
		}
		else if(a[i]<0){
			if(a[i]!=-1)printf("%d",a[i]);
			if(a[i]==-1)printf("-");
			if(n!=1) printf("x^%d",n);
			if(n==1)printf("x");
			n--;
			i++;
		}
			
	}
	if(a[temp]>0)printf("+%d",a[temp]);
	if(a[temp]<0)printf("%d",a[temp]);
}
