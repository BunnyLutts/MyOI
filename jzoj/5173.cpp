#define DEBUG
#include <cstdio>
#include <cmath>
#define MAXN 1000
#define MAXM 10000
#define MAXW 10000000
#define EPS 5.e-4

using namespace std;

int n, m, ind[MAXN+1], to[MAXM+1], link[MAXM+1];
double val[MAXM+1];

void addSide(int u, int v, double l) {
  m++;
  to[m] = v;
  val[m] = l;
  link[m] = ind[u];
  ind[u] = m;
}

bool belowCircle(long double x) {
  static double dis[2*MAXN+1];
  static int cnt[2*MAXN+1], q[2*MAXN+1];
  static bool book[2*MAXN+1];
  for (int i=1; i<=n; i++) {
    dis[i] = (double)MAXN*MAXW+1;
    cnt[i] = 0;
    book[i] = false;
  }
  for (int i=n; i>0; i--) {
    if (!cnt[i]) {
      dis[i] = 0, cnt[i] = 1, book[i] = true, q[1] = i;
      for (int head=0, tail=1; head!=tail; ) {
	head = head%(2*n)+1;
	book[q[head]]=false;
	for (int j=ind[q[head]]; j; j=link[j]) {
	  if (dis[to[j]]>=dis[q[head]]+val[j]-x) {
	    dis[to[j]] = dis[q[head]]+val[j]-x;
	    cnt[to[j]] = cnt[q[head]]+1;
	    if (cnt[to[j]]>n) {
	      return true;
	    }
	    if (!book[to[j]]) {
	      tail = tail%(2*n)+1;
	      q[tail] = to[j];
	      book[to[j]] = true;
	    }
	  }
	}
      }
    }
  }
  return false;
}

int main() {
#ifdef DEBUG
  freopen("5173.in", "r", stdin);
  freopen("5173.out", "w", stdout);
#endif

  int m;
  scanf("%d %d", &n, &m);
  for (int i=1; i<=m; i++) {
    int u, v, l;
    scanf("%d %d %d", &u, &v, &l);
    addSide(u, v, l);
  }

  double ans=-1;
  for (double l=0, r=MAXW, mid; l<=r; ) {
    mid = (l+r)/2;
    if (belowCircle(mid)) {
      r = mid-EPS;
      ans = mid;
    } else {
      l = mid+EPS;
    }
  }
  if (ans>=0) {
    printf("%.2lf", ans-0.0005);
  } else {
    printf("PaPaFish is laying egg!");
  }

  fclose(stdin);
  fclose(stdout);
  return 0;
}
