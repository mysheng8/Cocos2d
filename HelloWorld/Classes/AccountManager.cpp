#include "AccountManager.h"

AccountManager& AccountManager::sharedAccountManager()
{
	static AccountManager _manager;
	return _manager;
}

Account* AccountManager::createAccount(string str,Callback *action)
{
	Account *a=getAccount(str);
	if(a==NULL)
	{
		a=new Account(action);
		m_accountMap.insert(pair<string,Account*>(str,a));
	}
	return a;
}

Account* AccountManager::getAccount(string str)
{
	map<string,Account*>::const_iterator iter;

	iter=m_accountMap.find(str);
	if(iter==m_accountMap.end())
		return NULL;
	else
		return iter->second;
}