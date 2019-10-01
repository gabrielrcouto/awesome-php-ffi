#define FFI_LIB "/Library/Java/JavaVirtualMachines/jdk-13.jdk/Contents/Home/lib/server/libjvm.dylib"

char *strdup(const char *s);

typedef int jint;
typedef long jlong;
typedef signed char jbyte;
typedef unsigned char   jboolean;
typedef unsigned short  jchar;
typedef short           jshort;
typedef float           jfloat;
typedef double          jdouble;
typedef jint            jsize;

typedef const struct JNIInvokeInterface_ *JavaVM;
typedef const struct JNINativeInterface_ *JNIEnv;

struct _jobject;

typedef struct _jobject *jobject;
typedef jobject jclass;
typedef jobject jthrowable;
typedef jobject jstring;
typedef jobject jarray;
typedef jarray jbooleanArray;
typedef jarray jbyteArray;
typedef jarray jcharArray;
typedef jarray jshortArray;
typedef jarray jintArray;
typedef jarray jlongArray;
typedef jarray jfloatArray;
typedef jarray jdoubleArray;
typedef jarray jobjectArray;

struct _jmethodID;
typedef struct _jmethodID *jmethodID;

struct _jfieldID;
typedef struct _jfieldID *jfieldID;

typedef union jvalue {
    jboolean z;
    jbyte    b;
    jchar    c;
    jshort   s;
    jint     i;
    jlong    j;
    jfloat   f;
    jdouble  d;
    jobject  l;
} jvalue;

typedef struct {
    char *name;
    char *signature;
    void *fnPtr;
} JNINativeMethod;

typedef jobject jweak;

typedef enum _jobjectType {
     JNIInvalidRefType    = 0,
     JNILocalRefType      = 1,
     JNIGlobalRefType     = 2,
     JNIWeakGlobalRefType = 3
} jobjectRefType;

typedef struct JavaVMOption {
    char *optionString;
    void *extraInfo;
} JavaVMOption;

typedef struct JavaVMInitArgs {
    jint version;

    jint nOptions;
    JavaVMOption *options;
    jboolean ignoreUnrecognized;
} JavaVMInitArgs;

struct JNIInvokeInterface_ {
    void *reserved0;
    void *reserved1;
    void *reserved2;

    jint (*DestroyJavaVM)(JavaVM *vm);

    jint (*AttachCurrentThread)(JavaVM *vm, void **penv, void *args);

    jint (*DetachCurrentThread)(JavaVM *vm);

    jint (*GetEnv)(JavaVM *vm, void **penv, jint version);

    jint (*AttachCurrentThreadAsDaemon)(JavaVM *vm, void **penv, void *args);
};

typedef jobject (*CallObjectMethod_func_t)(JNIEnv *env, jobject obj, jmethodID methodID, ...);
typedef jobject (*CallObjectMethodA_func_t)(JNIEnv *env, jobject obj, jmethodID methodID, const jvalue * args);
typedef jclass (*FindClass_func_t)(JNIEnv *env, const char *name);
typedef jmethodID (*GetMethodID_func_t)(JNIEnv *env, jclass clazz, const char *name, const char *sig);
typedef jmethodID (*GetStaticMethodID_func_t)(JNIEnv *env, jclass clazz, const char *name, const char *sig);
typedef const char* (*GetStringUTFChars_func_t)(JNIEnv *env, jstring str, jboolean *isCopy);
typedef jint (*GetVersion_func_t)(JNIEnv *env);
typedef jobject (*NewObject_func_t)(JNIEnv *env, jclass clazz, jmethodID methodID, ...);
typedef jstring (*NewString_func_t)(JNIEnv *env, const jchar *unicode, jsize len);
typedef jstring (*NewStringUTF_func_t)(JNIEnv *env, const char *utf);

struct JNINativeInterface_ {
    void *reserved0;
    void *reserved1;
    void *reserved2;

