#include <jni.h>
#include <string>
#include <cstdarg>

/**
 * 调用Java的方法
 * @param env
 * @param java_obj
 * @param java_class
 * @param name
 * @param sig
 * @return
 */
jobject callStaticMethod(JNIEnv *env, jobject java_obj, const char *name, const char *sig) {
    jclass java_class = env->GetObjectClass(java_obj);
    jmethodID methodID = env->GetStaticMethodID(java_class, name, sig);
    jobject methodResult = env->CallStaticObjectMethod(java_class, methodID);
    env->DeleteLocalRef(java_class);
    return methodResult;
}

/**
 * 调用Java的方法
 * @param env
 * @param java_obj
 * @param java_class
 * @param name
 * @param sig
 * @return
 */
jobject callStaticMethod(JNIEnv *env, jclass java_class, const char *name, const char *sig) {
    jmethodID methodID = env->GetStaticMethodID(java_class, name, sig);
    jobject methodResult = env->CallStaticObjectMethod(java_class, methodID);
    return methodResult;
}

/**
 * 调用Java的方法
 * @param env
 * @param java_obj
 * @param java_class
 * @param name
 * @param sig
 * @return
 */
jobject callStaticMethod(JNIEnv *env, const char *java_class_name, const char *name, const char *sig) {
    jclass java_class = env->FindClass(java_class_name);
    jmethodID methodID = env->GetStaticMethodID(java_class, name, sig);
    jobject methodResult = env->CallStaticObjectMethod(java_class, methodID);
    env->DeleteLocalRef(java_class);
    return methodResult;
}

/**
 * 调用java的静态方法
 * @param env
 * @param java_obj
 * @param name
 * @param sig
 * @param args
 * @return
 */
jobject callStaticMethodArg(JNIEnv *env, jclass java_class, const char *name,
                            const char *sig, ...) {
    jmethodID methodID = env->GetStaticMethodID(java_class, name, sig);
    va_list args;
    va_start(args, sig);
    jobject methodResult = env->CallStaticObjectMethodV(java_class, methodID, args);
    va_end(args);
    return methodResult;
}


/**
 * 调用java的静态方法
 * @param env
 * @param java_obj
 * @param name
 * @param sig
 * @param args
 * @return
 */
jobject callStaticMethodArg(JNIEnv *env, jobject java_obj, const char *name,
                            const char *sig, ...) {
    jclass java_class = env->GetObjectClass(java_obj);
    jmethodID methodID = env->GetStaticMethodID(java_class, name, sig);

    va_list args;
    va_start(args, sig);
    jobject methodResult = env->CallStaticObjectMethodV(java_class, methodID, args);
    va_end(args);
    env->DeleteLocalRef(java_class);
    return methodResult;
}
/**
 * 调用java的静态方法
 * @param env
 * @param java_class_name
 * @param name
 * @param sig
 * @param ...
 * @return
 */
jobject callStaticMethodArg(JNIEnv *env, const char *java_class_name,
                            const char *name,const char *sig, ...) {
    jclass java_class = env->FindClass(java_class_name);
    jmethodID methodID = env->GetStaticMethodID(java_class, name, sig);
    va_list args;
    va_start(args, sig);
    jobject methodResult = env->CallStaticObjectMethodV(java_class, methodID, args);
    va_end(args);
    env->DeleteLocalRef(java_class);
    return methodResult;
}
/**-------------------- 静态方法分界线 -----------------------*/

/**
 * 调用Java的方法
 * @param env
 * @param java_obj
 * @param java_class
 * @param name
 * @param sig
 * @return
 */
jobject callJavaMethod(JNIEnv *env, jobject java_obj, const char *name, const char *sig) {
    jclass java_class = env->GetObjectClass(java_obj);
    jmethodID methodID = env->GetMethodID(java_class, name, sig);
    jobject methodResult = env->CallObjectMethod(java_obj, methodID);
    env->DeleteLocalRef(java_class);
    return methodResult;
}

/**
 * 调用Java的方法
 * @param env
 * @param java_obj
 * @param java_class
 * @param name
 * @param sig
 * @return
 */
jobject callJavaMethod(JNIEnv *env, jobject java_obj, jclass java_class,
                       const char *name, const char *sig) {
    jmethodID methodID = env->GetMethodID(java_class, name, sig);
    jobject methodResult = env->CallObjectMethod(java_obj, methodID);
    return methodResult;
}

/**
 * 调用Java的方法
 * @param env
 * @param java_obj
 * @param java_class
 * @param name
 * @param sig
 * @return
 */
