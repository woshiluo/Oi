#include <cstdio>
#include <cstring>
using namespace std;

char a[10],b[10];
int alen,blen;
int acnt,bcnt;

int main(){ 
    scanf("%s",a);
    scanf("%s",b);

    alen=strlen(a);
    blen=strlen(b);

    acnt=bcnt=1;
    for(int i=0;i<alen;i++)
        acnt=(acnt*(a[i]-'A'+1))%47;
    for(int i=0;i<blen;i++)
        bcnt=(bcnt*(b[i]-'A'+1))%47;

    if(acnt==bcnt) printf("GO\n");
    else printf("STAY\n");
}
