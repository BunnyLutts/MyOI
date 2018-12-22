#define DEBUG
#include <cstdio>
#include <bitset>
#include <algorithm>
#define MAXN 500
#define MAXM 500
#define MAXQ 600000

using namespace std;

class Ques {
public:
  int x, y, a, b, pos, next, prev;

  static bool cmp(Ques a, Ques b) {
    return a.y<b.y;
  }
};

void backward(bitset<MAXM+1> f[MAXN+1][MAXM+1], int from, int to, int n, int map[MAXN+1][MAXM+1]) {
  for (int j=from-1; j>=to; j--) {
    for (int i=n; i>0; i--) {
      if (!map[i][j]) {
	f[i][j] = 0;
	if (i+1<=n && !map[i+1][j]) {
	  f[i][j] = f[i][j]|f[i+1][j];
	}
	if (!map[i][j+1]) {
	  f[i][j] = f[i][j]|f[i][j+1];
	}
      }
    }
  }
}

void forward(bitset<MAXM+1> g[MAXN+1][MAXM+1], int from, int to, int n, int map[MAXN+1][MAXM+1]) {
  for (int j=from+1; j<=to; j++) {
    for (int i=1; i<=n; i++) {
      if (!map[i][j]) {
	g[i][j] = 0;
	if (i-1>0 && !map[i-1][j]) {
	  g[i][j] = g[i][j]|g[i-1][j];
	}
	if (!map[i][j-1]) {
	  g[i][j] = g[i][j]|g[i][j-1];
	}
      }
    }
  }
}

void solve(int l, int r, int map[MAXN+1][MAXM+1], Ques que[], bool ans[], int n, int m, int q) {
  if (l>r) {
    return;
  }
  static bitset<MAXM+1> f[MAXN+1][MAXM+1], g[MAXN+1][MAXM+1];
  int mid = (l+r)/2;
  for (int i=n; i>0; i--) {
    if (!map[i][mid]) {
      f[i][mid] = 0;
      f[i][mid][i] = 1;
      if (i+1<=n && !map[i+1][mid]) {
	f[i][mid] = f[i][mid] | f[i+1][mid];
      }
    }
  }
  for (int i=1; i<=n; i++) {
    if (!map[i][mid]) {
      g[i][mid] = 0;
      g[i][mid][i] = 1;
      if (i-1>0 && !map[i-1][mid]) {
	g[i][mid] = g[i][mid] | g[i-1][mid];
      }
    }
  }
  backward(f, mid, l, n, map);
  forward(g, mid, r, n, map);
  for (int i=que[0].next; i<=q; i=que[i].next) {
    if (que[i].y>mid) {
      break;
    }
    if (que[i].y>=l && que[i].y<=mid && que[i].b>=mid && que[i].b<=r) {
      ans[que[i].pos] = (f[que[i].x][que[i].y] & g[que[i].a][que[i].b]).any();
      que[que[i].prev].next = que[i].next, que[que[i].next].prev = que[i].prev;
    }
  }
  solve(l, mid-1, map, que, ans, n, m, q);
  solve(mid+1, r, map, que, ans, n, m, q);
}

int main() {
#ifdef DEBUG
  freopen("100048.in", "r", stdin);
  freopen("100048.out", "w", stdout);
#endif

  static int map[MAXN+1][MAXM+1];
  int n, m;
  scanf("%d %d", &n, &m);
  for (int i=1; i<=n; i++) {
    for (int j=1; j<=m; j++) {
      scanf("%1d", &map[i][j]);
    }
  }

  static Ques ques[MAXQ+2];
  int q;
  scanf("%d", &q);
  for (int i=1; i<=q; i++) {
    scanf("%d %d %d %d", &ques[i].x, &ques[i].y, &ques[i].a, &ques[i].b);
    ques[i].pos = i;
  }
  sort(ques+1, ques+q+1, Ques::cmp);
  ques[0].next = 1, ques[q+1].prev = q;
  for (int i=1; i<=q; i++) {
    ques[i].prev = i-1;
    ques[i].next = i+1;
  }

  static bool ans[MAXQ+1];
  solve(1, m, map, ques, ans, n, m, q);
  for (int i=1; i<=q; i++) {
    printf(ans[i] ? "Safe\n" : "Dangerous\n");
  }

  fclose(stdin);
  fclose(stdout);
  return 0;
}