jobject callJavaMethodArg(JNIEnv *env, jobject java_obj,
                          const char *name, const char *sig, ...) {
    jclass java_class = env->GetObjectClass(java_obj);
    jmethodID methodID = env->GetMethodID(java_class, name, sig);
    va_list args;
    va_start(args, sig);
    jobject methodResult = env->CallObjectMethodV(java_obj, methodID, args);
    va_end(args);
    env->DeleteLocalRef(java_class);
    return methodResult;
}

/**
 * 调用Java的方法
 * @param env
 * @param java_obj
 * @param java_class
 * @param name
 * @param sig
 * @param args
 * @return
 */
jobject callJavaMethodArg(JNIEnv *env, jobject java_obj, jclass java_class,
                          const char *name, const char *sig, ...) {
    jmethodID methodID = env->GetMethodID(java_class, name, sig);
    va_list args;
    va_start(args, sig);
    jobject methodResult = env->CallObjectMethodV(java_obj, methodID, args);
    va_end(args);
    return methodResult;
}
/**-------------------- 普通方法分界线 -----------------------*/
/**
 * 获取java的成员变量的值
 * @param env
 * @param java_obj
 * @param name
 * @param sig
 * @return
 */
jobject getJavaField(JNIEnv *env, jobject java_obj, const char *name, const char *sig) {
    jclass java_class = env->GetObjectClass(java_obj);
    jfieldID fieldId = env->GetFieldID(java_class, name, sig);
    jobject fieldResult = env->GetObjectField(java_obj, fieldId);
    env->DeleteLocalRef(java_class);
    return fieldResult;
}

jfieldID getJavaFieldId(JNIEnv *env, jobject java_obj, const char *name, const char *sig) {
    jclass java_class = env->GetObjectClass(java_obj);
    jfieldID fieldId = env->GetFieldID(java_class, name, sig);
    env->DeleteLocalRef(java_class);
    return fieldId;
}

/**
 * 获取java的成员变量的值
 * @param env
 * @param java_obj
 * @param java_class
 * @param name
 * @param sig
 * @return
 */
jobject getJavaField(JNIEnv *env, jobject java_obj, jclass java_class,
                     const char *name, const char *sig) {
    jfieldID fieldId = env->GetFieldID(java_class, name, sig);
    jobject fieldResult = env->GetObjectField(java_obj, fieldId);
    return fieldResult;
}

/**-------------------- 类操作方法分界线 -----------------------*/

/**
 * 创建一个Object
 * @param env
 * @param java_obj
 * @param java_class
 * @param name
 * @param sig
 * @param args
 * @return
 */
jobject newObject(JNIEnv *env, jclass java_class,
                  const char *method_name, const char *sig) {
    jmethodID methodID = env->GetMethodID(java_class, method_name, sig);
    jobject result = env->NewObject(java_class, methodID);
    return result;
}

/**
 * 创建一个Object
 * @param env
 * @param java_obj
 * @param java_class
 * @param name
 * @param sig
 * @param args
 * @return
 */
jobject newObject(JNIEnv *env, const char *java_class_name,
                  const char *method_name, const char *sig) {
    jclass java_class = env->FindClass(java_class_name);
    jmethodID methodID = env->GetMethodID(java_class, method_name, sig);
    jobject result = env->NewObject(java_class, methodID);
    env->DeleteLocalRef(java_class);
    return result;
}

/**
 * 带不确定参数的构建方法
 * @param env
 * @param java_class
 * @param name
 * @param sig
 * @param ...
 * @return
 */
jobject newObjectArg(JNIEnv *env, jclass java_class,
                     const char *method_name, const char *sig, ...) {
    jmethodID methodID = env->GetMethodID(java_class, method_name, sig);
    va_list args;
    va_start(args, sig);
    jobject methodResult = env->NewObjectV(java_class, methodID, args);
    va_end(args);
    return methodResult;
}

/**
 * 带不确定参数的构建方法
 * @param env
 * @param java_class
 * @param name
 * @param sig
 * @param ...
 * @return
 */
jobject newObjectArg(JNIEnv *env, const char *java_class_name,
                     const char *method_name, const char *sig, ...) {
    jclass java_class = env->FindClass(java_class_name);
    jmethodID methodID = env->GetMethodID(java_class, method_name, sig);
    va_list args;
    va_start(args, sig);
    jobject methodResult = env->NewObjectV(java_class, methodID, args);
    va_end(args);
    env->DeleteLocalRef(java_class);
    return methodResult;
}