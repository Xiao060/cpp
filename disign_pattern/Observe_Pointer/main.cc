#include "Pub.hh"
#include "Sub.hh"


int main(int argc, char* argv[]) {
    
    Pub p(12, "XiaoMing", 'F');

    Sub s1(p, 1);

    {
    Sub s2(p, 2);
    }

    Sub s3(p, 3);

    p.setinfo(13, "XiaoHong", 'M');



    return 0;
}




