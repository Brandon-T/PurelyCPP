#ifndef TYPES_HPP_INCLUDED
#define TYPES_HPP_INCLUDED

#include <vector>
#include <cassert>
#include <sstream>
#include <algorithm>
#include <utility>
#include "Defines.hpp"


/** Types **/


/**
 * 												POINTS
 *
 *
**/

namespace cxx
{
    struct Point
    {
        int X, Y;

        std::uint32_t Color;
        Point();                                                    //Default constructor.
        Point(int x, int y);                                        //Alternate constructor.
        Point(int x, int y, std::uint32_t Colour);
        ~Point();                                                   //Destructor.

        Point& operator ()(int x, int y);

        Point& operator ()(int x, int y, std::uint32_t Colour);

        bool operator == (const Point& PT) const;

        bool operator != (const Point& PT) const;

        Point& operator = (const Point& PT);

        Point& operator += (const int& I);

        Point& operator += (const Point& PT);

        Point& operator -= (const int& I);

        Point& operator -= (const Point& PT);

        Point& operator *= (const int& I);

        Point& operator *= (const Point& PT);

        Point& operator /= (const int& I);

        Point& operator /= (const Point& PT);

        friend tostream& operator << (tostream& Str, const Point& PT);

        Point operator + (const int& I);

        Point operator + (const Point& PT);

        Point operator - (const int& I);

        Point operator - (const Point& PT);

        friend double Distance(Point P1, Point P2);

        friend Point Invert(Point PT);
    };


    /**
     * 												BOXES
     *
     *
    **/

    struct Box
    {
        int X1, Y1, X2, Y2;
        Box();                                                                               //Default Constructor.
        Box(int x1, int y1, int x2, int y2);                                                 //Alternate Constructor.
        Box(Point UpperLeft, Point LowerRight);
        ~Box();                                                                              //Destructor.

        Box& operator ()(int x1, int y1, int x2, int y2);

        Box& operator ()(Point UpperLeft, Point LowerRight);

        operator const Box& () const;

        int Width() const;

        int Height() const;

        int Area() const;

        bool operator == (const Box& B) const;

        bool operator != (const Box& B) const;

        Box& operator += (const int& I);

        Box& operator += (const Box& B);

        Box& operator -= (const int& I);

        Box& operator -= (const Box& B);

        Box& operator *= (const int& I);

        Box& operator *= (const Box& B);

        Box& operator /= (const int& I);

        Box& operator /= (const Box& B);

        Point MidPoint(const Box& B);

        Box& ToBox(Point UpperLeft, Point LowerRight);

        Box& operator = (const Box& B);

        bool Contains(const Point& P) const;

        bool Contains(const Box& B) const;

        friend tostream& operator << (tostream& Str, const Box& B);

        Box operator + (const int& I);

        Box operator + (const Box& B);

        Box operator - (const int& I);

        Box operator - (const Box& B);
    };


    /**
     * 												BOXARRAYS
     *
     *
    **/

    class BoxArray
    {
        private:
            std::vector<Box> Container;

        public:
            explicit BoxArray();
            template<typename T, typename... Args>
            explicit BoxArray(T FirstBox, const Args... RemainingBoxes);
            ~BoxArray();

            std::size_t Size() const;

            std::size_t Size(int I) const;

            bool Empty() const;

            BoxArray& Clear();

            Box& operator [](int I);

            const Box& operator [](int I) const;

            operator const std::vector<Box>& () const;

            operator const BoxArray& () const;

            BoxArray& operator ()(std::vector<Box> BA);

            operator std::vector<Box>() const;

            bool operator == (const BoxArray& BA) const;

            bool operator != (const BoxArray& BA) const;

            BoxArray& operator += (const Box& B);

            BoxArray& operator += (const BoxArray& BA);

            BoxArray& operator -= (const Box& B);

            BoxArray& operator -= (const BoxArray& BA);

