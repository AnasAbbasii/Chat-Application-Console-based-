#include<chrono>
#include<thread>
#include<windows.h>
#include<iostream>
#include<conio.h>
#include<ctime>
#include<fstream>
#include<cstdlib>
#include<string>
#include<stdexcept>
using namespace std;

//==============================================
// CONSOLE HANDLE
//==============================================
HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);

//==============================================
// COLOUR FUNCTION
//==============================================
void colour(int c){
    SetConsoleTextAttribute(hConsole,c);
}
void hideCursor(){
    CONSOLE_CURSOR_INFO i;
    i.dwSize=1;
    i.bVisible=false;
    SetConsoleCursorInfo(hConsole,&i);
}
void showCursor(){
    CONSOLE_CURSOR_INFO i;
    i.dwSize=1;
    i.bVisible=true;
    SetConsoleCursorInfo(hConsole,&i);
}

//==============================================
// INPUT HANDLING
//==============================================
enum class InputEvent{NONE,SELECT,MOVE_UP,MOVE_DOWN};

bool isBlank(string s){
    if(s.length()==0) 
        return true;
    for(int i=0;i<(int)s.length();i++)
        if(s[i]!=' ') return false;
    return true;
}

string inputfield(bool &cancelled){
    string t="";
    char ch;
    while(true){
        ch=getch();
        if(ch==13){cout<<endl;break;}
        else if(ch==8){
            if(t.empty()){cancelled=true;return "";}
            t.pop_back();
            cout<<"\b \b";
        }
        else if(ch==0||ch==224){getch();}
        else{
            t.push_back(ch);
            cout<<(char)ch;
        }
    }
    return t;
}

string getpassword(){
    string pw="";
    int ch;
    while(true){
        ch=getch();
        if(ch==13) break;
        else if(ch==8){
            if(!pw.empty()){pw.pop_back();cout<<"\b \b";}
        }
        else if(ch==0||ch==224){
            getch();
            continue;}
        else{
            pw.push_back(ch);
            cout<<"*";}
    }
    cout<<endl;
    return pw;
}

//==============================================
// UI CLASS
// Handles all visual output in one place
// OOP Concept: Encapsulation, Static Members
//==============================================
class UI{
public:
    static void clear(){
        system("cls");
        hideCursor();
    }
    static void line(){
        colour(3);
        cout<<"  ════════════════════════════════════"<<endl;
        colour(15);
    }
    static void thinLine(){
        colour(8);
        cout<<"  ────────────────────────────────────"<<endl;
        colour(15);
    }
    static void header(string title){
        clear();
        colour(3);
        cout<<"  ╔══════════════════════════════════╗"<<endl;
        cout<<"  ║";
        colour(11);
        // Center the title
        int spaces=(34-(int)title.length())/2;
        for(int i=0;i<spaces;i++) cout<<" ";
        cout<<title;
        for(int i=0;i<34-(int)title.length()-spaces;i++) 
            cout<<" ";
        colour(3);
        cout<<"║"<<endl;
        cout<<"  ╚══════════════════════════════════╝"<<endl;
        colour(15);
        cout<<endl;
    }
    static void breadcrumb(string path){
        colour(8);
        cout<<"  "<<path<<endl;
        thinLine();
        colour(15);
        cout<<endl;
    }
    static void success(string msg){
        colour(2);
        cout<<"  ✓ "<<msg<<endl;
        colour(15);
    }
    static void error(string msg){
        colour(12);
        cout<<"  ✗ "<<msg<<endl;
        colour(15);
    }
    static void warning(string msg){
        colour(6);
        cout<<"  ! "<<msg<<endl;
        colour(15);
    }
    static void info(string msg){
        colour(11);
        cout<<"  • "<<msg<<endl;
        colour(15);
    }
    static void label(string lbl,string val){
        colour(8);
        cout<<"  "<<lbl;
        colour(15);
        cout<<val<<endl;
    }
    static void loading(string msg){
        colour(2);
        cout<<"  "<<msg;
        for(int i=0;i<5;i++){
            cout<<"."<<flush;
            this_thread::sleep_for(chrono::milliseconds(300));
            while(kbhit()) getch();
        }
        colour(15);
        cout<<endl;
    }
    static void pressKey(){
        cout<<endl;
        colour(8);
        cout<<"  Press any key to continue..."<<endl;
        colour(15);
        getch();
    }
    static void field(string label){
        colour(3);
        cout<<"  > ";
        colour(15);
        cout<<label<<" : ";
    }
    static void menuFooter(){
        cout<<endl;
        colour(8);
        cout<<"  [ ↑↓ Navigate ]  [ ENTER Select ]  [ BACKSPACE Back ]"<<endl;
        colour(15);
    }
    static void splash(){
        clear();
        cout<<endl<<endl;
        colour(3);
        cout<<"   ╔══════════════════════════════════╗"<<endl;
        cout<<"   ║                                  ║"<<endl;
        colour(11);
        cout<<"   ║          C  H  A  T  O           ║"<<endl;
        colour(15);
        cout<<"   ║    Console-Based Chat System     ║"<<endl;
        colour(8);
        cout<<"   ║      Secure  •  Simple  •  Fast  ║"<<endl;
        colour(3);
        cout<<"   ║                                  ║"<<endl;
        cout<<"   ╚══════════════════════════════════╝"<<endl;
        cout<<endl;
        colour(2);
        cout<<"   Loading";
        for(int i=0;i<8;i++){
            cout<<"."<<flush;
            this_thread::sleep_for(chrono::milliseconds(200));
        }
        colour(15);
        cout<<endl;
    }
    static void about(){
        hideCursor();
        header("ABOUT PROJECT");
        breadcrumb("CHATO > About");
        colour(11);
        cout<<"  Project  : CHATO - Console Chat App"<<endl;
        colour(15);
        cout<<"  Subject  : Object Oriented Programming"<<endl;
        cout<<"  Language : C++"<<endl;
        cout<<endl;
        colour(3);
        cout<<"  OOP Concepts Used:"<<endl;
        colour(15);
        thinLine();
        info("Classes and Objects");
        info("Encapsulation");
        info("Inheritance");
        info("Abstraction");
        info("Polymorphism");
        info("Friend Function");
        info("Static Members");
        info("Exception Handling");
        info("File Handling");
        info("Constructor and Destructor");
        pressKey();
    }
    static void help(){
        hideCursor();
        header("HELP & INSTRUCTIONS");
        breadcrumb("CHATO > Help");
        colour(11);
        cout<<"  How to use CHATO:"<<endl<<endl;
        colour(15);
        label("Step 1 : ","Register using your name and password");
        label("Step 2 : ","Save your User ID shown after registration");
        label("Step 3 : ","Login using User ID and password");
        label("Step 4 : ","Use Messages menu to send and receive");
        label("Step 5 : ","Use Contacts to find other users");
        label("Step 6 : ","Use Settings to update your profile");
        cout<<endl;
        colour(11);
        cout<<"  Navigation:"<<endl<<endl;
        colour(15);
        label("UP / DOWN  : ","Navigate menu options");
        label("ENTER      : ","Select option");
        label("BACKSPACE  : ","Go back or cancel input");
        pressKey();
    }
};

