#ifndef NUMBERS_H
#define NUMBERS_H

#include <string>
#include <vector>

#include "errorhandling.h"

class big_uint{
private:
    std::vector<uint8_t> digits;
    //Each uint8_t represents a digit, which is slightly overkill
    //The front of the vector corresponds to the 1's digit, the second element to the 10's digit, and so on.

public:
    big_uint(){}

    big_uint(std::string val){
        for(unsigned long long i = val.size()-1; i < val.size(); i--){
            digits.push_back(static_cast<uint8_t>(val[i] - '0'));
        }
        removeLeadingZeros(digits);
    }

    big_uint(std::vector<uint8_t> digits){
        this->digits = digits;
    }

    big_uint(unsigned long long val){
        while(val > 0){
            digits.push_back(static_cast<uint8_t>(val%10));
            val/=10;
        }
    }

    static void removeLeadingZeros(std::vector<uint8_t>& digits){
        for(unsigned long long i = digits.size()-1; i < digits.size(); i--){
            if(digits[i]==uint8_t(0)) digits.pop_back();
            else return;
        }
    }

    static std::string toString(const std::vector<uint8_t>& digits){
        if(digits.size()==0) return "0";

        std::string str;
        str.resize(digits.size());

        for(unsigned long long i = 0; i < digits.size(); i++)
            str[digits.size()-1-i] = static_cast<char>(digits[i]) + '0';

        return str;
    }

    std::string toString() const{
        return toString(digits);
    }

    friend std::ostream& operator<<(std::ostream& os, const big_uint& biggy){
        os << biggy.toString();
        return os;
    }

    bool isZero() const{
        return digits.size()==0;
    }

    bool isOne() const{
        return digits.size()==1 && digits[0]==1;
    }

    bool isEven() const{
        return digits.size()==0 || digits[0]%2==0;
    }

    bool isOdd() const{
        return !isEven();
    }

    /* Determine if one unsigned integer is greater than another */
    static bool isGreater(const std::vector<uint8_t>& a, const std::vector<uint8_t>& b){
        if(a.size() > b.size()) return true;
        else if(a.size() < b.size()) return false;

        for(unsigned long long i = a.size()-1; i < a.size(); i--){
            if(a[i] > b[i]) return true;
            else if(a[i] < b[i]) return false;
        }

        return false;
    }

    /* Determine if one unsigned integer is equal to another */
    static bool isEqual(const std::vector<uint8_t>& a, const std::vector<uint8_t>& b){
        if(a.size() > b.size()) return false;
        else if(a.size() < b.size()) return false;

        for(unsigned long long i = a.size()-1; i < a.size(); i--){
            if(a[i] > b[i]) return false;
            else if(a[i] < b[i]) return false;
        }

        return true;
    }

    /* Add two unsigned big integers */
    static std::vector<uint8_t> add(const std::vector<uint8_t>& a, const std::vector<uint8_t>& b){
        if(a.size() < b.size())
            return add(b,a);

        std::vector<uint8_t> scratch;
        scratch.resize(a.size()+1);
        bool carry = false;
        for(unsigned long long i = 0; i < b.size(); i++){
            uint8_t added_digits = a[i] + b[i] + carry;
            if(added_digits < 10){
                scratch[i] = added_digits;
                carry = false;
            }else{
                scratch[i] = added_digits - 10;
                carry = true;
            }
        }

        for(unsigned long long i = b.size(); i < a.size(); i++){
            if(a[i]==9 && carry){
                scratch[i] = 0;
                carry = true;
            }else{
                scratch[i] = a[i] + carry;
                carry = false;
                break;
            }
        }
        if(carry) scratch[a.size()] = 1;
        else scratch.pop_back();

        removeLeadingZeros(scratch);

        return scratch;
    }

    /* Subtract an unsigned integer b from a, where a is greater than b. */
    static std::vector<uint8_t> sub(const std::vector<uint8_t>& a, const std::vector<uint8_t>& b){
        if(isGreater(b,a)) error("big_uint underflow due to subtraction.");

        std::vector<uint8_t> scratch;
        scratch.resize(a.size());

        bool carry = false;
        for(unsigned long long i = 0; i < b.size(); i++){
            uint8_t subtracted_digits = a[i] - b[i] - carry + 10;
            if(subtracted_digits < 10){
                scratch[i] = subtracted_digits;
                carry = true;
            }else{
                scratch[i] = subtracted_digits - 10;
                carry = false;
            }
        }


        for(unsigned long long i = b.size(); i < a.size(); i++){
            if(carry && a[i]==0){
                scratch[i] = 9;
            }else{
                scratch[i] = a[i] - carry;
                for(unsigned long long j = i+1; j < a.size(); j++) scratch[j] = a[j];
                break;
            }
        }
        removeLeadingZeros(scratch);

        return scratch;
    }

