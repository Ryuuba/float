#if !defined(FLOAT32_H)
#define FLOAT32_H

#include <cstdint>
#include <iostream>
#include <bitset>
#include <string>

/** @brief This class provides utilities to get binary data from
 *  float number */
class IEEE754_32 {
private:
    /** @brief This union allows to reinterpret the binary code of an IEEE754 
     * single precision floating-point number o an 32-bit unsigned integer
     * */
    union Float
    {
        float number;
        uint32_t code;
        struct Field
        {
            uint32_t mant : 23;
            uint32_t exp  : 8;
            uint32_t sign : 1;
        } field;
        Float() : code(0) {}
        Float(float fpn) : number(fpn) {}
    } f;
    /** @brief Kinds of IEEE 754 floating-point numbers */
    enum class Kind : uint8_t {
        Undefined,
        Normalized,
        Inf,
        Nan,
        Denormalized
    };
    Kind k;
    /** @brief Analizes the exponent of the number to set the kind of
     * this object
     * **/
    void set_kind();
    /** @briefs Returns the sign of a normalized number (+/-) */
    char get_sign() const;
    /** @brief Returns the decimal value of the exponent of a normalized 
     *  number
     * */
    int get_exponent() const;
    /** @brief Return the decimal value of the mantissa of a 
     * normalized number 
     * */
    float get_mantissa() const;
public:
    /** Default constructor */
    IEEE754_32();  
    /** @brief Construct an object from a float number */
    IEEE754_32(float);
    /** @brief Constructs this object from three fields: 
     * - sign, 
     * - exp, and 
     * - mantissa
     * @param sign The sign of the floting-point number [0, 1]
     * @param exp The exponent of the floating-point number [0, 255]
     * @param mant The mantissa of the floating-point number [0, 2^(23)-1]
     *  */
    IEEE754_32(uint32_t, uint32_t, uint32_t);
    /** @brief Move constructor */
    IEEE754_32(IEEE754_32&&) = default;
    /** @brief Return the floating-point number this object holds*/
    float get();
    /** @briefs Returns the sign of a normalized number (+/-) */
    char get_sign();
    /** @brief Returns the decimal value of the exponent of a normalized 
     *  number
     * */
    int get_exponent();
    /** @brief Returns the decimal value of the mantissa of a 
     * normalized number 
     * */
    float get_mantissa();
    /** @brief Returns the binary code of the floating-point number */
    std::bitset<32> get_bin_code();
    /** @brief Sets the fields of the floating-point number:
     * - sign, 
     * - exp, and 
     * - mantissa
     * @param sign The sign of the floting-point number [0, 1]
     * @param exp The exponent of the floating-point number [0, 255]
     * @param mant The mantissa of the floating-point number [0, 2^(23)-1]
     *  */
    void set(uint32_t, uint32_t, uint32_t);
    /** @brief Returns a string holding the binary 
     * representation of this object
     * */
    std::string str_repr();
    /** @brief Prints this object in a human-readable format: 
     * sign(mantissa)(2^exp)
     * */
    friend std::ostream& operator<<(std::ostream&, const IEEE754_32&);
    /** @brief Compares two objects of this kind */
    bool operator==(const IEEE754_32&);
    bool operator==(const IEEE754_32&) const;
    /** @brief Adds two objects of this kind */
    IEEE754_32 operator+(const IEEE754_32&);
    IEEE754_32 operator+(const IEEE754_32&) const;
    /** @brief Subtracts two objects of this kind */
    IEEE754_32 operator-(const IEEE754_32&);
    IEEE754_32 operator-(const IEEE754_32&) const;
    /** @brief Multiplies two objects of this kind */
    IEEE754_32 operator*(const IEEE754_32&);
    IEEE754_32 operator*(const IEEE754_32&) const;
    /** @brief Divides two objects of this kind */
    IEEE754_32 operator/(const IEEE754_32&);
    IEEE754_32 operator/(const IEEE754_32&) const;
};

#endif // FLOT32_H