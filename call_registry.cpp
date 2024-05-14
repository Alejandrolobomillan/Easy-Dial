#include "call_registry.hpp"
#include <list>

//cost: 0(n)
void merge(vector<phone>& V, int esq, int mig, int dret) {
    int n1 = mig - esq + 1;
    int n2 = dret - mig;

    vector<phone> esqArray(n1);
    vector<phone> dretArray(n2);

    for (int i = 0; i < n1; i++) {
        esqArray[i] = V[esq + i];
    }
    for (int j = 0; j < n2; j++) {
        dretArray[j] = V[mig + 1 + j];
    }

    int i = 0;
    int j = 0;
    int k = esq;
    while (i < n1 && j < n2) {
        if (esqArray[i].nom() <= dretArray[j].nom()) { 
            V[k] = esqArray[i];
            i++;
        } else {
            V[k] = dretArray[j];
            j++;
        }
        k++;
    } 
    while (i < n1) {
        V[k] = esqArray[i];
        i++;
        k++;
    }   
    while (j < n2) {
        V[k] = dretArray[j];
        j++;
        k++;
    }
}

//cost: 0(n log n)
void mergeSort(vector<phone>& V, int esq, int dret) {
    if (esq < dret) {
        int mig = esq + (dret - esq) / 2;
        mergeSort(V, esq, mig);
        mergeSort(V, mig + 1, dret);
        merge(V, esq, mig, dret);
    }
}

//cost: 0(1)
//Inicialitza els membres de la classe en temps constant
call_registry::call_registry() throw(error) {
    _arrel = nullptr;
    _mida = 0;
}

//cost: 0(n)
//Realitza una copia de l'estructura de nodes, depen del numero de nodes n
call_registry::call_registry(const call_registry& R) throw(error) {
    _arrel = copiaNodes(R._arrel);
    _mida = R._mida;
}

//cost: 0(n)
//Realitza una copia de l'estructura de nodes, depen del numero de nodes n
call_registry& call_registry::operator=(const call_registry& R) throw(error) {
    esborraNodes(_arrel);
    _arrel = copiaNodes(R._arrel);
    _mida = R._mida;
    return *this;
}

//cost: 0(n)
//Realitza un alliberament de la memòria assignada, depen del numero de nodes n
call_registry::~call_registry() throw() {
    esborraNodes(_arrel);
}

//cost: 0(log n)
//Busca el numero en l'estructura de l'arbre AVL, per l'equilibri de l'arbre te
//una complexitat logarítmica, realitza assignacions de cost constant i si no es null
//insereix un node al arbre amb cost logaritmic per l'estructura de l'arbre
void call_registry::registra_trucada(nat num) throw(error) {
    node* trobat = busca_numero(_arrel, num);
    if(trobat != nullptr) {
        trobat->_contacte++;
    } else {
        phone p(num, "", 1);
        _arrel = afegeix_contacte(_arrel, p);
        _mida++;
    }
}

//cost: 0(log n)
//Busca el numero en l'estructura de l'arbre AVL, per l'equilibri de l'arbre te
//una complexitat logarítmica, realitza assignacions de cost constant i si no es null
//insereix un node al arbre amb cost logaritmic per l'estructura de l'arbre
void call_registry::assigna_nom(nat num, const string& name) throw(error) {
    node* trobat = busca_numero(_arrel, num);
    if(trobat != nullptr) {
        trobat->_contacte = phone(num, name, trobat->_contacte.frequencia());
    } else {
        phone p(num, name, 0);
        _arrel = afegeix_contacte(_arrel, p);
        ++_mida;
    }
}

//cost: 0(log n)
//Busca el numero en l'estructura de l'arbre AVL, per l'equilibri de l'arbre te
//una complexitat logarítmica i elimina el node en l'arbre amb cost logaritmic
void call_registry::elimina(nat num) throw(error) {
    node* trobat = busca_numero(_arrel, num);
    if(trobat != nullptr) {
        _arrel = elimina_contacte(_arrel, num);
        _mida--;
    } else {
        throw error(ErrNumeroInexistent);
    }
}

//cost: 0(log n)
//Busca el numero en l'estructura de l'arbre AVL, per l'equilibri de l'arbre te
//una complexitat logarítmica 
bool call_registry::conte(nat num) const throw() {
    bool conte = true;
    node* trobat = busca_numero(_arrel, num);
    if(trobat == nullptr) {
        conte = false;
    } 
    return conte;
}

