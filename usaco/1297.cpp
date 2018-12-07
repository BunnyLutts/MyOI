#define DEBUG
#include <cstdio>
#include <algorithm>
#define MAXN 10
#define MAXA 256
#define X (MAXA*MAXA-2*MAXA)

using namespace std;

int main() {
#ifdef DEBUG
  freopen("1297.in", "r", stdin);
  freopen("1297.out", "w", stdout);
#endif

  static int a[MAXN+1];
  static bool f[X+1];
  int n;
  scanf("%d", &n);
  for (int i=1; i<=n; i++) {
    scanf("%d", a+i);
  }
  
  int ans=0;
  f[0] = true;
  for (int i=0; i<=X; i++) {
    if (f[i]) {
      for (int j=1; j<=n; j++) {
	if (i+a[j]<=X) {
	  f[i+a[j]] = true;
	}
      }
    } else {
      ans = i;
    }
  }

  printf("%d", ans);

  fclose(stdin);
  fclose(stdout);
  return 0;
}
