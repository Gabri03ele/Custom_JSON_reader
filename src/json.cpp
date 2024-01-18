#include "json.hpp"

/*
 Definizione PARTE PRIVATA
 */
struct cell {
    json info;
    std::pair<std::string, json> value;
    
    cell* prev;
    cell* next;
};
typedef cell* pcella;

struct json::impl{
    // numero
    double num;
    
    // stringa
    std::string str;
    
    // null
    bool null;
    
    // boolean
    bool boolean;
    bool isBool;
    
    // Lista
    pcella headList;
    pcella tailList;
    bool isList;
    
    // Dizionario
    pcella headDict;
    pcella tailDict;
    bool isDict;
};

/*
 Dichiarazione LIST IT e CONST LIST IT
 */
struct json::list_iterator {
    using iterator_category = std::forward_iterator_tag;
    using value_type = json;
    using pointer = json*;
    using reference = json&;
    
    list_iterator(pcella ptr);
        
    reference operator*() const;
    
    pointer operator->() const;
    
    list_iterator& operator++ ();
    
    list_iterator operator++ (int /* dummy */);
    
    bool operator==(list_iterator const& rhs) const;
    bool operator!=(list_iterator const& rhs) const;
    operator bool() const;
    
private:
    pcella m_ptr;
};

struct json::const_list_iterator {
    using iterator_category = std::forward_iterator_tag;
    using value_type = json const;
    using pointer = json const*;
    using reference = json const&;
    
    const_list_iterator(pcella const ptr);
        
    reference operator*() const;
    
    pointer operator->() const;
    
    const_list_iterator& operator++ ();
    
    const_list_iterator operator++ (int /* dummy */);
        
    bool operator==(const_list_iterator const& rhs) const;
    bool operator!=(const_list_iterator const& rhs) const;
    operator bool() const;
    
private:
    cell const* m_ptr;
};

/*
 Definizione LIST IT
 */
json::list_iterator::list_iterator(pcella ptr) : m_ptr(ptr) {}

json::list_iterator::reference json::list_iterator::operator*() const {
    return m_ptr->info;
}

json::list_iterator::pointer json::list_iterator::operator->() const {
    return &(m_ptr->info);
}

json::list_iterator& json::list_iterator::operator++() {
    m_ptr = m_ptr->next;
    return *this;
}

json::list_iterator json::list_iterator::operator++(int) {
    list_iterator tmp = *this;
    m_ptr = m_ptr->next;
    return tmp;
}

bool json::list_iterator::operator==(list_iterator const& rhs) const {
    return m_ptr == rhs.m_ptr;
}

bool json::list_iterator::operator!=(list_iterator const& rhs) const {
    return !(*this == rhs);
}

json::list_iterator::operator bool() const {
    return m_ptr != nullptr;
}

json::list_iterator json::begin_list() {
    if(is_list()) {
        return {pimpl->headList};
    } else {
        throw json_exception{ "Testa della lista non valida" };
    }
}

json::list_iterator json::end_list() {
    if(is_list()) {
        return {nullptr};
    } else {
        throw json_exception{ "Coda della lista non valida" };
    }
}

/*
 Definizione CONST LIST IT
 */
json::const_list_iterator::const_list_iterator(pcella ptr) : m_ptr(ptr) {}

json::const_list_iterator::reference json::const_list_iterator::operator*() const {
    return m_ptr->info;
}

json::const_list_iterator::pointer json::const_list_iterator::operator->() const {
    return &(m_ptr->info);
}

json::const_list_iterator& json::const_list_iterator::operator++() {
    m_ptr = m_ptr->next;
    return *this;
}

json::const_list_iterator json::const_list_iterator::operator++(int) {
    const_list_iterator tmp = *this;
    m_ptr = m_ptr->next;
    return tmp;
}

bool json::const_list_iterator::operator==(const_list_iterator const& rhs) const {
    return m_ptr == rhs.m_ptr;
}

bool json::const_list_iterator::operator!=(const_list_iterator const& rhs) const {
    return !(*this == rhs);
}