//cost: 0(log n)
//Busca el numero en l'estructura de l'arbre AVL, per l'equilibri de l'arbre te
//una complexitat logarítmica 
string call_registry::nom(nat num) const throw(error) {
    node* trobat = busca_numero(_arrel, num);
    if(trobat != nullptr) {
        return trobat->_contacte.nom();
    } else {
        throw error(ErrNumeroInexistent);
    }
}

//cost: 0(log n)
//Busca el numero en l'estructura de l'arbre AVL, per l'equilibri de l'arbre te
//una complexitat logarítmica 
nat call_registry::num_trucades(nat num) const throw(error) {
    node* trobat = busca_numero(_arrel, num);
    if(trobat != nullptr) {
        return trobat->_contacte.frequencia();
    } else {
        throw error(ErrNumeroInexistent);
    }
}

//cost: 0(1)
//Retorna si el call_regisitry es buit, cost constant
bool call_registry::es_buit() const throw() {
    bool es_buit = false;
    if(_arrel == nullptr) {
        es_buit = true;
    }
    return es_buit; 
}

//cost: 0(1)
//Retorna la mida del call_regisitry es buit, cost constant
nat call_registry::num_entrades() const throw() {
    return _mida;
}

//cost: 0(n log n)
//Realitza bolcat que tracta n elements amb cost lineal i despres MergeSort
//amb un cost de n * log n 
void call_registry::dump(vector<phone>& V) const throw(error) {
    bolcat(V,_arrel);
    mergeSort(V, 0, V.size()-1);
    for(int i = 0; i < int(V.size()-1); ++i) {
        if(V[i].nom() == V[i+1].nom()) throw error(ErrNomRepetit);
    }    
}

//cost: 0(n)
//Realitza una copia de l'estructura de nodes, depen del numero de nodes n
call_registry::node* call_registry::copiaNodes(node* n) {
    if (n == nullptr) return nullptr; 
    node* aux = new node; 
    aux->_contacte = n->_contacte; 
    aux->_altura = n->_altura;
    aux->f_esq = copiaNodes(n->f_esq);
    aux->f_dret = copiaNodes(n->f_dret); 
    return aux; 
}

//cost: 0(n)
//Realitza un alliberament de la memòria assignada, depen del numero de nodes n
void call_registry::esborraNodes(node* n) {
    if (n != nullptr) {
        esborraNodes(n->f_esq);
        esborraNodes(n->f_dret);
        delete n;
    }
}

//cost: 0(n)
//Realitza un recorregut en l'estructura de nodes, depen del numero de nodes n
nat call_registry::comptaNodes(node* n) {
    if(n == nullptr) {
        return 0;
    }
    return comptaNodes(n->f_esq) + comptaNodes(n->f_dret) + 1;
}

//cost: 0(log n)
//Busca el numero en l'estructura de l'arbre AVL, per l'equilibri de l'arbre te
//una complexitat logarítmica 
call_registry::node* call_registry::busca_numero(node* n, nat num) {
    if(n != nullptr) {
        if(num < n->_contacte.numero()) {
            return busca_numero(n->f_esq, num);
        } else if(num > n->_contacte.numero()) {
            return busca_numero(n->f_dret, num);
        } else {
            return n;
        }
    }
    return nullptr;
} 

//cost: 0(log n)
//Realitza insercions en l'arbre AVL, mantenint l'equilibri, per l'estructura
//comporta una complexitat logarítmica
call_registry::node* call_registry::afegeix_contacte(node* n, phone p) {
    if (n == nullptr) {
        n = new node;
        n->f_esq = nullptr;
        n->f_dret = nullptr;
        n->_contacte = p;
        n->_altura = 1;

    } else if(p.numero() < n->_contacte.numero()) {
        n->f_esq = afegeix_contacte(n->f_esq, p);
    } else if(p.numero() > n->_contacte.numero()) {
        n->f_dret = afegeix_contacte(n->f_dret, p);
    }  

    n->_altura = max(altura(n->f_esq), altura(n->f_dret)) + 1;

    int fe = factor_equilibri(n);

    if(fe > 1 and p.numero() < n->f_esq->_contacte.numero()) {
        return rotacio_dreta(n);
    }

    if(fe < -1 and p.numero() > n->f_dret->_contacte.numero()) {
        return rotacio_esquerra(n);
    }

    if(fe > 1 and p.numero() > n->f_esq->_contacte.numero()) {
        n->f_esq = rotacio_esquerra(n->f_esq);
        return rotacio_dreta(n);
    }

    if(fe < -1 and p.numero() < n->f_dret->_contacte.numero()) {
        n->f_dret = rotacio_dreta(n->f_dret);
        return rotacio_esquerra(n);
    }
    return n;
}

