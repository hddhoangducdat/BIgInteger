#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class Decimal {
    private:
        string value;
        int length;
    public:
        Decimal(string s);
        bool operator=(Decimal target);
};

class Binary {
    private:
        string value;
        int length;
    public:
        Binary(string s);
        string BinToHex();
        bool operator=(Binary target);
};

class Hexadecimal {
    private:
        string value;
        int length;
    public:
        Hexadecimal(string s);
        string HexToBin();
        bool operator=(Hexadecimal target);
};

int main() {

}

//----------------------------------

Hexadecimal::Hexadecimal(string s){
    value = s;
    if (length > 32) length = 32;
    else length = s.length();
}

string Hexadecimal::HexToBin() {
    string result;
    for (int i = 0 ; i < length; i++){
        switch(value[i]) {
            case '0':
                result += "0000";
                break;
            case '1':
                result += "0001";
                break;
            case '2':
                result += "0010";
                break;
            case '3':
                result += "0011";
                break;
            case '4':
                result += "0100";
                break;
            case '5':
                result += "0101";
                break;
            case '6':
                result += "0110";
                break;
            case '7':
                result += "0111";
                break;
            case '8':
                result += "1000";
                break;
            case '9':
                result += "1001";
                break;
            case 'A':
                result += "1010";
                break;
            case 'B':
                result += "1011";
                break;
            case 'C':
                result += "1100";
                break;
            case 'D':
                result += "1101";
                break;
            case 'E':
                result += "1110";
                break;
            case 'F':
                result += "1111";
                break;
            default:
                break;
        }
    }
    return result;
}

bool Hexadecimal::operator=(Hexadecimal other) {
    if (this->length != other.length) return false;
    for (int i = 0 ; i < this->length; i++)
        if (this->value[i] != other.value[i]) return false;
    return true;
}

//-----------------------------------------------

Decimal::Decimal(string s) {
    value = s;
    if (length > 38) length = 38;
    else length = s.length();
}

bool Decimal::operator=(Decimal other) {
    if (this->length != other.length) return false;
    for (int i = 0 ; i < this->length; i++)
        if (this->value[i] != other.value[i]) return false;
    return true;
}

//-----------------------------------------

Binary::Binary(string s){
    value = s;
    if (length > 128) length = 128;
    else length = s.length();
}

string Binary::BinToHex(){
    string result;
    int du = length % 4;
    switch(du) {
        case 1:
            value = "000" + value;
            break;
        case 2:
            value = "00" + value;
            break;
        case 3:
            value = '0' + value;
            break;
        default: 
            break;
    }
    for (int i = 0 ; i < length; i += 4){
        string tmp; 
        for (int j = i ; j < i + 4 ; j++) tmp += value[j];
        if (tmp == "0000") result += '0';
        else if (tmp == "0001") result += '1';
        else if (tmp == "0010") result += '2';
        else if (tmp == "0011") result += '3';
        else if (tmp == "0100") result += '4';
        else if (tmp == "0101") result += '5';
        else if (tmp == "0110") result += '6';
        else if (tmp == "0111") result += '7';
        else if (tmp == "1000") result += '8';
        else if (tmp == "1001") result += '9';
        else if (tmp == "1010") result += 'A';
        else if (tmp == "1011") result += 'B';
        else if (tmp == "1100") result += 'C';
        else if (tmp == "1101") result += 'D';
        else if (tmp == "1110") result += 'E';
        else if (tmp == "1111") result += 'F';
    }
    return result;
}

bool Binary::operator=(Binary other) {
    if (this->length != other.length) return false;
    if (this->value[0] != other.value[0]) {
        int dem = 1; int ktra = 0;
        while (dem < this->length) {
            if (this->value[dem] != '0' || other.value[dem] != '0') ktra = 1;
        }
        if (ktra == 0) return true;
    }
    for (int i = 0 ; i < this->length; i++)
        if (this->value[i] != other.value[i]) return false;
    return true;
}