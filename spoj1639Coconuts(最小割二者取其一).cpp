#include<bits/stdc++.h>
using namespace std;
#define INF 0x3f3f3f3f
const int maxn=1e5+5;
int n,m,s,t;
int head[maxn],cnt;
struct Edge
{
    int v,w;
    int next;
}e[maxn<<1];
void addEdge(int u,int v,int w)
{
    e[++cnt]={v,w,head[u]};
    head[u]=cnt;
    e[++cnt]={u,0,head[v]};
    head[v]=cnt;
}

struct Dinic
{
    int cur[maxn],d[maxn];
    bool bfs()
    {
        queue<int> q;
        for(int i=0;i<=n+1;i++)
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
            for(int i=0;i<=n+1;i++)
                cur[i]=head[i];

            ans+=dfs(s,INF);
        }
        return ans;
    }
}_din;


void Init()
{
    cnt=-1;
    memset(head,-1,sizeof(head));
}
int main()
{
    while(scanf("%d%d",&n,&m))
    {
        if(!(n+m))
            break;
        Init();
        s=0,t=n+1;
        for(int i=1;i<=n;i++)
        {
            int x;
            scanf("%d",&x);
            ///s同意 t不同意
            ///同意：(s,i,1) (i,t,0)
            ///不同意：(s,i,0) (i,t,1)
            if(x)
            {
                addEdge(s,i,1);
                addEdge(i,t,0);
            }
            else
            {
                addEdge(s,i,0);
                addEdge(i,t,1);
            }
        }
        for(int i=1;i<=m;i++)
        {
            int u,v;
            scanf("%d%d",&u,&v);
            addEdge(u,v,1);
            addEdge(v,u,1);
        }

        printf("%d\n",_din.din());
    }
}
