// Copyright 2024 10xEngineers

#include "common_utilities.h"

#if defined(ARM_NEON)
    #include <arm_neon.h>
#elif defined(RISCV_VECTOR)
    #include "rhal_base.h"
#else
    #error "Unsupported architecture. Please define either ARM_NEON or RISCV_VECTOR."
#endif

// Function to run test cases with a given vect_sub
void run_test_cases(void (*vect_sub)(int16_t*, int8_t*, int, int16_t*)) {
    int16_t test_cases[][8] = {
        {1, 2, 3, 4, 5, 6, 7, 8},                   // Regular positive numbers
        {0, 0, 0, 0, 0, 0, 0, 0},                   // All zeros
        {-1, -2, -3, -4, -5, -6, -7, -8},           // Negative numbers
        {32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767},   // Maximum int16_t value
        {-32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768},   // Minimum int16_t value
        {32767, -32768, 32767, -32768, 32767, -32768, 32767, -32768},   // Max and Min int16_t values
        {5000, -5000, 10000, -10000, 2500, -2500, 7500, -7500},     // Mixed positive and negative numbers
        {1, 1, 1, 1, 1, 1, 1, 1}                    // All ones
    };

    int num_tests = sizeof(test_cases) / sizeof(test_cases[0]);

    for (int i = 0; i < num_tests; i++) {
        int16_t *a = test_cases[i];
        int8_t b[8] = {127, -128, 1, -1, 50, -50, 100, -100};
        int16_t result[8];

        vect_sub(a, b, 8, result);
        print_results(result, 8, INT16);
    }
}

#if defined(ARM_NEON)
// ARM Neon-specific implementation
void vsubw_s8_neon(int16_t *a, int8_t *b, int size, int16_t *result) {
    int16x8_t x = vld1q_s16(a);
    int8x8_t y = vld1_s8(b);
    int16x8_t z = vsubw_s8(x, y);
    vst1q_s16(result, z);
}
// Function to run tests using ARM Neon instructions/intrinsics
void run_tests_neon() {
    run_test_cases(vsubw_s8_neon);
}

#elif defined(RISCV_VECTOR)
// RISC-V Vector-specific implementation
void vsubw_s8_rvvector(int16_t *a, int8_t *b, int size, int16_t *result) {
    int16x8_t x = __riscv_vle16_v_i16m1(a, size);
    int8x8_t y = __riscv_vle8_v_i8m1(b, size);
    int16x8_t z = vsubw_s8_rvv(x, y);
    __riscv_vse16_v_i16m1(result, z, size);
}
// Function to run tests using RISC-V Vector instructions/intrinsics
void run_tests_rvv() {
    run_test_cases(vsubw_s8_rvvector);
}
#endif

int main() {
    #if defined(RISCV_VECTOR)
        run_tests_rvv();
    #elif defined(ARM_NEON)
        run_tests_neon();
    #else
        #error "Unsupported architecture. Please define either ARM_NEON or RISCV_VECTOR."
    #endif
    return 0;
}
