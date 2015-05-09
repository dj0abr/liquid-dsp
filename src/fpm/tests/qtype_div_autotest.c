/*
 * Copyright (c) 2007 - 2015 Joseph Gaeddert
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <stdio.h>
#include <math.h>

#include "autotest/autotest.h"
#include "liquidfpm.internal.h"

// API definition macro; helper function to keep code base small
#define LIQUIDFPM_AUTOTEST_DIV_API(Q)                               \
void Q(_test_div)(float _xf,                                        \
                  float _yf,                                        \
                  float _tol)                                       \
{                                                                   \
    /* convert to fixed-point */                                    \
    Q(_t) x = Q(_float_to_fixed)(_xf);                              \
    Q(_t) y = Q(_float_to_fixed)(_yf);                              \
                                                                    \
    /* execute operation */                                         \
    Q(_t) z = Q(_div)(x,y);                                         \
    float zf = _xf / _yf;                                           \
                                                                    \
    /* convert to floating-point */                                 \
    float ztest = Q(_fixed_to_float)(z);                            \
                                                                    \
    /* run comparison */                                            \
    CONTEND_DELTA(zf,ztest,_tol);                                   \
                                                                    \
    if (liquid_autotest_verbose) {                                  \
        printf("%12.8f / %12.8f = %12.8f (%12.8f)\n",               \
                _xf,     _yf,     ztest,  zf);                      \
    }                                                               \
}

// define autotest API
LIQUIDFPM_AUTOTEST_DIV_API(LIQUIDFPM_MANGLE_Q32)
LIQUIDFPM_AUTOTEST_DIV_API(LIQUIDFPM_MANGLE_Q16)

void autotest_q16_div()
{
    float tol = q16_fixed_to_float(1<<q16_intbits);

    // basic tests
    q16_test_div( 0.25f, 2.25f, tol);
    q16_test_div( 0.25f,-2.25f, tol);
}

void autotest_q32_div()
{
    float tol = q32_fixed_to_float(1<<q32_intbits);

    // basic tests
    q32_test_div( 0.25f, 2.25f, tol);
    q32_test_div( 0.25f,-2.25f, tol);
}

