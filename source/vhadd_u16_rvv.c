// Copyright 2024 10xEngineers

#include "rhal_base.h"

/**
 * @brief Performs an element-wise halving addition of two 16-bit unsigned integer vectors.
 * 
 * This function performs an element-wise addition of two 16-bit unsigned integer vectors (`a` and `b`),
 * each containing four elements, and then halves the result by shifting the sum of each pair of elements 
 * to the right by 1 bit. It utilizes the RISC-V Vector Extension to carry out the operation, making it 
 * analogous to the ARM Neon function `vhadd_u16`. The result is a new vector where each element is 
 * the halved sum of the corresponding elements in the input vectors, with the result stored as 
 * 16-bit unsigned integers.
 * 
 * @param a The first input vector of type uint16x4_t containing 16-bit unsigned integers.
 * @param b The second input vector of type uint16x4_t containing 16-bit unsigned integers.
 * @return uint16x4_t The result of the halving addition, returned as an 16-bit unsigned integer vector.
 */
uint16x4_t vhadd_u16_rvv(uint16x4_t a, uint16x4_t b) {
    return __riscv_vnsrl_wx_u16m1( __riscv_vwaddu_vv_u32m2(a, b, VLEN_4), 1, VLEN_4);
}