#include <jni.h>
#include <string>
#include "app-log.cpp"
#include "java-jni.cpp"

const char HEX_CODE[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E',
                         'F'};
const char *APP_SIGNATURE = "2S296E386B665E76ADF700E7EB84E4C6EEE33DFA";
char *appSha = NULL;

char *getPackageSha1(JNIEnv *pEnv, jobject pJobject);

char *toSha1Array(JNIEnv *pEnv, jbyteArray pArray);

jobject getAppPackageInfo(JNIEnv *pEnv, jobject pJobject);

/**
 *
 * get sha1  by reflect
 *
 */
char *getAppSha1(JNIEnv *env, jobject context_object) {
    if (appSha == NULL) {
        jobject package_info = getAppPackageInfo(env,context_object);
        appSha = getPackageSha1(env,package_info);
        env->DeleteLocalRef(package_info);
    }
    return appSha;
}


jboolean checkSignature(JNIEnv *env, jobject context) {
    const char *appSignatureSha1 = getAppSha1(env, context);
    jstring releaseSignature = env->NewStringUTF(APP_SIGNATURE);
    jstring appSignature = env->NewStringUTF(appSignatureSha1);
    const char *charAppSignature = env->GetStringUTFChars(appSignature, NULL);
    const char *charReleaseSignature = env->GetStringUTFChars(releaseSignature, NULL);
    jboolean result = JNI_FALSE;
    if (charAppSignature != NULL && charReleaseSignature != NULL) {
        if (strcmp(charAppSignature, charReleaseSignature) == 0) {
            result = JNI_TRUE;
        } else {
            throw "That is System BUG!";
        }
    } else {
        throw "That is System BUG!";
    }
    env->ReleaseStringUTFChars(appSignature, charAppSignature);
    env->ReleaseStringUTFChars(releaseSignature, charReleaseSignature);
    return result;
}


/**
 *
 *get Application Context
 *
 */
jobject getApplication(JNIEnv *env) {
    jobject application = NULL;
    jclass activity_thread_clz = env->FindClass("android/app/ActivityThread");
    if (activity_thread_clz != NULL) {
        jmethodID currentApplication = env->GetStaticMethodID(
                activity_thread_clz, "currentApplication", "()Landroid/app/Application;");
        if (currentApplication != NULL) {
            application = env->CallStaticObjectMethod(activity_thread_clz, currentApplication);
        }
        env->DeleteLocalRef(activity_thread_clz);
    }
    return application;
}


/**
 *
 *validate signature
 *
 */
jboolean checkSignature(JNIEnv *env) {
    jobject appContext = getApplication(env);
    if (appContext != NULL) {
        return checkSignature(env, appContext);
    }
    return JNI_FALSE;
}
/**
 * 获取安装包的信息
 * @param env
 * @param context
 * @return
 */
jobject getAppPackageInfo(JNIEnv *env, jobject context){
    jclass context_class = env->GetObjectClass(context);
    //获取pm
    jobject package_manager = callJavaMethod(env, context, context_class, "getPackageManager",
                                             "()Landroid/content/pm/PackageManager;");
    //获取包名
    jstring package_name = (jstring) callJavaMethod(env, context, context_class, "getPackageName",
                                                    "()Ljava/lang/String;");
    //释放context_class
    env->DeleteLocalRef(context_class);
    //获取packInfo
    jobject package_info = callJavaMethodArg(env, package_manager, "getPackageInfo",
                                             "(Ljava/lang/String;I)Landroid/content/pm/PackageInfo;",
                                             package_name, 0x40);
    //释放package_manager
    env->DeleteLocalRef(package_manager);
    //释放package_name
    env->DeleteLocalRef(package_name);
    return package_info;
}

/**
 * 获取安装包路径
 * @param env
 * @param context
 * @return
 */
