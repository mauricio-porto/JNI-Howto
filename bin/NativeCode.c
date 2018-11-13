/* NativeCode.c file */
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "JNICode.h"

#define DEBUG0(STUFF)    (fprintf(stdout, "%s:%d - %s\n", __FILE__, __LINE__, (STUFF)), fflush(stdout))		// for printing strings
#define DEBUG1(STUFF)    (fprintf(stdout, "%s:%d - %d\n", __FILE__, __LINE__, (STUFF)), fflush(stdout))		// for printing numbers
#define DEBUG2(STUFF)    (fprintf(stdout, "%s:%d - %p\n", __FILE__, __LINE__, (STUFF)), fflush(stdout))		// for printing addresses

JNIEnv* jniEnv;

jclass class_id;
jobject object_id;
jmethodID callback_id;


// Is automatically called once the native code is loaded via System.loadLibary(...);

/*
jint JNI_OnLoad(JavaVM* vm, void* reserved) {
    jint versione = (*vm)->GetEnv(vm, (void **) &jniEnv, JNI_VERSION_1_6);
    DEBUG1(versione);
    if (versione != JNI_OK) {
        return JNI_ERR;
    }
}
*/


// Is automatically called once the Classloader is destroyed

/*
void JNI_OnUnload(JavaVM *vm, void *reserved) {
    if ((*vm)->GetEnv(vm, (void **) &jniEnv, JNI_VERSION_1_6) != JNI_OK) {
        // Something is wrong but nothing we can do about this :(
        return;
    } else {
        // delete global references so the GC can collect them
        if (object_id != NULL) {
            (*jniEnv)->DeleteGlobalRef(jniEnv, object_id);
        }
     }
}
*/


static void setInt(JNIEnv *env, jobject obj, const char *name, jint value)
{
    jclass cls = (*env)->GetObjectClass(env, obj);
    jfieldID fid = (*env)->GetFieldID(env, cls, name, "I");
    
    (*env)->SetIntField(env, obj, fid, value);
}

static jint getInt(JNIEnv *env, jobject obj, const char *name)
{
    jclass cls = (*env)->GetObjectClass(env, obj);
    jfieldID fid = (*env)->GetFieldID(env, cls, name, "I");
    
    return (*env)->GetIntField(env, obj, fid);
}

static void throwException(JNIEnv *env, jobject obj, const char *message)
{
    jclass cls = (*env)->FindClass(env, "java/io/Exception");
    
    (*env)->ThrowNew(env, cls, message);
}

static void callback() {
	jstring message = (*jniEnv)->NewStringUTF(jniEnv, "Hello from C");
	(*jniEnv)->CallVoidMethod(jniEnv, object_id, callback_id, message);
}

JNIEXPORT void JNICALL Java_ks_mapo_jni_JNICode_registerCallback(JNIEnv *env, jobject obj, jstring methodName, jstring signature)
{
    const char *c_methodName = (*env)->GetStringUTFChars(env, methodName, NULL);
    const char *c_signature = (*env)->GetStringUTFChars(env, signature, NULL);

    jniEnv = env;
    object_id = obj;
    class_id = (*env)->GetObjectClass(env, obj);

    callback_id = (*env)->GetMethodID(env, class_id, c_methodName, c_signature);
	if (callback_id == NULL) {
		throwException(env, obj, "Could not register your callback.");
	} else {
		sleep(1);
		callback();
	}
}

JNIEXPORT void JNICALL Java_ks_mapo_jni_JNICode_printNative(JNIEnv *env, jobject obj, jstring message)
{
    const char *c_message = (*env)->GetStringUTFChars(env, message, NULL);
    DEBUG0("Received from Java:");
    DEBUG0(c_message);
}
