#define DEBUG
#include <cstdio>
#define MAXN 80
#define MAXM 80
#define MAXK 10000

using namespace std;

void copy(int *t, int *s) {
  if (t!=s) {
    for (int i=0; i<=s[0]; i++) {
      t[i] = s[i];
    }
  }
}

int cmp(int *a, int *b) {
  if (a[0]<b[0]) {
    return -1;
  } else if (a[0]>b[0]) {
    return 1;
  } else {
    for (int i=a[0]; i>0; i--) {
      if (a[i]<b[i]) {
	return -1;
      } else if (a[i]>b[i]) {
	return 1;
      }
    }
  }
  return 0;
}

int* max(int *a, int *b) {
  return cmp(a, b)>0 ? a : b;
}

void add(int *t, int *a, int *b) {
  t[0] = a[0]>b[0] ? a[0] : b[0];
  for (int i=1; i<=t[0]+1; i++) {
    t[i] = 0;
  }
  for (int i=1; i<=t[0]; i++) {
    int x = i>a[0] ? 0 : a[i], y = i>b[0] ? 0 : b[i];
    t[i] += x+y;
    t[i+1] += t[i]/MAXK;
    t[i] %= MAXK;
  }
  t[0] = t[t[0]+1] ? t[0]+1 : t[0];
}

void mul(int *t, int *a, int *b) {
  for (int i=1; i<=a[0]+b[0]; i++) {
    t[i] = 0;
  }
  for (int i=1; i<=a[0]; i++) {
    for (int j=1; j<=b[0]; j++) {
      t[i+j-1] += a[i]*b[j];
      t[i+j] += t[i+j-1]/MAXK;
      t[i+j-1] %= MAXK;
    }
  }
  t[0] = t[a[0]+b[0]] ? a[0]+b[0] : a[0]+b[0]-1;
}

int main() {
  freopen("game.in", "r", stdin);
  freopen("game.out", "w", stdout);

  static int mat[MAXN+1][MAXM+1][2];
  int n, m;
  scanf("%d %d", &n, &m);
  for (int i=1; i<=n; i++) {
    for (int j=1; j<=m; j++) {
      scanf("%d", &mat[i][j][1]);
      mat[i][j][0] = 1;
    }
    mat[i][0][0] = 1, mat[i][0][1] = m;
  }

  static int pow2[MAXM+1][31] = {{1, 1}}, two[2] = {1, 2}, sum[31], temp[4][31];
  for (int i=1; i<=m; i++) {
    mul(pow2[i], pow2[i-1], two);
  }

  static int f[MAXN+1][MAXM+2][MAXM+2][31];
  for (int i=1; i<=n; i++) {
    for (int j=m-1; j>=0; j--) {
      mul(temp[2], mat[i][j+1], pow2[m-j]);
      add(f[i][j][1], temp[2], f[i][j+1][1]);
      for (int k=2; k<m-j+1; k++) {
	mul(temp[0], mat[i][k-1], pow2[m-j]);
	add(temp[1], temp[0], f[i][j+1][k-1]);
	mul(temp[2], mat[i][k+j], pow2[m-j]);
	add(temp[3], temp[2], f[i][j+1][k]);
	copy(f[i][j][k], max(temp[1], temp[3]));
      }
      mul(temp[0], mat[i][m-j], pow2[m-j]);
      add(f[i][j][m-j+1], temp[0], f[i][j+1][m-j]);
    }
    copy(temp[0], f[i][0][1]);
    for (int j=2; j<=m+1; j++) {
      copy(temp[0], max(temp[0], f[i][0][j]));
    }
    add(temp[1], sum, temp[0]);
    copy(sum, temp[1]);
  }
  
  printf("%d", sum[sum[0]]);
  for (int i=sum[0]-1; i>0; i--) {
    printf("%04d", sum[i]);
  }

  fclose(stdin);
  fclose(stdout);
  return 0;
}
