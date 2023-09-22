#include <iostream>

using std::cin;
using std::cout;
using std::endl;

/*
void f2(int &x, int &y) {
	int z = x;
	x = y;
	y = z;
}

void f3(int *x, int *y) {
	int z = *x;
	*x = *y;
	*y = z;
}

int main() {
	int x, y;
	x = 10; y = 26;
	cout << "x, y = " << x << ", " << y << endl;
    
    f2(x, y);
    cout << "x, y = " << x << ", " << y << endl;
    
    f3(&x, &y);
    cout << "x, y = " << x << ", " << y << endl;
    
    x++; // ++x
    y--;
    f2(y, x);
    cout << "x, y = " << x << ", " << y << endl;
    
    return 0;
}
*/



/*
int foo(int x,int y) {
    if(x <= 0 || y <= 0)
    	return 1;
    return 3 * foo(x-1, y/2);
}

int main() {
    cout << foo(3,5) << endl;

    return 0;
}
*/


/*
int main() {
    int a[5]={1,2,3,4,5};
    int *ptr=(int *)(&a+1);
    printf("%d,%d\n",*(a+1),*(ptr-1));
}
*/


int main(int argc, char** argv) {
    int x;
    cin >> x;
    if(x++ > 5) {
    	cout << x << endl;
    } else {
    	cout << x-- << endl;
    }

    return 0;
}