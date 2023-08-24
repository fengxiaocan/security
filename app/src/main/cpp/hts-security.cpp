#include <jni.h>
#include <string>
#include "app-validate.cpp"

extern "C" {

JNIEXPORT jint JNICALL
JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env;
    if (vm->GetEnv((void **) (&env), JNI_VERSION_1_6) != JNI_OK) {
        throw "That is System Error！";
        return -1;
    }
    if (checkSignature(env) != JNI_TRUE) {
        return -1;
    }
    return JNI_VERSION_1_6;
}
}