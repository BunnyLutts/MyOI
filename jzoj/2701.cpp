#define DEBUG
#include <cstdio>
#include <cmath>
#include <cassert>
#define INF 0x7ffffff
#define MAXN 500
#define MAXM 500
#define MAXS (2*70000+2)

using namespace std;

int min(int a, int b) {
  return a<b ? a : b;
}

int max(int a, int b) {
  return a>b ? a : b;
}

class Flow {
public:
  int n, m, s, t, ind[10000], las[10000], val[3*MAXS], to[3*MAXS], link[3*MAXS];

  void init(int n, int s, int t) {
    this->n = n;
    this->s = s, this->t = t;
    m = 1;
    for (int i=0; i<n; i++) {
      ind[i] = 0;
    }
  }

  void addSide(int x, int y, int v) {
    m++;
    to[m] = y;
    val[m] = v;
    link[m] = ind[x];
    las[x] = ind[x] = m;
    m++;
    to[m] = x;
    val[m] = 0;
    link[m] = ind[y];
    las[y] = ind[y] = m;
  }

  int flow(int s, int t, int flo, int *dis, int *gap, bool &flag) {
    if (s==t) {
      return flo;
    }
    int have=0;
    for (int i=ind[s]; i; i=link[i]) {
      if (dis[s]==dis[to[i]]+1 && val[i]) {
	ind[s] = i;
	int now = flow(to[i], t, min(val[i], flo-have), dis, gap, flag);
	val[i] -= now, val[i^1] += now;
	have += now;
	if (have==flo || flag) {
	  return have;
	}
      }
    }
    ind[s] = las[s];
    if (!(--gap[dis[s]])) {
      flag = false;
    }
    gap[++dis[s]]++;
    return have;
  }

  int getFlow() {
    static int gap[MAXN+1], dis[MAXN+1];
    for (int i=0; i<=n; i++) {
      gap[i] = dis[i] = 0;
    }
    gap[0] = n;
    int ret=0;
    for (bool flag=true; flag && dis[s]<n; ret+=flow(s, t, INF, dis, gap, flag));
    return ret;
  }
};

class FlowWithRange{
public:
  Flow f;
  int n, m, ind[10000], to[MAXS], val[MAXS][2], link[MAXS], in[10000];

  void init(int n) {
    f.init(n+2, n, n+1);
    this->n = n, this->m = 1;
    for (int i=0; i<n; i++) {
      ind[i] = 0;
    }
  }

  void addSide(int u, int v, int l, int r) {
    m++;
    to[m] = v;
    val[m][0] = l, val[m][1] = r;
    link[m] = ind[u];
    ind[u] = m;
    f.addSide(u, v, r-l);
    m++;
  }

  int getFlow(int s, int t) {
    addSide(t, s, 0, INF);
    for (int i=0; i<n; i++) {
      for (int j=ind[i]; j; j=link[j]) {
	f.addSide(n, to[j], val[j][0]);
	f.addSide(i, n+1, val[j][0]);
      }
    }
    int ret = f.getFlow();
    bool flag=true;
    for (int i=2; i<=m && flag; i+=2) {
      if (val[i][0]+f.val[i^1]>val[i][1]) {
	flag = false;
      }
    }
    for (int i=f.ind[n]; i && flag; i=f.link[i]) {
      if (i%2==0 && f.val[i]) {
	flag = false;
      }
    }
    return flag ? ret : -1;
  }
};

int main() {
#ifdef DEBUG
  freopen("2701.in", "r", stdin);
  freopen("2701.out", "w", stdout);
#endif

  static int a[MAXN+1][MAXM+1], b[MAXN+1][MAXM+1], suf[2][MAXN+1];
  int n, m, l, r;
  scanf("%d %d", &n, &m);
  for (int i=1; i<=n; i++) {
    for (int j=1; j<=m; j++) {
      scanf("%d ", &a[i][j]);
      suf[0][i] += a[i][j];
      suf[1][j] += a[i][j];
    }
  }
  scanf("%d %d", &l, &r);

  static FlowWithRange flow;
  int ans=-1;
  for (int x=0, y=MAXN*1000, mid; x<=y; ) {
    mid = (x+y)/2;
    flow.init(n+m+2);
    for (int i=1; i<=n; i++) {
      flow.addSide(0, i, max(suf[0][i]-mid, m*l), min(suf[0][i]+mid, m*r));
    }
    for (int i=1; i<=m; i++) {
      flow.addSide(i+n, n+m+1, max(suf[1][i]-mid, n*l), min(suf[1][i]+mid, n*r));
    }
    int temp=flow.m+1;
    for (int i=1; i<=n; i++) {
      for (int j=1; j<=m; j++) {
	flow.addSide(i, j+n, l, r);
      }
    }
    if (flow.getFlow(0, n+m+1)>=0) {
      for (int i=1; i<=n; i++) {
	for (int j=1; j<=m; j++) {
	  b[i][j] = flow.val[temp][0]+flow.f.val[temp^1];
	  temp+=2;
	}
      }
      y = mid-1;
      ans = mid;
    } else {
      x = mid+1;
    }
  }

  printf("%d\n", ans);
  for (int i=1; i<=n; i++) {
    for (int j=1; j<=m; j++) {
      printf("%d ", b[i][j]);
    }
    printf("\n");
  }

  fclose(stdin);
  fclose(stdout);
  return 0;
}
