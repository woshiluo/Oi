#include<bits/stdc++.h>
using namespace std;
int C,S,F,N,M,a[2010],b[2010];
double f[2010][80],g[2010][80];
inline int read()
{
    int x=0,w=0;char ch=0;
    while(!isdigit(ch)){w|=ch=='-';ch=getchar();}
    while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    return w?-x:x;
}
int in(int pos,int L,int R)
{return L<=pos&&pos<=R;}
int main()
{
    C=read();S=read();F=read();N=read();M=read();
    for(int i=1;i<=N;i++)
        a[i]=read(),b[i]=read();
    for(int i=0;i<=M+1;i++)
    for(int j=0;j<=C+1;j++)
        f[j][i]=M+1;
    for(int i=C;i>=0;i--)g[i][M+1]=g[i+1][M+1]+f[i][M+1];
    for(int i=0;i<=C;i++)f[i][M]=M;
    for(int i=M-1;i>=0;i--){
        for(int j=C;j>=0;j--)g[j][i+1]=g[j+1][i+1]+f[j][i+1];
        for(int j=0;j<=C;j++){
            if(j==F){f[j][i]=i;continue;}
            for(int k=1;k<=N;k++){
                int L=j-b[k],R=j-a[k];
                //L
                if(R<0)f[j][i]=min(f[j][i],f[0][i+2]);
                else{
                    if(!in(-1,L,R)&&!in(F,L,R))f[j][i]=min(f[j][i],1.0*(g[L][i+1]-g[R+1][i+1])/(R-L+1));
                    else if(in(F,L,R)){
                        f[j][i]=min(f[j][i],1.0*(g[F+1][i+1]-g[R+1][i+1])/(R-L+1)+1.0*(i+1)*(F-L+1)/(R-L+1));
                        // if(j==10&&i==3&&k==2){
                        //     cout<<"FUCK "<<R-L+1<<endl;
                        //     cout<<(g[F+1][i+1]-g[R+1][i+1])<<' '<<(i+1)*(F-L+1)<<endl;
                        //     cout<<(g[F+1][i+1]-g[R+1][i+1])/(R-L+1)+(i+1)*(F-L+1)/(R-L+1)<<endl;
                        // }
                    }else if(in(-1,L,R)){
                        f[j][i]=min(f[j][i],-1.0*L*f[0][i+2]/(R-L+1)+1.0*(g[0][i+1]-g[R+1][i+1])/(R-L+1));
                        
                    }
                }
                // if(f[j][i]==0){
                //     cout<<"FUCKL "<<j<<' '<<i<<' '<<k<<endl;
                //     exit(0);
                // }
                // if(f[C][3]<4){
                //     cout<<"FUCKL "<<j<<' '<<i<<' '<<k<<' '<<L<<' '<<R<<endl;
                //     exit(0);
                // }
                L=j+a[k],R=j+b[k];
                //R
                if(L>C)f[j][i]=min(f[j][i],f[C][i+2]);
                else{
                    if(!in(C+1,L,R)&&!in(F,L,R))f[j][i]=min(f[j][i],1.0*(g[L][i+1]-g[R+1][i+1])/(R-L+1));
                    else if(in(F,L,R)){
                        f[j][i]=min(f[j][i],1.0*(g[L][i+1]-g[F][i+1])/(R-L+1)+1.0*(i+1)*(R-F+1)/(R-L+1));
                    }else if(in(C+1,L,R)){
                        f[j][i]=min(f[j][i],1.0*(R-C)*f[C][i+2]/(R-L+1)+1.0*g[L][i+1]/(R-L+1));
                    }
                }
                // if(f[C][1]<0){
                //     cout<<"FUCKR "<<j<<' '<<i<<' '<<k<<' '<<L<<' '<<R<<endl;
                //     exit(0);
                // }
                // if(f[j][i]==0){
                //     // cout<<"FUCKR "<<j<<' '<<i<<' '<<k<<' '<<L<<' '<<R<<endl;
                //     exit(0);
                // }
            }
        }
    }
    // for(int i=0;i<=M+1;i++)
    // for(int j=0;j<=C+1;j++)
    //     printf("%4.2f%c",f[j][i]," \n"[j==C+1]);
        // cout<<f[j][i]<<" \n"[j==C+1];
    printf("%.10f\n",f[S][0]);
}
/*
10 1 7
2 4
8 8
1 3

*/