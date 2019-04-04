#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

class Decimal  // cần class này để hỗ trợ tính toán chuyển từ Binary -> Decimal
{
private:
	string value;
	int length;
public:
	Decimal(string string);
	string standardized(string &number); //Hàm chuẩn hoá chuỗi
	string operator+(Decimal b);
	string operator - (Decimal b);
	string operator * (Decimal b);
};
Decimal::Decimal(string string)
{
	value = string;
	length = string.length();
}

string Decimal::standardized(string &number)
{
	bool sign = false; // false = không có dấu
	if (number[0] == '-')
	{
		sign = true;
		number.erase(0, 1); // xoá dấu
	}
	while ((number[0] - '0') == 0)
	{
		number.erase(0, 1);
	}
	if (sign == true)
		number.insert(0, 1, '-');// thêm lại dấu
	return number;
}


string Decimal::operator + (Decimal other)
{
	string temp = this->value; // sao lưu chuối gốc, tránh làm thay đổi chuỗi 
	string number = other.value;   // sao lưu chuối gốc, tránh làm thay đổi chuỗi 
	string result = (value.length() > number.length()) ? value : number;
	bool sign = true; // true = dương, false = âm
	char mem = '0'; // biến nhớ khi cộng
	if ((temp[0] == '-' && number[0] != '-') || (temp[0] != '-' && number[0] == '-')) // kiểu tra xem số có dấu hay không
	{
		if (temp[0] == '-') // a+b . nếu a mang dấu -
		{
			temp.erase(0, 1);
			Decimal a = Decimal(temp);
			result = other - a; // kết quả = b-a;
		}

		if (number[0] == '-') // a+b . nếu b mang dấu -
		{
			number.erase(0, 1);
			Decimal a = Decimal(temp);
			Decimal b = Decimal(number);
			result = a - b; // kết quả = a-b;
		}
	}

	else
	{
		if (temp[0] == '-'&& number[0] == '-')
		{
			temp.erase(0, 1); // loại bỏ dấu
			number.erase(0, 1); // loại bỏ dấu 
			result = (temp.length() > number.length()) ? temp : number;
			sign = false;  // lưu dấu, sẽ chèn lại dấu khi có kết quả cuối cùng
		}
		if (temp.length() > number.length())
			number.insert(0, temp.length() - number.length(), '0');
		else
			if (number.length() > temp.length())
				temp.insert(0, number.length() - temp.length(), '0');
		for (int i = temp.length() - 1; i >= 0; i--)
		{
			result[i] = ((temp[i] - '0') + (number[i] - '0') + (mem - '0')) + '0';
			if (i != 0)
			{
				if ((result[i] - '0') > 9)
				{
					mem = '1';  // nhớ 1
					result[i] = ((result[i] - '0') - 10) + '0';
				}
				else
					mem = '0';
			}
		}
		if ((result[0] - '0') > 9)
		{
			result[0] = ((result[0] - '0') - 10) + '0';
			result.insert(0, 1, '1');
		}
		if (sign == false)
			result.insert(0, 1, '-');
	}
	return result;
}