//==============================================
// FILE HANDLER CLASS
// All file operations in one place
// OOP Concept: Static Members, Encapsulation
//==============================================
class FileHandler{
public:
    static void writeLine(string filename,string data){
        try{
            ofstream file(filename,ios::app);
            if(!file.is_open()) throw runtime_error("Cannot open: "+filename);
            file<<data<<endl;
            if(file.fail()) throw runtime_error("Write failed: "+filename);
            file.close();
        }
        catch(runtime_error &e){UI::error(e.what());}
        catch(...){UI::error("Unknown file error.");}
    }
    static int readLines(string filename,string lines[],int maxLines){
        int count=0;
        try{
            ifstream file(filename);
            if(!file.is_open()) return 0;
            string line;
            while(getline(file,line)&&count<maxLines){
                if(!line.empty()){lines[count]=line;count++;}
            }
            if(file.bad()) throw runtime_error("Read error: "+filename);
            file.close();
        }
        catch(runtime_error &e){UI::error(e.what());}
        catch(...){UI::error("Unknown read error.");}
        return count;
    }
    static void writeAllLines(string filename,string lines[],int count){
        try{
            ofstream file(filename);
            if(!file.is_open()) throw runtime_error("Cannot write: "+filename);
            for(int i=0;i<count;i++){
                file<<lines[i]<<endl;
                if(file.fail()) throw runtime_error("Write failed at line "+to_string(i));
            }
            file.close();
        }
        catch(runtime_error &e){UI::error(e.what());}
        catch(...){UI::error("Unknown write error.");}
    }
    static int parseCSV(string line,string parts[],int maxParts){
        int count=0;
        string cur="";
        for (int i = 0; i <= (int)line.length() && count < maxParts; i++) {
            if (count == maxParts - 1) {
                parts[count] = line.substr(i);
                count++;
                break;}
            if (i == (int)line.length() || line[i] == ',') {
                parts[count] = cur;
                count++;
                cur = "";} 
            else {
                cur += line[i];}
        }
        return count;
    }
};

//==============================================
// ABSTRACT BASE CLASS
// OOP Concept: Abstraction, Pure Virtual Function
//==============================================
class Displayable{
public:
    virtual void display()=0;
    virtual ~Displayable(){}
};

//==============================================
// ACCOUNT CLASS (Base)
// OOP Concept: Inheritance base
//==============================================
class Account:public Displayable{
protected:
    string userID;
    string password;
public:
    Account(){
        userID="";
        password="";
    }
    Account(string id,string pw){
        userID=id;
        password=pw;
    }
    virtual ~Account(){
    }
    string getUserID(){return userID;}
    string getPassword(){return password;}
    void setUserID(string id){userID=id;}
    void setPassword(string pw){password=pw;}
    // Pure virtual from Displayable
    virtual void display()=0;
};

//==============================================
// USER CLASS
// Inherits from Account
// OOP Concept: Inheritance, Encapsulation,
//              Polymorphism, Friend Function
//==============================================
class User:public Account{
private:
    string firstName;
    string lastName;
    string status;
public:
    // Default constructor
    User():Account(){
        firstName="";
        lastName="";
        status="Hello I am using Chato";
    }
    // Parameterised constructor
    User(string id,string fn,string ln,string pw,string st):Account(id,pw){
        firstName=fn;
        lastName=ln;
        status=st;
    }
    // Destructor
    ~User(){}
    // Setters
    void setFirstName(string fn){firstName=fn;}
    void setLastName(string ln){lastName=ln;}
    void setStatus(string st){status=st;}
    // Getters
    string getFirstName(){return firstName;}
    string getLastName(){return lastName;}
    string getStatus(){return status;}
    string getFullName(){return firstName+" "+lastName;}
    // Override display from Displayable
    void display()override{
        UI::header("MY PROFILE");
        UI::breadcrumb("CHATO > Settings > Profile");
        cout << "   "; 
        colour(11);    
        cout << "Name     :  " << firstName << " " << lastName << endl;
        cout << "   "; 
        colour(8);    
        cout << "User ID  :  " << userID << endl;
        cout << "   "; 
        colour(10);    
        cout << "Status  :  " << status << endl;
        cout << "   ";
        colour(15);    
    }
    // Operator overloading == to compare users by ID
    bool operator==(const User &other){
        return userID==other.userID;
    }
    // Friend function declaration
    friend void showUserCard(User &u,int index);
    // Save to file
    void saveToFile(){
        try{
            string data=userID+","+firstName+","+lastName+","+password+","+status;
            FileHandler::writeLine("Users.csv",data);
        }
        catch(...){UI::error("Error saving user.");}
    }
    void updateInFile(string newpw,string newst){
        try{
            string lines[200];
            int count=FileHandler::readLines("Users.csv",lines,200);
            for(int i=0;i<count;i++){
                string parts[10];
                int n=FileHandler::parseCSV(lines[i],parts,10);
                if(n>=5&&parts[0]==userID){
                    lines[i]=userID+","+firstName+","+lastName+","+newpw+","+newst;
                    break;
                }
            }
            FileHandler::writeAllLines("Users.csv",lines,count);
        }
        catch(...){UI::error("Error updating user.");}
    }
};

//==============================================
// FRIEND FUNCTION
// Accesses private members of User directly
// OOP Concept: Friend Function
//==============================================
void showUserCard(User &u,int index){
    cout << "   "; 
    colour(11);    
    cout << u.firstName << " " << u.lastName;
    colour(8);    
    cout << " [" << u.userID << "]" << endl;
    cout << "   "; 
    colour(10);    
    cout << "Status: ";
    colour(15);
    cout<< u.status << endl;
    colour(8);     
    cout << "   ───────────────────────────────" << endl << endl;
    colour(15);
}

