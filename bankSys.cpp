#include<bits/stdc++.h>
#include<fstream>
using namespace std;

int transId = 1, loanID = 1; //global variables.

int searchUserRecordbyAcc(char*); //General Non Class functions.
void addAdmins();
void UserOperations();
void AdminOperations();
void displayHeading();
void displayFrontPage();
void displayHeadingAdmin();
void displayHeadingUser();
void displayAdminOperations();
void displayUserOperations();

struct DATE   //For dob, transaction dating.
{
    int dd,mm,yy;
};

struct TIME
{
    int Sec, Min, Hour;
};
struct MoneyTransfer //For transaction history records.
{
    char receiverAcc[6];
    int transId;
    double amt;
    TIME time;
    DATE date;
};

struct MoneyReceival  //For transaction history records.
{
    char issuerAcc[6];
    int transId;
    double amt;
    TIME time;
    DATE date;
};

struct Loan
{
    char requesterAcc[6];
    double loanAmt;
    int loanId;
    int loanStatus; //Status = -1->unprocessed, 0->rejected, 1->approved
    char loanCategory[20];
    TIME time;
    DATE date;
};

class User//done
{
    char Firstname[10], Lastname[10], Acc_no[6],UserId[10],Password[10], Email[30];
    char AddedBy[10], Branch[20], MobileNo[11], City[20], State[20], Country[20] ;
    DATE dob;
    int countIncoming, countOutgoing, Credit_score;
    MoneyTransfer Transfer[100];
    MoneyReceival Received[100];
    double Balance;


    public:
        User()
        {}
        User(char* adminName)
        {
            system("cls");
            displayHeading();
            cout<<"Adding New Users:- \n\n";
            cout<<"First Name: ";
            cin>>Firstname;
            cout<<"Last Name: ";
            cin>>Lastname;
            cout<<"Account Number: ";
            cin>>Acc_no;
            cout<<"Date of Birth(dd/mm/yyyy): ";
            cin>>dob.dd;
            cin>>dob.mm;
            cin>>dob.yy;
            cout<<"Mobile No.: ";
            cin>>MobileNo;
            cout<<"Email-ID: ";
            cin>>Email;
            cout<<"City: ";
            cin>>City;
            cout<<"State: ";
            cin>>State;
            cout<<"Country: ";
            cin>>Country;
            cout<<"Branch: ";
            cin>>Branch;
            cout<<"User ID: ";
            cin>>UserId;
            cout<<"Password: ";
            cin>>Password;
            cout<<"Credit Score: ";
            cin>>Credit_score;
            strcpy(AddedBy, adminName);
            cout<<"Account Balance: ";
            cin>>Balance;
            countIncoming = 0;
            countOutgoing = 0;
        }
        bool check(char* id, char* pass)
        {
            if (strcmp(UserId,id)==0 && strcmp(Password,pass)==0)
                return 1;
            return 0;
        }
        char* getAccNo()
        {
            return Acc_no;
        }
        void update(char* newId, char* newPass)
        {
            strcpy(UserId, newId);
            strcpy(Password, newPass);
        }
        void incBalance(double amt)
        {
            Balance+=amt;
        }
        void viewAllInfo();
        void transaction(int);
        void receiveMoney(double amt);
        void requestLoan();
};

