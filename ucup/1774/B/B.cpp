#include<bits/stdc++.h>
using namespace std;
int n,Len,c[1200010],fx[1200010],fuyi,flag;
int X[200010],Y[200010],Z[1200010],cnt;
int main()
{
    ios::sync_with_stdio(false);
    int T;cin>>T;
    while(T --> 0){
        cin>>n>>Len;cnt=0;fuyi=0;
        for(int i=1;i<=n;i++){
            cin>>X[i]>>Y[i];
            if(X[i]!=-1){
                Z[++cnt]=X[i];
                if(X[i]>1)Z[++cnt]=X[i]-1;
                if(X[i]<Len)Z[++cnt]=X[i]+1;
            }
            if(Y[i]!=-1){
                Z[++cnt]=Y[i];
                if(Y[i]>1)Z[++cnt]=Y[i]-1;
                if(Y[i]<Len)Z[++cnt]=Y[i]+1;
            }   
        }
        Z[++cnt]=1;
        Z[++cnt]=Len;
        sort(Z+1,Z+1+cnt);
        cnt=unique(Z+1,Z+1+cnt)-Z-1;
        Len=min(Len,cnt);
        for(int i=1;i<=n;i++){
            if(X[i]!=-1)
                X[i]=lower_bound(Z+1,Z+1+cnt,X[i])-Z;
            if(Y[i]!=-1)
                Y[i]=lower_bound(Z+1,Z+1+cnt,Y[i])-Z;
        }
        memset(c,0,sizeof(int)*(Len+5));
        memset(fx,0,sizeof(int)*(Len+5));
        for(int i=1;i<=n;i++){
            if(X[i]!=-1&&Y[i]!=-1){
                if(X[i]==Y[i])
                    fx[X[i]]=3;
                else{
                    fx[X[i]]=1;
                    fx[Y[i]]=-1;
                }
                c[X[i]]++;
                c[Y[i]+1]--;
            }else if(X[i]!=-1){
                c[X[i]]++;
                c[X[i]+1]--;
                fx[X[i]]=1;
            }else if(Y[i]!=-1){
                c[Y[i]]++;
                c[Y[i]+1]--;
                fx[Y[i]]=-1;
            }else fuyi++;
        }
        flag=1;
        int pos=0,duan=0,last=-1;
        fx[0]=12345;
        for(int i=1,temp=0;i<=Len;i++){
            temp+=c[i];
            if(temp>1)flag=0;
            if(!temp)pos+=Z[i]-Z[i-1];
            if((last==-1||last==3)&&(fx[i]==1||fx[i]==3)&&fx[i-1]==0)
                duan++;
            if(fx[i])last=fx[i];
        }
        if((last==-1||last==3)&&fx[Len]==0)
            duan++;
        // cout<<endl<<flag<<','<<duan<<','<<pos<<','<<fuyi<<'\n';
        if(duan>fuyi||pos<fuyi)flag=0;
        cout<<(flag?"TAK\n":"NIE\n");
    }
    // cout<<ans<<'\n';
}