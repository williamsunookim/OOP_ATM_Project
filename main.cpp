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
class User;


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
    vector<Account*> Account_list_of_Bank;
    string bank_name;

public:
    Bank(string name);
    string get_bank_name();
    int find_index_of_Account(string Account_number);
    Account* get_account_by_index(int index);
};
Bank::Bank(string name) : FinancialEntity(name){
    bank_name = name;
}
string Bank::get_bank_name(){
    return bank_name;
}
Account* Bank::get_account_by_index(int index){
    return Account_list_of_Bank[index];
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
    string password;
    string transaction_history = "";

public:
    Account(Bank* aBank , string user_name, string account_number, long long cash, string inputted_password);
    Bank* get_Bank();
    string get_Bank_name();
    string get_user_name();
    string get_account_number();
    long long get_balance();
    string get_password();
    void add_cash(long long cash);
    void add_history(string history);
};
Account::Account(Bank* aBank, string user_name, string account_number, long long cash, string inputted_password) : FinancialEntity(aBank->get_bank_name()){
    bank = aBank;
    NameofUser = user_name;
    NumofAccount = account_number;
    AmountofCash = cash;
    password = inputted_password;
}
Bank* Account::get_Bank(){
    return bank;
}
string Account::get_user_name(){
    return NameofUser;
}
long long Account::get_balance(){
    return AmountofCash;
}
string Account::get_account_number(){
    return NumofAccount;
}
int Bank::find_index_of_Account(string Account_number){
    for(int i = 0; i<Account_list_of_Bank.size(); i++){
        if(Account_list_of_Bank[i]->get_account_number() == Account_number) return i;
    }
    return -1;
}
string Account::get_password(){
    return password;
}
void Account::add_cash(long long cash){
    AmountofCash+=cash;
}
void Account::add_history(string history){
    transaction_history+=history;
}


//##############
//#####User#####
//##############
class User{
private:
    vector<Account*> Account_list_of_User;
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
    Account_list_of_User.push_back(account);
}
string User::get_user_name(){
    return NameofUser;
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
    string admin_card_number = "";

    
    int AmountOfCash[4]; // 1000원, 5000원, 10000원, 50000원

    //ATM 호출 때 선언되는 변수들
    bool IsEnglish; // 1이면 영어, 2이면 한국어 (REQ 1.3)


public:
    ATM(const bool language_option, Bank* bank_info, bool ATM_type, int initial_cash[], int admin_card_number);

    const int NonPrimaryDepositFee = 1000; //다른 은행 예금 수수료 (REQ 1.8)
    const int PrimaryWithdrawalFee = 1000; //같은 은행 출금 수수료 (REQ 1.8)
    const int NonPrimaryWithDrawalFee = 2000; //다른 은행 출금 수수료 (REQ 1.8)
    const int PrimarytoPrimaryFee = 2000; // 같은 은행끼리 송금 수수료 (REQ 1.8)
    const int NonPrimarytoPrimaryFee = 3000; //같은, 다른 은행끼리 송금 수수료 (REQ 1.8)
    const int NonPrimarytoNonPrimaryFee = 4000; // 다른 은행끼리 송금 수수료 (REQ 1.8)
    const int CashTransferFee = 5000; //무통장 송금 수수료 (REQ 1.8)

    const int LimitofCash = 50;
    const int LimitofCheck = 30;

    const int once_withdrawal_limit = 500000;

    bool get_language_option();
    bool get_language(); // true면 영어라는 뜻, false면 한국어라는 뜻
    bool get_ATM_type(); // isSinlge을 반환
    string get_bank_name();
    string get_unique_number();
    void get_cash();
    long long get_total_cash();
    Bank* get_bank();
    string get_admin_card_number();
    void add_cash(int money, int NumofMoney);
    void add_history(string history);
};
int ATM::order_number = 0;
ATM::ATM(const bool language_option, Bank* bank_info, bool ATM_type, int initial_cash[], int admin_card_number) : FinancialEntity(bank_info->get_bank_name()){
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
    this->admin_card_number = admin_card_number;
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
    cout<<"1000 won : " << AmountOfCash[0]<<'\n';
    cout<<"5000 won: " << AmountOfCash[1]<<'\n';
    cout<<"10000 won: " << AmountOfCash[2]<<'\n';
    cout<<"50000 won: " << AmountOfCash[3]<<'\n';
}
long long ATM::get_total_cash(){
    return AmountOfCash[0]*1000 + AmountOfCash[1] * 5000 + AmountOfCash[2] * 10000 + AmountOfCash[3] * 50000;
}
Bank* ATM::get_bank(){
    return bank;
}
string ATM::get_admin_card_number(){
    return admin_card_number;
}
void ATM::add_cash(int money, int NumofMoney){
    if(money==1000){
        AmountOfCash[0] += NumofMoney;
    }
    else if(money==5000){
        AmountOfCash[1] += NumofMoney;
    }
    else if(money==10000){
        AmountOfCash[2] += NumofMoney;
    }
    else if(money==50000){
        AmountOfCash[3] += NumofMoney;
    }
}
void ATM::add_history(string history){
    transaction_history += history;
}


