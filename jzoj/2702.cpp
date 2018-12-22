#define DEBUG
#include <cstdio>
#include <cstring>
#define INF 0x7ffffff
#define MAXN 10000
#define MAXM 200000

using namespace std;

int min(int a, int b) {
  return a<b ? a : b;
}

int max(int a, int b) {
  return a>b ? a : b;
}

class Graph {
public:
  int n, m, ind[MAXN+1], link[4*MAXM+1], to[4*MAXM+1], val[4*MAXM+1], id[4*MAXM+1];

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

  int solve(int s, int t) {
    static int f[MAXN+1][2][2], que[MAXN+2];
    static bool book[MAXN+1];
    memset(f, 127, sizeof(f));
    int head=0, tail=0;
    for (int i=ind[s]; i; i=link[i]) {
      f[to[i]][0][0] = val[i];
      f[to[i]][0][1] = id[i];
      que[++tail] = to[i];
      book[to[i]] = true;
    }
    for (; head!=tail; ) {
      head = head%(n+1)+1;
      int x = que[head], y;
      book[x] = false;
      for (int i=ind[x]; i; i=link[i]) {
	y = to[i];
	bool flag=false;
	if (f[y][0][0]>f[x][0][0]+val[i] && f[x][0][1]!=id[i]) {
	  if (f[y][0][1]!=f[x][0][1]) {
	    f[y][1][0] = f[y][0][0];
	    f[y][1][1] = f[y][0][1];
	  }
	  f[y][0][0] = f[x][0][0]+val[i];
	  f[y][0][1] = f[x][0][1];
	  flag = true;
	} else if (f[y][1][0]>f[x][0][0]+val[i] && f[y][0][1]!=f[x][0][1] && f[x][0][1]!=id[i]) {
	  f[y][1][0] = f[x][0][0]+val[i];
	  f[y][1][1] = f[x][0][1];
	  flag = true;
	}
	if (f[y][0][0]>f[x][1][0]+val[i] && f[x][1][1]!=id[i]) {
	  if (f[y][0][1]!=f[x][1][1]) {
	    f[y][1][0] = f[y][0][0];
	    f[y][1][1] = f[y][0][1];
	  }
	  f[y][0][0] = f[x][1][0]+val[i];
	  f[y][0][1] = f[x][1][1];
	  flag = true;
	} else if (f[y][1][0]>f[x][1][0]+val[i] && f[y][0][1]!=f[x][1][1] && f[x][1][1]!=id[i]) {
	  f[y][1][0] = f[x][1][0]+val[i];
	  f[y][1][1] = f[x][1][1];
	  flag = true;
	}
	if (flag && !book[y]) {
	  book[y] = true;
	  tail = tail%(n+1)+1;
	  que[tail] = y;
	}
      }
    }
    return f[t][0][0];
  }
};

int main() {
#ifdef DEBUG
  freopen("2702.in", "r", stdin);
  freopen("2702.out", "w", stdout);
#endif

  static Graph graph;
  int n, m;
  scanf("%d %d", &n, &m);
  for (int i=1; i<=m; i++) {
    int s, t, w, v;
    scanf("%d %d %d %d", &s, &t, &w, &v);
    graph.addSide(s, t, w, i);
    graph.addSide(t, s, v, i);
    if (s==1) {
      graph.addSide(0, t, w, i);
      graph.addSide(t, 0, v, i);
    } else if (t==1) {
      graph.addSide(s, 0, w, i);
      graph.addSide(0, s, v, i);
    }
  }
  graph.init(n);

  printf("%d", graph.solve(1, 0));

  fclose(stdin);
  fclose(stdout);
  return 0;
}
