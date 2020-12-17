#pragma once
#include "game_sdk/misc/c_user_cmd.h"
#include "i_move_helper.h"

class IPrediction {
private:
	virtual void unknown_virtual0() = 0;
	virtual void unknown_virtual1() = 0;
	virtual void unknown_virtual2() = 0;
	virtual void unknown_virtual3() = 0;
	virtual void unknown_virtual4() = 0;
	virtual void unknown_virtual5() = 0;
	virtual void unknown_virtual6() = 0;
	virtual void unknown_virtual7() = 0;
	virtual void unknown_virtual8() = 0;
	virtual void unknown_virtual9() = 0;
	virtual void unknown_virtual10() = 0;
	virtual void unknown_virtual11() = 0;
	virtual void unknown_virtual12() = 0;
	virtual void unknown_virtual13() = 0;
	virtual void unknown_virtual14() = 0;
	virtual void unknown_virtual15() = 0;
	virtual void unknown_virtual16() = 0;
	virtual void unknown_virtual17() = 0;
	virtual void unknown_virtual18() = 0;
	virtual void unknown_virtual19() = 0;
public:
	virtual void setup_move(void* player, CUserCmd* ucmd, IMoveHelper* pHelper, CMoveData* move) = 0; //20
	virtual void finish_move(void* player, CUserCmd* ucmd, CMoveData* move) = 0;
};