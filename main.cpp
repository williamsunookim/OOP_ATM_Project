#include <iostream>
#include <algorithm>
#include <string.h>
#include <vector>
#include <queue>
#include <map>

using namespace std;

//Forward declaration
class History;
class Account;
class Card;
class ATM;
class Bank;
class User;

//Classes declaration

class History{
    private:
        vector<string> transaction_history;
        queue<string> current_session_history;
    public:
        History();
        ~History();
        void add_history(string transaction);
        void add_current_history(string transaction);
        void update();
        void show_history();
        void reset_history();
};
History::History(){
    ;
}
History::~History(){
    ;
}
void History::add_history(string transaction){
    transaction_history.push_back(transaction);
}
void History::add_current_history(string transaction){
    current_session_history.push(transaction);
}
void History::update(){
    while(!current_session_history.empty()){
        string tmp = current_session_history.front();
        cout << tmp << '\n';
        current_session_history.pop();
        transaction_history.push_back(tmp);
    }
}
void History::show_history(){
    for(string line : transaction_history) cout << line << '\n';
}
void History::reset_history(){
    this->transaction_history.clear();
}
//#############
//####Bank#####
//#############
class Bank : public History{
private:
    vector<Account*> Account_list_of_Bank;
    string bank_name;
public:
    Bank(string name);
    ~Bank();
    string get_bank_name();
    Account* get_account_by_index(int index);
};
Bank::Bank(string name){
    this->bank_name = name;
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
class Account : public History{
private:
    Bank* bank;
    string NameofUser;
    string NumofAccount;
    long long AmountofCash;
    string password;
public:
    Account(Bank* aBank , string user_name, string account_number, long long cash, string inputted_password);
    ~Account();
    Bank* get_Bank();
    string get_Bank_name();
    string get_user_name();
    string get_account_number();
    long long get_balance();
    string get_password();
    void add_cash(long long cash);
};
Account::Account(Bank* aBank, string user_name, string account_number, long long cash, string inputted_password){
    bank = aBank;
    NameofUser = user_name;
    NumofAccount = account_number;
    AmountofCash = cash;
    password = inputted_password;
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
long long Account::get_balance(){
    return AmountofCash;
}
string Account::get_account_number(){
    return NumofAccount;
}
string Account::get_password(){
    return password;
}
void Account::add_cash(long long cash){
    AmountofCash+=cash;
}

//##############
//#####User#####
//##############
class User : public History{
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
class Card : public History{
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
//#####ATM#####
//#############
class ATM  : public History{
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
    ATM(const bool language_option, Bank* bank_info, bool ATM_type, int initial_cash[], string admin_card_number);

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
    /*
    void add_history(string history);
    void show_history();
    */
};
int ATM::order_number = 0;
ATM::ATM(const bool language_option, Bank* bank_info, bool ATM_type, int initial_cash[], string admin_card_number){
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
    if(money==1000) AmountOfCash[0] += NumofMoney;
    else if(money==5000) AmountOfCash[1] += NumofMoney;
    else if(money==10000) AmountOfCash[2] += NumofMoney;
    else if(money==50000) AmountOfCash[3] += NumofMoney;
}

int NonPrimaryDepositFee = 1000;            // 다른 은행 예금 수수료 (REQ 1.8)
int PrimaryDepositFee = 0;                  // 같은 은행 예금 수수료
int PrimaryWithdrawalFee = 1000;            // 같은 은행 출금 수수료 (REQ 1.8)
int NonPrimaryWithDrawalFee = 2000;         // 다른 은행 출금 수수료 (REQ 1.8)
int PrimarytoPrimaryFee = 2000;             // 같은 은행끼리 송금 수수료 (REQ 1.8)
int NonPrimarytoPrimaryFee = 3000;          // 같은, 다른 은행끼리 송금 수수료 (REQ 1.8)
int NonPrimarytoNonPrimaryFee = 4000;       // 다른 은행끼리 송금 수수료 (REQ 1.8)
int CashTransferFee = 5000;                 // 무통장 송금 수수료 (REQ 1.8)

vector<Bank*> Bank_list;
vector<ATM*> ATM_list;
vector<Account*> Account_list;
vector<User*> User_list;
map<string, Account*> Accounts_DB;
ATM* this_ATM;

void print(int situation);

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
        string admin_card_num;
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
    print(3001);
    for(i = 0; i<ATM_list.size(); i++){
        print(3002);
        cout << ATM_list[i]->get_unique_number() << "] ";
        print(3003);
        cout << ATM_list[i]->get_total_cash() << '\n';
    }
    cout << "\n";
    print(3004);
    for(i = 0; i<Account_list.size();i++){
        Account* tmp = Account_list[i];
        print(3005);
        cout << tmp->get_Bank_name();
        print(3006);
        cout << tmp->get_account_number();
        print(3007);
        cout << tmp->get_user_name();
        print(3008);
        cout << tmp->get_balance() << '\n';
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
            break;
        case 2:
            if(IsEnglish){
                cout << "------------ADMIN MODE------------\nPlease select a Menu.\n";
                cout << "[0] EXIT[1] Transaction History\n";
            }else{
                cout << "------------관리자 모드------------\n메뉴를 선택해 주세요.\n";
                cout << "[0] 나가기\n[1] 거래 기록\n";
            }
            break;
        case 3:
            if(IsEnglish) cout << "Wrong Input. Please try again : ";
            else cout << "잘못된 입력입니다. 다시 시도해 주세요 : ";
            break;
        case 4:
            if(IsEnglish) cout << "Please Enter Password : ";
            else cout << "비밀번호를 입력해 주세요 : ";
            break;
        case 5:
            if(IsEnglish) cout << "Password Incorrect! Please try again.\n";
            else cout << "비밀번호가 틀렸습니다. 다시 시도해 주세요.\n";
            break;
        case 6:
            if(IsEnglish){
                cout << "User identified!\nHow may I help you?\n";
                cout << "[0] Exit\n";
                cout << "[1] Deposit\n";
                cout << "[2] Withdrawal\n";
                cout << "[3] Transfer\n";
            }else{
                cout << "확인되었습니다!\n무엇을 도와드릴까요?\n";
                cout << "[0] 나가기\n";
                cout << "[1] 입금하기\n";
                cout << "[2] 출금하기\n";
                cout << "[3] 이체하기\n";
            }
            break;
        case 1001:
            if(IsEnglish) cout << "Exited From Option Selection.\n";
            else cout << "나가기 버튼을 선택하셨습니다.\n";
            break;
        case 1002:
            if(IsEnglish) cout << "[ERROR] Invalid Card.\n";
            else cout << "유효하지 않은 카드입니다.\n";
            break;
        case 1003:
            if(IsEnglish) cout << "[ERROR] This card is not able to use in this ATM.\n";
            else cout << "이 카드는 이 ATM에서 사용하실 수 없습니다.\n";
            break;
        case 1004:
            if(IsEnglish) cout << "[ERROR] Wrong password input for 3 times.\n";
            else cout << "비밀번호를 3회 잘못 입력하셨습니다.\n";
            break;
        case 1005:
            if(IsEnglish) cout << "[ERROR] Refused to pay fee.\n";
            else cout << "수수료 결제를 거부하셨습니다.\n";
            break;
        case 1006:
            if(IsEnglish) cout << "[ERROR] You inserted too much cash/check.\n";
            else cout << "지폐/수표를 제한 갯수보다 많이 넣으셨습니다.\n";
            break;
        case 1007:
            if(IsEnglish) cout << "[ERROR] Exceeded amount of available deposit attempt.\n";
            else cout << "3회 이상 출금하실 수 없습니다.\n";
            break;
        case 1008:
            if(IsEnglish) cout << "[ERROR] Not enough account balance.\n";
            else cout << "통장 잔액이 부족합니다.\n";
            break;
        case 1009:
            if(IsEnglish) cout << "[ERROR] Deposited wrong fee.\n";
            else cout << "수수료를 잘못 입금하셨습니다.\n";
            break;
        case 2000:
            if(IsEnglish) cout << "\n\nEnding ATM Session.\n\n";
            else cout << "\n\nATM 세션을 종료합니다.\n\n";
            break;
        case 3001:
            if(IsEnglish) cout << "----------------------------\nAll ATMs\' information: Remaining cash";
            else cout << "----------------------------\n모든 ATM의\' 정보: 잔여 현금 보유량";
            break;
        case 3002:
            if(IsEnglish) cout << "ATM [SN: ";
            else cout << "ATM [고유번호: ";
            break;
        case 3003:
            if(IsEnglish) cout << "Remaining Cash: ";
            else cout << "잔여 현금 보유량: ";
            break;
        case 3004:
            if(IsEnglish) cout << "----------------------------\nAll accounts\' information: Remaining balance\n";
            else cout << "----------------------------\n모든 계좌들의\' 정보: 통장 잔고\n";
            break;
        case 3005:
            if(IsEnglish) cout << "Account [";
            else cout << "계좌 [";
            break;
        case 3006:
            if(IsEnglish) cout << " Bank ";
            else cout << " 은행 ";
            break;
        case 3007:
            if(IsEnglish) cout << ", Owner : ";
            else cout << ", 예금주명 : ";
            break;
        case 3008:
            if(IsEnglish) cout << "] balance: ";
            else cout << "] 통장 잔고: ";
            break;
        case 10001:
            if(IsEnglish) cout << "You chose deposit\n";
            else cout << "입금 메뉴를 선택하셨습니다\n";
            break;
        case 10002:
            if(IsEnglish) cout << "There is an deposit fee of ";
            else cout << "출금 수수료 ";
            break;
        case 10003:
            if(IsEnglish){
                cout << " KRW. You have to deposit additional cash.\n";
                cout << "Will you continue?\n[0] NO\t[1] YES\n";
            }else{
                cout << "원을 추가로 입금해 주세요.\n";
                cout << "계속하시겠습니까?\n[0] 네\t[1] 아니오\n";
            }
            break;
        case 10004:
            if(IsEnglish) cout << "You added additional cash(1000 won, 1)\n";
            else cout << "추가로 1000원 1장을 입금하셨습니다.\n";
            break;
        case 10005:
            if(IsEnglish) cout << " KRW is deposited to your account.\n";
            else cout << "원이 계좌로 입금되었습니다.\n";
            break;
        case 10006:
            if(IsEnglish) cout << "your account's remaining balance is : ";
            else cout << "현재 계좌의 잔액은 ";
            break;
        case 10007:
            if(IsEnglish) cout << " KRW\n";
            else cout << "원 입니다.\n";
            break;
        case 20001:
            if(IsEnglish) cout << "You chose withdrawal.\n";
            else cout << "출금 메뉴를 선택하셨습니다.\n";
            break;
        case 20002:
            if(IsEnglish) cout << "Please type the amount of cash to withdrawal : ";
            else cout << "출금할 금액을 입력해 주세요 : ";
            break;
        case 20003:
            if(IsEnglish) cout << "There's not enough balance in your account. Please try again : ";
            else cout << "통장에 잔액이 충분하지 않습니다. 다시 시도해 주세요 : ";
            break;
        case 20004:
            if(IsEnglish) cout << "The maximum amount of cash to withdraw in once is ";
            else cout << "한 번에 출금할 수 있는 최대 금액은 ";
            break;
        case 20005:
            if(IsEnglish) cout << " KRW. Please try again: ";
            else cout << "원 입니다. 다시 시도해 주세요 : ";
            break;
        case 20006:
            if(IsEnglish) cout << "A withdrawal fee of ";
            else cout << "출금 수수료 ";
            break;
        case 20007:
            if(IsEnglish){
                cout << " KRW will be taken from your account.\n";
                cout << "Will you continue to withdrawal? [Y]/[N] : ";
            }else{
                cout << "원이 계좌에서 결제됩니다.\n";
                cout << "출금을 계속 진행하시겠습니까? [Y]/[N] : ";
            }
            break;
        case 20008:
            if(IsEnglish) cout << "Not withdrawable amount. Please try again: ";
            else cout << "출금 불가능한 금액입니다. 다시 시도해 주세요 : ";
            break;
        case 30001:
            if(IsEnglish) cout << "Please choose transfer type.\n[0] EXIT\n[1] Cash transfer\n[2] Account Transfer\n";
            else cout << "이체 종류를 선택해 주세요.\n[0] 나가기\n[1] 현금 이체\n[2] 계좌 이체\n";
            break;
        case 30002:
            if(IsEnglish) cout << "Please input the destination acount number(XXX-XXX-XXXXXX) : ";
            else cout << "이체할 곳의 계좌번호를 입력해 주세요(XXX-XXX-XXXXXX) : ";
            break;
        case 30003:
            if(IsEnglish) cout << "Not Existing Account. Please try again (enter 0 to exit) : ";
            else cout << "존재하지 않는 계좌입니다. 다시 시도해 주세요 (0을 눌러 나가기) : ";
            break;
        case 30004:
            if(IsEnglish) cout << "Can't Transfer to itself. Please try another : ";
            else cout << "자기 자신한테 이체할 수 없습니다. 다시 시도해 주세요 : ";
            break;
        case 30005:
            if(IsEnglish) cout << "transferring to ";
            else cout << "다음 계좌로 이체를 진행합니다 : ";
            break;
        case 30006:
            if(IsEnglish) cout << " Bank | Owner : ";
            else cout << " 은행 | 예금주명 : ";
            break;
        case 30007:
            if(IsEnglish) cout << "A transfer fee of ";
            else cout << "이체 수수료 ";
            break;
        case 30008:
            if(IsEnglish){
                cout << " KRW will be deposited from your account.\n";
                cout << "Will you continue to Transfer? [0] NO [1] YES : ";
            }else{
                cout << "원이 계좌에서 출금됩니다.\n";
                cout << "이체를 계속 진행하시겠습니까? [0] 아니오 [1] 예 : ";
            }
            break;
        case 30009:
            if(IsEnglish) cout << "Please deposit the transfer fee (";
            else cout << "이체 수수료 ";
            break;
        case 30010:
            if(IsEnglish) cout << " KRW)\n";
            else cout << "원을 입금해 주세요.\n";
            break;
        case 30011:
            if(IsEnglish) cout << "Wrong amount deposited!\n";
            else cout << "틀린 금액이 입금되었습니다.\n";
            break;
        case 30012:
            if(IsEnglish) cout << "Input the source account number : ";
            else cout << "이체할 계좌번호를 입력해 주세요 : ";
            break;
        case 30013:
            if(IsEnglish) cout << "Input the amount of fund to be transferred : ";
            else cout << "이체할 금액을 입력해 주세요 : ";
            break;
        case 30014:
            if(IsEnglish) cout << "A transfer fee of ";
            else cout << "이체 수수료";
            break;
        case 30015:
            if(IsEnglish){
                cout << " KRW will be deposited from your account.\n";
                cout << "Will you continue to Transfer? [0] NO [1] YES : ";
            }else{
                cout << "원이 계좌에서 출금됩니다.\n";
                cout << "이체를 계속 진행하시겠습니까? [0] 아니오 [1] 예 : ";
            }
            break;
        case 30016:
            if(IsEnglish) cout << "Transferred ";
            break;
        case 30017:
            if(IsEnglish) cout << " KRW to ";
            else cout << "원을 ";
            break;
        case 30018:
            if(IsEnglish) cout << " Bank | Owner : ";
            else cout << " 은행 | 예금주명 : ";
            break;
        case 30019:
            if(IsEnglish) cout << "\nRemaining Balance of My Account : ";
            else cout << "으로 이체했습니다.\n현재 내 계좌 잔액은 ";
            break;
        case 30020:
            if(IsEnglish) cout << " KRW\n\n";
            else cout << "원 입니다.\n\n";
            break;
    }
}

int Deposit(ATM *this_ATM){
    int CountCash = 0;
    int CountCheck = 0;
    long long tot_cash_deposited = 0;
    long long total_adding_cash = 0;
    cout << "Input either cash or money and the number of it (e.g., \"5000 2\", \"10000 3\") ";
    cout << "If you're done, input 0\n";
    while(1){
        string x1;
        long long money, NumofMoney;
        input_again_03:
        cin >> x1;
        if(x1 == "0") break;
        else if(x1 == "X"){
            display_everything();
            goto input_again_03;
        }
        money = stoll(x1);
        cin >> NumofMoney;
        if(money >= 100000){ // 수표일 때
            CountCheck += NumofMoney;
            if(CountCheck > this_ATM->LimitofCheck){
                cout << "The total amount of Check you gave : " << CountCheck << "\n";
                throw 1006;
            }
            //this_ATM->add_cash(total_adding_cash);
        }
        else if (money==1000 || money==5000 || money==10000 || money==50000){
            CountCash += NumofMoney;
            if(CountCash > this_ATM->LimitofCash){
                cout << "The total amount of Cash you gave: "<< CountCash << "\n";
                throw 1006;
            }
            this_ATM->add_cash(money, NumofMoney);
        }
        else{
            cout<<"Invalid Money type";
            cout<<"\n\n";
            continue;
        }
        total_adding_cash += money * NumofMoney;
    }
    return total_adding_cash;
}

void Session(bool* IsFinished){
    int ATM_index = before_session()-1;
    this_ATM = ATM_list[ATM_index];
    cout << "This is ATM " << ATM_index+1 << " session. Whenever you want to exit a session, please input 0\n";
    if(this_ATM->get_language_option()){
        cout << "Please Select a language.\n[0] EXIT\n[1] English\n[2] Korean" << '\n';
        int k;
        cin >> k;
        if(k == 0) throw 1001;
        IsEnglish = (k == 1) ? true : false;
    }
    while(1){       // transaction이 여러번 일어날 수 있기 때문
        print(1);   // insert card
        string card_num;
        input_again_10:
        cin >> card_num;
        int withdrawal_count = 0;
        if(card_num == this_ATM->get_admin_card_number()){
            //  ADMIN MODE
            print(2);
            string x;
            while(1){
                cin >> x;
                if(x == "0") return;
                else if(x == "1") break;
                else if(x == "X") display_everything();
                else print(3);
            }
            this_ATM->show_history();
        }
        else{
            if(card_num == "X"){
                display_everything();
                goto input_again_10;
            }
            // If Invalid Card :
            if(Accounts_DB.find(card_num) == Accounts_DB.end()) throw 1002;
            Account* this_account = Accounts_DB.at(card_num);
            bool is_primary_bank_account = (this_ATM->get_bank_name() == this_account->get_Bank_name()) ? true : false;
            // If Bank doesn't match (case : ATM only supports single bank)
            if(this_ATM->get_ATM_type() && !is_primary_bank_account) throw 1003;
            
            // Normal ATM session start
            int count_attempt=1;
            while(count_attempt<=4){
                if(count_attempt == 4) throw 1004;  // 4번째 시도일 경우
                string inputted_password;
                print(4);
                cin >> inputted_password;
                if(inputted_password == "X"){
                    display_everything();
                    continue;
                }else if(inputted_password != this_account->get_password()){
                    print(5);
                    count_attempt++;
                    continue;
                }else break;
            }
            print(6);
            string transaction_number;
            transaction_re_input: // goto로 돌아오는 부분
            cin >> transaction_number;
            if(transaction_number=="0"){
                *IsFinished = true;
                return;
            }
            else if(transaction_number=="1"){
                print(10001);
                int total_adding_cash = Deposit(this_ATM);
                int deposit_fee = (is_primary_bank_account) ? (PrimaryDepositFee) : (NonPrimaryDepositFee);
                print(10002);
                cout << deposit_fee;
                print(10003);
                cout << deposit_fee;
                string deposit_option;
                while(1){
                    cin >> deposit_option;
                    if(deposit_option == "0") throw 1005; // 수수료 안 내겠다
                    else if(deposit_option == "1"){
                        if(deposit_fee==1000) print(10004);
                        break;
                    }
                    else if(deposit_option == "X") display_everything();
                    else print(3);
                }
                this_ATM->add_cash(1000, 1); // 수수료 추가 납입
                this_account->add_cash(total_adding_cash);
                string local_history = "";
                string tmp = ("[Transaction ID: " + to_string(++unique_indentifier) + "] Deposited " + to_string(total_adding_cash) + " won to Card[ID: "+ this_account->get_account_number()+"]");
                local_history += tmp;
                this_ATM->add_current_history(local_history);
                this_account->add_history(local_history);
                cout << total_adding_cash;
                print(10005);
                print(10006);
                cout << this_account->get_balance();
                print(10007);
                break;
            }
            else if(transaction_number=="2"){ // withdrawal
                print(20001);
                withdrawal_count++;
                int LimitAmountCash = 500000; // 한 번 transaction당 최대 출금 금액
                if(withdrawal_count==4) throw 1007; // 출금 횟수 초과 예외 처리
                print(20002);
                string x;
                int withdrawal_fee = (is_primary_bank_account) ? PrimaryWithdrawalFee : NonPrimaryWithDrawalFee;
                while(1){
                    cin >> x;
                    //수수료를 포함한 출금 금액
                    if(this_account->get_balance() < stoll(x)+withdrawal_fee) print(20003);
                    else if(stoll(x)>LimitAmountCash){
                        print(20004);
                        cout << LimitAmountCash;
                        print(20005);
                    }else if(stoll(x)%1000!=0) print(20008);
                    else if(x == "X") display_everything();
                    else break;
                }
                long long withdrawal_cash_amount = stoll(x);
                // 수수료 출금
                print(20006);
                cout << withdrawal_fee;
                print(20007);
                string continue_option;
                while(1){
                    cin >> continue_option;
                    if(continue_option != "Y" && continue_option != "N") print(3);
                    else if(continue_option == "X") display_everything();
                    else break;
                }
                if(continue_option=="N") throw 1005;
                long long tmp_with_drawal_cash_amount = withdrawal_cash_amount;
                this_ATM->add_cash(50000, -1*(tmp_with_drawal_cash_amount/50000));
                tmp_with_drawal_cash_amount%=50000;
                this_ATM->add_cash(50000, -1*(tmp_with_drawal_cash_amount/10000));
                // 거래기록 업데이트
                this_account->add_cash(-1*(withdrawal_cash_amount+withdrawal_fee));
                string local_history = "";
                string tmp = ("[Transaction ID: " + to_string(++unique_indentifier) + "] Withdrawes " + to_string(withdrawal_cash_amount) + " KRW from Account[ID: "+ this_account->get_account_number()+"]");
                local_history += tmp;
                this_ATM->add_current_history(local_history);
                this_account->add_history(local_history);
                break;
            }
            else if(transaction_number=="3"){  // transfer  
                print(30001);
                string choice;
                while(1){
                    cin >> choice;
                    if(choice == "0") throw 1001;
                    else if(choice == "1" or choice == "2") break;
                    else if(transaction_number == "X") display_everything();
                    else print(3);
                }
                string destination;
                print(30002);
                while(1){
                    cin >> destination;
                    if(Accounts_DB.find(destination) ==  Accounts_DB.end()) print(30003);
                    else if(destination == this_account->get_account_number()) print(30004);
                    // else if(destination == "0") throw 1001;
                    else if(destination == "X") display_everything();
                    else break;
                }
                Account *destination_account = Accounts_DB.at(destination);
                print(30005);
                cout << destination << " [" << destination_account->get_Bank_name();
                print(30006);
                cout << destination_account->get_user_name() << "]\n";
                bool is_dest_primary_bank = (destination_account->get_Bank_name() == this_ATM->get_bank_name());
                int transfer_fee;
                int c = stoi(choice);
                switch(c){
                    case 1:
                    {
                        int inserted_cash = Deposit(this_ATM);
                        transfer_fee = CashTransferFee;
                        // 수수료 출금
                        print(30007);
                        cout << transfer_fee;
                        print(30008);
                        int continue_option;
                        while(1){
                            cin >> continue_option;
                            if(continue_option == 1) break;
                            else if(continue_option == 0) throw 1005;
                            else print(3);
                        }
                        print(30009);
                        cout << transfer_fee;
                        int deposited_fee = Deposit(this_ATM);
                        if(deposited_fee != transfer_fee){
                            print(30011);
                            throw 1009;
                        }
                        if(this_account->get_balance() < transfer_fee) throw 1008;
                        this_account->add_cash(-1*transfer_fee);
                        destination_account->add_cash(inserted_cash);
                        string local_history = "";
                        string tmp = ("[Transaction ID: " + to_string(++unique_indentifier) + "] Transfers " + to_string(inserted_cash) + " KRW from Account[ID: "+ this_account->get_account_number()+"] to Account[ID: "+ destination_account->get_account_number() +"]");
                        local_history += tmp;
                        this_ATM->add_current_history(local_history);
                        destination_account->add_history(local_history);
                        break;
                    }
                    case 2:
                    {
                        if(is_primary_bank_account && is_dest_primary_bank) transfer_fee = NonPrimarytoPrimaryFee;
                        else if(is_primary_bank_account || is_dest_primary_bank) transfer_fee = NonPrimarytoNonPrimaryFee;
                        else transfer_fee = NonPrimarytoNonPrimaryFee;
                        print(30012);
                        string source_account_num;
                        input_again_01:
                        cin >> source_account_num;
                        if(source_account_num == "X"){
                            display_everything();
                            goto input_again_01;
                        }
                        print(30013);
                        string x;
                        int transfer_amount;
                        input_again_02:
                        cin >> x;
                        if(x == "X"){
                            display_everything();
                            goto input_again_02;
                        }
                        transfer_amount = stoi(x);
                        if(transfer_amount > this_account->get_balance()) throw 1008;
                        print(30014);
                        cout << transfer_fee;
                        print(30015);
                        string continue_option;
                        while(1){
                            cin >> continue_option;
                            if(continue_option == "1") break;
                            else if(continue_option == "0") throw 1005;
                            else if(continue_option == "X") display_everything();
                            else print(3);
                        }
                        if(this_account->get_balance() < transfer_fee) throw 1008;
                        this_account->add_cash(-1*transfer_fee);
                        string local_history = ("[Transaction ID: " + to_string(++unique_indentifier) + "] Pays " + to_string(transfer_fee) + " KRW from Account[ID: "+ this_account->get_account_number()+"] for Transfer");
                        this_account->add_history(local_history);
                        this_ATM->add_history(local_history);
                        this_account->add_cash(-1*transfer_amount);
                        destination_account->add_cash(transfer_amount);
                        local_history = ("[Transaction ID: " + to_string(++unique_indentifier) + "] Transfers " + to_string(transfer_amount) + " KRW from Account[ID: "+ this_account->get_account_number()+"] to Account[ID: "+ destination_account->get_account_number() +"]");
                        this_ATM->add_current_history(local_history);
                        this_account->add_history(local_history);
                        destination_account->add_history(local_history);
                        print(30016);
                        cout << transfer_amount;
                        print(30017);
                        cout << destination << " [" << destination_account->get_Bank_name();
                        print(30018);
                        cout << destination_account->get_user_name();
                        print(30019);
                        cout << this_account->get_balance();
                        print(30020);
                        break;
                    }
                }
                break;
            }else{
                if(transaction_number == "X") display_everything();
                else print(3);
                goto transaction_re_input;
            }
        }   
    }
}

int main(){
    //Set_Initial_Condition();
    //input 생략법
    Bank_list.push_back(new Bank("Kakao"));
    Bank_list.push_back(new Bank("Daegu"));
    int arr_1[4] = {5, 0, 0, 0}; 
    int arr_2[4] = {0, 1, 0, 0}; 
    int arr_3[4] = {0, 1, 0, 0}; 
    ATM_list.push_back(new ATM(false, Bank_list[0], true, arr_1, "1"));
    ATM_list.push_back(new ATM(true, Bank_list[1], false, arr_2, "1"));
    ATM_list.push_back(new ATM(true, Bank_list[1], false, arr_3, "1"));
    User_list.push_back(new User("David"));
    User_list.push_back(new User("Jane"));
    User_list.push_back(new User("Kate"));
    Account_list.push_back(new Account(Bank_list[0], "David", "111-111-111111", 5000, "1"));
    Account_list.push_back(new Account(Bank_list[1], "Jane", "222-222-222222", 5000, "1"));
    Account_list.push_back(new Account(Bank_list[0], "Kate", "333-333-333333", 5000, "1"));
    Accounts_DB["111-111-111111"] = Account_list[0];
    Accounts_DB["222-222-222222"] = Account_list[1];
    Accounts_DB["333-333-333333"] = Account_list[2];   

    bool IsFinished = false;
    while(1){
        try{
            Session(&IsFinished);
            if(IsFinished) break;
        }
        catch(int error_code){
            print(error_code);
        }
        print(2000);
        this_ATM->update();
        display_everything();
        cout << "\n\n";
    }
    
    return 0;
}