json::const_list_iterator::operator bool() const {
    return m_ptr != nullptr;
}

json::const_list_iterator json::begin_list() const{
    if(is_list()) {
        return {pimpl->headList};
    } else {
        throw json_exception{ "Testa della lista const non valida" };
    }
}

json::const_list_iterator json::end_list() const {
    if(is_list()) {
        return {nullptr};
    } else {
        throw json_exception{ "Coda della lista const non valida" };
    }
}

/*
    Dichiarazione DICT IT e CONST DICT IT
 */

struct json::dictionary_iterator {
    using iterator_category = std::forward_iterator_tag;
    using value_type = std::pair<std::string, json>;
    using pointer = std::pair<std::string, json>*;
    using reference = std::pair<std::string, json>&;

    dictionary_iterator(pcella ptr);

    reference operator*() const;
    pointer operator->() const;
    
    // prefix increment
    dictionary_iterator& operator++ ();
    
    // postifx increment
    dictionary_iterator operator++ (int /* dummy */);
        
    bool operator==(dictionary_iterator const& rhs) const;
    bool operator!=(dictionary_iterator const& rhs) const;
    operator bool() const;
    
private:
    pcella m_ptr;
};

struct json::const_dictionary_iterator {
    using iterator_category = std::forward_iterator_tag;
    using value_type = std::pair<std::string, json> const;
    using pointer = std::pair<std::string, json> const*;
    using reference = std::pair<std::string, json> const&;

    const_dictionary_iterator(pcella ptr);
        
    reference operator*() const;
    pointer operator->() const;
    
    const_dictionary_iterator& operator++ ();
    const_dictionary_iterator operator++ (int /* dummy */);
        
    bool operator==(const_dictionary_iterator const& rhs) const;
    bool operator!=(const_dictionary_iterator const& rhs) const;
    operator bool() const;
    
private:
    cell const* m_ptr;
};

/*
 Definizione DICT IT
 */
json::dictionary_iterator::dictionary_iterator(pcella ptr) : m_ptr(ptr) {}

json::dictionary_iterator::reference json::dictionary_iterator::operator*() const {
    return m_ptr->value;
}

json::dictionary_iterator::pointer json::dictionary_iterator::operator->() const {
    return &(m_ptr->value);
}

json::dictionary_iterator& json::dictionary_iterator::operator++() {
    m_ptr = m_ptr->next;
    return *this;
}

json::dictionary_iterator json::dictionary_iterator::operator++(int) {
    dictionary_iterator tmp = *this;
    m_ptr = m_ptr->next;
    return tmp;
}

bool json::dictionary_iterator::operator==(dictionary_iterator const& rhs) const {
    return m_ptr == rhs.m_ptr;
}

bool json::dictionary_iterator::operator!=(dictionary_iterator const& rhs) const {
    return !(*this == rhs);
}

json::dictionary_iterator::operator bool() const {
    return m_ptr != nullptr;
}

json::dictionary_iterator json::begin_dictionary() {
    if(is_dictionary()) {
        return {pimpl->headDict};
    } else {
        throw json_exception{ "Testa del dizionario non valida" };
    }
}

json::dictionary_iterator json::end_dictionary() {
    if(is_dictionary()) {
        return {nullptr};
    } else {
        throw json_exception{ "Coda del dizionario non valida" };
    }
}

/*
 Definizione CONST DICT IT
 */
json::const_dictionary_iterator::const_dictionary_iterator(pcella ptr) : m_ptr(ptr) {}

json::const_dictionary_iterator::reference json::const_dictionary_iterator::operator*() const {
    return m_ptr->value;
}

json::const_dictionary_iterator::pointer json::const_dictionary_iterator::operator->() const {
    return &(m_ptr->value);
}

json::const_dictionary_iterator& json::const_dictionary_iterator::operator++() {
    m_ptr = m_ptr->next;
    return *this;
}

json::const_dictionary_iterator json::const_dictionary_iterator::operator++(int) {
    const_dictionary_iterator tmp = *this;
    m_ptr = m_ptr->next;
    return tmp;
}