    /* Multiply two unsigned integers */
    static std::vector<uint8_t> mult(const std::vector<uint8_t>& a, const std::vector<uint8_t>& b){
        if(a.size() < b.size()) return mult(b,a);

        std::vector<uint8_t> scratch;
        scratch.resize(a.size()+b.size(), 0);

        for(unsigned long long i = 0; i < a.size(); i++){
            for(unsigned long long j = 0; j < b.size(); j++){
                uint8_t multiplied_digit = a[i]*b[j];
                uint8_t first_digit = multiplied_digit % 10;
                uint8_t second_digit = multiplied_digit / 10;
                bool carry_first = ((scratch[i+j] + first_digit) > 9);
                bool carry_second = ((scratch[i+j+1] + second_digit + carry_first) > 9);

                scratch[i+j] += first_digit;
                if(carry_first) scratch[i+j] -= 10;

                scratch[i+j+1] += second_digit + carry_first;
                if(carry_second){
                    scratch[i+j+1] -= 10;
                    unsigned long long k;
                    for(k = 2; scratch[i+j+k] == 9; k++){
                        scratch[i+j+k] = 0;
                    }
                    scratch[i+j+k]++;
                }
            }
        }
        removeLeadingZeros(scratch);

        return scratch;
    }

    bool operator>(const big_uint& other) const{
        return isGreater(digits, other.digits);
    }

    bool operator==(const big_uint& other) const{
        return isEqual(digits, other.digits);
    }

    bool operator!=(const big_uint& other) const{
        return !isEqual(digits, other.digits);
    }

    bool operator>=(const big_uint& other) const{
        return operator>(other) || operator==(other);
    }

    bool operator<(const big_uint& other) const{
        return other >= *this;
    }

    bool operator<=(const big_uint& other) const{
        return other > *this;
    }

    bool operator==(unsigned long long val) const{
        unsigned long long i = 0;
        while(val > 0){
            if(digits.size()==i || digits[i] != val%10) return false;
            val/=10;
            i++;
        }
        return i==digits.size();
    }

    bool operator!=(unsigned long long val) const{
        return !operator==(val);
    }

    big_uint operator+(const big_uint& other) const{
        return big_uint(add(digits,other.digits));
    }

    big_uint operator-(const big_uint& other) const{
        return big_uint(sub(digits, other.digits));
    }

    big_uint operator*(const big_uint& other) const{
        return big_uint(mult(digits,other.digits));
    }

    big_uint operator+=(const big_uint& other){
        *this = operator+(other);
        return *this;
    }

    big_uint operator-=(const big_uint& other){
        *this = operator-(other);
        return *this;
    }

    big_uint operator*=(const big_uint& other){
        *this = operator*(other);
        return *this;
    }

    big_uint operator++(){
        unsigned long long i;
        for(i = 0; i < digits.size() && digits[i]==9; i++)
            digits[i] = 0;
        if(i==digits.size()) digits.push_back(1);
        else digits[i]++;
        return *this;
    }

    big_uint operator--(){
        unsigned long long i;
        for(i = 0; digits[i]==0; i++)
            digits[i] = 9;
        digits[i]--;
        return *this;
    }

    big_uint operator++(int){
        big_uint pre_increment = *this;
        operator++();
        return pre_increment;
    }

    big_uint operator--(int){
        big_uint pre_decrement = *this;
        operator--();
        return pre_decrement;
    }

    big_uint e(unsigned long long power) const{
        std::vector<uint8_t> raised;
        for(unsigned long long i = 0; i < power; i++) raised.push_back(0);
        for(unsigned long long i = 0; i < digits.size(); i++) raised.push_back(digits[i]);

        return big_uint(raised);
    }

    static void longDivision(big_uint dividend, big_uint divisor, big_uint& quotient_out, big_uint& remainder_out){
        if(divisor > dividend){
            quotient_out = big_uint("0");
            remainder_out = dividend;
            return;
        }

        unsigned long long factor_difference = dividend.digits.size() - divisor.digits.size();
        quotient_out.digits.resize(factor_difference+1);

        for(unsigned long long i = factor_difference; i <= factor_difference; i--){
            quotient_out.digits[i] = 0;
            big_uint raised_divisor = divisor.e(i);
            while(dividend >= raised_divisor){
                dividend -= raised_divisor;
                quotient_out.digits[i]++;
            }
        }

        removeLeadingZeros(quotient_out.digits);
        removeLeadingZeros(dividend.digits);
        remainder_out = dividend;
    }

    big_uint operator/(const big_uint& other) const{
        big_uint quotient;
        big_uint remainder;
        longDivision(*this,other,quotient,remainder);
        if(remainder!=big_uint("0")) error("Integer division had remainder - use longDivision() where remainders may exist.");

        return quotient;
    }

    big_uint operator/=(const big_uint& other){
        return *this = *this / other;
    }

    big_uint operator%(const big_uint& other) const{
        big_uint quotient;
        big_uint remainder;
        longDivision(*this,other,quotient,remainder);

        return remainder;
    }
};

inline big_uint pow(const big_uint& a, const big_uint& b){
    if(b.isZero()){
        return 1;
    }else if(b.isEven()){
        big_uint remainder, half_b;
        big_uint::longDivision(b, 2, half_b, remainder);

        return pow(a*a,half_b);
    }else{
        big_uint remainder, half_b_minus_1;
        big_uint::longDivision(b-1, 2, half_b_minus_1, remainder);

        return a*pow(a*a, half_b_minus_1);
    }
}

