#pragma once

class IMoveHelper
{
private:
	virtual void unk() = 0;
public:
	virtual void set_host(void* host) = 0;
};