bool json::const_dictionary_iterator::operator==(const_dictionary_iterator const& rhs) const {
    return m_ptr == rhs.m_ptr;
}

bool json::const_dictionary_iterator::operator!=(const_dictionary_iterator const& rhs) const {
    return !(*this == rhs);
}

json::const_dictionary_iterator::operator bool() const {
    return m_ptr != nullptr;
}

json::const_dictionary_iterator json::begin_dictionary() const{
    if(is_dictionary()) {
        return {pimpl->headDict};
    } else {
        throw json_exception{ "Testa del dizionario const non valida" };
    }
}

json::const_dictionary_iterator json::end_dictionary() const{
    if(is_dictionary()) {
        return {nullptr};
    } else {
        throw json_exception{ "Coda del dizionario const non valida" };
    }
}

void clear(pcella& head, pcella& tail) {
    pcella pc = head;
    while(pc) {
        pc = pc->next;
        delete head;
        head = pc;
    }
    head = nullptr;
    tail = nullptr;
}

// Costruttori e distruttore
json::json() {
    pimpl = new impl;
    
    pimpl->headList = nullptr;
    pimpl->tailList = nullptr;
    
    pimpl->headDict = nullptr;
    pimpl->tailDict = nullptr;
    
    pimpl->num = std::numeric_limits<double>::quiet_NaN();
    pimpl->boolean = false;
    pimpl->str = "";
    pimpl->null = true;
    
    pimpl->isBool = false;
    pimpl->isList = false;
    pimpl->isDict = false;
}

json::json(json const& k) : json() {
    pimpl->num = k.pimpl->num;
    pimpl->boolean = k.pimpl->boolean;
    pimpl->str = k.pimpl->str;
    pimpl->null = k.pimpl->null;
    pimpl->isBool = k.pimpl->isBool;
    pimpl->isList = k.pimpl->isList;
    pimpl->isDict = k.pimpl->isDict;
    
    pcella tmp = k.pimpl->headList;
    while (tmp) {
        push_back(tmp->info);
        tmp = tmp->next;
    }

    pcella temp = k.pimpl->headDict;
    while(temp) {
        insert(temp->value);
        temp = temp->next;
    }
}

json::json(json&& l) : json() {
    pimpl->headList = l.pimpl->headList;
    pimpl->tailList = l.pimpl->tailList;
    pimpl->headDict = l.pimpl->headDict;
    pimpl->tailDict = l.pimpl->tailDict;

    l.pimpl->headList = nullptr;
    l.pimpl->tailList = nullptr;
    l.pimpl->headDict = nullptr;
    l.pimpl->tailDict = nullptr;

    pimpl->boolean = l.pimpl->boolean;
    pimpl->num = l.pimpl->num;
    pimpl->str = l.pimpl->str;
    pimpl->null = l.pimpl->null;
    
    pimpl->isBool = l.pimpl->isBool;
    pimpl->isList = l.pimpl->isList;
    pimpl->isDict = l.pimpl->isDict;
}

json::~json() {
    clear(pimpl->headList, pimpl->tailList);
    clear(pimpl->headDict, pimpl->tailDict);
    
    delete pimpl;
}

// Overloading op. assegnamento
json& json::operator=(json const& l) {
    if(this != &l) {
        clear(pimpl->headList, pimpl->tailList);
        clear(pimpl->headDict, pimpl->tailDict);
        
        pimpl->num = l.pimpl->num;
        pimpl->str = l.pimpl->str;
        pimpl->boolean = l.pimpl->boolean;
        pimpl->null = l.pimpl->null;
        
        pimpl->isBool = l.pimpl->isBool;
        pimpl->isList = l.pimpl->isList;
        pimpl->isDict = l.pimpl->isDict;
        
        pcella pc1 = l.pimpl->headList;
        while(pc1) {
            push_back(pc1->info);
            pc1 = pc1->next;
        }
        
        pcella temp = l.pimpl->headDict;
        while(temp) {
            insert(temp->value);
            temp = temp->next;
        }
    }
    return *this;
}

