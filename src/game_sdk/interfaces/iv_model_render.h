#pragma once
#include "i_client_renderable.h"
#include "i_material_system.h"
#include <game_sdk/misc/i_material.h>

//struct model_t;
class IClientRenderable;
struct studiohdr_t;
struct studiohwdata_t;

struct ModelRenderInfo_t
{
	Vector                  origin;
	QAngle                  angles;
	char                    pad[0x4];
	IClientRenderable* pRenderable;
	const model_t* pModel;
	const matrix3x4_t* pModelToWorld;
	const matrix3x4_t* pLightingOffset;
	const Vector* pLightingOrigin;
	int                     flags;
	int                     entity_index;
	int                     skin;
	int                     body;
	int                     hitboxset;
	ModelInstanceHandle_t   instance;

	ModelRenderInfo_t()
	{
		pModelToWorld = NULL;
		pLightingOffset = NULL;
		pLightingOrigin = NULL;
	}
};

typedef void* StudioDecalHandle_t;
typedef int OverrideType_t;
struct ColorMeshInfo_t;

struct DrawModelState_t
{
	studiohdr_t* m_pStudioHdr;
	studiohwdata_t* m_pStudioHWData;
	IClientRenderable* m_pRenderable;
	const matrix3x4_t* m_pModelToWorld;
	StudioDecalHandle_t     m_decals;
	int                     m_drawFlags;
	int                     m_lod;
};

class IVModelRender
{
public:
	virtual int draw_model(int flags, IClientRenderable* pRenderable, ModelInstanceHandle_t instance, int entity_index, const model_t* model, Vector const& origin, QAngle const& angles, int skin, int body, int hitboxset, const matrix3x4_t* modelToWorld = NULL, const matrix3x4_t* pLightingOffset = NULL) = 0;
	virtual void forced_material_override(IMaterial* newMaterial, int nOverrideType = 0, int nOverrides = 0) = 0;
	virtual bool is_forced_material_override(void) = 0;
};