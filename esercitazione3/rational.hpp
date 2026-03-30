#include <iostream>
#include <concepts> // serve per std::integral 
#include <cmath>  //necessario per abs

template<typename I> requires std::integral<I>
class rational
{
	I num_;
	I den_;
    
public:
    /* Costruttore di default */
    rational()
        : num_(I{0}), den_(I{1})
    {}
    
	/*Segno al numeratore */
	rational& segno_num() {
		if (den_<0) {			// se den negativo porto segno al numeratore
			den_ = -den_;
			num_ = -num_;
		}
		return *this;
	}
	
    /* Costruttore user-defined */
    rational(const I& px, const I& py) 
        : num_(px), den_(py) {
		segno_num();	//segno al numeratore
    }
    
    /* Restituiscono i valori di num e den */
	//faccio anche metodi per verificare inf e NaN
    I num() const {
		return num_;
		}
    I den() const {
		return den_;
		}
	bool is_inf() const {
		return den_ == 0 && num_ != 0; 	// x/0 -> inf
	}
	bool is_nan() const {
		return den_ == 0 && num_ == 0;	// 0/0 -> NaN
	}
	
    /* Implementazione canonica dell'incremento */
    rational& operator+=(const rational& other) {
		// eccezioni inf e NaN
		if (is_nan() || other.is_nan()) {
			num_ = 0;
			den_ = 0;
            return *this;  // Somma con NaN resta NaN
        }
        else if (is_inf() || other.is_inf()) {		//NaN+inf cade nel primo if -> NaN
			if (is_inf() && other.is_inf()) {		//inf+-inf
				if ((num_ > 0 && other.num() < 0) ||(num_ < 0 && other.num() > 0)) {	//+inf-inf -> NaN
					num_ = 0;
					den_ = 0;
				}
				// else inf concordi -> rimane uguale
				return *this;
			}
			if	(other.is_inf()){	// solo other inf
				num_ = other.num(); //prendo segno other
				den_ = 0;
				return *this;
			}
			return *this;  // Solo rational è inf
		}
        // Somma normale dei razionali
        num_ = num_ * other.den_ + other.num_ * den_;
		den_ *= other.den_;
		// faccio mcd(num,den) con algoritmo di euclide
		I a = std::abs(num_);		//uso abs perchè con numeri negativi algoritmo può rompersi
		I b = std::abs(den_);	
		while (b!=0) {
			I r = a%b;
			a = b;
			b = r;
		} // il mcd rimane in a
		// semplifico numeratore e denominatore
		num_ = num_/a;
		den_ = den_/a;
		//sistemo segno denominatore(potrebbe eseere negativo)
		segno_num();
		return *this;
    }
    
    /* Implementazione canonica della somma */
    rational operator+(const rational& other) const {
        rational ret = *this;
        ret += other;
        return ret;
    }
    
    /* Implementazione canonica del decremento */
	rational& operator-=(const rational& other) {
		rational neg = other;
		neg.num_ = -neg.num_;
		*this += neg;
		return *this;
	}
	
    /* Implementazione canonica della differenza */
    rational operator-(const rational& other) const {
        rational ret = *this;
        ret -= other;
        return ret;
    }	
	
    /* Implementazione canonica di *=  */
    rational& operator*=(const rational& other) {
        if (is_nan()||other.is_nan()){		// se uno dei due NaN -> prodotto NaN
			num_ = 0;
			den_ = 0;
			return *this;
		}
		if (is_inf()||other.is_inf()) {	//se uno dei due è inf -> prodotto inf
			if ((num_==0 && !is_inf()) || (other.num()==0 && !other.is_inf())){		// 0*inf -> NaN
				num_ = 0;
				den_ = 0;
				return *this;
			}
			den_ = 0;	//uno dei due è 0 -> den_=0
			int sign = 1;	// normalizzo segno per evitare possibili problemi
			if ((num_ < 0 && other.num() >= 0) ||(num_ >= 0 && other.num() < 0)) {
				sign = -1;
			}
			num_ = sign;
			return *this;
		}
		// caso base senza inf e NaN
		num_ *= other.num();
		den_ *= other.den();
		// faccio mcd(num,den) con algoritmo di euclide
		I a = std::abs(num_);		//uso abs perchè con numeri negativi algoritmo può rompersi
		I b = std::abs(den_);	
		while (b!=0) {
			I r = a%b;
			a = b;
			b = r;
		} // il mcd rimane in a
		// semplifico numeratore e denominatore
		num_ = num_/a;
		den_ = den_/a;
		segno_num();
        return *this;
    }
    
    /* Implementazione canonica del prodotto */
    rational operator*(const rational& other) const {
        rational ret = *this;
        ret *= other;
        return ret;
    }
	
	/* Implementazione canonica di /= */
	rational& operator/=(const rational& other) {
		// faccio inverso  other e moltiplico 
		// caso almeno uno NaN -> NaN
		if (is_nan() || other.is_nan()) {
			num_ = 0;
			den_ = 0;
			return *this;
		}
		// caso /= 0 (0/den) divisione per 0 -> divido per casi this
		if (other.num_ == 0 && other.den_ != 0) {
			if (num_ == 0) {	//0/0 -> NaN
				num_ = 0; 
				den_ = 0;
			}
			else {				// x/0 ->inf
				den_ = 0;           
			}
			return *this;
		}
		// caso /= inf(num/0) divido per inf -> 0 funziona con caso semplice
		// caso senza problemi
		rational inv(other.den_, other.num_);
		*this *= inv;
		return *this;
	}
	
	/* Implementazione canonica divisione */
	rational operator/(const rational& other) const {
		rational ret = *this;
		ret /= other;
		return ret;
	}
};


/* Operatore << per stampa oggetto */
template<typename I>
std::ostream&
operator << (std::ostream& os, const rational<I>& rat) {
	if (rat.is_inf()) {
		if (rat.num()<0){
			os << "-inf";
		}
		else {
			os << "+inf";
		}
	}
	else if (rat.is_nan()) {
		os << "NaN";
	}
	else {
		os << rat.num() << "/" << rat.den();
	}
	return os;
}