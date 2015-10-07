#pragma once

#ifndef INSTANCE
#define INSTANCE(_cName) _cName::getInstance()
#define CLASS_INSTANCE(_cName) \
static _cName* getInstance() \
{\
static _cName* pIns = nullptr;\
if (pIns == nullptr)\
{\
pIns = new _cName();\
pIns->init();\
}\
return pIns;\
}\

#endif // !INSTANCE
