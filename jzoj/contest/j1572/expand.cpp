#define DEBUG
#include <cstdio>
#define MAXLEN 10000

using namespace std;

bool isNum(char x) {
  return x>='0' && x<='9';
}

bool isAlpha(char x) {
  return x>='a' && x<='z';
}

void expand(char *s, int u, char *t, int &v, int p1, int p2, int p3) {
  char temp[MAXLEN+1];
  int len=-1;
  for (char i=s[u-1]+1; i<s[u+1]; i++) {
    char t;
    if (p1==1) {
      t = i;
    } else if (p1==2) {
      if (isAlpha(i)) {
	t = i-'a'+'A';
      } else {
	t = i;
      }
    } else {
      t = '*';
    }
    for (int j=1; j<=p2; j++) {
      temp[++len] = t;
    }
  }

  if (p3==1) {
    for (int i=0; i<=len; i++) {
      t[++v] = temp[i];
    }
  } else {
    for (int i=len; i>=0; i--) {
      t[++v] = temp[i];
    }
  }
}

int main() {
  freopen("expand.in", "r", stdin);
  freopen("expand.out", "w", stdout);

  static char s[MAXLEN+1], ans[MAXLEN+1];
  int p1, p2, p3;
  scanf("%d %d %d %s", &p1, &p2, &p3, s);

  for (int i=0, p=-1; s[i]!='\0'; i++) {
    if (s[i]=='-' && i-1>=0 && s[i+1]-s[i-1]>0 && ((isNum(s[i+1]) && isNum(s[i-1])) || (isAlpha(s[i+1]) && isAlpha(s[i-1])))) {
      expand(s, i, ans, p, p1, p2, p3);
    } else {
      ans[++p] = s[i];
    }
  }

  printf("%s", ans);

  fclose(stdin);
  fclose(stdout);
  return 0;
}