class Fee{
public:
    int NonPrimaryDepositFee;           // 다른 은행 예금 수수료 (REQ 1.8)
    int PrimaryDepositFee;              // 같은 은행 예금 수수료
    int PrimaryWithdrawalFee;           // 같은 은행 출금 수수료 (REQ 1.8)
    int NonPrimaryWithDrawalFee;        // 다른 은행 출금 수수료 (REQ 1.8)
    int PrimarytoPrimaryFee;            // 같은 은행끼리 송금 수수료 (REQ 1.8)
    int NonPrimarytoPrimaryFee;         // 같은, 다른 은행끼리 송금 수수료 (REQ 1.8)
    int NonPrimarytoNonPrimaryFee;      // 다른 은행끼리 송금 수수료 (REQ 1.8)
    int CashTransferFee;                // 무통장 송금 수수료 (REQ 1.8)
    Fee(){}
    void initialize_fee(int non_primary_deposit, int primary_deposit, int primary_withdrawal, int non_primary_withdrawal,
    int primary_transfer, int primary_to_non_transfer, int non_primary_transfer, int cash_transfer);   
};
void Fee::initialize_fee(int non_primary_deposit, int primary_deposit, int primary_withdrawal, int non_primary_withdrawal,
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

vector<Bank*> Bank_list;
vector<ATM*> ATM_list;
vector<Account*> Account_list;
vector<User*> User_list;
map<string, Account*> Accounts_DB;
Fee *fee = new Fee();

void Set_Initial_Condition(){

    // BANK
    cout << "Process 01 : Initializing Bank Information" << '\n';
    cout << "Write down the Bank's name. If you're done, input 0" << '\n';
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
        cout << index << "th User's name : ";
        string name;
        cin >> name;
        if(name == "0") break;
        User_list.push_back(new User(name));
        index++;
    }
    cout << "\n\n";
    // ACCOUNT
    cout << "Process 03 : Initializing Account Information" << '\n';
    cout << "Give the account's information. If you're done, input -1" << '\n';
    index = 1;
    while(1){
        cout << "-----" << index << "th account input-----" << '\n';
        cout << "Select the Bank the account belongs to. Here are the options of the banks." << '\n';
        for(int i = 0; i<Bank_list.size(); i++){
            cout << "[" << i << "] " << Bank_list[i]->get_bank_name() << " Bank" << '\n';
        }
        cout << "[-1] End Input" << '\n';
        int bank_index;
        cin >> bank_index;
        if(bank_index == -1) break;
        //user name input
        cout << "User\'s name of the account : ";
        string user_name;
        cin >> user_name;
        //account number input
        cout << "What is the number of this account? The format should be 000-000-000000 : ";
        string account_number;
        cin >> account_number;
        // cash input
        cout << "How much money would this account have? Only integer is allowed : ";
        long long balance;
        cin >> balance;
        cout << "What is the account's password? (6 digits) : ";
        string password;
        cin >> password;
        // input
        Account *account = new Account(Bank_list[bank_index], user_name, account_number, balance, password);
        Accounts_DB[account_number] = account;
        Account_list.push_back(account);
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
        cout<<"|Available Funds: KRW "<<tmp_account->get_balance()<<"\n";
        cout << "| Password : " << tmp_account->get_password() << '\n';
        cout<<"--------------------------------------\n";
        cout<<'\n';
    }

    // ATM
    cout << "Process 04 : Initializing ATM Information" << '\n';
    index = 1;
    while(1){
        cout << "-----" << index << "th ATM input-----" << '\n';
        //language_option(Unilingual/Bilingual) input
        cout << "Select the ATM language option. Bilingual[Y] / Unilingual[N] / End input[0] : ";
        string language_option;
        bool IsBilingual;
        while(1){
            cin >> language_option;
            if(language_option == "Y"){
                IsBilingual = true;
                break;
            }else if(language_option == "N"){
                IsBilingual = false;
                break;
            }else if(language_option == "0") break;
            else cout << "Wrong Input. Please try again : ";
        }
        if(language_option == "0") break;
        cout << "This ATM will be "<< ((IsBilingual) ? "Bilingual" : "Unilingual") << '\n';
        //Bank input
        cout << "Select the Primary Bank that the ATM will be using. Here are the options of the banks." << '\n';
        for(int i = 0; i<Bank_list.size(); i++){
            cout << "[" << i << "] " << Bank_list[i]->get_bank_name() << " Bank" << '\n';
        }
        int bank_index;
        cin >> bank_index;
        cout << "You chose " << Bank_list[bank_index]->get_bank_name() << " Bank" << '\n';
        //bank_type(Single/Multiple) input
        cout << "Select the ATM type. Multiple Bank[Y] / Single Bank[N] : ";
        string bank_type;
        bool IsSingle;
        while(1){
            cin >> bank_type;
            if(bank_type == "Y"){
                IsSingle = false;
                break;
            }else if(bank_type == "N"){
                IsSingle = true;
                break;
            }else cout << "Wrong Input. Please try again : ";
        }
        cout << "This ATM will be using " << ((IsSingle) ? "Single Banks" : "Multiple Banks") << '\n';
        //cash input
        int arr[4] = {1000, 5000, 10000, 50000};
        int cash[4];
        for(int i = 0; i< 4; i++){
            cout << "How much " << arr[i] << " won cash will this ATM have: ";
            cin >> cash[i];
        }
        cout << "The admin card number : ";
        int admin_card_num;
        cin >> admin_card_num;
        // input
        ATM_list.push_back(new ATM(IsBilingual, Bank_list[bank_index], IsSingle, cash, admin_card_num));
        //cash info
        cout << "Current cash amount of this ATM:" << '\n';
        ATM_list[index-1]->get_cash();
        index++;
        cout << "-----------------------";
        cout << '\n';
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

    // FEE
    cout << "Process 05 : Initializing Fee Information" << '\n';
}

int before_session(){
    cout << "-------------------------------------------\n";
    cout << "\n";
    for(int i = 0; i<ATM_list.size(); i++) cout << "[" << i+1 << "] ATM " << i+1 << " ("<<ATM_list[i]->get_bank_name() << ", supporting " << (ATM_list[i]->get_ATM_type() ? "Single" : "Multiple") << " language)" << '\n';
    cout << "Choose the ATM which you will use. Input a number : ";
    int index;
    cin >> index;
    return index;
}

void display_everything(){
    int i;
    cout << "----------------------------\nAll ATMs\' information: Remaining cash";
    for(i = 0; i<ATM_list.size(); i++){
        cout << "ATM [SN: " << ATM_list[i]->get_unique_number() << "] remaining cash: " << ATM_list[i]->get_total_cash();
        cout << '\n';
    }
    cout << "\n";
    cout << "----------------------------\nAll accounts\' information: Remaining balance\n";
    for(i = 0; i<Account_list.size();i++){
        Account* tmp = Account_list[i];
        cout << "Account [Bank: " << tmp->get_Bank_name() << ", No: " << tmp->get_account_number() << ", Owner: " << tmp->get_user_name() << "] balance: " << tmp->get_balance();
        cout << '\n';
    }
    cout << "\n";
}

int unique_indentifier = 0;
bool IsEnglish = true;

void print(int situation){
    switch(situation){
        case 1:
            if(IsEnglish) cout << "Please Insert Your Card.\nCard Number : ";
            else cout << "카드를 삽입해 주세요.\n카드 번호 : ";
    }
}

int Deposit(ATM *this_ATM, Account *this_account){
    int CountCash = 0;
    int CountCheck = 0;
    int tot_cash_deposited = 0;
    long long total_adding_cash = 0;
    cout << "Input either cash or money and the number of it (e.g., \"5000 2\", \"10000 3\") ";
    cout << "If you're done, input 0\n";
    while(1){
        long long money, NumofMoney;
        cin >> money;
        if(money == 0) break;
        cin >> NumofMoney;
        if(money >= 100000){ // 수표일 때
            CountCheck += NumofMoney;
            if(CountCheck > this_ATM->LimitofCheck){
                cout << "The total amount of Check you gave : " << CountCheck << "\n";
                CountCheck -= NumofMoney;
                continue;
            }
            if(this_ATM->get_bank_name() != this_account->get_Bank_name()){
                cout<<"The fee will be "<<this_ATM->NonPrimaryDepositFee<<"won\n";
                cout<<"Will you give fee? If yes, input 1. If no, input 0: ";
                bool Ispayed;
                cin >> Ispayed;
                if(!Ispayed){
                    cout<<"Abort transaction\n";
                    throw 5;
                }
            }
            this_account->add_cash(money * NumofMoney);
            total_adding_cash += money*NumofMoney;
            this_ATM->add_cash(1000, 1);
            
        }
        else if (money==1000 || money==5000 || money==10000 || money==50000){
            CountCash += NumofMoney;
            if(CountCash > this_ATM->LimitofCash){
                cout << "The total amount of Cash you gave: "<< CountCash << "\n";
                throw 6;
            }
            this_account->add_cash(money*NumofMoney);
            total_adding_cash+=money*NumofMoney;
            this_ATM->add_cash(money, NumofMoney);
        }
        else{
            cout<<"Invalid Money type";
            cout<<"\n\n";
            continue;
        }
    }
    return total_adding_cash;
}

void Session(bool* IsFinished){
    int ATM_index = before_session()-1;
    ATM* this_ATM = ATM_list[ATM_index];
    cout << "This is ATM " << ATM_index+1 << " session. Whenever you want to exit a session, please input 0";
    string x;
    cin >> x;
    if(this_ATM->get_language_option()){
        cout << "Please Select a language.\n[0] EXIT\n[1] English\n[2] Korean" << '\n';
        int k;
        cin >> k;
        if(k == 0) throw 1;
        IsEnglish = (k == 1) ? true : false;
    }
    while(1){       // transaction이 여러번 일어날 수 있기 때문
        print(1);   // insert card
        string card_num;
        cin >> card_num;
        int index_of_Account = this_ATM->get_bank()->find_index_of_Account(card_num);
        int withdrawal_count = 0;
        if(card_num == this_ATM->get_admin_card_number()){
            //activate admin mode
        }
        else{
            // If Invalid Card :
            if(Accounts_DB.find(card_num) == Accounts_DB.end()) throw 2;
            Account* this_account = Accounts_DB.at(card_num);
            bool is_primary_bank_account = this_ATM->get_bank_name() == this_account->get_Bank_name();
            // If Bank doesn't match (case : ATM only supports single bank)
            if(this_ATM->get_ATM_type() and !is_primary_bank_account) throw 3;
            
            // Normal ATM session start
            int count_attempt=1;
            while(count_attempt<=4){
                if(count_attempt == 4){// 4번째 시도 이면
                    cout << "Session aborted\n";
                    cout << "Card returned\n";
                    throw 4;
                }
                string inputted_password;
                cout << "Please Enter Password : ";
                cin >> inputted_password;
                if(inputted_password != this_account->get_password()){
                    cout << "Password Incorrect! Please try again (" << 3-count_attempt << " Attempts remaining)." << '\n';
                    count_attempt++;
                    continue;
                }else break;
            }
            cout << "User identified!\nHow may I help you?\n";
            cout << "[0] Exit\n";
            cout << "[1] Deposit\n";
            cout << "[2] Withdrawal\n";
            cout << "[3] Transfer\n";
            
            int transaction_number;
            transaction_re_input:
            cin >> transaction_number;
            switch(transaction_number){
                case 0:
                    throw 1;
                case 1:
                {
                    cout << "You chose deposit\n";
                    int total_adding_cash = Deposit(this_ATM, this_account);
                    string local_history = "";
                    string tmp = ("[Transaction ID: " + to_string(++unique_indentifier) + "] Deposited " + to_string(total_adding_cash) + " won to Card[ID: "+ this_account->get_account_number()+"]");
                    local_history += tmp;
                    this_ATM->add_history(local_history);
                    this_account->add_history(local_history);
                }
                case 2:
                {
                    // withdrawal
                    cout << "You chose withdrawal.\n";
                    withdrawal_count++;
                    if(withdrawal_count==4){
                        cout<<"Four withdrawal in one session is not allowed.\n";
                        cout<<"Session aborted\n";
                        throw 1007;
                    }
                    cout << "Please type the amount of cash to withdrawal : ";
                    int withdrawal_cash_amount;
                    while(1){
                        cin >> withdrawal_cash_amount;
                        if(this_account->get_balance() < withdrawal_cash_amount) cout << "There's not enough balance in your account. Please try again : ";
                        else break;
                    }
                    // 수수료 출금
                    int withdrawal_fee = (is_primary_bank_account) ? fee->PrimaryWithdrawalFee : fee->NonPrimaryWithDrawalFee;
                    cout << "A withdrawal fee of " << withdrawal_fee << " KRW will be deposited from your account.\n";
                    cout << "Will you continue to withdrawal? [Y]/[N] : ";
                    string continue_option;
                    while(1){
                        cin >> continue_option;
                        if(continue_option != "Y" and continue_option != "N") cout << "Wrong input. Please try again : ";
                        else break;
                    }
                    if(this_account->get_balance() < withdrawal_fee) throw 1008;
                    // 출금 옵션 선택
                    // 거래기록 업데이트
                    this_account->add_cash(-1*withdrawal_cash_amount);
                    string local_history = "";
                    string tmp = ("[Transaction ID: " + to_string(++unique_indentifier) + "] Withdrawes " + to_string(withdrawal_cash_amount) + " KRW from Account[ID: "+ this_account->get_account_number()+"]");
                    local_history += tmp;
                    this_ATM->add_history(local_history);
                    this_account->add_history(local_history);
                }
                case 3:
                    //transfer
                default:
                    cout << "Wrong input. Please try again : ";
                    goto transaction_re_input;
            }   
        }   
    }
}

int main(){
    Set_Initial_Condition();
    try{
        bool IsFinished = false;
        while(1){
            Session(&IsFinished);
            if(IsFinished) break;
        }
        display_everything();
    }
    catch(int error_code){
        switch(error_code){
            case 1001:
                // 메뉴 선택에서 종료 선택한 경우
                cout << "Exited From Option Selection. Ending ATM Session." << '\n';
                break;
            case 1002:
                // Invalid한 카드 삽입한 경우
                break;
            case 1003:
                // Single Bank일 때, 카드 은행 불일치하는 경우
                break;
            case 1004:
                // 비밀번호 3회 이상 틀린 경우
                break;
            case 1005:
                // 수수료 안 내겠다고 선택한 경우
                break;
            case 1006:
                // 지폐를 제한 개수보다 많이 넣은 경우
                break;
            case 1007:
                // 출금 횟수 초과한 경우
                break;
            case 1008:
                // 통장 잔액 부족한 경우
                break;
        }
    }
    return 0;
}