//==============================================
// MESSAGE CLASS
// Inherits from Displayable
// OOP Concept: Inheritance, Polymorphism
//==============================================
class Message:public Displayable{
private:
    string senderID;
    string receiverID;
    string content;
    string timestamp;
public:
    Message(){
        senderID="";receiverID="";content="";timestamp="";
    }
    Message(string sid,string rid,string msg,string ts){
        senderID=sid;receiverID=rid;content=msg;timestamp=ts;
    }
    ~Message(){}
    string getSenderID(){return senderID;}
    string getReceiverID(){return receiverID;}
    string getContent(){return content;}
    string getTimestamp(){return timestamp;}
    // Override display from Displayable
    void display()override{
        colour(3);
        cout<<"  │ ";colour(8);cout<<timestamp<<endl;
        colour(3);
        cout<<"  │ ";colour(15);cout<<content<<endl;
    }
    void saveToFile(){
        try{
            string data=senderID+","+receiverID+","+timestamp+","+content;
            FileHandler::writeLine("Messages.csv",data);
        }
        catch(...){UI::error("Error saving message.");}
    }
};

//==============================================
// AUTHENTICATION CLASS
//==============================================
class Authentication{
private:
    string generateID(){
        try{
            int id=rand()%9000+1000;
            return "User"+to_string(id);
        }
        catch(...){return "User1000";}
    }
    bool idExists(string id){
        try{
            string lines[200];
            int count=FileHandler::readLines("Users.csv",lines,200);
            for(int i=0;i<count;i++){
                string parts[10];
                FileHandler::parseCSV(lines[i],parts,10);
                if(parts[0]==id) return true;
            }
        }
        catch(...){return false;}
        return false;
    }
public:
    User registerUser(){
        User newUser;
        bool cancelled=false;
        UI::header("REGISTRATION");
        UI::breadcrumb("CHATO > Register");
        showCursor();
        string fn,ln,pw,pw2;
        // First name
        while(true){
            try{
                UI::field("First Name");
                fn=inputfield(cancelled);
                if(cancelled){
                    hideCursor();
                    newUser.setUserID("");
                    return newUser;}
                if(isBlank(fn)) throw invalid_argument("First name cannot be empty.");
                break;
            }
            catch(invalid_argument &e){UI::error(e.what());}
        }
        // Last name
        while(true){
            try{
                UI::field("Last Name ");
                ln=inputfield(cancelled);
                if(cancelled){
                    hideCursor();
                    newUser.setUserID("");
                    return newUser;}
                if(isBlank(ln)) throw invalid_argument("Last name cannot be empty.");
                break;
            }
            catch(invalid_argument &e){UI::error(e.what());}
        }
        // Password
        while(true){
            try{
                UI::field("Password  ");
                pw=getpassword();
                if(pw.length()<4) throw invalid_argument("Password must be at least 4 characters.");
                UI::field("Confirm PW");
                pw2=getpassword();
                if(pw!=pw2) throw invalid_argument("Passwords do not match. Try again.");
                break;
            }
            catch(invalid_argument &e){UI::error(e.what());}
        }
        hideCursor();
        cout<<endl;
        UI::loading("Creating your account");
        try{
            bool exists=false;
            string lines[200];
            int count=FileHandler::readLines("Users.csv",lines,200);
            for(int i=0;i<count;i++){
                string parts[10];
                int n=FileHandler::parseCSV(lines[i],parts,10);
                if(n>=4&&parts[1]==fn&&parts[2]==ln&&parts[3]==pw){exists=true;break;}
            }
            if(exists) throw runtime_error("Account with same credentials already exists.");
            string newID=generateID();
            int attempts=0;
            while(idExists(newID)){
                newID=generateID();attempts++;
                if(attempts>100) throw runtime_error("Could not generate unique ID.");
            }
            newUser.setUserID(newID);
            newUser.setFirstName(fn);
            newUser.setLastName(ln);
            newUser.setPassword(pw);
            newUser.setStatus("Hello I am using Chato");
            newUser.saveToFile();
            UI::clear();
            colour(3);
            cout<<"  ╔══════════════════════════════════╗"<<endl;
            cout<<"  ║";
            colour(2);
            cout<<"      REGISTRATION SUCCESSFUL     ";
            colour(3);
            cout<<"║"<<endl;
            cout<<"  ╚══════════════════════════════════╝"<<endl;
            cout<<endl;
            UI::label("  Name    :  ",fn+" "+ln);
            UI::label("  User ID :  ",newID);
            cout<<endl;
            UI::warning("Save your User ID to LOGIN");
            newUser.setUserID("");
        }
        catch(runtime_error &e){
            UI::clear();
            colour(12);
            cout<<"  ╔══════════════════════════════════╗"<<endl;
            cout<<"  ║        REGISTRATION FAILED       ║"<<endl;
            cout<<"  ╚══════════════════════════════════╝"<<endl;
            colour(15);cout<<endl;
            UI::error(e.what());
        }
        catch(...){UI::error("Unexpected error during registration.");}
        UI::pressKey();
        return newUser;
    }

    User loginUser(){
        User loggedUser;
        bool cancelled=false;
        UI::header("LOGIN");
        UI::breadcrumb("CHATO > Login");
        showCursor();
        string uid,pw;
        try{
            UI::field("User ID  ");
            uid=inputfield(cancelled);
            if(cancelled){
                hideCursor();
                loggedUser.setUserID("");
                return loggedUser;}
            if(isBlank(uid)) throw invalid_argument("User ID cannot be empty.");
            UI::field("Password ");
            pw=getpassword();
            if(isBlank(pw)) throw invalid_argument("Password cannot be empty.");
        }
        catch(invalid_argument &e){
            hideCursor();
            UI::error(e.what());
            UI::pressKey();
            loggedUser.setUserID("");
            return loggedUser;
        }
        hideCursor();
        cout<<endl;
        UI::loading("Verifying credentials");
        try{
            string lines[200];
            int count=FileHandler::readLines("Users.csv",lines,200);
            if(count==0) throw runtime_error("No registered users found.");
            bool found=false;
            for(int i=0;i<count;i++){
                string parts[10];
                int n=FileHandler::parseCSV(lines[i],parts,10);
                if(n>=5&&parts[0]==uid&&parts[3]==pw){
                    loggedUser.setUserID(parts[0]);
                    loggedUser.setFirstName(parts[1]);
                    loggedUser.setLastName(parts[2]);
                    loggedUser.setPassword(parts[3]);
                    loggedUser.setStatus(parts[4]);
                    found=true;break;
                }
            }
            if(!found) throw runtime_error("Invalid User ID or Password.");
        }
        catch(runtime_error &e){
            UI::clear();
            colour(12);
            cout<<"  ╔══════════════════════════════════╗"<<endl;
            cout<<"  ║          LOGIN FAILED            ║"<<endl;
            cout<<"  ╚══════════════════════════════════╝"<<endl;
            colour(15);cout<<endl;
            UI::error(e.what());
            UI::pressKey();
            loggedUser.setUserID("");
        }
        catch(...){UI::error("Unexpected error.");UI::pressKey();loggedUser.setUserID("");}
        return loggedUser;
    }
};

