#ifndef STRING_UTILITY_HPP_
#define STRING_UTILITY_HPP_

#include <string>
#include <sstream>
#include <vector>
#include <utility>
#include <regex>
#include <algorithm>
#include <cctype>

namespace str_util
{
enum class TokenOption : std::uint8_t
{
    REMOVE_EMPTY_TOKKEN,
    ALLOW_EMPTY_TOKKEN
};

inline std::vector<std::string> split(std::string const &source, std::string const &delims, TokenOption option = TokenOption::ALLOW_EMPTY_TOKKEN)
{
    using iterator = std::regex_token_iterator<std::string::const_iterator>;
    std::vector<std::string> tokens;
    std::regex reg("[" + delims + "]");
    std::transform(
        iterator(source.begin(), source.end(), reg, -1),
        iterator(),
        std::back_inserter(tokens),
        [](auto m) { return std::string(m.first, m.second); });

    if (option == TokenOption::REMOVE_EMPTY_TOKKEN)
    {
        auto new_end = std::remove_if(tokens.begin(), tokens.end(), [](std::string const &str) { return (str.empty() ? true : false); });
        tokens.erase(new_end, tokens.end());
    }

    return tokens;
}

inline bool check_pattern(const std::string &source, std::regex pattern)
{
    return std::regex_match(source, pattern);
}
} // namespace str_util

#endif // !STRING_UTILITY_HPP_
