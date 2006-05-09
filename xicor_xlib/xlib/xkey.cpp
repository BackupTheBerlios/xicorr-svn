#include "xkey.h"
#include "xencoding_table.h"

#include <iostream>

namespace xicor {
namespace xlib {

	xKey::xKey()
		:encoding_table(xEncodingTable::makeObject(RUSSIAN))
	{
	}
	
	xKey::xKey(KeySym _key)
		:key(_key),
		encoding_table(xEncodingTable::makeObject(RUSSIAN))
	{
	}
	
	xKey::xKey(KeySym _key, KeySym _modifier) throw(XlibException)
		:key(_key), modifier(_modifier),
		encoding_table(xEncodingTable::makeObject(RUSSIAN))
	{	
		char *strPtr = NULL;
		
		//TODO:
		KeySym latinKS = key;//encoding_table->getLatinKeysym(key, RUSSIAN);
		latinChar = encoding_table->getSpecialCharFromKeysym(key);
			
		if ((latinKS != None) && !latinChar) {
			strPtr = XKeysymToString (latinKS);
			latinChar = strPtr[0];
			XFree(strPtr);
		}
		std::cout << latinChar << std::endl;
	}
	
	bool xKey::isChar() throw(XlibException)
	{
		return latinChar?true:false;
	}
	
	bool xKey::isModified() throw(XlibException)
	{
		if (modifier != None)
			return true;
		return false;
	}
		
	char xKey::getChar() throw(XlibException)
	{
		return latinChar;
	}
	
	KeySym xKey::getKeysym() throw(XlibException)
	{
		return key;
	}
	
	std::string xKey::getModifier() throw(XlibException)
	{
		return "";
	}

} //namespace xlib
} //namespace xicor
