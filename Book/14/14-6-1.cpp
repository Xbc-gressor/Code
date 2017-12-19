const int MAXN = 1100;
const double EPSILON = 1E-7;

struct point {
    double x, y;
    point (double x = 0, double y = 0): x(x), y(y) {}
    point operator + (point p) { return point(x + p.x, y + p.y); };
    point operator - (point p) { return point(x - p.x, y - p.y); };
    point operator * (double k) { return point(x * k, y * k); };
    point operator / (double k) { return point(x / k, y / k); };
};

typedef vector<point> polygon;

double norm(point a)
{
    return a.x * a.x + a.y * a.y;
}

double abs(point a)
{
    return sqrt(norm(a));
}

double dot(point a, point b)
{
    return a.x * b.x + a.y * b.y;
}

double cross(point a, point b)
{
    return a.x * b.y - a.y * b.x;
}

struct line
{
    point a, b;
    double angle;
};

double cp(point a, point b, point c)
{
    return cross(b - a, c - a);
}

bool cw(point a, point b, point c)
{
    return cp(a, b, c) < -EPSILON;
}

bool cmpLine(line p, line q)
{
    if (fabs(p.angle - q.angle) <= EPSILON)
        return cp(q.a, q.b, p.a) < EPSILON;
    return p.angle < q.angle;
}

bool cmpAngle(line p, line q)
{
    return fabs(p.angle - q.angle) <= EPSILON;
}

bool paralle(line p, line q)
{
    return fabs((p.a.x - p.b.x) * (q.a.y - q.b.y) -
        (q.a.x - q.b.x) * (p.a.y - p.b.y)) <= EPSILON;
}

point getIntersection(line p, line q)
{
    point p1 = p.a;
    double scale =
        ((p.a.x - q.a.x) * (q.a.y - q.b.y) - (p.a.y - q.a.y) * (q.a.x - q.b.x)) /
        ((p.a.x - p.b.x) * (q.a.y - q.b.y) - (p.a.y - p.b.y) * (q.a.x - q.b.x));
    p1.x += (p.b.x - p.a.x) * scale;
    p1.y += (p.b.y - p.a.y) * scale;
    return p1;
}

line pointToLine(point a, point b)
{
    line lr;
    lr.a = a, lr.b = b, lr.angle = atan2(b.y - a.y, b.x - a.x);
    return lr;
}

line shiftLine(point a, point b, double d)
{
    double D = abs(a - b);
    point offset(a.y - b.y, b.x - a.x);
    offset = offset * d / D;
    return pointToLine(a + offset, b + offset);
}

polygon halfPlaneIntersection(line *edges, int nLine)
{
    polygon pg;
    line deques[MAXN];

    sort(edges, edges + nLine, cmpLine);
    nLine = unique(edges, edges + nLine, cmpAngle) - edges;

    int bottom = 0, top = 1;
    deques[0] = edges[0], deques[1] = edges[1];

    for (int i = 2; i < nLine; i++)
    {
        if (paralle(deques[top], deques[top - 1]) ||
            paralle(deques[bottom], deques[bottom + 1]))
            return pg;

        while (bottom < top && cw(edges[i].a, edges[i].b,
            getIntersection(deques[top], deques[top - 1])))
            top--;
        while (bottom < top && cw(edges[i].a, edges[i].b,
            getIntersection(deques[bottom], deques[bottom + 1])))
            bottom++;

        deques[++top] = edges[i];
    }

    while (bottom < top && cw(deques[bottom].a, deques[bottom].b,
        getIntersection(deques[top], deques[top - 1])))
        top--;
    while (bottom < top && cw(deques[top].a, deques[top].b,
        getIntersection(deques[bottom], deques[bottom + 1])))
        bottom++;

    if (top <= (bottom + 1)) return pg;

    for (int i = bottom; i < top; i++)
        pg.push_back(getIntersection(deques[i], deques[i + 1]));
    if (bottom < (top + 1))
        pg.push_back(getIntersection(deques[bottom], deques[top]));

    return pg;
}
