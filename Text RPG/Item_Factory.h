#pragma once
#ifndef ITEM_FACTORY_H_
#define ITEM_FACTORY_H_

#include "Equipment.h"

class ItemFactory
{
public:
    // TODO: 기본 검 아이템 생성 함수 시그니처
    static Equipment Create_Basic_Sword();

    // TODO: 기본 방패 아이템 생성 함수 시그니처
    static Equipment Create_Basic_Shield();

    // TODO: 고급 무기 아이템 생성 함수 시그니처
    static Equipment Create_Rare_Sword();

};

#endif