string Decimal::operator-(Decimal other)
{
	string temp = this->value; // sao lưu chuối gốc, tránh làm thay đổi chuỗi 
	string number = other.value;   // sao lưu chuối gốc, tránh làm thay đổi chuỗi 
	string result = (value.length() > number.length()) ? value : number;
	bool check = true; // biến để lưu giá trị kiểm tra xem số nào lớn hơn
	bool sign = true; // true= dương, false = dương
	char mem = '0'; // biến nhớ khi cộng
	//------- cân bằng chuỗi . Ex: 7777
	//-------                     -37

	//------- sẽ thành             7777
	//-------                     -0037
	if ((temp[0] == '-' && number[0] != '-') || (temp[0] != '-' && number[0] == '-')) // kiểu tra xem số có dấu hay không
	{
		if (temp[0] == '-') // a-b . nếu a mang dấu -
		{
			temp.erase(0, 1);
			Decimal a = Decimal(temp);
			result = a + other; // kết quả = b-a;
			result.insert(0, 1, '-');
		}

		if (number[0] == '-') // a+b . nếu b mang dấu -
		{
			number.erase(0, 1);
			Decimal a = Decimal(temp);
			Decimal b = Decimal(number);
			result = a + b; // kết quả = a-b;
		}
	}
	else
	{
		if (temp[0] == '-'&& number[0] == '-')
		{
			temp.erase(0, 1);
			number.erase(0, 1);
			result = (temp.length() > number.length()) ? temp : number;
			sign = false;

		}
		if (temp.length() > number.length())
			number.insert(0, temp.length() - number.length(), '0');
		else
			if (number.length() > temp.length())
				temp.insert(0, number.length() - temp.length(), '0');
		//------- So sánh chuỗi xem số nào lớn hơn
		for (int i = 0; i < temp.length(); i++)
		{
			if ((temp[i] - '0') == (number[i] - '0'))
			{
				continue;
			}
			else
			{
				if ((temp[i] - '0') > (number[i] - '0'))
				{
					break;
				}
				else
				{
					check = false;
					break;
				}
			}
		}
		//------ Bắt đầu tính toán
		for (int i = temp.length() - 1; i >= 0; i--)
		{
			if (check == true) // Nếu số trừ lớn hơn số bị trừ. For ex: 444-433;
			{
				result[i] = ((temp[i] - '0') - (number[i] - '0') - (mem - '0')) + '0';
				if (i != 0)
				{
					if ((result[i] - '0') < 0)
					{

						result[i] = ((temp[i] - '0') + 10 - (number[i] - '0') - (mem - '0')) + '0';
						mem = '1';  // nhớ 1
					}
					else
						mem = '0';
				}
			}
			else  // Số trừ bé hơn số bị trừ. For ex: 333-344
			{
				result[i] = ((number[i] - '0') - (temp[i] - '0') - (mem - '0')) + '0';
				if (i != 0)
				{
					if ((result[i] - '0') < 0)
					{

						result[i] = ((number[i] - '0') + 10 - (temp[i] - '0') - (mem - '0')) + '0';
						mem = '1';  // nhớ 1
					}
					else
						mem = '0';
				}
			}
		}
		if (check == false)
		{
			result.insert(0, 1, '-');
		}
		else
			if (sign == false)
				result.insert(0, 1, '-');
	}
	return result;
}

string Decimal::operator*(Decimal b)
{
	int *res;
	string temp = value;
	string number = b.value;
	string result;
	bool sign = true; // true = dương, false = ấm
	if ((temp[0] == '-' && number[0] != '-') || (temp[0] != '-' && number[0] == '-'))
	{
		if (temp[0] == '-')
		{
			temp.erase(0, 1); // xoá dấu
			sign = false;  // là số âm
		}
		if (number[0] == '-')
		{
			number.erase(0, 1);
			sign = false;
		}
	}
	if (temp[0] == '-' && number[0] == '-')
	{
		temp.erase(0, 1);
		number.erase(0, 1);
	}
	res = new int[temp.size() + number.size()];
	for (int i = 0; i <= temp.size() + number.size(); i++)
		res[i] = 0;

	for (int i = temp.size() - 1; i >= 0; i--) {
		for (int j = number.size() - 1; j >= 0; j--)
			res[i + 1 + j] += (temp[i] - '0') * (number[j] - '0');
	}

	for (int i = temp.size() + number.size(); i >= 0; i--)
		if (res[i] > 9) {
			res[i - 1] += res[i] / 10;
			res[i] %= 10;
		}
	for (int i = 0; i < temp.size() + number.size(); i++)
		result += (res[i] + '0');
	if (sign == false)
		result.insert(0, 1, '-');
	return result;
}
//-------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------