json& json::operator=(json&& l) {
    if(this != &l) {
        clear(pimpl->headList, pimpl->tailList);
        clear(pimpl->headDict, pimpl->tailDict);
        
        pimpl->headList = l.pimpl->headList;
        pimpl->tailList = l.pimpl->tailList;
        pimpl->headDict = l.pimpl->headDict;
        pimpl->tailDict = l.pimpl->tailDict;
        
        l.pimpl->headList = nullptr;
        l.pimpl->tailList = nullptr;
        l.pimpl->headDict = nullptr;
        l.pimpl->tailDict = nullptr;
        
        pimpl->boolean = l.pimpl->boolean;
        pimpl->num = l.pimpl->num;
        pimpl->str = l.pimpl->str;
        pimpl->null = l.pimpl->null;
        
        pimpl->isBool = l.pimpl->isBool;
        pimpl->isList = l.pimpl->isList;
        pimpl->isDict = l.pimpl->isDict;
    }
    return *this;
}

/*
 Implementazione di tutte le IS function
 */
bool json::is_number() const {
    return pimpl->num == pimpl->num;
}

bool json::is_string() const {
    return !pimpl->str.empty();
}

bool json::is_bool() const {
    return pimpl->isBool;
}

bool json::is_list() const {
    return pimpl->isList;
}

bool json::is_dictionary() const {
    return pimpl->isDict;
}

bool json::is_null() const {
    return pimpl->null;
}

/*
 Implmentazione di tutte le GET function
 */
double& json::get_number() {
    if (is_number()) {
        return pimpl->num;
    } else {
        throw json_exception{ "Numero non valido" };
    }
}

double const& json::get_number() const {
    if (is_number()) {
        return pimpl->num;
    } else {
        throw json_exception{ "Numero non valido" };
    }
}

bool& json::get_bool() {
    if (is_bool()) {
        return pimpl->boolean;
    } else {
        throw json_exception{ "Booleano non valido" };
    }
}

bool const& json::get_bool() const {
    if (is_bool()) {
        return pimpl->boolean;
    } else {
        throw json_exception{ "Booleano non valido" };
    }
}

std::string& json::get_string() {
    if (is_string()) {
        return pimpl->str;
    } else {
        throw json_exception{ "Stringa non valida" };
    }
}

std::string const& json::get_string() const {
    if (is_string()) {
        return pimpl->str;
    } else {
        throw json_exception{ "Stringa non valida" };
    }
}

/*
 Implementazione SET functions
 */
void json::set_number(double l) {
    clear(pimpl->headList, pimpl->tailList);
    clear(pimpl->headDict, pimpl->tailDict);
    
    pimpl->num = l;
    pimpl->boolean = false;
    pimpl->str = "";
    pimpl->null = false;
    pimpl->isBool = false;
    pimpl->isList = false;
    pimpl->isDict = false;
}

void json::set_bool(bool k) {
    clear(pimpl->headList, pimpl->tailList);
    clear(pimpl->headDict, pimpl->tailDict);
    
    pimpl->num = std::numeric_limits<double>::quiet_NaN();
    pimpl->boolean = k;
    pimpl->str = "";
    pimpl->null = false;
    pimpl->isBool = true;
    pimpl->isList = false;
    pimpl->isDict = false;
}

void json::set_string(std::string const& str) {
    clear(pimpl->headList, pimpl->tailList);
    clear(pimpl->headDict, pimpl->tailDict);
    
    pimpl->num = std::numeric_limits<double>::quiet_NaN();
    pimpl->boolean = false;
    pimpl->str = str;
    pimpl->null = false;
    pimpl->isBool = false;
    pimpl->isList = false;
    pimpl->isDict = false;
}

void json::set_null() {
    clear(pimpl->headList, pimpl->tailList);
    clear(pimpl->headDict, pimpl->tailDict);
    
    pimpl->num = std::numeric_limits<double>::quiet_NaN();
    pimpl->boolean = false;
    pimpl->str = "";
    pimpl->null = true;
    pimpl->isBool = false;
    pimpl->isList = false;
    pimpl->isDict = false;
}

