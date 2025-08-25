#include "fir.h"
#include <stdlib.h>

int fir_init(FIR *f, const float *h, size_t N)
{
    if (!f || !h || N == 0) return -1;
    f->N = N;
    f->idx = 0;
    f->h = (float*)malloc(N * sizeof(float));
    f->d = (float*)malloc(N * sizeof(float));
    if (!f->h || !f->d) {
        fir_free(f);
        return -2;
    }
    for (size_t i = 0; i < N; ++i) {
        f->h[i] = h[i];
        f->d[i] = 0.0f;
    }
    return 0;
}

void fir_free(FIR *f)
{
    if (!f) return;
    if (f->h) free(f->h);
    if (f->d) free(f->d);
    f->h = NULL;
    f->d = NULL;
    f->N = 0;
    f->idx = 0;
}

float fir_process(FIR *f, float x)
{
    size_t n = f->N;
    f->d[f->idx] = x;

    float y = 0.0f;
    size_t di = f->idx;
    for (size_t i = 0; i < n; ++i) {
        y += f->h[i] * f->d[di];
        if (di == 0) di = n - 1; else --di;
    }

    f->idx = (f->idx + 1) % n;
    return y;
}

void fir_process_block(FIR *f, const float *in, float *out, size_t count)
{
    for (size_t i = 0; i < count; ++i) {
        out[i] = fir_process(f, in[i]);
    }
}
