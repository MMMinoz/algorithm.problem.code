#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define INF 0x3f3f3f3f
#define mem(a,b) memset(a,b,sizeof(a))
const int maxn=1e5+5;
int n,m,s,t;
int head[maxn],cnt;
struct Edge
{
    int v,flow,dis;
    int next;
}e[maxn];
void addEdge(int u,int v,int flow,int dis)
{
    e[++cnt]={v,flow,dis,head[u]};
    head[u]=cnt;
    e[++cnt]={u,0,-dis,head[v]};
    head[v]=cnt;
}

struct MCMF
{
    int dis[maxn],pre[maxn],last[maxn];
    bool vis[maxn];
    int flow[maxn];
    bool spfa()
    {
        mem(dis,INF);
        mem(flow,INF);
        mem(vis,0);
        queue<int> q;

        q.push(s);
        vis[s]=1;
        dis[s]=0;
        pre[t]=-1;

        while(!q.empty())
        {
            int u=q.front();
            q.pop();
            vis[u]=0;
            for(int i=head[u];~i;i=e[i].next)
            {
                int v=e[i].v;
                if(e[i].flow&&dis[v]>dis[u]+e[i].dis)
                {
                    dis[v]=dis[u]+e[i].dis;
                    pre[v]=u;
                    last[v]=i;
                    flow[v]=min(flow[u],e[i].flow);
                    if(!vis[v])
                    {
                        vis[v]=1;
                        q.push(v);
                    }
                }
            }
        }
        return pre[t]!=-1;
    }

    int maxflow;ll mincost;
    int mcmf()
    {
        mincost=0,maxflow=0;
        while(spfa())
        {
            ll flow=INF;
            for(int i=t;i!=s;i=pre[i])
                flow=min(flow,(ll)e[last[i]].flow);
            mincost+=dis[t]*flow;
            maxflow+=flow;
            for(int i=t;i!=s;i=pre[i])
            {
                e[last[i]].flow-=flow;
                e[last[i]^1].flow+=flow;
            }
        }
        return mincost;
    }
}_mcmf;


bool judje()
{
    for(int i=head[s];~i;i=e[i].next)
    {
        if(e[i].flow&&i%2==0)
            return false;
    }
    for(int i=head[t];~i;i=e[i].next)
    {
        if(e[i].flow&&i%2==0)
            return false;
    }
    return true;
}

int pre[maxn];
int Find(int x)
{
    while(x!=pre[x])
        x=pre[x];

    return x;
}
bool mix(int a,int b)
{
    int fa=Find(a);
    int fb=Find(b);
    if(fa!=fb)
    {
        pre[fb]=fa;
        return 0;
    }
    return 1;
}

int tot,ans,du[maxn];
void Init()
{
    s=n+1,t=n+2;
    cnt=-1;
    mem(head,-1);
    mem(du,0);
    for(int i=0;i<=n+2;i++)
        pre[i]=i;
    ans=0;
    tot=n;
}

int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&m);
        Init();
        for(int i=1;i<=m;i++)
        {
            int u,v,d;
            scanf("%d%d%d",&u,&v,&d);
            addEdge(u,v,INF,d);
            du[u]++,du[v]--;
            ans+=d;
            if(!mix(u,v))
                tot--;
        }
        ///是否连通
        if(tot!=1)
            puts("-1");
        else
        {
            int mf=0;
            for(int i=0;i<n;i++)
            {
                if(du[i]>0)
                    addEdge(i,t,du[i],0),mf+=du[i];
                else if(du[i]<0)
                    addEdge(s,i,-du[i],0);
            }
            ans+=_mcmf.mcmf();
            mf-=_mcmf.maxflow;
            if(mf!=0)
                puts("-1");
//            if(!judje())
//                puts("-1");
            else
                printf("%d\n",ans);
        }
    }
}
