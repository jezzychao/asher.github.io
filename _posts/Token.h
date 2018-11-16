// create a class to manager union
#pragma once
#include <string>
#include <iostream>

class Token
{
    friend void printval(std::ostream &, const Token &);

  public:
    Token();
    Token(const Token &);
    Token &operator=(const Token &);
    ~Token();
    Token(Token &&);
    Token &operator=(Token &&);

    Token &operator=(int);
    Token &operator=(double);
    Token &operator=(char);
    Token &operator=(const std::string &);

  private:
    union {
        int ival;
        double dval;
        char cval;
        std::string sval;
    };
    enum
    {
        INT,
        DBL,
        CHAR,
        STR
    } tok;
    void copy(const Token &);
};

void printval(std::ostream &os, const Token &t)
{
    switch (t.tok)
    {
    case Token::INT:
        os << t.ival;
        break;
    case Token::DBL:
        os << t.dval;
        break;
    case Token::CHAR:
        os << t.cval;
        break;
    case Token::STR:
        os << t.sval;
        break;
    }
}

Token::Token() : ival(0), tok(INT)
{
}

Token::Token(const Token &t) : tok(t.tok)
{
    copy(t);
}

Token &Token::operator=(const Token &t)
{
    if (tok == STR && t.tok != STR)
        sval.~basic_string();
    if (tok == STR && t.tok == STR)
        sval = t.sval;
    else
        copy(t);
    tok = t.tok;
    return *this;
}

Token::~Token()
{
    if (tok == STR)
        sval.~basic_string();
}

Token::Token(Token &&t)
    : tok(t.tok)
{
    if (t.tok == STR)
        new (&sval) std::string(std::move(t.sval));
    else
        copy(t);
}

Token &Token::operator=(Token &&t)
{
    if (tok == STR && t.tok != STR)
        sval.~basic_string();
    if (tok == STR && t.tok == STR)
        sval = std::move(t.sval);
    else if (tok != STR && t.tok == STR)
        new (&sval) std::string(std::move(t.sval));
    else
        copy(t);
    tok = t.tok;
    return *this;
}

Token &Token::operator=(int i)
{
    if (tok == STR)
        sval.~basic_string();
    ival = i;
    tok = INT;
    return *this;
}

Token &Token::operator=(double d)
{
    if (tok == STR)
        sval.~basic_string();
    dval = d;
    tok = DBL;
    return *this;
}

Token &Token::operator=(char c)
{
    if (tok == STR)
        sval.~basic_string();
    cval = c;
    tok = CHAR;
    return *this;
}

Token &Token::operator=(const std::string &s)
{
    if (tok != STR)
        new (&sval) std::string(s);
    else
        sval = s;
    tok = STR;
    return *this;
}

void Token::copy(const Token &t)
{
    switch (t.tok)
    {
    case INT:
        ival = t.ival;
        break;
    case DBL:
        dval = t.dval;
        break;
    case CHAR:
        cval = t.cval;
        break;
    case STR:
        new (&sval) std::string(t.sval);
        break;
    }
}
