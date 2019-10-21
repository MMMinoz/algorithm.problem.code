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
int num,result;
void Init()
{
    cnt=-1;
    mem(head,-1);
    mem(du,0);
    num=0;
}

///删点前 s t 超级源点 超级汇点
///删点后 s t 源点 汇点
int main()
{
    while(~scanf("%d%d",&n,&m))
    {
        Init();
        for(int i=1;i<=m;i++)
        {
            int u,v,z,c;
            scanf("%d%d%d%d",&u,&v,&z,&c);
            if(c)
            {
                ans[i]=z;
                du[u]-=z;
                du[v]+=z;
            }
            else
                addEdge(u,v,z,i);
        }
        s=n+1,t=n+2;
        for(int i=1;i<=n;i++)
        {
            if(du[i]>0)
                addEdge(s,i,du[i],0);
            else
                addEdge(i,t,-du[i],0);
        }
        _din.din();

        addEdge(n,1,INF,0);

        result=_din.din();
        bool flag=false;
        for(int i=head[s];~i;i=e[i].next)
        {
            if(e[i].w)
            {
                puts("Impossible");
                flag=true;
                break;
            }
        }
        if(!flag)
        {
            printf("%d\n",result);
            for(int i=0;i<=cnt;i+=2)
                ans[e[i].id]=e[i^1].w;
            for(int i=1;i<m;i++)
                printf("%d\n",ans[i]);
            printf("%d\n",ans[m]);
        }
    }
}
