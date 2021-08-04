
import numpy as np
from scipy.io import wavfile
import ctypes
from timeit import default_timer as timer
import matplotlib.pyplot as plt

num = 4
infile = f"./data/test{num}.wav"
outfile = f"./data/out{num}.wav"

fun = ctypes.CDLL("./bin/main.so")

fun.process.argtypes = [ctypes.POINTER(
    ctypes.c_int16), ctypes.c_uint32, ctypes.c_uint16]

samplerate, data = wavfile.read(infile)

data[0][0] = 9
data[0][1] = 123
data[1][0] = 10
data[1][1] = 456

flat = data.flatten("A")
# flat = (flat / (2**32)) * (2**15)
flat = flat.astype(np.int16)
flat_p = flat.ctypes.data_as(ctypes.POINTER(ctypes.c_int16))

len_c = ctypes.c_uint32(len(data))
sample_c = ctypes.c_uint16(samplerate)

start = timer()
returnVale = fun.process(flat_p, len_c, sample_c)
end = timer()
print(f"processed {len(data)} samples in {round((end - start) * 1000, 3)}ms")
print(f"{2 * len(data)} filter, with {round(((end - start) * 1000 * 1000*1000) / (2*len(data)), 3)}ns per filter")

restored = flat.reshape(-1, 2)

wavfile.write(outfile, samplerate, restored)

print(data[:, 0])
print(restored[:, 0])

# plt.figure(1)
# plt.subplot(411)
# plt.specgram(restored[:, 0], Fs=samplerate, scale="dB", cmap="rainbow")
# plt.subplot(412)
# plt.specgram(restored[:, 1], Fs=samplerate, scale="dB", cmap="rainbow")
# plt.subplot(413)
# plt.specgram(data[:, 0], Fs=samplerate, scale="dB", cmap="rainbow")
# plt.subplot(414)
# plt.specgram(data[:, 1], Fs=samplerate, scale="dB", cmap="rainbow")
# plt.show()