inline big_uint greatestCommonDivisor(const big_uint& a, const big_uint& b){
    if(b.isZero())            return a;
    else if(a.isZero())       return b;
    else if(a==b)             return a;
    else if(a > b)            return greatestCommonDivisor(a-b,b);
    else                      return greatestCommonDivisor(a,b-a);

}


class rational{
public:
    big_uint numerator;
    big_uint denominator;
    bool is_negative;

public:
    rational(){
        is_negative = false;
    }

    rational(big_uint num, big_uint denom, bool is_negative){
        numerator = num;
        denominator = denom;
        this->is_negative = is_negative;
    }

    rational(unsigned long long num, unsigned long long denom, bool is_negative){
        numerator = num;
        denominator = denom;
        this->is_negative = is_negative;
    }

    rational(long long num){
        is_negative = (num < 0);
        numerator = static_cast<unsigned long long>(is_negative ? -num : num);
        denominator = 1;
    }

    rational reciprocal() const{
        return rational(denominator, numerator, is_negative);
    }

    std::string toString() const{
        std::string str = "";
        if(is_negative && !numerator.isZero()) str += "-";
        str += numerator.toString();
        if(!denominator.isOne() && !numerator.isZero()) str += " / " + denominator.toString();

        return str;
    }

    friend std::ostream& operator<<(std::ostream& os, const rational& r){
        os << r.toString();
        return os;
    }

    bool isZero() const{
        return numerator.isZero() && !denominator.isZero();
    }

    bool isOne() const{
        return numerator==denominator && !numerator.isZero() && !is_negative;
    }

    bool isIntegerNumber(){
        return denominator.isOne();
    }

    void simplify(){
        big_uint gcd = greatestCommonDivisor(numerator,denominator);
        numerator /= gcd;
        denominator /= gcd;
    }

    rational operator*(const rational& other) const{
        big_uint num_unsimplified = numerator*other.numerator;
        big_uint den_unsimplified = denominator*other.denominator;
        big_uint gcd = greatestCommonDivisor(num_unsimplified,den_unsimplified);
        return rational(num_unsimplified/gcd, den_unsimplified/gcd, is_negative != other.is_negative);
    }

    rational operator/(const rational& other) const{
        big_uint num_unsimplified = numerator*other.denominator;
        big_uint den_unsimplified = denominator*other.numerator;
        big_uint gcd = greatestCommonDivisor(num_unsimplified,den_unsimplified);
        return rational(num_unsimplified/gcd, den_unsimplified/gcd, is_negative != other.is_negative);
    }

    rational operator-() const{
        return rational(numerator,denominator,!is_negative);
    }

    rational operator+(const rational& other) const{
        big_uint gcd = greatestCommonDivisor(denominator, other.denominator);
        big_uint left_factor = other.denominator/gcd;
        big_uint right_factor = denominator/gcd;

        big_uint left_num_scaled = numerator*left_factor;
        big_uint right_num_scaled = other.numerator*right_factor;

        if(is_negative==other.is_negative){
            return rational(left_num_scaled + right_num_scaled, denominator*left_factor, is_negative);
        }else if(left_num_scaled > right_num_scaled){
            return rational(left_num_scaled - right_num_scaled, denominator*left_factor, is_negative);
        }else{
            return rational(right_num_scaled - left_num_scaled, denominator*left_factor, !is_negative);
        }
    }

    rational operator-(const rational& other) const{
        big_uint gcd = greatestCommonDivisor(denominator, other.denominator);
        big_uint left_factor = other.denominator/gcd;
        big_uint right_factor = denominator/gcd;

        big_uint left_num_scaled = numerator*left_factor;
        big_uint right_num_scaled = other.numerator*right_factor;

        if(is_negative!=other.is_negative){
            return rational(left_num_scaled + right_num_scaled, denominator*left_factor, is_negative);
        }else if(left_num_scaled > right_num_scaled){
            return rational(left_num_scaled - right_num_scaled, denominator*left_factor, is_negative);
        }else{
            return rational(right_num_scaled - left_num_scaled, denominator*left_factor, !is_negative);
        }
    }

    rational operator%(const rational& other) const{
        big_uint gcd = greatestCommonDivisor(denominator, other.denominator);
        big_uint left_factor = other.denominator/gcd;
        big_uint right_factor = denominator/gcd;

        big_uint left_num_scaled = numerator*left_factor;
        big_uint right_num_scaled = other.numerator*right_factor;

        return rational(left_num_scaled % right_num_scaled, denominator*left_factor, is_negative!=other.is_negative);
    }

    rational operator+=(const rational& other){
        *this = *this + other;
        return *this;
    }

    rational operator-=(const rational& other){
        *this = *this - other;
        return *this;
    }

    rational operator*=(const rational& other){
        *this = *this * other;
        return *this;
    }

    rational operator/=(const rational& other){
        *this = *this / other;
        return *this;
    }
};

#endif // NUMBERS_H
