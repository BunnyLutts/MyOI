#define DEBUG
#include <cstdio>
#include <algorthm>
#define MAXN 100000

using namespace std;

class Candy {
public:
  int x, y, color;
};

int solve(Candy candy[], int n, int k) {
  //Bookmark
}

int main() {
#ifdef DEBUG
  freopen("5229.in", "r", stdin);
  freopen("5229.out", "w", stdout);
#endif

  int t;
  scanf("%d", &t);
  for (int ti=1; ti<=t; ti++) {
    int n, k;
    static Candy candy[MAXN+1];
    scanf("%d %d", &n, &k);
    for (int i=1; i<=n; i++) {
      scanf("%d %d %d", &candy[i].x, &candy[i].y, &candy[i].color);
    }
    int ans=solve(candy, n, k);
    for (int i=1; i<=n; i++){
      candy[i].y = -candy[i].y;
    }
    ans = max(ans, solve(candy, n, k));
    printf("%d\n", ans);
  }

  fclose(stdin);
  fclose(stdout);
  return 0;
}
