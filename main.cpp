#include <iostream>
#include <algorithm>
#include <string.h>
#include <vector> //쓸 지는 모르겠음

using namespace std;

//Forward declaration
class Account;
class ATM;
class Bank;


//Classes declaration
class User{
private:

public:

};

//one Account, one Bank
class Account{
private:
    Bank bank_info
    

public:

};

class Bank{
private:
    string bank_name;
public:
    Bank(string name);
    string get_bank_game();
};

Bank::Bank(string name){
    bank_name = name;
}
string Bank::get_bank_game(){
    return bank_name;
}

class ATM {
private:
    //ATM 선언 때 선언되는 변수들
    bool isbilingual; //isbilingual은 이 atm이 두 가지의 언어를 지원하는지 알려줌 -> false면 영어만 언어 지원 (REQ 1.3)
    bool isSingle; //isSingle은 이 atm이 하나의 은행만 가능한지 두 가지 다 가능한지 알려줌 -> true이면 한 개만 됨 (REQ 1.2)

    const int NonPrimaryDepositFee = 1000; //다른 은행 예금 수수료 (REQ 1.8)
    const int PrimaryWithdrawalFee = 1000; //같은 은행 출금 수수료 (REQ 1.8)
    const int NonPrimaryWithDrawalFee = 2000; //다른 은행 출금 수수료 (REQ 1.8)
    const int PrimarytoPrimaryFee = 2000; // 같은 은행끼리 송금 수수료 (REQ 1.8)
    const int NonPrimarytoPrimaryFee = 3000; //같은, 다른 은행끼리 송금 수수료 (REQ 1.8)
    const int NonPrimarytoNonPrimaryFee = 4000; // 다른 은행끼리 송금 수수료 (REQ 1.8)
    const int CashTransferFee = 5000; //무통장 송금 수수료 (REQ 1.8)
    
    int AmountOfCash;

    //ATM 호출 때 선언되는 변수들
    int language_type; // 1이면 영어, 2이면 한국어 (REQ 1.3)


public:
    ATM(const bool language_option, bool ATM_type, int cash);

    bool get_language(); // true면 영어라는 뜻, false면 한국어라는 뜻
    bool get_ATM_type(); // isSinlge을 반환

};
ATM::ATM(const bool language_option, bool ATM_type, int cash){
    isbilingual = language_option;
    isSingle = ATM_type;
    AmountOfCash = cash;
}
bool ATM::get_language(){
    if(!isbilingual) return true; // unilingual이면 영어만 지원함
    if(language_type == 1) return true;
    else if(language_type == 2) return false;
}
bool ATM::get_ATM_type(){
    return isSingle;
}


int main(){
    Bank* DaeguBank = new Bank("Daegu");
    Bank* KookMinBank = new Bank("Kookmin");
    Bank* WooriBank = new Bank("Woori");
    Bank* ShinHanBank = new Bank("ShinHan");
    Bank* NongHyupBank = new Bank("NonghHyup");

    return 0;
}