#include <cstdio>
using namespace std;
			
int main(){				
	int n,m;			
	scanf("%d",&n);			
	int a[n];				
	for(int i=0;i<n;i++){				
		scanf("%d",&a[i]);					
	}						
	scanf("%d",&m);			
	int b[m];				
	for(int i=0;i<n;i++) scanf("%d",&b[i]);			
	int last,i,cnt;
	for(i=0;i<n;i++){
		for(int j=0;j<n;j++){
			if(a[i]==b[j]){
				last=j;
				break;
			}
		}
	}
	for(;i<n;i++){					
		for(int j=0;j<m;j++){
			if(a[i]>a[j]){
				for(int k=last;k<m;k++){
					if(b[k]==a[j])break;
					else {j=m;break;}
				}
				cnt++;
			}
		}
	}				
}
