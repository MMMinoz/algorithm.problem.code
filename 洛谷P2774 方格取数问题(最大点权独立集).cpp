#include<bits/stdc++.h>
using namespace std;
#define INF 0x3f3f3f3f
const int maxn=2e3+5;
int n,m,s,t;
int sum=0;
int a[105][105];
int col[105][105];
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
int dx[4]={0,1,-1,0};
int dy[4]={1,0,0,-1};

struct Dinic
{
    int cur[maxn],d[maxn];
    bool bfs()
    {
        queue<int> q;
        for(int i=0;i<=n*m+1;i++)
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
            for(int i=0;i<=n*m+1;i++)
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
    Init();
    scanf("%d%d",&n,&m);
    s=0,t=n*m+1;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            scanf("%d",&a[i][j]);
            sum+=a[i][j];
            if((i%2&&j%2)||(i%2==0&&j%2==0))
                col[i][j]=1;
        }
    }

    for(int i=1;i<=n;i++)
    {
		for(int j=1;j<=m;j++)
        {
			if(col[i][j])
                addEdge(m*(i-1)+j,t,a[i][j]);
			else
			{
				addEdge(s,m*(i-1)+j,a[i][j]);
				for(int k=0;k<4;k++)
                {
					int nx=i+dx[k],ny=j+dy[k];
					if(nx>0&&ny>0&&nx<=n&&ny<=m)
                        addEdge(m*(i-1)+j,m*(nx-1)+ny,INF);
				}
			}
		}
    }
    printf("%d\n",sum-_din.din());
}
