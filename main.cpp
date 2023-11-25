#include <iostream>
#include <algorithm>
#include <string.h>
#include <vector>

using namespace std;

//Forward declaration
class Account;
class Card;
class ATM;
class Bank;



//Classes declaration
class User{
private:
    vector<Account*> Account_list;
    vector<string> Transaction_history;

};

//one Account, one Bank
//#############
//###Account###
//#############
class Account{
private:
    Bank* bank;
    Card* card;
public:
    Account();
    Account(Bank* aBank , Card* aCard);
    Bank* get_Bank();
    string get_Bank_name();
};
Account::Account(Bank* aBank, Card* aCard){
    bank = aBank;
    card = aCard;
}
Bank* Account::get_Bank(){
    return bank;
}


//#############
//####Card#####
//#############
class Card{
protected:
    string CardNum;
public:
    Card(string CardNum);
    string get_card_number();
};
string Card::get_card_number(){
    return CardNum;
}

//#############
//####Bank#####
//#############
class Bank{
private:
    vector<Account*> Account_list;
    string bank_name;

public:
    Bank(string name);
    string get_bank_name();
};

Bank::Bank(string name){
    bank_name = name;
}
string Bank::get_bank_name(){
    return bank_name;
}
string Account::get_Bank_name(){
    return bank->get_bank_name();
}

//#############
//#####Atm#####
//#############

class ATM {
private:
    //ATM 선언 때 선언되는 변수들
    bool isbilingual; //isbilingual은 이 atm이 두 가지의 언어를 지원하는지 알려줌 -> false면 영어만 언어 지원 (REQ 1.3)
    bool isSingle; //isSingle은 이 atm이 하나의 은행만 가능한지 두 가지 다 가능한지 알려줌 -> true이면 한 개만 됨 (REQ 1.2)

    Bank* bank;

    static int order_number;
    string unique_number = ""; // ATM마다 다른 고유 식별 번호, 6자리  
    string transaction_history = ""; //거래 내역을 담는 곳

    const int NonPrimaryDepositFee = 1000; //다른 은행 예금 수수료 (REQ 1.8)
    const int PrimaryWithdrawalFee = 1000; //같은 은행 출금 수수료 (REQ 1.8)
    const int NonPrimaryWithDrawalFee = 2000; //다른 은행 출금 수수료 (REQ 1.8)
    const int PrimarytoPrimaryFee = 2000; // 같은 은행끼리 송금 수수료 (REQ 1.8)
    const int NonPrimarytoPrimaryFee = 3000; //같은, 다른 은행끼리 송금 수수료 (REQ 1.8)
    const int NonPrimarytoNonPrimaryFee = 4000; // 다른 은행끼리 송금 수수료 (REQ 1.8)
    const int CashTransferFee = 5000; //무통장 송금 수수료 (REQ 1.8)
    
    long long AmountOfCash;

    //ATM 호출 때 선언되는 변수들
    int language_type; // 1이면 영어, 2이면 한국어 (REQ 1.3)


public:
    ATM(const bool language_option, Bank* bank_info, bool ATM_type, long long cash);

    bool get_language_option();
    bool get_language(); // true면 영어라는 뜻, false면 한국어라는 뜻
    bool get_ATM_type(); // isSinlge을 반환
    string get_bank_name();
    string get_unique_number();
    long long get_cash();

};

int ATM::order_number = 0;
ATM::ATM(const bool language_option, Bank* bank_info, bool ATM_type, long long cash){
    bank = bank_info;
    order_number++;
    string front = to_string((int)bank->get_bank_name()[0]);
    string back = to_string(order_number);
    string tmp = "";
    for(int i = 0; i<6-front.size()-back.size(); i++){
        tmp+="0";
    }
    unique_number = front + tmp +back;

    isbilingual = language_option;
    isSingle = ATM_type;
    AmountOfCash = cash;
}
bool ATM::get_language_option(){
    return isbilingual;
}
bool ATM::get_language(){
    if(!isbilingual) return true; // unilingual이면 영어만 지원함
    if(language_type == 1) return true;
    else if(language_type == 2) return false;
}
bool ATM::get_ATM_type(){
    return isSingle;
}
string ATM::get_bank_name(){
    return this->bank->get_bank_name();
}
string ATM::get_unique_number(){
    return unique_number;
}
long long ATM::get_cash(){
    return AmountOfCash;
}


