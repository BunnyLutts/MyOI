#define DEBUG
#include <cstdio>
#include <cstring>
#define MODS 1000000007
#define MAXN 1001

using namespace std;

char s[MAXN+1];
long long f[MAXN+1][MAXN+1];
int n;

int main() {
#ifdef DEBUG
  freopen("5219.in", "r", stdin);
  freopen("5219.out", "w", stdout);
#endif

  scanf("%s", s+1);
  n = strlen(s+1)+1;
  f[1][1] = 1;
  for (int i=2; i<=n; i++) {
    long long sum=f[i-1][1];
    if (s[i-1]=='?' || s[i-1]=='I') {
      for (int j=2; j<=i; j++) {
	f[i][j] = (f[i][j]+sum)%MODS;
	sum = (f[i-1][j]+sum)%MODS;
      }
    }
    sum=0;
    if (s[i-1]=='?' || s[i-1]=='D') {
      for (int j=i-1; j>0; j--) {
	sum = (sum+f[i-1][j])%MODS;
	f[i][j] = (f[i][j]+sum)%MODS;
      }
    }
  }
  
  long long ans=0;
  for (int i=1; i<=n; i++) {
    ans = (ans+f[n][i])%MODS;
  }
  printf("%lld", ans);

  fclose(stdin);
  fclose(stdout);
  return 0;
}
