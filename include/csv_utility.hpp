#ifndef CSV_UTILITY_HPP_
#define CSV_UTILITY_HPP_

#include <filesystem>
#include <fstream>
#include <sstream>
#include <vector>

#include "string_utility.hpp"
#include "math_utility.hpp"

namespace csv
{
    namespace fs = std::filesystem;

    struct CSVData
    {
        std::string header;
        std::uint32_t item_per_raw;
        std::vector<float> data;

        friend std::ostream& operator<< (std::ostream& stream, const CSVData& csv_data)
        {
            if(!csv_data.header.empty())
                stream << csv_data.header << '\n';
            auto interval = csv_data.item_per_raw - 1;
            for(auto i= 0u; i < csv_data.data.size(); i += csv_data.item_per_raw)
            {
                for(auto j = 0u; j < interval; ++j)
                    stream << csv_data.data[i + j] << ", " ;
                stream << csv_data.data[i + interval] << '\n';
            }

            return stream;
        } 
    };

    inline void interpolate_bad_value(std::vector<float>& src, float bad_value = 0)
    {
        if(src.empty())
            return;

        float mu = 0.5f;

        if(src.size() > 2)
        {
            for(auto itr = src.begin() + 1; itr != src.end() - 1; ++itr)
            {
                if(*itr == bad_value)
                    *itr = math_util::interpolation::linear(*(itr-1), *(itr + 1), 0.5f);
            }
        }

        if(src.size() > 1)
            src.back() = math_util::interpolation::linear(*(src.end()-2), *(src.end()-1), 0.5f);
    }

    inline void write_to_file(const std::string& file_path, CSVData& csv_data)
    {
         std::ofstream file(file_path);
        if(file.is_open())
        {
            file << csv_data;
            file.close();
        }
    }

    inline void read_from_file(const std::string& csv_file, CSVData& csv_data)
    {
        auto file_path = fs::path(csv_file);
        if(!fs::exists(file_path))
        {
            std::cerr << "ERROR in function 'csv::read_from_file' -> File not found: " << file_path << std::endl;
            return;
        }

        if(!file_path.has_extension() || file_path.extension() != ".csv")
        {
            std::cerr << "ERROR in function 'csv::read_from_file' -> Unvalid file format: " << file_path << std::endl;
            return;
        }

        csv_data.data.clear();
        csv_data.header = "";
        csv_data.item_per_raw = 0;

        bool has_header = false;
        std::string line;
        std::ifstream file(file_path);
        if(file.is_open())
        {
            if(std::getline(file, line))
            {
                if(line.find_first_of("\"#") != std::string::npos) {
                    csv_data.header = line;
                    if(std::getline(file, line))
                    {
                        auto tokens = str_util::split(line, ",; ", str_util::TokenOption::REMOVE_EMPTY_TOKKEN);
                        for(auto i = 0u; i < tokens.size(); ++i)
                            csv_data.data.emplace_back(std::stof(tokens[i]));
                        csv_data.item_per_raw = (std::uint16_t)tokens.size();
                    }
                }
                else {
                    auto tokens = str_util::split(line, ",; ", str_util::TokenOption::REMOVE_EMPTY_TOKKEN);
                    for(auto i = 0u; i < tokens.size(); ++i)
                        csv_data.data.emplace_back(std::stof(tokens[i]));
                    csv_data.item_per_raw = (std::uint16_t)tokens.size();
                }
            }

            while(std::getline(file, line))
            {
                auto tokens = str_util::split(line, ", ", str_util::TokenOption::REMOVE_EMPTY_TOKKEN);
                for(auto i = 0u; i < tokens.size(); ++i)
                    csv_data.data.emplace_back(std::stof(tokens[i]));
            }

            file.close();
        }
    }
}

#endif // !CSV_UTILITY_HPP_