#define DEBUG
#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAXN 50
#define MAXC 20
#define MAXAB 40
#define MAXL (MAXN*MAXC*MAXAB)

using namespace std;

int main() {
#ifdef DEBUG
  freopen("0.in", "r", stdin);
  freopen("0.out", "w", stdout);
#endif // DEBUG

  static int a[MAXN+1], b[MAXN+1], c[MAXN+1], d[MAXN+1], f[MAXN+1][MAXL*2+1], suf[MAXN+2][2];
  int n;
  scanf("%d", &n);
  for (int i=1; i<=n; i++) {
    scanf("%d %d %d %d", a+i, b+i, c+i, d+i);
  }
  for (int i=n; i>0; i--) {
    if (a[i]*c[i]>b[i]*c[i]) {
      suf[i][1] = suf[i+1][1]+a[i]*c[i];
      suf[i][0] = suf[i+1][0]+b[i]*c[i];
    } else {
      suf[i][0] = suf[i+1][0]+a[i]*c[i];
      suf[i][1] = suf[i+1][1]+b[i]*c[i];
    }
  }

  memset(f, 128, sizeof(f));

  f[0][MAXL] = 0;
  for (int i=1; i<=n; i++) {
    for (int j=-suf[i+1][1]; j<=-suf[i+1][0]; j++) {
      for (int k=a[i]; k<=b[i]; k++) {
	if (j-c[i]*k+MAXL>=0 && j-c[i]*k+MAXL<=2*MAXL) {
	  if (f[i][j+MAXL]<f[i-1][j-c[i]*k+MAXL]+k*d[i]) {
	    f[i][j+MAXL] = f[i-1][j-c[i]*k+MAXL]+k*d[i];
	  }
	}
      }
    }
  }

  printf("%d", f[n][MAXL]);

  fclose(stdin);
  fclose(stdout);
  return 0;
}