class Admin//done
{
    char adminId[10], adminPass[10], adminName[10];
    public:
        Admin() //Default constructor for empty objects to read file
        {}      //blocks into.
        Admin(char* id,char* pass,char* name)//Constructor to
        {                                    // initialize admins
            strcpy(adminId, id);
            strcpy(adminPass, pass);
            strcpy(adminName, name);
        }
        bool check(char* id, char* pass)
        {
            if (strcmp(adminId,id)==0 && strcmp(adminPass,pass)==0)
                return 1;
            return 0;
        }
        char* getName()
        {
            return this->adminName;
        }
        void update(char* newId, char* newPass)
        {
            strcpy(adminId,newId);
            strcpy(adminPass,newPass);
        }
        void viewUserRecordsbyAcc(char* acc);
        void viewAllRecords();
        void enterRecords();
        void checkLoans();
};
void Admin::viewUserRecordsbyAcc(char*acc)//done
{
    fstream f1;
    char ch;
    int key;
    bool flag = 0;

    f1.open("UserRecords.dat",ios::binary|ios::in);
    f1.seekg(0,ios::beg);

    system("cls");
    displayHeading();
    cout<<"USER RECORD:-\n\n";

    if(!f1)
    {
        cout<<"User Record Not Found\n";
        cout<<"Do You Wish To Add a New Record? (y/n) \n";
        cin>>ch;

        if(ch=='y')
        {
            flag=1;
            enterRecords();
            cout<<"Record Successfully Added\n";
        }
        f1.close();
        return ;
    }
    else
    {
        User user;
        while(1)
        {
            f1.read((char*)&user,sizeof(user));
            if(f1.eof())
                break;
            if(strcmp(user.getAccNo(),acc)==0)
            {
                f1.close();
                flag = 1;
                user.viewAllInfo();
                break;
            }
        }
    }
    if(!flag)
    {
        system("cls");
        f1.close();
        displayHeading();
        cout<<"Invalid Account Number \n\n\n";
        cout<<"Press Any Key To Return ";
        cin.ignore();
        getchar();
        return;
    }
    system("cls");
    displayHeading();
    cout<<"\nPress Any Key To Return ";
    cin.ignore();
    cin>>key;
    f1.close();
}
void Admin::viewAllRecords()//done
{
    fstream f1;
    int key,i=1;
    User user;
    f1.open("UserRecords.dat",ios::binary|ios::in);
    system("cls");
    displayHeading();
    cout<<"USER RECORDS:-\n\n";

    if(!f1)
        cout<<"No User Record Exists\n";
    else
    {
        while(1)
        {
            f1.read((char*)&user,sizeof(user));
            if(f1.eof())
                break;
            cout<<"Record "<<i<<":- \n";
            user.viewAllInfo();
            cout<<"\n\n";
            i++;
        }
    }
    cout<<"Press Any Key To Return ";
    cin.ignore();
    getchar();
    f1.close();
}
void Admin::enterRecords()//done
{
    fstream f1;
    char ch;
    f1.open("UserRecords.dat",ios::binary|ios::app);

    system("cls");
    displayHeading();
    cout<<"Adding New Users:-\n\n";
    do
    {
        User newUser(this->adminName);
        f1.write((char*)&newUser,sizeof(newUser));
        cout<<"\nRecord successfully added\n";
        cout<<"Want To Add More Records? (y/n) \n";
        cin>>ch;
    }while(ch=='y');
    f1.close();
}
void Admin::checkLoans()//done
{
    fstream f1,f2;
    char ans;
    int posUser, ch;
    User user;
    Loan loan;

    f1.open("Loans.dat",ios::out|ios::in|ios::binary);
    system("cls");
    displayHeading();
    cout<<"Loan Records:-\n\n";
    if(!f1)
    {
        cout<<"No Pending Loans\n";
        f1.close();
        cout<<"Press Any Key To Return\n";
        cin.ignore();
        getchar();
        return;
    }
    while(1)
    {
        system("cls");
        displayHeading();
        cout<<"Loan Records:-\n\n";
        f1.read((char*)&loan,sizeof(loan));
        if(f1.eof())
        {
            cout<<"No Pending Loan Records\n";
            break;
        }
        if(loan.loanStatus == -1)
        {
            cout<<"Loan Id: "<<loan.loanId<<endl;
            cout<<"Loan Requested By Account(Account Number): "<<loan.requesterAcc<<"\n";
            cout<<"Loan Amount: "<<loan.loanAmt<<"\n";
            cout<<"Loan Category: "<<loan.loanCategory<<"\n";
            cout<<"Loan Requested On Date: "<<loan.date.dd<<"/"<<loan.date.mm<<"/"<<loan.date.yy<<endl;
            cout<<"Loan Requested At Time: "<<loan.time.Hour<<":"<<loan.time.Min<<":"<<loan.time.Sec<<"\n\n";
            cout<<"Enter 1 If You Wish To See The Details Of The Account Requesting The Loan:-\n";
            cin>>ch;
            if(ch==1)
            {
                system("cls");
                displayHeading();
                this->viewUserRecordsbyAcc(loan.requesterAcc);
            }
            system("cls");
            displayHeading();
            cin.ignore();
            cout<<"Do You Wish To Approve The Loan? (y/n) ";
            cin>>ans;
            if(ans == 'y')
            {
                cout<<"\nLoan Approved \n";
                loan.loanStatus = 1;
                posUser = searchUserRecordbyAcc(loan.requesterAcc);
                f2.open("UserRecords.dat",ios::out|ios::in|ios::binary);
                f2.seekg(posUser,ios::beg);
                f2.read((char*)&user,sizeof(user));

                user.incBalance(loan.loanAmt);
                f2.seekp(posUser,ios::beg);
                f2.write((char*)&user,sizeof(user));
                f2.close();
                cin.ignore();
                getchar();
            }
            else
            {
                cout<<"\nLoan Rejected \n";
                loan.loanStatus = 0;
                cout<<"Press Any Key To View The Next Record ";
                cin.ignore();
                getchar();
            }
            f1.seekp(-sizeof(loan),ios::cur);
            f1.write((char*)&loan,sizeof(loan));
        }
    }
    cout<<"Press Any Key To Go Back ";
    cin.ignore();
    getchar();
    f1.close();
}
void User::viewAllInfo()//done
{
    system("cls");
    displayHeading();
    cout<<"User Record:-\n\n";
    cout<<"First Name: "<<Firstname;
    cout<<"\n";
    cout<<"Last Name: "<<Lastname;
    cout<<"\n";
    cout<<"Account Number: "<<Acc_no;
    cout<<"\n";
    cout<<"Date of Birth(dd/mm/yyyy): "<<dob.dd<<"/"<<dob.mm<<"/"<<dob.yy;
    cout<<"\n";
    cout<<"Mobile No.: "<<MobileNo<<"\n";
    cout<<"Email-ID: "<<Email<<"\n";
    cout<<"City: "<<City<<"\n";
    cout<<"State: "<<State<<"\n";
    cout<<"Country: "<<Country<<"\n";
    cout<<"Branch: "<<MobileNo<<"\n";
    cout<<"Credit Score: "<<Credit_score;
    cout<<"\n";
    cout<<"Added By(Admin Name): "<<AddedBy<<"\n \n";
    cout<<"Account Balance: "<<Balance;
    cout<<"\n\n";
    cout<<"The List of Incoming Transaction:-\n\n";
    if(countIncoming==0)
        cout<<"No Incoming Transaction\n\n";
    else
    {
        for(int i = 0; i<countIncoming;i++)
        {
            cout<<"Transaction Id: "<<Received[i].transId<<endl;
            cout<<"Issuing Account: "<<Received[i].issuerAcc<<endl;
            cout<<"Date Of Transaction: "<<Received[i].date.dd<<"/"<<Received[i].date.mm<<"/"<<Received[i].date.yy<<endl;
            cout<<"Time Of Transaction: "<<Received[i].time.Hour<<":"<<Received[i].time.Min<<":"<<Received[i].time.Sec<<endl;
            cout<<"Amount: "<<Received[i].amt<<"\n\n";
        }
    }
    cout<<"The List of Outgoing Transactions:-\n\n";
    if(countOutgoing==0)
        cout<<"No Outgoing Transaction\n";
    else
    {
        for(int i = 0; i<countOutgoing;i++)
        {
            cout<<"Transaction Id: "<<Transfer[i].transId<<endl;
            cout<<"Receiving Account: "<<Transfer[i].receiverAcc<<endl;
            cout<<"Date Of Transaction: "<<Transfer[i].date.dd<<"/"<<Transfer[i].date.mm<<"/"<<Transfer[i].date.yy<<endl;
            cout<<"Time Of Transaction: "<<Transfer[i].time.Hour<<":"<<Transfer[i].time.Min<<":"<<Transfer[i].time.Sec<<endl;
            cout<<"Amount: "<<Transfer[i].amt<<"\n\n";
        }
    }
    cout<<"\nPress Any Key To Go Back ";
    cin.ignore();
    getchar();
}

