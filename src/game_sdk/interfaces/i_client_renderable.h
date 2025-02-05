#pragma once

#include "game_sdk/misc/studio.h"
#include "math/qangle.h"
#include "math/vector3d.h"

#include "math/vmatrix.h"

typedef unsigned short ClientShadowHandle_t;
typedef unsigned short ClientRenderHandle_t;
typedef unsigned short ModelInstanceHandle_t;
typedef unsigned char uint8_t;

class IClientUnknown;


class IClientRenderable
{
public:
	virtual IClientUnknown* get_i_client_unknown() = 0;
	virtual Vector const& get_render_origin(void) = 0;
	virtual QAngle const& get_render_angles(void) = 0;
	virtual bool                       should_draw(void) = 0;
	virtual int                        get_render_flags(void) = 0; // ERENDERFLAGS_xxx
	virtual void                       unused(void) const {}
	virtual ClientShadowHandle_t       get_shadow_handle() const = 0;
	virtual ClientRenderHandle_t& render_handle() = 0;
	virtual const model_t* get_model() const = 0;
	virtual int                        draw_model(int flags, const int /*RenderableInstance_t*/& instance) = 0;
	virtual int                        get_body() = 0;
	virtual void                       get_color_modulation(float* color) = 0;
	virtual bool                       lod_test() = 0;
	virtual bool					   setup_bones(matrix3x4_t* pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime) = 0;
	virtual void                       setup_weights(const matrix3x4_t* pBoneToWorld, int nFlexWeightCount, float* pFlexWeights, float* pFlexDelayedWeights) = 0;
	virtual void                       do_animation_events(void) = 0;
	virtual void* /*IPVSNotify*/       get_pvs_notify_interface() = 0;
	virtual void                       get_render_bounds(Vector& mins, Vector& maxs) = 0;
	virtual void                       get_render_bounds_worldspace(Vector& mins, Vector& maxs) = 0;
	virtual void                       get_shadow_render_bounds(Vector& mins, Vector& maxs, int /*ShadowType_t*/ shadowType) = 0;
	virtual bool                       should_receive_projected_textures(int flags) = 0;
	virtual bool                       get_shadow_cast_distance(float* pDist, int /*ShadowType_t*/ shadowType) const = 0;
	virtual bool                       get_shadow_cast_direction(Vector* pDirection, int /*ShadowType_t*/ shadowType) const = 0;
	virtual bool                       is_shadow_dirty() = 0;
	virtual void                       mark_shadow_dirty(bool bDirty) = 0;
	virtual IClientRenderable* get_shadow_parent() = 0;
	virtual IClientRenderable* first_shadow_child() = 0;
	virtual IClientRenderable* next_shadow_peer() = 0;
	virtual int /*ShadowType_t*/       shadow_cast_type() = 0;
	virtual void                       create_model_instance() = 0;
	virtual ModelInstanceHandle_t      get_model_instance() = 0;
	virtual const matrix3x4_t& renderable_to_world_transform() = 0;
	virtual int                        lookup_attachment(const char* pAttachmentName) = 0;
	virtual   bool                     get_attachment(int number, Vector& origin, QAngle& angles) = 0;
	virtual bool                       get_attachment(int number, matrix3x4_t& matrix) = 0;
	virtual float* get_render_clip_plane(void) = 0;
	virtual int                        get_skin() = 0;
	virtual void                       on_threaded_draw_setup() = 0;
	virtual bool                       uses_flex_delayed_weights() = 0;
	virtual void                       record_tool_message() = 0;
	virtual bool                       should_draw_for_split_screen_user(int nSlot) = 0;
	virtual uint8_t                    override_alpha_modulation(uint8_t nAlpha) = 0;
	virtual uint8_t                    override_shadow_alpha_modulation(uint8_t nAlpha) = 0;
};