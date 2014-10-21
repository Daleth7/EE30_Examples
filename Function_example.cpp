#include <iostream>
#include <cmath>

double funky(double, double);   // Function prototype.
                                //  Let the compiler know it exists.

int main(){
    using namespace std;

    cout << funky(4e5, 5.63e-2);    // Function call.
                                    //  Use the function.

    /* Special note:
        "cout << [FOO]" actually calls a function. It is declared
        similarly to the following:

        namespace std{
            ostream& operator<<(ostream&, decltype([FOO]));
        }

        where decltype([FOO]) is the data type of [FOO], an
        arbitrary value.

        For the actual list, see:
        http://www.cplusplus.com/reference/ostream/ostream/operator%3C%3C/
    */

    return 0;
}

double funky(double x, double y){   // Function definition.
                                    //  Specify what the function does.
    return std::atan(std::cos(x * y));  // std::atan() and std::cos()
                                        //  are functions as well.
}