    void *reserved3;

    GetVersion_func_t *GetVersion;

    jclass (*DefineClass)
      (JNIEnv *env, const char *name, jobject loader, const jbyte *buf,
       jsize len);

    FindClass_func_t *FindClass;

    jmethodID (*FromReflectedMethod)
      (JNIEnv *env, jobject method);
    jfieldID (*FromReflectedField)
      (JNIEnv *env, jobject field);

    jobject (*ToReflectedMethod)
      (JNIEnv *env, jclass cls, jmethodID methodID, jboolean isStatic);

    jclass (*GetSuperclass)
      (JNIEnv *env, jclass sub);
    jboolean (*IsAssignableFrom)
      (JNIEnv *env, jclass sub, jclass sup);

    jobject (*ToReflectedField)
      (JNIEnv *env, jclass cls, jfieldID fieldID, jboolean isStatic);

    jint (*Throw)
      (JNIEnv *env, jthrowable obj);
    jint (*ThrowNew)
      (JNIEnv *env, jclass clazz, const char *msg);
    jthrowable (*ExceptionOccurred)
      (JNIEnv *env);
    void (*ExceptionDescribe)
      (JNIEnv *env);
    void (*ExceptionClear)
      (JNIEnv *env);
    void (*FatalError)
      (JNIEnv *env, const char *msg);

    jint (*PushLocalFrame)
      (JNIEnv *env, jint capacity);
    jobject (*PopLocalFrame)
      (JNIEnv *env, jobject result);

    jobject (*NewGlobalRef)
      (JNIEnv *env, jobject lobj);
    void (*DeleteGlobalRef)
      (JNIEnv *env, jobject gref);
    void (*DeleteLocalRef)
      (JNIEnv *env, jobject obj);
    jboolean (*IsSameObject)
      (JNIEnv *env, jobject obj1, jobject obj2);
    jobject (*NewLocalRef)
      (JNIEnv *env, jobject ref);
    jint (*EnsureLocalCapacity)
      (JNIEnv *env, jint capacity);

    jobject (*AllocObject)
      (JNIEnv *env, jclass clazz);
    
    NewObject_func_t *NewObject;
    
    jobject (*NewObjectV)
      (JNIEnv *env, jclass clazz, jmethodID methodID, va_list args);
    jobject (*NewObjectA)
      (JNIEnv *env, jclass clazz, jmethodID methodID, const jvalue *args);

    jclass (*GetObjectClass)
      (JNIEnv *env, jobject obj);
    jboolean (*IsInstanceOf)
      (JNIEnv *env, jobject obj, jclass clazz);

    GetMethodID_func_t *GetMethodID;

    CallObjectMethod_func_t *CallObjectMethod;
    jobject (*CallObjectMethodV)
      (JNIEnv *env, jobject obj, jmethodID methodID, va_list args);
    CallObjectMethodA_func_t *CallObjectMethodA;

    jboolean (*CallBooleanMethod)
      (JNIEnv *env, jobject obj, jmethodID methodID, ...);
    jboolean (*CallBooleanMethodV)
      (JNIEnv *env, jobject obj, jmethodID methodID, va_list args);
    jboolean (*CallBooleanMethodA)
      (JNIEnv *env, jobject obj, jmethodID methodID, const jvalue * args);

    jbyte (*CallByteMethod)
      (JNIEnv *env, jobject obj, jmethodID methodID, ...);
    jbyte (*CallByteMethodV)
      (JNIEnv *env, jobject obj, jmethodID methodID, va_list args);
    jbyte (*CallByteMethodA)
      (JNIEnv *env, jobject obj, jmethodID methodID, const jvalue *args);

    jchar (*CallCharMethod)
      (JNIEnv *env, jobject obj, jmethodID methodID, ...);
    jchar (*CallCharMethodV)
      (JNIEnv *env, jobject obj, jmethodID methodID, va_list args);
    jchar (*CallCharMethodA)
      (JNIEnv *env, jobject obj, jmethodID methodID, const jvalue *args);

