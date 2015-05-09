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
// Fixed-point dot product
//

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "liquid.h"

// portable structured dot product object
struct dotprod_crcq16_s {
    q16_t * h;          // coefficients array
    unsigned int n;     // length
};

// basic dot product
//  _h      :   coefficients array [size: 1 x _n]
//  _x      :   input array [size: 1 x _n]
//  _n      :   input lengths
//  _y      :   output dot product
void dotprod_crcq16_run(q16_t *      _h,
                        cq16_t *     _x,
                        unsigned int _n,
                        cq16_t *     _y)
{
    // initialize accumulators (separate I/Q)
    q16_at ri = 0;
    q16_at rq = 0;

    unsigned int i;
    for (i=0; i<_n; i++) {
        ri += (q16_at)_h[i] * (q16_at)(_x[i].real);
        rq += (q16_at)_h[i] * (q16_at)(_x[i].imag);
    }

    // return result
    (*_y).real = (ri >> q16_fracbits);
    (*_y).imag = (rq >> q16_fracbits);
}

// basic dotproduct, unrolling loop
//  _h      :   coefficients array [size: 1 x _n]
//  _x      :   input array [size: 1 x _n]
//  _n      :   input lengths
//  _y      :   output dot product
void dotprod_crcq16_run4(q16_t *      _h,
                         cq16_t *     _x,
                         unsigned int _n,
                         cq16_t *     _y)
{
    // initialize accumulator (separate I/Q)
    q16_at ri = 0;
    q16_at rq = 0;

    // t = 4*(floor(_n/4))
    unsigned int t=(_n>>2)<<2; 

    // compute dotprod in groups of 4
    unsigned int i;
    for (i=0; i<t; i+=4) {
        // real component
        ri += (q16_at)_h[i  ] * (q16_at)(_x[i  ].real);
        ri += (q16_at)_h[i+1] * (q16_at)(_x[i+1].real);
        ri += (q16_at)_h[i+2] * (q16_at)(_x[i+2].real);
        ri += (q16_at)_h[i+3] * (q16_at)(_x[i+3].real);

        // imaginary component
        rq += (q16_at)_h[i  ] * (q16_at)(_x[i  ].imag);
        rq += (q16_at)_h[i+1] * (q16_at)(_x[i+1].imag);
        rq += (q16_at)_h[i+2] * (q16_at)(_x[i+2].imag);
        rq += (q16_at)_h[i+3] * (q16_at)(_x[i+3].imag);
    }

    // clean up remaining
    for ( ; i<_n; i++) {
        ri += (q16_at)_h[i] * (q16_at)(_x[i].real);
        rq += (q16_at)_h[i] * (q16_at)(_x[i].imag);
    }

    // return result
    (*_y).real = (ri >> q16_fracbits);
    (*_y).imag = (rq >> q16_fracbits);
}

//
// structured dot product
//

// create structured dot product object
//  _h      :   coefficients array [size: 1 x _n]
//  _n      :   dot product length
dotprod_crcq16 dotprod_crcq16_create(q16_t * _h,
                                     unsigned int _n)
{
    dotprod_crcq16 q = (dotprod_crcq16) malloc(sizeof(struct dotprod_crcq16_s));
    q->n = _n;

    // allocate memory for coefficients
    q->h = (q16_t*) malloc((q->n)*sizeof(q16_t));

    // move coefficients
    memmove(q->h, _h, (q->n)*sizeof(q16_t));

    // return object
    return q;
}

// re-create dot product object
//  _q      :   old dot dot product object
//  _h      :   new coefficients [size: 1 x _n]
//  _n      :   new dot product size
dotprod_crcq16 dotprod_crcq16_recreate(dotprod_crcq16 _q,
                                       q16_t *        _h,
                                       unsigned int   _n)
{
    // check to see if length has changed
    if (_q->n != _n) {
        // set new length
        _q->n = _n;

        // re-allocate memory
        _q->h = (q16_t*) realloc(_q->h, (_q->n)*sizeof(q16_t));
    }

    // move new coefficients
    memmove(_q->h, _h, (_q->n)*sizeof(q16_t));

    // return re-structured object
    return _q;
}

// destroy dot product object
void dotprod_crcq16_destroy(dotprod_crcq16 _q)
{
    free(_q->h);    // free coefficients memory
    free(_q);       // free main object memory
}

// print dot product object
void dotprod_crcq16_print(dotprod_crcq16 _q)
{
    printf("dotprod [%u elements]:\n", _q->n);
    unsigned int i;
    for (i=0; i<_q->n; i++)
        printf("  %4u: %12.8f\n", i, q16_fixed_to_float(_q->h[i]));
}

// execute structured dot product
//  _q      :   dot product object
//  _x      :   input array [size: 1 x _n]
//  _y      :   output dot product
void dotprod_crcq16_execute(dotprod_crcq16 _q,
                            cq16_t *       _x,
                            cq16_t *       _y)
{
    // run basic dot product with unrolled loops
    dotprod_crcq16_run4(_q->h, _x, _q->n, _y);
}

