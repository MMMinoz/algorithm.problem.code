#include<bits/stdc++.h>
using namespace std;
#define INF 0x3f3f3f3f
#define mem(a,b) memset(a,b,sizeof(a))
const int maxn=1e5+5;
int n,m,s,t,ss,tt;
int down[maxn];
int head[maxn],cnt;
struct Edge
{
    int v,w;
    int next;
    int id;
}e[maxn<<1];
void addEdge(int u,int v,int w,int id)
{
    e[++cnt]={v,w,head[u],id};
    head[u]=cnt;
    e[++cnt]={u,0,head[v],id};
    head[v]=cnt;
}

struct Dinic
{
    int cur[maxn],d[maxn];
    bool bfs()
    {
        queue<int> q;
        for(int i=0;i<=n+m+4;i++)
            d[i]=-1;
        d[s]=0;
        q.push(s);
        while(!q.empty())
        {
            int u=q.front();
            q.pop();
            for(int i=head[u];i!=-1;i=e[i].next)
            {
                int v=e[i].v;
                if(d[v]==-1&&e[i].w>0)
                {
                    d[v]=d[u]+1;
                    q.push(v);
                }
            }
        }
        return d[t]!=-1;
    }

    int dfs(int u,int flow)
    {
        int nowflow=0;
        if(u==t) return flow;
        for(int i=cur[u];i!=-1;i=e[i].next)
        {
            cur[u]=i;
            int v=e[i].v;
            if(d[v]==d[u]+1&&e[i].w>0)
            {
                if(int k=dfs(v,min(flow-nowflow,e[i].w)))
                {
                    e[i].w-=k;
                    e[i^1].w+=k;
                    nowflow+=k;
                    if(nowflow==flow)
                        break;
                }
            }
        }
        if(!nowflow) d[u]=-2;
        return nowflow;
    }
    int din()
    {
        int ans=0;
        while(bfs())
        {
            for(int i=0;i<=n+m+4;i++)
                cur[i]=head[i];

            ans+=dfs(s,INF);
        }
        return ans;
    }
}_din;

int du[maxn],ans[maxn];
int num;
void Init()
{
    cnt=-1;
    mem(head,-1);
    mem(du,0);
    num=0;
}

int main()
{
    while(~scanf("%d%d",&n,&m))
    {
        Init();
        ss=n+m+1;
        tt=n+m+2;
        for(int i=1;i<=m;i++)
        {
            int x;
            scanf("%d",&x);
            du[i+n]-=x;
            du[tt]+=x;
            addEdge(i+n,tt,INF-x,0);
        }
        for(int i=1;i<=n;i++)
        {
            int c,d;
            scanf("%d%d",&c,&d);
            addEdge(ss,i,d,0);
            for(int j=1;j<=c;j++)
            {
                int th,x,y;
                scanf("%d%d%d",&th,&x,&y);
                du[i]-=x;
                du[n+th+1]+=x;
                ans[++num]=x;
                addEdge(i,n+th+1,y-x,num);
            }
        }
        s=n+m+3;
        t=n+m+4;
        for(int i=1;i<=n+m+2;i++)
        {
            if(du[i]>0)
                addEdge(s,i,du[i],0);
            else
                addEdge(i,t,-du[i],0);
        }
        addEdge(tt,ss,INF,0);

        _din.din();
        bool flag=false;
        for(int i=head[s];~i;i=e[i].next)
        {
            if(e[i].w)
            {
                puts("-1");
                flag=true;
                break;
            }
        }

        if(!flag)
        {
            s=ss,t=tt;
            printf("%d\n",_din.din());
            for(int i=0;i<=cnt;i+=2)
                ans[e[i^1].id]+=e[i^1].w;
            for(int i=1;i<=num;i++)
                printf("%d\n",ans[i]);
        }
        puts("");
    }
}
