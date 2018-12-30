#define DEBUG
#include <cstdio>
#define MODS 1000000007
#define MAXN 5000
#define MAXH 5000

using namespace std;

int min(int a, int b) {
  return a<b ? a : b;
}

int max(int a, int b) {
  return a>b ? a : b;
}

int main() {
  freopen("brick.in", "r", stdin);
  freopen("brick.out", "w", stdout);

  static int h[MAXN+1], f[MAXN+1][MAXH+2];
  int n;
  scanf("%d", &n);
  for (int i=1; i<=n; i++) {
    scanf("%d", h+i);
  }
  if (h[1]!=-1 && h[1]!=0) {
    printf("0");
    return 0;
  }
  f[1][0] = 1;
  for (int i=2, l=0, r=0; i<=n; i++) {
    if (h[i]>=0) {
      l = r = h[i];
    } else {
      l = max(0, l-1), r=min(MAXH+1, r+1);
    }
    bool flag=false;
    for (int j=l; j<=r; j++) {
      for (int k=-1; k<=1; k++) {
	if (j+k>=0 && j+k<=MAXH+1) {
	  f[i][j] = (f[i][j]+f[i-1][j+k])%MODS;
	  if (f[i][j]>0) {
	    flag = true;
	  }
	}
      }
    }
    if (!flag) {
      printf("1");
      return 0;
    }
  }
  printf("%d", f[n][0]);

  fclose(stdin);
  fclose(stdout);
  return 0;
}
