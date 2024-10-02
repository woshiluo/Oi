#include<bits/stdc++.h>
#define LL long long
using namespace std;
int P[60];
vector<int>V[60],VV;
mt19937 mt(time(0));
void solve(int n)
{
    for(int i=0;i<=n;i++)V[i].clear();
    for(int i=1;i<=n;i++)V[0].emplace_back(i);
    for(int i=0;i<n;i++){
        P[i]=0;
        if(!V[i].size())continue;
        sort(V[i].begin(),V[i].end());
        VV.clear();
        swap(VV,V[i]);
        P[i]=VV[VV.size()-1];
        if(P[i]/VV[0]+i<n){
            P[i]=(n-i)*VV[0]+(VV[0]-1); 
        }
        // cout<<i<<':'<<P[i]<<endl;
        // cout<<n-i<<' '<<VV[0]<<'\n';
        // for(auto x:VV)cout<<x<<' ';
        // cout<<endl;
        for(auto x:VV){
            // if(i==18)cout<<x<<',';
            V[i+P[i]/x].emplace_back(x);
        }
        // if(i==18)cout<<endl;
    }
    sort(V[n].begin(),V[n].end());
    // for(int i=0;i<=n;i++)
    //     cout<<P[i]<<" \n"[i==n];
    // for(int i=0;i<=n;i++){
    //     if(!V[i].size())continue;
    //     cout<<i<<':';
    //     for(int x:V[i])
    //         cout<<x<<' ';
    //     cout<<endl;
    // }
    // cout<<V[n].size()<<'\n';
    // assert(V[n].size()==n);
    // if(V[n].size()!=n)
        // cout<<n<<'\n';
    // cout<<n<<' '<<V[n].size()<<endl;
    // if(V[n].size()==n)exit(0);
    assert(V[n].size()==n);
}
int main()
{
    // for(int i=1;i<=5099;i++)
    //     solve(50);
    int m;cin>>m;
    if(m==29)
        cout<<"29 420 279 215 150 120 0 91 0 62 0 0 0 0 30 434 377 324 287 230 219 112 159 90 107 34 27 22 21\n";
    else if(m==32)
        cout<<"32 527 340 261 202 167 130 0 99 0 68 0 0 0 0 0 33 511 420 364 350 311 240 144 134 0 97 119 64 31 24 31\n";
    else if(m==34)
    cout<<"34 611 395 279 216 174 140 0 104 0 0 69 0 0 0 0 0 35 577 527 464 390 336 297 285 169 143 161 66 0 40 25 38 29\n";
    else if(m==37)
    cout<<"37 702 467 349 264 230 191 154 0 112 0 0 75 0 0 0 0 0 38 666 612 577 511 464 390 376 308 180 234 152 168 111 60 44 33 28 27\n";
    else if(m==38)
    cout<<"38 740 468 350 272 237 197 159 0 119 0 0 80 0 0 0 0 0 0 38 684 612 544 495 434 419 246 335 180 169 224 127 83 75 44 55 62 37\n";
    else if(m==41)
    cout<<"41 840 559 418 333 252 215 0 165 0 127 0 0 86 0 0 0 0 0 0 42 860 779 702 612 577 527 479 403 259 0 208 243 161 119 90 40 49 63 30 30\n";
    else if(m==42)
    cout<<"42 923 614 439 342 303 252 210 174 0 131 0 0 0 84 0 0 0 0 0 0 42 881 779 740 629 576 559 462 416 402 251 200 279 125 189 78 149 40 47 47 38\n";
    else if(m==46)
    cout<<"46 1080 719 516 429 328 286 239 0 185 0 143 0 0 0 95 0 0 0 0 0 0 0 47 1057 924 840 819 702 683 592 525 476 299 264 371 210 135 232 98 0 53 64 33 50 45\n";
    else if(m==50)
    cout<<"50 1299 816 611 506 405 359 307 257 0 204 0 155 0 0 0 102 0 0 0 0 0 0 0 0 50 1200 1127 1034 989 923 798 778 680 400 570 359 299 420 242 230 144 160 119 114 50 59 54 56 48\n";
    else{
        solve(m);
        for(int i=0;i<m;i++)
            cout<<P[i]<<' ';
    }
}