void User::receiveMoney(double amt)//done
{
    MoneyReceival received;
    time_t t = time(NULL);
	tm* timePtr = localtime(&t);

    Balance += amt;
    received.amt = amt;
    strcpy(received.issuerAcc,this->Acc_no);
    received.date.dd = timePtr->tm_mday;
    received.date.mm = timePtr->tm_mon;
    received.date.yy = timePtr->tm_year;
    received.time.Hour = timePtr->tm_hour;
    received.time.Min = timePtr->tm_min;
    received.time.Sec = timePtr->tm_sec;
    received.transId = transId;

    this->Received[countIncoming++] = received;
}
void User::transaction(int curPos)//done
{
    char acc[6];
    int pos;
    double amt;
    fstream f1;
    User user;
    time_t t = time(NULL);
	tm* timePtr = localtime(&t);

    system("cls");
    displayHeading();
    cout<<"Transaction:-\n\n";
    cout<<"Enter The Account Number You Wish To Transfer Money To: ";
    cin>>acc;
    pos = searchUserRecordbyAcc(acc);

    if(pos==-1)
    {
        cout<<"Invalid Account Number\n";
        cout<<"Press Any Key To Return ";
        cin.ignore();
        getchar();
        return;
    }
    cout<<"Enter The Amount You Wish To Transfer: ";
    cin>>amt;

    f1.open("UserRecords.dat",ios::out|ios::in|ios::binary);
    f1.seekg((pos)*sizeof(user),ios::beg);
    f1.read((char*)&user,sizeof(user));
    f1.seekp((pos)*sizeof(user),ios::beg);

    if(amt<=this->Balance)
    {
        Balance-=amt;
        user.receiveMoney(amt);
        f1.write((char*)&user,sizeof(user));

        MoneyTransfer transfer;

        f1.seekp(curPos, ios::beg);
        transfer.amt = amt;
        strcpy(transfer.receiverAcc, acc);
        transfer.transId = transId;
        transId++;

        transfer.date.dd = timePtr->tm_mday;
        transfer.date.mm = timePtr->tm_mon;
        transfer.date.yy = timePtr->tm_year;
        transfer.time.Hour = timePtr->tm_hour;
        transfer.time.Min = timePtr->tm_min;
        transfer.time.Sec = timePtr->tm_sec;
        f1.write((char*)&(*this),sizeof(User));
        this->Transfer[countOutgoing++] = transfer;

        cout<<"\n\nTransaction Successful\n";
    }
    else
        cout<<"\n\nInsufficient Account Balance\n";
    cout<<"Press Any Key To Return ";
    cin.ignore();
    getchar();
    f1.close();
}

