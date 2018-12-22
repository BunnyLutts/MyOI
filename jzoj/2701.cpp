#define DEBUG
#include <cstdio>
#define INF 0x7ffffff
#define MAXN 200
#define MAXM 200
#define MAXS (2*(MAXN*MAXM+MAXN+MAXM+MAXN+MAXM+4)+2)

using namespace std;

class Flow {
public:
  int n, m, s, t, ind[MAXN+MAXM+4], val[MAXS], to[MAXS], link[MAXS], run[MAXS];

  void init(int n, int s, int t) {
    this->n = n;
    this->s = s, this->t = t;
    m = 1;
  }

  void addSide(int x, int y, int v) {
    m++;
    to[m] = y;
    val[m] = v;
    link[m] = ind[x];
    ind[x] = m;
    m++;
    to[m] = x;
    val[m] = 0;
    link[m] = ind[y];
    ind[y] = m;
  }

  int flow(int o, int size, int *dis, int *gap) {
    for (int i=ind[o]; i; i=link[i]) {

    }
  }

  int getFlow() {
    static int gap[MAXN+1], dis[MAXN+1];
    for (int i=2; i<=m; i++) {
      run[i] = 0;
    }
    for (int i=0; i<n; i++) {
      gap[i] = dis[i] = 0;
    }
    gap[0] = n;
    return flow(s, INF, dis, gap);
  }
};

int main() {
#ifdef DEBUG
  freopen("2701.in", "r", stdin);
  freopen("2701.out", "w", stdout);
#endif

  static int a[MAXN+1][MAXM+1];
  int n, m, l, r;
  scanf("%d %d", &n, &m);
  for (int i=1; i<=n; i++) {
    for (int j=1; j<=m; j++) {
      scanf("%d ", &a[i][j]);
    }
  }
  scanf("%d %d", &l, &r);

  int ans=0;
  for (int x=0, y=1000, mid; x<=y; ) {
    mid = (x+y)/2;
  }

  fclose(stdin);
  fclose(stdout);
  return 0;
}
