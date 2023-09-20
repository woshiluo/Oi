#include <cstdio>
using namespace std;

int max_cnt=-1,max=-1,cnt;
int a[8],b[8];

int main(){
	for(int i=0;i<7;i++) scanf("%d%d",&a[i],&b[i]);
	for(int i=0;i<7;i++){
		if(a[i]+b[i]<=8) continue;
		else {
			cnt=a[i]+b[i]-8;
			if(cnt>max_cnt){
				max_cnt=cnt;
				max=i+1;
			}
		}
	}
	printf("%d",max);
}