void User::requestLoan()//done
{
    Loan loan;
    fstream f1;
    time_t t = time(NULL);
	tm* timePtr = localtime(&t);

    f1.open("Loans.dat",ios::app|ios::binary);
    system("cls");
    displayHeading();
    cout<<"Loan Request:-\n\n";
    cout<<"Enter The Purpose Of The Loan: ";
    cin>>loan.loanCategory;
    cout<<"Enter The Amount Of The Loan: ";
    cin>>loan.loanAmt;

    loan.loanId = loanID;
    loanID++;
    loan.loanStatus = -1;
    strcpy(loan.requesterAcc, this->Acc_no);
    loan.date.dd = timePtr->tm_mday;
    loan.date.mm = timePtr->tm_mon;
    loan.date.yy = timePtr->tm_year;
    loan.time.Hour = timePtr->tm_hour;
    loan.time.Min = timePtr->tm_min;
    loan.time.Sec = timePtr->tm_sec;

    cout<<"\n\nLoan Successfully Requested\n";
    f1.seekp(0,ios::end);
    f1.write((char*)&loan,sizeof(loan));
    f1.close();
    cout<<"Press Any Key To Return ";
    cin.ignore();
    getchar();
}
void AdminOperations()//done
{
    char id[10], pass[10], newId[10], newPass[10],acc[6];
    fstream f1;
    char ans;
    bool flag = 0;
    Admin admin, newAdmin;
    int pos = 0; //start index of the admin in the file.

    system("cls");
    displayHeadingAdmin();

    f1.open("Admins.dat",ios::out|ios::in|ios::binary);
    if(!f1)
    {
        cout<<"No Admin Records\n";
        return ;
    }
    f1.seekg(0,ios::beg);

    cout<<"Enter the Login id and the Password\n";
    cout<<"Login Id: ";
    cin>>id;
    cout<<"Password: ";
    cin>>pass;

    while(1)
    {
        f1.read((char*)&admin, sizeof(admin));
        if(f1.eof())
            break;
        if(admin.check(id,pass))
        {
            f1.close();
            int ch;
            flag = 1;

            system("cls");
            displayHeadingAdmin();
            displayAdminOperations();
            do
            {
                cin>>ch;

                switch(ch)
                {
                    case 1:cout<<"Enter new User Id:";
                           cin>>newId;
                           cout<<"Enter new password:";
                           cin>>newPass;

                           admin.update(newId, newPass);

                           f1.open("Admins.dat",ios::out|ios::in|ios::binary);
                           f1.seekp(pos, ios::beg);
                           f1.write((char*)&admin, sizeof(admin));
                           f1.close();

                           cout<<"User Id and Password updated successfully\n";
                           break;

                    case 2:admin.viewAllRecords();
                           break;

                    case 3:cout<<"Enter the account number\n";
                           cin>>acc;

                           admin.viewUserRecordsbyAcc(acc);
                           break;

                    case 4:admin.enterRecords();
                           break;

                    case 5:admin.checkLoans();
                           break;
                    case 6:return;
                    default:cout<<"Invalid choice entered\n";
                }
                system("cls");
                displayHeadingAdmin();
                displayAdminOperations();
            }while(1);
            break;
        }
        else
            continue;
        pos++;
    }
    if(!flag)
        cout<<"\nId or password is invalid\n";
    f1.close();
}

