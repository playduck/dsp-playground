#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "pipeline.h"


uint16_t process(int16_t* s, int16_t len, uint16_t samplerate) {
    initilize(samplerate);

    for(uint16_t i = 0; i < len; i++)   {
        process_sample(
            s +     2*i,
            s + 1 + 2*i
        );
    }

    return 0;
}
