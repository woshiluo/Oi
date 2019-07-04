#include <cstdio>
using namespace std;


int main(){
	int n;
	scanf("%d",&n);
	int a[n];
	for(int i=0;i<n;i++) scanf("%d",&a[i]);
	for(int i=0;i<n;i++){
		for(int j=i;j<n;j++){
			if(a[i]>a[j]){
				int temp;
				temp=a[i];
				a[i]=a[j];
				a[j]=temp;
			}		
		}
	}
	for(int i=0;i<n;i++) printf("%d\n",a[i]);
}
