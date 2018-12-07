#define DEBUG
#include <cstdio>
#include <algorithm>
#define MAXN 100000

using namespace std;

class SegmentTree {
public:
  int v[8*MAXN+1];

  void init() {
    for (int i=0; i<=8*MAXN; i++) {
      v[i] = 0;
    }
  }

  void add(int o, int l, int r, int t, int tv) {
    if (l==r) {
      v[o] += tv;
    } else {
      int mid = (l+r)/2;
      if (t<=mid) {
	add(o*2, l, mid, t, tv);
      } else {
	add(o*2+1, mid+1, r, t, tv);
      }
      v[o] = v[o*2]+v[o*2+1];
    }
  }

  int get(int o, int l, int r, int tl, int tr) {
    if (l==tl && r==tr) {
      return v[o];
    } else {
      int mid=(l+r)/2, ret=0;
      if (tr>=l && tl<=mid) {
	ret += get(o*2, l, mid, max(tl, l), min(tr, mid));
      }
      if (tr>mid && tl<=r) {
	ret += get(o*2+1, mid+1, r, max(tl, mid+1), min(tr, r));
      }
      return ret;
    }
  }
};

class Lines{
public:
  int p[MAXN+1], l[MAXN+1], r[MAXN+1], size;

  void init(int o, int x, int y) {
    size++;
    p[size] = o, l[size] = x, r[size] = y;
  }
};

class Point {
public:
  int x, y, flag;

  static bool cmp(Point x, Point y) {
    return x.x<y.x;
  }
};

class Points {
public:
  int size;
  Point p[MAXN*2+1];

  void init(int x, int y, int flag) {
    size++;
    this->p[size].x = x, this->p[size].y=y, this->p[size].flag=flag;
  }

  void mysort() {
    sort(p+1, p+size+1, Point::cmp);
  }
};

class HashEle {
public:
  int *pos, value;

  void init(int *x) {
    pos = x;
    value = *x;
  }

  static bool cmp(HashEle a, HashEle b) {
    return a.value<b.value;
  }
};

int init (Lines *q, Points *points, const Lines *linex, const Lines *liney, int x) {
  static HashEle xhash[2*MAXN+1], yhash[2*MAXN+1];
  int xhashsize=0, yhashsize=0;
  for (int i=1; i<=linex->size; i++) {
    if (linex->r[i]-linex->l[i]>2*x) {
      points->init(linex->l[i]+x, linex->p[i], +1);
      xhash[++xhashsize].init(&points->p[points->size].x);
      yhash[++yhashsize].init(&points->p[points->size].y);
      points->init(linex->r[i]-x, linex->p[i], -1);
      xhash[++xhashsize].init(&points->p[points->size].x);
      yhash[++yhashsize].init(&points->p[points->size].y);
    }
  }
  for (int i=1; i<=liney->size; i++) {
    if (liney->r[i]-liney->l[i]>2*x) {
      q->init(liney->p[i], liney->l[i]+x, liney->r[i]-x);
      xhash[++xhashsize].init(&q->p[q->size]);
      yhash[++yhashsize].init(&q->l[q->size]);
      yhash[++yhashsize].init(&q->r[q->size]);
    }
  }

  int px=0, py=0;
  if (xhashsize) {
    sort(xhash+1, xhash+xhashsize+1, HashEle::cmp);
    px=1;
    *xhash[1].pos = px;
    for (int i=2; i<=xhashsize; i++) {
      if (xhash[i].value!=xhash[i-1].value) {
	px++;
      }
      *xhash[i].pos = px;
    }
  }
  if (yhashsize) {
    sort(yhash+1, yhash+yhashsize+1, HashEle::cmp);
    py=1;
    *yhash[1].pos = py;
    for (int i=2; i<=yhashsize; i++) {
      if (yhash[i].value!=yhash[i-1].value) {
	py++;
      }
      *yhash[i].pos = py;
    }
  }

  points->mysort();
  return max(px, py);
}

bool solve(int x, const Lines *linex, const Lines *liney) {
  static Lines q;
  static Points points;
  int r=init(&q, &points, linex, liney, x);

  static SegmentTree sgt;
  sgt.init();
  for (int i=1, j=1; i<=q.size; i++) {
    for (; points.p[j].x<=q.p[i]; j++) {
      sgt.add(1, 1, r, points.p[j].y, points.p[j].flag);
    }
    if (sgt.get(1, 1, r, q.l[i], q.r[i])>0) {
      return true;
    }
  }
  return false;
}

int main() {
#ifdef DEBUG
  freopen("3838.in", "r", stdin);
  freopen("3838.out", "w", stdout);
#endif

  static Lines linex, liney;
  int n, maxlen=0;
  scanf("%d", &n);
  for (int i=1; i<=n; i++) {
    int x1, y1, x2, y2;
    scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
    if (y1==y2) {
      linex.init(y1, x1, x2);
      maxlen = max(maxlen, x2-x1);
    } else {
      liney.init(x1, y1, y2);
      maxlen = max(maxlen, y2-y1);
    }
  }

  int ans=0;
  for (int l=1, r=maxlen, mid; l<=r; ) {
    mid = (l+r)/2;
    if (solve(mid, &linex, &liney)) {
      ans = mid;
      l = mid+1;
    } else {
      r = mid-1;
    }
  }
  if (ans) {
    printf("%d", ans);
  } else {
    printf("Human intelligence is really terrible");
  }

  fclose(stdin);
  fclose(stdout);
  return 0;
}