void UserOperations()//done
{
    int ch,pos=0;
    char id[10], pass[10], newId[10], newPass[10],ans;
    fstream f1;
    bool flag = 0;
    User user,userObj;

    system("cls");
    displayHeadingUser();
    f1.open("UserRecords.dat",ios::out|ios::in|ios::binary);
    if(!f1)
    {
        f1.close();

        cout<<"No User Record Exists \n";
        cout<<"Press Any Key To Return\n";
        cin.ignore();
        getchar();
        return;
    }

    cout<<"Enter the Login Id and Password \n";
    cout<<"Login Id: ";
    cin>>id;
    cout<<"Password: ";
    cin>>pass;
    f1.seekg(0,ios::beg);

    while(1)
    {
        f1.read((char*)&user, sizeof(user));
        if(f1.eof())
            break;
        if(user.check(id,pass))
        {
            flag = 1;
            f1.close();
            system("cls");
            displayHeadingUser();
            displayUserOperations();

            do
            {
                int ch;
                cin>>ch;

                switch(ch)
                {
                    case 1:cout<<"Enter new User Id: ";
                           cin>>newId;
                           cout<<"Enter new password: ";
                           cin>>newPass;

                           user.update(newId, newPass);
                           f1.open("UserRecords.dat",ios::out|ios::in|ios::binary);
                           f1.seekp(pos, ios::beg);
                           f1.write((char*)&userObj, sizeof(userObj));

                           cout<<"User Id and Password updated successfully\n";
                           f1.close();
                           break;

                    case 2:user.viewAllInfo();
                           break;

                    case 3:user.transaction(pos);
                           break;

                    case 4:user.requestLoan();
                           break;

                    /*case 5:f1.close();
                           user.requestCheckBook();*/
                    case 5:return;
                    default:cout<<"Invalid choice entered\n";
                }
                system("cls");
                displayHeadingUser();
                displayUserOperations();

            }while(1);
            break;
        }
        else
            continue;
        pos++;
    }
    if(!flag)
        cout<<"\n\nId or password is invalid\n\n";
    cout<<"Press Any Key To Return ";
    cin.ignore();
    getchar();
    f1.close();
}
int searchUserRecordbyAcc(char* acc)//done
{
    User user;
    fstream f1;
    int pos = 0;

    f1.open("UserRecords.dat",ios::out|ios::in|ios::binary);
    f1.seekg(0,ios::beg);

    if(!f1)
    {
        f1.close();
        return -1;
    }
    while(1)
    {
        f1.read((char*)&user,sizeof(user));
        if(f1.eof())
            break;
        if(strcmp(user.getAccNo(),acc)==0)
        {
            f1.close();
            return pos;
        }
        pos++;
    }
    f1.close();
    return -1;
}

