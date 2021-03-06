/*
 * Copyright 2012 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */
#include "SkPathOpsPoint.h"
#include "Test.h"

static const SkDPoint tests[] = {
    {0, 0},
    {1, 0},
    {0, 1},
    {2, 1},
    {1, 2},
    {1, 1},
    {2, 2}
};

static const size_t tests_count = sizeof(tests) / sizeof(tests[0]);

static void DVectorTest(skiatest::Reporter* reporter) {
    for (size_t index = 0; index < tests_count - 1; ++index) {
        SkDVector v1 = tests[index + 1] - tests[index];
        SkDVector v2 = tests[index] - tests[index + 1];
        v1 += v2;
        REPORTER_ASSERT(reporter, v1.fX == 0 && v1.fY == 0);
        SkDPoint p = tests[index + 1] + v2;
        REPORTER_ASSERT(reporter, p == tests[index]);
        v2 -= v2;
        REPORTER_ASSERT(reporter, v2.fX == 0 && v2.fY == 0);
        v1 = tests[index + 1] - tests[index];
        v1 /= 2;
        v1 *= 2;
        v1 -= tests[index + 1] - tests[index];
        REPORTER_ASSERT(reporter, v1.fX == 0 && v1.fY == 0);
        SkVector sv = v1.asSkVector();
        REPORTER_ASSERT(reporter, sv.fX == 0 && sv.fY == 0);
        v1 = tests[index + 1] - tests[index];
        double lenSq = v1.lengthSquared();
        double v1Dot = v1.dot(v1);
        REPORTER_ASSERT(reporter, lenSq == v1Dot);
        REPORTER_ASSERT(reporter, approximately_equal(sqrt(lenSq), v1.length()));
        double v1Cross = v1.cross(v1);
        REPORTER_ASSERT(reporter, v1Cross == 0);
    }
}

#include "TestClassDef.h"
DEFINE_TESTCLASS("PathOpsDVector", PathOpsDVectorClass, DVectorTest)
