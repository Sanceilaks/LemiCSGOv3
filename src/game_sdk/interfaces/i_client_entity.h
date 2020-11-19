#pragma once
#include "i_client_unknown.h"
#include "i_client_renderable.h"
#include "i_client_networkable.h"
#include "i_client_thinkable.h"

class IClientEntity : public IClientUnknown, public IClientRenderable, public IClientNetworkable, public IClientThinkable
{
public:
	virtual void release(void) = 0;
};