            BoxArray& operator = (const BoxArray& BA);

            BoxArray& operator << (const Box& B);

            BoxArray& operator << (const BoxArray& BA);

            void SetLength(const std::size_t NewLength, const Box& B = Box(0, 0, 0, 0));

            template<typename T, typename... Args>
            BoxArray& operator ()(T FirstBox, const Args... RemainingBoxes);

            bool Contains(const Box& BoxToFind);

            BoxArray& Append(const BoxArray& Boxes);

            BoxArray& Delete(std::uint32_t Position);

            BoxArray& Delete(const Box& BoxToDelete, bool All = false);

            BoxArray& Delete(const BoxArray& BoxesToDelete);

            friend tostream& operator << (tostream& Str, const BoxArray& BA);

            BoxArray operator + (const Box& B);

            BoxArray operator + (const BoxArray& BA);

            BoxArray operator - (const Box& B);

            BoxArray operator - (const BoxArray& BA);
    };

    /**
     * 												DECLARATION FOR BOXARRAYS NON-INLINE TEMPLATES
     *
     *
    **/

    template<typename T, typename... Args>
    BoxArray::BoxArray(T FirstBox, const Args... RemainingBoxes) : Container(0)
    {
        Container = {FirstBox, RemainingBoxes...};
    }

    template<typename T, typename... Args>
    BoxArray& BoxArray::operator ()(T FirstBox, const Args... RemainingBoxes)
    {
        for (T BoxData :
                {
                    FirstBox, RemainingBoxes...
                })
        {
            Container.emplace_back(BoxData);
        }
        return *this;
    }


    /**
     * 												INTEGERARRAYS
     *
     *
    **/

    class IntegerArray
    {
        private:
            std::vector<int> Container;

        public:
            explicit IntegerArray();
            template<typename T, typename... Args>
            explicit IntegerArray(T FirstInt, const Args... RemainingInts);
            ~IntegerArray();

            std::size_t Size() const;

            bool Empty() const;

            IntegerArray& Clear();

            int& operator [](int I);

            const int& operator [](int I) const;

            operator const std::vector<int>& () const;

            operator const IntegerArray& () const;

            IntegerArray& operator ()(std::vector<int> IA);

            operator std::vector<int>() const;

            bool operator == (const IntegerArray& I) const;

            bool operator != (const IntegerArray& I) const;

            IntegerArray& operator += (const int& I);

            IntegerArray& operator += (const IntegerArray& IA);

            IntegerArray& operator -= (const int& I);

            IntegerArray& operator -= (const IntegerArray& IA);

            IntegerArray& operator = (const IntegerArray& IA);

            IntegerArray& operator << (const int& I);

            IntegerArray& operator << (const IntegerArray& IA);

            void SetLength(const std::size_t NewLength, const int& I = int());

            template<typename T, typename... Args>
            IntegerArray& operator ()(T FirstInt, const Args... RemainingInts);

            bool Contains(int IntToFind);

            IntegerArray& Append(const IntegerArray& IA);

            IntegerArray& Delete(std::uint32_t Position);

            IntegerArray& Delete(const int& IntToDelete, bool All);

            IntegerArray& Delete(const IntegerArray& IA);

            friend tostream& operator << (tostream& Str, const IntegerArray& IA);

            IntegerArray operator + (const int& I);

            IntegerArray operator + (const IntegerArray& IA);

            IntegerArray operator - (const int& I);

            IntegerArray operator - (const IntegerArray& IA);
    };

    /**
     * 												DECLARATION FOR INTEGERARRAYS NON-INLINE TEMPLATES
     *
     *
    **/

    template<typename T, typename... Args>
    IntegerArray::IntegerArray(T FirstInt, const Args... RemainingInts) : Container(0)
    {
        this->Container = {FirstInt, RemainingInts...};
    }

