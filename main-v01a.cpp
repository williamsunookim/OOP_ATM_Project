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

//#############
//####Bank#####
//#############
class Bank{
private:
    string bank_name;
    vector<Account*> Account_list;
    
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

//one Account, one Bank
//#############
//###Account###
//#############
class Account{
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
Account::Account(Bank* aBank, string user_name, string account_number, long long cash){
    bank = aBank;
    NameofUser = user_name;
    NumofAccount = account_number;
    AmountofCash = cash;
}
Bank* Account::get_Bank(){
    return bank;
}
string Account::get_Bank_name(){
    return bank->get_bank_name();
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

class Fee{
protected:
    int NonPrimaryDepositFee;           // 다른 은행 예금 수수료 (REQ 1.8)
    int PrimaryDepositFee;              // 같은 은행 예금 수수료
    int PrimaryWithdrawalFee;           // 같은 은행 출금 수수료 (REQ 1.8)
    int NonPrimaryWithDrawalFee;        // 다른 은행 출금 수수료 (REQ 1.8)
    int PrimarytoPrimaryFee;            // 같은 은행끼리 송금 수수료 (REQ 1.8)
    int NonPrimarytoPrimaryFee;         // 같은, 다른 은행끼리 송금 수수료 (REQ 1.8)
    int NonPrimarytoNonPrimaryFee;      // 다른 은행끼리 송금 수수료 (REQ 1.8)
    int CashTransferFee;                // 무통장 송금 수수료 (REQ 1.8)
public:
    Fee(int non_primary_deposit, int primary_deposit, int primary_withdrawal, int non_primary_withdrawal,
    int primary_transfer, int primary_to_non_transfer, int non_primary_transfer, int cash_transfer);   
};
Fee::Fee(int non_primary_deposit, int primary_deposit, int primary_withdrawal, int non_primary_withdrawal,
    int primary_transfer, int primary_to_non_transfer, int non_primary_transfer, int cash_transfer){
    this->NonPrimaryDepositFee = non_primary_deposit;
    this->PrimaryDepositFee = primary_deposit;
    this->PrimaryWithdrawalFee = primary_withdrawal;
    this->NonPrimaryWithDrawalFee = non_primary_withdrawal;
    this->PrimarytoPrimaryFee = primary_transfer;
    this->NonPrimarytoPrimaryFee = primary_to_non_transfer;
    this->NonPrimarytoNonPrimaryFee = non_primary_transfer;
    this->CashTransferFee = cash_transfer;
}
//#############
//#####Atm#####
//#############

class ATM{
private:
    //ATM 선언 때 선언되는 변수들
    bool isbilingual;   //isbilingual은 이 atm이 두 가지의 언어를 지원하는지 알려줌 -> false면 영어만 언어 지원 (REQ 1.3)
    bool isSingle;      //isSingle은 이 atm이 하나의 은행만 가능한지 두 가지 다 가능한지 알려줌 -> true이면 한 개만 됨 (REQ 1.2)

    Bank* bank;
    static int order_number;
    string unique_number = "";          // ATM마다 다른 고유 식별 번호, 6자리  
    string transaction_history = "";    //거래 내역을 담는 곳
    
    int AmountOfCash[4];                        // 1000원, 5000원, 10000원, 50000원

    //ATM 호출 때 선언되는 변수들
    int language_type;                          // 1이면 영어, 2이면 한국어 (REQ 1.3)


public:
    ATM(const bool language_option, Bank* bank_info, bool ATM_type, vector<int>& initial_cash);

    bool get_language_option();
    bool get_language(); // true면 영어라는 뜻, false면 한국어라는 뜻
    bool get_ATM_type(); // isSinlge을 반환
    string get_bank_name();
    string get_unique_number();
    int get_existing_cash();
    void get_cash();
};
int ATM::order_number = 0;
ATM::ATM(const bool language_option, Bank* bank_info, bool ATM_type, int &initial_cash){
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
int ATM::get_existing_cash(){
    int bill_value[4] = {1000, 5000, 10000, 50000};
    int existing_cash = 0;
    for(int i=0; i<4; i++) existing_cash += AmountOfCash[i] * bill_value[i];
    return existing_cash;
}
void ATM::get_cash(){
    cout<<"1000 won : "<<AmountOfCash[0]<<'\n';
    cout<<"5000 won: "<<AmountOfCash[1]<<'\n';
    cout<<"10000 won: "<<AmountOfCash[2]<<'\n';
    cout<<"50000 won: "<<AmountOfCash[3]<<'\n';
}


void Initial_Condition_Input(vector<Bank*>& Bank_list, vector<ATM*>& ATM_list, vector<Account*>& Account_list, vector<User*>& User_list){
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
    cout<<"This is ATM input section. If you're done, input 0 or \"zero\"\n";
    int index = 1;
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
    //User input
    cout<<"This is User input session. If you're done, input 0 or \"zero\"\n";
    index = 1;
    while(1){
        cout<<"-----"<<index<<"th user input-----\n";
        cout<<"Input the user name: ";
        string name;
        cin>>name;
        if(name=="0" || name=="zero"){
            break;
        }
        User_list.push_back(new User(name));
        index++;
        cout<<"---------------------------";
        cout<<'\n';
    }
    //Account input
    cout<<"This is Account input session. If you're done, input 0 or \"zero\"\n";
    index = 1;
    while(1){
        cout<<"-----"<<index<<"th account input-----\n";
        cout<<"Current banks list:\n";
        for(int i = 0; i<Bank_list.size(); i++){
            cout<<Bank_list[i]->get_bank_name();
            cout<<"\n";
        }
        cout<<"Which Bank does this account use? : ";
        string bank_name;
        cin>>bank_name;
        if(bank_name=="0" || bank_name == "zero"){
            break;
        }
        int bank_index = -1;
        try
        {
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
        //user name input
        cout<<"What is the user\'s name of this account?: ";
        string user_name;
        cin>>user_name;
        cout<<"This account\'s user name is "<<user_name<<'\n';
        //account number input
        cout<<"What is the number of this account? The format should be 000-000-000000 : ";
        string account_number;
        cin>>account_number;
        cout<<"This account\'s number is "<<account_number<<"\n";
        // cash input
        cout<<"How much money would this account have? Only integer is allowed : ";
        long long cash;
        cin>>cash;
        cout<<"This account will have "<<cash<<" won\n";
        //input
        Account_list.push_back(new Account(Bank_list[bank_index],user_name, account_number, cash));
        for(int i = 0; i<User_list.size(); i++){
            if(user_name == User_list[i]->get_user_name()){
                User_list[i]->attach(Account_list[index-1]);
            }
        }
        index++;
        cout<<"---------------------------";
        cout<<'\n';
    }
    cout<<"\n\n";
    //print Account
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

}

int main(){
    // test case: Kookmin, Woori, Hana, Shinhan, Nonghyeop, Kakao
    // Bank input
    string bank_names[6] = {"Kookmin", "Woori", "Hana", "Shinhan", "Nonghyeop", "Kakao"};
    vector<Bank*> Bank_list;
    map<int, ATM*> ATM_list;
    map<string, Account*> Account_list;
    vector<User*> User_list;

    for(auto bank_name_ : bank_names){
        Bank* bank_ = new Bank(bank_name_);
        Bank_list.push_back(bank_);
    }
    
    // Initalizing Account Info
    Account("Kakao", "David", "111-111-111111", 5000);
    Account("Daegu", "Jane", "222-222-222222", 5000);
    Account("Kakao", "Kate", "333-333-333333", 5000);

    // Initializing ATM Info
    ATM("Kakao", 111111, false, false, {5, 0, 0, 0});
    ATM("Daegu", 222222, true, true, {5, 0, 0, 0});
    ATM("Daegu", 333333, true, true, {5, 0, 0, 0});

    Fee(1000, 0, 1000, 2000, 2000, 3000, 4000, 5000);
    
    // Initial_Condition_Input(Bank_list, ATM_list, Account_list, User_list);
    


    return 0;
}