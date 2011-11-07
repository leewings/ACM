/*
 *  SRC: POJ 1113
 * PROB: Wall
 * ALGO: Graham Scan(Convex Hull)
 * DATE: Jul 26, 2011 
 * COMP: g++
 *
 * Created by Leewings Ac
 */

#include <cstdio>
#include <cmath>
#include <algorithm>

using std::sort;
using std::swap;

const int MAX_N = 1000;
const double pi = acos(-1.0);
const double eps = 1e-12;

inline bool eq0(double x) { return fabs(x) < eps; }
inline bool eq(double x, double y) { return fabs(x - y) < eps; }
inline bool ls(double x, double y) { return x + eps < y; }
inline bool gr(double x, double y) { return x - eps > y; }

struct Point {
    double x, y;
    double agl;

    Point() { }
    Point(double _x, double _y) : x(_x), y(_y) { }

    bool operator <(const Point &other) const
    {
        if (!eq(y, other.y)) return ls(y, other.y);
        return ls(x, other.x);
    }

    Point operator -(const Point &other) const
    {
        return Point(x - other.x, y - other.y);
    }

    double sqlen() const { return x * x + y * y; }
    double length() const { return sqrt(sqlen()); }
};
typedef Point Vec;

inline double cross(const Vec &u, const Vec &v)
{
    return u.x * v.y - u.y * v.x;
}

Point ver[MAX_N];
int stack[MAX_N], top;

inline bool cmp(const Point &a, const Point &b)
{
    if (eq(a.agl, b.agl))
        return ls((a - ver[0]).sqlen(), (b - ver[0]).sqlen());
    return ls(a.agl, b.agl);
}

inline bool check(int p)
{
    Vec u = ver[stack[top - 1]] - ver[stack[top - 2]],
        v = ver[p] - ver[stack[top - 2]];
    return cross(u, v) > eps;
}

double graham_scan(int n)
{
    int min_ver = 0;
    for (int i = 1; i < n; i++)
        if (ver[i] < ver[min_ver]) min_ver = i;
    swap(ver[0], ver[min_ver]);

    for (int i = 1; i < n; i++)
        ver[i].agl = atan2(ver[i].y - ver[0].y, ver[i].x - ver[0].x);
    sort(ver + 1, ver + n, cmp);

    top = 0;
    stack[top++] = 0;
    stack[top++] = 1;
    for (int i = 2; i < n; i++) {
        while (top > 1 && !check(i)) top--;
        stack[top++] = i;
    }
    stack[top] = 0;

    double res = 0;
    for (int i = 0; i < top; i++)
        res += (ver[stack[i]] - ver[stack[i + 1]]).length();

    return res;
}

int main()
{
    int n, l;
    scanf("%d%d", &n, &l);
    for (int i = 0; i < n; i++)
        scanf("%lf%lf", &ver[i].x, &ver[i].y);

    printf("%.0f\n", graham_scan(n) + 2.0 * pi * l);

    return 0;
}
