#define DEBUG
#include <cstdio>
#define MAXN 1000
#define MAXM 1000

using namespace std;

bool solve(int mat[MAXN+1][MAXM+1], int peek[][2], int n, int m) {
  for (int i=1; i<=n; i++) {
    for (int j=1; j<=m; j++) {
      if (mat[i][j]) {
	mat[i][j] = 0;
	for (int k=2; k<=peek[0][0]; k++) {
	  int x=i+peek[k][0], y=j+peek[k][1];
	  if (x>0 && y>0 && x<=n && y<=m && mat[x][y]) {
	    mat[x][y] = 0;
	  } else {
	    return false;
	  }
	}
      }
    }
  } 
  return true;
}

int main() {
#ifdef DEBUG
  freopen("0.in", "r", stdin);
  freopen("0.out", "w", stdout);
#endif

  int t;
  scanf("%d", &t);
  for (int ti=1; ti<=t; ti++) {
    int n, m, a, b;
    scanf("%d %d %d %d", &n, &m, &a, &b);
    static int mat[MAXN+1][MAXM+1], peek[MAXN*MAXM+1][2];
    for (int i=1; i<=n; i++) {
      for (int j=1; j<=m; j++) {
	scanf("%1d", &mat[i][j]);
      }
    } 
    peek[0][0] = 0;
    for (int i=1; i<=a; i++) {
      for (int j=1; j<=b; j++) {
	int temp;
	scanf("%1d", &temp);
	if (temp) {
	  if (peek[0][0]) {
	    peek[0][0]++;
	    peek[peek[0][0]][0] = i-peek[1][0];
	    peek[peek[0][0]][1] = j-peek[1][1];
	  } else {
	    peek[0][0]++;
	    peek[1][0] = i, peek[1][1] = j;
	  }
	}
      }
    }
    
    printf(solve(mat, peek, n, m) ? "YES\n" : "NO\n");
  }

  fclose(stdin);
  fclose(stdout);
  return 0;
}
