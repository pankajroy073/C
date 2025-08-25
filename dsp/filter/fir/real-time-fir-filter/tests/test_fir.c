#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "fir.h"

static int nearly_equal(float a, float b, float eps) {
    float diff = fabsf(a - b);
    float norm = fmaxf(1.0f, fmaxf(fabsf(a), fabsf(b)));
    return diff <= eps * norm;
}

int main(void)
{
    /* Small test taps */
    float h[] = {0.25f, 0.5f, 0.25f};
    size_t N = sizeof(h)/sizeof(h[0]);
    FIR f;
    if (fir_init(&f, h, N) != 0) {
        fprintf(stderr, "fir_init failed\n");
        return 1;
    }

    /* Impulse response should equal h[k] in order */
    float y;
    y = fir_process(&f, 1.0f);
    if (!nearly_equal(y, h[0], 1e-6f)) { fprintf(stderr, "impulse[0]\n"); return 1; }
    for (size_t i = 1; i < N; ++i) {
        y = fir_process(&f, 0.0f);
        if (!nearly_equal(y, h[i], 1e-6f)) { fprintf(stderr, "impulse[%zu]\n", i); return 1; }
    }

    /* Compare block processing to reference convolution */
    const size_t L = 64;
    float in[L], out[L], ref[L];
    for (size_t i = 0; i < L; ++i) in[i] = (float)(i % 7) - 3.0f;

    /* Reference streaming convolution matching our coefficient order */
    FIR g;
    fir_init(&g, h, N);
    for (size_t i = 0; i < L; ++i) {
        ref[i] = fir_process(&g, in[i]);
    }
    fir_free(&g);

    fir_process_block(&f, in, out, L);

    for (size_t i = 0; i < L; ++i) {
        if (!nearly_equal(out[i], ref[i], 1e-6f)) {
            fprintf(stderr, "block mismatch at %zu (out=%f ref=%f)\n", i, out[i], ref[i]);
            return 1;
        }
    }

    fir_free(&f);
    return 0;
}
