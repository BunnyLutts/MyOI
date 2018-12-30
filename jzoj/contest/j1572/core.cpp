#define DEBUG
#include <cstdio>
#define INF 0x7ffffff
#define MAXN 300

using namespace std;

int min(int a, int b) {
  return a<b ? a : b;
}

int max(int a, int b) {
  return a>b ? a : b;
}

struct Tree {
  int n, m, ind[MAXN+1], to[MAXN*2], link[MAXN*2], val[MAXN*2];
  int dis[MAXN+1][MAXN+1], diameter;

  void addSide(int u, int v, int w) {
    m++;
    to[m] = v;
    val[m] = w;
    link[m] = ind[u];
    ind[u] = m;
  }

  int fareast(int o, int fa, int t, int d) {
    diameter = max(diameter, d);
    dis[t][o] = d;
    int ret=d;
    for (int i=ind[o]; i; i=link[i]) {
      if (to[i]!=fa) {
	ret = max(ret, fareast(to[i], o, t, d+val[i]));
      }
    }
    return ret;
  }

  void initdis() {
    for (int i=1; i<=n; i++) {
      fareast(i, 0, i, 0);
    }
  }

  int getAns(int o, int fa, int d, int s, bool &flag) {
    static int stack[MAXN+1][2];
    stack[++stack[0][0]][0] = o;
    stack[stack[0][0]][1] = d;
    int ret=INF;
    if (flag) {
      return INF;
    }
    if (d==diameter) {
      for (int h=1, t=1; t<=stack[0][0]; t++) {
	for (; stack[t][1]-stack[h][1]>s; h++);
	int ecc=0, temp;
	for (int i=1; i<=n; i++) {
	  temp=INF;
	  for (int j=h; j<=t; j++) {
	    temp = min(temp, dis[stack[j][0]][i]);
	  }
	  ecc = max(temp, ecc);
	}
	ret = min(ret, ecc);
      }
      flag = true;
    } else {
      for (int i=ind[o]; i; i=link[i]) {
	if (to[i]!=fa) {
	  ret = min(ret, getAns(to[i], o, d+val[i], s, flag));
	  if (flag) {
	    return ret;
	  }
	}
      }
    }
    stack[0][0]--;
    return ret;
  }

  int solve(int s) {
    initdis();
    int ret=INF;
    bool flag=false;
    for (int i=1; i<=n; i++) {
      ret = min(ret, getAns(i, 0, 0, s, flag));
    }
    return ret;
  }
};

int main() {
  freopen("core.in", "r", stdin);
  freopen("core.out", "w", stdout);

  static Tree tree;
  int n, s;
  scanf("%d %d", &n, &s);
  tree.n = n;
  for (int i=1; i<n; i++) {
    int u, v, w;
    scanf("%d %d %d", &u, &v, &w);
    tree.addSide(u, v, w);
    tree.addSide(v, u, w);
  }

  printf("%d", tree.solve(s));

  fclose(stdin);
  fclose(stdout);
  return 0;
}