void displayHeading()
{
    cout<<"\n\n-----------------------------ONLINE BANKING SYSTEM------------------------------\n\n";
}

void displayHeadingAdmin()
{
    cout<<"\n\n-----------------------------ONLINE BANKING SYSTEM------------------------------\n\n";
    cout<<"Administrator Menu:-\n\n";
}

void displayHeadingUser()
{
    cout<<"\n\n-----------------------------ONLINE BANKING SYSTEM------------------------------\n\n";
    cout<<"User Menu:-\n\n";
}

void displayFrontPage()
{
    cout<<"Enter 1 If You Are an Administrator\n";
    cout<<"Enter 2 If You Are a User\n";
    cout<<"Enter 3 If You Wish To Exit\n";
}

void displayAdminOperations()
{
    cout<<"Enter 1 If You Wish To Change Your User Id Or Password\n";
    cout<<"Enter 2 If You Wish To View The Details Of All The Users\n";
    cout<<"Enter 3 If You Wish To Search for a User By Account No.\n";
    cout<<"Enter 4 If You Wish To Enter New User Records\n";
    cout<<"Enter 5 If You Wish To Check The Loan Database\n";
    cout<<"Enter 6 If You Wish To Go Back\n";
}

void displayUserOperations()
{
    cout<<"Enter 1 If You Wish To Change Your User Id or Password\n";
    cout<<"Enter 2 If You Wish To View Your Complete Record\n";
    cout<<"Enter 3 If You Wish To Transfer Money To Another Account\n";
    cout<<"Enter 4 If You Wish To Request For a Loan\n";
    cout<<"Enter 5 If You Wish To Go Back\n";
}

void addAdmins()//done
{
    char* id ="Mad1997\0", *pass="password\0", *name="Madhur\0";
    Admin newAdmin(id,pass,name);
    fstream f1;
    f1.open("Admins.dat",ios::out|ios::binary);
    f1.write((char*)&newAdmin, sizeof(newAdmin));
    f1.close();
}

/*void checkRecords()
{
    fstream f1;
    Admin admin;

    f1.open("Admins.dat",ios::in|ios::binary);
    if(!f1)
        cout<<"No Admins\n";
    else
    {
        f1.seekg(0,ios::beg);
        while(!f1.eof())
        {
            f1.read((char*)&admin,sizeof(admin));
            if(f1.eof())
                break;
            cout<<admin.getName();
        }
    }
    f1.close();
}*/
int main()
{
    int ch;

    addAdmins(); //Adding the admins
    //checkRecords();

    displayHeading();
    displayFrontPage();

    do
    {
        cin>>ch;
        switch(ch)
        {
            case 1:AdminOperations();
                   break;
            case 2:UserOperations();
                   break;
            case 3:exit(0);
            default:cout<<"Invalid Choice\n";
        }
        system("cls");
        displayHeading();
        displayFrontPage();
    }while(1);
    return 0;
}