//==============================================
// CHAT CLASS
//==============================================
class Chat{
private:
    User currentUser;
    string getTime(){
        try{
            time_t now=time(0);char buf[20];
            struct tm* t=localtime(&now);
            sprintf(buf,"%02d:%02d",t->tm_hour,t->tm_min);
            return string(buf);
        }catch(...){return "00:00";}
    }
    string getDate(){
        try{
            time_t now=time(0);char buf[30];
            struct tm* t=localtime(&now);
            sprintf(buf,"%02d/%02d/%04d",t->tm_mday,t->tm_mon+1,t->tm_year+1900);
            return string(buf);
        }catch(...){return "00/00/0000";}
    }
    string getNameByID(string uid){
        try{
            string lines[200];
            int count=FileHandler::readLines("Users.csv",lines,200);
            for(int i=0;i<count;i++){
                string parts[10];
                int n=FileHandler::parseCSV(lines[i],parts,10);
                if(n>=3&&parts[0]==uid) return parts[1]+" "+parts[2];
            }
        }catch(...){}
        return "Unknown";
    }
    string getStatusByID(string uid){
        try{
            string lines[200];
            int count=FileHandler::readLines("Users.csv",lines,200);
            for(int i=0;i<count;i++){
                string parts[10];
                int n=FileHandler::parseCSV(lines[i],parts,10);
                if(n>=5&&parts[0]==uid) return parts[4];
            }
        }catch(...){}
        return "";
    }
    bool userExists(string uid){
        try{
            string lines[200];
            int count=FileHandler::readLines("Users.csv",lines,200);
            for(int i=0;i<count;i++){
                string parts[10];
                FileHandler::parseCSV(lines[i],parts,10);
                if(parts[0]==uid) return true;
            }
        }catch(...){}
        return false;
    }
    int countInbox(){
        int count=0;
        try{
            string lines[500];
            int total=FileHandler::readLines("Messages.csv",lines,500);
            for(int i=0;i<total;i++){
                string parts[10];
                int n=FileHandler::parseCSV(lines[i],parts,10);
                if(n>=2&&parts[1]==currentUser.getUserID()) count++;
            }
        }catch(...){}
        return count;
    }
    int countSent(){
        int count=0;
        try{
            string lines[500];
            int total=FileHandler::readLines("Messages.csv",lines,500);
            for(int i=0;i<total;i++){
                string parts[10];
                int n=FileHandler::parseCSV(lines[i],parts,10);
                if(n>=1&&parts[0]==currentUser.getUserID()) count++;
            }
        }catch(...){}
        return count;
    }
public:
    Chat(User u){currentUser=u;}

    int getInboxCount(){return countInbox();}
    int getSentCount(){return countSent();}

    void sendMessage(){
        bool cancelled=false;
        UI::header("SEND MESSAGE");
        UI::breadcrumb("CHATO > Messages > Send");
        showCursor();
        string receiverID;
        while(true){
            try{
                UI::field("Receiver User ID");
                receiverID=inputfield(cancelled);
                if(cancelled) {
                    hideCursor();
                    return ;
                }
                if(isBlank(receiverID)) throw invalid_argument("Receiver ID cannot be empty.");
                if(receiverID==currentUser.getUserID()) throw invalid_argument("Cannot send message to yourself.");
                if(!userExists(receiverID)) throw invalid_argument("User not found. Check the ID.");
                break;
            }
            catch(invalid_argument &e){UI::error(e.what());}
        }
        string receiverName=getNameByID(receiverID);
        string receiverStatus=getStatusByID(receiverID);
        cout<<endl;
        colour(3);
        cout<<"  ┌──────────────────────────────────┐"<<endl;
        cout<<"  │ ";colour(11);cout<<"Chatting with: "<<receiverName;
        int pad=19+(int)receiverName.length();
        for(int i=pad;i<35;i++) cout<<" ";
        colour(3);cout<<"│"<<endl;
        cout<<"  │ ";colour(8);cout<<"Status: "<<receiverStatus;
        int pad2=8+(int)receiverStatus.length();
        for(int i=pad2;i<34;i++) cout<<" ";
        colour(3);cout<<"│"<<endl;
        cout<<"  └──────────────────────────────────┘"<<endl;
        colour(15);
        cout<<endl;
        colour(8);
        cout<<"  Type message. BACKSPACE on empty to exit."<<endl;
        cout<<endl;
        while(true){
            try{
                colour(11);cout<<"  You > ";colour(15);
                string msg=inputfield(cancelled);
                if(cancelled){
                    hideCursor();
                    break;
                }
                if(isBlank(msg)) throw invalid_argument("Message cannot be empty.");
                string ts=getDate()+" "+getTime();
                Message m(currentUser.getUserID(),receiverID,msg,ts);
                m.saveToFile();
                colour(2);cout<<"  ✓ Sent ";colour(8);cout<<"("<<ts<<")"<<endl;colour(15);
            }
            catch(invalid_argument &e){UI::error(e.what());}
            catch(...){UI::error("Error sending message.");}
        }
    }

    void viewInbox(){
        UI::header("INBOX");
        UI::breadcrumb("CHATO > Messages > Inbox");
        try{
            string lines[500];
            int count=FileHandler::readLines("Messages.csv",lines,500);
            if(count==0) throw runtime_error("No messages found.");
            bool found=false;
            for(int i=0;i<count;i++){
                string parts[10];
                int n=FileHandler::parseCSV(lines[i],parts,10);
                if(n>=4&&parts[1]==currentUser.getUserID()){
                    found=true;
                    string senderName=getNameByID(parts[0]);
                    
                    // Header style: From: Name [ID]
                    cout << "  ";
                    colour(11); cout << "From: " << senderName;
                    colour(8);  cout << " [" << parts[0] << "]" << endl;
                    
                    // Timestamp on the next line
                    cout << "  ";
                    colour(8);  cout << parts[2] << endl;
                    
                    // Content message body
                    cout << "  ";
                    colour(15); cout << parts[3] << endl;
                    
                    // Clean divider line
                    colour(8);
                    cout << "  ────────────────────────────────────" << endl << endl;
                    colour(15);
                }
            }
            if(!found) throw runtime_error("Your inbox is empty.");
        }
        catch(runtime_error &e){
            cout<<endl;
            colour(8);
            cout<<"  ╔══════════════════════════════════╗"<<endl;
            cout<<"  ║          Inbox is empty          ║"<<endl;
            cout<<"  ╚══════════════════════════════════╝"<<endl;
            colour(15);
        }
        catch(...){UI::error("Error loading inbox.");}
        UI::pressKey();
    }

