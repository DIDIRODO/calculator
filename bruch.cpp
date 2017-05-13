#include "bruch.h"
#include <iostream>

unsigned int ggT(unsigned int a, unsigned int b){
    if(b == 0)
        return a;
    else return ggT(b, a % b);
}

unsigned int kgV(unsigned int a, unsigned int b){
    return (a * b) / ggT(a, b);
}

Bruch::Bruch(int zaehler, unsigned int nenner):
    zaehler_(zaehler), nenner_(nenner){
    kuerzen();
}

Bruch::Bruch(double wert):
    zaehler_(static_cast<int>(wert*1000000.0 + 0.5)), nenner_(1000000){
    kuerzen();
}

void Bruch::kuerzen(){
    unsigned int tmp(ggT(zaehler_, nenner_));
    zaehler_ /= tmp;
    nenner_ /= tmp;
}

Bruch& Bruch::operator+=(Bruch const &lvalue){
    const unsigned int tmp = kgV(nenner_, lvalue.nenner_);
    zaehler_ = zaehler_ * (tmp / nenner_) + lvalue.zaehler_ * (tmp / lvalue.nenner_);
    nenner_ = tmp;
    return *this;       // Referenz auf sich selbst
}

Bruch& Bruch::operator-=(Bruch const &lvalue){
    const unsigned int tmp = kgV(nenner_, lvalue.nenner_);
    zaehler_ = zaehler_ * (tmp / nenner_) - lvalue.zaehler_ * (tmp / lvalue.nenner_);
    nenner_ = tmp;
    return *this;       // Referenz auf sich selbst
}

Bruch& Bruch::operator*=(Bruch const &lvalue){
    zaehler_ *= lvalue.zaehler_;
    nenner_ *= lvalue.nenner_;
    kuerzen();
    return *this;       // Referenz auf sich selbst
}

Bruch& Bruch::operator/=(Bruch const &lvalue){
    zaehler_ *= lvalue.nenner_;
    nenner_ *= lvalue.zaehler_;
    kuerzen();
    return *this;       // Referenz auf sich selbst
}

std::ostream& operator<<(std::ostream &os, Bruch const &bruch){
    return os << '(' << bruch.zaehler() <<'/' << bruch.nenner() << ')';
}

std::istream& operator>>(std::istream &is, Bruch &bruch){
    char tmp;
    int zaehler;
    unsigned int nenner;
    is >> tmp;
    if(tmp == '('){
        is >> zaehler;
        is >> tmp;
        if(tmp == '/'){
            is >> nenner;
            is >> tmp;
            if(tmp == ')'){
                bruch = Bruch(zaehler, nenner);
                return is;
            }
        }
    }
    is.setstate(std::ios_base::failbit);
    return is;
}

int main() {
    Bruch zahl1, zahl2, ergebnis;
    char rechenzeichen;

    std::cout << "Geben Sie eine Rechenaufgabe ein: ";
    std::cin >>zahl1 >> rechenzeichen >> zahl2;

    switch(rechenzeichen){
        case '+': ergebnis = zahl1 + zahl2; break;
        case '-': ergebnis = zahl1 - zahl2; break;
        case '*': ergebnis = zahl1 * zahl2; break;
        case '/': ergebnis = zahl1 / zahl2; break;

        default: std::cout << "unbekanntes Rechenzeichen...\n"; return 1;
    }

    std::cout << zahl1 << ' ' << rechenzeichen << ' ' << zahl2 << " = " << ergebnis << '\n';
    std::cout << static_cast<double>(zahl1) << ' '
              << rechenzeichen << ' '
              << static_cast<double>(zahl2) << " = "
              << static_cast<double>(ergebnis) << '\n';
}