    template<typename T, typename... Args>
    IntegerArray& IntegerArray::operator ()(T FirstInt, const Args... RemainingInts)
    {
        for (T IntData :
                {
                    FirstInt, RemainingInts...
                })
        {
            Container.emplace_back(IntData);
        }
        return *this;
    }


    /**
     * 												INTEGER2DARRAYS
     *
     *
    **/


    class Integer2DArray
    {
        private:
            std::vector<IntegerArray> Container;

        public:
            explicit Integer2DArray();
            template<typename T, typename... Args>
            explicit Integer2DArray(T FirstIA, const Args... RemainingIAs);
            ~Integer2DArray();

            std::size_t Size() const;

            std::size_t Size(int I) const;

            bool Empty() const;

            Integer2DArray& Clear();

            Integer2DArray& operator ()(IntegerArray IA);

            IntegerArray& operator [](int I);

            const IntegerArray& operator [](int I) const;

            operator const std::vector<IntegerArray>& () const;

            operator const Integer2DArray& () const;

            Integer2DArray& operator ()(std::vector<IntegerArray> IA);

            operator std::vector<IntegerArray>() const;

            bool operator == (const Integer2DArray& I2D) const;

            bool operator != (const Integer2DArray& I2D) const;

            Integer2DArray& operator += (const IntegerArray& IA);

            Integer2DArray& operator += (const Integer2DArray& I2D);

            Integer2DArray& operator -= (const IntegerArray& IA);

            Integer2DArray& operator -= (const Integer2DArray& I2D);

            Integer2DArray& operator = (const Integer2DArray& IA);

            Integer2DArray& operator << (const IntegerArray& IA);

            Integer2DArray& operator << (const Integer2DArray& I2D);

            void SetLength(const std::size_t NewLength, const std::size_t& InnerLength = int(), const int& I = int());

            void SetLength(const std::size_t NewLength, const IntegerArray& IA);

            template<typename T, typename... Args>
            Integer2DArray& operator()(T FirstIA, const Args... RemainingIAs);

            bool Contains(const IntegerArray& IntArrayToFind);

            Integer2DArray& Append(const Integer2DArray& I2D);

            Integer2DArray& Delete(std::uint32_t Position);

            Integer2DArray& Delete(const IntegerArray& IA, bool All = false);

            Integer2DArray& Delete(const Integer2DArray& I2D);

            friend tostream& operator << (tostream& Str, const Integer2DArray& I2D);

            Integer2DArray operator + (const IntegerArray& IA);

            Integer2DArray operator + (const Integer2DArray& I2D);

            Integer2DArray operator - (const IntegerArray& IA);

            Integer2DArray operator - (const Integer2DArray& I2D);
    };

    /**
     * 												DECLARATION FOR INTEGER2DARRAYS NON-INLINE TEMPLATES
     *
     *
    **/

    template<typename T, typename... Args>
    Integer2DArray::Integer2DArray(T FirstIA, const Args... RemainingIAs) : Container(0)
    {
        this->Container = {FirstIA, RemainingIAs...};
    }

    template<typename T, typename... Args>
    Integer2DArray& Integer2DArray::operator()(T FirstIA, const Args... RemainingIAs)
    {
        for (T TIAData :
                {
                    FirstIA, RemainingIAs...
                })
        {
            Container.emplace_back(TIAData);
        }
        return *this;
    }


    /**
     * 												POINTARRAYS
     *
     *
    **/


    class PointArray
    {
        private:
            std::vector<Point> Container;

        public:
            explicit PointArray();
            PointArray(Box& B);
            template<typename T, typename... Args>
            explicit PointArray(T FirstPoint, const Args... RemainingPoints);
            IntegerArray Colors;
            ~PointArray();

            std::size_t Size() const;

            bool Empty() const;

            PointArray& Clear();

            IntegerArray GetColours() const;

            Point& operator [](int I);

            const Point& operator [](int I) const;

            operator const std::vector<Point>& () const;

