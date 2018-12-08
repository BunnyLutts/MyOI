#define DEBUG
#include <cstdio>
#include <algorithm>
#define MAXN 50
#define MAXR 1024

using namespace std;

int main() {
#ifdef DEBUG
  freopen("1298.in", "r", stdin);
  freopen("1298.out", "w", stdout);
#endif

  static int board[MAXN+1], target[MAXR+1];
  int n, r;
  scanf("%d", &n);
  for (int i=1; i<=n; i++) {
    scanf("%d", board+i);
  }
  sort(board+1, board+n+1);
  scanf("%d", &r);
  for (int i=1; i<=r; i++) {
    scanf("%d", target+i);
  }
  sort(target+1, target+r+1);

  int ans=0;
  for (int i=1, j=1; i<=n; i++) {
    for (; board[i]>=target[j]; board[i]-=target[j], j++) ans++;
  }
  printf("%d\n", ans);
  

  fclose(stdin);
  fclose(stdout);
  return 0;
}
