#define DEBUG
#include <cstdio>
#include <algorithm>
#include <cassert>

#define MAXN 5000
#define MAXK 100000

using namespace std;

class Candy {
public:
  int x, y, color;

  static bool cmpX(Candy a, Candy b) {
    return a.x<b.x;
  }
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

void makeHash(int n, Candy a[], int &xn, int &yn) {
  static HashEle x[MAXN+1], y[MAXN+1];
  for (int i=1; i<=n; i++) {
    x[i].init(&a[i].x);
    y[i].init(&a[i].y);
  }
  sort(x+1, x+n+1, HashEle::cmp);
  sort(y+1, y+n+1, HashEle::cmp);
  int p=1;
  *x[1].p=1;
  for (int i=1; i<=n; i++) {
    if (x[i].v!=x[i-1].v) {
      p++;
    }
    *x[i].p=p;
  }
  xn = p;
  p=1;
  *y[1].p=1;
  for (int i=1; i<=n; i++) {
    if (y[i].v!=y[i-1].v) {
      p++;
    }
    *y[i].p=p;
  }
  yn = p;
}

int solve(int n, int k, Candy candy[], int xn, int yn) {
  static int bucket[MAXK+1][2];
  int ans=0, ver=0;
  sort(candy+1, candy+n, Candy::cmpX);
  for (int i=1; i<=yn; i++) {
    ver++;
    bucket[0][0] = ver;
    bucket[0][1] = 0;
    for (int h=1, t=1, ph=1, pt=1; t<=xn; t++) {
      for (; pt<=n && candy[pt].x<=t; pt++) {
	if (candy[pt].y<=i) {
	  if (bucket[candy[pt].color][0]!=ver) {
	    bucket[candy[pt].color][0] = ver;
	    bucket[candy[pt].color][1] = 0;
	  }
	  if (!bucket[candy[pt].color][1]) {
	    bucket[0][1]++;
	  }
	  bucket[candy[pt].color][1]++;
	}
      }
      for (; h<=t && bucket[0][1]>=k; h++) {
	for (; candy[ph].x<h; ph++) {
	  if (candy[pt].y<=i) {
	    assert(bucket[candy[pt].color][0]==ver);
	    bucket[candy[pt].color][1]--;
	    if (!bucket[candy[pt].color][1]) {
	      bucket[0][1]--;
	    }
	  }
	}
      }
      ans = max(ans, pt-ph);
    }
  }
  for (int i=1; i<=yn; i++) {
    ver++;
    bucket[0][0] = ver;
    bucket[0][1] = 0;
    for (int h=1, t=1, ph=1, pt=1; t<=xn; t++) {
      for (; pt<=n && candy[pt].x<=t; pt++) {
	if (candy[pt].y>=i) {
	  if (bucket[candy[pt].color][0]!=ver) {
	    bucket[candy[pt].color][0] = ver;
	    bucket[candy[pt].color][1] = 0;
	  }
	  if (!bucket[candy[pt].color][1]) {
	    bucket[0][1]++;
	  }
	  bucket[candy[pt].color][1]++;
	}
      }
      for (; h<=t && bucket[0][1]>=k; h++) {
	for (; candy[ph].x<h; ph++) {
	  if (candy[pt].y>=i) {
	    assert(bucket[candy[pt].color][0]==ver);
	    bucket[candy[pt].color][1]--;
	    if (!bucket[candy[pt].color][1]) {
	      bucket[0][1]--;
	    }
	  }
	}
      }
      ans = max(ans, pt-ph);
    }
  }
  return ans;
}

int main() {
#ifdef DEBUG
  freopen("1.in", "r", stdin);
  freopen("1.out", "w", stdout);
#endif

  int t;
  scanf("%d", &t);
  for (int ti=1; ti<=t; ti++) {
    static Candy candy[MAXN+1];
    int n, k, xn, yn;
    scanf("%d %d", &n, &k);
    for (int i=1; i<=n; i++) {
      scanf("%d %d %d", &candy[i].x, &candy[i].y, &candy[i].color);
    }
    makeHash(n, candy, xn, yn);
    printf("%d\n", solve(n, k, candy, xn, yn));
  }

  fclose(stdin);
  fclose(stdout);
  return 0;
}
