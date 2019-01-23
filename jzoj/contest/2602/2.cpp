#define DEBUG
#include <cstdio>
#define INF 0x7ffffff
#define MAXM 100002 

using namespace std;

int abs(int a) {
  return a>0 ? a : -a;
}

int min(int a, int b) {
  return a<b ? a : b;
}

class Point {
public:
  int x, y, ref;

  static bool cmpRow(Point x, Point y) {
    return x.x<y.x || (x.x==y.x && x.y<y.y);
  }

  static bool cmpCol(Point x, Point y) {
    return x.y<y.y || (x.y==y.y && x.x<y.x);
  }
};

void sort(Point *a, int l, int r, bool cmp(Point, Point), int map[][2], int o) {
  int i=l, j=r;
  Point mid=a[(l+r)/2], temp;
  for (; i<=j; ) {
    for (; cmp(mid, a[j]); j--);
    for (; cmp(a[i], mid); i++);
    if (i<=j) {
      temp=a[i], a[i]=a[j], a[j]=temp;
      map[a[i].ref][o] = i, map[a[j].ref][o] = j;
      i++, j--;
    }
  }
  if (i<r) {
    sort(a, i, r, cmp, map, o);
  }
  if (j>l) {
    sort(a, l, j, cmp, map, o);
  }
}

int main() {
#ifdef DEBUG
  freopen("2.in", "r", stdin);
  freopen("2.out", "w", stdout);
#endif

  Point row[MAXM+1], col[MAXM+1];
  static int map[MAXM+1][2];
  int n, m;
  scanf("%d %d", &n, &m);
  for (int i=1; i<=m+2; i++) {
    scanf("%d %d", &row[i].x, &row[i].y);
    row[i].ref = i;
    col[i] = row[i];
    map[i][0] = map[i][1] = i;
  }

  sort(row, 1, m+2, Point::cmpRow, map, 0);
  sort(col, 1, m+2, Point::cmpCol, map, 1);

  static int dis[MAXM+1][2], que[2*MAXM+1][2];
  static bool book[MAXM+1][2];
  for (int i=1; i<=m+2; i++) {
    for (int j=0; j<2; j++) {
      dis[i][j] = INF;
    }
  }
  for (int i=0; i<2; i++) {
    dis[m+1][i] = 0;
    book[m+1][i] = true;
    que[i+1][0] = m+1, que[i+1][1] = i;
  }
  for (int h=0, t=2; h!=t; ) {
    h = h%(2*m+4)+1;
    int x=que[h][0], u=que[h][1];
    book[x][u] = false;
    if (row[map[x][0]-1].x==row[map[x][0]].x) {
      int y=row[map[x][0]-1].ref, v=0, turn= v!=u, l=abs(row[map[x][0]].y-row[map[y][0]].y);
      if (dis[y][v]>dis[x][u]+turn+2*l) {
	dis[y][v] = dis[x][u]+turn+2*l;
	if (!book[y][v]) {
	  t = t%(2*m+4)+1;
	  que[t][0] = y, que[t][1] = v;
	  book[y][v] = true;
	}
      }
    }
    if (row[map[x][0]+1].x==row[map[x][0]].x) {
      int y=row[map[x][0]+1].ref, v=0, turn= v!=u, l=abs(row[map[x][0]].y-row[map[y][0]].y);
      if (dis[y][v]>dis[x][u]+turn+2*l) {
	dis[y][v] = dis[x][u]+turn+2*l;
	if (!book[y][v]) {
	  t = t%(2*m+4)+1;
	  que[t][0] = y, que[t][1] = v;
	  book[y][v] = true;
	}
      }
    }
    if (col[map[x][1]-1].y==col[map[x][1]].y) {
      int y=col[map[x][1]-1].ref, v=1, turn= v!=u, l=abs(col[map[x][1]].x-col[map[y][1]].x);
      if (dis[y][v]>dis[x][u]+turn+2*l) {
	dis[y][v] = dis[x][u]+turn+2*l;
	if (!book[y][v]) {
	  t = t%(2*m+4)+1;
	  que[t][0] = y, que[t][1] = v;
	  book[y][v] = true;
	}
      }
    }
    if (col[map[x][1]+1].y==col[map[x][1]].y) {
      int y=col[map[x][1]+1].ref, v=1, turn= v!=u, l=abs(col[map[x][1]].x-col[map[y][1]].x);
      if (dis[y][v]>dis[x][u]+turn+2*l) {
	dis[y][v] = dis[x][u]+turn+2*l;
	if (!book[y][v]) {
	  t = t%(2*m+4)+1;
	  que[t][0] = y, que[t][1] = v;
	  book[y][v] = true;
	}
      }
    }
  }

  if (dis[m+2][0]>=INF && dis[m+2][1]>=INF) {
    printf("-1");
  } else {
    printf("%d", min(dis[m+2][0], dis[m+2][1]));
  }

  fcloseall();
  return 0;
}