            operator const PointArray& () const;

            PointArray& operator ()(std::vector<Point> PA);

            operator std::vector<Point>() const;

            bool operator == (const PointArray& PA) const;

            bool operator != (const PointArray& PA) const;

            PointArray& operator += (const Point& PT);

            PointArray& operator += (const PointArray& PA);

            PointArray& operator -= (const Point& PT);

            PointArray& operator -= (const PointArray& PA);

            PointArray& operator = (const PointArray& PA);

            PointArray& operator << (const Point& PT);

            PointArray& operator << (const PointArray& PA);

            void SetLength(std::size_t NewLength, Point P = Point(0, 0));

            template<typename T, typename... Args>
            PointArray& operator()(T FirstPoint, const Args... RemainingPoints);

            Point Middle();

            PointArray& FromBox(const Box& B);

            bool Contains(const Point& PointToFind);

            PointArray& Append(const PointArray& PA);

            PointArray& Delete(std::uint32_t Position);

            PointArray& Delete(const Point& PointToDelete, bool All = false);

            PointArray& Delete(const PointArray& PointsToDelete);

            PointArray& StringToPointArray(const tstring& StringToConvert);

            friend tostream& operator << (tostream& Str, const PointArray& PA);

            PointArray operator + (const Point& PT);

            PointArray operator + (const PointArray& PA);

            PointArray operator - (const Point& PT);

            PointArray operator - (const PointArray& PA);
    };

    /**
     * 												DECLARATION FOR INTEGER2DARRAYS NON-INLINE TEMPLATES
     *
     *
    **/

    template<typename T, typename... Args>
    PointArray::PointArray(T FirstPoint, const Args... RemainingPoints) : Container(0), Colors()
    {
        this->Container = {FirstPoint, RemainingPoints...};
        for (std::size_t I = 0; I < Container.size(); ++I)
        {
            Colors(Container[I].Color);
        }
    }

    template<typename T, typename... Args>
    PointArray& PointArray::operator()(T FirstPoint, const Args... RemainingPoints)
    {
        for (T PointData :
                {
                    FirstPoint, RemainingPoints...
                })
        {
            Container.emplace_back(PointData);
            Colors(PointData.Color);
        }
        return *this;
    }


    /**
     * 												POINT2DARRAYS
     *
     *
    **/


    class Point2DArray
    {
        private:
            std::vector<PointArray> Container;

        public:
            explicit Point2DArray();
            template<typename T, typename... Args>
            explicit Point2DArray(T FirstTPA, const Args... RemainingTPAs);
            Integer2DArray Colors2DA;
            ~Point2DArray();

            std::size_t Size() const;

            std::size_t Size(int I) const;

            bool Empty() const;

            Point2DArray& Clear();

            PointArray& operator [](int I);

            const PointArray& operator [](int I) const;

            operator const std::vector<PointArray>& () const;

            operator const Point2DArray& () const;

            Point2DArray& operator ()(std::vector<PointArray> PA);

            operator std::vector<PointArray>() const;

            bool operator == (const Point2DArray& P2D) const;

            bool operator != (const Point2DArray& P2D) const;

            Point2DArray& operator += (const PointArray& PA);

            Point2DArray& operator += (const Point2DArray& P2D);

            Point2DArray& operator -= (const PointArray& PA);

            Point2DArray& operator -= (const Point2DArray& P2D);

            Point2DArray& operator = (const Point2DArray& P2D);

            Point2DArray& operator << (const PointArray& PA);

            Point2DArray& operator << (const Point2DArray& P2D);

            void SetLength(std::size_t NewLength, std::size_t InnerLength = 0, Point P = Point(0, 0));

            void SetLength(std::size_t NewLength, PointArray PA);

            template<typename T, typename... Args>
            Point2DArray& operator()(T FirstTPA, const Args... RemainingTPAs);

            bool Contains(const PointArray& PA);

