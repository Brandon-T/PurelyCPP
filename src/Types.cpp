// *** ADDED BY HEADER FIXUP ***
#include <cstdlib>
// *** END ***
#include "Types.hpp"

/** Types **/

namespace cxx
{
    Point::Point() : X(0), Y(0), Color(0) {}

    Point::Point(int x, int y) : X(x), Y(y), Color(0) {}

    Point::Point(int x, int y, std::uint32_t Colour) : X(x), Y(y), Color(Colour) {}

    Point::~Point() {}

    Point& Point::operator ()(int x, int y)
    {
        if (X != x && Y != y)
        {
            X = x;
            Y = y;
        }
        return *this;
    }

    Point& Point::operator ()(int x, int y, std::uint32_t Colour)
    {
        if (X != x && Y != y && Colour != Color)
        {
            X = x;
            Y = y;
            Color = Colour;
        }
        return *this;
    }

    bool Point::operator == (const Point& PT) const//Are the points Equal?
    {
        return ((X == PT.X) && (Y == PT.Y));
    }

    bool Point::operator != (const Point& PT) const//Are the points Not equal?
    {
        return ((X != PT.X) && (Y != PT.Y));
    }

    Point& Point::operator = (const Point& PT)
    {
        if (this != &PT)
        {
            X = PT.X;
            Y = PT.Y;
        }
        return *this;
    }

    Point& Point::operator += (const int& I)
    {
        if (I > 0)
        {
            X += I;
            Y += I;
        }
        return *this;
    }

    Point& Point::operator += (const Point& PT)
    {
        X += PT.X;
        Y += PT.Y;
        return *this;
    }

    Point& Point::operator -= (const int& I)
    {
        if (I > 0)
        {
            X -= I;
            Y -= I;
        }
        return *this;
    }

    Point& Point::operator -= (const Point& PT)					//"^([^\S])"
    {
        X -= PT.X;
        Y -= PT.Y;
        return *this;
    }

    Point& Point::operator *= (const int& I)
    {
        X *= I;
        Y *= I;
        return *this;
    }

    Point& Point::operator *= (const Point& PT)
    {
        X *= PT.X;
        Y *= PT.Y;
        return *this;
    }

    Point& Point::operator /= (const int& I)
    {
        assert(I != 0);
        X /= I;
        Y /= I;
        return *this;
    }

    Point& Point::operator /= (const Point& PT)
    {
        assert((PT.X != 0) || (PT.Y != 0));
        X /= PT.X;
        Y /= PT.Y;
        return *this;
    }

    tostream& operator << (tostream& Str, const Point& PT)  //For use with Writeln&  cout.
    {
        Str << _T("(") << PT.X << _T(", ") << PT.Y << _T(")");
        return Str;
    }

    Point Point::operator + (const int& I)
    {
        return ((I > 0) ? (Point(*this) += I) : *this);
    }

    Point Point::operator + (const Point& PT)   //Add two points.
    {
        return Point(*this) += PT;
    }

    Point Point::operator - (const int& I)
    {
        return ((I > 0) ? (Point(*this) -= I) : *this);
    }

    Point Point::operator - (const Point& PT)   //Subtract two points.
    {
        return Point(*this) -= PT;
    }


    /**
     * 												DECLARATION FOR BOXES
     *
     *
    **/


    Box::Box() : X1(0), Y1(0), X2(0), Y2(0) {}

    Box::Box(int x1, int y1, int x2, int y2) : X1(x1), Y1(y1), X2(x2), Y2(y2) {}

    Box::Box(Point UpperLeft, Point LowerRight) : X1(UpperLeft.X), Y1(UpperLeft.Y), X2(LowerRight.X), Y2(LowerRight.Y) {}

    Box::~Box() {}

    Box& Box::operator ()(int x1, int y1, int x2, int y2)
    {
        if ((X1 != x1) && (Y1 != y1) && (X2 != x2) && (Y2 != y2))
        {
            X1 = x1;
            Y1 = y1;
            X2 = x2;
            Y2 = y2;
        }
        return *this;
    }

    Box& Box::operator ()(Point UpperLeft, Point LowerRight)
    {
        if ((X1 != UpperLeft.X) && (Y1 != UpperLeft.Y) && (X2 != LowerRight.X) && (Y2 != LowerRight.Y))
        {
            X1 = UpperLeft.X;
            Y1 = UpperLeft.Y;
            X2 = LowerRight.X;
            Y2 = LowerRight.Y;
        }
        return *this;
    }

    Box::operator const Box& () const
    {
        return *this;
    }

    int Box::Width() const
    {
        return ((X2 < 0 ? -X2 : X2) - (X1 < 0 ? -X1 : X1));
    }

    int Box::Height() const
    {
        return ((Y2 < 0 ? -Y2 : Y2) - (Y1 < 0 ? -Y1 : Y1));
    }

    int Box::Area() const
    {
        return (((X2 < 0 ? -X2 : X2) - (X1 < 0 ? -X1 : X1)) * ((Y2 < 0 ? -Y2 : Y2) - (Y1 < 0 ? -Y1 : Y1)));
    }

    bool Box::operator == (const Box& B) const
    {
        return ((X1 == B.X1) && (X2 == B.X2) && (Y1 == B.Y1) && (Y2 == B.Y2));
    }

    bool Box::operator != (const Box& B) const
    {
        return !(*this == B);
    }

    Box& Box::operator += (const int& I)
    {
        if (I > 0)
            X2 += I;
        return *this;
    }

    Box& Box::operator += (const Box& B)
    {
        X1 += B.X1;
        Y1 += B.Y1;
        X2 += B.X2;
        Y2 += B.Y2;
        return *this;
    }

    Box& Box::operator -= (const int& I)
    {
        if (I > 0)
        {
            X1 -= I;
            Y1 -= I;
            X2 -= I;
            Y2 -= I;
        }
        return *this;
    }

    Box& Box::operator -= (const Box& B)
    {
        X1 -= B.X1;
        Y1 -= B.Y1;
        X2 -= B.X2;
        Y2 -= B.Y2;
        return *this;
    }

    Box& Box::operator *= (const int& I)
    {
        X1 *= I;
        Y1 *= I;
        X2 *= I;
        Y2 *= I;
        return *this;
    }

    Box& Box::operator *= (const Box& B)
    {
        X1 *= B.X1;
        Y1 *= B.Y1;
        X2 *= B.X2;
        Y2 *= B.Y2;
        return *this;
    }

    Box& Box::operator /= (const int& I)
    {
        assert(I != 0);
        X1 /= I;
        Y1 /= I;
        X2 /= I;
        Y2 /= I;
        return *this;
    }

    Box& Box::operator /= (const Box& B)
    {
        assert((B.X1 != 0) || (B.Y1 != 0) || (B.X2 != 0) || (B.Y2 != 0));
        X1 /= B.X1;
        Y1 /= B.Y1;
        X2 /= B.X2;
        Y2 /= B.Y2;
        return *this;
    }

    Point Box::MidPoint(const Box& B)
    {
        return Point(((B.X1 + B.X2) / 2), ((B.Y1 + B.Y2) / 2));
    }

    Box& Box::ToBox(Point UpperLeft, Point LowerRight)
    {
        if ((X1 != UpperLeft.X) && (Y1 != UpperLeft.Y) && (X2 != LowerRight.X) && (Y2 != LowerRight.Y))
        {
            X1 = UpperLeft.X;
            Y1 = UpperLeft.Y;
            X2 = LowerRight.X;
            Y2 = LowerRight.Y;
        }
        return *this;
    }

    Box& Box::operator = (const Box& B)
    {
        if (this != &B)
        {
            X1 = B.X1;
            Y1 = B.Y1;
            X2 = B.X2;
            Y2 = B.Y2;
        }
        return *this;
    }

    bool Box::Contains(const Point& P) const
    {
        return (X1 <= P.X && X2 >= P.X && Y1 <= P.X && Y2 >= P.X);
    }

    bool Box::Contains(const Box& B) const
    {
        return (X1 <= B.X1 && X2 >= B.X2 && Y1 <= B.Y1 && Y2 >= B.Y2);
    }