void json::set_list() {
    clear(pimpl->headList, pimpl->tailList);
    clear(pimpl->headDict, pimpl->tailDict);

    pimpl->num = std::numeric_limits<double>::quiet_NaN();
    pimpl->boolean = false;
    pimpl->str = "";
    pimpl->null = false;
    pimpl->isBool = false;
    pimpl->isList = true;
    pimpl->isDict = false;
}


void json::set_dictionary() {
    clear(pimpl->headList, pimpl->tailList);
    clear(pimpl->headDict, pimpl->tailDict);

    pimpl->num = std::numeric_limits<double>::quiet_NaN();
    pimpl->boolean = false;
    pimpl->str = "";
    pimpl->null = false;
    pimpl->isBool = false;
    pimpl->isList = false;
    pimpl->isDict = true;
}

/*
 Funzioni per AGGIUNTA ELEMENTI a LISTE e DIZIONARI
 */
void json::push_front(json const& x) {
    if (!is_list()) throw json_exception{ "Non possibile eseguire il push_front" };
    
    pcella nuovo = new cell;
    nuovo->info = x;
    nuovo->next = pimpl->headList;
    nuovo->prev = nullptr;
    std::pair<std::string, json> tmp;
    tmp.first = "";
    tmp.second.set_null();
    nuovo->value = tmp;

    if (pimpl->headList == nullptr) {
        pimpl->headList = nuovo;
        pimpl->tailList = nuovo;
    } else {
        pimpl->headList->prev = nuovo;
        pimpl->headList = nuovo;
    }
}

void json::push_back(json const& x) {
    if (!is_list()) throw json_exception{ "Non possibile eseguire il push_back" };

    pcella nuovo = new cell;
    nuovo->info = x;
    nuovo->next = nullptr;
    nuovo->prev = pimpl->tailList;
    std::pair<std::string, json> tmp;
    tmp.first = "";
    tmp.second.set_null();
    nuovo->value = tmp;

    if (pimpl->headList == nullptr) {
        pimpl->headList = nuovo;
        pimpl->tailList = nuovo;
    } else {
        pimpl->tailList->next = nuovo;
        pimpl->tailList = nuovo;
    }
}

void json::insert(std::pair<std::string, json> const& x) {
    if (!is_dictionary()) throw json_exception{ "Non possibile eseguire l'insert" };
    
    pcella tmp = new cell;
    tmp->value = x;
    tmp->next = nullptr;
    tmp->prev = pimpl->tailDict;
    json j;
    tmp->info = j;
    
    if (pimpl->headDict == nullptr) {
        pimpl->headDict= tmp;
        pimpl->tailDict = tmp;
    } else {
        pimpl->tailDict->next = tmp;
        pimpl->tailDict = tmp;
    }
}

/*
 Metodi di accesso, overloading op. []
 */
json& json::operator[](std::string const& l) {
    if (is_dictionary()) {
        pcella tmp = pimpl->headDict;
        while(tmp) {
            if (tmp->value.first == l) {
                return tmp->value.second;
            }
            tmp = tmp->next;
        }
        json nuovo;
        std::pair<std::string, json> res;
        res.first = l;
        res.second = nuovo;
        insert(res);
        
        return pimpl->tailDict->value.second;
        
    } else {
        throw json_exception{ "Non è un dizionario" };
    }
}

json const& json::operator[](std::string const& l) const {
    if (is_dictionary()) {
        pcella tmp = pimpl->headDict;
        while(tmp) {
            if (tmp->value.first == l) {
                return tmp->value.second;
            }
            tmp = tmp->next;
        }
        throw json_exception{ "Stringa non presente nel dizionario" };
    } else {
        throw json_exception{ "Non è un dizionario" };
    }
}

/*
 Metodi per lettura e stampa
 */