            Point2DArray& Append(const Point2DArray& P2D);

            Point2DArray& Delete(std::uint32_t Position);

            Point2DArray& Delete(const PointArray& PA, bool All = false);

            Point2DArray& Delete(const Point2DArray& PA);

            friend tostream& operator << (tostream& Str, const Point2DArray& P2D);

            Point2DArray operator + (const PointArray& PA);

            Point2DArray operator + (const Point2DArray& P2D);

            Point2DArray operator - (const PointArray& PA);

            Point2DArray operator - (const Point2DArray& P2D);
    };

    /**
     * 												DECLARATION FOR POINT2DARRAYS NON-INLINE TEMPLATES
     *
     *
    **/

    template<typename T, typename... Args>
    Point2DArray::Point2DArray(T FirstTPA, const Args... RemainingTPAs) : Container(0), Colors2DA()
    {
        this->Container = {FirstTPA, RemainingTPAs...};
        for (std::size_t I = 0; I < Container.size(); ++I)
        {
            Colors2DA(Container[I].Colors);
        }
    }

    template<typename T, typename... Args>
    Point2DArray& Point2DArray::operator()(T FirstTPA, const Args... RemainingTPAs)
    {
        for (T PAInfo :
                {
                    FirstTPA, RemainingTPAs...
                })
        {
            Container.emplace_back(PAInfo);
            Colors2DA(PAInfo.Colors);
        }
        return *this;
    }


    /**
     * 												EXTENDEDARRAYS
     *
     *
    **/


    class ExtendedArray
    {
        private:
            std::vector<double> Container;

        public:
            explicit ExtendedArray();
            template<typename T, typename... Args>
            explicit ExtendedArray(T FirstExt, const Args... RemainingExts);
            ~ExtendedArray();

            std::size_t Size() const;

            bool Empty() const;

            ExtendedArray& Clear();

            double& operator [](int I);

            const double& operator [](int I) const;

            operator const std::vector<double>& () const;

            operator const ExtendedArray& () const;

            ExtendedArray& operator ()(std::vector<double> EA);

            operator std::vector<double>() const;

            bool operator == (const ExtendedArray& EA) const;

            bool operator != (const ExtendedArray& EA) const;

            ExtendedArray& operator += (const double& D);

            ExtendedArray& operator += (const ExtendedArray& EA);

            ExtendedArray& operator -= (const double& D);

            ExtendedArray& operator -= (const ExtendedArray& EA);

            ExtendedArray& operator = (const ExtendedArray& EA);

            ExtendedArray& operator << (const double& D);

            ExtendedArray& operator << (const ExtendedArray& EA);

            void SetLength(std::size_t NewLength, double D = 0);

            template<typename T, typename... Args>
            ExtendedArray& operator ()(T FirstExt, const Args... RemainingExts);

            bool Contains(double ExtendedToFind);

            ExtendedArray& Append(const ExtendedArray& EA);

            ExtendedArray& Delete(std::uint32_t Position);

            ExtendedArray& Delete(const double& ExtendedToDelete, bool All);

            ExtendedArray& Delete(const ExtendedArray& ExtendsToDelete);

            friend tostream& operator << (tostream& Str, const ExtendedArray& EA);

            ExtendedArray operator + (const double& D);

            ExtendedArray operator + (const ExtendedArray& EA);

            ExtendedArray operator - (const double& D);

            ExtendedArray operator - (const ExtendedArray& EA);
    };

    /**
     * 												DECLARATION FOR EXTENDEDARRAYS NON-INLINE TEMPLATES
     *
     *
    **/

    template<typename T, typename... Args>
    ExtendedArray::ExtendedArray(T FirstExt, const Args... RemainingExts)
    {
        this->Container = {FirstExt, RemainingExts...};
    }

    template<typename T, typename... Args>
    ExtendedArray& ExtendedArray::operator ()(T FirstExt, const Args... RemainingExts)
    {
        this->Container = {FirstExt, RemainingExts...};
        return *this;
    }


