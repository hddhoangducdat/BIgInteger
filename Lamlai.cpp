#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

class Binary {
    private:
        vector<char> value;
        int l, r;
    public:
        Binary(string);
        Binary(string, int);
        string clone();
        Binary Bu2();
        string BinToDec();
        string BinToHex();
        Binary operator =(Binary);
        Binary operator +(Binary);
        Binary operator -(Binary);
        Binary operator *(Binary);
        Binary operator /(Binary);
        int Bigger(Binary);
        bool Bang0();
        string operator >>(int);
        string operator <<(int);
        string operator &(Binary);
        string operator |(Binary);
        string operator ^(Binary);
        string negative();
        string rol();
        string ror();
        string ToString();
};

int main() {
    return 0;
}

Binary::Binary(string target) {
    for (int i = 0 ; i < 128; i++) this->value.push_back('0');
    int length = target.length() < 128 ? target.length() : 128; 
    r = 127;
    l = r - length + 1;
    this->value[0] = target[0];
    for (int i = 1 ; i < length; i++) 
        if (i < 128) this->value[l + i] = target[i]; 
    l++;
}

Binary::Binary(string target, int heso) {
    
}

string Binary::clone(){
    string s;
    for (int i = 0; i < 128 ; i++) {
        s = s + this->value[i];
    }
    return s;
}

Binary Binary::Bu2(){
    auto tmp = *this;
    for (int i = 0 ; i < 128; i++){
        if (this->value[i] == '1') tmp.value[i] = '0';
        else tmp.value[i] = '1';
    } 
    Binary cong1("01");
    return tmp + cong1;
}

string Binary::BinToDec() {
    
}

string Binary::BinToHex() {

}

Binary Binary::operator=(Binary other){
    for (int i = 0 ; i < 128 ; i++) {
        this->value[i] = other.value[i];
    }
    return *this;
}

Binary Binary::operator+(Binary other){
    string result;
    int du = 0;
    for (int i = 127; i >= 0 ; i--) {
        int c1 = this->value[i] - '0';
        int c2 = other.value[i] - '0';
        int t = c1 + c2 + du;
        switch(t) {
            case 0: 
                result = '0' + result;
                du = 0;
                break;
            case 1:
                result = '1' + result;
                du = 0;
                break;
            case 2:
                result = '0' + result;
                du = 1;
                break;
            case 3:
                result = '1' + result;
                du = 1;
                break;
        }
    }
    Binary kq(result);
    return kq;
}

Binary Binary::operator-(Binary other){
    return *this + other.Bu2();
}

Binary Binary::operator*(Binary other){
    char q1 = '0';
    string tmp;
    for (int i = 0 ; i < 128 ; i++) tmp = tmp + '0';
    Binary a(tmp); int k = 128;
    while (k > 0) {
        if (other.value[127] == '1' && q1 == '0') a = *this - a;
        else if (other.value[127] == '0' && q1 == '1') a = *this + a;
        string nho;
        for (int i = 0 ; i < 128; i++) nho = nho + a.value[i];
        for (int i = 0 ; i < 128; i++) nho = nho + other.value[i];
        for (int i = 1 ; i < 128; i++) a.value[i] = nho[i - 1];
        for (int i = 0; i < 128; i++) other.value[i] = nho[i + 128];
        q1 = nho[256];
        k--;
    }
    return other;
}

int Binary::Bigger(Binary other) {
    for (int i = 0 ; i < 128 ; i++) {
        if (this->value[i] > other.value[i]) return 1;
        else if (this->value[i] < other.value[i]) return -1;
    }
    return 0;
}

bool Binary::Bang0(){
    if (this->value[0] == '1'){
        for (int i = 1 ;i < 128; i++) 
            if (this->value[i] == '1') return false;
    }
    else {
        for (int i = 1 ; i < 128 ; i++) 
            if (this->value[i] == '1') return false;
    }
    return true;
}

Binary Binary::operator/(Binary other) {
    auto dau1 = this->value[0];
    auto dau2 = other.value[0];
    auto m = dau1 == '1' ? this->Bu2() : *this;
    auto q = dau2 == '1' ? other.Bu2() : other;
    int ss = m.Bigger(q);
    if (ss == -1) {
        Binary kq("00");
        return kq;
    }
    else if (ss == 0) {
        Binary kq("01");
        q = kq;
    }
    else {
        string tmp;
        for (int i = 0 ; i < 128 ; i++) tmp = q.value[0] == '0' ? '0' : '1';
        Binary a(tmp); int k = 128;
        while (k > 0) {
            string nho;
            for (int i = 1 ; i < 128; i++) nho = nho + a.value[i];
            for (int i = 0 ; i < 128; i++) nho = nho + q.value[i];
            for (int i = 0 ; i < 128; i++) a.value[i] = nho[i];
            for (int i = 0; i < 127; i++) q.value[i] = nho[i + 128];    
            q.value[127] = '0';

            auto tam = a;
            a = a - m;
            if (a.value[0] == '1' && !a.Bang0()) {
                q.value[127] = '0';
                a = tam;
            }
            else q.value[127] = '1';

            k--;
        }
    }
    if (dau1 != dau2) q = q.Bu2();
    return q;
}

