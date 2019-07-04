#include <cstdio>
using namespace std;

int w[11000],y[110],time=0,cnt=0;
bool x[11000];

int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;i++){ 
		scanf("%d",&w[i]);
		cnt+=w[i];
	}
	for(int i=0;i<m;i++){ 
		y[i]=i;
		x[i]=true;
	}
	while(1){
		if(cnt==0)break;
		for(int i=0;i<m;i++){
			if(y[i]>=0){
				w[y[i]]--;
				cnt--;
				if(w[y[i]]==0){
					bool temp=true;
					for(int j=0;j<n;j++){
						if(x[j]==false){
							y[i]=j;
							x[j]=true;
							temp=false;
							break;
						}
						if(temp) y[i]=-1;
					}
				}
			}
		}
		time++;
	}
	printf("%d",time);
}
