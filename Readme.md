# DSP-PLAYGROUND

A stand-alone application and framework for audio effects.
This was created in conjunction with a dedicated [Bluetooth A2DP Receiver](https://github.com/playduck/esp32-bluetooth-dsp).

The code can be embedded into an esp-idf project as a submodule/component or used by itself when compiled as a library.

## Python

Compiling the project via `make all` generates the `./bin/main` library (or dll on windows).

**NOTE: You must create `./obj` and `./bin` directories prior to running make.**

Enabeling the python test script requires python 3.
Generate a virtual enviornment:

- `python -m venv ./venv`
- `source ./venv/bin/activate` (or equivealent depedning on shell)

Install dependencies:

- `pip install -r requirements.txt`

Compile and run python script:

- `make all; python main.py`

This will call [`main.c:process()`](./src/main.c#L7) with all samples in a stereo audio file.
The test files, by default, should be `.wav`, 16 bit stereo. Located at `./data` and named `test{number}.wav`. (This can be changed in the python script.)
This will generate and save a new, modified, version of the file with a `-f` suffix.

## DSP

Every sample is processed by a fixed pipeline located in [`pipeline.c`](./src/pipeline.c).
Input and Outputs are to be 16-bit words.
The processing is done in 32-Bit IEE754 floating point.

Currently available processes include:
- biquad
- dynamic range compressor
- dynamic range gate
- delay
- gain
- virtual / psycoacustic bass enhancement

## TODO

- more docs
- noise shaping
