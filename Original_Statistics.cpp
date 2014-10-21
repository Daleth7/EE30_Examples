#include <iterator>
#include <set>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <cmath>

template <class Iter>
    double calc_median(Iter, const Iter&);
template <class Iter>
    double calc_rms(const Iter&, const Iter&);
template <class Iter>
    double calc_stddev(const Iter&, const Iter&, double avg_hint=0.0);
template <class Iter>
    double calc_rms(Iter, const Iter&, double offset);
template <class Iter>
    double calc_mean(Iter, const Iter&);
template <class Iter>
    double calc_sum(Iter, const Iter&);

template <class Set_Con>
    void read_data(std::istream&, Set_Con&);
template <class Set_Con>
    void output_stats(
        std::ostream&,
        const std::string&,
        const Set_Con&
    );

int main(int argc, char* argv[])
{
    using namespace std;

    srand(time(nullptr));
    ofstream err("error.log", ios_base::app);
    time_t currtime;

    const string
        default_ipath("data.dat"),
        default_opath("stats.txt"),
        generate_com("-gen"),
        calc_com("-calc")
    ;

    if(argc > 1){   //Command Prompt / Terminal command
        for(int i(1); i < argc; ++i){
            if(generate_com == argv[i]){
                for(++i; i < argc; ++i){
                    if(argv[i][0] == '-'){
                        --i;
                        break;
                    }
                    ofstream newdata(string(argv[i]));
                    if(!newdata.is_open()){
                        time(&currtime);
                        err << ctime(&currtime) << ": Failed to open data file for generation.\n";
                        return -1;
                    }
                    unsigned pop(rand());
                    while(pop-- > 0)
                        newdata << (static_cast<double>(rand())/(rand()+1)) << '\n';
                    newdata.close();
                }
            }
            if(calc_com == argv[i] && i+2 < argc){
                for(++i; i < argc; i+=2){
                    if(argv[i][0] == '-'){
                        --i;
                        break;
                    }
                    ifstream src(string(argv[i]));  //Data
                    if(!src.is_open()){
                        time(&currtime);
                        err << ctime(&currtime) << ": Failed to open data file for calculation.\n";
                        return -1;
                    }

                    multiset<double> data;
                    read_data(src, data);
                    src.close();

                    ofstream dest(string(argv[i+1]));   //Output
                    if(!dest.is_open()){
                        time(&currtime);
                        err << ctime(&currtime) << ": Failed to open output file.\n";
                        return -1;
                    }
                    output_stats(dest, string(argv[i]), data);
                    dest.close();
                }
            }
        }
    }else{  //Default
        ifstream src(default_ipath);
        if(!src.is_open()){
            time(&currtime);
            err << ctime(&currtime) << ": Failed to open data file for calculation.\n";
            return -1;
        }
        multiset<double> data;
        read_data(src, data);
        src.close();

        ofstream dest(default_opath);
        if(!dest.is_open()){
            time(&currtime);
            err << ctime(&currtime) << ": Failed to open output file.\n";
            return -1;
        }
        output_stats(dest, default_ipath, data);
        dest.close();
    }

    err.close();
    return 0;
}

template <class Iter>
double calc_median(Iter begin, const Iter& end){
    std::advance(begin, std::distance(begin, end)/2);
    return *begin;
}

template <class Iter>
double calc_rms(const Iter& begin, const Iter& end)
    {return calc_rms(begin, end, 0);}

template <class Iter>
double calc_stddev(const Iter& curr, const Iter& end, double avg){
    if(avg > -0.01 && avg < 0.01)
        avg = calc_mean(curr, end);
    return calc_rms(curr, end, avg);
}

template <class Iter>
double calc_rms(Iter curr, const Iter& end, double offset){
    double sum(0);
    std::size_t size(std::distance(curr, end));
    while(curr != end){
        sum += (offset - *curr)*(offset - *curr);
        ++curr;
    }
    return std::sqrt(sum/size);
}

template <class Iter>
double calc_mean(Iter begin, const Iter& end)
    {return calc_sum(begin, end)/std::distance(begin, end);}

template <class Iter>
double calc_sum(Iter curr, const Iter& end){
    double toreturn(0);
    while(curr != end)
        toreturn += *(curr++);
    return toreturn;
}

template <class Set_Con>
void read_data(std::istream& in, Set_Con& dest){
    double hold(0);
    while(in >> hold)
        dest.insert(hold);
}

template <class Set_Con>
void output_stats(
    std::ostream& dest,
    const std::string& pathname,
    const Set_Con& data
){
    const unsigned w(30);
    using namespace std;
    dest
        << setw(w) << left << "Source:"
            << setw(w) << right << pathname << "\n\n"
        << setw(w) << left << "Number of data points:"
            << setw(w) << right << data.size() << '\n'
    ;
    double average(calc_mean(data.begin(), data.end()));
    dest
        << setw(w) << left << "Mean:"
            << setw(w) << right << average << '\n'
        << setw(w) << left << "Max:"
            << setw(w) << right << *data.rbegin() << '\n'
        << setw(w) << left << "Min:"
            << setw(w) << right << *data.begin() << '\n'
        << setw(w) << left << "Median:"
            << setw(w) << right << calc_median(data.begin(), data.end()) << '\n'
        << setw(w) << left << "Root-Mean-Square:"
            << setw(w) << right << calc_rms(data.begin(), data.end()) << '\n'
        << setw(w) << left << "Standard Deviation:"
            << setw(w) << right << calc_stddev(data.begin(), data.end(), average) << '\n'
    ;
}