//cost: 0(log n)
//Realitza eliminacions en l'arbre AVL, mantenint l'equilibri, per l'estructura
//comporta una complexitat logarítmica
call_registry::node* call_registry::elimina_contacte(node* n, nat num) {
    if (n == nullptr) {
        return n; 
    }
    if (num < n->_contacte.numero()) {
        n->f_esq = elimina_contacte(n->f_esq, num);
    } else if (num > n->_contacte.numero()) {
        n->f_dret = elimina_contacte(n->f_dret, num);
    } else {
        if (n->f_esq == nullptr) {
            node* aux = n->f_dret;
            delete n;
            return aux;
        } else if (n->f_dret == nullptr) {
            node* aux = n->f_esq;
            delete n;
            return aux;
        }
        node* aux = n->f_dret;
        while (aux->f_esq != nullptr) {
            aux = aux->f_esq;
        }

        n->_contacte = aux->_contacte;

        n->f_dret = elimina_contacte(n->f_dret, aux->_contacte.numero());
    }

    n->_altura = 1 + max(altura(n->f_esq), altura(n->f_dret));

    int fe = factor_equilibri(n);

    if (fe > 1 && factor_equilibri(n->f_esq) >= 0) {
        return rotacio_dreta(n);
    }
    if (fe > 1 && factor_equilibri(n->f_esq) < 0) {
        n->f_esq = rotacio_esquerra(n->f_esq);
        return rotacio_dreta(n);
    }
    if (fe < -1 && factor_equilibri(n->f_dret) <= 0) {
        return rotacio_esquerra(n);
    }
    if (fe < -1 && factor_equilibri(n->f_dret) > 0) {
        n->f_dret = rotacio_dreta(n->f_dret);
        return rotacio_esquerra(n);
    }
    return n;
}

//cost: 0(n)
//Realitza un recorregut per l'arbre i agrega els contactes al vector
//ha de recorre n elements que comporta un cost linial
void call_registry::bolcat(vector<phone>& V, node* n) const throw(error) {
    if (n != nullptr) {
        if(n->_contacte.nom() != "") {
            V.push_back(n->_contacte);
        }
        bolcat(V,n->f_esq);
        bolcat(V,n->f_dret);
    }
}

//cost: 0(1)
//Retorna l'altura del node de l'arbre AVL amb cost constant
int call_registry::altura(node* n) {
    if(n == nullptr) 
        return 0;
    return n->_altura;
}

//cost: 0(1)
//Calcula i retorna el factor d'equilibri de un node de l'arbre AVL
int call_registry::factor_equilibri(node* n) {
    if(n == nullptr) 
        return 0;
    return altura(n->f_esq) - altura(n->f_dret);
}

//cost: 0(1)
//Realitza una rotació a la dreta del AVL i reajust ales altures
//l'operació es de temps constant
call_registry::node* call_registry::rotacio_dreta(node* y) {
    node *x = y->f_esq;
    node *T2 = x->f_dret;

    x->f_dret = y;
    y->f_esq = T2;

    y->_altura = max(altura(y->f_esq), altura(y->f_dret)) + 1;
    x->_altura = max(altura(x->f_esq), altura(x->f_dret)) + 1;

    return x;
}

//cost: 0(1)
//Realitza una rotació a l'esquerra del AVL i reajust ales altures
//l'operació es de temps constant
call_registry::node* call_registry::rotacio_esquerra(node* x) {
    node *y = x->f_dret;
    node *T2 = y->f_esq;

    y->f_esq = x;
    x->f_dret = T2;

    x->_altura = max(altura(x->f_esq), altura(x->f_dret)) + 1;
    y->_altura = max(altura(y->f_esq), altura(y->f_dret)) + 1;

    return y;
}
