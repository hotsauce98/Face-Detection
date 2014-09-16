///////////////////////////////////////////////////
//
//         Luxand FaceCrop Library 
//
//  Copyright(c) 2005-2010 Luxand, Inc.
//         http://www.luxand.com
//
///////////////////////////////////////////////////

#ifndef _LUXANDFACECROP_
#define _LUXANDFACECROP_

#define fcErrorOk				0
#define fcErrorFailed			-1
#define fcErrorNotActivated		-2
#define fcErrorOutOfMemory		-3
#define fcErrorInvalidArgument  -4
#define fcErrorIOError			-5
#define fcErrorImageTooSmall  -6
#define fcErrorFaceNotFound  -7
#define fcErrorInsufficientBufferSize  -8
#define fcUnsupportedImageExtension       -9
#define fcCannotOpenFile -10
#define fcCannotCreateFile -11
#define fcBadFileFormat -12
#define fcFileNotFound -13

typedef enum {
	fcPerformanceRealtime = 0,
	fcPerformanceNormal,
	fcPerformancePrecise
} FcDetectionPerformance; 


#if defined( _WIN32 ) || defined ( _WIN64 )
#define _FCIMPORT_ __declspec(dllimport) __cdecl

#include <windows.h>
#ifdef __cplusplus
extern "C" {
#endif

#else
#define _FCIMPORT_
#endif


int _FCIMPORT_ fcInitialize();
int _FCIMPORT_ fcActivate(char * licenseKey);
int _FCIMPORT_ fcFinalize();
int _FCIMPORT_ fcGetLicenseInfo(char * licenseInfo);
int _FCIMPORT_ fcGetHardwareID(char * hardwareID);


int _FCIMPORT_ fcCreateContextID(int * contextID);
int _FCIMPORT_ fcFreeContextID(int contextID);

int _FCIMPORT_ fcFaceCrop(char * inFileName, char * outFileName, int width, int height);
int _FCIMPORT_ fcFaceCrop_C(char * inFileName, char * outFileName, int width, int height, int contextID);
#if defined( _WIN32 ) || defined ( _WIN64 )
int _FCIMPORT_ fcFaceCrop_FileToHBITMAP(char * inFileName, HBITMAP * outHBITMAP, int width, int height);
int _FCIMPORT_ fcFaceCrop_FileToHBITMAP_C(char * inFileName, HBITMAP * outHBITMAP, int width, int height, int contextID);
int _FCIMPORT_ fcFaceCrop_HBITMAPToHBITMAP(HBITMAP * inHBITMAP, HBITMAP * outHBITMAP, int width, int height);
int _FCIMPORT_ fcFaceCrop_HBITMAPToHBITMAP_C(HBITMAP * inHBITMAP, HBITMAP * outHBITMAP, int width, int height, int contextID);
#endif

int _FCIMPORT_ fcGetFacePosition(char * inFileName, int width, int height, int * x1, int * y1, int * x2, int * y2); // возвращает прямоугольник с лицом
int _FCIMPORT_ fcGetFacePosition_C(char * inFileName, int width, int height, int * x1, int * y1, int * x2, int * y2, int contextID); // возвращает прямоугольник с лицом
#if defined( _WIN32 ) || defined ( _WIN64 )
int _FCIMPORT_ fcGetFacePosition_HBITMAP(HBITMAP * inHBITMAP, int width, int height, int * x1, int * y1, int * x2, int * y2); 
int _FCIMPORT_ fcGetFacePosition_HBITMAP_C(HBITMAP * inHBITMAP, int width, int height, int * x1, int * y1, int * x2, int * y2, int contextID); 
#endif

int _FCIMPORT_ fcSetFaceScale(float scale); // задает, насколько масштабировать лицо при вырезании. По умолчанию scale = 1
int _FCIMPORT_ fcSetFaceScale_C(float scale, int contextID); // задает, насколько масштабировать лицо при вырезании. По умолчанию scale = 1
int _FCIMPORT_ fcSetFaceShift(float shiftX, float shiftY); // значения параметров в отрезке -1..1 задают, насколько сдвигать лицо при вырезании относительно центра. По умолчанию оба параметра равны 0.
int _FCIMPORT_ fcSetFaceShift_C(float shiftX, float shiftY, int contextID); // значения параметров в отрезке -1..1 задают, насколько сдвигать лицо при вырезании относительно центра. По умолчанию оба параметра равны 0.
int _FCIMPORT_ fcSetDetectionThreshold(int threshold); // аналогично FSDK_SetFaceDetectionThreshold. По умолчанию threshold = 3
int _FCIMPORT_ fcSetDetectionThreshold_C(int threshold, int contextID); // аналогично FSDK_SetFaceDetectionThreshold. По умолчанию threshold = 3
int _FCIMPORT_ fcSetDetectionPerformance(FcDetectionPerformance level); // как-то отображает level на парметры FSDK_SetFaceDetectionParameters.
int _FCIMPORT_ fcSetDetectionPerformance_C(FcDetectionPerformance level, int contextID); // как-то отображает level на парметры FSDK_SetFaceDetectionParameters.
int _FCIMPORT_ fcSetJpegQuality(int quality); // аналогично FSDK_SetJpegComressionQuality
int _FCIMPORT_ fcSetJpegQuality_C(int quality, int contextID); // аналогично FSDK_SetJpegComressionQuality



#if defined( _WIN32 ) || defined ( _WIN64 )
#ifdef __cplusplus
}
#endif
#endif

#endif

