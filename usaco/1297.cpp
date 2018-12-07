#define DEBUG
#include <cstdio>
#include <algorithm>
#define INF 2000000000
#define MAXN 10
#define MAXA 256
#define X (MAXA*MAXA-2*MAXA)

using namespace std;

int gcd(int a, int b) {
  for (int r=a%b; r; a=b, b=r, r=a%b);
  return b;
}

int main() {
#ifdef DEBUG
  freopen("1297.in", "r", stdin);
  freopen("1297.out", "w", stdout);
#endif

  static int a[MAXN+1];
  static bool f[X+1];
  int n, temp;
  scanf("%d", &n);
  for (int i=1; i<=n; i++) {
    scanf("%d", a+i);
    temp = i==1 ? a[i] : gcd(temp, a[i]);
  }
  
  long long ans=0;
  if (temp==1) {
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
  } else {
    ans = INF%temp ? INF : INF-1;
  }

  printf("%lld", ans);

  fclose(stdin);
  fclose(stdout);
  return 0;
}
