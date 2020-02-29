#include <cstdio>
using namespace std;

int a[110][2];
int x[110];

int main(){
	int n;
	scanf("%d",&n);
	for(int i=0;i<n;i++){ 
		int left,right;
		scanf("%d %d",&left,&right);
		if(left>right){
			int temp=right;
			right=left;
			left=temp;
		}
		a[i][0]=left;
		a[i][1]=right;
	}
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			if(i==j) continue;
				int temp=0;
				if(a[i][0]<a[j][0]&&a[i][1]>a[j][1]) temp=a[j][1]-a[j][0]+1;				
				x[i]+=temp;
		}
	}
	for(int i=0;i<n;i++)printf("%d ",x[i]);  
}
