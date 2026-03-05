/* LoadLibrary, FreeLibrary and GetProcAddress require <Windows.h> */
#include <Windows.h>
#include "matlab_i18n_init.h"

/* Declare a function handle for the i18n_init function */
typedef void (*fhi18n_init)(void);
int matlab_i18n_init() {    
    /* Obtain a handle to libmwi18n.dll */ 
    HMODULE matlab_i18 = LoadLibrary("libmwi18n.dll");
    if (matlab_i18 == NULL) {
        return -1;
    }
    /* Locate and obtain a handle to the correct initialization function */
    fhi18n_init i18n_init = 
            (fhi18n_init) GetProcAddress(matlab_i18,"i18n_init");
    if (i18n_init == NULL) {
        return -2;
    }    
    /* Call the initialization function */
    i18n_init();
    /* Release this specific reference to the library */
    FreeLibrary(matlab_i18);
    /* Return success */
    return 0;
}