    jshort (*CallShortMethod)
      (JNIEnv *env, jobject obj, jmethodID methodID, ...);
    jshort (*CallShortMethodV)
      (JNIEnv *env, jobject obj, jmethodID methodID, va_list args);
    jshort (*CallShortMethodA)
      (JNIEnv *env, jobject obj, jmethodID methodID, const jvalue *args);

    jint (*CallIntMethod)
      (JNIEnv *env, jobject obj, jmethodID methodID, ...);
    jint (*CallIntMethodV)
      (JNIEnv *env, jobject obj, jmethodID methodID, va_list args);
    jint (*CallIntMethodA)
      (JNIEnv *env, jobject obj, jmethodID methodID, const jvalue *args);

    jlong (*CallLongMethod)
      (JNIEnv *env, jobject obj, jmethodID methodID, ...);
    jlong (*CallLongMethodV)
      (JNIEnv *env, jobject obj, jmethodID methodID, va_list args);
    jlong (*CallLongMethodA)
      (JNIEnv *env, jobject obj, jmethodID methodID, const jvalue *args);

    jfloat (*CallFloatMethod)
      (JNIEnv *env, jobject obj, jmethodID methodID, ...);
    jfloat (*CallFloatMethodV)
      (JNIEnv *env, jobject obj, jmethodID methodID, va_list args);
    jfloat (*CallFloatMethodA)
      (JNIEnv *env, jobject obj, jmethodID methodID, const jvalue *args);

    jdouble (*CallDoubleMethod)
      (JNIEnv *env, jobject obj, jmethodID methodID, ...);
    jdouble (*CallDoubleMethodV)
      (JNIEnv *env, jobject obj, jmethodID methodID, va_list args);
    jdouble (*CallDoubleMethodA)
      (JNIEnv *env, jobject obj, jmethodID methodID, const jvalue *args);

    void (*CallVoidMethod)
      (JNIEnv *env, jobject obj, jmethodID methodID, ...);
    void (*CallVoidMethodV)
      (JNIEnv *env, jobject obj, jmethodID methodID, va_list args);
    void (*CallVoidMethodA)
      (JNIEnv *env, jobject obj, jmethodID methodID, const jvalue * args);

    jobject (*CallNonvirtualObjectMethod)
      (JNIEnv *env, jobject obj, jclass clazz, jmethodID methodID, ...);
    jobject (*CallNonvirtualObjectMethodV)
      (JNIEnv *env, jobject obj, jclass clazz, jmethodID methodID,
       va_list args);
    jobject (*CallNonvirtualObjectMethodA)
      (JNIEnv *env, jobject obj, jclass clazz, jmethodID methodID,
       const jvalue * args);

    jboolean (*CallNonvirtualBooleanMethod)
      (JNIEnv *env, jobject obj, jclass clazz, jmethodID methodID, ...);
    jboolean (*CallNonvirtualBooleanMethodV)
      (JNIEnv *env, jobject obj, jclass clazz, jmethodID methodID,
       va_list args);
    jboolean (*CallNonvirtualBooleanMethodA)
      (JNIEnv *env, jobject obj, jclass clazz, jmethodID methodID,
       const jvalue * args);

    jbyte (*CallNonvirtualByteMethod)
      (JNIEnv *env, jobject obj, jclass clazz, jmethodID methodID, ...);
    jbyte (*CallNonvirtualByteMethodV)
      (JNIEnv *env, jobject obj, jclass clazz, jmethodID methodID,
       va_list args);
    jbyte (*CallNonvirtualByteMethodA)
      (JNIEnv *env, jobject obj, jclass clazz, jmethodID methodID,
       const jvalue *args);

