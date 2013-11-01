#ifndef __PROPFACTORY_H__
#define __PROPFACTORY_H__

#include<stdio.h>
#include<map>
using namespace std;

typedef void*(*createClass)(void);
class PropFactory
{
public:
	PropFactory();
	virtual ~PropFactory();
	void* GetClassByName(string className);
	void registClass(string name,createClass method);
	static PropFactory& sharedClassFactory();
private:
	map<string,createClass> m_classMap;
};

claaa RegistClass
{
public:
	RegistClass(string name,createClass method)
	{
		PropFactory::sharedClassFactory().registClass(name,method);
	}
}

#define DECLARE_CLASS(className)string className##Name ;static RegistClass* m_className##dc ;
#define IMPLEMENT_CLASS(className)RegistClass* className::m_className##dc = new RegistClass(#className, className::createInstance) ;


#endif