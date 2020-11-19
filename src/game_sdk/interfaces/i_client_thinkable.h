#pragma once

class IClientUnknown;
class CClientThinkHandlePtr;
typedef CClientThinkHandlePtr* ClientThinkHandle_t;

class IClientThinkable
{
public:
	virtual IClientUnknown* get_i_client_unknown() = 0;
	virtual void                client_think() = 0;
	virtual ClientThinkHandle_t get_think_handle() = 0;
	virtual void                set_think_handle(ClientThinkHandle_t hThink) = 0;
	virtual void                release() = 0;
};