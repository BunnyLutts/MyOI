#define DEBUG
#include <cstdio>
#define MAXN 1000000000
#define MAXM 100000

using namespace std;

int min(int a, int b);
int max(int a, int b);

class SegmentTree {
public:
  SegmentTree *left, *right;
  int l, r, mark;

  SegmentTree(int l, int r) {
    this->l = l, this->r = r;
    mark = 0;
    left = right = NULL;
  }

  int get(int t) {
    if (l==r) {
      return mark;
    } else {
      int mid=(l+r)/2;
      if (t<=mid) {
	return left ? mark+left->get(t) : mark;
      } else {
	return right ? mark+right->get(t) : mark;
      }
    }
  }

  void set(int tl, int tr, int tv) {
    if (l==tl && r==tr) {
      mark += tv;
    } else {
      int mid=(l+r)/2;
      if (tl<=mid && tr>=l) {
	if (!left) {
	  left = new SegmentTree(l, mid);
	}
	left->set(max(l, tl), min(mid, tr), tv);
      }
      if (tl<=r && tr>mid) {
	if (!right) {
	  right = new SegmentTree(mid+1, r);
	}
	right->set(max(mid+1, tl), min(r, tr), tv);
      }
    }
  }
};

int min(int a, int b) {
  return a<b ? a : b;
}

int max(int a, int b) {
  return a>b ? a : b ;
}

void change(SegmentTree *sgt, int pos, int val, int n, int a, int p, int tv) {
    int l, r;
    if (val) {
      l=(p-a*pos%n+n)%n, r=n-1-a*pos%n;
    } else {
      l=n-a*pos%n, r=(p-1-a*pos%n+n)%n;
    }
    if (l<=r) {
      sgt->set(l, r, tv);
    } else {
      sgt->set(0, r, tv);
      sgt->set(l, n-1, tv);
    }
}

int main() {
#ifdef DEBUG
  freopen("4417.in", "r", stdin);
  freopen("4417.out", "w", stdout);
#endif

  static int c[MAXM+1];
  int n, a, b, p, m, q;
  scanf("%d %d %d %d %d", &n, &a, &b, &p, &m);
  SegmentTree *sgt=new SegmentTree(0, n-1);
  for (int i=0; i<m; i++) {
    scanf("%1d", c+i);
    change(sgt, i, c[i], n, a, p, 1);
  }
  scanf("%d", &q);
  for (int i=1; i<=q; i++) {
    char s[7];
    int x;
    scanf(" %s %d ", s, &x);
    if (s[0]=='Q') {
      printf("%d\n", m-sgt->get((a*x+b)%n));
    } else {
      change(sgt, x, c[x], n, a, p, -1);
      c[x] = !c[x];
      change(sgt, x, c[x], n, a, p, +1);
    }
  }

  fcloseall();
  return 0;
}
