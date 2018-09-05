#if defined(BUILD_ATOT)
#  define ATOT_API _declspec(dllexport)
#else
#  define ATOT_API _declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

ATOT_API void atot_set_host_and_port(const char* host, int port);
ATOT_API void atot_set_timeout(int timeout_sec);
ATOT_API int atot_recognize(const char* wav_filename, const char* text_filename);

#ifdef __cplusplus
}
#endif
