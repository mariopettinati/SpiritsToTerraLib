#if defined( WIN32 ) || defined( __WIN32__ ) || defined ( _WIN32 ) || defined( WIN64 ) || defined( _WIN32_WCE )

#if defined(_MSC_VER) /* MSVC Compiler */
#pragma warning(disable: 4251)
#endif

#ifdef TERRALIB_CONVERTER_AS_DLL
#define TC_DLL __declspec(dllexport)
#else
#define TC_DLL __declspec(dllimport)
#endif

#else
#define TC_DLL
#endif