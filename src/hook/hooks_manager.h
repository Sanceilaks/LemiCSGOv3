#pragma once
#include <game_sdk/interfaces/i_client_mode.h>
#include <game_sdk/misc/c_user_cmd.h>
#include <d3d9.h>
#include <interfaces.h>

#include <game_sdk/misc/c_view_setup.h>

namespace hooks
{
	struct create_move_hook
	{
		static const unsigned int index = 24;

		using fn = bool(__thiscall*)(IClientMode*, float, CUserCmd*);
		static bool __stdcall hook(float frame_time, CUserCmd* ucmd);

		static inline fn original;
		static inline void* target;
	};

	struct end_scane_hook
	{
		static const unsigned int index = 42;

		using fn = long(__stdcall*)(IDirect3DDevice9*);
		static long __stdcall hook(IDirect3DDevice9* device);

		static inline fn original;
		static inline void* target;
	};

	struct reset_hook
	{
		static const unsigned int index = 16;

		using fn = long(__stdcall*)(IDirect3DDevice9*, D3DPRESENT_PARAMETERS*);
		static long __stdcall hook(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* present_parameters);

		static inline fn original;
		static inline void* target;
	};

	struct override_view_hook
	{
		static const unsigned int index = 18;

		using fn = void(__thiscall*)(IClientMode*, CViewSetup*);
		static void __stdcall hook(CViewSetup* view);

		static inline fn original;
		static inline void* target;
	};

	struct lock_cursor_hook
	{
		static const unsigned int index = 67;

		using fn = void(__thiscall*)(ISurface*);
		static void __stdcall hook();

		static inline fn original;
		static inline void* target;
	};

	struct draw_model_execute
	{
		static const unsigned int index = 21;

		using fn = void(__thiscall*)(IVModelRender*, IMatRenderContext*, const DrawModelState_t*, const ModelRenderInfo_t*, matrix3x4_t*);
		static void __stdcall hook(IMatRenderContext* context, const DrawModelState_t& state, const ModelRenderInfo_t& info, matrix3x4_t* bone);

		static inline fn original;
		static inline void* target;
	};
}



class HooksManager
{
public:
	void init();
	void shutdown();
	
}; extern HooksManager* hooks_manager;