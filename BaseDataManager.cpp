//
//  BaseDataManager.cpp
//  threeKingdoms
//
//  Created by .m on 13-12-26.
//
//

#include "BaseDataManager.h"
#include "cocos2d/external/tinyxml2/tinyxml2.h"

bool BaseDataManager::init()
{
    return true;
}

void BaseDataManager::removeAllXml()
{
    //xmlDic->removeAllObjects();
	xmlDic.clear();
}
/*
*
<?xml version="1.0" encoding="UTF-8"?>
<root>
	<data>
		<tId type="int" multiLanguage="0">90001</tId>
		<type type="int" multiLanguage="0">1</type>
		<desc type="String" multiLanguage="1">config.xls_7_90001_2</desc>
	</data>
	<data>
		<tId type="int" multiLanguage="0">90002</tId>
		<type type="int" multiLanguage="0">1</type>
		<desc type="String" multiLanguage="1">config.xls_7_90002_2</desc>
	</data>
</root>
*/

ValueMap BaseDataManager::getXml(const string& xmlPath)
{
	string path("xml/");
	tinyxml2::XMLDocument* pDoc = new tinyxml2::XMLDocument();
	tinyxml2::XMLError errorid = pDoc->LoadFile((path + xmlPath).c_str());
	if (errorid != 0)
	{
		return xmlDic;
	}
	//root节点
	tinyxml2::XMLElement* rootEle = pDoc->RootElement();
	//第一个节点的属性
	tinyxml2::XMLElement* dataEle = rootEle->FirstChildElement();//data节点
	tinyxml2::XMLElement* nextDataEle = dataEle->ToElement();

	//log("%s",nextDataEle->Value());
	while (nextDataEle)
	{
		tinyxml2::XMLElement* roldId = nextDataEle->FirstChildElement();//roldId节点
		const tinyxml2::XMLAttribute* roldIdAtt = roldId->FirstAttribute();//roldId的第一个属性
		tinyxml2::XMLElement* nextEle = roldId->ToElement();
		ValueMap subDic;
		string id = nextEle->FirstChild()->Value();
		while (nextEle)
		{
			string key = nextEle->Value();
			string val = nextEle->FirstChild()->Value();
			subDic[key] = val;
			nextEle = nextEle->NextSiblingElement();
	//		log("%s,%s",key.c_str(),val.c_str());
		}
		xmlDic[id] = subDic;
		nextDataEle = nextDataEle->NextSiblingElement();
	}
	delete pDoc;
	
   return xmlDic;
}

string BaseDataManager::getLan(string param)
{
    if(lanDic.empty()){
        loadLan();
    }
	//string result = lanDic.at(param.c_str()).asString();
	string result = Value(lanDic[param]).asString();
	if(result.empty()){
        return string("missLanguage");
    }else{
        return result;
    }
}

void BaseDataManager::loadLan()
{
    string path = "language/conf_lang.txt";
	//lanDic = FileUtils::getInstance()->getValueMapFromFile(path);
	string content = FileUtils::getInstance()->getStringFromFile(path);

	//按行分割
	vector<string> line = split(content,"\n");
	for (const auto& m : line)
	{
		//log("%s",Value(m).asString().c_str());
		//按“=”分割
		vector<string> lan = split(Value(m).asString(),"=");
		//for (const auto& n : lan)
		//{
		//	log("%s",Value(n).asString().c_str());
		//}
		lanDic[lan[0]] = lan[1];
	}
	

}

//C++按符号分割字符串
vector<string> BaseDataManager::split(string str,string pattern)
{
	vector<string> ret;
	if (pattern.empty())
	{
		return ret;
	}
	size_t start = 0,index = str.find_first_of(pattern,0);
	while (index!=str.npos)
	{
		if (start!=index)
		{
			ret.push_back(str.substr(start,index-start));
			start = index + 1;
			index = str.find_first_of(pattern,start);
		}
	}

	if (!str.substr(start).empty())
	{
		ret.push_back(str.substr(start));
	}
	return ret;
}
