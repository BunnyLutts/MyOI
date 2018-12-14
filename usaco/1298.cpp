#define DEBUG
#include <cstdio>
#include <algorithm>
#define MAXN 50
#define MAXM 1023

using namespace std;

bool solve(int o, int x, int n, int m, int a[], int b[], int prea, int preb) {
  for (int i)
}

int main() {
#ifdef DEBUG
  freopen("1298.in", "r", stdin);
  freopen("1298.out", "w", stdout);
#endif

  static int a[MAXN+1], b[MAXM+1];
  int n, m;
  scanf("%d", &n);
  for (int i=1; i<=n; i++) {
    scanf("%d", a+i);
  }
  sort(a+1, a+n+1);
  scanf("%d", &m);
  for (int i=1; i<=m; i++) {
    scanf("%d", b+i);
  }
  sort(b+1, b+m+1);
  int temp=0;
  for (int i=1; i<=n; i++) {
    temp += a[i];
  }
  for (int i=1; i<=m; i++) {
    temp -= b[i];
    if (temp<0) {
      m = i-1;
    }
  }

  int ans=0;
  for (int l=1, r=m, mid; l<r; ) {
    mid = (l+r)/2;
    if (solve(1, mid, n, m, a, b)) {
      l = mid+1;
      ans = mid;
    } else {
      r = mid-1;
    }
  }
  printf("%d", ans);

  fclose(stdin);
  fclose(stdout);
  return 0;
}
