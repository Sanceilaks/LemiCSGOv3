#pragma once

class IClientUnknown;
class ClientClass;
class bf_read;

class IClientNetworkable
{
public:
	virtual IClientUnknown* get_i_client_unknown() = 0;
	virtual void					release() = 0;
	/* 2 */ virtual ClientClass* get_client_class() = 0;
	virtual void					notify_should_transmit(int state) = 0;
	virtual void					on_pre_data_changed(int updateType) = 0;
	virtual void					on_data_changed(int updateType) = 0;
	virtual void					pre_data_update(int updateType) = 0;
	virtual void					post_data_update(int updateType) = 0;
	virtual void					__unkn(void) = 0;
	/* 9 */ virtual bool			is_dormant(void) = 0;
	/* 10 */ virtual int			index(void) const = 0;
	virtual void					receive_message(int classID, bf_read& msg) = 0;
	virtual void* GetDataTableBasePtr() = 0;
	/* 13 */ virtual void			set_destroyed_on_recreate_entities(void) = 0;
};