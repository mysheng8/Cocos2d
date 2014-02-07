#ifndef __ACCOUNTMANAGER_H__
#define __ACCOUNTMANAGER_H__

#include <stdio.h>
#include"CheckerBoard.h"

using namespace std;

class Callback
{
public:
	virtual void operator()(){};
};

class OnRemoveCallback
{
public:
	OnRemoveCallback(CheckerBoard *parent=0){m_parent=parent;};
	void operator()()
	{
		if(m_parent)
			m_parent->onRemovedPieces();
	};
private:
	CheckerBoard *m_parent;
};

class OnDropCallback
{
public:
	OnDropCallback(CheckerBoard *parent=0){m_parent=parent;};
	void operator()()
	{
		if(m_parent)
			m_parent->onDropPieces();
	};
private:
	CheckerBoard *m_parent;
};

class Account
{
public:
	Account(Callback *action=0):count(0),callback(action){};
	void Add(){++count;};
	void Sub(){--count;if(count==0)(*callback)();};
	void setCallback(Callback *action){callback=action;};
private:
	unsigned int count;
	Callback *callback;
};

class AccountManager
{
public:
	static AccountManager& sharedAccountManager();
	Account* createAccount(string str,Callback *action=0);
	Account* getAccount(string str);
	void removeAccount(Account* a);
private:
	map<string,Account*> m_accountMap;
};

#endif