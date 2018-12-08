#define DEBUG
#include <cstdio>
#include <algorithm>
#define MAXN 5000

using namespace std;

class Point {
public:
  int x, y;
};

class HashEle {
public:
  int v, *p;

  void init(int *x) {
    p = x;
    v = *x;
  }

  static bool cmp(HashEle a, HashEle b) {
    return a.v<b.v;
  }
};

void makeHash(int n, Point a[n]) {
  static HashEle x[MAXN+1], y[MAXN+1];
  for (int i=1; i<=n; i++) {
  }
}

int main() {
  #ifdef DEBUG
  freopen("1.in", "r", stdin);
  freopen("1.out", "w", stdout);
  #endif

  int t;
  scanf("%d", &t);
  for (int ti=1; ti<=t; ti++) {
    static Point candy[MAXN+1];
    int n, k;
    scanf("%d %d", &n, &k);
    for (int i=1; i<=n; i++) {
      scanf("%d %d", &candy[i].x, &candy[i].y);
    }

    makeHash(n, candy);
  }

  fclose(stdin);
  fclose(stdout);
  return 0;
}
