#include <iostream>
#include <ostream>
#include "01.line.hh"

using std::ostream;

class Line::LineImpl {
public:
    LineImpl(int x1, int y1, int x2, int y2) 
    : _p1(x1, y1)
    , _p2(x2, y2) {}

    friend ostream& operator<<(ostream& os, const LineImpl& l);

    class Point {
    public:
        Point(int x, int y)
        : _ix(x)
        , _iy(y) {}

        friend ostream& operator<<(ostream& os, const Point& p);

    private:
        int _ix;
        int _iy;
    };

private:
    Point _p1;
    Point _p2;
};


ostream& operator<<(ostream& os, const Line::LineImpl::Point& p) {
    os << "(" << p._ix << ", " << p._iy << ")";
    return os;
}

ostream& operator<<(ostream& os, const Line::LineImpl& l) {
    os << l._p1 << " --------> " << l._p2;
    return os;
}

ostream& operator<<(ostream& os, const Line& l) {
    os << *l._pimpl;
    return os;
}


Line::Line(int x1, int y1, int x2, int y2) 
: _pimpl(new LineImpl(x1, y1, x2, y2)) {}


Line::~Line() {
    if (_pimpl) {
        delete _pimpl;
        _pimpl = nullptr;
    }
}

