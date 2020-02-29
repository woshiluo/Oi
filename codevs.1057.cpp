#include <cstdio>
using namespace std;

int less,cnt;
bool f=true;

int main(){
	for(int i=1;i<=12;i++){
		int temp,temp_less;
		scanf("%d",&temp);
		if(300+less-temp<0&&f) {
			printf("-%d",i);
			f=false;
			
		}
		temp_less=(300+less-temp)%100;
		less+=temp_less;
		if(temp>=300){
			less=less-(temp-300);
		}
		cnt+=300+less-temp_less;
	}
	if(f)printf("%.0lf",1.2*cnt);
}
