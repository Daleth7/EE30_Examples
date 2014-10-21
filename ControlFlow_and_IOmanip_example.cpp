#include <iostream>
#include <iomanip>
    // You can ignore the headers below
#include <string>
#include <cctype>
#include <cstddef>
#include <limits>

int main(){
    using namespace std;

    cout
        << "Welcome to a simple example of setw."
        << "\n\tPlease enter the filler character followed by "
            "the width of the row and the string.\n"
        << "\t\tFiller: "
    ;
    char filler('\0');
    cin >> filler;

    cout << "\t\tWidth: ";
    size_t width(0); // std::size_t is an unsigned integral type
    cin >> width;
        // You can ignore the following line.
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "\t\tString: ";
    string user_input;
    getline(cin, user_input);

    if(isprint(filler))     // Check if the filler is
                            //  a character you can see.
        cout << setfill(filler);
    else
        cout << setfill(' ');

    cout
        << "\n\nHere is your formatted string: "
        << setw(width) << left << user_input
    ;

    return 0;
}