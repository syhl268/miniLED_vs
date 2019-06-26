#ifndef  _SINGLE_CAMERA_CONTROL_H_
#define _SINGLE_CAMERA_CONTROL_H_


#define byte unsigned char
#define CAMERAAPI extern "C"  __declspec(dllexport)

typedef void (*CameraCallback)(byte* imgData, int width, int height);

enum Camera_State {
	SUCCESS,
	INITIAL_COMPLETE,
	ERROR_INV,
	ERROR_OPENFAIL,
	ERROR_NULLDATA,
	ERROR_RETURN,
	ERROR_OPEN_CAMERA_FAILED,
	ERROR_CLOSE_CAMERA_FAILED,
	ERROR_SET_FAILED,
	ERROR_GET_FAILED
};

	CAMERAAPI bool Open();
	CAMERAAPI void SetCallback(CameraCallback camImgProcess);
	CAMERAAPI bool Grabbing();
	CAMERAAPI bool Abort();
	CAMERAAPI bool setExposureTime(int microSeconds);
	CAMERAAPI int getExposureTime();
	CAMERAAPI bool Close();

#endif // ! _SINGLE_CAMERA_CONTROL_H_