#ifndef BRUCH_H
#define BRUCH_H

class Bruch{
public:
    Bruch(int zaehler = 0, unsigned int nenner = 1);
    Bruch(double wert);

    int zaehler()const{ return zaehler_; }
    unsigned int nenner()const { return nenner_; }

    Bruch& operator+=(Bruch const& lvalue);
    Bruch& operator-=(Bruch const& lvalue);
    Bruch& operator*=(Bruch const& lvalue);
    Bruch& operator/=(Bruch const& lvalue);

    operator float() {return static_cast<float>(zaehler_)/nenner_;}
    operator double() {return static_cast<double>(zaehler_)/nenner_;}
    operator long double() {return static_cast<long double>(zaehler_)/nenner_;}

private:
    void kuerzen();

    int zaehler_;
    unsigned int nenner_;
};

inline Bruch const operator+(Bruch lhs, Bruch const &rhs){ return lhs += rhs; }
inline Bruch const operator-(Bruch lhs, Bruch const &rhs){ return lhs -= rhs; }
inline Bruch const operator*(Bruch lhs, Bruch const &rhs){ return lhs *= rhs; }
inline Bruch const operator/(Bruch lhs, Bruch const &rhs){ return lhs /= rhs; }

#endif // BRUCH_H
