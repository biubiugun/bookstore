#ifndef MAIN_CPP_USER_H
#define MAIN_CPP_USER_H
#include "unrolledlist.h"
#include "Storerecord.h"
#include <cstring>
#define bookfile "book.dat"
#define financefile "finance.dat"
#define billfile "bill.dat"
#define useridfile "userid.dat"
#define keyfile "keyfile.dat"
#define USER "user.dat"
#define isbnfile "isbn.dat"
#define namefile "name.dat"
#define authorfile "author.dat"
#define trace "logtrace.dat"
#define reportemployer "reporte.dat"
#define reportfinance "reportf.dat"
using namespace std;

class user{
public:
    int priority = 0;
    char password[31] = "";
    char userid[31] = "";
    char name[31] = "";
    int select_book = -1;
    user(){};
    user(const string &pass,const string &id,const string &the_name,int p);
};

bool checkpassword(const string &password);

bool checkuserid(const string &id);

bool checkname(const string &name);

bool checkkeyword(const string &keyword);

bool checkisbn(const string &isbn);

bool checkauthor(const string &author);

void su(const string &userid,string &password);

void Register(user &obj);

void logout();

void useradd(user &obj);

void deleteuser(string &id);

void changepassword(const string &userid,const string &newp,const string &oldp);

void select(const string &isbn);

void modifyname(const string& new_name);

void modifyauthor(const string& new_author);

void modifykeyword(const string& new_keyword);

void modifyisbn(const string& new_isbn);

void modifyprice(double new_price);

void import(int quantity,double cost_price);

void show();

void show(const string &target,unrolledlist &a);

void show_finance();

void show_finance(int times);

void buy(string &number,int quantity);

void run_program(string &line);

void get_command(string &a,string &key);

void clear();

void get_keyword(const string &line,vector<string>&keywords);

void initialize();

bool check(const string &key,const string &obj);

template<class T>
T read(const string &file,int offset = 0){
    fstream in;
    in.open(file,ios::in | ios::binary);
    if(!in)throw("error");
    in.seekg(offset);
    T temp;
    in.read(reinterpret_cast<char*>(&temp),sizeof(T));
    in.close();
    return temp;
}

template<class T>
int write(const string &file,T &obj,int offset = -1){
    fstream out;
    out.open(file,ios::in | ios::out | ios::binary);
    if(!out)throw("error");
    if(offset == -1){
        out.seekp(0,ios::end);
        offset = out.tellp();
    }else{
        out.seekp(offset);
    }
    out.write(reinterpret_cast<char*>(&obj),sizeof(T));
    out.close();
    return offset;
}




#endif