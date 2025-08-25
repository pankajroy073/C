# fir-filter (C)

A tiny, dependency-free, real‑time friendly FIR filter library in C.  
Single-sample streaming API with a circular delay line. Works in ISRs, audio callbacks, or tight polling loops.

## Features
- Streaming, single-sample API: `fir_process(&f, x)` → `y`
- Circular buffer for O(N) MAC with minimal cache misses
- Dynamic tap count (no preprocessor caps)
- Block processing helper
- Clean C API; CMake and Make builds; unit tests; GitHub Actions CI

## Coefficient order
This library assumes **`h[0]` multiplies the newest sample** (Direct-Form I).  
So for an impulse input, the output will be `y[0]=h[0], y[1]=h[1], ...`.

If your design tool exported the opposite order, just reverse your taps.

## Quick start

### Build (CMake)
```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
ctest --test-dir build --output-on-failure
```

### Build (Make)
```bash
make
make test
```

### Use from your project
```c
#include "fir.h"

// Example taps (replace with your own)
float h[] = {0.1f, 0.15f, 0.5f, 0.15f, 0.1f}; // h[0] for newest sample
FIR f;
fir_init(&f, h, sizeof(h)/sizeof(h[0]));

float y = fir_process(&f, 1.0f); // process one sample
fir_free(&f);
```

### Real-time example
A simple stdin→stdout float stream example is in `examples/realtime_stdin.c`.

## API
```c
typedef struct {
    size_t N;         // number of taps
    float *h;         // coeffs (length N)
    float *d;         // delay line (length N)
    size_t idx;       // circular index of newest sample
} FIR;

int   fir_init(FIR *f, const float *h, size_t N);                // allocs and copies taps
void  fir_free(FIR *f);
float fir_process(FIR *f, float x);                              // single-sample
void  fir_process_block(FIR *f, const float *in, float *out, size_t count);
```

## Testing
- `tests/test_fir.c` checks the impulse response and compares against reference convolution.
- Run via `ctest` (CMake) or `make test`.

## License
MIT