    jchar (*CallNonvirtualCharMethod)
      (JNIEnv *env, jobject obj, jclass clazz, jmethodID methodID, ...);
    jchar (*CallNonvirtualCharMethodV)
      (JNIEnv *env, jobject obj, jclass clazz, jmethodID methodID,
       va_list args);
    jchar (*CallNonvirtualCharMethodA)
      (JNIEnv *env, jobject obj, jclass clazz, jmethodID methodID,
       const jvalue *args);

    jshort (*CallNonvirtualShortMethod)
      (JNIEnv *env, jobject obj, jclass clazz, jmethodID methodID, ...);
    jshort (*CallNonvirtualShortMethodV)
      (JNIEnv *env, jobject obj, jclass clazz, jmethodID methodID,
       va_list args);
    jshort (*CallNonvirtualShortMethodA)
      (JNIEnv *env, jobject obj, jclass clazz, jmethodID methodID,
       const jvalue *args);

    jint (*CallNonvirtualIntMethod)
      (JNIEnv *env, jobject obj, jclass clazz, jmethodID methodID, ...);
    jint (*CallNonvirtualIntMethodV)
      (JNIEnv *env, jobject obj, jclass clazz, jmethodID methodID,
       va_list args);
    jint (*CallNonvirtualIntMethodA)
      (JNIEnv *env, jobject obj, jclass clazz, jmethodID methodID,
       const jvalue *args);

    jlong (*CallNonvirtualLongMethod)
      (JNIEnv *env, jobject obj, jclass clazz, jmethodID methodID, ...);
    jlong (*CallNonvirtualLongMethodV)
      (JNIEnv *env, jobject obj, jclass clazz, jmethodID methodID,
       va_list args);
    jlong (*CallNonvirtualLongMethodA)
      (JNIEnv *env, jobject obj, jclass clazz, jmethodID methodID,
       const jvalue *args);

    jfloat (*CallNonvirtualFloatMethod)
      (JNIEnv *env, jobject obj, jclass clazz, jmethodID methodID, ...);
    jfloat (*CallNonvirtualFloatMethodV)
      (JNIEnv *env, jobject obj, jclass clazz, jmethodID methodID,
       va_list args);
    jfloat (*CallNonvirtualFloatMethodA)
      (JNIEnv *env, jobject obj, jclass clazz, jmethodID methodID,
       const jvalue *args);

    jdouble (*CallNonvirtualDoubleMethod)
      (JNIEnv *env, jobject obj, jclass clazz, jmethodID methodID, ...);
    jdouble (*CallNonvirtualDoubleMethodV)
      (JNIEnv *env, jobject obj, jclass clazz, jmethodID methodID,
       va_list args);
    jdouble (*CallNonvirtualDoubleMethodA)
      (JNIEnv *env, jobject obj, jclass clazz, jmethodID methodID,
       const jvalue *args);

    void (*CallNonvirtualVoidMethod)
      (JNIEnv *env, jobject obj, jclass clazz, jmethodID methodID, ...);
    void (*CallNonvirtualVoidMethodV)
      (JNIEnv *env, jobject obj, jclass clazz, jmethodID methodID,
       va_list args);
    void (*CallNonvirtualVoidMethodA)
      (JNIEnv *env, jobject obj, jclass clazz, jmethodID methodID,
       const jvalue * args);

    jfieldID (*GetFieldID)
      (JNIEnv *env, jclass clazz, const char *name, const char *sig);

    jobject (*GetObjectField)
      (JNIEnv *env, jobject obj, jfieldID fieldID);
    jboolean (*GetBooleanField)
      (JNIEnv *env, jobject obj, jfieldID fieldID);
    jbyte (*GetByteField)
      (JNIEnv *env, jobject obj, jfieldID fieldID);
    jchar (*GetCharField)
      (JNIEnv *env, jobject obj, jfieldID fieldID);
    jshort (*GetShortField)
      (JNIEnv *env, jobject obj, jfieldID fieldID);
    jint (*GetIntField)
      (JNIEnv *env, jobject obj, jfieldID fieldID);
    jlong (*GetLongField)
      (JNIEnv *env, jobject obj, jfieldID fieldID);
    jfloat (*GetFloatField)
      (JNIEnv *env, jobject obj, jfieldID fieldID);
    jdouble (*GetDoubleField)
      (JNIEnv *env, jobject obj, jfieldID fieldID);

