#include "PropFactory.h"

void* PropFactory::GetClassByName(string className)
{
	map<string,createClass>::const_iterator iter;

	iter=m_classMap.find(className);
	if(iter==m_classMap.end())
		return NULL;
	else
		return iter->second();
}

void PropFactory::registClass(string name,createClass method)
{
	m_classMap.insert(pair<string,createClass>(name,method));
}

PropFactory& PropFactory::sharedClassFactory()
{
	static PropFactory _sharedClassFactory;
	return _sharedClassFactory;
}