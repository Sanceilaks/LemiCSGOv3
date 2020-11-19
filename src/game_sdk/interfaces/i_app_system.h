#pragma once

typedef void* (*CreateInterfaceFn)(const char* pName, int* pReturnCode);
typedef void* (*InstantiateInterfaceFn)();

class IAppSystem
{
	virtual bool                            connect(CreateInterfaceFn factory) = 0;                                     // 0
	virtual void                            disconnect() = 0;                                                           // 1
	virtual void* QueryInterface(const char* pInterfaceName) = 0;                             // 2
	virtual int /*InitReturnVal_t*/         init() = 0;                                                                 // 3
	virtual void                            shutdown() = 0;                                                             // 4
	virtual const void* /*AppSystemInfo_t*/ get_dependencies() = 0;                                                      // 5
	virtual int /*AppSystemTier_t*/         get_tier() = 0;                                                              // 6
	virtual void                            reconnect(CreateInterfaceFn factory, const char* pInterfaceName) = 0;       // 7
	virtual void                            unk_func() = 0;                                                              // 8
};