    tostream& operator << (tostream& Str, const Box& B)//For use with Writeln&  cout.
    {
        Str << _T("(") << B.X1 << _T(", ") << B.Y1 << _T(", ") << B.X2 << _T(", ") << B.Y2 << _T(")");
        return Str;
    }

    Box Box::operator + (const int& I)  //Increase Box Size.
    {
        return ((I > 0) ? (Box(*this) += I) : *this);
    }

    Box Box::operator + (const Box& B)
    {
        return Box(*this) += B;
    }

    Box Box::operator - (const int& I)  //Decrease Box Size.
    {
        return ((I > 0) ? (Box(*this) -= I) : *this);
    }

    Box Box::operator - (const Box& B)
    {
        return Box(*this) += B;
    }




    /**
     * 												DECLARATION FOR BOXARRAYS
     *
     *
    **/

    BoxArray::BoxArray() : Container(0) {}

    BoxArray::~BoxArray() {}

    std::size_t BoxArray::Size() const
    {
        return Container.size();
    }

    std::size_t BoxArray::Size(int I) const
    {
        assert(I >= 0 && !Container.empty());
        return (Container[I].Width() * Container[I].Height());
    }

    bool BoxArray::Empty() const
    {
        return Container.empty();
    }

    BoxArray& BoxArray::Clear()
    {
        Container.clear();
        return *this;
    }

    Box& BoxArray::operator [](int I)
    {
        assert(I >= 0 && !Container.empty());
        return Container[I];
    }

    const Box& BoxArray::operator [](int I) const
    {
        assert(I >= 0 && !Container.empty());
        return Container[I];
    }

    BoxArray::operator const std::vector<Box>& () const
    {
        return Container;
    }

    BoxArray::operator const BoxArray& () const
    {
        return *this;
    }

    BoxArray& BoxArray::operator ()(std::vector<Box> BA)
    {
        if (Container != BA)
        {
            if (!Container.empty())
                Container.clear();

            Container.insert(Container.end(), BA.begin(), BA.end());
        }
        return *this;
    }

    BoxArray::operator std::vector<Box>() const
    {
        return std::vector<Box>(Container.begin(), Container.end());
    }

    bool BoxArray::operator == (const BoxArray& BA) const			//Should this be friend?
    {
        return (Container == BA.Container);
    }

    bool BoxArray::operator != (const BoxArray& BA) const
    {
        return !(Container == BA.Container);
    }

    BoxArray& BoxArray::operator += (const Box& B)
    {
        Container.emplace_back(B);
        return *this;
    }

    BoxArray& BoxArray::operator += (const BoxArray& BA)
    {
        Container.insert(Container.end(), BA.Container.begin(), BA.Container.end());
        return *this;
    }

    BoxArray& BoxArray::operator -= (const Box& B)
    {
        this->Delete(B, true);
        return *this;
    }

    BoxArray& BoxArray::operator -= (const BoxArray& BA)
    {
        this->Delete(BA);
        return *this;
    }

    BoxArray& BoxArray::operator = (const BoxArray& BA)
    {
        if (this != &BA)
        {
            if (!Container.empty())
                Container.clear();

            Container.insert(Container.end(), BA.Container.begin(), BA.Container.end());
        }
        return *this;
    }

    BoxArray& BoxArray::operator << (const Box& B)
    {
        Container.emplace_back(B);
        return *this;
    }

    BoxArray& BoxArray::operator << (const BoxArray& BA)
    {
        Container.insert(Container.end(), BA.Container.begin(), BA.Container.end());
        return *this;
    }

    void BoxArray::SetLength(const std::size_t NewLength, const Box& B)
    {
        this->Container.resize(NewLength, B);
    }

    bool BoxArray::Contains(const Box& BoxToFind)
    {
        return std::find(Container.begin(), Container.end(), BoxToFind) != Container.end();
    }

    BoxArray& BoxArray::Append(const BoxArray& BA)
    {
        Container.insert(Container.end(), BA.Container.begin(), BA.Container.end());
        return *this;
    }

    BoxArray& BoxArray::Delete(std::uint32_t Position)
    {
        if (!Container.empty() && (Container.size() >= Position))
            this->Container.erase(Container.begin() + Position);

        return *this;
    }

    BoxArray& BoxArray::Delete(const Box& BoxToDelete, bool All)
    {
        if (All)
        {
            Container.erase(std::remove(Container.begin(), Container.end(), BoxToDelete), Container.end());
        }
        else
        {
            auto it = std::find(Container.begin(), Container.end(), BoxToDelete);
            if (it != Container.end())
            {
                Container.erase(it);
            }
        }
        return *this;
    }

    BoxArray& BoxArray::Delete(const BoxArray& BA)
    {
        for (auto it = BA.Container.begin(); it != BA.Container.end(); ++it)
        {
            this->Delete(*it, true);
        }
        return *this;
    }

    tostream& operator << (tostream& Str, const BoxArray& BA)   //For use with Writeln&  cout.
    {
        if (!BA.Container.empty())
        {
            Str << _T("[");
            for (auto it = BA.Container.begin(); it != BA.Container.end() - 1; ++it)
            {
                Str << *it << _T(", ");
            }
            Str << BA.Container.back() << _T("]");
        }
        else
        {
            Str << _T("[]");
        }
        return Str;
    }

    BoxArray BoxArray::operator + (const Box& B)
    {
        return (BoxArray(*this) += B);
    }

    BoxArray BoxArray::operator + (const BoxArray& BA)
    {
        return (BoxArray(*this) += BA);
    }

    BoxArray BoxArray::operator - (const Box& B)
    {
        return (BoxArray(*this) -= B);
    }

    BoxArray BoxArray::operator - (const BoxArray& BA)
    {
        return (BoxArray(*this) -= BA);
    }


    /**
     * 												DECLARATION FOR INTEGERARRAYS
     *
     *
    **/

    IntegerArray::IntegerArray() : Container(0) {}

    IntegerArray::~IntegerArray() {}

    std::size_t IntegerArray::Size() const
    {
        return Container.size();
    }

    bool IntegerArray::Empty() const
    {
        return Container.empty();
    }

    IntegerArray& IntegerArray::Clear()
    {
        Container.clear();
        return *this;
    }

    int& IntegerArray::operator [](int I)
    {
        assert(I >= 0 && !Container.empty());
        return Container[I];
    }

    const int& IntegerArray::operator [](int I) const
    {
        assert(I >= 0 && !Container.empty());
        return Container[I];
    }

    IntegerArray::operator const std::vector<int>& () const
    {
        return Container;
    }

    IntegerArray::operator const IntegerArray& () const
    {
        return *this;
    }

    IntegerArray& IntegerArray::operator ()(std::vector<int> IA)
    {
        if (Container != IA)
        {
            Container.clear();
            Container.insert(Container.end(), IA.begin(), IA.end());
        }
        return *this;
    }

    IntegerArray::operator std::vector<int>() const
    {
        return std::vector<int>(Container.begin(), Container.end());
    }

    bool IntegerArray::operator == (const IntegerArray& I) const			//Should this be friend?
    {
        return (Container == I.Container);
    }

    bool IntegerArray::operator != (const IntegerArray& I) const
    {
        return !(Container == I.Container);
    }

    IntegerArray& IntegerArray::operator += (const int& I)
    {
        Container.emplace_back(I);
        return *this;
    }

    IntegerArray& IntegerArray::operator += (const IntegerArray& IA)
    {
        Container.insert(Container.end(), IA.Container.begin(), IA.Container.end());
        return *this;
    }

    IntegerArray& IntegerArray::operator -= (const int& I)
    {
        this->Delete(I, true);
        return *this;
    }

    IntegerArray& IntegerArray::operator -= (const IntegerArray& IA)
    {
        this->Delete(IA);
        return *this;
    }

    IntegerArray& IntegerArray::operator = (const IntegerArray& IA)
    {
        if (this != &IA)
        {
            Container.insert(Container.end(), IA.Container.begin(), IA.Container.end());
        }
        return *this;
    }

    IntegerArray& IntegerArray::operator << (const int& I)
    {
        Container.emplace_back(I);
        return *this;
    }

    IntegerArray& IntegerArray::operator << (const IntegerArray& IA)
    {
        Container.insert(Container.end(), IA.Container.begin(), IA.Container.end());
        return *this;
    }

