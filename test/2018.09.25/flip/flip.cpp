#include <cstdio>
using namespace std;

inline int Mmin(int a,int b){return a<b?a:b;}
inline int Mmax(int a,int b){return a>b?a:b;}

int n,tmp,cnt;
int lb,lw,mb=1<<30,mw=1<<30;
bool bll,sbl;

int main(){
	freopen("flip.in","r",stdin);
	freopen("flip.out","w",stdout);
	scanf("%1d",&tmp);
	if(tmp==0){
		bll=false;
		lw=1;
	}
	else {
		bll=true;
		lb=1;
	}
	while(scanf("%1d",&tmp)!=EOF){
		if(tmp==0){
			if(bll){
				cnt++;
				bll=false;
				if(cnt!=1) mw=Mmin(mw,lb+lw);
				lw=1;
			}
			else lw++;
		}
		else {
			if(!bll){
				cnt++;
				bll=true;
				if(cnt!=1) mb=Mmin(mb,lb+lw);
				lb=1;
			}
			else lb++;
		}
	}
	cnt++;
	mw=Mmin(mw,lb+lw);
	mb=Mmin(mb,lb+lw);
	if(cnt==2) mw=mb=Mmax(lb,lw);
	printf("%d",Mmax(mb,mw));
	fclose(stdin);
	fclose(stdout);
}
