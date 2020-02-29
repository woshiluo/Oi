#include <cstdio>
using namespace std;

int main(){
	 int n;
	 scanf("%d",&n);
	 int a[n],cnt=0;
	 for(int i=0;i<n;i++){
		scanf("%d",&a[i]);
		cnt+=a[i];
	 }
	 int pj=cnt/n;
	 int ans=0;
	for(int i=0;i<n-1;i++){
		if(a[i]<pj) {
			int temp=pj-a[i];
			a[i+1]-=temp;
			a[i]+=temp;
			ans++;
		}
		else if(a[i]>pj){
			int temp=a[i]-pj;
			a[i]-=pj;
			a[i+1]+=temp;
			ans++;
		}
	 } 
	 if(a[n-1]!=pj) ans++;
	 printf("%d",ans);
}
