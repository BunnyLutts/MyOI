#define DEBUG
#include <cstdio>
#include <cassert>
#define MAXN 20000

using namespace std;

struct Set {
  int fa, size;
};

void swap(int &a, int &b) {
  int t;
  t=a, a=b, b=t;
}

void sort(int *a, int *b, int *w, int l, int r) {
  int i=l, j=r, mid=w[(l+r)/2];
  for (; i<=j; ) {
    for (; i<=j && w[j]>mid; j--);
    for (; i<=j && w[i]<mid; i++);
    if (i<=j) {
      swap(a[i], a[j]), swap(b[i], b[j]), swap(w[i], w[j]);
      i++, j--;
    }
  }
  if (i<r) {
    sort(a, b, w, i, r);
  }
  if (j>l) {
    sort(a, b, w, l, j);
  }
}

void init(Set *set, int n) {
  for (int i=1; i<=n; i++) {
    set[i].fa = i, set[i].size = 1;
  }
}

int getFa(Set *set, int o) {
  if (set[o].fa!=o) {
    set[o].fa = getFa(set, set[o].fa);
  }
  return set[o].fa;
}

void merge(Set *set, int x, int y) {
  if (getFa(set, x)!=getFa(set, y)) {
    set[getFa(set, y)].size += set[getFa(set, x)].size;
    set[getFa(set, x)].fa = getFa(set, y);
  }
}

int main() {
#ifdef DEBUG
  freopen("2940.in", "r", stdin);
  freopen("2940.out", "w", stdout);
#endif

  int t;
  scanf("%d", &t);
  for (int ti=1; ti<=t; ti++) {
    static int a[MAXN], b[MAXN], w[MAXN];
    static Set set[MAXN+1];
    int n;
    scanf("%d", &n);
    for (int i=1; i<n; i++) {
      scanf("%d %d %d", a+i, b+i, w+i);
    }
    sort(a, b, w, 1, n-1);

    init(set, n);
    long long ans=0;
    for (int i=1; i<n; i++) {
      ans += (long long)set[getFa(set, a[i])].size*set[getFa(set, b[i])].size*(w[i]+1)-1;
      merge(set, a[i], b[i]);
    }
    printf("%lld\n", ans);
  } 

  fcloseall();
  return 0;
}