    void IntegerArray::SetLength(const std::size_t NewLength, const int& I)
    {
        this->Container.resize(NewLength, I);
    }

    bool IntegerArray::Contains(int IntToFind)
    {
        return std::find(Container.begin(), Container.end(), IntToFind) != Container.end();
    }

    IntegerArray& IntegerArray::Append(const IntegerArray& IA)
    {
        Container.insert(Container.end(), IA.Container.begin(), IA.Container.end());
        return *this;
    }

    IntegerArray& IntegerArray::Delete(std::uint32_t Position)
    {
        if (!Container.empty() && (Container.size() >= Position))
            this->Container.erase(Container.begin() + Position);

        return *this;
    }

    IntegerArray& IntegerArray::Delete(const int& IntToDelete, bool All)
    {
        if (All)
        {
            Container.erase(std::remove(Container.begin(), Container.end(), IntToDelete), Container.end());
        }
        else
        {
            auto it = std::find(Container.begin(), Container.end(), IntToDelete);
            if (it != Container.end())
            {
                Container.erase(it);
            }
        }

        return *this;
    }

    IntegerArray& IntegerArray::Delete(const IntegerArray& IA)
    {
        for (auto it = IA.Container.begin(); it != IA.Container.end(); ++it)
        {
            this->Delete(*it, true);
        }
        return *this;
    }

    tostream& operator << (tostream& Str, const IntegerArray& IA)  //For use with Writeln&  cout.
    {
        if (!IA.Container.empty())
        {
            Str << _T("[");
            for (auto it = IA.Container.begin(); it != IA.Container.end() - 1; ++it)
            {
                Str << *it << _T(", ");
            }
            Str << IA.Container.back() << _T("]");
        }
        else
        {
            Str << _T("[]");
        }
        return Str;
    }

    IntegerArray IntegerArray::operator + (const int& I)
    {
        return (IntegerArray(*this) += I);
    }

    IntegerArray IntegerArray::operator + (const IntegerArray& IA)
    {
        return (IntegerArray(*this) += IA);
    }

    IntegerArray IntegerArray::operator - (const int& I)
    {
        return (IntegerArray(*this) -= I);
    }

    IntegerArray IntegerArray::operator - (const IntegerArray& IA)
    {
        return (IntegerArray(*this) -= IA);
    }


    /**
     * 												DECLARATION FOR INTEGER2DARRAYS
     *
     *
    **/

    Integer2DArray::Integer2DArray() : Container(0) {}

    Integer2DArray::~Integer2DArray() {}

    std::size_t Integer2DArray::Size() const
    {
        return Container.size();
    }

    std::size_t Integer2DArray::Size(int I) const
    {
        assert(I >= 0 && !Container.empty());
        return Container[I].Size();
    }

    bool Integer2DArray::Empty() const
    {
        return Container.empty();
    }

    Integer2DArray& Integer2DArray::Clear()
    {
        Container.clear();
        return *this;
    }

    Integer2DArray& Integer2DArray::operator ()(IntegerArray IA)
    {
        this->Container.emplace_back(IA);
        return *this;
    }

    IntegerArray& Integer2DArray::operator [](int I)
    {
        assert(I >= 0 && !Container.empty());
        return Container[I];
    }

    const IntegerArray& Integer2DArray::operator [](int I) const
    {
        assert(I >= 0 && !Container.empty());
        return Container[I];
    }

    Integer2DArray::operator const std::vector<IntegerArray>& () const
    {
        return Container;
    }

    Integer2DArray::operator const Integer2DArray& () const
    {
        return *this;
    }

    Integer2DArray& Integer2DArray::operator ()(std::vector<IntegerArray> IA)
    {
        if (Container != IA)
        {
            Container.clear();
            Container.insert(Container.end(), IA.begin(), IA.end());
        }
        return *this;
    }

    Integer2DArray::operator std::vector<IntegerArray>() const
    {
        return std::vector<IntegerArray>(Container.begin(), Container.end());
    }

    bool Integer2DArray::operator == (const Integer2DArray& I2D) const			//Should this be friend?
    {
        return (Container == I2D.Container);
    }

    bool Integer2DArray::operator != (const Integer2DArray& I2D) const
    {
        return !(Container == I2D.Container);
    }

    Integer2DArray& Integer2DArray::operator += (const IntegerArray& IA)
    {
        for (std::size_t I = 0; I < IA.Size(); ++I)
            Container.emplace_back(IA[I]);
        return *this;
    }

    Integer2DArray& Integer2DArray::operator += (const Integer2DArray& I2D)
    {
        Container.insert(Container.end(), I2D.Container.begin(), I2D.Container.end());
        return *this;
    }

    Integer2DArray& Integer2DArray::operator -= (const IntegerArray& IA)
    {
        this->Delete(IA, true);
        return *this;
    }

    Integer2DArray& Integer2DArray::operator -= (const Integer2DArray& I2D)
    {
        this->Delete(I2D);
        return *this;
    }

    Integer2DArray& Integer2DArray::operator = (const Integer2DArray& IA)
    {
        if (this != &IA)
        {
            Container.clear();
            Container.insert(Container.end(), IA.Container.begin(), IA.Container.end());
        }
        return *this;
    }

    Integer2DArray& Integer2DArray::operator << (const IntegerArray& IA)
    {
        Container.emplace_back(IA);
        return *this;
    }

    Integer2DArray& Integer2DArray::operator << (const Integer2DArray& I2D)
    {
        Container.insert(Container.end(), I2D.Container.begin(), I2D.Container.end());
        return *this;
    }

    void Integer2DArray::SetLength(const std::size_t NewLength, const std::size_t& InnerLength, const int& I)
    {
        IntegerArray IA;
        IA.SetLength(InnerLength, I);
        this->Container.resize(NewLength, IA);
    }

    void Integer2DArray::SetLength(const std::size_t NewLength, const IntegerArray& IA)
    {
        this->Container.resize(NewLength, IA);
    }

    bool Integer2DArray::Contains(const IntegerArray& IA)
    {
        return std::find(Container.begin(), Container.end(), IA) != Container.end();
    }

    Integer2DArray& Integer2DArray::Append(const Integer2DArray& IA)
    {
        Container.insert(Container.end(), IA.Container.begin(), IA.Container.end());
        return *this;
    }

    Integer2DArray& Integer2DArray::Delete(std::uint32_t Position)
    {
        if (!Container.empty() && (Container.size() >= Position))
            this->Container.erase(Container.begin() + Position);
        return *this;
    }

    Integer2DArray& Integer2DArray::Delete(const IntegerArray& IA, bool All)
    {
        if (All)
        {
            Container.erase(std::remove(Container.begin(), Container.end(), IA), Container.end());
        }
        else
        {
            auto it = std::find(Container.begin(), Container.end(), IA);
            if (it != Container.end())
            {
                Container.erase(it);
            }
        }
        return *this;
    }

    Integer2DArray& Integer2DArray::Delete(const Integer2DArray& I2D)
    {
        for (auto it = I2D.Container.begin(); it != I2D.Container.end(); ++it)
        {
            this->Delete(*it, true);
        }
        return *this;
    }

    tostream& operator << (tostream& Str, const Integer2DArray& I2D)//For use with Writeln&  cout.
    {
        if (!I2D.Container.empty())
        {
            Str << _T("[");
            for (auto it = I2D.Container.begin(); it != I2D.Container.end() - 1; ++it)
            {
                Str << *it << _T(", ");
            }
            Str << I2D.Container.back() << _T("]");
        }
        else
        {
            Str << _T("[]");
        }
        return Str;
    }

    Integer2DArray Integer2DArray::operator + (const IntegerArray& IA)
    {
        return (Integer2DArray(*this) += IA);
    }

    Integer2DArray Integer2DArray::operator + (const Integer2DArray& I2D)
    {
        return (Integer2DArray(*this) += I2D);
    }

    Integer2DArray Integer2DArray::operator - (const IntegerArray& IA)
    {
        return (Integer2DArray(*this) -= IA);
    }

    Integer2DArray Integer2DArray::operator - (const Integer2DArray& I2D)
    {
        return (Integer2DArray(*this) -= I2D);
    }



    /**
     * 												DECLARATION FOR POINTARRAYS
     *
     *
    **/

