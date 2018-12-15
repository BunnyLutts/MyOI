#define DEBUG
#include <cstdio>
#define MAXN 200
#define MAXM 200

using namespace std;

bool dfs(int x, int y, int a, int b, int n, int m, int map[MAXN+1][MAXM+1], bool book[MAXN+1][MAXM+1]) {
  if (x==a && y==b) {
    return true;
  }
  book[x][y] = true;
  if (x+1<=n && !map[x+1][y] && !book[x+1][y]) {
    if (dfs(x+1, y, a, b, n, m, map, book)) {
      return true;
    }
  }
  if (y+1<=m && !map[x][y+1] && !book[x][y+1]) {
    if (dfs(x, y+1, a, b, n, m, map, book)) {
      return true;
    }
  }
  return false;
}

void dfs(int x, int y, int n, int m, bool flag[51][51], int map[MAXN+1][MAXM+1]) {
  flag[x][y] = true;
  if (x+1<=n && !map[x+1][y] && !flag[x+1][y]) {
    dfs(x+1, y, n, m, flag, map);
  }
  if (y+1<=m && !map[x][y+1] && !flag[x][y+1]) {
    dfs(x, y+1, n, m, flag, map);
  }
}

int main() {
#ifdef DEBUG
  freopen("2.in", "r", stdin);
  freopen("2.out", "w", stdout);
#endif

  static int map[MAXN+1][MAXM+1];
  static bool f[51][51][51][51], temp[MAXN+1][MAXM+1];
  int n, m;
  scanf("%d", &n);
  bool type = n<=50 && m<=50;
  for (int i=1; i<=n; i++) {
    for (int j=1; j<=m; j++) {
      scanf("%1d", &map[i][j]);
    }
  }

  scanf("%d", &m);
  if (type) {
    for (int i=1; i<=n; i++) {
      for (int j=1; j<=m; j++) {
	dfs(i, j, n, m, f[i][j], map);
      }
    }
  }
  for (int i=1; i<=m; i++) {
    int x, y, a, b;
    scanf("%d %d %d %d", &x, &y, &a, &b);
    if (type) {
      printf(f[x][y][a][b] ? "Safe\n" : "Dangerous\n");
    } else {
      for (int i=1; i<=n; i++) {
	for (int j=1; j<=m; j++) {
	  temp[i][j] = false;
	}
      }
      printf(dfs(x, y, a, b, n, m, map, temp) ? "Safe\n" : "Dangerous\n");
    }
  }

  fclose(stdin);
  fclose(stdout);
 
  return 0;
}
