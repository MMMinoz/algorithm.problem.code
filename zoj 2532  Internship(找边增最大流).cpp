#include<bits/stdc++.h>
using namespace std;
#define mem(a,b) memset(a,b,sizeof(a))
#define INF 0x3f3f3f3f
const int maxn=1e3+5;
int n,m,s,t,l;
int ans[maxn];

struct Edge
{
    int u,v,w;
    int next;
    int id;
}e[maxn<<1];

int head[maxn],cnt;
void addEdge(int u,int v,int w,int id)
{
    e[++cnt]={u,v,w,head[u],id};
    head[u]=cnt;
    e[++cnt]={v,u,0,head[v],id};
    head[v]=cnt;
}

struct Din
{
    int cur[maxn],d[maxn];
    bool bfs()
    {
        for(int i=0;i<=n+m+1;i++)
            d[i]=-1;
        d[s]=0;
        queue<int> q;
        q.push(s);
        while(!q.empty())
        {
            int u=q.front();
            q.pop();
            for(int i=head[u];~i;i=e[i].next)
            {
                int v=e[i].v;
                if(d[v]==-1&&e[i].w)
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
        if(u==t)
            return flow;
        int nowflow=0;
        for(int i=cur[u];~i;i=e[i].next)
        {
            cur[u]=i;
            int v=e[i].v;
            if(d[v]==d[u]+1&&e[i].w)
            {
                int k=dfs(v,min(flow-nowflow,e[i].w));
                if(k)
                {
                    nowflow+=k;
                    e[i].w-=k;
                    e[i^1].w+=k;
                    if(nowflow==flow)
                        break;
                }
            }
        }
        if(!nowflow)
            d[u]=-2;
        return nowflow;
    }

    int din()
    {
        int ans=0;
        while(bfs())
        {
            for(int i=0;i<=m+n+1;i++)
                cur[i]=head[i];
            ans+=dfs(s,INF);
        }
        return ans;
    }
}_din;

///s可以到达i点，from[i]=1
///i可以到达t点，to[i]=1,
bool from[maxn],to[maxn];
void DFS(int u,int flag)
{
    for(int i=head[u];~i;i=e[i].next)
    {
        if(!((i&1)&&!flag || !(i&1) && flag))
            continue;

        int v=e[i].v;
        if(!from[v]&&flag&&e[i].w)
        {
            from[v]=1;
            DFS(v,flag);
        }
        if(!to[v]&&!flag&&e[i^1].w)///由于求的是t->i是反着求的，e[i^1]才是这条边对应的正向边
        {
            to[v]=1;
            DFS(v,flag);
        }
    }
}
void Init()
{
    s=n+m+1,t=0;
    cnt=-1;
    mem(head,-1);
    mem(from,0);
    mem(to,0);

}

int main()
{
    while(~scanf("%d%d%d",&n,&m,&l))
    {
        if(n==0)
            return 0;
        Init();
        for(int i=1;i<=l;i++)
        {
            int u,v,w;
            scanf("%d%d%d",&u,&v,&w);
            addEdge(u,v,w,i);
        }
        for(int i=1;i<=n;i++)
            addEdge(s,i,INF,0);

        _din.din();
        from[s]=1,to[t]=1;
        DFS(s,true);
        DFS(t,false);
        int num=0;
        for(int i=0;i<=2*l-2;i+=2)
            if(from[e[i].u]&&to[e[i].v]&&!e[i].w)
                ans[num++]=e[i].id;

        sort(ans,ans+num);
        for(int i=0;i<num-1;i++)
            printf("%d ",ans[i]);
        if(num)printf("%d",ans[num-1]);
        puts("");
    }
}
