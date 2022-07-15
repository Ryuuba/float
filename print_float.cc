#include <iostream>
#include <cstdlib>
#include "float32.h"

int main(int argc, char const *argv[])
{
    using std::cout, std::cerr, std::endl;
    if (argc != 2)
    {
        cerr << "A floating point number is needed" << endl;
        exit(1);
    }
    float arg1 = atof(argv[1]);
    IEEE754_32 float_num(arg1);
    cout << "Number: " << float_num << endl;
    cout << "Binary code: " << float_num.str_repr() << endl;
    return 0;
}
