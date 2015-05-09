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

//
// iirfilt_xxxq16_autotest.c : test fixed-point filters
//

#include "autotest/autotest.h"
#include "liquid.h"

// autotest data definitions
#include "src/filter/tests/iirfilt_autotest.h"

// 
// AUTOTEST: iirfilt_rrrq16 tests
//
void xautotest_iirfilt_rrrq16_h3x64()
{
    iirfilt_rrrq16_test(iirfilt_rrrf_data_h3x64_b,
                        iirfilt_rrrf_data_h3x64_a, 3,
                        iirfilt_rrrf_data_h3x64_x, 64,
                        iirfilt_rrrf_data_h3x64_y, 64);
}
void xautotest_iirfilt_rrrq16_h5x64()
{
    iirfilt_rrrq16_test(iirfilt_rrrf_data_h5x64_b,
                        iirfilt_rrrf_data_h5x64_a, 5,
                        iirfilt_rrrf_data_h5x64_x, 64,
                        iirfilt_rrrf_data_h5x64_y, 64);
}
void xautotest_iirfilt_rrrq16_h7x64()
{
    iirfilt_rrrq16_test(iirfilt_rrrf_data_h7x64_b,
                        iirfilt_rrrf_data_h7x64_a, 7,
                        iirfilt_rrrf_data_h7x64_x, 64,
                        iirfilt_rrrf_data_h7x64_y, 64);
}


// 
// AUTOTEST: iirfilt_crcq16 tests
//
void xautotest_iirfilt_crcq16_h3x64()
{
    iirfilt_crcq16_test(iirfilt_crcf_data_h3x64_b,
                        iirfilt_crcf_data_h3x64_a, 3,
                        iirfilt_crcf_data_h3x64_x, 64,
                        iirfilt_crcf_data_h3x64_y, 64);
}
void xautotest_iirfilt_crcq16_h5x64()
{
    iirfilt_crcq16_test(iirfilt_crcf_data_h5x64_b,
                        iirfilt_crcf_data_h5x64_a, 5,
                        iirfilt_crcf_data_h5x64_x, 64,
                        iirfilt_crcf_data_h5x64_y, 64);
}
void xautotest_iirfilt_crcq16_h7x64()
{
    iirfilt_crcq16_test(iirfilt_crcf_data_h7x64_b,
                        iirfilt_crcf_data_h7x64_a, 7,
                        iirfilt_crcf_data_h7x64_x, 64,
                        iirfilt_crcf_data_h7x64_y, 64);
}


// 
// AUTOTEST: iirfilt_cccq16 tests
//
void xautotest_iirfilt_cccq16_h3x64()
{
    iirfilt_cccq16_test(iirfilt_cccf_data_h3x64_b,
                        iirfilt_cccf_data_h3x64_a, 3,
                        iirfilt_cccf_data_h3x64_x, 64,
                        iirfilt_cccf_data_h3x64_y, 64);
}
void xautotest_iirfilt_cccq16_h5x64()
{
    iirfilt_cccq16_test(iirfilt_cccf_data_h5x64_b,
                        iirfilt_cccf_data_h5x64_a, 5,
                        iirfilt_cccf_data_h5x64_x, 64,
                        iirfilt_cccf_data_h5x64_y, 64);
}
void xautotest_iirfilt_cccq16_h7x64()
{
    iirfilt_cccq16_test(iirfilt_cccf_data_h7x64_b,
                        iirfilt_cccf_data_h7x64_a, 7,
                        iirfilt_cccf_data_h7x64_x, 64,
                        iirfilt_cccf_data_h7x64_y, 64);
}


