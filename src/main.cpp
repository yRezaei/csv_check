#include <string>
#include <iostream>
#include <iomanip>
#include <csv_utility.hpp>

int main(int argc, char const *argv[])
{
    switch (argc)
    {
    case 3:
    {
        csv::CSVData csv_data;
        csv::read_from_file(argv[1], csv_data);
        if (!csv_data.data.empty())
        {
            csv::interpolate_bad_value(csv_data.data, 0.5f);
            csv::write_to_file(argv[2], csv_data);
            std::cout << "Done." << std::endl;
        }
        else
        {
            std::cerr << "ERROR -> Something is wrong with file." << std::endl;
        }
        
        break;
    }

    default:
        std::cout << "Usage:\n"
                  << std::left
                  << '\t' << std::setw(15) << "csv_check <input_file_path> <output_file_path>" << std::endl;
        break;
    }

    return 0;
}
