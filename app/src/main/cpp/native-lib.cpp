#include <jni.h>
#include <string>

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_estyle_myapplication321c_MainActivity_stringFromJNI(
    JNIEnv *env,
    jobject /* this */) {
  std::string hello = "Hello from C++";
  return env->NewStringUTF(hello.c_str());
}

// c调用java，调jar和aar相同
extern "C" JNIEXPORT jstring
Java_com_example_estyle_myapplication321c_MainActivity_callMyClassFromJava(
    JNIEnv *env,
    jobject) {

  jclass clazz = env->FindClass("com/example/estyle/myapplication321c/MyClass1");
  jstring hello;
  jint plus;

  jmethodID helloMethod =
      env->GetStaticMethodID(clazz, "hello", "(Ljava/lang/String;)Ljava/lang/String;");
  hello = (jstring) env->CallStaticObjectMethod(clazz, helloMethod, env->NewStringUTF("dnf"));

  jmethodID myClassInit = env->GetMethodID(clazz, "<init>", "()V");
  jobject myClass = env->NewObject(clazz, myClassInit);
  jmethodID plusMethod = env->GetMethodID(clazz, "plus", "(II)I");
  plus = env->CallIntMethod(myClass, plusMethod, 1, 2);

  return hello;
}

// 操作jobject
extern "C" JNIEXPORT jobjectArray
Java_com_example_estyle_myapplication321c_MainActivity_createUsers(
    JNIEnv *env,
    jobject obj,
    jobject user) {

  jclass userClass = env->GetObjectClass(user);
  jmethodID userInit = env->GetMethodID(userClass, "<init>", "()V");
  jfieldID ageField = env->GetFieldID(userClass, "age", "I");
  jfieldID genderField = env->GetFieldID(userClass, "gender", "Z");
  jfieldID nameField = env->GetFieldID(userClass, "name", "Ljava/lang/String;");

  jint age = env->GetIntField(user, ageField);
  jboolean gender = env->GetBooleanField(user, genderField);
  auto name = (jstring) env->GetObjectField(user, nameField);

  jobject newUser = env->NewObject(userClass, userInit);
  env->SetIntField(newUser, ageField, age + 1);
  env->SetBooleanField(newUser, genderField, static_cast<jboolean>(!gender));
  env->SetObjectField(newUser, nameField, name);

  jsize userSize = 5;
  jobjectArray users = env->NewObjectArray(userSize, userClass, nullptr);
  for (int i = 0; i < userSize; ++i) {
    if (i < userSize - 1) {
      jobject user = env->NewObject(userClass, userInit);
      env->SetIntField(user, ageField, i);
      env->SetBooleanField(user, genderField, gender);
      env->SetObjectField(user, nameField, name);

      env->SetObjectArrayElement(users, i, user);
    } else {
      env->SetObjectArrayElement(users, i, newUser);
    }
  }

  return users;
}

// 启动Activity
extern "C" JNIEXPORT void
Java_com_example_estyle_myapplication321c_MainActivity_nativeStartActivity(
    JNIEnv *env,
    jobject activity,
    jclass clazz) {

  jclass intentClass = env->FindClass("android/content/Intent");
  jmethodID intentInit =
      env->GetMethodID(intentClass, "<init>", "(Landroid/content/Context;Ljava/lang/Class;)V");
  jobject intent = env->NewObject(intentClass, intentInit, activity, clazz);

  jclass activityClass = env->FindClass("android/app/Activity");
  jmethodID startActivityMethod =
      env->GetMethodID(activityClass, "startActivity", "(Landroid/content/Intent;)V");

  env->CallNonvirtualVoidMethod(activity, activityClass, startActivityMethod, intent);
}