//ohhhhhhhhhhhh
#include <iostream>
#include <cstring>
#include <string>
#include "user.h"
#ifndef MAIN_CPP_BOOK_H
#define MAIN_CPP_BOOK_H

using namespace std;

class book{
public:
    char name[61];
    char isbn[21];
    char author[61];
    char keyword[61];
    int quantity;
    double price;
    book() = default;
    book(double p,int q,const string the_name,const string ISBN,const string the_author,const string key);
    bool operator<(book &other);
    void showlist()const;
};

class bill{
public:
    char userid[31];
    char isbn[21];
    double bonus;
    int quantity;
    bill() = default;
    bill(const string &id,const string &ISBN,double bo,int q);
};

class logtrace{
public:
    char name[61] = "";
    char the_trace[250] = "";
    double sum = 0;
    logtrace() = default;
    logtrace(const string &the_name,const string &tr,double s = 0);
};

class report_employer{
public:
    char name[61] = "";
    char the_trace[250] = "";
    double sum = 0;
    report_employer() = default;
    report_employer(const string &the_name,const string &tr,double s = 0);
};

class report_finance{
public:
    char the_trace[250] = "";
    double sum = 0;
    report_finance() = default;
    report_finance(const string &tr,double s);
};

class finance{
public:
    double cost = 0;
    double benefit = 0;
    finance() = default;
    finance(double co,double be);
};

#endif