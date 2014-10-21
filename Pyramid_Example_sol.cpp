/*  Brief:
    Print a pyramid whose height is given by the user.
    Ask the user if he/she wants a pyramid to look like
     *
    * *
    OR
     *
    ***
*/
#include <iostream>
#include <iomanip>
#include <cctype>
#include <string>
#include <sstream>  //std::istringstream
#include <limits>   //std::numeric_limits<typename>::max()

/*  void read_number()
    Read input from standard input. Check for invalid input.
    Parameters:
        1) The variable where the input is stored
        2) A limit to the number that can be read
        3) A message to display.
*/
void read_number(std::size_t&, std::string = "");
/* void Pause()
    Pause the program until the user presses ENTER or
        exceeds the streamsize limit.
*/
void Pause();
    //Make a type alias to make typing faster; used more than twice
typedef std::numeric_limits<std::streamsize> StreamMax;

/*  printPyramid(std::size_t, bool)
    Given a height and a choice, print a pyramid made of asterisks.
    Parameters:
        1) Height of the pyramid
        2) Whether or not the pyramid rows follow 1, 2, 3 pattern
            or a 1, 3, 5 pattern.
*/
void printPyramid(std::size_t, bool);

int main()
{
    using std::cout;
    using std::cin;
    using std::endl;
    cout << "Welcome to a basic pyramid printing program.\n";

    while(true){
        std::size_t height(0);  // std::size_t is an unsigned integral
                                //  type.
        read_number(
            height,
            "Please enter the height of the pyramid "
            "(height is measured in asterisks)[0 to quit]: "
        );
        if(height == 0)
            break;

        cout << "Would you like a normal pyramid? ";
        std::string input("");  //
        std::getline(cin, input);   // Read a string from standard
                                    //  input, expecting "yes".
        for(std::size_t i(0); i < input.size(); ++i)    // Convert the
            input[i] = std::tolower(input[i]);          //  string to
                                                        //  lower case,
                                                        //  so we don't
                                                        //  have to care
                                                        //  about case.

        cout << "Thank you!\n";

        printPyramid(height, input != "yes");

        cout << "Press ENTER to continue.";
        Pause();
    }

    cout
        << "\nThank you for using this program!\n"
        << "Press ENTER to terminate the program."
    ;
    Pause();

    return 0;
}

void printPyramid(std::size_t height, bool odd){
    using std::cout;
    const std::size_t width(height);

    while(height-- > 0){    // Count down to 0
        cout
            << std::setw(height)
            << std::setfill(' ')
            << ""
        ;
        if(odd){
            cout
                << std::setw((width - height)*2 - 1)
                << std::setfill('*')
                << '*'
            ;
        }else{
            for(std::size_t i(0); i < width - height; ++i)
                cout << "* ";
        }
/*  Alternative code:
        for(std::size_t i(0); i < width - height; ++i)
            cout << '*' << (odd ? '*' : ' ');
*/
        cout << '\n';
    }
}

    // Ignore the code below.

void read_number(std::size_t& dest, std::string message){
    using std::cin;
    using std::cout;
    if(!message.empty())
        cout << '\n' << message;

    std::string input("");
    std::getline(cin, input);
    std::istringstream iss(input);
    char dumdum('\0');
    while(
        !(iss >> dest) ||   //Failure to read
            //There are white spaces or
            //  non-integers after the number,
            //  e.g. "123 456" or "123.456"
        (iss >> std::ws && iss.get(dumdum))
    ){
        iss.clear();
        cout << "\nError. Not a positive integer! Try again.\n";
        cout << '\n' << message;
        std::getline(cin, input);
        iss.str(input);
    }
}

void Pause()
    {std::cin.ignore(StreamMax::max(), '\n');}