#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "php.h"
#include "zend_API.h"
#include "php_ini.h"
#include "math.h"
#include "ext/standard/info.h"

#ifndef IN_FACECROP_EXT_CPP
#define IN_FACECROP_EXT_CPP
#endif

#include "php_luxand_facecrop.h"
#include "LuxandFaceCrop.h"

#ifndef FACECROP_MAX
#define FACECROP_MAX(x, y) (((x) >= (y)) ? (x) : (y))
#endif
#ifndef FACECROP_MIN
#define FACECROP_MIN(x, y) (((x) >= (y)) ? (y) : (x))
#endif


extern "C"{

static function_entry luxand_facecrop_functions[] = {
    PHP_FE(fcActivate, NULL)
    PHP_FE(fcGetHardwareID, NULL)
    PHP_FE(fcGetLicenseInfo, NULL)
    PHP_FE(fcCreateContextID, NULL)
    PHP_FE(fcFreeContextID, NULL)
    PHP_FE(fcGetFacePosition, NULL)
    PHP_FE(fcFaceCrop, NULL)
	PHP_FE(fcSetFaceScale, NULL)
	PHP_FE(fcSetFaceShift, NULL)
	PHP_FE(fcSetDetectionThreshold, NULL)
	PHP_FE(fcSetDetectionPerformance, NULL)
	PHP_FE(fcSetJpegQuality, NULL)

    {NULL, NULL, NULL}
};

zend_module_entry luxand_facecrop_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
    STANDARD_MODULE_HEADER,
#endif
    PHP_LUXAND_FACECROP_EXTNAME,
    luxand_facecrop_functions,
    PHP_MINIT(luxand_facecrop),
    PHP_MSHUTDOWN(luxand_facecrop),
    NULL,
    NULL,
    PHP_MINFO(luxand_facecrop),
#if ZEND_MODULE_API_NO >= 20010901
    PHP_LUXAND_FACECROP_VERSION,
#endif
    STANDARD_MODULE_PROPERTIES
};


#ifdef COMPILE_DL_LUXAND_FACECROP
ZEND_GET_MODULE(luxand_facecrop)
#endif

PHP_MINIT_FUNCTION(luxand_facecrop)
{
	fcInitialize();
	return SUCCESS;
}
PHP_MSHUTDOWN_FUNCTION(luxand_facecrop)
{
	fcFinalize();
	return SUCCESS;
}

PHP_MINFO_FUNCTION(luxand_facecrop)
{
	php_info_print_table_start();
	php_info_print_table_row(2, "luxand_facecrop support", "enabled");
	php_info_print_table_row(2, "luxand_facecrop version", PHP_LUXAND_FACECROP_VERSION);
	php_info_print_table_end();
}

}


PHP_FUNCTION(fcActivate)
{
	char * key;
	long keylen;
	
	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &key, &keylen) == FAILURE) {
		RETURN_NULL();
	}

	long result = fcActivate(key);
	RETURN_LONG(result);
}

PHP_FUNCTION(fcGetHardwareID)
{
	char hwid[1024];
	if (!fcGetHardwareID(hwid)){
		RETURN_STRING(hwid, 1);
	}
	
}


PHP_FUNCTION(fcGetLicenseInfo)
{
	char licinf[1024];
	if (!fcGetLicenseInfo(licinf)){
		RETURN_STRING(licinf, 1);
	}
	
}


PHP_FUNCTION(fcCreateContextID)
{
	int c_id=0;
	if (!fcCreateContextID(&c_id)){
		RETURN_LONG(c_id);
	} else {
		RETURN_NULL();
	}
}

PHP_FUNCTION(fcFreeContextID)
{
	long c_id;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &c_id) == FAILURE) {
		RETURN_NULL();
	}
	
	if (!fcFreeContextID((int)c_id)){ 
		RETURN_LONG(0);
	}else{
		RETURN_NULL();
	}
}

//using php args passing
static void php_luxand_face_crop(INTERNAL_FUNCTION_PARAMETERS, int only_return_coords)
{
	char * fname;
	long fnamelen;
	char * outfname;
	long outfnamelen;
	long width, height; //desired_width, desired_height
	long context_id;	

	if(only_return_coords){
		if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "slll", &fname, &fnamelen, &width, &height, &context_id) == FAILURE) {
			RETURN_NULL();
		}
	} else { //crop face
		if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sslll", &fname, &fnamelen, &outfname, &outfnamelen, &width, &height, &context_id) == FAILURE) {
			RETURN_NULL();
		}
	}

	long result;
	
	if(only_return_coords){
		int x1 = 0;
		int y1 = 0;
		int x2 = 0;
		int y2 = 0;
		result = fcGetFacePosition_C(fname, width, height, &x1, &y1, &x2, &y2, context_id);
		if (result){
			RETURN_LONG(result);
		}
	
		array_init(return_value);
		add_assoc_long(return_value, "x1", x1);
		add_assoc_long(return_value, "y1", y1);
		add_assoc_long(return_value, "x2", x2);
		add_assoc_long(return_value, "y2", y2);
	} else {
		result = fcFaceCrop_C(fname, outfname, width, height, context_id);
		RETURN_LONG(result);
	}
	
}

PHP_FUNCTION(fcGetFacePosition)
{
	php_luxand_face_crop(INTERNAL_FUNCTION_PARAM_PASSTHRU, 1);
}
PHP_FUNCTION(fcFaceCrop)
{
	php_luxand_face_crop(INTERNAL_FUNCTION_PARAM_PASSTHRU, 0);
}

PHP_FUNCTION(fcSetFaceScale)
{
	long context_id;	
	double scale;
	
	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "dl", &scale, &context_id) == FAILURE) {
		RETURN_NULL();
	}

	long result = fcSetFaceScale_C(scale, context_id);
	RETURN_LONG(result);
}

PHP_FUNCTION(fcSetFaceShift)
{
	long context_id;	
	double shiftX, shiftY;
	
	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ddl", &shiftX, &shiftY, &context_id) == FAILURE) {
		RETURN_NULL();
	}

	long result = fcSetFaceShift_C(shiftX, shiftY, context_id);
	RETURN_LONG(result);
}

PHP_FUNCTION(fcSetDetectionThreshold)
{
	long context_id;	
	long threshold;
	
	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ll", &threshold, &context_id) == FAILURE) {
		RETURN_NULL();
	}

	long result = fcSetDetectionThreshold_C(threshold, context_id);
	RETURN_LONG(result);
}

PHP_FUNCTION(fcSetDetectionPerformance)
{
	long context_id;	
	long perf_level;
	
	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ll", &perf_level, &context_id) == FAILURE) {
		RETURN_NULL();
	} else if (perf_level < 0 || perf_level > 2){
		RETURN_NULL();
	}

	long result = fcSetDetectionPerformance_C((FcDetectionPerformance)perf_level, context_id);
	RETURN_LONG(result);
}

PHP_FUNCTION(fcSetJpegQuality)
{
	long context_id;	
	long jpeg_quality;
	
	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ll", &jpeg_quality, &context_id) == FAILURE) {
		RETURN_NULL();
	}

	long result = fcSetJpegQuality_C(jpeg_quality, context_id);
	RETURN_LONG(result);
}

/*
Zend type specifiers
---------------
  l      - long
  d      - double
  s      - string (with possible null bytes) and its length
  b      - boolean, stored in zend_bool
  r      - resource (stored in zval)
  a      - array
  o      - object (of any type)
  O      - object (of specific type, specified by class entry)
  z      - the actual zval
*/
