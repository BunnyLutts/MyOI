#define DEBUG
#include <cstdio>
#include <cmath>
#define MODS 1000000007
#define MAXN 10000
#define MAXD 100
#define MAXK 100
#define MAXLOGN 17

using namespace std;

long long qpower(long long a, long long n) {
  long long s=1;
  for (; n>1; n/=2) {
    if (n%2) {
      s = (s*a)%MODS;
    }
    a = (a*a)%MODS;
  }
  return (s*a)%MODS;
}

long long c(long long n, long long m) {
  long long ret = 1;
  for (int i=1; i<=n; i++) {
    ret = ((ret*(m-i+1))%MODS*qpower(i, MODS-2))%MODS;
  }
  return ret;
}

int main() {
  #ifdef DEBUG
  freopen("2368.in", "r", stdin);
  freopen("2368.out", "w", stdout);
  #endif

  static long long f[MAXLOGN+2][MAXN+1];
  int n, k, d, t;
  scanf("%d %d %d", &n, &k, &d);
  t=log2(n);
  if ((1<<t)<n) {
    t++;
  }

  f[0][0] = 1;
  for (int i=0; i<=t; i++) {
    for (int j=0; j<=n-k; j++) {
      if (f[i][j]) {
	int temp;
	for (int q=0; (temp=j+q*(d+1)*(1<<i))<=n-k && (q*(d+1))<=k/2; q++) {
	  f[i+1][temp] = (f[i+1][temp]+f[i][j]*c(q*(d+1), k/2))%MODS;
	}
      }
    }
  }

  long long ans=0;
  for (int i=0; i<=n; i++) {
    ans = (ans+(f[t+1][i]*c(k/2, n-k/2-i))%MODS)%MODS;
  }
  printf("%lld", (c(k, n)+MODS-ans)%MODS);

  fclose(stdin);
  fclose(stdout);
  return 0;
}
