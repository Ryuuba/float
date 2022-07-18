#include <iomanip>
#include <limits>
#include <utility>
#include "float32.h"

IEEE754_32::IEEE754_32() : f(0), k(Kind::Normalized) {}

IEEE754_32::IEEE754_32(float fpn) 
        : f(fpn)
{
    set_kind();
}

IEEE754_32::IEEE754_32(uint32_t sign, uint32_t exp, uint32_t mantissa)
    : f(0)
    , k(Kind::Undefined)
{
    f.field.sign = sign & 0x00000001;
    f.field.exp = exp & 0x000000FF;
    f.field.mant = mantissa & 0x007FFFFF;
    set_kind();
}

void IEEE754_32::set_kind()
{
    if (f.field.exp == 255)
    {
        if (f.field.mant == 0)
            k = Kind::Inf;
        else
            k = Kind::Nan;
    }
    else if (f.field.exp == 0)
        k = Kind::Denormalized;
    else
        k = Kind::Normalized;
}

char IEEE754_32::get_sign() {
    return f.field.sign == 0 ? '+' : '-'; 
}

int IEEE754_32::get_exponent() {
    return k == Kind::Inf || k == Kind::Inf ? 255 : f.field.exp - 127;
}

float IEEE754_32::get_mantissa() {
    Float mantissa(f.number);
    mantissa.code = mantissa.code & 0x007FFFFF;
    return mantissa.number;
}

char IEEE754_32::get_sign() const{
    return f.field.sign == 0 ? '+' : '-'; 
}

int IEEE754_32::get_exponent() const
{
    return k == Kind::Inf || k == Kind::Inf ? 255 : f.field.exp - 127;
}

float IEEE754_32::get_mantissa() const
{
    Float mantissa(f.number);
    mantissa.code &= 0x007FFFFF;
    mantissa.field.exp = 0x7F;
    return mantissa.number;
}

float IEEE754_32::get()
{
    return f.number;
}

std::bitset<32> IEEE754_32::get_bin_code()
{
    return std::bitset<32>(f.code);
}

void IEEE754_32::set(uint32_t sign, uint32_t exp, uint32_t mantissa)
{
    f.field.sign = sign & 0x00000001;
    f.field.exp = exp & 0x000000FF;
    f.field.mant = mantissa & 0x007FFFFF;
    set_kind();
}

std::string IEEE754_32::str_repr()
{
    std::string str(get_bin_code().to_string());
    str.insert(1, 1, ' ');
    str.insert(10, 1, ' ');
    return str;
}

std::ostream& operator<<(std::ostream& os, const IEEE754_32& fpn) {
    using std::flush;
    if
    (
            fpn.k == IEEE754_32::Kind::Normalized || 
            fpn.k == IEEE754_32::Kind::Denormalized
    )
    {
        os << std::setprecision(std::numeric_limits<long double>::digits10 + 1)
           << fpn.get_sign()
           << '(' << fpn.get_mantissa() << ')'
           << "2^(" << fpn.get_exponent() << ')'
           << flush;
    }
    else if (fpn.k == IEEE754_32::Kind::Inf)
        os << fpn.get_sign() << "inf";
    else
        os << fpn.get_sign() << "nan";
    return os;
}

bool IEEE754_32::operator==(const IEEE754_32& rhs)
{
    return this->f.code == rhs.f.code;
}

bool IEEE754_32::operator==(const IEEE754_32& rhs) const
{
    return this->f.code == rhs.f.code;
}

IEEE754_32 IEEE754_32::operator+(const IEEE754_32& rhs)
{
    return this->f.number + rhs.f.number;
}

IEEE754_32 IEEE754_32::operator+(const IEEE754_32& rhs) const
{
    return this->f.number + rhs.f.number;
}

IEEE754_32 IEEE754_32::operator-(const IEEE754_32& rhs)
{
    return this->f.number - rhs.f.number;
}

IEEE754_32 IEEE754_32::operator-(const IEEE754_32& rhs) const
{
    return this->f.number - rhs.f.number;
}

IEEE754_32 IEEE754_32::operator*(const IEEE754_32& rhs)
{
    return this->f.number * rhs.f.number;
}

IEEE754_32 IEEE754_32::operator*(const IEEE754_32& rhs) const
{
    return this->f.number * rhs.f.number;
}

IEEE754_32 IEEE754_32::operator/(const IEEE754_32& rhs)
{
    return this->f.number / rhs.f.number;
}

IEEE754_32 IEEE754_32::operator/(const IEEE754_32& rhs) const
{
    return this->f.number / rhs.f.number;
}