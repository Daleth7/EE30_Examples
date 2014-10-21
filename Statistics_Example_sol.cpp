#include <iostream>
#include <cmath>
#include <iomanip>
#include <cstddef>

    /** void calc_maxminrange(
     *      const double* begin, const double* end,
     *      double& max, double& min, double& range
     *  );
     *  \brief Calculate the maximum, minimum, and range of a data set.
     *  
     *  \param begin The pointer to the first element in the array.
     *  \param end The pointer to the last element in the array.
     *  \param max The storage destination for the maximum.
     *  \param min The storage destination for the minimum.
     *  \param range The storage destination for the range.
     */
void calc_maxminrange
    (const double*, const double*, double&, double&, double&);
    /** double calc_rms(const double* begin, const double* end)
     *  \brief Calculate the root-mean-square of a data set.
     *  
     *  \param begin The pointer to the first element in the array.
     *  \param end The pointer to the last element in the array.
     *  
     *  \return The root-mean-square of the data set.
     */
double calc_rms(const double*, const double*);
    /** double calc_stddev
     *    (const double* begin, const double* end, double avg_hint=0.0)
     *  
     *  \brief Calculate the standard deviation of a data set.
     *  
     *  \param begin The pointer to the first element in the array.
     *  \param end The pointer to the last element in the array.
     *  \param avg_hint Optional hint as to what average to use.
     *      If not specified, the average will be calculated internally.
     *  
     *  \return The standard deviation of the data set.
     */
double calc_stddev(const double*, const double*, double avg_hint=0.0);
    /** double calc_rms
     *    (const double* begin, const double* end, double offset)
     *
     *  \brief Calculate the root-mean-square of a data set with a
     *      given offset.    
     *  
     *  \param begin The pointer to the first element in the array.
     *  \param end The pointer to the last element in the array.
     *  \param offset An offset applied to all data points before
     *      calculating the root-mean-square.
     *  
     *  \return The root-mean-square of the data set.
     */
double calc_rms(const double*, const double*, double offset);
    /** double calc_mean(const double* begin, const double* end)
     *  \brief Calculate the average of a data set.
     *  
     *  \param begin The pointer to the first element in the array.
     *  \param end The pointer to the last element in the array.
     *  
     *  \return The average of the data set.
     */
double calc_mean(const double*, const double*);
    /** double calc_sum(const double* begin, const double* end)
     *  \brief Calculate the sum of all the numbers in the data set.
     *  
     *  \param begin The pointer to the first element in the array.
     *  \param end The pointer to the last element in the array.
     *  
     *  \return The sum of the data set.
     */
double calc_sum(const double*, const double*);

int main(){
    using namespace std;

        // Ask the user to enter data of the format:
        //  N n0 n1 n2 ... nN
    cout << "Please enter the number of data points: ";
    size_t population(0);   // std::size_t is an unsigned data type.
    cin >> population;

    cout << "\nNow enter the data points.\n";
    double* data = new double[population];  // Allocate the necessary
                                            //  memory to hold all the
                                            //  data points.
    for(size_t i(0); i < population; ++i){
        cout << "\tData point #" << (i+1) << ": ";
        cin >> data[i];
    }

    const unsigned row_width(30);
    cout
        << setw(row_width) << left << "Number of data points:"
            << setw(row_width) << right << population << '\n'
    ;
    double
        max(0), min(0), range(0),
        average(calc_mean(data, (data + population)))
    ;
    calc_maxminrange(data, data + population, max, min, range);
    cout
        << setw(row_width) << left << "Mean:"
            << setw(row_width) << right << average << '\n'
        << setw(row_width) << left << "Max:"
            << setw(row_width) << right << max << '\n'
        << setw(row_width) << left << "Min:"
            << setw(row_width) << right << min << '\n'
        << setw(row_width) << left << "Range:"
            << setw(row_width) << right << range << '\n'
        << setw(row_width) << left << "Root-Mean-Square:"
            << setw(row_width) << right << calc_rms(data, data + population) << '\n'
        << setw(row_width) << left << "Standard Deviation:"
            << setw(row_width) << right << calc_stddev(data, data + population, average) << '\n'
    ;

    delete[] data;  // Always remember to clean up resources.

    return 0;
}

void calc_maxminrange(
    const double* begin, const double* end,
    double& max, double& min, double& range
){
    max = min = *begin;     // Start with the first element in
                            //  the array, so we have one less
                            //  iteration to go through.
    while(++begin != end){  // Iterate through the array. The
        if(max < *begin)    //  standard library by convention
            max = *begin;   //  uses iterators, which I try to
        if(*begin < min)    //  follow.
            min = *begin;
    }
    range = max - min;
}

double calc_rms(const double* begin, const double* end)
    {return calc_rms(begin, end, 0);}   // Take advantage of a more
                                        //  generic calc_rms function.
                                        //  This avoids copy-pasting.

double calc_stddev(const double* curr, const double* end, double avg){
    if(avg > -0.01 && avg < 0.01)   // If the caller did not provide
        avg = calc_mean(curr, end); //  an average or if the average
                                    //  happened to be 0, calculate it.
    return calc_rms(curr, end, avg);    // Std. Dev. is very similar
                                        //  to RMS. It is basically
                                        //  RMS with respect to the
                                        //  average, so let's take
                                        //  advantage of that.
}

double calc_rms(const double* curr, const double* end, double offset){
    double sum(0);
    const std::size_t size(curr - end);
        // Remember RMS is the root of the mean of the squares.
        //  This one happens to have an offset for each data
        //  point before squaring.
    while(curr != end){
        sum += (offset - *curr)*(offset - *curr);
        ++curr;
    }
    return std::sqrt(sum/size);
}

double calc_mean(const double* begin, const double* end)
    {return calc_sum(begin, end)/(end - begin);}    // Pointers store
                                                    //  memory addresses,
                                                    //  which are like
                                                    //  unsigned integers.
                                                    //  This allows pointer
                                                    //  arithmetic. You don't
                                                    //  even need to worry
                                                    //  about the size of the
                                                    //  data type.

double calc_sum(const double* curr, const double* end){
    double toreturn(0);
    while(curr != end)
        toreturn += *(curr++);
    return toreturn;
}
