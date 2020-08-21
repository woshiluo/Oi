#include <bits/stdc++.h>
#include <queue>
#define ll long long
#define pii pair<int, int>
using namespace std;
 
priority_queue <int, vector<int>, greater<int>> a,b,c;
int main(){
    int n, k;
    cin >> n>> k;
    for (int i = 1; i <= n; i++){
        int x, y, z;
        cin >> x >> y >> z;
        if (y && z) c.push(x);
        else if(z) b.push(x);
        else if(y) a.push(x);        
    }
    int ka = k, kb = k;
    int ans = 0;
    if (a.size() + c.size() < k || b.size() + c.size() < k){
        cout << -1 << endl;
        return 0;
    }
    while (ka > 0 && kb > 0){
        int ta = 0, tb = 0, tc = 0;
        int va = 0, vb = 0, vc = 0;
        if (!a.empty() && ka != 0){
            ta = a.top(); 
            va = 1;
        }
        if (!b.empty() && kb != 0){
            tb = b.top();
            vb = 1;
        }
        if (!c.empty()){
            tc = c.top();
            vc = 1;
        }
        if (ka != 0 && va == 0) ta = 1000000;
        if (kb != 0 && vb == 0) tb = 1000000;
        if (vc == 0) tc = 1000000;
        if (tc < ta + tb){
            ans += tc;
            if (ka) ka -= vc;
            if (kb) kb -= vc;
            if (vc) c.pop();
            //cout << tc <<" "<<vc<< endl;
        }
        else{
            //cout << ta <<" "<< tb <<" "<<va<<" "<<vb<< endl;
            ans += ta + tb;
            ka -= va;
            kb -= vb;
			if( va == 0 || vb  == 0 ) 
				printf( "-1" );
            if (va) a.pop();
            if (vb) b.pop();
        }
    }
    cout << ans << endl;
 
}