    /**
     * 												EXTENDED2DARRAYS
     *
     *
    **/

    class Extended2DArray
    {
        private:
            std::vector<ExtendedArray> Container;

        public:
            explicit Extended2DArray();
            template<typename T, typename... Args>
            explicit Extended2DArray(T FirstExtA, const Args... RemainingExtAs);
            ~Extended2DArray();

            std::size_t Size() const;

            std::size_t Size(int I) const;

            bool Empty() const;

            Extended2DArray& Clear();

            ExtendedArray& operator [](int I);

            const ExtendedArray& operator [](int I) const;

            operator const std::vector<ExtendedArray>& () const;

            operator const Extended2DArray& () const;

            Extended2DArray& operator ()(std::vector<ExtendedArray> E2D);

            operator std::vector<ExtendedArray>() const;

            bool operator == (const Extended2DArray& E2D) const;

            bool operator != (const Extended2DArray& E2D) const;

            Extended2DArray& operator += (const ExtendedArray& EA);

            Extended2DArray& operator += (const Extended2DArray& E2D);

            Extended2DArray& operator -= (const ExtendedArray& EA);

            Extended2DArray& operator -= (const Extended2DArray& E2D);

            Extended2DArray& operator = (const Extended2DArray& E2D);

            Extended2DArray& operator << (const ExtendedArray& EA);

            Extended2DArray& operator << (const Extended2DArray& E2D);

            void SetLength(std::size_t NewLength, std::size_t Inner = 0, double D = 0);

            void SetLength(std::size_t NewLength, ExtendedArray EA);

            template<typename T, typename... Args>
            Extended2DArray& operator ()(T FirstExtA, const Args... RemainingExtAs);

            bool Contains(const ExtendedArray& EA);

            Extended2DArray& Append(const Extended2DArray& E2D);

            Extended2DArray& Delete(std::uint32_t Position);

            Extended2DArray& Delete(const ExtendedArray& EA, bool All = false);

            Extended2DArray& Delete(const Extended2DArray& EA);

            friend tostream& operator << (tostream& Str, const Extended2DArray& E2D);

            Extended2DArray operator + (const ExtendedArray& EA);

            Extended2DArray operator + (const Extended2DArray& E2D);

            Extended2DArray operator - (const ExtendedArray& EA);

            Extended2DArray operator - (const Extended2DArray& E2D);
    };

    /**
     * 												DECLARATION FOR EXTENDED2DARRAYS NON-INLINE TEMPLATES
     *
     *
    **/

    template<typename T, typename... Args>
    Extended2DArray::Extended2DArray(T FirstExtA, const Args... RemainingExtAs) : Container()
    {
        this->Container = {FirstExtA, RemainingExtAs...};
    }

    template<typename T, typename... Args>
    Extended2DArray& Extended2DArray::operator ()(T FirstExtA, const Args... RemainingExtAs)
    {
        for (T EXAData :
                {
                    FirstExtA, RemainingExtAs...
                })
        {
            Container.emplace_back(EXAData);
        }
        return *this;
    }


    /**
     * 												STRINGARRAYS
     *
     *
    **/

    class StringArray
    {
        private:
            std::vector<tstring> Container;

        public:
            explicit StringArray();
            template<typename T, typename... Args>
            explicit StringArray(T FirstStr, const Args... RemainingStrs);
            ~StringArray();

            std::size_t Size() const;

            bool Empty() const;

            StringArray& Clear();

            tstring& operator [](int I);

            const tstring& operator [](int I) const;

            operator const std::vector<tstring>& () const;

            operator const StringArray& () const;

            StringArray& operator ()(std::vector<tstring> SA);

            operator std::vector<tstring>() const;

            bool operator == (const StringArray& SA) const;

            bool operator != (const StringArray& SA) const;

