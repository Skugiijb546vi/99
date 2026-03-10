#ifndef TOOLS_H
#define TOOLS_H

#include <jni.h>
#include <string>

inline std::string GetAndroidID(JNIEnv *env, jobject context) {
    jclass contextClass = env->GetObjectClass(context);
    jmethodID getContentResolverMethod = env->GetMethodID(contextClass, "getContentResolver", "()Landroid/content/ContentResolver;");
    jobject contentResolver = env->CallObjectMethod(context, getContentResolverMethod);

    jclass settingsSecureClass = env->FindClass("android/provider/Settings$Secure");
    jmethodID getStringMethod = env->GetStaticMethodID(settingsSecureClass, "getString", "(Landroid/content/ContentResolver;Ljava/lang/String;)Ljava/lang/String;");

    jstring androidIdStr = env->NewStringUTF("android_id");
    jstring androidId = (jstring) env->CallStaticObjectMethod(settingsSecureClass, getStringMethod, contentResolver, androidIdStr);

    const char *idChars = env->GetStringUTFChars(androidId, 0);
    std::string result(idChars);
    env->ReleaseStringUTFChars(androidId, idChars);

    env->DeleteLocalRef(androidIdStr);
    env->DeleteLocalRef(contentResolver);
    env->DeleteLocalRef(contextClass);
    env->DeleteLocalRef(settingsSecureClass);

    return result;
}

inline std::string GetDeviceModel(JNIEnv *env) {
    jclass buildClass = env->FindClass("android/os/Build");
    jfieldID modelId = env->GetStaticFieldID(buildClass, "MODEL", "Ljava/lang/String;");
    jstring modelStr = (jstring) env->GetStaticObjectField(buildClass, modelId);
    const char *modelChars = env->GetStringUTFChars(modelStr, 0);
    std::string result(modelChars);
    env->ReleaseStringUTFChars(modelStr, modelChars);
    env->DeleteLocalRef(modelStr);
    env->DeleteLocalRef(buildClass);
    return result;
}

inline std::string GetDeviceBrand(JNIEnv *env) {
    jclass buildClass = env->FindClass("android/os/Build");
    jfieldID brandId = env->GetStaticFieldID(buildClass, "BRAND", "Ljava/lang/String;");
    jstring brandStr = (jstring) env->GetStaticObjectField(buildClass, brandId);
    const char *brandChars = env->GetStringUTFChars(brandStr, 0);
    std::string result(brandChars);
    env->ReleaseStringUTFChars(brandStr, brandChars);
    env->DeleteLocalRef(brandStr);
    env->DeleteLocalRef(buildClass);
    return result;
}

inline std::string GetDeviceUniqueIdentifier(JNIEnv *env, const char* hwid) {
    return std::string(hwid);
}

#endif // TOOLS_H
