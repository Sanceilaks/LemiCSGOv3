#pragma once
#include "material_system_staff.h"
#include <math/qangle.h>
#include <math/vector4d.h>
#include <game_sdk/misc/i_material.h>

struct Rect_t;

class IMatRenderContext
{
public:
	/*0*/   virtual void	begin_render() = 0;
	/*1*/	virtual void	end_render() = 0;
	/*2*/	virtual void	flush(bool flushHardware = false) = 0;
	/*3*/	virtual void	bind_local_cubemap(ITexture* pTexture) = 0;
	/*4*/	virtual void	set_render_target(ITexture* pTexture) = 0;
	/*5*/	virtual ITexture* get_render_target(void) = 0;
	/*6*/	virtual void	get_render_target_dimensions(int& width, int& height) const = 0;
	/*7*/	virtual void	bind(IMaterial* material, void* proxyData = 0) = 0;
	/*8*/	virtual void	bind_lightmap_page(int lightmapPageID) = 0;
	/*9*/	virtual void	depth_range(float zNear, float zFar) = 0;
	/*10*/	virtual void	clear_buffers(bool bClearColor, bool bClearDepth, bool bClearStencil = false) = 0;
	/*11*/	virtual void	read_pixels(int x, int y, int width, int height, unsigned char* data, ImageFormat dstFormat) = 0;
	/*12*/	virtual void	set_ambient_light(float r, float g, float b) = 0;
	/*13*/	virtual void	set_light(int lightNum, const LightDesc_t& desc) = 0;
	/*14*/	virtual void	set_ambient_light_cube(Vector4D cube[6]) = 0;
	/*15*/	virtual void	copy_render_target_to_texture(ITexture* pTexture) = 0;
	/*16*/	virtual void	set_frame_buffer_copy_texture(ITexture* pTexture, int textureIndex = 0) = 0;
	/*17*/	virtual ITexture* get_frame_buffer_copy_texture(int textureIndex) = 0;
	/*18*/	virtual void	matrix_mode(MaterialMatrixMode_t matrixMode) = 0;
	/*19*/	virtual void	push_matrix(void) = 0;
	/*20*/	virtual void	pop_matrix(void) = 0;
	/*21*/	virtual void	load_matrix(VMatrix const& matrix) = 0;
	/*22*/	virtual void	load_matrix(matrix3x4_t const& matrix) = 0;
	/*23*/	virtual void	mult_matrix(VMatrix const& matrix) = 0;
	/*24*/	virtual void	mult_matrix(matrix3x4_t const& matrix) = 0;
	/*25*/	virtual void	mult_matrix_local(VMatrix const& matrix) = 0;
	/*26*/	virtual void	MultMatrixLocal(matrix3x4_t const& matrix) = 0;
	/*27*/	virtual void	get_matrix(MaterialMatrixMode_t matrixMode, VMatrix* matrix) = 0;
	/*28*/	virtual void	get_matrix(MaterialMatrixMode_t matrixMode, matrix3x4_t* matrix) = 0;
	/*29*/	virtual void	load_identity(void) = 0;
	/*30*/	virtual void	ortho(double left, double top, double right, double bottom, double zNear, double zFar) = 0;
	/*31*/	virtual void	perspective_x(double fovx, double aspect, double zNear, double zFar) = 0;
	/*32*/	virtual void	pick_matrix(int x, int y, int width, int height) = 0;
	/*33*/	virtual void	rotate(float angle, float x, float y, float z) = 0;
	/*34*/	virtual void	translate(float x, float y, float z) = 0;
	/*35*/	virtual void	scale(float x, float y, float z) = 0;
	/*36*/	virtual void	viewport(int x, int y, int width, int height) = 0;
	/*37*/	virtual void	get_viewport(int& x, int& y, int& width, int& height) const = 0;
	/*38*/	virtual void	cull_mode(MaterialCullMode_t cullMode) = 0;
	/*39*/	virtual void	set_height_clip_mode(MaterialHeightClipMode_t nHeightClipMode) = 0;
	/*40*/	virtual void	set_height_clip_z(float z) = 0;
	/*41*/	virtual void	fog_mode(MaterialFogMode_t fogMode) = 0;
	/*42*/	virtual void	fog_start(float fStart) = 0;
	/*43*/	virtual void	fog_end(float fEnd) = 0;
	/*44*/	virtual void	set_fog_z(float fogZ) = 0;
	/*45*/	virtual MaterialFogMode_t	get_fog_mode(void) = 0;
	/*46*/	virtual void	fog_color3_f(float r, float g, float b) = 0;
	/*47*/	virtual void	fog_color3_fv(float const* rgb) = 0;
	/*48*/	virtual void	fog_color3_ub(unsigned char r, unsigned char g, unsigned char b) = 0;
	/*49*/	virtual void	fog_color3_ubv(unsigned char const* rgb) = 0;
	/*50*/	virtual void	get_fog_color(unsigned char* rgb) = 0;
	/*51*/	virtual void	set_num_bone_weights(int numBones) = 0;
	/*52*/	virtual IMesh* create_static_mesh(VertexFormat_t fmt, const char* pTextureBudgetGroup, IMaterial* pMaterial = NULL) = 0;
	/*53*/	virtual void	destroy_static_mesh(IMesh* mesh) = 0;
	/*54*/	virtual IMesh* get_dynamic_mesh(bool buffered = true, IMesh* pVertexOverride = 0, IMesh* pIndexOverride = 0, IMaterial* pAutoBind = 0) = 0;
	/*55*/	virtual IVertexBuffer* create_static_vertex_buffer(VertexFormat_t fmt, int nVertexCount, const char* pTextureBudgetGroup) = 0;
	/*56*/	virtual IIndexBuffer* create_static_index_buffer(MaterialIndexFormat_t fmt, int nIndexCount, const char* pTextureBudgetGroup) = 0;
	/*57*/	virtual void	destroy_vertex_buffer(IVertexBuffer*) = 0;
	/*58*/	virtual void	destroy_index_buffer(IIndexBuffer*) = 0;
	/*59*/	virtual IVertexBuffer* get_dynamic_vertex_buffer(int streamID, VertexFormat_t vertexFormat, bool bBuffered = true) = 0;
	/*60*/	virtual IIndexBuffer* get_dynamic_index_buffer(MaterialIndexFormat_t fmt, bool bBuffered = true) = 0;
	/*61*/	virtual void	bind_vertex_buffer(int streamID, IVertexBuffer* pVertexBuffer, int nOffsetInBytes, int nFirstVertex, int nVertexCount, VertexFormat_t fmt, int nRepetitions = 1) = 0;
	/*62*/	virtual void	bind_index_buffer(IIndexBuffer* pIndexBuffer, int nOffsetInBytes) = 0;
	/*63*/	virtual void	draw(MaterialPrimitiveType_t primitiveType, int firstIndex, int numIndices) = 0;
	/*64*/	virtual int		selection_mode(bool selectionMode) = 0;
	/*65*/	virtual void	selection_buffer(unsigned int* pBuffer, int size) = 0;
	/*66*/	virtual void	clear_selection_names() = 0;
	/*67*/	virtual void	load_selection_name(int name) = 0;
	/*68*/	virtual void	push_selection_name(int name) = 0;
	/*69*/	virtual void	pop_selection_name() = 0;
	/*70*/	virtual void	clear_color3_ub(unsigned char r, unsigned char g, unsigned char b) = 0;
	/*71*/	virtual void	clear_color4_ub(unsigned char r, unsigned char g, unsigned char b, unsigned char a) = 0;
	/*72*/	virtual void	override_depth_enable(bool bEnable, bool bDepthEnable) = 0;
	/*73*/	virtual void	draw_screen_space_quad(IMaterial* pMaterial) = 0;
	/*74*/	virtual void	sync_token(const char* pToken) = 0;
	/*75*/	virtual float	compute_pixel_width_of_sphere(const Vector& origin, float flRadius) = 0;
	/*76*/	virtual OcclusionQueryObjectHandle_t create_occlusion_query_object(void) = 0;
	/*77*/	virtual void	destroy_occlusion_query_object(OcclusionQueryObjectHandle_t) = 0;
	/*78*/	virtual void	begin_occlusion_query_drawing(OcclusionQueryObjectHandle_t) = 0;
	/*79*/	virtual void	end_occlusion_query_drawing(OcclusionQueryObjectHandle_t) = 0;
	/*80*/	virtual int		occlusion_query_get_num_pixels_rendered(OcclusionQueryObjectHandle_t) = 0;
	/*81*/	virtual void	set_flashlight_mode(bool bEnable) = 0;
	/*82*/	virtual void	set_flashlight_state(const FlashlightState_t& state, const VMatrix& worldToTexture) = 0;
	/*83*/	virtual MaterialHeightClipMode_t get_height_clip_mode() = 0;
	/*84*/	virtual float	compute_pixel_diameter_of_sphere(const Vector& vecAbsOrigin, float flRadius) = 0;
	/*85*/	virtual void	enable_user_clip_transform_override(bool bEnable) = 0;
	/*86*/	virtual void	user_clip_transform(const VMatrix& worldToView) = 0;
	/*87*/	virtual bool	get_flashlight_mode() const = 0;
	/*88*/	virtual void	reset_occlusion_query_object(OcclusionQueryObjectHandle_t) = 0;
	/*89*/	virtual void	unused3() = 0;
	/*90*/	virtual IMorph* create_morph(MorphFormat_t format, const char* pDebugName) = 0;
	/*91*/	virtual void	destroy_morph(IMorph* pMorph) = 0;
	/*92*/	virtual void	bind_morph(IMorph* pMorph) = 0;
	/*93*/	virtual void	set_flex_weights(int nFirstWeight, int nCount, const MorphWeight_t* pWeights) = 0;
	/*94*/	virtual void	unused4() = 0;
	/*95*/	virtual void	unused5() = 0;
	/*96*/	virtual void	unused6() = 0;
	/*97*/	virtual void	unused7() = 0;
	/*98*/	virtual void	unused8() = 0;
	/*99*/	virtual void	read_pixels_and_stretch(Rect_t* pSrcRect, Rect_t* pDstRect, unsigned char* pBuffer, ImageFormat dstFormat, int nDstStride) = 0;
	/*100*/	virtual void	get_window_size(int& width, int& height) const = 0;
	/*101*/	virtual void	draw_screen_space_rectangle(IMaterial* pMaterial, int destx, int desty, int width, int height, float src_texture_x0, float src_texture_y0, float src_texture_x1, float src_texture_y1, int src_texture_width, int src_texture_height, int nXDice = 1, int nYDice = 1) = 0;
	/*102*/	virtual void	load_bone_matrix(int boneIndex, const matrix3x4_t& matrix) = 0;
	/*103*/	virtual void	push_render_target_and_viewport() = 0;
	/*104*/	virtual void	push_render_target_and_viewport(ITexture* pTexture) = 0;
	/*105*/	virtual void	push_render_target_and_viewport(ITexture* pTexture, int nViewX, int nViewY, int nViewW, int nViewH) = 0;
	/*106*/	virtual void	push_render_target_and_viewport(ITexture* pTexture, ITexture* pDepthTexture, int nViewX, int nViewY, int nViewW, int nViewH) = 0;
	/*107*/	virtual void	pop_render_target_and_viewport(void) = 0;
	/*108*/	virtual void	bind_lightmap_texture(ITexture* pLightmapTexture) = 0;
	/*109*/	virtual void	copy_render_target_to_texture_ex(ITexture* pTexture, int nRenderTargetID, Rect_t* pSrcRect, Rect_t* pDstRect = NULL) = 0;
	/*110*/	virtual void	copy_texture_to_render_target_ex(int nRenderTargetID, ITexture* pTexture, Rect_t* pSrcRect, Rect_t* pDstRect = NULL) = 0;
	/*111*/	virtual void	perspective_off_center_x(double fovx, double aspect, double zNear, double zFar, double bottom, double top, double left, double right) = 0;
	/*112*/	virtual void	set_float_rendering_parameter(int parm_number, float value) = 0;
	/*113*/	virtual void	set_int_rendering_parameter(int parm_number, int value) = 0;
	/*114*/	virtual void	set_vector_rendering_parameter(int parm_number, Vector const& value) = 0;
	/*115*/	virtual void	set_stencil_enable(bool onoff) = 0;
	/*116*/	virtual void	set_stencil_fail_operation(StencilOperation_t op) = 0;
	/*117*/	virtual void	set_stencil_z_fail_operation(StencilOperation_t op) = 0;
	/*118*/	virtual void	set_stencil_pass_operation(StencilOperation_t op) = 0;
	/*119*/	virtual void	set_stencil_compare_function(StencilComparisonFunction_t cmpfn) = 0;
	/*120*/	virtual void	set_stencil_reference_value(int ref) = 0;
	/*121*/	virtual void	set_stencil_test_mask(UINT32 msk) = 0;
	/*122*/	virtual void	set_stencil_write_mask(UINT32 msk) = 0;
	/*123*/	virtual void	clear_stencil_buffer_rectangle(int xmin, int ymin, int xmax, int ymax, int value) = 0;
	/*124*/	virtual void	set_render_target_ex(int nRenderTargetID, ITexture* pTexture) = 0;
	/*125*/	virtual void	push_custom_clip_plane(const float* pPlane) = 0;
	/*126*/	virtual void	pop_custom_clip_plane(void) = 0;
	/*127*/	virtual void	get_max_to_render(IMesh* pMesh, bool bMaxUntilFlush, int* pMaxVerts, int* pMaxIndices) = 0;
	/*128*/	virtual int		get_max_vertices_to_render(IMaterial* pMaterial) = 0;
	/*129*/	virtual int		get_max_indices_to_render() = 0;
	/*130*/	virtual void	disable_all_local_lights() = 0;
	/*131*/	virtual int		compare_material_combos(IMaterial* pMaterial1, IMaterial* pMaterial2, int lightMapID1, int lightMapID2) = 0;
	/*132*/	virtual IMesh* get_flex_mesh() = 0;
	/*133*/	virtual void	set_flashlight_state_ex(const FlashlightState_t& state, const VMatrix& worldToTexture, ITexture* pFlashlightDepthTexture) = 0;
	/*134*/	virtual ITexture* get_local_cubemap() = 0;
	/*135*/	virtual void	clear_buffers_obey_stencil(bool bClearColor, bool bClearDepth) = 0;
	/*136*/	virtual bool	enable_clipping(bool bEnable) = 0;
	/*137*/	virtual void	get_fog_distances(float* fStart, float* fEnd, float* fFogZ) = 0;
	/*138*/	virtual void	begin_pix_event(unsigned long color, const char* szName) = 0;
	/*139*/	virtual void	end_pix_event() = 0;
	/*140*/	virtual void	set_pix_marker(unsigned long color, const char* szName) = 0;
	/*141*/	virtual void	begin_batch(IMesh* pIndices) = 0;
	/*142*/	virtual void	bind_batch(IMesh* pVertices, IMaterial* pAutoBind = NULL) = 0;
	/*143*/	virtual void	draw_batch(int firstIndex, int numIndices) = 0;
	/*144*/	virtual void	end_batch() = 0;
	/*145*/	virtual ICallQueue* get_call_queue() = 0;
	/*146*/	virtual void	get_world_space_camera_position(Vector* pCameraPos) = 0;
	/*147*/	virtual void	get_world_space_camera_vectors(Vector* pVecForward, Vector* pVecRight, Vector* pVecUp) = 0;
	/*148*/	virtual void	reset_tone_mapping_scale(float monoscale) = 0; 			// set scale to monoscale instantly with no chasing
	/*149*/	virtual void	set_goal_tone_mapping_scale(float monoscale) = 0;
	/*150*/	virtual void	turn_on_tone_mapping() = 0;
	/*151*/	virtual void	set_tone_mapping_scale_linear(const Vector& scale) = 0;
	/*152*/	virtual Vector	get_tone_mapping_scale_linear(void) = 0;
	/*153*/	virtual void	set_shadow_depth_bias_factors(float fSlopeScaleDepthBias, float fDepthBias) = 0;
	/*154*/	virtual void	perform_full_screen_stencil_operation(void) = 0;
	/*155*/	virtual void	set_lighting_origin(Vector vLightingOrigin) = 0;
	/*156*/	virtual void	set_scissor_rect(const int nLeft, const int nTop, const int nRight, const int nBottom, const bool bEnableScissor) = 0;
	/*157*/	virtual void	begin_morph_accumulation() = 0;
	/*158*/	virtual void	end_morph_accumulation() = 0;
	/*159*/	virtual void	accumulate_morph(IMorph* pMorph, int nMorphCount, const MorphWeight_t* pWeights) = 0;
	/*160*/	virtual void	push_deformation(DeformationBase_t const* Deformation) = 0;
	/*161*/	virtual void	pop_deformation() = 0;
	/*162*/	virtual int		get_num_active_deformations() const = 0;
	/*163*/	virtual bool	get_morph_accumulator_tex_coord(Vector2D* pTexCoord, IMorph* pMorph, int nVertex) = 0;
	/*164*/	virtual IMesh* get_dynamic_mesh_ex(VertexFormat_t vertexFormat, bool bBuffered = true, IMesh* pVertexOverride = 0, IMesh* pIndexOverride = 0, IMaterial* pAutoBind = 0) = 0;
	/*165*/	virtual void	fog_max_density(float flMaxDensity) = 0;
	/*166*/	virtual IMaterial* get_current_material() = 0;
	/*167*/	virtual int		get_current_num_bones() const = 0;
	/*168*/	virtual void* get_current_proxy() = 0;
	/*169*/	virtual void	enable_color_correction(bool bEnable) = 0;
	/*170*/	virtual ColorCorrectionHandle_t add_lookup(const char* pName) = 0;
	/*171*/	virtual bool	remove_lookup(ColorCorrectionHandle_t handle) = 0;
	/*172*/	virtual void	lock_lookup(ColorCorrectionHandle_t handle) = 0;
	/*173*/	virtual void	load_lookup(ColorCorrectionHandle_t handle, const char* pLookupName) = 0;
	/*174*/	virtual void	unlock_lookup(ColorCorrectionHandle_t handle) = 0;
	/*175*/	virtual void	set_lookup_weight(ColorCorrectionHandle_t handle, float flWeight) = 0;
	/*176*/	virtual void	reset_lookup_weights() = 0;
	/*177*/	virtual void	set_resetable(ColorCorrectionHandle_t handle, bool bResetable) = 0;
	/*178*/	virtual void	set_full_screen_depth_texture_validity_flag(bool bIsValid) = 0;
	/*179*/	virtual void	set_non_interactive_pacifier_texture(ITexture* pTexture, float flNormalizedX, float flNormalizedY, float flNormalizedSize) = 0;
	/*180*/	virtual void	set_non_interactive_temp_fullscreen_buffer(ITexture* pTexture, MaterialNonInteractiveMode_t mode) = 0;
	/*181*/	virtual void	enable_non_interactive_mode(MaterialNonInteractiveMode_t mode) = 0;
	/*182*/	virtual void	refresh_front_buffer_non_interactive() = 0;
	/*183*/	virtual void* lock_render_data(int nSizeInBytes) = 0;
	/*184*/	virtual void	unlock_render_data(void* pData) = 0;
	/*185*/	virtual void	add_ref_render_data() = 0;
	/*186*/	virtual void	release_render_data() = 0;
	/*187*/	virtual bool	is_render_data(const void* pData) const = 0;
	/*188*/	virtual void	printf_va(char* fmt, va_list vargs) = 0;
	/*189*/	virtual void	printf(const char* fmt, ...) = 0;
	/*190*/	virtual float	knob(char* knobname, float* setvalue = NULL) = 0;
	/*191*/	virtual void	override_alpha_write_enable(bool bEnable, bool bAlphaWriteEnable) = 0;
	/*192*/	virtual void	override_color_write_enable(bool bOverrideEnable, bool bColorWriteEnable) = 0;
	/*193*/	virtual void	clear_buffers_obey_stencil_ex(bool bClearColor, bool bClearAlpha, bool bClearDepth) = 0;
	// there's more shit below this but I'm lazy lol.
};