            StringArray& operator += (const tstring& S);

            StringArray& operator += (const StringArray& SA);

            StringArray& operator -= (const tstring& S);

            StringArray& operator -= (const StringArray& SA);

            StringArray& operator = (const StringArray& SA);

            StringArray& operator << (const tstring& S);

            StringArray& operator << (const StringArray& SA);

            void SetLength(std::size_t NewLength, tstring S = tstring());

            template<typename T, typename... Args>
            StringArray& operator ()(T FirstStr, const Args... RemainingStrs);

            StringArray& RemoveSortDuplicates();

            bool Contains(tstring StringToFind, bool CaseSensitive = true);

            StringArray& Append(const StringArray& SA);

            StringArray& Delete(std::uint32_t Position);

            StringArray& Delete(tstring StringToDelete, bool CaseSensitive = true, bool All = false);

            StringArray& Delete(const StringArray& StringsToDelete, bool CaseSensitive = true);

            friend tostream& operator << (tostream& Str, const StringArray& SA);

            StringArray operator + (const tstring& S);

            StringArray operator + (const StringArray& SA);

            StringArray operator - (const tstring& S);

            StringArray operator - (const StringArray& SA);
    };

    /**
     * 												DECLARATION FOR STRINGARRAYS NON-INLINE TEMPLATES
     *
     *
    **/

    template<typename T, typename... Args>
    StringArray::StringArray(T FirstStr, const Args... RemainingStrs) : Container(0)
    {
        this->Container = {FirstStr, RemainingStrs...};
    }

    template<typename T, typename... Args>
    StringArray& StringArray::operator ()(T FirstStr, const Args... RemainingStrs)
    {
        for (T StrData :
                {
                    FirstStr, RemainingStrs...
                })
        {
            Container.emplace_back(StrData);
        }
        return *this;
    }


    /**
     * 												STRING2DARRAYS
     *
     *
    **/


    class String2DArray
    {
        private:
            std::vector<StringArray> Container;

        public:
            explicit String2DArray();
            template<typename T, typename... Args>
            explicit String2DArray(T FirstStr, const Args... RemainingStrs);
            ~String2DArray();

            std::size_t Size() const;

            std::size_t Size(int I) const;

            bool Empty() const;

            String2DArray& Clear();

            StringArray& operator [](int I);

            const StringArray& operator [](int I) const;

            operator const std::vector<StringArray>& () const;

            operator const String2DArray& () const;

            String2DArray& operator ()(std::vector<StringArray> S2D);

            operator std::vector<StringArray>() const;

            bool operator == (const String2DArray& S2D) const;

            bool operator != (const String2DArray& S2D) const;

            String2DArray& operator += (const StringArray& SA);

            String2DArray& operator += (const String2DArray& S2D);

            String2DArray& operator -= (const StringArray& SA);

            String2DArray& operator -= (const String2DArray& S2D);

            String2DArray& operator = (const String2DArray& S2D);

            String2DArray& operator << (const StringArray& SA);

            String2DArray& operator << (const String2DArray& S2D);

            void SetLength(std::size_t NewLength, std::size_t InnerLength = 0, tstring S = tstring());

            void SetLength(std::size_t NewLength, StringArray SA);

            template<typename T, typename... Args>
            String2DArray& operator ()(T FirstStr, const Args... RemainingStrs);

            bool Contains(StringArray StringArrayToFind, bool CaseSensitive = true);

            String2DArray& Append(const String2DArray& S2D);

            String2DArray& Delete(std::uint32_t Position);

            String2DArray& Delete(StringArray SA, bool CaseSensitive = true, bool All = false);

            String2DArray& Delete(String2DArray SA, bool CaseSensitive = true);

            friend tostream& operator << (tostream& Str, const String2DArray& S2D);

            String2DArray operator + (const StringArray& SA);

            String2DArray operator + (const String2DArray& S2D);

