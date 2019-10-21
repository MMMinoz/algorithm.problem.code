#include<bits/stdc++.h>
using namespace std;
#define INF 0x3f3f3f3f
#define mem(a,b) memset(a,b,sizeof(a))
const int maxn=1e5+5;
int n,m,s,t;
int down[maxn];
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

int du[maxn];
void Init()
{
    s=0,t=n+1;
    cnt=-1;
    mem(head,-1);
    mem(du,0);
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
            int u,v,z;
            scanf("%d%d%d%d",&u,&v,&down[i],&z);
            addEdge(u,v,z-down[i]);
            du[u]-=down[i];
            du[v]+=down[i];
        }
        for(int i=1;i<=n;i++)
        {
            if(du[i]<0)
                addEdge(i,t,-du[i]);
            else
                addEdge(s,i,du[i]);
        }
        _din.din();
        bool flag=false;
        for(int i=head[s];~i;i=e[i].next)
        {
            if(e[i].w)
            {
                puts("NO");
                flag=true;
                break;
            }
        }
        if(flag)
            continue;
        puts("YES");
        for(int i=0;i<=2*m-2;i+=2)
            printf("%d\n",e[i^1].w+down[i/2+1]);
    }
}
