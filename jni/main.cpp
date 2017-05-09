#include <jni.h>
#include <dlfcn.h>
#include <android/log.h>
#include <stdlib.h>
#include <Substrate.h>
#include <string>

#define LOG_TAG "FixOptions"
#define LOG(...) ((void)__android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__))

class AppPlatform{
 public:
 static std::string HOME_PATH;
 static std::string SETTINGS_PATH;
};
class AppPlatform_android{
 public:
 std::string _getAppDataOptionsLocation();
 std::string _getDefaultStoragePath();
 std::string& getInternalStoragePath();
 std::string& getSettingsPath();
 std::string& getUserdataPath();
};

std::string (*_AppPlatform_android$_getAppDataOptionsLocation)(AppPlatform_android*);
std::string AppPlatform_android$_getAppDataOptionsLocation(AppPlatform_android* app){
 std::string path=_AppPlatform_android$_getAppDataOptionsLocation(app);
//LOG("%s",(app->getUserdataPath()+AppPlatform::SETTINGS_PATH).c_str());
 return app->getUserdataPath()+AppPlatform::SETTINGS_PATH;
};

JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved) {
 MSHookFunction((void*)&AppPlatform_android::_getAppDataOptionsLocation,(void*)&AppPlatform_android$_getAppDataOptionsLocation,(void**)&_AppPlatform_android$_getAppDataOptionsLocation);
	return JNI_VERSION_1_2;
}
