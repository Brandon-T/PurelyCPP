#ifndef REGEX_HPP_INCLUDED
#define REGEX_HPP_INCLUDED

#define MatchFlags boost::regbase::flag_type
#define Perl boost::regex::perl
#define ICase boost::regex::icase

#include "Strings.hpp"
#include "Types.hpp"
#include <Boost/Regex.hpp>

class RegEx
{
    private:
        boost::regex RegExpression;    //<\\s*td[^>]*>(.*?)<\\s*/td\\s*>   //Matches <td></td>

    public:
        RegEx();
        RegEx(std::string Expression, MatchFlags Matching = 0);
        ~RegEx();

        bool Match(std::string InputSource, std::string Expression = std::string());
        bool Match(std::string InputSource, std::string Expression, std::string &Matches);

        StringArray MatchAll(std::string InputSource);
        StringArray MatchAll(std::string InputSource, std::string Expression);

        String2DArray PregMatchAll(const std::string& InputSource);
};

#endif // REGEX_HPP_INCLUDED
