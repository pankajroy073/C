#ifndef FIR_H
#define FIR_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

typedef struct {
    size_t N;     /* number of taps */
    float *h;     /* coefficients h[0]..h[N-1], with h[0] for newest sample */
    float *d;     /* delay line (circular buffer), length N */
    size_t idx;   /* write index (points to newest sample) */
} FIR;

/* Initialize FIR filter state.
   - Copies 'h' into internal memory.
   - Returns 0 on success, -1 on invalid args, -2 on allocation failure. */
int   fir_init(FIR *f, const float *h, size_t N);

/* Free all resources associated with FIR. Safe to call on a zeroed/partially inited struct. */
void  fir_free(FIR *f);

/* Process a single sample. Direct-Form I with circular buffer. */
float fir_process(FIR *f, float x);

/* Process a block of samples using the same internal state. */
void  fir_process_block(FIR *f, const float *in, float *out, size_t count);

#ifdef __cplusplus
}
#endif

#endif /* FIR_H */