    void (*SetObjectField)
      (JNIEnv *env, jobject obj, jfieldID fieldID, jobject val);
    void (*SetBooleanField)
      (JNIEnv *env, jobject obj, jfieldID fieldID, jboolean val);
    void (*SetByteField)
      (JNIEnv *env, jobject obj, jfieldID fieldID, jbyte val);
    void (*SetCharField)
      (JNIEnv *env, jobject obj, jfieldID fieldID, jchar val);
    void (*SetShortField)
      (JNIEnv *env, jobject obj, jfieldID fieldID, jshort val);
    void (*SetIntField)
      (JNIEnv *env, jobject obj, jfieldID fieldID, jint val);
    void (*SetLongField)
      (JNIEnv *env, jobject obj, jfieldID fieldID, jlong val);
    void (*SetFloatField)
      (JNIEnv *env, jobject obj, jfieldID fieldID, jfloat val);
    void (*SetDoubleField)
      (JNIEnv *env, jobject obj, jfieldID fieldID, jdouble val);

    GetStaticMethodID_func_t *GetStaticMethodID;

    jobject (*CallStaticObjectMethod)
      (JNIEnv *env, jclass clazz, jmethodID methodID, ...);
    jobject (*CallStaticObjectMethodV)
      (JNIEnv *env, jclass clazz, jmethodID methodID, va_list args);
    jobject (*CallStaticObjectMethodA)
      (JNIEnv *env, jclass clazz, jmethodID methodID, const jvalue *args);

    jboolean (*CallStaticBooleanMethod)
      (JNIEnv *env, jclass clazz, jmethodID methodID, ...);
    jboolean (*CallStaticBooleanMethodV)
      (JNIEnv *env, jclass clazz, jmethodID methodID, va_list args);
    jboolean (*CallStaticBooleanMethodA)
      (JNIEnv *env, jclass clazz, jmethodID methodID, const jvalue *args);

    jbyte (*CallStaticByteMethod)
      (JNIEnv *env, jclass clazz, jmethodID methodID, ...);
    jbyte (*CallStaticByteMethodV)
      (JNIEnv *env, jclass clazz, jmethodID methodID, va_list args);
    jbyte (*CallStaticByteMethodA)
      (JNIEnv *env, jclass clazz, jmethodID methodID, const jvalue *args);

    jchar (*CallStaticCharMethod)
      (JNIEnv *env, jclass clazz, jmethodID methodID, ...);
    jchar (*CallStaticCharMethodV)
      (JNIEnv *env, jclass clazz, jmethodID methodID, va_list args);
    jchar (*CallStaticCharMethodA)
      (JNIEnv *env, jclass clazz, jmethodID methodID, const jvalue *args);

    jshort (*CallStaticShortMethod)
      (JNIEnv *env, jclass clazz, jmethodID methodID, ...);
    jshort (*CallStaticShortMethodV)
      (JNIEnv *env, jclass clazz, jmethodID methodID, va_list args);
    jshort (*CallStaticShortMethodA)
      (JNIEnv *env, jclass clazz, jmethodID methodID, const jvalue *args);

    jint (*CallStaticIntMethod)
      (JNIEnv *env, jclass clazz, jmethodID methodID, ...);
    jint (*CallStaticIntMethodV)
      (JNIEnv *env, jclass clazz, jmethodID methodID, va_list args);
    jint (*CallStaticIntMethodA)
      (JNIEnv *env, jclass clazz, jmethodID methodID, const jvalue *args);

