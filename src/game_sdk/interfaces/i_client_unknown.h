#pragma once

#include <game_sdk/misc/i_handle_entity.h>

#include "math/vector3d.h"

//class ICollideable;
class IClientNetworkable;
class IClientRenderable;
class IClientEntity;
class c_base_entity;
class IClientThinkable;
class IClientAlphaProperty;

enum SolidType_t;

class ICollideable
{
public:
	virtual IHandleEntity* get_entity_handle() = 0;
	virtual const Vector& obb_mins() const = 0;
	virtual const Vector& obb_maxs() const = 0;
};


class IClientUnknown : public IHandleEntity
{
public:
	virtual ICollideable* get_collideable() = 0;
	virtual IClientNetworkable* get_client_networkable() = 0;
	virtual IClientRenderable* get_client_renderable() = 0;
	virtual IClientEntity* get_i_client_entity() = 0;
	virtual c_base_entity* get_base_entity() = 0;
	virtual IClientThinkable* get_client_thinkable() = 0;
	//virtual IClientModelRenderable*  GetClientModelRenderable() = 0;
	virtual IClientAlphaProperty* get_client_alpha_property() = 0;
};