#pragma once
#include <cstdint>
#include <game_sdk/misc/i_handle_entity.h>

class IClientNetworkable;
class IClientEntity;

class VClientEntityList
{
public:
	virtual void init() = 0;
	virtual void unused_1() = 0;
	virtual void unused_2() = 0;
	virtual void* get_entity_by_index(int index) = 0;
	virtual void* get_entity_by_handle(CBaseHandle handle) = 0;
	virtual void unused_5() = 0;
	virtual int get_highest_enetity_index() = 0;
	virtual void unused_7() = 0;
	virtual void unused_8() = 0;
};