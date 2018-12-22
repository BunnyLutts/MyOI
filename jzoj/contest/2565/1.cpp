#define DEBUG
#include <cstdio>
#define INF 0x7ffffff
#define MAXN 500
#define MAXM 10000

using namespace std;

int min(int a, int b) {
  return a<b ? a : b;
}

int max(int a, int b) {
  return a>b ? a : b;
}

class Graph {
public:
  int n, m, ind[MAXN+1], link[2*MAXM+1], to[2*MAXM+1], val[2*MAXM+1], id[2*MAXM+1];

  void addSide(int u, int v, int w, int o) {
    m++;
    to[m] = v;
    id[m] = o;
    val[m] = w;
    link[m] = ind[u];
    ind[u] = m;
  }

  void init(int n) {
    this->n = n;
  }

  void solve(int o, int limit, int len, int &ans) {
    static bool book[MAXM+1];
    if (len<limit && len<ans) {
      for (int i=ind[o]; i; i=link[i]) {
	if (!book[id[i]]) {
	  book[id[i]] = true;
	  if (to[i]==1) {
	    ans = min(ans, len+val[i]);
	  } else {
	    solve(to[i], limit, len+val[i], ans);
	  }
	  if (ans<=limit) {
	    return;
	  }
	  book[id[i]] = false;
	}
      }
    }
  }
};

int main() {
#ifdef DEBUG
  freopen("1.in", "r", stdin);
  freopen("1.out", "w", stdout);
#endif

  static Graph graph;
  int n, m, temp=0;
  scanf("%d %d", &n, &m);
  for (int i=1; i<=m; i++) {
    int s, t, w, v;
    scanf("%d %d %d %d", &s, &t, &w, &v);
    graph.addSide(s, t, w, i);
    graph.addSide(t, s, v, i);
    temp += max(w, v);
  }
  graph.init(n);

  int ans=INF;
  for (int l=0, r=temp, mid; l<=r; ) {
    mid = (l+r)/2;
    graph.solve(1, mid, 0, ans);
    if (ans<=mid) {
      r = mid-1;
    } else {
      l = mid+1;
    }
  }
  printf("%d", ans);

  fclose(stdin);
  fclose(stdout);
  return 0;
}
