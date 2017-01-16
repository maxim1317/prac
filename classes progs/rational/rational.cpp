#include "rational.h"

Rational::Rational(){}
Rational::Rational(const int32_t num) : num_(num){};
Rational::Rational(const int32_t num, const int32_t denum){
    if (denum == 0){
        throw "Can't devide by zero";
    }
    num_ = num;
    denum_ = denum;
    normalize();
}
bool Rational::operator== (const Rational s) const{
    return (num_ == s.num_ && denum_ == s.denum_);
}
bool Rational::operator!= (const Rational s) const{
    return (!operator==(s));
}
Rational Rational::operator+ (const Rational s) const{
    return Rational ((num_ * s.denum_ + denum_ * s.num_), denum_ * s.denum_);
}
Rational Rational::operator- (const Rational s) const{
    return Rational ((num_ * s.denum_ - denum_ * s.num_), denum_ * s.denum_);
}
Rational Rational::operator* (const Rational s) const{
    return Rational (num_ * s.num_, denum_ * s.denum_);
}
Rational Rational::operator/ (const Rational s) const {
    return Rational (num_ * s.denum_, denum_ * s.num_);
}
Rational& Rational::operator= (const Rational& s) = default;

double Rational::toDouble() const {
    double n = num_;
    double dn = denum_;
    return n / dn;
}

std::string Rational::toString() const {
    std::string str = "";
    str = std::to_string(num_);
    str += "/";
    str += std::to_string(denum_);
    return str;
}

void Rational::normalize(){
    int nod_ = nod(num_, denum_);
    if (num_ / nod_ == denum_ / nod_) {
        num_ = num_ / nod_;
        denum_ = 1;
    } else {
        num_ = num_ / nod_;
        denum_ = denum_ / nod_;
    }
}

std::ostream& Rational::writeTo(std::ostream& os) const {
    os << num_ << "/" << denum_;
    return os;
}
