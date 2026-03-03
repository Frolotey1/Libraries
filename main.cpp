#include <iostream>
#include <optional>
#include <charconv>
#include <algorithm>

template<typename Temp,
         typename = std::enable_if<std::is_arithmetic<Temp>::value>>
class Fraction {
    Temp numerator;
    Temp denominator;
public:
    explicit Fraction() :
        numerator(static_cast<Temp>(0)), denominator(static_cast<Temp>(0)) {}
    explicit Fraction(Temp _numerator, Temp _denominator) {
        if(!std::optional<Temp>(_numerator).has_value()
          && !std::optional<Temp>(_denominator).has_value())
            throw std::invalid_argument("Invalid arguments for variables");

        numerator = _numerator;
        denominator = _denominator;
    }

    Fraction(const Fraction& other) {
        this->numerator = other.numerator;
        this->denominator = other.denominator;
    }

    void operator+(const Fraction& add_other) {
        if(this->denominator * add_other.denominator == 0)
            throw std::runtime_error("Division by zero");

        std::cout <<
            ((this->numerator * add_other.denominator)
                      + (this->denominator * add_other.numerator))
                         / (this->denominator * add_other.denominator) << std::endl;
    }

    void operator-(const Fraction& sub_other) {
        if(this->denominator * sub_other.denominator == 0)
            throw std::runtime_error("Division by zero");

        std::cout <<
            ((this->numerator * sub_other.denominator)
             - (this->denominator * sub_other.numerator))
                / (this->denominator * sub_other.denominator) << std::endl;
    }

    void operator*(const Fraction& mul_other) {
        if(this->denominator * mul_other.denominator == 0)
            throw std::runtime_error("Division by zero");

        std::cout <<
            ((this->numerator * mul_other.numerator)
             / (this->denominator * mul_other.denominator)) << std::endl;
    }

    void operator/(const Fraction& div_other) {
        if(this->denominator * div_other.numerator == 0)
            throw std::runtime_error("Division by zero");

        std::cout <<
            (this->numerator * div_other.denominator) /
                         (this->denominator * div_other.numerator) << std::endl;
    }

    void set_new(Temp new_numerator, Temp new_denominator) {
        if(!std::optional<Temp>(new_numerator).has_value()
            && !std::optional<Temp>(new_denominator).has_value())
            throw std::invalid_argument("Invalid arguments for variables");
        this->numerator = new_numerator;
        this->denominator = new_denominator;
    }

    template<typename OtherTemp,
             typename = std::enable_if<std::is_arithmetic<OtherTemp>::value>>
    std::pair<OtherTemp,OtherTemp> convert_to() {
        if(std::is_same<OtherTemp,Temp>::value)
            throw std::invalid_argument("Template types are same");

        return{static_cast<OtherTemp>(numerator),
                static_cast<OtherTemp>(denominator)};
    }

    template<typename StringToArithmetic,
             typename = std::enable_if<std::is_arithmetic<StringToArithmetic>::value>>
    std::pair<StringToArithmetic,StringToArithmetic> stoa(std::string numerator, std::string denominator) {
        if(!std::optional<std::string>(numerator).has_value()
          && !std::optional<std::string>(denominator).has_value())
            throw std::invalid_argument("Invalid arguments for variables");

        std::for_each(numerator.begin(),numerator.end(),
                      [](auto& check){if(!std::isdigit(check,std::locale(""))) throw std::invalid_argument("Numerator is not digit");});

        std::for_each(denominator.begin(),denominator.end(),
                      [](auto& check){if(!std::isdigit(check,std::locale(""))) throw std::invalid_argument("Denominator is not digit");});

        StringToArithmetic for_numerator = static_cast<StringToArithmetic>(0);
        StringToArithmetic for_denominator = static_cast<StringToArithmetic>(0);

        auto [ptr,result_numerator] =
            std::from_chars(numerator.data(),numerator.data() + numerator.size(),for_numerator);
        auto [ptr2,result_denominator] =
            std::from_chars(denominator.data(),denominator.data() + denominator.size(),for_denominator);

        if(result_numerator == std::errc() && result_denominator == std::errc())
            return {for_numerator,for_denominator};

        return {static_cast<StringToArithmetic>(0),static_cast<StringToArithmetic>(0)};
    }

    friend std::ostream& operator<<(std::ostream& output, const Fraction& target) {
        output << target.get_numerator() << " " << target.get_denominator() << std::endl;
        return output;
    }

    friend std::istream& operator>>(std::istream& input, const Fraction& target) {
        input >> target.get_numerator() >> " " >> target.get_denominator();
        return input;
    }

    bool operator==(const Fraction& is_equal) {
        if(this->numerator == is_equal.numerator
            && this->denominator == is_equal.denominator)
            return true;
        return false;
    }

private:
    Temp get_numerator() const {return numerator;}
    Temp get_denominator() const {return denominator;}
};

int main() {
    Fraction<int> fraction{10,20};
    Fraction<int> fraction2 = fraction;

    if(fraction == fraction2) {

        std::cout << "Addition\n";
        fraction + fraction2;
        std::cout << "Substitution\n";
        fraction - fraction2;
        std::cout << "Multiplication\n";
        fraction * fraction2;
        std::cout << "Division:\n";
        fraction / fraction2;

    }

    std::cout << "First Fraction: " << fraction << "\nSecond Fraction: " << fraction2 << std::endl;

    fraction2.set_new(40,50);

    std::cout << "New values for second fraction: " << fraction2 << std::endl;

    auto pair = fraction.convert_to<double>();

    std::cout << "Numerator has " << pair.first << "\nDenominator: " << pair.second << std::endl;

    std::cout << "Numerator has " << typeid(pair.first).name() << "\nDenominator: " << typeid(pair.second).name() << std::endl;

    auto stoa = fraction.stoa<int>("500","500");

    std::cout << stoa.first << " " << stoa.second << std::endl;
    return 0;
}
