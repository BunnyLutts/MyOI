#define DEBUG
#include <cstdio>
#define MAXN 1000
#define MAXM 1000

using namespace std;

int n, m, iq[MAXN+1], temp[MAXN+1], tmp[MAXN+1], a[MAXN+1];

int merge(int *a, int l, int r) {
     if (l==r) {
	  return 0;
     }
     int mid=(l+r)/2, ret= merge(a, l, mid) + merge(a, mid+1, r);
     for (int i=1, j=mid, k=l; k<=r; k++) {
	  if (j>r || (i<=mid && a[i]<a[j])) {
	       tmp[k] = a[i];
	       i++;
	  } else {
	       if (i<=mid) {
		    ret++;
	       }
	       tmp[k] = a[j];
	       j++;
	  }
     }
     for (int i=l; i<=r; i++) {
	  a[i] = tmp[i];
     }
     return ret;
}

int getAns() {
     for (int i=1; i<=n; i++) {
	  temp[i] = iq[i];
     }
     return merge(temp, 1, n);
}

int main() {
#ifdef DEBUG
     freopen("3.in", "r", stdin);
     freopen("3.out", "w", stdout);
#endif

     scanf("%d %d", &n, &m);
     for (int i=1; i<=n; i++) {
	  scanf("%d",  iq+i);
     }
     printf("%d\n", getAns());
     for (int i=1; i<=m; i++) {
	  int t;
	  scanf("%d", &t);
	  for (int i=t; i<=n; i++) {
	       if (iq[i]<=iq[t]) {
		    a[++a[0]] = iq[i];
	       }
	  }
	  merge(a, 1, a[0]);
	  for (int i=n; i>=t; i--) {
	       if (iq[i]<=iq[t]) {
		    iq[i] = a[a[0]--];
	       }
	  }
	  printf("%d\n", getAns());
     }

     fclose(stdin);
     fclose(stdout);
     return 0;
}
