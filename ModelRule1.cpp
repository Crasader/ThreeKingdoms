//
//  ModelRule.cpp
//  threeKingdoms
//
//  Created by .m on 13-12-26.
//
//

#include "ModelRule.h"
#include "BaseDataManager.h"
//#include "SkillRule.h"

bool ModelRule::init()
{
    //lastId = -1;
    //mainDic = NULL;
    return true;
}

string ModelRule::getModelFrameNameByModelId(int modelId,RoleStatus status,bool containPng)
{
    string result = Value(modelId).asString();
    switch (status) {
        case RoleStatusStand:
			result += "_stand";
            break;
        case RoleStatusWalk:
			result += "_walk";
            break;
        case RoleStatusRun:
			result += "_run";
            break;
        case RoleStatusAttack:
			result += "_attack";
            break;
        case RoleStatusAttack_1:
			result += "_attack_1";
            break;
        case RoleStatusAttack_2:
			result += "_attack_2";
            break;
        case RoleStatusAttack_3:
			result += "_attack_3";
            break;
        case RoleStatusAttack_4:
			result += "_attack_4";
            break;
        case RoleStatusAttack_5:
			result += "_attack_5";
            break;
        case RoleStatusHurt:
			result += "_hurt";
            break;
        case RoleStatusDie:
			result += "_die";
            break;
        case RoleStatusSkill:
			result += "_skill";
            break;
        case RoleStatusAttackEffect:
			result += "_attack_effect";
            break;
        case RoleStatusSkillEffect:
			result += "_skill_effect";
            break;
        default:
            break;
    }
    if(containPng){
		return result + ".png";
    }else{
        return result;
    }
}

string ModelRule::getModelFirstFrameNameByModelId(int modelId,RoleStatus status)
{
    string result = getModelFrameNameByModelId(modelId,status);
	result += "_0000.png";
    return result;
}

//string ModelRule::getModelPath(int modelId)
//{
//    CCString* result = CCString::createWithFormat("model/%d/",modelId);
//    return result->getCString();
//}
//
//CCPoint ModelRule::getModelAnchorPoint(int modelId)
//{
//    float _x = INSTANCE(StringUtils)->stringToFloat(getModelAttribute(modelId, "pointX"));
//    float _y = INSTANCE(StringUtils)->stringToFloat(getModelAttribute(modelId, "pointY"));
//    return ccp(_x, _y);
//}
//
//CCPoint ModelRule::getModelSkillEffectAnchorPoint(int modelId)
//{
//    float _x = INSTANCE(StringUtils)->stringToFloat(getModelAttribute(modelId, "skillpointX"));
//    float _y = INSTANCE(StringUtils)->stringToFloat(getModelAttribute(modelId, "skillpointY"));
//    return ccp(_x, _y);
//}
//
//CCPoint ModelRule::getModelAttackEffectAnchorPoint(int modelId)
//{
//    float _x = INSTANCE(StringUtils)->stringToFloat(getModelAttribute(modelId, "attackpointX"));
//    float _y = INSTANCE(StringUtils)->stringToFloat(getModelAttribute(modelId, "attackpointY"));
//    return ccp(_x, _y);
//}
//
//CCSize ModelRule::getModelHurtSize(int modelId)
//{
//    string temp = getModelAttribute(modelId, "size");
//    if(temp == "0"){
//        return CCSizeMake(0, 0);
//    }
//    vector<int> size = INSTANCE(StringUtils)->getIntVectorFromString(temp, "_");
//    return CCSizeMake(size[0], size[1]);
//}
//
//CCSize ModelRule::getModelAttackSize(int modelId)
//{
//    string temp = getModelAttribute(modelId, "AttackSize");
//    if(temp == "0"){
//        return CCSizeMake(0, 0);
//    }
//    vector<int> size = INSTANCE(StringUtils)->getIntVectorFromString(temp, "_");
//    return CCSizeMake(size[0], size[1]);
//}
//
//CCPoint ModelRule::getSkillHitAnchorPoint(int skillId)
//{
//    return INSTANCE(SkillRule)->getSkillHitAnchorPoint(skillId);
//}
//
//string ModelRule::getSkillHitFrameName(int skillId,bool containPng)
//{
//    string result = CCString::createWithFormat("%d_skill_hit",skillId)->getCString();
//    if(containPng){
//        result.append(".png");
//    }
//    return result;
//}
//
//CCDictionary* ModelRule::getModelDic(int modelId)
//{
//    if(mainDic == NULL){
//        mainDic = INSTANCE(BaseDataManager)->getXml(ModelConfigXml);
//    }
//    if(lastId != modelId){
//        lastId = modelId;
//        lastSubDic = (CCDictionary *) mainDic->objectForKey(INSTANCE(StringUtils)->intToString(modelId));
//    }
//    
//    return lastSubDic;
//}
//
////string ModelRule::getModelAttribute(int modelId, const char *attributeName)
//{
//    return ((CCString *) getModelDic(modelId)->objectForKey(attributeName))->getCString();
//}