    void viewSent(){
        UI::header("SENT MESSAGES");
        UI::breadcrumb("CHATO > Messages > Sent");
        try{
            string lines[500];
            int count=FileHandler::readLines("Messages.csv",lines,500);
            if(count==0) throw runtime_error("No messages found.");
            bool found=false;
            for(int i=0;i<count;i++){
                string parts[10];
                int n=FileHandler::parseCSV(lines[i],parts,10);
                if(n>=4&&parts[0]==currentUser.getUserID()){
                    found=true;
                    string rname=getNameByID(parts[1]);
                    
                    // Header style: To: Name [ID]
                    cout << "  ";
                    colour(11); cout << "To: " << rname;
                    colour(8);  cout << " [" << parts[1] << "]" << endl;
                    
                    // Timestamp on the next line
                    cout << "  ";
                    colour(8);  cout << parts[2] << endl;
                    
                    // Content message body
                    cout << "  ";
                    colour(15); cout << parts[3] << endl;
                    
                    // Clean divider line
                    colour(8);
                    cout << "  ────────────────────────────────────" << endl << endl;
                    colour(15);
                }
            }
            if(!found) throw runtime_error("No sent messages.");
        }
        catch(runtime_error &e){
            cout<<endl;
            colour(8);
            cout<<"  ╔══════════════════════════════════╗"<<endl;
            cout<<"  ║       No sent messages yet       ║"<<endl;
            cout<<"  ╚══════════════════════════════════╝"<<endl;
            colour(15);
        }
        catch(...){UI::error("Error loading sent.");}
        UI::pressKey();
    }

    void viewConversation(){
        bool cancelled=false;
        UI::header("CONVERSATION");
        UI::breadcrumb("CHATO > Messages > Conversation");
        showCursor();
        string otherID;
        while(true){
            try{
                UI::field("Enter User ID");
                otherID=inputfield(cancelled);
                if(cancelled){
                    hideCursor();
                    return ;
                }
                if(isBlank(otherID)) throw invalid_argument("User ID cannot be empty.");
                if(!userExists(otherID)) throw invalid_argument("User not found.");
                break;
            }
            catch(invalid_argument &e){UI::error(e.what());}
        }
        hideCursor();
        string otherName=getNameByID(otherID);
        string otherStatus=getStatusByID(otherID);
        UI::clear();
        colour(3);
        cout<<"  ╔══════════════════════════════════╗"<<endl;
        cout<<"  ║ ";colour(11);cout<<otherName;
        int p=(int)otherName.length();
        for(int i=p;i<33;i++) cout<<" ";
        colour(3);cout<<"║"<<endl;
        cout<<"  ║ ";colour(10);cout<<otherStatus;
        int p2=(int)otherStatus.length();
        for(int i=p2;i<33;i++) cout<<" ";
        colour(3);cout<<"║"<<endl;
        cout<<"  ╚══════════════════════════════════╝"<<endl;
        colour(15);cout<<endl;
        try{
            string lines[500];
            int count=FileHandler::readLines("Messages.csv",lines,500);
            if(count==0) throw runtime_error("No messages.");
            bool found=false;
            for(int i=0;i<count;i++){
                string parts[10];
                int n=FileHandler::parseCSV(lines[i],parts,10);
                if(n<4) continue;
                bool sent=(parts[0]==currentUser.getUserID()&&parts[1]==otherID);
                bool recv=(parts[0]==otherID&&parts[1]==currentUser.getUserID());
                if(sent||recv){
                    found=true;
                    if(sent){
                        colour(3);cout<<"  [You]      ";colour(15);
                    }else{
                        colour(11);cout<<"  ["<<otherName<<"] ";colour(15);
                    }
                    cout<<parts[3];
                    colour(8);cout<<"  ("<<parts[2]<<")"<<endl;colour(15);
                }
            }
            if(!found) throw runtime_error("No conversation with this user.");
        }
        catch(runtime_error &e){
            cout<<endl;
            colour(8);
            cout<<"  ╔══════════════════════════════════╗"<<endl;
            cout<<"  ║    No conversation found yet     ║"<<endl;
            cout<<"  ╚══════════════════════════════════╝"<<endl;
            colour(15);
        }
        catch(...){UI::error("Error loading conversation.");}
        UI::pressKey();
    }


    void exportConversation(){
        bool cancelled=false;
        UI::header("EXPORT CONVERSATION");
        UI::breadcrumb("CHATO > Messages > Export");
        showCursor();
        string otherID;
        while(true){
            try{
                UI::field("Enter User ID");
                otherID=inputfield(cancelled);
                if(cancelled){
                    hideCursor();
                    return;
                }
                if(isBlank(otherID)) throw invalid_argument("User ID cannot be empty.");
                if(!userExists(otherID)) throw invalid_argument("User not found.");
                break;
            }
            catch(invalid_argument &e){UI::error(e.what());}
        }
        hideCursor();
        try{
            string otherName=getNameByID(otherID);
            string filename="Chat_"+currentUser.getUserID()+"_"+otherID+".txt";
            ofstream outFile(filename);
            if(!outFile.is_open()) throw runtime_error("Cannot create export file.");
            outFile<<"===== Conversation with "<<otherName<<" ====="<<endl;
            outFile<<"Exported by: "<<currentUser.getFullName()<<endl;
            outFile<<"User ID: "<<currentUser.getUserID()<<endl;
            outFile<<"======================================="<<endl<<endl;
            string lines[500];
            int count=FileHandler::readLines("Messages.csv",lines,500);
            bool found=false;
            for(int i=0;i<count;i++){
                string parts[10];
                int n=FileHandler::parseCSV(lines[i],parts,10);
                if(n<4) continue;
                bool sent=(parts[0]==currentUser.getUserID()&&parts[1]==otherID);
                bool recv=(parts[0]==otherID&&parts[1]==currentUser.getUserID());
                if(sent||recv){
                    found=true;
                    if(sent) outFile<<"[You]        : "<<parts[3]<<" ("<<parts[2]<<")"<<endl;
                    else outFile<<"["<<otherName<<"] : "<<parts[3]<<" ("<<parts[2]<<")"<<endl;
                }
            }
            outFile.close();
            if(!found) UI::warning("No messages to export.");
            else{
                UI::success("Conversation exported to: "+filename);
            }
        }
        catch(runtime_error &e){UI::error(e.what());}
        catch(...){UI::error("Export failed.");}
        UI::pressKey();
    }

