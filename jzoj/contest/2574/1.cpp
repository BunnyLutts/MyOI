#define DEBUG
#include <cstdio>
#define INF 0x7ffffff
#define MAXN 5000

using namespace std;

int max(int a, int b) {
  return a>b ? a : b;
}

void print(int f[MAXN+2][MAXN+2][4], int x, int y, int *a) {
  if (x) {
    print(f, f[x][y][2], f[x][y][3], a);
    printf("%d ", a[x]);
  }
}

int main() {
#ifdef DEBUG
  freopen("1.in", "r", stdin);
  freopen("1.out", "w", stdout);
#endif

  static int a[MAXN+2], b[MAXN+2], f[MAXN+2][MAXN+2][4];
  int n, m;
  scanf("%d", &n);
  for (int i=1; i<=n; i++) {
    scanf("%d", a+i);
  }
  a[++n] = INF;
  scanf("%d", &m);
  for (int i=1; i<=m; i++) {
    scanf("%d", b+i);
  }
  b[++m] = INF;

  for (int i=1; i<=n; i++) {
    for (int j=1; j<=m; j++) {
      if (a[i]==b[j]) {
	int x = ++f[i][0][0];
	f[i][x][0] = j;
	f[i][x][1] = 1;
	for (int k=1; k<=i; k++) {
	  if (a[k]<a[i]) {
	    for (int l=1; l<=f[k][0][0] && f[k][l][0]<j; l++) {
	      if (f[i][x][1]<f[k][l][1]+1) {
		f[i][x][2] = k;
		f[i][x][3] = l;
		f[i][x][1] = f[k][l][1]+1;
	      }
	    }
	  }
	}
      }
    }
  }

  printf("%d\n", f[n][f[n][0][0]][1]-1);
  print(f, f[n][f[n][0][0]][2], f[n][f[n][0][0]][3], a);

  fclose(stdin);
  fclose(stdout);
  return 0;
}