    PointArray::PointArray() : Container(0), Colors() {}

    PointArray::~PointArray() {}

    PointArray::PointArray(Box& B) : Container(0), Colors()
    {
        std::uint32_t Width = abs(B.X2 - B.X1);
        std::uint32_t Height = abs(B.Y2 - B.Y1);
        if (Width != 0 && Height != 0)
            for (std::size_t I = 0; I < Height; ++I)
            {
                for (std::size_t J = 0; J < Width; ++J)
                {
                    this->Container.emplace_back(Point(J, I));
                }
            }
        else
            this->Container.emplace_back(Point(0, 0));

        for (auto it = Container.begin(); it != Container.end(); ++it)
            Colors(it->Color);
    }

    std::size_t PointArray::Size() const
    {
        return Container.size();
    }

    bool PointArray::Empty() const
    {
        return Container.empty();
    }

    PointArray& PointArray::Clear()
    {
        Container.clear();
        return *this;
    }

    IntegerArray PointArray::GetColours() const
    {
        return Colors;
    }

    Point& PointArray::operator [](int I)
    {
        assert(I >= 0 && !Container.empty());
        return Container[I];
    }

    const Point& PointArray::operator [](int I) const
    {
        assert(I >= 0 && !Container.empty());
        return Container[I];
    }

    PointArray::operator const std::vector<Point>& () const
    {
        return Container;
    }

    PointArray::operator const PointArray& () const
    {
        return *this;
    }

    PointArray& PointArray::operator ()(std::vector<Point> PA)
    {
        if (Container != PA)
        {
            Container.clear();
            Container.insert(Container.end(), PA.begin(), PA.end());
        }
        return *this;
    }

    PointArray::operator std::vector<Point>() const
    {
        return std::vector<Point>(Container.begin(), Container.end());
    }

    bool PointArray::operator == (const PointArray& PA) const			//Should this be friend?
    {
        return (Container == PA.Container);
    }

    bool PointArray::operator != (const PointArray& PA) const
    {
        return !(Container == PA.Container);
    }

    PointArray& PointArray::operator += (const Point& PT)
    {
        Container.emplace_back(PT);
        return *this;
    }

    PointArray& PointArray::operator += (const PointArray& PA)
    {
        if (!PA.Empty())
        {
            Container.insert(Container.end(), PA.Container.begin(), PA.Container.end());
        }
        return *this;
    }

    PointArray& PointArray::operator -= (const Point& PT)
    {
        this->Delete(PT, true);
        return *this;
    }

    PointArray& PointArray::operator -= (const PointArray& PA)
    {
        this->Delete(PA);
        return *this;
    }

    PointArray& PointArray::operator = (const PointArray& PA)
    {
        if (this != &PA)
        {
            Container.clear();
            Container.insert(Container.end(), PA.Container.begin(), PA.Container.end());
        }
        return *this;
    }

    PointArray& PointArray::operator << (const Point& PT)
    {
        Container.emplace_back(PT);
        return *this;
    }

    PointArray& PointArray::operator << (const PointArray& PA)
    {
        Container.insert(Container.begin(), PA.Container.begin(), PA.Container.end());
        return *this;
    }

    void PointArray::SetLength(std::size_t NewLength, Point P)
    {
        this->Container.resize(NewLength, P);
    }

    Point PointArray::Middle()
    {
        if (Container.size() < 1)
            return Point(0, 0);

        Point Result;
        std::size_t Length = Container.size();
        for (auto it = Container.begin(); it != Container.end(); ++it)
            Result += *it;

        return (Result /= Length);
    }

    PointArray& PointArray::FromBox(const Box& B)
    {
        std::uint32_t Width = abs(B.X2 - B.X1);
        std::uint32_t Height = abs(B.Y2 - B.Y1);
        if (Width != 0 && Height != 0)
            for (std::size_t I = 0; I < Height; ++I)
            {
                for (std::size_t J = 0; J < Width; ++J)
                {
                    this->Container.emplace_back(Point(J, I));
                }
            }
        else
            this->Container.emplace_back(Point(0, 0));

        return *this;
    }

    bool PointArray::Contains(const Point& PointToFind)
    {
        return std::find(Container.begin(), Container.end(), PointToFind) != Container.end();
    }

    PointArray& PointArray::Append(const PointArray& PA)
    {
        Container.insert(Container.end(), PA.Container.begin(), PA.Container.end());
        return *this;
    }

    PointArray& PointArray::Delete(std::uint32_t Position)
    {
        if (!Container.empty() && (Container.size() >= Position))
            this->Container.erase(Container.begin() + Position);

        return *this;
    }

    PointArray& PointArray::Delete(const Point& PointToDelete, bool All)
    {
        if (All)
        {
            Container.erase(std::remove(Container.begin(), Container.end(), PointToDelete), Container.end());
        }
        else
        {
            auto it = std::find(Container.begin(), Container.end(), PointToDelete);
            if (it != Container.end())
            {
                Container.erase(it);
            }
        }
        return *this;
    }

    PointArray& PointArray::Delete(const PointArray& PA)
    {
        for (auto it = PA.Container.begin(); it != PA.Container.end(); ++it)
        {
            this->Delete(*it, true);
        }
        return *this;
    }

    tostream& operator << (tostream& Str, const PointArray& PA)  //For use with Writeln&  cout.
    {
        if (!PA.Container.empty())
        {
            Str << _T("[");
            for (auto it = PA.Container.begin(); it != PA.Container.end() - 1; ++it)
            {
                Str << *it << _T(", ");
            }
            Str << PA.Container.back() << _T("]");
        }
        else
        {
            Str << _T("[]");
        }
        return Str;
    }

    PointArray PointArray::operator + (const Point& PT)
    {
        return std::move(PointArray(this->Container) += PT);
    }

    PointArray PointArray::operator + (const PointArray& PA)
    {
        return std::move(PointArray(this->Container) += PA);
    }

    PointArray PointArray::operator - (const Point& PT)
    {
        return std::move(PointArray(this->Container) -= PT);
    }

    PointArray PointArray::operator - (const PointArray& PA)
    {
        return std::move(PointArray(this->Container) -= PA);
    }



    /**
     * 												DECLARATION FOR POINT2DARRAYS
     *
     *
    **/

    Point2DArray::Point2DArray() : Container(0), Colors2DA() {}

    Point2DArray::~Point2DArray() {}

    std::size_t Point2DArray::Size() const
    {
        return Container.size();
    }

    std::size_t Point2DArray::Size(int I) const
    {
        assert(I >= 0 && !Container.empty());
        return Container[I].Size();
    }

    bool Point2DArray::Empty() const
    {
        return Container.empty();
    }

    Point2DArray& Point2DArray::Clear()
    {
        Container.clear();
        return *this;
    }

    PointArray& Point2DArray::operator [](int I)
    {
        assert(I >= 0 && !Container.empty());
        return Container[I];
    }

    const PointArray& Point2DArray::operator [](int I) const
    {
        assert(I >= 0 && !Container.empty());
        return Container[I];
    }

    Point2DArray::operator const std::vector<PointArray>& () const
    {
        return Container;
    }

    Point2DArray::operator const Point2DArray& () const
    {
        return *this;
    }

    Point2DArray& Point2DArray::operator ()(std::vector<PointArray> PA)
    {
        if (Container != PA)
        {
            Container.clear();
            Container.insert(Container.end(), PA.begin(), PA.end());
        }
        return *this;
    }

    Point2DArray::operator std::vector<PointArray>() const
    {
        return std::vector<PointArray>(Container.begin(), Container.end());
    }

    bool Point2DArray::operator == (const Point2DArray& P2D) const			//Should this be friend?
    {
        return (Container == P2D.Container);
    }

    bool Point2DArray::operator != (const Point2DArray& P2D) const
    {
        return !(Container == P2D.Container);
    }

    Point2DArray& Point2DArray::operator += (const PointArray& PA)
    {
        Container.emplace_back(PA);
        return *this;
    }

    Point2DArray& Point2DArray::operator += (const Point2DArray& P2D)
    {
        Container.insert(Container.end(), P2D.Container.begin(), P2D.Container.end());
        return *this;
    }

    Point2DArray& Point2DArray::operator -= (const PointArray& PA)
    {
        this->Delete(PA, true);
        return *this;
    }

