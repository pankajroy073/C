#include <stdio.h>
#include <stdlib.h>
#include "fir.h"

int main(void)
{
    /* Example: 16-tap Hamming LPF prototype (replace with your own) */
    float h[] = {
        -0.001050f, -0.002694f, -0.006374f, -0.010329f,
        -0.011355f, -0.006155f,  0.006340f,  0.023231f,
         0.038245f,  0.044558f,  0.038134f,  0.020218f,
        -0.003878f, -0.027487f, -0.039414f, -0.032215f
    };

    FIR f;
    if (fir_init(&f, h, sizeof(h)/sizeof(h[0])) != 0) {
        fprintf(stderr, "FIR init failed\n");
        return 1;
    }

    float x;
    while (fread(&x, sizeof(float), 1, stdin) == 1) {
        float y = fir_process(&f, x);
        fwrite(&y, sizeof(float), 1, stdout);
    }

    fir_free(&f);
    return 0;
}
