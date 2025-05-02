// Copyright (c) 2025-present Dinh Son Hai

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef MERCURY_OBJECT_HEADER_FILE
#define MERCURY_OBJECT_HEADER_FILE

#include "C:\MercuryLang\Mercury\type.cpp"
#include "C:\MercuryLang\Mercury\global.cpp"

typedef struct _pcode mCode_T;
typedef struct _code mOpCode_T;
typedef struct _type mType_T;
typedef struct _object mObject_T;
typedef vector<__global *> __global_table;
typedef __global_table GlobalTable;

mObject_T *_MerObject_init(
    mType_T *_Type = NULL_TYPE_PTR,
    mType_T *_Value = NULL_TYPE_PTR,
    mType_T *_File = NULL_TYPE_PTR,
    mType_T *_Name = NULL_TYPE_PTR,
    mCode_T *_Code = NULL_CODE_PTR
);

#endif // MERCURY_OBJECT_HEADER_FILE