#include "phone.hpp"

//cost: 0(1)
phone::phone(nat num, const string& name, nat compt) throw(error) {
	_numero = num;
	for(int i = 0; i < int(name.size()); ++i) {
		if(name[i] == '<' or name[i] == '|' or name[i] == '\0') {
			throw error(ErrNomIncorrecte);
		}
	}
	_nom = name;
	_trucades = compt;
}

//cost: 0(1)
phone::phone(const phone& t) throw(error) {
	_numero = t._numero;
	_nom = t._nom;
	_trucades = t._trucades;
}

//cost: 0(1)
phone& phone::operator=(const phone& t) throw(error) {
	_numero = t._numero;
	_nom = t._nom;
	_trucades = t._trucades;
	return *this;
}

//cost: 0(1)
phone::phone::~phone() throw() {

}

//cost: 0(1)
nat phone::numero() const throw() {
	return _numero;
}

//cost: 0(1)
string phone::nom() const throw() {
	return _nom;
}

//cost: 0(1)
nat phone::frequencia() const throw() {
	return _trucades;
}

//cost: 0(1)
phone& phone::operator++() throw() {
	_trucades++;
	return *this;
}

//cost: 0(1)
phone phone::operator++(int) throw() {
	phone aux = *this;
	_trucades++;
	return aux;
}

//cost: 0(1)
bool phone::operator==(const phone& t) const throw() {
	bool iguals = true;
	if(_nom != t._nom or _trucades != t._trucades) {
		iguals = false;
	}
	return iguals;
}

//cost: 0(1)
bool phone::operator!=(const phone& t) const throw() {
	return not(*this == t);
}

//cost: 0(1)
bool phone::operator<(const phone& t) const throw() {
	bool ho_es;
	if(_trucades < t._trucades) {
		ho_es = true;
	} else if(_trucades > t._trucades) {
		ho_es = false;
	} else if(_trucades == t._trucades) {
		ho_es = (_nom < t._nom);
	}
	return ho_es;
}

//cost: 0(1)
bool phone::operator>(const phone& t) const throw() {
	bool ho_es;
	if(_trucades > t._trucades) {
		ho_es = true;
	} else if(_trucades < t._trucades) {
		ho_es = false;
	} else if(_trucades == t._trucades) {
		ho_es = (_nom > t._nom);
	}
	return ho_es;
}

//cost: 0(1)
bool phone::operator<=(const phone& t) const throw() {
	bool ho_es;
	if(_trucades < t._trucades) {
		ho_es = true;
	} else if(_trucades > t._trucades) {
		ho_es = false;
	} else if(_trucades == t._trucades) {
		ho_es = (_nom <= t._nom);
	}
	return ho_es;
}

//cost: 0(1)
bool phone::operator>=(const phone& t) const throw() {
	bool ho_es;
	if(_trucades > t._trucades) {
		ho_es = true;
	} else if(_trucades < t._trucades) {
		ho_es = false;
	} else if(_trucades == t._trucades) {
		ho_es = (_nom >= t._nom);
	}
	return ho_es;
}

