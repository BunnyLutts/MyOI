#define DEBUG
#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAXN 200
#define MAXC 20
#define MAXAB 50
#define MAXL (MAXN*MAXC*MAXAB)

using namespace std;

int main() {
#ifdef DEBUG
  freopen("100044.in", "r", stdin);
  freopen("100044.out", "w", stdout);
#endif // DEBUG

  static int a[MAXN+1], b[MAXN+1], c[MAXN+1], d[MAXN+1], f[2][MAXL*2+1], suf[MAXN+2][2];
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
	  if (f[i%2][j+MAXL]<f[(i-1)%2][j-c[i]*k+MAXL]+k*d[i]) {
	    f[i%2][j+MAXL] = f[(i-1)%2][j-c[i]*k+MAXL]+k*d[i];
	  }
	}
      }
    }
  }

  printf("%d", f[n%2][MAXL]);

  fclose(stdin);
  fclose(stdout);
  return 0;
}
