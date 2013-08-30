// *** ADDED BY HEADER FIXUP ***
#include <string>
// *** END ***
#include "Serialize.hpp"

namespace cxx
{
    Serialize& operator << (Serialize& Destination, const std::string &Value)
    {
        Destination << Value.size();
        for (auto it = Value.begin(); it != Value.end(); ++it)
        {
            Destination << *it;
        }
        return Destination;
    }

    DeSerialize& operator >> (DeSerialize& Source, std::string &Value)
    {
        typedef typename std::string::size_type SizeType;
        SizeType Size;
        Source >> Size;
        Value.reserve(Size);
        for (SizeType I = 0; I < Size; ++I)
        {
            char Temp;
            Source >> Temp;
            Value += Temp;
        }
        return Source;
    }
}