    Point2DArray& Point2DArray::operator -= (const Point2DArray& P2D)
    {
        this->Delete(P2D);
        return *this;
    }

    Point2DArray& Point2DArray::operator = (const Point2DArray& P2D)
    {
        if (this != &P2D)
        {
            Container.clear();
            Container.insert(Container.end(), P2D.Container.begin(), P2D.Container.end());
        }
        return *this;
    }

    Point2DArray& Point2DArray::operator << (const PointArray& PA)
    {
        Container.emplace_back(PA);
        return *this;
    }

    Point2DArray& Point2DArray::operator << (const Point2DArray& P2D)
    {
        Container.insert(Container.end(), P2D.Container.begin(), P2D.Container.end());
        return *this;
    }

    void Point2DArray::SetLength(std::size_t NewLength, std::size_t InnerLength, Point P)
    {
        PointArray PA;
        PA.SetLength(InnerLength, P);
        this->Container.resize(NewLength, PA);
    }

    void Point2DArray::SetLength(std::size_t NewLength, PointArray PA)
    {
        this->Container.resize(NewLength, PA);
    }

    bool Point2DArray::Contains(const PointArray& PA)
    {
        return std::find(Container.begin(), Container.end(), PA) != Container.end();
    }

    Point2DArray& Point2DArray::Append(const Point2DArray& P2D)
    {
        Container.insert(Container.end(), P2D.Container.begin(), P2D.Container.end());
        return *this;
    }

    Point2DArray& Point2DArray::Delete(std::uint32_t Position)
    {
        if(!Container.empty() && (Container.size() >= Position))
            this->Container.erase(Container.begin() + Position);

        return *this;
    }

    Point2DArray& Point2DArray::Delete(const PointArray& PA, bool All)
    {
        if (All)
        {
            Container.erase(std::remove(Container.begin(), Container.end(), PA), Container.end());
        }
        else
        {
            auto it = std::find(Container.begin(), Container.end(), PA);
            if (it != Container.end())
            {
                Container.erase(it);
            }
        }
        return *this;
    }

    Point2DArray& Point2DArray::Delete(const Point2DArray& PA)
    {
        for (auto it = PA.Container.begin(); it != PA.Container.end(); ++it)
        {
            this->Delete(*it, true);
        }
        return *this;
    }

    tostream& operator << (tostream& Str, const Point2DArray& P2D) //For use with Writeln&  cout.
    {
        if (!P2D.Container.empty())
        {
            Str << _T("[");
            for (auto it = P2D.Container.begin(); it != P2D.Container.end() - 1; ++it)
            {
                Str << *it << _T(", ");
            }
            Str << P2D.Container.back() << _T("]");
        }
        else
        {
            Str << _T("[]");
        }
        return Str;
    }

    Point2DArray Point2DArray::operator + (const PointArray& PA)
    {
        return std::move(Point2DArray(this->Container) += PA);
    }

    Point2DArray Point2DArray::operator + (const Point2DArray& P2D)
    {
        return std::move(Point2DArray(this->Container) += P2D);
    }

    Point2DArray Point2DArray::operator - (const PointArray& PA)
    {
        return std::move(Point2DArray(this->Container) -= PA);
    }

    Point2DArray Point2DArray::operator - (const Point2DArray& P2D)
    {
        return std::move(Point2DArray(this->Container) -= P2D);
    }


    /**
     * 												DECLARATION FOR EXTENDEDARRAYS
     *
     *
    **/

    ExtendedArray::ExtendedArray() : Container(0) {}

    ExtendedArray::~ExtendedArray() {}

    std::size_t ExtendedArray::Size() const
    {
        return Container.size();
    }

    bool ExtendedArray::Empty() const
    {
        return Container.empty();
    }

    ExtendedArray& ExtendedArray::Clear()
    {
        Container.clear();
        return *this;
    }

    double& ExtendedArray::operator [](int I)
    {
        assert(I >= 0 && !Container.empty());
        return Container[I];
    }

    const double& ExtendedArray::operator [](int I) const
    {
        assert(I >= 0 && !Container.empty());
        return Container[I];
    }

    ExtendedArray::operator const std::vector<double>& () const
    {
        return Container;
    }

    ExtendedArray::operator const ExtendedArray& () const
    {
        return *this;
    }

    ExtendedArray& ExtendedArray::operator ()(std::vector<double> EA)
    {
        if (Container != EA)
        {
            Container.clear();
            Container.insert(Container.end(), EA.begin(), EA.end());
        }
        return *this;
    }

    ExtendedArray::operator std::vector<double>() const
    {
        return std::vector<double>(Container.begin(), Container.end());
    }

    bool ExtendedArray::operator == (const ExtendedArray& EA) const			//Should this be friend?
    {
        return (Container == EA.Container);
    }

    bool ExtendedArray::operator != (const ExtendedArray& EA) const
    {
        return !(Container == EA.Container);
    }

    ExtendedArray& ExtendedArray::operator += (const double& D)
    {
        Container.emplace_back(D);
        return *this;
    }

    ExtendedArray& ExtendedArray::operator += (const ExtendedArray& EA)
    {
        if (!EA.Empty())
        {
            Container.insert(Container.end(), EA.Container.begin(), EA.Container.end());
        }
        return *this;
    }

    ExtendedArray& ExtendedArray::operator -= (const double& D)
    {
        this->Delete(D, true);
        return *this;
    }

    ExtendedArray& ExtendedArray::operator -= (const ExtendedArray& EA)
    {
        this->Delete(EA);
        return *this;
    }

    ExtendedArray& ExtendedArray::operator = (const ExtendedArray& EA)
    {
        if (this != &EA)
        {
            Container.insert(Container.end(), EA.Container.begin(), EA.Container.end());
        }
        return *this;
    }

    ExtendedArray& ExtendedArray::operator << (const double& D)
    {
        Container.emplace_back(D);
        return *this;
    }

    ExtendedArray& ExtendedArray::operator << (const ExtendedArray& EA)
    {
        Container.insert(Container.end(), EA.Container.begin(), EA.Container.end());
        return *this;
    }

    void ExtendedArray::SetLength(std::size_t NewLength, double D)
    {
        this->Container.resize(NewLength, D);
    }

    bool ExtendedArray::Contains(double ExtendedToFind)
    {
        return std::find(Container.begin(), Container.end(), ExtendedToFind) != Container.end();
    }

    ExtendedArray& ExtendedArray::Append(const ExtendedArray& EA)
    {
        Container.insert(Container.end(), EA.Container.begin(), EA.Container.end());
        return *this;
    }

    ExtendedArray& ExtendedArray::Delete(std::uint32_t Position)
    {
        if (!Container.empty() && (Container.size() >= Position))
            this->Container.erase(Container.begin() + Position);

        return *this;
    }

    ExtendedArray& ExtendedArray::Delete(const double& ExtendedToDelete, bool All)
    {
        if (All)
        {
            Container.erase(std::remove(Container.begin(), Container.end(), ExtendedToDelete), Container.end());
        }
        else
        {
            auto it = std::find(Container.begin(), Container.end(), ExtendedToDelete);
            if (it != Container.end())
            {
                Container.erase(it);
            }
        }
        return *this;
    }

    ExtendedArray& ExtendedArray::Delete(const ExtendedArray& EA)
    {
        for (auto it = EA.Container.begin(); it != EA.Container.end(); ++it)
        {
            this->Delete(*it, true);
        }
        return *this;
    }

    tostream& operator << (tostream& Str, const ExtendedArray& EA)   //For use with Writeln&  cout.
    {
        if (!EA.Container.empty())
        {
            Str << _T("[");
            for (auto it = EA.Container.begin(); it != EA.Container.end() - 1; ++it)
            {
                Str << *it << _T(", ");
            }
            Str << EA.Container.back() << _T("]");
        }
        else
        {
            Str << _T("[]");
        }
        return Str;
    }

    ExtendedArray ExtendedArray::operator + (const double& D)
    {
        return (ExtendedArray(*this) += D);
    }

    ExtendedArray ExtendedArray::operator + (const ExtendedArray& EA)
    {
        return (ExtendedArray(*this) += EA);
    }

    ExtendedArray ExtendedArray::operator - (const double& D)
    {
        return (ExtendedArray(*this) -= D);
    }