std::istream& operator>>(std::istream& is, json& t) {
    char c;
    is >> c;
    
    if ((c >= '0' and c <= '9') or c == '-' or c == '.') {
        is.putback(c);
        
        double num;
        is >> num;
        
        t.set_number(num);
    } else if(c == 't') {
        std::string str;
        str += c;
        
        is >> c;
        while(c != 'e') {
            str += c;
            is >> c;
        }
        str += c;
        if(str == "true") {
            t.set_bool(true);
        } else {
            throw json_exception{ "Non un bool \"false\"" };
        }
        
    } else if (c == 'f') {
        std::string str;
        str += c;
        
        is >> c;
        while(c != 'e') {
            str += c;
            is >> c;
        }
        str += c;
        if(str == "false") {
            t.set_bool(false);
        } else {
            throw json_exception{ "Non un bool \"false\"" };
        }
        
    } else if(c == '"') {
        std::string str;
        char tmp;
        
        while (is.get(tmp) && tmp != '"') {
            str += tmp;
            if (tmp == '\\') {
                is >> tmp;
                while(tmp == '\\') {
                    str += tmp;
                    is >> tmp;
                }
                str += tmp;
            }
        }
        t.set_string(str);
        
    } else if(c == '[') {
        char check_end;
        is >> check_end;
        if (check_end == ']') {
            t.set_list();
            return is;
        }
        
        is.putback(check_end);
        t.set_list();
        
        json j;
        char tmp;
        bool stop = false;
        while (!stop) {
            is >> j;
            t.push_back(j);
            is >> tmp;

            if (tmp == ']') {
                stop = true;
            } else if (tmp != ',') {
                throw json_exception{ "Input non valido nel parser lista" };
            }
        }
        
    } else if (c == '{') {
        char check_end;
        is >> check_end;
        if (check_end == '}') {
            t.set_dictionary();
            return is;
        }
        
        is.putback(check_end);
        t.set_dictionary();
        
        std::pair<std::string, json> j;
        char tmp;
        bool stop = false;
        do {
            is >> tmp;
            if(tmp != '"') throw json_exception{ "Non è una stringa nel dizionario" };
            j.first = "";
            while(is.get(tmp) && tmp != '"') {
                j.first += tmp;
                if (tmp == '\\') {
                    is >> tmp;
                    while(tmp == '\\') {
                        j.first += tmp;
                        is >> tmp;
                    }
                    j.first += tmp;
                }
            }
            
            is >> tmp;
            if(tmp != ':') throw json_exception{ "Non è una coppia chiave:valore nel dizionario" };
            is >> j.second;
            t.insert(j);
            
            is >> tmp;
            if (tmp != ',') {
                if (tmp == '}') {
                    stop = true;
                } else {
                    throw json_exception{ "Input non valido nel parser dizionario" };
                }
            }
            
        } while(!stop);
        
    } else if(c == 'n') {
        std::string str;
        str += c;
        
        is >> c;
        str += c;
        
        is >> c;
        str += c;
        
        is >> c;
        str += c;
        if(str == "null") {
            t.set_null();
        } else {
            throw json_exception{ "Non un null valido" };
        }
    }
    return is;
}

std::ostream& operator<<(std::ostream& lhs, json const& rhs) {
    if(rhs.is_number()) {
        lhs << rhs.get_number();
        
    } else if(rhs.is_bool()) {
        if(rhs.get_bool() == 1) {
            std::cout<< "true";
        } else {
            std::cout<< "false";
        }
        
    } else if(rhs.is_string()) {
        lhs << "\"";
        lhs<< rhs.get_string();
        lhs << "\"";
        
    } else if(rhs.is_list()) {
        auto startList = rhs.begin_list();
        
        std::cout<< "[";
        while(startList) {
            lhs << *startList;
            ++startList;
            if(startList) std::cout<< ", ";
        }
        std::cout<< "]";
        
    } else if (rhs.is_dictionary()) {
        auto startDict = rhs.begin_dictionary();
        
        std::cout<< "{";
        while(startDict) {
            std::cout << '"' << startDict->first << '"' <<  " : " << startDict->second;
            ++startDict;
            if(startDict) std::cout<< ", ";
        }
        std::cout<< "}";
        
    } else if(rhs.is_null()) {
        lhs << "null";
    }
    
    return lhs;
}
