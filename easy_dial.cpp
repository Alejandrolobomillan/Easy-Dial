#include "easy_dial.hpp"
//COST: O(n)
void merge(vector<string>& V, int esq, int mig, int dret) {
    int n1 = mig - esq + 1;
    int n2 = dret - mig;

    vector<string> esqArray(n1);
    vector<string> dretArray(n2);

    
    for (int i = 0; i < n1; i++){
        esqArray[i] = V[esq + i];
    }
    for (int j = 0; j < n2; j++){
       dretArray[j] = V[mig + 1 + j];
    }
   
    int i = 0;
    int j = 0;
    int k = esq;
    while (i < n1 && j < n2) {
        if (esqArray[i] <= dretArray[j]) {
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

//COST: O(n log(n))
void mergeSort(vector<string>& V, int esq, int dret) {
    if (esq < dret) {
        int mig = esq + (dret - esq) / 2;
        mergeSort(V, esq, mig);
        mergeSort(V, mig + 1, dret);
        merge(V, esq, mig, dret);
    }
}

//COST: O(n)
void merge2(vector<phone>& V, int esq, int mig, int dret) {
    int n1 = mig - esq + 1;
    int n2 = dret - mig;

    vector<phone> esqArray(n1);
    vector<phone> dretArray(n2);

    
    for (int i = 0; i < n1; i++){
        esqArray[i] = V[esq + i];
    }
    for (int j = 0; j < n2; j++){
       dretArray[j] = V [mig + 1 + j];
    }
   
    int i = 0;
    int j = 0;
    int k = esq;
    while (i < n1 && j < n2) {
        if (esqArray[i] >= dretArray[j]) { 
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

//COST: O(n log(n))
void mergeSort2(vector<phone>& V, int esq, int dret) {
    if (esq < dret) {
        int mig = esq + (dret - esq) / 2;
        mergeSort2(V, esq, mig);
        mergeSort2(V, mig + 1, dret);
        merge2(V, esq, mig, dret);
    }
}
//COST O(n),el cost literal de la insercio sera O(n*M) en el pitjor cas i O(n log(M)) en el cas on es distribueix l'arbre
// de forma  uniforme, ara be, com M es la longitud mitjana de les paraules i aquesta es constant, el cost sera lineal en tot cas
easy_dial::easy_dial(const call_registry& R) throw(error) {
    vector<phone> aux;
    R.dump(aux);
    _referencia_maxima = -1;
    _freq_total = 0;
    _itv = 0;
    if (aux.size() != 0 ){
        mergeSort2(aux,0,aux.size()-1);
        _telefons =  new phone[aux.size()];
        _visitats =  new phone[aux.size()];
        _referencia_maxima = 0;
        _telefons[0] = aux[0];
        _it = 1;
        _freq_total += aux[0].frequencia();
    }
    else {
         _telefons =  nullptr;
        _visitats =  nullptr;
        _it = 0;
    }
    unsigned int i = 1;
    _iniciat = false;
    _arrel = nullptr; 
    while(i < aux.size()) {
        _freq_total += aux[i].frequencia();
        _telefons[i] = aux[i];
        insereix(aux[i].nom(), i);
        ++_it; 
        ++i;  
    }
}
// COST: O(n), el cost sera lineal perque s'han de copiar tots el nodes de l'arbre (n).
easy_dial::easy_dial(const easy_dial& D) throw(error) {
    _arrel = copiaNodes(D._arrel);
    _prefix_curs = D._prefix_curs;
    _iniciat = D._iniciat;
    _it = D._it;
    _itv = D._itv;
    _freq_total = D._freq_total;
    _referencia_maxima = D._referencia_maxima;
    _noprefix = D._noprefix;

    if (_it != 0){

        _telefons = new phone[_it];
        _visitats = new phone[_it];
        for(int i = 0; i < _it; ++i) {
            _telefons[i] = D._telefons[i];
        }
        for(int j = 0; j < _itv; ++j) {
            _visitats[j] = D._visitats[j];
        }
    }
    else{

        _telefons = nullptr;
        _visitats = nullptr;
    }

}



//COST: O(n), al igual que la copia el cost sera el de copiar tots els nodes
easy_dial& easy_dial::operator=(const easy_dial& D) throw(error) {
    esborraNodes(_arrel);
    _arrel = copiaNodes(D._arrel);
    _prefix_curs = D._prefix_curs;
    _iniciat = D._iniciat;
    _it = D._it;
    _itv = D._itv;
    _freq_total = D._freq_total;
    _noprefix = D._noprefix;
    _referencia_maxima = D._referencia_maxima;
    if (_it != 0){

        _telefons = new phone[_it];
        _visitats = new phone[_it];
        for(int i = 0; i < _it; ++i) {
            _telefons[i] = D._telefons[i];
        }
        for(int j = 0; j < _itv; ++j) {
            _visitats[j] = D._visitats[j];
        }
    }
    else{

        _telefons = nullptr;
        _visitats = nullptr;
    }
    return *this;
}
//COST: O(n), s'han d'eliminar tots els nodes de l'arbre.
easy_dial::~easy_dial() throw() {

    if (_arrel != nullptr) {
        esborraNodes(_arrel);
        _arrel = nullptr;
    }
    if (_telefons != nullptr){
        
          delete[] _telefons;
          _telefons = nullptr;
    }
    if (_visitats != nullptr){
        
        delete[] _visitats;
        _visitats = nullptr;
    }


}
//COST: O(), com guardem l'element de l'inici directament en la contructora, accedir-hi desde inici es cost constat.
string easy_dial::inici() throw() {
   _itv = 0;
   _prefix_curs = "";
   _iniciat = true;
   _noprefix = false;

    if(_referencia_maxima == -1) {
    _noprefix = true;
    return "";
   }

   _visitats[_itv] = _telefons[_referencia_maxima];
   ++_itv;
   return _visitats[_itv-1].nom();  
}
//COST: O(), per trobar la paraula adient amb l'operacio seguent, busquem el node que representa aquell prefix
// on es representa el maxim, tindra un cost de M * log(z) on M es lalongitud mitjana d'una paraula i z el nombre 
// de caracters del alfabet utilitzat, aquest calcul es mantendra constant
string easy_dial::seguent(char c) throw(error) {
    if (not _iniciat) {
        throw error(ErrPrefixIndef);
    }
    if(_noprefix) {
        _iniciat = false;
       
        throw error(ErrPrefixIndef);
    }
    _prefix_curs = _prefix_curs+c;
    string aux = _prefix_curs;
    int ref = -1;
    ref = troba_prefix(_arrel, aux);
    if(ref == -1 ) {
        _noprefix = true;
        return "";
    }
    _visitats[_itv]= _telefons[ref];
    ++_itv;
    return _telefons[ref].nom();
}
// COST O(), com tenim un array on guardem els elements que s'han trobat en les busquedes,anterior nomes 
// ha d'accedir a l'ultim resultat, marcat per un "iterador(_itv)".
string easy_dial::anterior() throw(error) {
    if (_iniciat == false) throw error(ErrPrefixIndef);
    if (_prefix_curs == "") {
        _iniciat = false; 
        throw error(ErrNoHiHaAnterior);
    }
    if (_noprefix) {
        ++_itv;
        _noprefix = false; 
    }
    _prefix_curs = _prefix_curs.substr(0, _prefix_curs.size() - 1);
    _itv--;
    return _visitats[_itv-1].nom();
}
//COST: O(),num_telf accedeix directamenta l'array on son tots els contactes , i en la posicio que marqui _itv
// estara el contacte que busquem.
nat easy_dial::num_telf() const throw(error) {
       
    if (_iniciat == false) throw error(ErrPrefixIndef);
    if (_visitats == nullptr or _noprefix) throw error(ErrNoExisteixTelefon);
    else {
        return _visitats[_itv-1].numero();
        
    } 
}
//COST: O(n), en cas de no haber prefix recorrera l'array per aconsguir tots els phones
// en cas d'haberi executara omple_vector amb cost O(n)
void easy_dial::comencen(const string& pref, vector<string>& result) const throw(error) {
    
    if (_it != 0){
        string prefix = pref;
        if (prefix.empty()){
            int i = 0;
            while(i < _it){
              result.push_back(_telefons[i].nom());  
              ++i;
            }
        }

        else{
            if (conte_prefix(pref,_telefons[_referencia_maxima].nom())) result.push_back(_telefons[_referencia_maxima].nom());
            string aux = pref;
            omple_vector(_arrel,result,prefix,aux);
        }  
        mergeSort(result,0,result.size()-1);
    }
              
}

//COST: O(n), hem de recorrer la branca de l'arbre a partir del prefix, trobar aquest prefix tindra un cost constant
// mentre que recorrer la branca tindra la forma n/x.
void easy_dial::omple_vector(node* n,vector<string>& result,string& prefix,const string prefix_original) const {
    if (n != nullptr){
        if (not prefix.empty()) {
            if (prefix[0] < n->_lletra) {
                omple_vector(n->f_esq, result, prefix,prefix_original);
            } else if (prefix[0] > n->_lletra) {
                omple_vector(n->f_dret, result, prefix,prefix_original);
            } else {
                bool conte = conte_prefix(prefix_original,_telefons[n->_referencia].nom());
                if (n->_referencia != -1 and conte ){
                   result.push_back(_telefons[n->_referencia].nom()); 
                }
                string busca_prefix = prefix.substr(1);
                omple_vector(n->f_cen,result,busca_prefix,prefix_original);
            }
        } 
        else{
            bool conte = conte_prefix(prefix_original,_telefons[n->_referencia].nom());
            if (n->_referencia != -1 and conte){
                   result.push_back(_telefons[n->_referencia].nom()); 
            }
            omple_vector(n->f_esq, result, prefix,prefix_original);
            omple_vector(n->f_cen,result,prefix,prefix_original);
            omple_vector(n->f_dret, result, prefix,prefix_original);
        }
        
    }
}

//COST O(n), que es el cost d'execucio de suma_long, on n es el nombre de nodes de l'arbre.
double easy_dial::longitud_mitjana() const throw() {  
    return suma_long(_arrel,1.0); 
}
//COST: O(log), que sera el cost de executar la funcio 
void easy_dial::insereix(const string& nom, int ref) {
    string nom_arbre = nom + phone::ENDPREF;
    _arrel = rinsereix(_arrel, 0, nom_arbre, ref);
}
//COST: O(log n), que sera el cost de trobar on s'ha de colocar el node.
typename easy_dial::node* easy_dial::rinsereix(node* n, nat i, string nom, int ref) {
    if(n == nullptr) {
        n = new node;
        n->f_esq = n->f_dret = n->f_cen = nullptr;
        n->_referencia = ref;
        ref = -1;
        n->_lletra = nom[i];
        if(i < nom.length()) {
            n->f_cen = rinsereix(n->f_cen, i+1, nom, ref);
        }   
    } else {
        if(n->_lletra > nom[i]) {
            n->f_esq = rinsereix(n->f_esq, i, nom, ref); 
        } else if(n->_lletra < nom[i]) {
            n->f_dret = rinsereix(n->f_dret, i, nom, ref);
        } else {
            if(n->_referencia ==-1) {
                n->_referencia = ref;
                ref = -1;
            }
            n->f_cen = rinsereix(n->f_cen, i+1, nom, ref);
        }

    }
    return n;
}

//COST: O(n) on n sera el nombre de nodes de l'arbre
void easy_dial::esborraNodes(node* n){
    if (n != nullptr){
        esborraNodes(n->f_esq);
        esborraNodes(n->f_dret);
        esborraNodes(n->f_cen);
        delete n;
    }
}
//COST: O(n) on n sera el nombre de nodes de l'arbre a copiar
easy_dial::node* easy_dial::copiaNodes(node* n) {
    if (n == nullptr) return nullptr; 
    node* aux = new node; 
    aux->_referencia = n->_referencia; 
    aux->_lletra = n->_lletra;
    aux->f_esq = copiaNodes(n->f_esq);
    aux->f_dret = copiaNodes(n->f_dret); 
    aux->f_cen = copiaNodes(n->f_cen); 
    return aux; 
}
//COST: O(1), el cost de trobar un prefix al nostre arbre sera M *log(z) on M es la longitud de la paraula
//i z el nombre de caracters de l'alfabet, si ho passem a M longitud mitjana de les paraules tenim const constant
int easy_dial::troba_prefix(node* n, string prefix) {
    int ref = -1;
    if(n != nullptr) {
        if (prefix.size() > 1) {
            if (prefix[0] < n->_lletra) {
                ref = troba_prefix(n->f_esq, prefix);
            } else if (prefix[0] > n->_lletra) {
                ref = troba_prefix(n->f_dret, prefix);
            } else {
                ref = troba_prefix(n->f_cen, prefix.substr(1));
            }
        } else {
            if(prefix[0] < n->_lletra) {
                 ref = troba_prefix(n->f_esq, prefix);         
            } else if(prefix[0] > n->_lletra) {      
                ref = troba_prefix(n->f_dret, prefix);
            } else {
                ref = n->_referencia;
            }   
        }     
    }
    return ref;
}
//COST: O(n) on n sera la longitud de l'estring mes curta entre el prefix i el nom
bool easy_dial::conte_prefix(const string &pref,const string &nom){

    bool conte = true;
    unsigned int i = 0;
    conte = pref.size() <= nom.size();
    while (conte and i < pref.size() and i < nom.size()){
        if (pref[i] != nom[i]) conte = false;
        ++i;
    }

    return conte;
}
//COST: O(n),on n sera els nodes de l'arbre, ja que hem de recorrer l'arbre acumulant els calculs
double easy_dial::suma_long(node* n, double h) const {
    double acumula_suma = 0.0;

    if (n != nullptr) {
        if (n->_referencia != -1) {
            double freq = (_telefons[n->_referencia].frequencia());
            if (_freq_total != 0 ) {
                acumula_suma = (freq / double(_freq_total)) * h;
            }
        }
        acumula_suma += suma_long(n->f_esq, h);
        acumula_suma += suma_long(n->f_cen, h + 1);
        acumula_suma += suma_long(n->f_dret, h);
    }
    return acumula_suma;
}