class Binary {
    private:
        vector<char> value;
        int lastbit;
    public:
        Binary(string);
        string Div2(string);
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

class Tool {
    private: 
        string value;
    public:
        Tool(string);
        string getT();
        int getL();
        char getLast();
        Tool operator=(Tool);
        void Div2();
        bool Dung();
        Tool operator+(Tool);
};

int main() {
    return 0;
}

Binary::Binary(string target) {
    bool dau = false;
    if (target[0] == '1') {
        for (int i = 0 ; i < target.length(); i++) target[i] = target[i] == '0' ? '1' : '0';
        dau = true;
    }
    for (int i = 0 ; i < 128; i++) this->value.push_back('0');
    int length = target.length() < 128 ? target.length() : 128; 
    int r = 127;
    int l = r - length + 1;
    for (int i = 1 ; i < length; i++) 
        if (i < 128) this->value[l + i] = target[i]; 
    if (dau) *this = this->Bu2();
}

Binary::Binary(string target, int heso) {
    int k = 128;
    vector <char> kq;
    for (int i = 0 ; i < 128; i++) kq.push_back('0');
    if (heso == 10) {
        Tool X(target);
        while (X.Dung()) {
            kq[k] = char((X.getLast() - '0') % 2 + '0'); 
            X.Div2();
            k--;
        }
    }
    else {
        for (int i = target.length() ; i >= 0 ; i--) {
            string s;
            switch(target[i]) {
                case '0':
                    s = "0000";
                    break;
                case '1':
                    s = "0001";
                    break;
                case '2':
                    s = "0010";
                    break;
                case '3':
                    s = "0011";
                    break;
                case '4':
                    s = "0100";
                    break;
                case '5':
                    s = "0101";
                    break;
                case '6':
                    s = "0110";
                    break;
                case '7':
                    s = "0111";
                    break;
                case '8':
                    s = "1000";
                    break;
                case '9':
                    s = "1001";
                    break;
                case 'A':
                    s = "1010";
                    break;
                case 'B':
                    s = "1011";
                    break;
                case 'C':
                    s = "1100";
                    break;
                case 'D':
                    s = "1101";
                    break;
                case 'E':
                    s = "1110";
                    break;
                case 'F':
                    s = "1111";
                    break;
            }
            if (k - 1 >= 0) kq[k--] = s[3];
            if (k - 1 >= 0) kq[k--] = s[2];
            if (k - 1 >= 0) kq[k--] = s[1];
            if (k - 1 >= 0) kq[k--] = s[0];
        }
    }
    for (int i = 0 ; i < 128 ; i ++) this->value.push_back(kq[i]);
    if (target[0] == '-') *this = this->Bu2();
}

string Binary::clone() {
    string s;
    for (int i = 0; i < 128 ; i++) { 
        s = s + this->value[i];
    }
    return s;
}

Binary Binary::Bu2() {
    auto tmp = *this;
    for (int i = 0 ; i < 128; i++){
        if (this->value[i] == '1') tmp.value[i] = '0';
        else tmp.value[i] = '1';
    }   
    Binary cong1("01");
    return tmp + cong1;
}

string Binary::BinToDec()  
{
    
	string mu; /// lưu phần có mũ... ví dụ 2^2
	Decimal Two = Decimal("2");
	string result = "0"; /// lưu kết quả số thập phân sau khi chuyển đổi

	for (int i = Bin.length() - 1; i >= 0; i--)
	{
		mu = "2";
		if ((Bin[i] - '0') == 0) // nếu bit =0 thì bỏ qua
			continue;

		else
		{
			//-----------trường hợp mũ 0
			if (i == Bin.length() - 1 )
			{
				if (i == 0 && (Bin[0] - '0') == 1)
				{
					mu = "-1";
					result = mu;
					break;
				}
				else
				{
					mu = "1";
					result = mu;
					continue;
				}
			}
			//-----------trường hợp mũ 1
			if (i == Bin.length() - 2)
			{
				//dec = add(dec, mu);
				if ((Bin[0] - '0') == 1 && i == 0) // nếu bit đầu là 1 thì nó vừa mang dấu vừa mang giá trị
				{
					mu.insert(0, 1, '-');
				}
				else
				{
					Decimal DEC = Decimal(result);
					Decimal MU = Decimal(mu);
					result = DEC + MU; // dùng toán tử + của class Decimal
					continue;
				}
			
			}
			else//-----------trường hợp còn lại
				for (int j = i; j <= Bin.length() - 3; j++)
				{
					Decimal MU = Decimal(mu);
					mu = MU * Two;    // dùng toán tử * của class Decimal
				}
		}
		if ((Bin[0] - '0') == 1 && i==0) // nếu bit đầu là 1 thì nó vừa mang dấu vừa mang giá trị
		{
			mu.insert(0, 1, '-');
		}
		Decimal MU = Decimal(mu);
		Decimal DEC = Decimal(result);

		result = MU + DEC;   // dùng toán tử + của class Decimal
	}
	standardized(result); // chuẩn hoá ( bỏ các số không ở đầu chuỗi)
	return result;
}

string Binary::BinToHex() {
    string kq;
    for (int i = 0 ; i < 128 ; i++) {
        string tmp;
        for (int j = i ; j < i + 4 ; j++) {
            tmp = tmp + this->value[j];
        }
        if (tmp == "0000") kq = kq + '0';
        else if (tmp == "0001") kq = kq + '1';
        else if (tmp == "0010") kq = kq + '2';
        else if (tmp == "0011") kq = kq + '3';
        else if (tmp == "0100") kq = kq + '4';
        else if (tmp == "0101") kq = kq + '5';
        else if (tmp == "0110") kq = kq + '6';
        else if (tmp == "0111") kq = kq + '7';
        else if (tmp == "1000") kq = kq + '8';
        else if (tmp == "1001") kq = kq + '9';
        else if (tmp == "1010") kq = kq + 'A';
        else if (tmp == "1011") kq = kq + 'B';
        else if (tmp == "1100") kq = kq + 'C';
        else if (tmp == "1101") kq = kq + 'D';
        else if (tmp == "1110") kq = kq + 'E';
        else if (tmp == "1111") kq = kq + 'F';
    }
    return kq;
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

//---------------------------------------------

Tool::Tool(string s) {
    int vt = s[0] == '-' ? 1 : 0;
    string tmp;
    for (int i = vt ; i < s.length(); i++) tmp = tmp + s[i];
    this->value = tmp;
}

string Tool::getT() {
    return this->value;
}

int Tool::getL() {
    return this->value.length();
}

char Tool::getLast() {
    return this->value[this->getL() - 1];
}

Tool Tool::operator=(Tool other) {
    this->value = other.value;
    return *this;
}

void Tool::Div2() {
    string result;
    int du = this->value[0] - '0'; 
    int vt = 0;
    while (vt < this->getL() - 1) {
        if (du < 2) {
            vt++;
            int chia = du * 10 + int(this->value[vt] - '0');
            chia /= 2;
            result = result + char(chia + 48);
            du -= 2 * chia;
        } 
        else {
            int chia = du / 2;
            result = result + char(chia + 48);
            du -= 2 * chia;
        }
    } 
    this->value = result;
}

bool Tool::Dung() {
    if (this->getL() == 1 && this->getL() < '2') return true;
    return false;
}

Tool Tool::operator+(Tool other) {
    string kq;
    auto tmp1 = *this;
    auto tmp2 = other;
    while (tmp1.getL() > tmp2.getL()) tmp2.value = '0' + tmp2.value;
    while (tmp2.getL() > tmp1.getL()) tmp1.value = '0' + tmp1.value;
    int du = 0;
    for (int i = tmp1.getL() - 1 ; i >= 0 ; i--) {
        int c1 = tmp1.value[i] - '0';
        int c2 = tmp2.value[i] - '0';
        int t = c1 + c2 + du;
        if (t > 9) {
            du = 1;
            kq = char(t - 10 + 48) + kq;
        }
        else {
            du = 0;
            kq = char(t + 48) + kq;
        }
    }
    if (du == 1) kq = '1' + kq;
    Tool result(kq);
    return result;
}
string Binary::operator&(Binary number)
{
	string temp = Bin;
	string other = number.Bin;
	string result= (length > number.length) ? temp : other;
	if (this->length < number.length)
		temp.insert(0, number.length - this->length, '0');
	else
		if(this->length > number.length)
			other.insert(0, this->length- number.length, '0');
	for (int i = temp.length()-1; i >= 0; i--)
	{
		if ((temp[i] - '0') == 0)
		{
			result[i] = '0';
		}
		else
		{
			if ((other[i] - '0') == 0)
				result[i] = '0';
			else
				result[i] = '1';
		}
	}
	return result;
}
string Binary::operator|(Binary number)
{
	string temp = Bin;
	string other = number.Bin;
	string result = (length > number.length) ? temp : other;
	if (this->length < number.length)
		temp.insert(0, number.length - this->length, '0');
	else
		if (this->length > number.length)
			other.insert(0, this->length - number.length, '0');
	for (int i = temp.length() - 1; i >= 0; i--)
	{
		if ((temp[i] - '0') == 1)
		{
			result[i] = '1';
		}
		else
		{
			if ((other[i] - '0') == 0)
				result[i] = '0';
			else
				result[i] = '1';
		}
	}
	return result;
}
string Binary::operator^(Binary number)
{
	string temp = Bin;
	string other = number.Bin;
	string result = (length > number.length) ? temp : other;
	if (this->length < number.length)
		temp.insert(0, number.length - this->length, '0');
	else
		if (this->length > number.length)
			other.insert(0, this->length - number.length, '0');
	for (int i = temp.length() - 1; i >= 0; i--)
	{
		if ((temp[i] - '0') == 1)
		{
			if ((other[i] - '0') == 0)
				result[i] = '1';
			else
				result[i] = '0';
		}
		else
		{
			if ((other[i] - '0') == 0)
				result[i] = '0';
			else
				result[i] = '1';
		}
	}
	return result;
}

