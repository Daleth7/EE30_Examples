#include <iostream>

int main(){
    using namespace std;

    const unsigned arr_size(10u);
    double arr[arr_size] = {0}; // Declare an array.

    cout << "Original:\t";
    for(unsigned i(0); i < arr_size; ++i) // Assign each slot with some value
        cout << (arr[i] = (i+3)*(i+1)) << ' ';  // Access each array
                                                //  element with subscript
                                                //  operator ("[]").
    cout << endl;

    double* a_ptr = arr + 2;    // Declare a pointer to a double.
                                //  Initialize it with the memory
                                //  address of the 3rd element in
                                //  the array.
    *a_ptr += arr_size; // Dereference the pointer, i.e. access that
                        //  memory location and do something with the
                        //  variable there.
    ++a_ptr;    // Move a_ptr to the next element in the array.
    *a_ptr = *(arr + 5u) * 2u;  // You can treat name of arrays like
                                //  pointers as well.

    double** a_ptr_ptr = &a_ptr;    // This is a pointer to a pointer.
                                    //  An easy way to tell what a pointer
                                    //  points to is to ignore the last
                                    //  asterisk, e.g.:
                                    //  double* --> double * --> pointer
                                    //      to a double.
                                    //  double** --> double* * -->
                                    //      pointer to a pointer to a
                                    //      double.
    *a_ptr_ptr = arr + 9;   // Modifies a_ptr
    **a_ptr_ptr = 6;    // Modifies arr[9] or *a_ptr

    cout << "After:\t\t";
    for(unsigned i(0); i < arr_size; ++i)
        cout << arr[i] << ' ';

    return 0;
}