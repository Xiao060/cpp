#ifndef __LINE_HPP__
#define __LINE_HPP__

#include <ostream>
using std::ostream;

class Line {
public:
    Line(int x1 = 0, int y1 = 0, int x2 = 0, int y2 = 0);
    ~Line();
    friend ostream& operator<<(ostream& os, const Line& l);
    // 向前声明
    class LineImpl;

private:
    LineImpl* _pimpl;
};


#endif