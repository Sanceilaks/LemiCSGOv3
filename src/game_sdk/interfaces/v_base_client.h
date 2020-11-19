#pragma once
#include <game_sdk/misc/c_client_class.h>

/*
666
*/

class VBaseClient
{
public:
	virtual void init() = 0;
	virtual void unknown1() = 0;
	virtual void unknown2() = 0;
	virtual void unknown3() = 0;
	virtual void unknown4() = 0;
	virtual void unknown5() = 0;
	virtual void unknown6() = 0;
	virtual void unknown7() = 0;
	virtual ClientClass* get_all_classes() = 0;
};