    ExtendedArray ExtendedArray::operator - (const ExtendedArray& EA)
    {
        return (ExtendedArray(*this) -= EA);
    }


    /**
     * 												DECLARATION FOR EXTENDED2DARRAYS
     *
     *
    **/

    Extended2DArray::Extended2DArray() : Container() {}

    Extended2DArray::~Extended2DArray() {}

    std::size_t Extended2DArray::Size() const
    {
        return Container.size();
    }

    std::size_t Extended2DArray::Size(int I) const
    {
        assert(I >= 0 && !Container.empty());
        return Container[I].Size();
    }

    bool Extended2DArray::Empty() const
    {
        return Container.empty();
    }

    Extended2DArray& Extended2DArray::Clear()
    {
        Container.clear();
        return *this;
    }

    ExtendedArray& Extended2DArray::operator [](int I)
    {
        assert(I >= 0 && !Container.empty());
        return Container[I];
    }

    const ExtendedArray& Extended2DArray::operator [](int I) const
    {
        assert(I >= 0 && !Container.empty());
        return Container[I];
    }

    Extended2DArray::operator const std::vector<ExtendedArray>& () const
    {
        return Container;
    }

    Extended2DArray::operator const Extended2DArray& () const
    {
        return *this;
    }

    Extended2DArray& Extended2DArray::operator ()(std::vector<ExtendedArray> E2D)
    {
        if (Container != E2D)
        {
            Container.clear();
            Container.insert(Container.end(), E2D.begin(), E2D.end());
        }
        return *this;
    }

    Extended2DArray::operator std::vector<ExtendedArray>() const
    {
        return std::vector<ExtendedArray>(Container.begin(), Container.end());
    }

    bool Extended2DArray::operator == (const Extended2DArray& I) const			//Should this be friend?
    {
        return (Container == I.Container);
    }

    bool Extended2DArray::operator != (const Extended2DArray& I) const
    {
        return !(Container == I.Container);
    }

    Extended2DArray& Extended2DArray::operator += (const ExtendedArray& EA)
    {
        Container.emplace_back(EA);
        return *this;
    }

    Extended2DArray& Extended2DArray::operator += (const Extended2DArray& E2D)
    {
        Container.insert(Container.end(), E2D.Container.begin(), E2D.Container.end());
        return *this;
    }

    Extended2DArray& Extended2DArray::operator -= (const ExtendedArray& EA)
    {
        this->Delete(EA, true);
        return *this;
    }

    Extended2DArray& Extended2DArray::operator -= (const Extended2DArray& E2D)
    {
        this->Delete(E2D);
        return *this;
    }

    Extended2DArray& Extended2DArray::operator = (const Extended2DArray& E2D)
    {
        if (this != &E2D)
        {
            Container.clear();
            Container.insert(Container.end(), E2D.Container.begin(), E2D.Container.end());
        }
        return *this;
    }

    Extended2DArray& Extended2DArray::operator << (const ExtendedArray& EA)
    {
        Container.emplace_back(EA);
        return *this;
    }

    Extended2DArray& Extended2DArray::operator << (const Extended2DArray& E2D)
    {
        Container.insert(Container.end(), E2D.Container.begin(), E2D.Container.end());
        return *this;
    }

    void Extended2DArray::SetLength(std::size_t NewLength, std::size_t Inner, double D)
    {
        ExtendedArray Container;
        Container.SetLength(Inner, D);
        this->Container.resize(NewLength, Container);
    }

    void Extended2DArray::SetLength(std::size_t NewLength, ExtendedArray EA)
    {
        this->Container.resize(NewLength, EA);
    }

    bool Extended2DArray::Contains(const ExtendedArray& EA)
    {
        return std::find(Container.begin(), Container.end(), EA) != Container.end();
    }

    Extended2DArray& Extended2DArray::Append(const Extended2DArray& E2D)
    {
        Container.insert(Container.end(), E2D.Container.begin(), E2D.Container.end());
        return *this;
    }

    Extended2DArray& Extended2DArray::Delete(std::uint32_t Position)
    {
        if(!Container.empty() && (Container.size() >= Position))
            this->Container.erase(Container.begin() + Position);

        return *this;
    }

    Extended2DArray& Extended2DArray::Delete(const ExtendedArray& EA, bool All)
    {
        if (All)
        {
            Container.erase(std::remove(Container.begin(), Container.end(), EA), Container.end());
        }
        else
        {
            auto it = std::find(Container.begin(), Container.end(), EA);
            if (it != Container.end())
            {
                Container.erase(it);
            }
        }
        return *this;
    }

    Extended2DArray& Extended2DArray::Delete(const Extended2DArray& E2D)
    {
        for (auto it = E2D.Container.begin(); it != E2D.Container.end(); ++it)
        {
            this->Delete(*it, true);
        }
        return *this;
    }

    tostream& operator << (tostream& Str, const Extended2DArray& E2D)   //For use with Writeln&  cout.
    {
        if (!E2D.Container.empty())
        {
            Str << _T("[");
            for (auto it = E2D.Container.begin(); it != E2D.Container.end() - 1; ++it)
            {
                Str << *it << _T(", ");
            }
            Str << E2D.Container.back() << _T("]");
        }
        else
        {
            Str << _T("[]");
        }
        return Str;
    }

    Extended2DArray Extended2DArray::operator + (const ExtendedArray& EA)
    {
        return (Extended2DArray(*this) += EA);
    }

    Extended2DArray Extended2DArray::operator + (const Extended2DArray& E2D)
    {
        return (Extended2DArray(*this) += E2D);
    }

    Extended2DArray Extended2DArray::operator - (const ExtendedArray& EA)
    {
        return (Extended2DArray(*this) -= EA);
    }

    Extended2DArray Extended2DArray::operator - (const Extended2DArray& E2D)
    {
        return (Extended2DArray(*this) -= E2D);
    }


    /**
     * 												DECLARATION FOR STRINGARRAYS
     *
     *
    **/

    StringArray::StringArray() : Container(0) {}

    StringArray::~StringArray() {}

    std::size_t StringArray::Size() const
    {
        return Container.size();
    }

    bool StringArray::Empty() const
    {
        return Container.empty();
    }

    StringArray& StringArray::Clear()
    {
        Container.clear();
        return *this;
    }

    tstring& StringArray::operator [](int I)
    {
        assert(I >= 0 && !Container.empty());
        return Container[I];
    }

    const tstring& StringArray::operator [](int I) const
    {
        assert(I >= 0 && !Container.empty());
        return Container[I];
    }

    StringArray::operator const std::vector<tstring>& () const
    {
        return Container;
    }

    StringArray::operator const StringArray& () const
    {
        return *this;
    }

    StringArray& StringArray::operator ()(std::vector<tstring> SA)
    {
        if (Container != SA)
        {
            Container.clear();
            Container.insert(Container.end(), SA.begin(), SA.end());
        }
        return *this;
    }

    StringArray::operator std::vector<tstring>() const
    {
        return std::vector<tstring>(Container.begin(), Container.end());
    }

    bool StringArray::operator == (const StringArray& SA) const			//Should this be friend?
    {
        return (Container == SA.Container);
    }

    bool StringArray::operator != (const StringArray& SA) const
    {
        return !(Container == SA.Container);
    }

    StringArray& StringArray::operator += (const tstring& S)
    {
        Container.emplace_back(S);
        return *this;
    }

    StringArray& StringArray::operator += (const StringArray& SA)
    {
        if (!SA.Empty())
        {
            Container.insert(Container.end(), SA.Container.begin(), SA.Container.end());
        }
        return *this;
    }

    StringArray& StringArray::operator -= (const tstring& S)
    {
        this->Delete(S, true, true);
        return *this;
    }

    StringArray& StringArray::operator -= (const StringArray& SA)
    {
        this->Delete(SA, true);
        return *this;
    }

    StringArray& StringArray::operator = (const StringArray& SA)
    {
        if (this != &SA)
        {
            Container.clear();
            Container.insert(Container.end(), SA.Container.begin(), SA.Container.end());
        }
        return *this;
    }

    StringArray& StringArray::operator << (const tstring& S)
    {
        Container.emplace_back(S);
        return *this;
    }

