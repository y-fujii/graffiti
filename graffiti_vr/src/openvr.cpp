#if defined(__MINGW32__)
	#include <openvr/openvr_mingw.hpp>
#else
	#include <openvr/openvr.h>
#endif


extern "C" vr::IVRSystem* vr_init() {
	vr::HmdError err;
	return vr::VR_Init(&err, vr::VRApplication_Overlay);
}

extern "C" vr::IVRSystem* vr_system() {
	return vr::VRSystem();
}

extern "C" vr::IVROverlay* vr_overlay() {
	return vr::VROverlay();
}

extern "C" void vr_get_device_to_absolute_tracking_pose(vr::IVRSystem* self, vr::TrackedDevicePose_t* poses, uint32_t n) {
	self->GetDeviceToAbsoluteTrackingPose(vr::TrackingUniverseStanding, 0.0, poses, n);
}

extern "C" void vr_get_controller_state_with_pose(vr::IVRSystem* self, uint32_t index, vr::VRControllerState_t* state, vr::TrackedDevicePose_t* pose) {
	self->GetControllerStateWithPose(vr::TrackingUniverseStanding, index, state, sizeof(vr::VRControllerState_t), pose);
}

extern "C" void vr_shutdown(vr::IVRSystem*) {
	vr::VR_Shutdown();
}

extern "C" uintptr_t vr_overlay_create(vr::IVROverlay* self, char const* key, char const* name) {
	uintptr_t handle = 0;
	self->CreateOverlay(key, name, &handle);
	return handle;
}

extern "C" bool vr_overlay_set_width_in_meters(vr::IVROverlay* self, uintptr_t handle, float width) {
	return self->SetOverlayWidthInMeters(handle, width) == 0;
}

extern "C" bool vr_overlay_set_transform_tracked_device_relative(vr::IVROverlay* self, uintptr_t handle, uint32_t device, vr::HmdMatrix34_t const* transform) {
	return self->SetOverlayTransformTrackedDeviceRelative(handle, device, transform) == 0;
}

extern "C" bool vr_overlay_set_texture(vr::IVROverlay* self, uintptr_t handle, uintptr_t tex_handle) {
	vr::Texture_t texture {
		reinterpret_cast<void*>(tex_handle),
		vr::TextureType_OpenGL,
		vr::ColorSpace_Linear,
	};
	return self->SetOverlayTexture(handle, &texture) == 0;
}

extern "C" bool vr_overlay_show(vr::IVROverlay* self, uintptr_t handle) {
	return self->ShowOverlay(handle) == 0;
}

extern "C" bool vr_overlay_destroy(vr::IVROverlay* self, uintptr_t handle) {
	return self->DestroyOverlay(handle) == 0;
}