    void deleteAllMessages(){
        UI::header("DELETE MESSAGES");
        UI::breadcrumb("CHATO > Messages > Delete All");
        cout<<endl;
        colour(6);
        cout<<"  ╔══════════════════════════════════╗"<<endl;
        cout<<"  ║  Delete all your sent messages?  ║"<<endl;
        cout<<"  ╚══════════════════════════════════╝"<<endl;
        colour(15);
        cout<<endl;
        cout<<"  Confirm (Y/N) : ";
        showCursor();
        char ch=getch();
        hideCursor();
        cout<<(char)ch<<endl;
        if(ch=='Y'||ch=='y'){
            try{
                string lines[500];
                int count=FileHandler::readLines("Messages.csv",lines,500);
                string kept[500];
                int keptCount=0,deleted=0;
                for(int i=0;i<count;i++){
                    string parts[10];
                    FileHandler::parseCSV(lines[i],parts,10);
                    if(parts[0]!=currentUser.getUserID()){kept[keptCount]=lines[i];keptCount++;}
                    else deleted++;
                }
                FileHandler::writeAllLines("Messages.csv",kept,keptCount);
                UI::success(to_string(deleted)+" message(s) deleted.");
            }
            catch(...){UI::error("Error deleting messages.");}
        }else{
            UI::info("Cancelled.");
        }
        UI::pressKey();
    }
};

//==============================================
// CONTACTS CLASS
//==============================================
class Contacts{
private:
    User currentUser;
public:
    Contacts(User u){currentUser=u;}
    void viewAll(){
        UI::header("ALL CONTACTS");
        UI::breadcrumb("CHATO > Contacts > All");
        try{
            string lines[200];
            int count=FileHandler::readLines("Users.csv",lines,200);
            if(count==0) throw runtime_error("No users found.");
            int index=1;
            for(int i=0;i<count;i++){
                string parts[10];
                int n=FileHandler::parseCSV(lines[i],parts,10);
                if(n<5) continue;
                User temp(parts[0],parts[1],parts[2],parts[3],parts[4]);
                showUserCard(temp,index);
                index++;
                cout<<endl;
            }
        }
        catch(runtime_error &e){
            cout<<endl;
            colour(8);
            cout<<"  ╔══════════════════════════════════╗"<<endl;
            cout<<"  ║        No contacts found         ║"<<endl;
            cout<<"  ╚══════════════════════════════════╝"<<endl;
            colour(15);
        }
        catch(...){UI::error("Error loading contacts.");}
        UI::pressKey();
    }
    void searchByID(){
        bool cancelled=false;
        UI::header("SEARCH BY ID");
        UI::breadcrumb("CHATO > Contacts > Search ID");
        showCursor();
        string sid;
        while(true){
            try{
                UI::field("Enter User ID");
                sid=inputfield(cancelled);
                if(cancelled){
                    hideCursor();
                    return;
                }
                if(isBlank(sid)) throw invalid_argument("ID cannot be empty.");
                break;
            }
            catch(invalid_argument &e){UI::error(e.what());}
        }
        hideCursor();
        cout<<endl;
        try{
            string lines[200];
            int count=FileHandler::readLines("Users.csv",lines,200);
            bool found=false;
            for(int i=0;i<count;i++){
                string parts[10];
                int n=FileHandler::parseCSV(lines[i],parts,10);
                if(n>=5&&parts[0]==sid){
                    User temp(parts[0],parts[1],parts[2],parts[3],parts[4]);
                    showUserCard(temp,1);
                    found=true;break;
                }
            }
            if(!found) throw runtime_error("User not found.");
        }
        catch(runtime_error &e){UI::warning(e.what());}
        catch(...){UI::error("Error searching.");}
        UI::pressKey();
    }
    void searchByName(){
        bool cancelled=false;
        UI::header("SEARCH BY NAME");
        UI::breadcrumb("CHATO > Contacts > Search Name");
        showCursor();
        string sname;
        while(true){
            try{
                UI::field("Enter Name");
                sname=inputfield(cancelled);
                if(cancelled){
                    hideCursor();
                    return;
                }
                if(isBlank(sname)) throw invalid_argument("Name cannot be empty.");
                break;
            }
            catch(invalid_argument &e){UI::error(e.what());}
        }
        hideCursor();
        cout<<endl;
        try{
            string lines[200];
            int count=FileHandler::readLines("Users.csv",lines,200);
            bool found=false;
            int index=1;
            for(int i=0;i<count;i++){
                string parts[10];
                int n=FileHandler::parseCSV(lines[i],parts,10);
                if(n<5) continue;
                // Case insensitive
                string fn=parts[1],ln=parts[2],kw=sname;
                for(int j=0;j<(int)fn.length();j++) if(fn[j]>='A'&&fn[j]<='Z') fn[j]+=32;
                for(int j=0;j<(int)ln.length();j++) if(ln[j]>='A'&&ln[j]<='Z') ln[j]+=32;
                for(int j=0;j<(int)kw.length();j++) if(kw[j]>='A'&&kw[j]<='Z') kw[j]+=32;
                if(fn.find(kw)!=string::npos||ln.find(kw)!=string::npos){
                    User temp(parts[0],parts[1],parts[2],parts[3],parts[4]);
                    showUserCard(temp,index);
                    index++;cout<<endl;
                    found=true;
                }
            }
            if(!found) throw runtime_error("No users found with that name.");
        }
        catch(runtime_error &e){UI::warning(e.what());}
        catch(...){UI::error("Error searching.");}
        UI::pressKey();
    }
};

//==============================================
// SETTINGS CLASS
//==============================================
class Settings{
private:
    User &currentUser;
public:
    Settings(User &u):currentUser(u){}

    void viewProfile(){
        currentUser.display();
        UI::pressKey();
    }

    void editName(){
        bool cancelled=false;
        UI::header("EDIT NAME");
        UI::breadcrumb("CHATO > Settings > Edit Name");
        showCursor();
        string fn,ln;
        while(true){
            try{
                UI::field("New First Name");
                fn=inputfield(cancelled);
                if(cancelled){
                    hideCursor();
                    return ;
                }
                if(isBlank(fn)) throw invalid_argument("First name cannot be empty.");
                break;
            }
            catch(invalid_argument &e){UI::error(e.what());}
        }
        while(true){
            try{
                UI::field("New Last Name ");
                ln=inputfield(cancelled);
                if(cancelled) return;
                if(isBlank(ln)) throw invalid_argument("Last name cannot be empty.");
                break;
            }
            catch(invalid_argument &e){UI::error(e.what());}
        }
        hideCursor();
        try{
            currentUser.setFirstName(fn);
            currentUser.setLastName(ln);
            currentUser.updateInFile(currentUser.getPassword(),currentUser.getStatus());
            UI::success("Name updated successfully!");
        }
        catch(...){UI::error("Error updating name.");}
        UI::pressKey();
    }

    void changeStatus(){
        bool cancelled=false;
        UI::header("CHANGE STATUS");
        UI::breadcrumb("CHATO > Settings > Status");
        showCursor();
        UI::label("  Current : ",currentUser.getStatus());
        cout<<endl;
        while(true){
            try{
                UI::field("New Status");
                string ns=inputfield(cancelled);
                if(cancelled){
                    hideCursor();
                    return ;
                }
                if(isBlank(ns)) throw invalid_argument("Status cannot be empty.");
                currentUser.setStatus(ns);
                currentUser.updateInFile(currentUser.getPassword(),ns);
                hideCursor();
                UI::success("Status updated!");
                break;
            }
            catch(invalid_argument &e){UI::error(e.what());}
            catch(...){UI::error("Error updating status.");break;}
        }
        UI::pressKey();
    }