int main(){
    // test case: Daegu, Kookmin, Woori, ShinHan, NonghHyup
    //Bank input
    vector<Bank*> Bank_list;
    cout << "Please Insert Card" << '\n';
    cout << "Write down the Bank's name. If you're done, input 0 or \"zero\"\n";
    // 은행별로 번호 주고 선택하라고 하는 게 낫지 않나?
    while(1){
        string bank_name;
        cout<<"Bank name: ";
        cin>>bank_name;
        if(bank_name=="0" || bank_name=="zero"){
            cout<<"Banks you inputted are [";
            for(int i = 0; i<Bank_list.size(); i++){
                cout<<Bank_list[i]->get_bank_name();
                if(i==Bank_list.size()-1) break;
                cout<<", ";
            }
            cout<<"]\n";
            break;
        }
        Bank_list.push_back(new Bank(bank_name));
    }
    cout<<'\n';
    //ATM input
    vector<ATM*> ATM_list;
    cout<<"This is ATM input section. If you're done, input 0 or \"zero\"\n";
    int index = 1;
    while(1){
        cout<<"-----"<<index<<"th ATM info-----\n";
        //language_option(Unilingual/Bilingual) input
        cout<<"ATM language option(Unilingual/Bilingual): ";
        string language_option;
        cin>>language_option;
        bool IsBilingual;
        if(language_option == "0" || language_option=="zero") break;
        if(language_option[0] == 'B' || language_option[0] == 'b') IsBilingual = true;
        else IsBilingual = false;
        cout<<"This ATM will be "<<language_option<<'\n';
        //Bank input
        cout<<"Current banks list:\n";
        for(int i = 0; i<Bank_list.size(); i++){
            cout<<i+1<<". "<<Bank_list[i]->get_bank_name();
            cout<<"\n";
        }
        cout<<"Which Bank does this ATM use? ";
        string bank_name;
        int bank_index = -1;
        try
        {
            cin>>bank_name;
            for(int i = 0; i<Bank_list.size(); i++){
                if(Bank_list[i]->get_bank_name() == bank_name){
                    bank_index = i;
                    break;
                }
            }
            if(bank_index==-1){
                throw bank_name;
            }
        }
        catch(string x)
        {
            cout<<"There is no such bank \""<<x<<"\"\n\n";
            continue;
        }
        
        
        cout<<"You chose "<<bank_name<<'\n';
        //cash input
        cout<<"How much cash will this ATM have: ";
        long long cash;
        cin>>cash;
        cout<<"This ATM will have "<<cash<<" Won\n";
        //bank_type(Single/Multiple) input
        cout<<"ATM type(Single/Multiple): ";
        string bank_type;
        cin>>bank_type;
        bool IsSingle;
        if(bank_type[0] == 'S' || bank_type[0] == 's') IsSingle = true;
        else IsSingle = false;
        cout<<"This ATM will be "<<bank_type<<'\n';
        // input
        ATM_list.push_back(new ATM(IsBilingual, Bank_list[bank_index-1], IsSingle, cash));
        index++;
        cout<<'\n';
    }
    cout<<'\n';
    //Account input

    cout<<"This is Account input session. If you're done, input 0 or \"zero\"\n";
    

    //print ATM
    for(int i = 0; i<ATM_list.size(); i++){
        ATM* tmp_atm(ATM_list[i]);
        cout<<"-------------"<<i+1<<"th ATM info-------------\n";
        cout<<"|Bank: "<<tmp_atm->get_bank_name()<<"\n";
        cout<<"|ATM Language Option: "<<((tmp_atm->get_language_option())?"Bilingual":"Unilingual")<<"\n";
        cout<<"|ATM type: "<<((tmp_atm->get_ATM_type()) ? "Single" : "Multiple")<<"\n";
        cout<<"|ATM unique number: "<<tmp_atm->get_unique_number()<<"\n";
        cout<<"|Remaining cash: "<<tmp_atm->get_cash()<<"\n";
        cout<<"--------------------------------------\n";
        cout<<'\n';
    }

    return 0;
}