    jlong (*CallStaticLongMethod)
      (JNIEnv *env, jclass clazz, jmethodID methodID, ...);
    jlong (*CallStaticLongMethodV)
      (JNIEnv *env, jclass clazz, jmethodID methodID, va_list args);
    jlong (*CallStaticLongMethodA)
      (JNIEnv *env, jclass clazz, jmethodID methodID, const jvalue *args);

    jfloat (*CallStaticFloatMethod)
      (JNIEnv *env, jclass clazz, jmethodID methodID, ...);
    jfloat (*CallStaticFloatMethodV)
      (JNIEnv *env, jclass clazz, jmethodID methodID, va_list args);
    jfloat (*CallStaticFloatMethodA)
      (JNIEnv *env, jclass clazz, jmethodID methodID, const jvalue *args);

    jdouble (*CallStaticDoubleMethod)
      (JNIEnv *env, jclass clazz, jmethodID methodID, ...);
    jdouble (*CallStaticDoubleMethodV)
      (JNIEnv *env, jclass clazz, jmethodID methodID, va_list args);
    jdouble (*CallStaticDoubleMethodA)
      (JNIEnv *env, jclass clazz, jmethodID methodID, const jvalue *args);

    void (*CallStaticVoidMethod)
      (JNIEnv *env, jclass cls, jmethodID methodID, ...);
    void (*CallStaticVoidMethodV)
      (JNIEnv *env, jclass cls, jmethodID methodID, va_list args);
    void (*CallStaticVoidMethodA)
      (JNIEnv *env, jclass cls, jmethodID methodID, const jvalue * args);

    jfieldID (*GetStaticFieldID)
      (JNIEnv *env, jclass clazz, const char *name, const char *sig);
    jobject (*GetStaticObjectField)
      (JNIEnv *env, jclass clazz, jfieldID fieldID);
    jboolean (*GetStaticBooleanField)
      (JNIEnv *env, jclass clazz, jfieldID fieldID);
    jbyte (*GetStaticByteField)
      (JNIEnv *env, jclass clazz, jfieldID fieldID);
    jchar (*GetStaticCharField)
      (JNIEnv *env, jclass clazz, jfieldID fieldID);
    jshort (*GetStaticShortField)
      (JNIEnv *env, jclass clazz, jfieldID fieldID);
    jint (*GetStaticIntField)
      (JNIEnv *env, jclass clazz, jfieldID fieldID);
    jlong (*GetStaticLongField)
      (JNIEnv *env, jclass clazz, jfieldID fieldID);
    jfloat (*GetStaticFloatField)
      (JNIEnv *env, jclass clazz, jfieldID fieldID);
    jdouble (*GetStaticDoubleField)
      (JNIEnv *env, jclass clazz, jfieldID fieldID);

    void (*SetStaticObjectField)
      (JNIEnv *env, jclass clazz, jfieldID fieldID, jobject value);
    void (*SetStaticBooleanField)
      (JNIEnv *env, jclass clazz, jfieldID fieldID, jboolean value);
    void (*SetStaticByteField)
      (JNIEnv *env, jclass clazz, jfieldID fieldID, jbyte value);
    void (*SetStaticCharField)
      (JNIEnv *env, jclass clazz, jfieldID fieldID, jchar value);
    void (*SetStaticShortField)
      (JNIEnv *env, jclass clazz, jfieldID fieldID, jshort value);
    void (*SetStaticIntField)
      (JNIEnv *env, jclass clazz, jfieldID fieldID, jint value);
    void (*SetStaticLongField)
      (JNIEnv *env, jclass clazz, jfieldID fieldID, jlong value);
    void (*SetStaticFloatField)
      (JNIEnv *env, jclass clazz, jfieldID fieldID, jfloat value);
    void (*SetStaticDoubleField)
      (JNIEnv *env, jclass clazz, jfieldID fieldID, jdouble value);