jstring getApkPath(JNIEnv *env, jobject context) {
    //获取packInfo
    jobject package_info = getAppPackageInfo(env,context);

    jobject application_info_obj = getJavaField(env, package_info, "applicationInfo",
                                                "Landroid/content/pm/ApplicationInfo;");
    //释放package_info
    env->DeleteLocalRef(package_info);

    jstring sourcePathObj = (jstring) getJavaField(env, application_info_obj, "sourceDir",
                                                   "Ljava/lang/String;");
    env->DeleteLocalRef(application_info_obj);
    return sourcePathObj;
}

/**
 * 获取apk的签名sha1
 * @param env
 * @param package_info
 * @return
 */
char *getPackageSha1(JNIEnv *env, jobject package_info) {
    jobjectArray signature_object_array = (jobjectArray)
            getJavaField(env, package_info, "signatures", "[Landroid/content/pm/Signature;");
    //获取签名数组中的第一个签名信息
    jobject signature_object = env->GetObjectArrayElement(signature_object_array, 0);

    env->DeleteLocalRef(signature_object_array);
    //签名新转byte数组
    jbyteArray signature_byte = (jbyteArray)
            callJavaMethod(env, signature_object, "toByteArray", "()[B");
    env->DeleteLocalRef(signature_object);

    jobject byte_array_input = newObjectArg(env, "java/io/ByteArrayInputStream", "<init>", "([B)V",
                                            signature_byte);
    env->DeleteLocalRef(signature_byte);

    jstring x_509_jstring = env->NewStringUTF("X.509");
    jclass certificate_factory_class = env->FindClass("java/security/cert/CertificateFactory");
    jobject cert_factory = callStaticMethodArg(env, certificate_factory_class, "getInstance",
                                               "(Ljava/lang/String;)Ljava/security/cert/CertificateFactory;",
                                               x_509_jstring);
    env->DeleteLocalRef(x_509_jstring);
    jobject x509_cert = callJavaMethodArg(env, cert_factory, certificate_factory_class,
                                          "generateCertificate",
                                          ("(Ljava/io/InputStream;)Ljava/security/cert/Certificate;"),
                                          byte_array_input);
    env->DeleteLocalRef(byte_array_input);
    env->DeleteLocalRef(certificate_factory_class);
    env->DeleteLocalRef(cert_factory);

    jbyteArray cert_byte = (jbyteArray) callJavaMethod(env, x509_cert, "getEncoded", "()[B");

    env->DeleteLocalRef(x509_cert);

    jclass message_digest_class = env->FindClass("java/security/MessageDigest");
    jstring sha1_jstring = env->NewStringUTF("SHA1");

    jobject sha1_digest = callStaticMethodArg(env, message_digest_class, "getInstance",
                                              "(Ljava/lang/String;)Ljava/security/MessageDigest;",
                                              sha1_jstring);
    jbyteArray sha1_byte = (jbyteArray) callJavaMethodArg(env, sha1_digest, "digest", "([B)[B",
                                                          cert_byte);
    env->DeleteLocalRef(cert_byte);
    env->DeleteLocalRef(sha1_jstring);
    env->DeleteLocalRef(message_digest_class);
    env->DeleteLocalRef(sha1_digest);
    return toSha1Array(env,sha1_byte);
}

char *toSha1Array(JNIEnv *env, jbyteArray sha1_byte) {
    jsize array_size = env->GetArrayLength(sha1_byte);
    jbyte *sha1 = env->GetByteArrayElements(sha1_byte, NULL);

    char *hex_sha = new char[array_size * 2 + 1];
    for (int i = 0; i < array_size; ++i) {
        hex_sha[2 * i] = HEX_CODE[((unsigned char) sha1[i]) / 16];
        hex_sha[2 * i + 1] = HEX_CODE[((unsigned char) sha1[i]) % 16];
    }
    hex_sha[array_size * 2] = '\0';
    env->DeleteLocalRef(sha1_byte);
    return hex_sha;
}
