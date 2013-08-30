#include "Regex.hpp"

RegEx::RegEx() : RegExpression(boost::regex(std::string(), ICase)) {}

RegEx::~RegEx(){}

RegEx::RegEx(std::string Expression, MatchFlags Matching) : RegExpression(boost::regex(std::string(), ICase))
{
    if (Matching == 0)
		RegExpression = boost::regex(Expression);
    else
    {
		if (Matching != ICase)
			return;
		RegExpression = boost::regex(Expression, Matching);
    }
}

bool RegEx::Match(std::string InputSource, std::string Expression)
{
    std::string Matches;
    return Match(InputSource, Expression, Matches);
}

bool RegEx::Match(std::string InputSource, std::string Expression, std::string &Matches)
{
    if (!Expression.empty())
        RegExpression = boost::regex(Expression);

    try
    {
		std::string::const_iterator start, end;
		start = InputSource.begin();
		end = InputSource.end();
		boost::smatch what;
		boost::regex_constants::match_flag_type flags = boost::match_default;

		while(boost::regex_search(start, end, what, RegExpression, flags))
		{
			Matches = what[0];
			start = what[0].second;
		}
    }
    catch(...){}
    return (!Matches.empty());
}

StringArray RegEx::MatchAll(std::string InputSource)
{
    boost::sregex_token_iterator Iter(InputSource.begin(), InputSource.end(), RegExpression, 0);
    boost::sregex_token_iterator end;
    StringArray Matches;

    while(Iter != end)
    {
		Matches(*Iter++);
    }
    return Matches;
}

String2DArray RegEx::PregMatchAll(const std::string& InputSource)
{
    StringArray Temp;
    String2DArray Result;
    Result.SetLength(1);

    boost::sregex_iterator I(InputSource.begin(), InputSource.end(), RegExpression), J;
    while(I != J)
    {
		for (size_t K = 0; K <= I->size(); ++K)
		{
			if(!I->str(K).empty())
                Temp(I->str(K));
		}
		++I;
    }

    for (size_t K = 0; K < Temp.Size(); K += 2)
		Result[0](Temp[K]);

    if (Temp.Size() > 1)
    {
        Result.SetLength(2);
        for (size_t K = 1; K < Temp.Size(); K += 2)
            Result[1](Temp[K]);
    }

    return Result;
}
