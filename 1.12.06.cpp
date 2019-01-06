#include <stdio.h>

int a[11000][110],h[11000][110];
int n,m;

int sl(int l,int r){
	int cnt=0;
	for(int i=r;i>=0;i--){
		if(a[l][i]==1){
			cnt++;
			if(cnt==2)return i;
		}
	}
	for(int i=m-1;i>r;i--){
		if(a[l][i]==1){ 
			cnt++;
			if(cnt==2)return i;
		}
	}
	return 0;
}

int main(){
	int first;
	scanf("%d %d",&n,&m);
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			scanf("%d %d",&a[i][j],&h[i][j]);
		}
	}
	scanf("%d",&first);
	int ans=0,temp_room=first,temp_lou;
	for(int i=0;i<n;i++){
		ans+=h[i][temp_room];
		temp_lou=sl(i,temp_room);
		temp_room=temp_lou;
	}
	printf("%d",ans%20123);
}
