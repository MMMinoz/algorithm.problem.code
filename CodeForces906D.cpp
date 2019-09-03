#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int maxn=1e5+5;
ll a[maxn];
map<int,int> mp;
ll qpow(ll a,ll b,ll mod)
{
    ll res=1;
    while(b)
    {
        if(b&1)
            res=res*a>mod?res*a%mod+mod:res*a;
        a=a*a>mod?a*a%mod+mod:a*a;
        b>>=1;
    }
    return res;
}

ll phi(ll n)
{
    ll res=n;
    for(int i=2;i*i<=n;i++)
    {
        if(n%i==0)
        {
            while(n%i==0)
                n/=i;
            res=res-res/i;
        }
    }
    if(n>1)
        res=res-res/n;
    return res;
}

ll Solve(int l,int r,ll m)
{
    if(l==r)
        return a[r];
    if(m==1||a[l]==1)
        return 1ll;
    ll p=mp[m];
    return qpow(a[l],Solve(l+1,r,p),m);
}

int main()
{
    int n;
    ll m;
    cin>>n>>m;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    
    //预处理m的所有欧拉函数
    int cur=m;
    while(cur != 1)
    {
        mp[cur]=phi(cur);
        cur=phi(cur);
    }

    int q;
    cin>>q;
    while(q--)
    {
        int l,r;
        cin>>l>>r;
        cout<<Solve(l,r,m)%m<<endl;
    }
}