    StringArray& StringArray::operator << (const StringArray& SA)
    {
        Container.insert(Container.end(), SA.Container.begin(), SA.Container.end());
        return *this;
    }

    void StringArray::SetLength(std::size_t NewLength, tstring S)
    {
        this->Container.resize(NewLength, S);
    }

    StringArray& StringArray::RemoveSortDuplicates()
    {
        std::sort(Container.begin(), Container.end());
        Container.erase(std::unique(Container.begin(), Container.end()), Container.end());
        return *this;
    }

    bool StringArray::Contains(tstring StringToFind, bool CaseSensitive)
    {
        return Container.end() != (CaseSensitive ? std::find(Container.begin(), Container.end(), StringToFind) : std::find_if(Container.begin(), Container.end(), [&StringToFind](tstring & Value)
        {
            return ToLowerCase(Value) == ToLowerCase(StringToFind);
        }));
    }

    StringArray& StringArray::Append(const StringArray& SA)
    {
        Container.insert(Container.end(), SA.Container.begin(), SA.Container.end());
        return *this;
    }

    StringArray& StringArray::Delete(std::uint32_t Position)
    {
        if(!Container.empty() && (Container.size() >= Position))
            this->Container.erase(Container.begin() + Position);

        return *this;
    }

    StringArray& StringArray::Delete(tstring StringToDelete, bool CaseSensitive, bool All)
    {
        if (CaseSensitive)
        {
            if (All)
            {
                Container.erase(std::remove(Container.begin(), Container.end(), StringToDelete), Container.end());
            }
            else
            {
                auto it = std::find(Container.begin(), Container.end(), StringToDelete);
                if (it != Container.end())
                {
                    Container.erase(it);
                }
            }
        }
        else
        {
            if (All)
            {
                Container.erase(std::remove_if(Container.begin(), Container.end(), [&StringToDelete](tstring & Value)
                {
                    return ToLowerCase(Value) == ToLowerCase(StringToDelete);
                }), Container.end());
            }
            else
            {
                auto it = std::find_if(Container.begin(), Container.end(), [&StringToDelete](tstring & Value)
                {
                    return ToLowerCase(Value) == ToLowerCase(StringToDelete);
                });
                if (it != Container.end())
                {
                    Container.erase(it);
                }
            }
        }

        return *this;
    }

    StringArray& StringArray::Delete(const StringArray& SA, bool CaseSensitive)
    {
        for (auto it = SA.Container.begin(); it != SA.Container.end(); ++it)
        {
            this->Delete(*it, CaseSensitive, true);
        }
        return *this;
    }

    tostream& operator << (tostream& Str, const StringArray& SA)  //For use with Writeln&  cout.
    {
        if (!SA.Container.empty())
        {
            Str << _T("[");
            for (auto it = SA.Container.begin(); it != SA.Container.end() - 1; ++it)
            {
                Str << *it << _T(", ");
            }
            Str << SA.Container.back() << _T("]");
        }
        else
        {
            Str << _T("[]");
        }
        return Str;
    }

    StringArray StringArray::operator + (const tstring& S)
    {
        return (StringArray(*this) += S);
    }

    StringArray StringArray::operator + (const StringArray& SA)
    {
        return (StringArray(*this) += SA);
    }

    StringArray StringArray::operator - (const tstring& S)
    {
        return (StringArray(*this) -= S);
    }

    StringArray StringArray::operator - (const StringArray& SA)
    {
        return (StringArray(*this) -= SA);
    }



    /**
     * 												DECLARATION FOR STRING2DARRAYS
     *
     *
    **/

    String2DArray::String2DArray() : Container(0) {}

    String2DArray::~String2DArray() {}

    std::size_t String2DArray::Size() const
    {
        return Container.size();
    }

    std::size_t String2DArray::Size(int I) const
    {
        assert(I >= 0 && !Container.empty());
        return Container[I].Size();
    }

    bool String2DArray::Empty() const
    {
        return Container.empty();
    }

    String2DArray& String2DArray::Clear()
    {
        Container.clear();
        return *this;
    }

    StringArray& String2DArray::operator [](int I)
    {
        assert(I >= 0 && !Container.empty());
        return Container[I];
    }

    const StringArray& String2DArray::operator [](int I) const
    {
        assert(I >= 0 && !Container.empty());
        return Container[I];
    }

    String2DArray::operator const std::vector<StringArray>& () const
    {
        return Container;
    }

    String2DArray::operator const String2DArray& () const
    {
        return *this;
    }

    String2DArray& String2DArray::operator ()(std::vector<StringArray> S2D)
    {
        if (Container != S2D)
        {
            Container.clear();
            Container.insert(Container.end(), S2D.begin(), S2D.end());
        }
        return *this;
    }

    String2DArray::operator std::vector<StringArray>() const
    {
        return std::vector<StringArray>(Container.begin(), Container.end());
    }

    bool String2DArray::operator == (const String2DArray& S2D) const			//Should this be friend?
    {
        return (Container == S2D.Container);
    }

    bool String2DArray::operator != (const String2DArray& S2D) const
    {
        return !(Container == S2D.Container);
    }

    String2DArray& String2DArray::operator += (const StringArray& SA)
    {
        Container.emplace_back(SA);
        return *this;
    }

    String2DArray& String2DArray::operator += (const String2DArray& S2D)
    {
        Container.insert(Container.end(), S2D.Container.begin(), S2D.Container.end());
        return *this;
    }

    String2DArray& String2DArray::operator -= (const StringArray& SA)
    {
        this->Delete(SA, true, true);
        return *this;
    }

    String2DArray& String2DArray::operator -= (const String2DArray& S2D)
    {
        this->Delete(S2D, true);
        return *this;
    }

    String2DArray& String2DArray::operator = (const String2DArray& S2D)
    {
        if (this != &S2D)
        {
            Container.clear();
            Container.insert(Container.end(), S2D.Container.begin(), S2D.Container.end());
        }
        return *this;
    }

    String2DArray& String2DArray::operator << (const StringArray& SA)
    {
        Container.emplace_back(SA);
        return *this;
    }

    String2DArray& String2DArray::operator << (const String2DArray& S2D)
    {
        Container.insert(Container.end(), S2D.Container.begin(), S2D.Container.end());
        return *this;
    }

    void String2DArray::SetLength(std::size_t NewLength, std::size_t InnerLength, tstring S)
    {
        StringArray SA;
        SA.SetLength(InnerLength, S);
        this->Container.resize(NewLength, SA);
    }

    void String2DArray::SetLength(std::size_t NewLength, StringArray SA)
    {
        this->Container.resize(NewLength, SA);
    }

    bool String2DArray::Contains(StringArray SA, bool CaseSensitive)
    {
        if (!CaseSensitive)
        {
            return Container.end() != std::find_if(Container.begin(), Container.end(), [&SA](StringArray & Value)
            {
                for (std::size_t I = 0, J = 0; I < Value.Size() && J < SA.Size(); ++I, ++J)
                {
                    if (ToLowerCase(Value[I]) != ToLowerCase(SA[J]))
                    {
                        return false;
                    }
                }
                return true;
            });
        }

        return std::find(Container.begin(), Container.end(), SA) != Container.end();
    }

    String2DArray& String2DArray::Append(const String2DArray& S2D)
    {
        Container.insert(Container.end(), S2D.Container.begin(), S2D.Container.end());
        return *this;
    }

    String2DArray& String2DArray::Delete(std::uint32_t Position)
    {
        if (!Container.empty() && (Container.size() >= Position))
            this->Container.erase(Container.begin() + Position);
        return *this;
    }

    String2DArray& String2DArray::Delete(StringArray SA, bool CaseSensitive, bool All)
    {
        String2DArray Temp;
        if (!CaseSensitive)
        {
            Temp.Container = Container;
            for (std::size_t I = 0; I < SA.Size(); ++I)
                SA[I] = ToLowerCase(SA[I]);

            for (std::size_t I = 0; I < Container.size(); ++I)
                for (std::size_t J = 0; J < Container[I].Size(); ++J)
                    Temp[I][J] = ToLowerCase(Temp[I][J]);
        }

        std::size_t J = 0;
        bool Deleted = false;
        for (std::size_t I = 0; I < Container.size(); ++I)
        {
            if (CaseSensitive ? (Container[I] != SA) : (Temp[I] != SA))
            {
                Container[J++] = Container[I];
            }
            else
            {
                if (Deleted && !All)
                    Container[J++] = Container[I];
                Deleted = true;
            }
        }
        Container.erase(Container.begin() + J, Container.end());
        return *this;
    }