    void changePassword(){
        UI::header("CHANGE PASSWORD");
        UI::breadcrumb("CHATO > Settings > Password");
        showCursor();
        try{
            UI::field("Current Password");
            string oldpw=getpassword();
            if(oldpw!=currentUser.getPassword()) throw runtime_error("Incorrect current password.");
            string newpw,confirmpw;
            while(true){
                try{
                    UI::field("New Password    ");
                    newpw=getpassword();
                    if(newpw.length()<4) throw invalid_argument("Min 4 characters.");
                    UI::field("Confirm Password");
                    confirmpw=getpassword();
                    if(newpw!=confirmpw) throw invalid_argument("Passwords do not match.");
                    break;
                }
                catch(invalid_argument &e){UI::error(e.what());}
            }
            currentUser.setPassword(newpw);
            currentUser.updateInFile(newpw,currentUser.getStatus());
            hideCursor();
            UI::success("Password changed!");
        }
        catch(runtime_error &e){hideCursor();UI::error(e.what());}
        catch(...){UI::error("Error changing password.");}
        UI::pressKey();
    }

    void viewAllUsers(){
        UI::header("ALL USERS");
        UI::breadcrumb("CHATO > Settings > Users");
        try{
            string lines[200];
            int count=FileHandler::readLines("Users.csv",lines,200);
            if(count==0) throw runtime_error("No users found.");
            int index=1;
            for(int i=0;i<count;i++){
                string parts[10];
                int n=FileHandler::parseCSV(lines[i],parts,10);
                if(n<5) continue;
                User temp(parts[0],parts[1],parts[2],parts[3],parts[4]);
                showUserCard(temp,index);
                index++;cout<<endl;
            }
        }
        catch(runtime_error &e){UI::warning(e.what());}
        catch(...){UI::error("Error loading users.");}
        UI::pressKey();
    }

};

//==============================================
// MENU CLASS
// OOP Concept: Encapsulation, Objects
//==============================================
class Menu{
private:
    int choice;
    int total;
    string items[15];
public:
    Menu(){choice=0;total=0;}
    void setItems(string arr[],int n){
        total=n;
        for(int i=0;i<n;i++) items[i]=arr[i];
    }
    void setChoice(int c){choice=c;}
    int getChoice(){return choice;}
    void render(string title,string path){
        UI::clear();
        colour(3);
        cout<<"  ╔══════════════════════════════════╗"<<endl;
        cout<<"  ║";colour(11);
        int spaces=(34-(int)title.length())/2;
        for(int i=0;i<spaces;i++) cout<<" ";
        cout<<title;
        for(int i=0;i<34-(int)title.length()-spaces;i++) cout<<" ";
        colour(3);cout<<"║"<<endl;
        cout<<"  ╚══════════════════════════════════╝"<<endl;
        colour(15);cout<<endl;
        colour(8);cout<<"  "<<path<<endl;
        UI::thinLine();
        cout<<endl;
        for(int i=0;i<total;i++){
            if(i==choice){
                cout<<"  ";
                colour(112);
                cout<<" "<<items[i]<<" "<<endl;
                colour(15);
            }else{
                colour(15);
                cout<<"  "<<items[i]<<endl;
            }
        }
        UI::menuFooter();
    }
    InputEvent handleKey(){
        try{
            int key=getch();
            if(key==224){
                key=getch();
                if(key==72){choice--;if(choice<0)choice=total-1;return InputEvent::MOVE_UP;}
                if(key==80){choice++;if(choice>=total)choice=0;return InputEvent::MOVE_DOWN;}
            }
            else if(key==13) return InputEvent::SELECT;
        }
        catch(...){return InputEvent::NONE;}
        return InputEvent::NONE;
    }
};

//==============================================
// MAIN APPLICATION CLASS
// OOP Concept: Composition
//==============================================
class Chato{
private:
    Menu mainMenu;
    Authentication auth;
    User loggedUser;

    void showDashboard(){
        UI::clear();
        Chat chatCounter(loggedUser);
        int inbox=chatCounter.getInboxCount();
        int sent=chatCounter.getSentCount();
        hideCursor();
        
        const int interiorWidth = 34;
        
        colour(3);
        cout<<"  ╔══════════════════════════════════╗"<<endl;
        
        // ==============================================
        // 1. CENTERED WELCOME MESSAGE
        // ==============================================
        string welcomeMsg = "Welcome, " + loggedUser.getFullName();
        int totalWelcomeSpaces = interiorWidth - (int)welcomeMsg.length();
        int welcomeLeft = totalWelcomeSpaces / 2;
        int welcomeRight = totalWelcomeSpaces - welcomeLeft; // Handles odd-numbered space remainders safely
        
        cout<<"  ║";
        for(int i=0; i<welcomeLeft; i++) cout<<" ";
        colour(11); cout<<welcomeMsg;
        colour(3);
        for(int i=0; i<welcomeRight; i++) cout<<" ";
        cout<<"║"<<endl;
        
        cout<<"  ╠══════════════════════════════════╣"<<endl;
        
        // ==============================================
        // 2. CENTERED INBOX COUNTER
        // ==============================================
        string inboxText = "Inbox  : " + to_string(inbox) + " message(s)";
        int totalInboxSpaces = interiorWidth - (int)inboxText.length();
        int inboxLeft = totalInboxSpaces / 2;
        int inboxRight = totalInboxSpaces - inboxLeft;
        
        cout<<"  ║";
        for(int i=0; i<inboxLeft; i++) cout<<" ";
        colour(12); cout<<"Inbox  : ";
        colour(15); cout<<inbox<<" message(s)";
        colour(3);
        for(int i=0; i<inboxRight; i++) cout<<" ";
        cout<<"║"<<endl;
        
        // ==============================================
        // 3. CENTERED SENT COUNTER
        // ==============================================
        string sentText = "Sent   : " + to_string(sent) + " message(s)";
        int totalSentSpaces = interiorWidth - (int)sentText.length();
        int sentLeft = totalSentSpaces / 2;
        int sentRight = totalSentSpaces - sentLeft;
        
        cout<<"  ║";
        for(int i=0; i<sentLeft; i++) cout<<" ";
        colour(2);  cout<<"Sent   : ";
        colour(15); cout<<sent<<" message(s)";
        colour(3);
        for(int i=0; i<sentRight; i++) cout<<" ";
        cout<<"║"<<endl;
        
        cout<<"  ╚══════════════════════════════════╝"<<endl;
        cout << "  "; // Aligns it perfectly with the left edge of the boxes
        colour(10); // Light Green color code
        cout << " • Status: " << loggedUser.getStatus() << endl;
        colour(15);cout<<endl;
    }

