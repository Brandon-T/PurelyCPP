/**  © 2012, Brandon T. All Rights Reserved.
  *
  *  This file is part of the GLHook Library.
  *  You may use this file only for your personal, and non-commercial use.
  *  You may not modify or use the contents of this file for any purpose (other
  *  than as specified above) without the express written consent of the author.
  *  You may not reproduce, republish, post, transmit, publicly display,
  *  publicly perform, or distribute in print or electronically any of the contents
  *  of this file without express consent of rightful owner.
  *  This License is subject to change at any time without notice/warning.
  *
  *						Author : Brandon T.
  *						Contact: Brandon.T-@Live.com
  */

#ifndef SERIALIZE_HPP_INCLUDED
#define SERIALIZE_HPP_INCLUDED

#include <vector>
#include <sstream>
#include <iostream>
#include <list>

/** Core **/

namespace cxx
{
    class Serialize
    {
        private:
            std::ostringstream Data;

        public:
            Serialize(const void* Buffer, std::size_t BufferSize) : Data()
            {
                Data.rdbuf()->pubsetbuf(const_cast<char*>(reinterpret_cast<const char*>(Buffer)), BufferSize);
            }

            template <typename T>
            friend Serialize& operator << (Serialize& Destination, const T& Value)
            {
                Destination.Data.write(reinterpret_cast<const char*>(&Value), sizeof(T));
                return Destination;
            }
    };

    template <typename T, typename Allocator>
    Serialize& operator <<(Serialize& Destination, const std::vector<T, Allocator>& Value)
    {
        typedef typename std::vector<T, Allocator>::const_iterator Iterator;
        Destination << Value.size();
        for(Iterator it = Value.begin(); it != Value.end(); ++it)
        {
            Destination << (*it);
        }
        return Destination;
    }

    template <typename T, typename Allocator>
    Serialize& operator << (Serialize& Destination, const std::list<T, Allocator>& Value)
    {
        typedef typename std::list<T, Allocator>::const_iterator Iterator;
        Destination << Value.size();
        for(Iterator it = Value.begin(); it != Value.end(); ++it)
        {
            Destination << (*it);
        }
        return Destination;
    }

    class DeSerialize
    {
        private:
            std::istringstream Data;

        public:
            DeSerialize(const void *Buffer, std::size_t Size) : Data()
            {
                Data.rdbuf()->pubsetbuf(const_cast<char*>(reinterpret_cast<const char*>(Buffer)), Size);
            }

            template <typename T>
            friend DeSerialize& operator >> (DeSerialize& Source, T& Value)
            {
                Source.Data.read(reinterpret_cast<char*>(&Value), sizeof(T));
                return Source;
            }
    };

    template <typename T, typename Allocator>
    DeSerialize& operator >> (DeSerialize& Source, std::vector<T, Allocator>& Value)
    {
        typedef typename std::vector<T, Allocator>::size_type SizeType;
        SizeType Size;
        Source >> Size;
        Value.reserve(Size);
        for(SizeType I = 0; I < Size; ++I)
        {
            T Temp = T();
            Source >> Temp;
            Value.emplace_back(Temp);
        }
        return Source;
    }

    template <typename T, typename Allocator>
    DeSerialize& operator >> (DeSerialize& Source, std::list<T, Allocator>& Value)
    {
        typedef typename std::list<T, Allocator>::size_type SizeType;
        SizeType Size;
        Source >> Size;
        for(SizeType I = 0; I < Size; ++I)
        {
            T Temp = T();
            Source >> Temp;
            Value.emplace_back(Temp);
        };
        return Source;
    }

    Serialize& operator << (Serialize& Destination, const std::string &Value);
    DeSerialize& operator >> (DeSerialize& Source, std::string &Value);
}

#endif // SERIALIZE_HPP_INCLUDED
