#ifndef PHP_LUXAND_FACECROP_H
#define PHP_LUXAND_FACECROP_H

#define PHP_LUXAND_FACECROP_VERSION "1.0.0"
#define PHP_LUXAND_FACECROP_EXTNAME "luxand_facecrop"

#ifdef ZTS
# include "TSRM.h"
#endif



PHP_FUNCTION(fcActivate);
PHP_FUNCTION(fcGetLicenseInfo);
PHP_FUNCTION(fcGetHardwareID);
PHP_FUNCTION(fcCreateContextID);
PHP_FUNCTION(fcFreeContextID);
PHP_FUNCTION(fcGetFacePosition);
PHP_FUNCTION(fcFaceCrop);
PHP_FUNCTION(fcSetFaceScale);
PHP_FUNCTION(fcSetFaceShift);
PHP_FUNCTION(fcSetDetectionThreshold);
PHP_FUNCTION(fcSetDetectionPerformance);
PHP_FUNCTION(fcSetJpegQuality);





#ifdef IN_FACECROP_EXT_CPP
extern "C"{
#endif

PHP_MINFO_FUNCTION(luxand_facecrop);
PHP_MINIT_FUNCTION(luxand_facecrop);
PHP_MSHUTDOWN_FUNCTION(luxand_facecrop);

extern zend_module_entry luxand_facecrop_module_entry;
#define phpext_luxand_facecrop_ptr &luxand_facecrop_module_entry

#ifdef IN_FACECROP_EXT_CPP
}
#endif

#endif

