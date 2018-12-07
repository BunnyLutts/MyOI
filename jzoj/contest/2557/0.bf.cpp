#define DEBUG
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#define MAXN 20

using namespace std;

int t[MAXN+1], temp[MAXN+1], n;

class Array{
public:
  int v[MAXN+1];

  static bool cmp(Array x, Array y) {
    for (int i=1; i<=n; i++) {
      if (x.v[i]!=y.v[i]) {
	return x.v[i]<y.v[i];
      }
    }
    return false;
  }
} a[MAXN+1];

bool check() {
  for (int i=2; i<=n; i++) {
    for (int j=1; j<=n; j++) {
      a[i].v[j] = a[1].v[(j+i-2)%n+1];
    }
  }
  sort(a+1, a+n+1, Array::cmp);

  for (int i=1; i<=n; i++) {
    if (a[i].v[n]!=t[i]) {
      return false;
    }
  }
  return true;
}

void generate(int o) {
  if (o>n) {
    for (int i=1; i<=n; i++) {
      a[1].v[i] = temp[i];
    }
    if (check()) {
      for (int i=1; i<=n; i++) {
	printf("%d ", a[1].v[i]);
      }
      exit(0);
    }
  } else {
    temp[o] = 0;
    generate(o+1);
    temp[o] = 1;
    generate(o+1);
  }
}

int main() {
#ifdef DEBUG
  freopen("0.in", "r", stdin);
  freopen("0.bf.out", "w", stdout);
#endif

  scanf("%d", &n);
  for (int i=1; i<=n; i++) {
    scanf("%d", t+i);
  }

  generate(1);

  fclose(stdin);
  fclose(stdout);
}
