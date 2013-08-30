#ifndef BASE64_HPP_INCLUDED
#define BASE64_HPP_INCLUDED

#include "Mathematics.hpp"

namespace cxx
{
    const static tstring Base64Chars = _T("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/");

    inline bool IsBase64(std::uint8_t C)
    {
        return (_istalnum(C) || (C == '+') || (C == '/'));
    }

    tstring EncodeBase64(tstring Data);

    tstring DecodeBase64(tstring Data);
}

/*tstring EncodeB64Chars(tstring StringToEncode);

tstring DecodeB64Chars(tstring StringToDecode);

tstring EncodeB64(tstring StringToEncode);

tstring DecodeB64(tstring StringToDecode);

tstring EncodeB64X(tstring StringToEncode);

tstring DecodeB64X(tstring StringToEncode);*/

#endif // BASE64_HPP_INCLUDED
