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

#include "C:\MercuryLang\v2.0.1\mercury\include\type.h"

typedef struct _pcode mCode_T;
typedef struct _type mType_T;
typedef struct _object mObject_T;

static mObject_T NULL_OBJECT_INSTANCE = mObject_T();
static mType_T NULL_TYPE_INSTANCE = mType_T();
static mCode_T NULL_CODE_INSTANCE = mCode_T();

#define NULL_OBJECT NULL_OBJECT_INSTANCE
#define NULL_TYPE NULL_TYPE_INSTANCE
#define NULL_CODE NULL_CODE_INSTANCE

#define NULL_OBJECT_PTR &NULL_OBJECT_INSTANCE
#define NULL_TYPE_PTR &NULL_TYPE_INSTANCE
#define NULL_CODE_PTR &NULL_CODE_INSTANCE

#define NULL_INT 0
#define NULL_FLOAT 0.0
#define NULL_DOUBLE 0.0
#define NULL_LONG 0
#define NULL_BOOL 0
#define NULL_STRING ""

#define NULL_STRING_PTR &NULL_STRING
#define NULL_INT_PTR &NULL_INT
#define NULL_FLOAT_PTR &NULL_FLOAT
#define NULL_DOUBLE_PTR &NULL_DOUBLE
#define NULL_LONG_PTR &NULL_LONG
#define NULL_BOOL_PTR &NULL_BOOL


#endif // MERCURY_OBJECT_HEADER_FILE