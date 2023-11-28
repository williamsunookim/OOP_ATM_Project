#include <iostream>
#include <algorithm>
#include <string.h>
#include <vector>
#include <map>

using namespace std;

//Forward declaration
class Account;
class Card;
class ATM;
class Bank;


//Classes declaration

//#########################
//#####FinancialEntity#####
//#########################
class FinancialEntity {
protected:
    string name;

public:
    FinancialEntity(string name) : name(name) {}
    string get_name();
};

string FinancialEntity::get_name(){
    return name;
}
//#############
//####Bank#####
//#############
class Bank : public FinancialEntity{
private:
    vector<Account*> Account_list;
    string bank_name;

public:
    Bank(string name);
    string get_bank_name();
};
Bank::Bank(string name) : FinancialEntity(name){
    bank_name = name;
}
string Bank::get_bank_name(){
    return bank_name;
}

//##############
//#####User#####
//##############
class User{
private:
    vector<Account*> Account_list;
    vector<string> Transaction_history;
    string NameofUser;
public:
    User(string name);
    void attach(Account* account);
    string get_user_name();
};
User::User(string name){
    NameofUser = name;
}
void User::attach(Account* account){
    Account_list.push_back(account);
}
string User::get_user_name(){
    return NameofUser;
}

//one Account, one Bank
//#############
//###Account###
//#############
class Account : public FinancialEntity{
private:
    Bank* bank;
    string NameofUser;
    string NumofAccount;
    long long AmountofCash;
public:
    Account(Bank* aBank , string user_name, string account_number, long long cash);
    Bank* get_Bank();
    string get_Bank_name();
    string get_user_name();
    string get_account_number();
    long long get_cash();
};
Account::Account(Bank* aBank, string user_name, string account_number, long long cash) : FinancialEntity(aBank->get_bank_name()){
    bank = aBank;
    NameofUser = user_name;
    NumofAccount = account_number;
    AmountofCash = cash;
}
Bank* Account::get_Bank(){
    return bank;
}
string Account::get_user_name(){
    return NameofUser;
}
string Account::get_account_number(){
    return NumofAccount;
}
long long Account::get_cash(){
    return AmountofCash;
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
string Account::get_Bank_name(){
    return name;
}

//#############
//#####ATM#####
//#############
class ATM  : public FinancialEntity{
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
    
    int AmountOfCash[4]; // 1000원, 5000원, 10000원, 50000원

    //ATM 호출 때 선언되는 변수들
    bool IsEnglish; // 1이면 영어, 2이면 한국어 (REQ 1.3)


public:
    ATM(const bool language_option, Bank* bank_info, bool ATM_type, vector<int>& initial_cash);

    bool get_language_option();
    bool get_language(); // true면 영어라는 뜻, false면 한국어라는 뜻
    bool get_ATM_type(); // isSinlge을 반환
    string get_bank_name();
    string get_unique_number();
    void get_cash();
    long long get_total_cash();

};
int ATM::order_number = 0;
ATM::ATM(const bool language_option, Bank* bank_info, bool ATM_type, vector<int>& initial_cash) : FinancialEntity(bank_info->get_bank_name()){
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
    for(int i = 0; i<4; i++){
        AmountOfCash[i] = initial_cash[i];
    }
}
bool ATM::get_language_option(){
    return isbilingual;
}
bool ATM::get_language(){
    return IsEnglish;
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
void ATM::get_cash(){
    cout<<"1000 won : "<<AmountOfCash[0]<<'\n';
    cout<<"5000 won: "<<AmountOfCash[1]<<'\n';
    cout<<"10000 won: "<<AmountOfCash[2]<<'\n';
    cout<<"50000 won: "<<AmountOfCash[3]<<'\n';
}
long long ATM::get_total_cash(){
    return AmountOfCash[0]*1000 + AmountOfCash[1] * 5000 + AmountOfCash[2] * 10000 + AmountOfCash[3] * 50000;
}

// [7] = {"", "Kookmin", "Woori", "Hana", "Shinhan", "Nonghyeop", "Kakao"};
vector<Bank*> Bank_list;
vector<ATM*> ATM_list;
vector<Account*> Account_list;
vector<User*> User_list;

void Set_Initial_Condition(){
    // BANK
    cout << "Process 01 : Initializing Bank Information" << '\n';
    cout << "Give the Bank's name. If you're done, input 0" << '\n';
    while(1){
        string bank_name;
        cin >> bank_name;
        if(bank_name == "0") break;
        Bank_list.push_back(new Bank(bank_name));
    }
    cout << "\n\n";
    // USER
    cout << "Process 02 : Initializing User Information" << '\n';
    cout << "Give the User's name. If you're done, input 0" << '\n';
    int index = 1;
    while(1){
        cout << "-----" << index << "th user input-----" << '\n';
        cout << "User's name : ";
        string name;
        cin >> name;
        if(name == "0") break;
        User_list.push_back(new User(name));
        index++;
        cout<<"---------------------------";
        cout<<'\n';
    }
    cout << "\n\n";
    // ACCOUNT
    cout << "Process 03 : Initializing Account Information" << '\n';
    cout << "Give the account's information. If you're done, input 0" << '\n';
    index = 1;
    while(1){
        cout << "-----" << index << "th account input-----" << '\n';
        cout << "Select the Bank the account belongs to. Here are the options of the banks." << '\n';
        for(int i = 0; i<Bank_list.size(); i++){
            cout << "[" << i << "]" << Bank_list[i]->get_bank_name() << "Bank" << '\n';
        }
        int bank_index;
        cin >> bank_index;
        cout << Bank_list[bank_index]->get_bank_name() << "Bank Selected" << '\n';
        //user name input
        cout << "User\'s name of the account : ";
        string user_name;
        cin >> user_name;
        cout << "This account\'s user name is " << user_name << '\n';
        //account number input
        cout << "What is the number of this account? The format should be 000-000-000000 : ";
        string account_number;
        cin >> account_number;
        cout << "This account\'s number is "<<account_number<<"\n";
        // cash input
        cout << "How much money would this account have? Only integer is allowed : ";
        long long balance;
        cin >> balance;
        cout << "This account will have " << balance << " won\n";
        // input
        Account_list.push_back(new Account(Bank_list[bank_index], user_name, account_number, balance));
        for(int i = 0; i<User_list.size(); i++){
            if(user_name == User_list[i]->get_user_name()) User_list[i]->attach(Account_list[index-1]);
        }
        index++;
        cout<<"---------------------------";
        cout<<'\n';
    }
    cout << "\n\n";
    // print Account
    for(int i = 0; i<Account_list.size(); i++){
        Account* tmp_account(Account_list[i]);
        cout<<"-------------"<<i+1<<"th ATM info-------------\n";
        cout<<"|Bank: "<<tmp_account->get_Bank_name()<<"\n";
        cout<<"|user name: "<<tmp_account->get_user_name()<<"\n";
        cout<<"|Account number: "<<tmp_account->get_account_number()<<'\n';
        cout<<"|Available Funds: KRW "<<tmp_account->get_cash()<<"\n";
        cout<<"--------------------------------------\n";
        cout<<'\n';
    }
    // ATM
    cout << "Process 04 : Initializing ATM Information" << '\n';
    cout << "This is ATM input section. If you're done, input 0" << '\n';
    index = 1;
    while(1){
        cout<<"-----"<<index<<"th ATM input-----\n";
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
            cout<<Bank_list[i]->get_bank_name();
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
        //bank_type(Single/Multiple) input
        cout<<"ATM type(Single/Multiple): ";
        string bank_type;
        cin>>bank_type;
        bool IsSingle;
        if(bank_type[0] == 'S' || bank_type[0] == 's') IsSingle = true;
        else IsSingle = false;
        cout<<"This ATM will be "<<bank_type<<'\n';
        //cash input
        int arr[4] = {1000, 5000, 10000, 50000};
        vector<int> cash;
        for(int i = 0; i< 4; i++){
            cout<<"How much "<<arr[i]<<" won cash will this ATM have: ";
            int NumofCash;
            cin>>NumofCash;
            cash.push_back(NumofCash);
        }
        // input
        ATM_list.push_back(new ATM(IsBilingual, Bank_list[bank_index], IsSingle, cash));
        //cash info
        cout<<"Current cash amount of this ATM:"<<'\n';
        ATM_list[index-1]->get_cash();
        index++;
        cout<<"-----------------------";
        cout<<'\n';
    }
    cout<<"\n\n";
    //print ATM
    for(int i = 0; i<ATM_list.size(); i++){
        ATM* tmp_atm(ATM_list[i]);
        cout<<"-------------"<<i+1<<"th ATM info-------------\n";
        cout<<"|Bank: "<<tmp_atm->get_bank_name()<<"\n";
        cout<<"|ATM Language Option: "<<((tmp_atm->get_language_option())?"Bilingual":"Unilingual")<<"\n";
        cout<<"|ATM type: "<<((tmp_atm->get_ATM_type()) ? "Single" : "Multiple")<<"\n";
        cout<<"|ATM unique number: "<<tmp_atm->get_unique_number()<<"\n";
        cout<<"|Remaining cash: \n";
        tmp_atm->get_cash();
        cout<<"--------------------------------------\n";
        cout<<'\n';
    }
    cout<<"\n\n";
}

int before_session(){
    cout<<"-------------------------------------------\n";
    cout<<"\n";
    for(int i = 0; i<ATM_list.size(); i++){
        string language_type = ATM_list[i]->get_ATM_type() ? "Single" : "Multiple";
        cout<<i+1<<". ATM "<<i+1<<" ("<<ATM_list[i]->get_bank_name()<<", "<<language_type<<")";
        cout<<'\n';
    }
    cout<<"Choose the ATM which you will use. Input a number : ";
    int index;
    cin>>index;
    
    return index;

}

void display_everything(){
    int i;
    cout<<"----------------------------\nAll ATMs\' information: Remaining cash";
    for(i = 0; i<ATM_list.size(); i++){
        cout<<"ATM [SN: "<<ATM_list[i]->get_unique_number()<<"] remaining cash: "<<ATM_list[i]->get_total_cash();
        cout<<'\n';
    }
    cout<<"\n";
    cout<<"----------------------------\nAll accounts\' information: Remaining balance\n";
    for(i = 0; i<Account_list.size();i++){
        Account* tmp = Account_list[i];
        cout<<"Account [Bank: "<<tmp->get_Bank_name()<<", No: "<<tmp->get_account_number()<<", Owner: "<<tmp->get_user_name()<<"] balance: "<<tmp->get_cash();
        cout<<'\n';
    }
    cout<<"\n";
}

int main(){
    //Bank input
    Set_Initial_Condition();
    while(1){
        int ATM_index = before_session()-1;
        ATM* this_ATM = ATM_list[ATM_index];
        cout<<"This is ATM "<<ATM_index+1<<" session. Whenever you want to exit a session, please input \"exit\"";
        string x;
        cin>>x;
        bool IsEnglish = true;
        if(this_ATM->get_ATM_type()){
            cout<<"Which do you prefer, Engilsh or Korean? If you prefer Engilsh, input 1 if not, input 0 ";
            cin>>IsEnglish;
        }
        if(IsEnglish){ // 영어일 때
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           
        }
        else{ // 한국어일 때
            // some code
        }
    }
    display_everything();

    return 0;
}