    NewString_func_t *NewString;
    jsize (*GetStringLength)
      (JNIEnv *env, jstring str);
    const jchar *(*GetStringChars)
      (JNIEnv *env, jstring str, jboolean *isCopy);
    void (*ReleaseStringChars)
      (JNIEnv *env, jstring str, const jchar *chars);

    NewStringUTF_func_t *NewStringUTF;
    jsize (*GetStringUTFLength)
      (JNIEnv *env, jstring str);
    GetStringUTFChars_func_t *GetStringUTFChars;
    void (*ReleaseStringUTFChars)
      (JNIEnv *env, jstring str, const char* chars);


    jsize (*GetArrayLength)
      (JNIEnv *env, jarray array);

    jobjectArray (*NewObjectArray)
      (JNIEnv *env, jsize len, jclass clazz, jobject init);
    jobject (*GetObjectArrayElement)
      (JNIEnv *env, jobjectArray array, jsize index);
    void (*SetObjectArrayElement)
      (JNIEnv *env, jobjectArray array, jsize index, jobject val);

    jbooleanArray (*NewBooleanArray)
      (JNIEnv *env, jsize len);
    jbyteArray (*NewByteArray)
      (JNIEnv *env, jsize len);
    jcharArray (*NewCharArray)
      (JNIEnv *env, jsize len);
    jshortArray (*NewShortArray)
      (JNIEnv *env, jsize len);
    jintArray (*NewIntArray)
      (JNIEnv *env, jsize len);
    jlongArray (*NewLongArray)
      (JNIEnv *env, jsize len);
    jfloatArray (*NewFloatArray)
      (JNIEnv *env, jsize len);
    jdoubleArray (*NewDoubleArray)
      (JNIEnv *env, jsize len);

    jboolean * (*GetBooleanArrayElements)
      (JNIEnv *env, jbooleanArray array, jboolean *isCopy);
    jbyte * (*GetByteArrayElements)
      (JNIEnv *env, jbyteArray array, jboolean *isCopy);
    jchar * (*GetCharArrayElements)
      (JNIEnv *env, jcharArray array, jboolean *isCopy);
    jshort * (*GetShortArrayElements)
      (JNIEnv *env, jshortArray array, jboolean *isCopy);
    jint * (*GetIntArrayElements)
      (JNIEnv *env, jintArray array, jboolean *isCopy);
    jlong * (*GetLongArrayElements)
      (JNIEnv *env, jlongArray array, jboolean *isCopy);
    jfloat * (*GetFloatArrayElements)
      (JNIEnv *env, jfloatArray array, jboolean *isCopy);
    jdouble * (*GetDoubleArrayElements)
      (JNIEnv *env, jdoubleArray array, jboolean *isCopy);

    void (*ReleaseBooleanArrayElements)
      (JNIEnv *env, jbooleanArray array, jboolean *elems, jint mode);
    void (*ReleaseByteArrayElements)
      (JNIEnv *env, jbyteArray array, jbyte *elems, jint mode);
    void (*ReleaseCharArrayElements)
      (JNIEnv *env, jcharArray array, jchar *elems, jint mode);
    void (*ReleaseShortArrayElements)
      (JNIEnv *env, jshortArray array, jshort *elems, jint mode);
    void (*ReleaseIntArrayElements)
      (JNIEnv *env, jintArray array, jint *elems, jint mode);
    void (*ReleaseLongArrayElements)
      (JNIEnv *env, jlongArray array, jlong *elems, jint mode);
    void (*ReleaseFloatArrayElements)
      (JNIEnv *env, jfloatArray array, jfloat *elems, jint mode);
    void (*ReleaseDoubleArrayElements)
      (JNIEnv *env, jdoubleArray array, jdouble *elems, jint mode);

