#include <cstdio>
#include <cstring>
using namespace std;
 
struct FUCK{
    int a[5][5],x,y,deep;
    char bs[100];
}dl[400000],ed;
 
int z;
int dx[4]={0,-1,0,1};
int dy[4]={-1,0,1,0};
char d[4]={'L','U','R','D'};

long long zys(FUCK ){
	long long ans=0;
	memset(x,false,sizeof(x));
	for(long long i=1;i<=n-1;i++){
		long long tcnt=0;
		for(long long j=1;j<a[i];j++) if(x[j]==false) tcnt++;
		ans=ans+tcnt*p[n-i];
		x[a[i]]=true;
	}
	ans++;
	return ans;
}

int main(){
 
    for(int i=1;i<=4;i++){
        for(int j=1;j<=4;j++){
            scanf("%d",&dl[1].a[i][j]);
            if(dl[1].a[i][j]==0){
                dl[1].x=i;
                dl[1].y=j;
            }
        }
    }
    dl[1].deep=0;
    int l=1;
    for(int i=1;i<=4;i++){
        for(int j=1;j<=4;j++){
            ed.a[i][j]=l++;
        }
    }  
    ed.a[4][4]=0;
    ed.x=ed.y=4;
 
    int r;
    l=r=1;
     
     
    while(l<=r){
        for(int i=0;i<4;i++){
            FUCK fir=dl[l];
            fir.x=dl[l].x+dx[i];
            fir.y=dl[l].y+dy[i];
             
            if(fir.x>=1&&fir.x<=4&&fir.y>=1&&fir.y<=4){
                int temp=fir.a[fir.x][fir.y];
                fir.a[fir.x][fir.y]=fir.a[dl[l].x][dl[l].y];
                fir.a[dl[l].x][dl[l].y]=temp;
                fir.bs[fir.deep]=d[i];
                fir.deep=dl[l].deep+1;
                r++;
                dl[r]=fir;
                if(fir.x==ed.x&&fir.y==ed.y){
                    bool x=false;
                    for(int j=1;j<=4;j++){
                        for(int k=1;k<=4;k++){
                            if(ed.a[j][k]!=fir.a[j][k]) x=true;
                        }
                    }
                    if(!x){
                        for(int j=0;j<fir.deep;j++) printf("%c",fir.bs[j]);
                        printf("\n");
                        return 0;
                    }
                    if(fir.deep>=51){
                        printf("1\n");    
                        return 0;
                    }
                }

            }
        }
        l++;
    }
    printf("1");

}
