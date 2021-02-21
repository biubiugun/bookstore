#include "Storerecord.h"

using namespace std;

book::book(double p, int q, const string the_name, const string ISBN, const string the_author, const string key) {
    price = p;
    quantity = q;
    strcpy(name,the_name.c_str());
    strcpy(isbn,ISBN.c_str());
    strcpy(author,the_author.c_str());
    strcpy(keyword,key.c_str());
}

bool book::operator<(book &other) {
    if(strcmp(isbn,other.isbn) < 0)return true;
    else return false;
}

void book::showlist() const {
    printf("%s\t", isbn);
    printf("%s\t", name);
    printf("%s\t", author);
    printf("%s\t", keyword);
    printf("%.2lf\t",price);
    printf("%d\n",quantity);
}

bill::bill(const string &id, const string &ISBN, double bo, int q) {
    strcmp(userid,id.c_str());
    strcmp(isbn,ISBN.c_str());
    bonus = bo;
    quantity = q;
}

logtrace::logtrace(const string &the_name, const string &tr, double s) {
    strcpy(name,the_name.c_str());
    strcpy(the_trace,tr.c_str());
    sum = s;
}

report_employer::report_employer(const string &the_name, const string &tr, double s) {
    strcpy(name,the_name.c_str());
    strcpy(the_trace,tr.c_str());
    sum = s;
}

report_finance::report_finance(const string &tr, double s) {
    strcpy(the_trace,tr.c_str());
    sum = s;
}

finance::finance(double co, double be) {
    cost = co;
    benefit = be;
}