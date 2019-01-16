#define DEBUG
#include <cstdio>
#include <cassert>
#define MAXN 1000
#define MAXM 1000

using namespace std;

bool solve(int mat[MAXN+100][MAXM+100], int o[][2], int peek[][2], int n, int m) {
  for (int t=o[0][1]; t; t=o[t][1]) {
    int i=t/m+1, j=t%m;
    mat[i][j] = 0;
    int temp=i*m+j-m;
    o[o[temp][0]][1] = o[temp][1];
    o[o[temp][1]][0] = o[temp][0];
    for (int k=2; k<=peek[0][0]; k++) {
      int x=i+peek[k][0], y=j+peek[k][1];
      if (x>0 && y>0 && x<=n && y<=m && mat[x][y]) {
	mat[x][y] = 0;
	temp=x*m+y-m;
	o[o[temp][0]][1] = o[temp][1];
	o[o[temp][1]][0] = o[temp][0];
      } else {
	return false;
      }
    }
  } 
  return true;
}

int main() {
#ifdef DEBUG
  freopen("4761.in", "r", stdin);
  freopen("4761.out", "w", stdout);
#endif

  int t;
  scanf("%d", &t);
  for (int ti=1; ti<=t; ti++) {
    int n, m, a, b;
    scanf("%d %d %d %d", &n, &m, &a, &b);
    static int mat[MAXN+100][MAXM+100], peek[MAXN*MAXM+100][2], o[MAXN*MAXM+100][2];
    o[0][0] = o[0][1] = 0;
    for (int i=1; i<=n; i++) {
      for (int j=1; j<=m; j++) {
	scanf("%1d", &mat[i][j]);
	if (mat[i][j]) {
	  int v=i*m+j-m;;
	  o[o[0][0]][1] = o[0][0] = v;
	  o[v][0] = o[0][0], o[v][1] = 0;
	}
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
    
    printf(solve(mat, o, peek, n, m) ? "YES\n" : "NO\n");
  }

  fclose(stdin);
  fclose(stdout);
  return 0;
}