    void (*GetBooleanArrayRegion)
      (JNIEnv *env, jbooleanArray array, jsize start, jsize l, jboolean *buf);
    void (*GetByteArrayRegion)
      (JNIEnv *env, jbyteArray array, jsize start, jsize len, jbyte *buf);
    void (*GetCharArrayRegion)
      (JNIEnv *env, jcharArray array, jsize start, jsize len, jchar *buf);
    void (*GetShortArrayRegion)
      (JNIEnv *env, jshortArray array, jsize start, jsize len, jshort *buf);
    void (*GetIntArrayRegion)
      (JNIEnv *env, jintArray array, jsize start, jsize len, jint *buf);
    void (*GetLongArrayRegion)
      (JNIEnv *env, jlongArray array, jsize start, jsize len, jlong *buf);
    void (*GetFloatArrayRegion)
      (JNIEnv *env, jfloatArray array, jsize start, jsize len, jfloat *buf);
    void (*GetDoubleArrayRegion)
      (JNIEnv *env, jdoubleArray array, jsize start, jsize len, jdouble *buf);

    void (*SetBooleanArrayRegion)
      (JNIEnv *env, jbooleanArray array, jsize start, jsize l, const jboolean *buf);
    void (*SetByteArrayRegion)
      (JNIEnv *env, jbyteArray array, jsize start, jsize len, const jbyte *buf);
    void (*SetCharArrayRegion)
      (JNIEnv *env, jcharArray array, jsize start, jsize len, const jchar *buf);
    void (*SetShortArrayRegion)
      (JNIEnv *env, jshortArray array, jsize start, jsize len, const jshort *buf);
    void (*SetIntArrayRegion)
      (JNIEnv *env, jintArray array, jsize start, jsize len, const jint *buf);
    void (*SetLongArrayRegion)
      (JNIEnv *env, jlongArray array, jsize start, jsize len, const jlong *buf);
    void (*SetFloatArrayRegion)
      (JNIEnv *env, jfloatArray array, jsize start, jsize len, const jfloat *buf);
    void (*SetDoubleArrayRegion)
      (JNIEnv *env, jdoubleArray array, jsize start, jsize len, const jdouble *buf);

    jint (*RegisterNatives)
      (JNIEnv *env, jclass clazz, const JNINativeMethod *methods,
       jint nMethods);
    jint (*UnregisterNatives)
      (JNIEnv *env, jclass clazz);

    jint (*MonitorEnter)
      (JNIEnv *env, jobject obj);
    jint (*MonitorExit)
      (JNIEnv *env, jobject obj);

    jint (*GetJavaVM)
      (JNIEnv *env, JavaVM **vm);

    void (*GetStringRegion)
      (JNIEnv *env, jstring str, jsize start, jsize len, jchar *buf);
    void (*GetStringUTFRegion)
      (JNIEnv *env, jstring str, jsize start, jsize len, char *buf);

    void * (*GetPrimitiveArrayCritical)
      (JNIEnv *env, jarray array, jboolean *isCopy);
    void (*ReleasePrimitiveArrayCritical)
      (JNIEnv *env, jarray array, void *carray, jint mode);

    const jchar * (*GetStringCritical)
      (JNIEnv *env, jstring string, jboolean *isCopy);
    void (*ReleaseStringCritical)
      (JNIEnv *env, jstring string, const jchar *cstring);

    jweak (*NewWeakGlobalRef)
       (JNIEnv *env, jobject obj);
    void (*DeleteWeakGlobalRef)
       (JNIEnv *env, jweak ref);

    jboolean (*ExceptionCheck)
       (JNIEnv *env);

    jobject (*NewDirectByteBuffer)
       (JNIEnv* env, void* address, jlong capacity);
    void* (*GetDirectBufferAddress)
       (JNIEnv* env, jobject buf);
    jlong (*GetDirectBufferCapacity)
       (JNIEnv* env, jobject buf);

    /* New JNI 1.6 Features */

    jobjectRefType (*GetObjectRefType)
        (JNIEnv* env, jobject obj);
};

jint JNI_CreateJavaVM(JavaVM **pvm, void **penv, void *args);