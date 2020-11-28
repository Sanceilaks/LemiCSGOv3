#pragma once
#include <cstdint>

#include "i_app_system.h"

class IConsoleDisplayFunc
{
public:
    virtual void color_print(const uint8_t* clr, const char* pMessage) = 0;
    virtual void print(const char* pMessage) = 0;
    virtual void d_print(const char* pMessage) = 0;
};


class ConVar {
public:
    float get_float()
	{
        using fn = float(__thiscall*)(ConVar*);
        return (*(fn**)this)[12](this);
    }

    int get_int()
	{
        using fn = int(__thiscall*)(ConVar*);
        return (*(fn**)this)[13](this);
    }

    void set_value(int value)
	{
        using fn = void(__thiscall*)(ConVar*, int);
        return (*(fn**)this)[16](this, value);
    }

    void set_value(float value)
    {
        using fn = void(__thiscall*)(ConVar*, float);
        return (*(fn**)this)[15](this, value);
    }

	void set_value(const char* value)
    {
        using fn = void(__thiscall*)(ConVar*, const char*);
        return (*(fn**)this)[14](this, value);
    }
};

typedef void* CVarDLLIdentifier_t;
typedef void* ConCommandBase;
typedef void* ConCommand;
typedef void* FnChangeCallback_t;

class Color;

class ICvar : public IAppSystem
{
public:
    virtual CVarDLLIdentifier_t        allocate_dll_identifier() = 0; // 9
    virtual void                       register_con_command(ConCommandBase* pCommandBase) = 0; //10
    virtual void                       unregister_con_command(ConCommandBase* pCommandBase) = 0;
    virtual void                       unregister_con_commands(CVarDLLIdentifier_t id) = 0;
    virtual const char* get_command_line_value(const char* pVariableName) = 0;
    virtual ConCommandBase* find_command_base(const char* name) = 0;
    virtual const ConCommandBase* find_command_base(const char* name) const = 0;
    virtual ConVar* find(const char* var_name) = 0; //16
    virtual const ConVar* find(const char* var_name) const = 0;
    virtual ConCommand* find_command(const char* name) = 0;
    virtual const ConCommand* find_command(const char* name) const = 0;
    virtual void                       install_global_change_callback(FnChangeCallback_t callback) = 0;
    virtual void                       remove_global_change_callback(FnChangeCallback_t callback) = 0;
    virtual void                       call_callbacks(ConVar* var, const char* pOldString, float flOldValue) = 0;
    virtual void                       install_console_display_func(IConsoleDisplayFunc* pDisplayFunc) = 0;
    virtual void                       remove_console_display_func(IConsoleDisplayFunc* pDisplayFunc) = 0;
    virtual void                       console_color_printf(const Color& clr, const char* pFormat, ...) const = 0;
    virtual void                       console_printf(const char* pFormat, ...) const = 0;
    virtual void                       console_DPrintf(const char* pFormat, ...) const = 0;
    virtual void                       revert_flagged_con_vars(int nFlag) = 0;
};