            String2DArray operator - (const StringArray& SA);

            String2DArray operator - (const String2DArray& S2D);
    };

    /**
     * 												DECLARATION FOR STRING2DARRAYS NON-INLINE TEMPLATES
     *
     *
    **/

    template<typename T, typename... Args>
    String2DArray::String2DArray(T FirstStr, const Args... RemainingStrs) : Container(0)
    {
        this->Container = {FirstStr, RemainingStrs...};
    }

    template<typename T, typename... Args>
    String2DArray& String2DArray::operator ()(T FirstStr, const Args... RemainingStrs)
    {
        for (T StrAData :
                {
                    FirstStr, RemainingStrs...
                })
        {
            Container.emplace_back(StrAData);
        }
        return *this;
    }


    /**
     * 												CHARARRAYS
     *
     *
    **/


    class CharArray
    {
        private:
            std::vector<TCHAR> Container;

        public:
            explicit CharArray();
            template<typename T, typename... Args>
            explicit CharArray(T FirstChr, const Args... RemainingChrs);
            ~CharArray();

            std::size_t Size() const;

            bool Empty() const;

            CharArray& Clear();

            TCHAR& operator [](int I);

            const TCHAR& operator [](int I) const;

            operator const std::vector<TCHAR>& () const;

            operator const CharArray& () const;

            CharArray& operator ()(std::vector<TCHAR> CA);

            operator std::vector<TCHAR>() const;

            bool operator == (const CharArray& CA) const;

            bool operator != (const CharArray& CA) const;

            CharArray& operator += (const TCHAR& C);

            CharArray& operator += (const CharArray& CA);

            CharArray& operator -= (const TCHAR& C);

            CharArray& operator -= (const CharArray& CA);

            CharArray& operator = (const CharArray& CA);

            CharArray& operator << (const TCHAR& C);

            CharArray& operator << (const CharArray& CA);

            void SetLength(std::size_t NewLength);

            template<typename T, typename... Args>
            CharArray& operator ()(T FirstChr, const Args... RemainingChrs);

            bool Contains(TCHAR CharToFind, bool CaseSensitive = true);

            CharArray& Append(const CharArray& CA);

            CharArray& Delete(std::uint32_t Position);

            CharArray& Delete(TCHAR CharToDelete, bool CaseSensitive = true, bool All = false);

            CharArray& Delete(const CharArray& CharsToDelete, bool CaseSensitive = true);

            friend tostream& operator << (tostream& Str, const CharArray& CA);

            CharArray operator + (const TCHAR& C);

            CharArray operator + (const CharArray& CA);

            CharArray operator - (const TCHAR& C);

            CharArray operator - (const CharArray& CA);
    };

    /**
     * 												DECLARATION FOR CHARARRAYS NON-INLINE TEMPLATES
     *
     *
    **/

    template<typename T, typename... Args>
    CharArray::CharArray(T FirstChr, const Args... RemainingChrs) : Container(0)
    {
        this->Container = {FirstChr, RemainingChrs...};
    }

    template<typename T, typename... Args>
    CharArray& CharArray::operator ()(T FirstChr, const Args... RemainingChrs)
    {
        for (T CharData :
                {
                    FirstChr, RemainingChrs...
                })
        {
            Container.emplace_back(CharData);
        }
        return *this;
    }


    /**
     * 												REPLACEMENTFLAGS
     *
     *
    **/


    struct ReplacementFlags
    {
        public:
            bool rfReplaceAll, rfIgnoreCase;
            ReplacementFlags(bool ReplaceAll = false, bool IgnoreCase = false);
            ~ReplacementFlags();

            ReplacementFlags& operator ()(bool ReplaceAll = false, bool IgnoreCase = false);

        private:
            bool operator == (const ReplacementFlags& RF) const;

            bool operator != (const ReplacementFlags& RF) const;
    };
}

#endif //TYPES_HPP_INCLUDED
