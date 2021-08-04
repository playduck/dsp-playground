#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "pipeline.h"

uint16_t process(int16_t* s, uint32_t len, uint16_t samplerate) {
    initilize(samplerate);

    for(uint32_t i = 0; i < len; i++)   {
        process_sample(CHANNEL_ONE,
            s +     2*i,
            s + 1 + 2*i
        );
    }

    return 0;
}
