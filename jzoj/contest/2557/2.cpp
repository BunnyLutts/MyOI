#define DEBUG
#include <cstdio>
#include <cstring>
#define MAXN 1001

using namespace std;

int f[MAXN+1][MAXN+1][2];
char s[MAXN+2];

int main() {
#ifdef DEBUG
  freopen("2.in", "r", stdin);
  freopen("2.out", "w", stdout);
#endif

  scanf("%s", s+2);
  int n = strlen(s+2)+1;
  for (int i=1; i<=n; i++) {
    f[1][i][1] = 1;
  }
  for (int i=2; i<=n; i++) {
    int sum=f[i-1][1][1]+f[i-1][1][0];
    if (s[i]=='?' || s[i]=='I') {
      for (int j=2; j<=n; j++) {
	f[i][j][1] = sum;
	sum += f[i-1][j][0]+f[i-1][j][1];
      }
    }
    sum = f[i-1][n][1]+f[i-1][n][0];
    if (s[i]=='?' || s[i]=='D') {
      for (int j=n-1; j>0; j--) {
	f[i][j][0] = sum;
	sum += f[i-1][j][0]+f[i-1][j][1];
      }
    }
  }

  #ifdef DEBUG
  for (int i=1; i<=n; i++) {
    for (int j=1; j<=n; j++) {
      printf("(%d,%d) ", f[i][j][0], f[i][j][1]);
    }
    printf("\n");
  }
  #endif

  int ans=0;
  for (int i=1; i<=n; i++) {
    ans += f[n][i][0]+f[n][i][1];
  }
  printf("%d", ans);

  fclose(stdin);
  fclose(stdout);
  return 0;
}
