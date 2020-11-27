
#include "include/tinyxml2.h"
#include "include/tinyxml2.cpp"
using namespace tinyxml2;
using namespace std;
#include <iostream>

void validateAccount(); //verify credentials
void createAccount(string userName, string password); //create account
bool accountExists(string userName);   //check if account exists
void accessAccount();   //login to account
void createAuthentication();    //create xml that stores credentials

int main()
{
    int option;
    do{
        cout << "Create account: 1" << endl;
        cout << "Log in to account: 2" << endl;
        cout << "Exit Program: 3" << endl;
        cout << "      Choose one of the above options: ";
        cin >> option;
        switch (option)
        {
            case 1:
                cout << endl << "............................Create Account..............................\n";
                validateAccount();
                cout << endl;
                break;
            case 2:
                cout << endl << "............................Account Homepage............................\n";
                accessAccount();
                cout << endl;
                break;
            case 3:
                cout << endl << "............................EXITING PROGRAM.............................\n";
                cout << endl;
                return 0;
        }
    cout << endl << endl;
    }while( option == 1 || option == 2);

    return 0;
}

void validateAccount(){
    bool exists = true;
    string userName;    //holds username
    string password = "";   //holds password
    string checkPassword = "";  //holds password for verification
    while(exists){  
        cout << "Type account Username: ";
        cin >> userName;    //take username input
        if(accountExists(userName)) //check if username already taken
            cout << "An account with that username already exists." << endl << endl;
        else
            exists = false;
    }
    do{         //ask for password until it is verified 
        cout << "Type New password: ";
        cin >> password;    //take password input
        cout << endl;

        cout << "Type password again: ";
        cin >> checkPassword;   //take password input
        if (password.compare(checkPassword) != 0)   //check password and check password match
            cout << "passwords don't match!" << endl << endl;
    }while(password.compare(checkPassword) !=0 );
    createAccount(userName,password);   //create account with given credentials
    cout << "Account creation successful!" << endl;
    int option = 1;         //switch for homepage logout
    while(option != 0){     //stay logged in until input = 0
        cout << "You are logged in. " << endl;
        cout << userName << " Home Page." << endl;
        cout << "Press 0 to log out." << endl;
        cin >> option;  //if input is 0, exit the loop
    }
    cout << "Logged out." << endl;
    //clear memory
    password.clear(); 
    checkPassword.clear();
    userName.clear();
}

void createAccount(string userName, string password){
    XMLDocument doc;    
    doc.LoadFile( "Accounts.xml" );     
    XMLElement *pRootElement = doc.RootElement();  
    XMLElement *pAccounts = pRootElement->FirstChildElement("Accounts");
    XMLElement* pAccount = pAccounts->FirstChildElement("Account");

    XMLNode *newAccount = doc.NewElement("Account");
    pAccounts->InsertEndChild(newAccount);
    XMLElement* pElement = doc.NewElement("Username");
    pElement->SetText(strdup(userName.c_str()));
    newAccount->InsertEndChild(pElement);
    pElement = doc.NewElement("Password");
    pElement->SetText(strdup(password.c_str()));
    newAccount->InsertEndChild(pElement);

    XMLError eResult = doc.SaveFile("Accounts.xml");
}

bool accountExists(string userName){ //check if account exists
    XMLDocument doc;
    bool fileExists = doc.LoadFile( "Accounts.xml" );
    if(fileExists == 1){
        createAuthentication(); //create file to hold credentials
        doc.LoadFile("Accounts.xml");
    }
    XMLElement *pRootElement = doc.RootElement();
    XMLElement *pAccounts = pRootElement->FirstChildElement("Accounts");
    XMLElement *pAccount = pAccounts->FirstChildElement("Account");
    while(pAccount){
        XMLElement *pUsername = pAccount->FirstChildElement("Username");
        if(pUsername->GetText() == userName){
            return true;
        }
        pAccount = pAccount->NextSiblingElement("Account"); 
    }
    return false;
}


void accessAccount(){
    string userName;
    string password;
    cout << "Username: ";
    cin >> userName;

    XMLDocument doc;
    bool fileExists = doc.LoadFile( "Accounts.xml" );
    if(fileExists == 1){
        createAuthentication();
        doc.LoadFile("Accounts.xml");
    }
    XMLElement *pRootElement = doc.RootElement();
    XMLElement *pAccounts = pRootElement->FirstChildElement("Accounts");
    XMLElement *pAccount = pAccounts->FirstChildElement("Account");

    while(accountExists(userName) == false){
        cout << "Account with username " << userName << " doesn't exist." << endl << endl;
        int option;
        cout << "To go back to main menu press 1 or 2 to try new Username: ";
        cin >> option;
        if (option == 1)
            return;
        cout << "Username: ";
        cin >> userName;
    }
    while(pAccount){
        XMLElement *pUsername = pAccount->FirstChildElement("Username");

        if(pUsername->GetText() == userName){
            XMLElement *pPassword = pAccount->FirstChildElement("Password");
            cout << "Password: " ;
            cin >> password;
            for(int i = 0; i < 4; i++){ //allow password verification only 4 times
                if(pPassword->GetText() != password){
                    cout << "Incorrect password! try again." << endl;
                    cout << "Password: " ;
                    cin >> password; 
                }
                if(pPassword->GetText() == password){
                    int option = 1;
                    while(option != 0){
                        cout << "You are logged in. " << endl;
                        cout << userName << " Home Page." << endl;
                        cout << "Press 0 to log out." << endl;
                        cin >> option;
                    }
                    cout << "Logged out." << endl;
                    return;
                }
            }
            cout << "Too many password tries. Contact your administrator." << endl;
            return;
        }
        pAccount = pAccount->NextSiblingElement("Account"); 
    }
}

void createAuthentication(){
    XMLDocument xmlDoc;
    XMLNode* pRoot = xmlDoc.NewElement("Root");
    xmlDoc.InsertFirstChild(pRoot);
    XMLNode* nHead = xmlDoc.NewElement("Accounts");
    pRoot->InsertEndChild(nHead);
    XMLError eResult = xmlDoc.SaveFile("Accounts.xml");
}