    void runMessagesMenu(){
        Menu msgMenu;
        string items[]={"Send Message","View Inbox","View Sent","View Conversation","Export Conversation","Delete All Sent","Back"};
        msgMenu.setItems(items,7);
        msgMenu.setChoice(0);
        Chat chat(loggedUser);
        while(true){
            msgMenu.render("MESSAGES","CHATO > Messages");
            InputEvent ev=msgMenu.handleKey();
            if(ev==InputEvent::SELECT){
                int c=msgMenu.getChoice();
                if(c==0) chat.sendMessage();
                else if(c==1) chat.viewInbox();
                else if(c==2) chat.viewSent();
                else if(c==3) chat.viewConversation();
                else if(c==4) chat.exportConversation();
                else if(c==5) chat.deleteAllMessages();
                else if(c==6) return;
            }
        }
    }

    void runContactsMenu(){
        Menu contactsMenu;
        string items[]={"View All Contacts","Search by ID","Search by Name","Back"};
        contactsMenu.setItems(items,4);
        contactsMenu.setChoice(0);
        Contacts contacts(loggedUser);
        while(true){
            contactsMenu.render("CONTACTS","CHATO > Contacts");
            InputEvent ev=contactsMenu.handleKey();
            if(ev==InputEvent::SELECT){
                int c=contactsMenu.getChoice();
                if(c==0) contacts.viewAll();
                else if(c==1) contacts.searchByID();
                else if(c==2) contacts.searchByName();
                else if(c==3) return;
            }
        }
    }

    void runSettingsMenu(){
        Menu settingsMenu;
        string items[]={"View Profile","Edit Name","Change Status","Change Password","View All Users","Back"};
        settingsMenu.setItems(items,6);
        settingsMenu.setChoice(0);
        Settings settings(loggedUser);
        while(true){
            settingsMenu.render("SETTINGS","CHATO > Settings");
            InputEvent ev=settingsMenu.handleKey();
            if(ev==InputEvent::SELECT){
                int c=settingsMenu.getChoice();
                if(c==0) settings.viewProfile();
                else if(c==1) settings.editName();
                else if(c==2) settings.changeStatus();
                else if(c==3) settings.changePassword();
                else if(c==4) settings.viewAllUsers();
                else if(c==5) return;
            }
        }
    }

    void runDashboardMenu(){
        Menu dashboard;
        string items[]={"Messages","Contacts","Settings","About","Help","Logout"};
        dashboard.setItems(items,6);
        dashboard.setChoice(0);
        while(true){
            showDashboard();
            colour(8);
            cout<<"  "<<"CHATO > Dashboard"<<endl;
            UI::thinLine();
            cout<<endl;
            int c=dashboard.getChoice();
            string arr[]={"Messages","Contacts","Settings","About","Help","Logout"};
            for(int i=0;i<6;i++){
                if(i==c){
                    cout<<"  ";
                    colour(112);
                    cout<<" "<<arr[i]<<" "<<endl;
                    colour(15);}
                else{
                    colour(15);
                    cout<<"  "<<arr[i]<<endl;}
            }
            UI::menuFooter();
            InputEvent ev=dashboard.handleKey();
            if(ev==InputEvent::SELECT){
                if(c==0) runMessagesMenu();
                else if(c==1) runContactsMenu();
                else if(c==2) runSettingsMenu();
                else if(c==3) UI::about();
                else if(c==4) UI::help();
                else if(c==5){
                    // Confirm logout
                    UI::clear();
                    cout<<endl<<endl;
                    colour(6);
                    cout<<"  ╔══════════════════════════════════╗"<<endl;
                    cout<<"  ║      Confirm Logout? (Y/N)       ║"<<endl;
                    cout<<"  ╚══════════════════════════════════╝"<<endl;
                    colour(15);
                    cout<<endl<<"  Choice : ";
                    showCursor();
                    char ch=getch();
                    hideCursor();
                    cout<<(char)ch<<endl;
                    if(ch=='Y'||ch=='y'){
                        UI::clear();
                        colour(2);
                        cout<<endl<<endl;
                        cout<<"  ╔══════════════════════════════════╗"<<endl;
                        cout<<"  ║      Logged out successfully     ║"<<endl;
                        cout<<"  ╚══════════════════════════════════╝"<<endl;
                        colour(15);
                        this_thread::sleep_for(chrono::milliseconds(1200));
                        return;
                    }
                }
            }
        }
    }

public:
    Chato(){
        string items[]={"Register","Login","About","Help","Exit"};
        mainMenu.setItems(items,5);
        mainMenu.setChoice(0);
    }

    void run(){
        hideCursor();
        try{
            UI::splash();
            while(true){
                mainMenu.render("CHATO","CHATO > Main Menu");
                InputEvent ev=mainMenu.handleKey();
                if(ev==InputEvent::SELECT){
                    int c=mainMenu.getChoice();
                    if(c==0) auth.registerUser();
                    else if(c==1){
                        User u=auth.loginUser();
                        if(u.getUserID()!=""){
                            loggedUser=u;
                            runDashboardMenu();
                        }
                    }
                    else if(c==2) UI::about();
                    else if(c==3) UI::help();
                    else if(c==4){
                        UI::clear();
                        cout<<endl<<endl;
                        hideCursor();
                        colour(3);
                        cout<<"  ╔══════════════════════════════════╗"<<endl;
                        colour(11);
                        cout<<"  ║      Thank you for using         ║"<<endl;
                        cout<<"  ║          C H A T O !             ║"<<endl;
                        colour(3);
                        cout<<"  ╚══════════════════════════════════╝"<<endl;
                        colour(15);
                        this_thread::sleep_for(chrono::milliseconds(1500));
                        return;
                    }
                }
            }
        }
        catch(exception &e){
            UI::error("Critical Error: "+string(e.what()));
            UI::pressKey();
        }
        catch(...){
            UI::error("Unknown critical error.");
            UI::pressKey();
        }
    }
};

//==============================================
// MAIN
//==============================================
int main(){
    try{
        srand(time(0));
        colour(15);
        SetConsoleOutputCP(CP_UTF8);
        SetConsoleCP(CP_UTF8);
        Chato app;
        hideCursor();
        app.run();
    }
    catch(exception &e){
        cout<<"Fatal Error: "<<e.what()<<endl;
        getch();
    }
    catch(...){
        cout<<"Fatal unknown error."<<endl;
        getch();
    }
    return 0;
}