    String2DArray& String2DArray::Delete(String2DArray S2D, bool CaseSensitive)
    {
        for (std::size_t I = 0; I < S2D.Size(); ++I)
        {
            this->Delete(S2D[I], CaseSensitive, true);
        }
        return *this;
    }

    tostream& operator << (tostream& Str, const String2DArray& S2D)  //For use with Writeln&  cout.
    {
        if (!S2D.Container.empty())
        {
            Str << _T("[");
            for (std::size_t I = 0; I < S2D.Container.size() - 1; ++I)
            {
                Str << S2D.Container[I] << _T(", ");
            }
            Str << S2D.Container[S2D.Container.size() - 1] << _T("]");
        }
        else
        {
            Str << _T("[]");
        }
        return Str;
    }

    String2DArray String2DArray::operator + (const StringArray& SA)
    {
        return (String2DArray(*this) += SA);
    }

    String2DArray String2DArray::operator + (const String2DArray& S2D)
    {
        return (String2DArray(*this) += S2D);
    }

    String2DArray String2DArray::operator - (const StringArray& SA)
    {
        return (String2DArray(*this) -= SA);
    }

    String2DArray String2DArray::operator - (const String2DArray& S2D)
    {
        return (String2DArray(*this) -= S2D);
    }


    /**
     * 												DECLARATION FOR CHARARRAYS
     *
     *
    **/

    CharArray::CharArray() : Container(0) {}

    CharArray::~CharArray() {}

    std::size_t CharArray::Size() const
    {
        return Container.size();
    }

    bool CharArray::Empty() const
    {
        return Container.empty();
    }

    CharArray& CharArray::Clear()
    {
        Container.clear();
        return *this;
    }

    TCHAR& CharArray::operator [](int I)
    {
        assert(I >= 0 && !Container.empty());
        return Container[I];
    }

    const TCHAR& CharArray::operator [](int I) const
    {
        assert(I >= 0 && !Container.empty());
        return Container[I];
    }

    CharArray::operator const std::vector<TCHAR>& () const
    {
        return Container;
    }

    CharArray::operator const CharArray& () const
    {
        return *this;
    }

    CharArray& CharArray::operator ()(std::vector<TCHAR> CA)
    {
        if (Container != CA)
        {
            if (!Container.empty())
                Container.clear();

            for (std::size_t I = 0; I < CA.size(); ++I)
                Container.emplace_back(CA[I]);
        }
        return *this;
    }

    CharArray::operator std::vector<TCHAR>() const
    {
        return std::vector<TCHAR>(Container.begin(), Container.end());
    }

    bool CharArray::operator == (const CharArray& CA) const			//Should this be friend?
    {
        return (Container == CA.Container);
    }

    bool CharArray::operator != (const CharArray& CA) const
    {
        return !(Container == CA.Container);
    }

    CharArray& CharArray::operator += (const TCHAR& C)
    {
        Container.emplace_back(C);
        return *this;
    }

    CharArray& CharArray::operator += (const CharArray& CA)
    {
        if (!CA.Empty())
        {
            for (std::size_t I = 0; I < CA.Size(); ++I)
            {
                Container.emplace_back(CA[I]);
            }
        }
        return *this;
    }

    CharArray& CharArray::operator -= (const TCHAR& C)
    {
        this->Delete(C, true, true);
        return *this;
    }

    CharArray& CharArray::operator -= (const CharArray& CA)
    {
        this->Delete(CA, true);
        return *this;
    }

    CharArray& CharArray::operator = (const CharArray& CA)
    {
        if (this != &CA)
        {
            if (!Container.empty())
                Container.clear();

            for (std::size_t I = 0; I < CA.Container.size(); ++I)
                Container.emplace_back(CA.Container[I]);
        }
        return *this;
    }

    CharArray& CharArray::operator << (const TCHAR& C)
    {
        Container.emplace_back(C);
        return *this;
    }

    CharArray& CharArray::operator << (const CharArray& CA)
    {
        for (std::size_t I = 0; I < CA.Size(); ++I)
            Container.emplace_back(CA[I]);

        return *this;
    }

    void CharArray::SetLength(std::size_t NewLength)
    {
        this->Container.resize(NewLength);
    }

    bool CharArray::Contains(TCHAR CharToFind, bool CaseSensitive)
    {
        for (std::size_t I = 0, J = 0; I < Container.size(); ++I)
        {
            if (CaseSensitive ? (Container[I] != CharToFind) : (_totlower(Container[I]) != _totlower(CharToFind)))
                Container[J++] = Container[I];
            else
                return true;
        }
        return false;
    }

    CharArray& CharArray::Append(const CharArray& CA)
    {
        for (std::size_t I = 0; I < CA.Size(); ++I)
        {
            this->Container.emplace_back(CA[I]);
        }
        return *this;
    }

    CharArray& CharArray::Delete(std::uint32_t Position)
    {
        if (!Container.empty() && (Container.size() >= Position))
            this->Container.erase(Container.begin() + Position);
        return *this;
    }

    CharArray& CharArray::Delete(TCHAR CharToDelete, bool CaseSensitive, bool All)
    {
        std::size_t J = 0;
        bool Deleted = false;
        for (std::size_t I = 0; I < Container.size(); ++I)
        {
            if (CaseSensitive ? (Container[I] != CharToDelete) : (ToLower(Container[I]) != ToLower(CharToDelete)))
            {
                Container[J++] = Container[I];
            }
            else
            {
                if (Deleted && !All)
                    Container[J++] = Container[I];
                Deleted = true;
            }
        }
        Container.erase(Container.begin() + J, Container.end());

        return *this;
    }

    CharArray& CharArray::Delete(const CharArray& CA, bool CaseSensitive)
    {
        for (std::size_t I = 0; I < CA.Size(); ++I)
        {
            this->Delete(CA[I], CaseSensitive, true);
        }
        return *this;
    }

    tostream& operator << (tostream& Str, const CharArray& CA) //For use with Writeln&  cout.
    {
        if (!CA.Container.empty())
        {
            Str << _T("[");
            for (std::size_t I = 0; I < CA.Container.size() - 1; ++I)
            {
                Str << CA.Container[I] << _T(", ");
            }
            Str << CA.Container[CA.Container.size() - 1] << _T("]");
        }
        else
        {
            Str << _T("[]");
        }
        return Str;
    }

    CharArray CharArray::operator + (const TCHAR& C)
    {
        return (CharArray(*this) += C);
    }

    CharArray CharArray::operator + (const CharArray& CA)
    {
        return (CharArray(*this) += CA);
    }

    CharArray CharArray::operator - (const TCHAR& C)
    {
        return (CharArray(*this) -= C);
    }

    CharArray CharArray::operator - (const CharArray& CA)
    {
        return (CharArray(*this) -= CA);
    }



    /**
     * 												DECLARATION FOR REPLACEMENTFLAGS
     *
     *
    **/

    ReplacementFlags::ReplacementFlags(bool ReplaceAll, bool IgnoreCase) : rfReplaceAll(ReplaceAll), rfIgnoreCase(IgnoreCase) {}

    ReplacementFlags::~ReplacementFlags() {}

    ReplacementFlags& ReplacementFlags::operator ()(bool ReplaceAll, bool IgnoreCase)
    {
        if((rfReplaceAll != ReplaceAll) && (rfIgnoreCase != IgnoreCase))
        {
            rfReplaceAll = ReplaceAll;
            rfIgnoreCase = IgnoreCase;
        }
        return *this;
    }

    bool ReplacementFlags::operator == (const ReplacementFlags& RF) const
    {
        return ((rfReplaceAll == RF.rfReplaceAll) && (rfIgnoreCase == RF.rfIgnoreCase));
    }

    bool ReplacementFlags::operator != (const ReplacementFlags& RF) const
    {
        return !((rfReplaceAll == RF.rfReplaceAll) && (rfIgnoreCase == RF.rfIgnoreCase));
    }
}
