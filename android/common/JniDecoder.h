/*
 * Copyright (C) 2020 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include <filament/Engine.h>

#include <backend/PixelBufferDescriptor.h>

#include <jni.h>

class JniDecoder {
public:
    static void Init(JavaVM* vm, const char* decoder_class_name) {}

    static JniDecoder* GetInstance();

    filament::backend::PixelBufferDescriptor getRgba(filament::Engine* engine,
            uint8_t const* sourceBuffer, int sourceLength,
            int* width, int* height);

    bool getInfo(filament::Engine* engine,
            uint8_t const* sourceBuffer, int sourceLength,
            int* width, int* height);

private:
    JavaVM* vm_;
    jobject jni_decoder_java_ref_;
    jclass jni_decoder_java_class_;

    // This class uses singleton pattern and can be invoked from multiple threads,
    // so each method locks the mutex for thread safety.
    mutable pthread_mutex_t mutex_;

    jstring GetExternalFilesDirJString(JNIEnv *env);
    jclass RetrieveClass(JNIEnv *jni, const char* class_name);

    JniDecoder();
    ~JniDecoder();
    JniDecoder(const JniDecoder& rhs);
    JniDecoder& operator=(const JniDecoder& rhs);
};
