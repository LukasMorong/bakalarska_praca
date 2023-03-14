import numpy, scipy.optimize
import math

from libs.data_transformation import split_data
from libs.data_transformation import delta_encoding

def encode_two_sine(data_arr, ant_arr):
    predictor = sine_predictor(data_arr, ant_arr)

    time_len = split_data.time_len(ant_arr)
    sine_values = generate_sine(predictor, time_len)
    encoded = []

    for idx, value in enumerate(data_arr):
        encoded.append(data_arr[idx] - sine_values[idx])

    return encoded, predictor

def encode_one_sine(data_arr, ant_arr):
    predictor = sine_predictor(data_arr, ant_arr)

    time_len = split_data.time_len(ant_arr)
    sine_values = generate_sine(predictor, time_len)
    encoded = []

    for idx, value in enumerate(data_arr):
        encoded.append(data_arr[idx] - sine_values[idx])

    return encoded, predictor

def encode_one_sine_delta(data):
    predictor = sine_predictor(data['i'], data['ant'])

    time_len = split_data.time_len(data['ant'])
    sine_values = generate_sine(predictor, time_len)
    cosine_values = generate_cosine(predictor, time_len)

    encoded_i = []
    last = 0
    for idx, value in enumerate(data['i']):
        if data['ant'][idx] == 1:
            encoded_i.append(value - sine_values[idx])
        else:
            encoded_i.append(0)

        last = value
        
    encoded_q = []
    last = 0
    for idx, value in enumerate(data['q']):
        if data['ant'][idx] == 1:
            encoded_q.append(value - cosine_values[idx])
        else:
            encoded_q.append(value-last)

        last = value

    return encoded_i, encoded_q, predictor

def sine_predictor(data_arr, ant_arr):
    _, data_sep = split_data.split_by_ant(data_arr, ant_arr)
    
    tt1, yy1 = split_data.generate_ttyy_axs(data_sep['1'], ant_arr)

    return fit_sin(tt1, yy1)


def sine_predictor_wf(data_arr, ant_arr, ff):
    _, data_sep = split_data.split_by_ant(data_arr, ant_arr)
    
    tt, yy = split_data.generate_ttyy_axs(data_sep['2'], ant_arr)

    return fit_sin_3p(tt, yy, ff)


def generate_sine(params, time_len):
    amp = params['amp']
    phase = params['phase']
    offset = params['offset']
    freq = params['freq']

    time_axs = numpy.linspace(0, time_len, 625)###change

    return (amp * numpy.sin(2*numpy.pi*freq*time_axs + phase))

def generate_cosine(params, time_len):
    amp = params['amp']
    phase = params['phase']
    offset = params['offset']
    freq = params['freq']

    time_axs = numpy.linspace(0, time_len, 625)###change

    return (amp * numpy.sin(2*numpy.pi*freq*time_axs + phase - numpy.pi/2))


#4 parameter sin-fit
def fit_sin(tt, yy):
    '''Fit sin to the input time sequence, and return fitting parameters "amp", "omega", "phase", "offset", "freq", "period" and "fitfunc"'''
    tt = numpy.array(tt)
    yy = numpy.array(yy)
    ff = numpy.fft.fftfreq(len(tt), (tt[1]-tt[0]))   # assume uniform spacing

    Fyy = abs(numpy.fft.fft(yy))
    guess_freq = abs(ff[numpy.argmax(Fyy[1:])+1])   # excluding the zero frequency "peak", which is related to offset
    guess_amp = numpy.std(yy) * 2.**0.5
    guess_offset = numpy.mean(yy)
    guess = numpy.array([guess_amp, 2.*numpy.pi*guess_freq, 0., guess_offset])

    def sinfunc(t, A, w, p, c):  return A * numpy.sin(w*t + p) + c
    popt, pcov = scipy.optimize.curve_fit(sinfunc, tt, yy, p0=guess)
    A, w, p, c = popt
    f = w/(2.*numpy.pi)
    fitfunc = lambda t: A * numpy.sin(w*t + p) + c
    return {"amp": A, "omega": w, "phase": p, "offset": c, "freq": f, "period": 1./f, "fitfunc": fitfunc, "maxcov": numpy.max(pcov), "rawres": (guess,popt,pcov)}

def fit_sin_3p(tt,yy,freq):
    tt = numpy.array(tt)
    yy = numpy.array(yy)
    ff = numpy.fft.fftfreq(len(tt), (tt[1]-tt[0]))   # assume uniform spacing

    Fyy = abs(numpy.fft.fft(yy))
    guess_freq = abs(ff[numpy.argmax(Fyy[1:])+1])   # excluding the zero frequency "peak", which is related to offset
    guess_amp = numpy.std(yy) * 2.**0.5
    guess_offset = numpy.mean(yy)
    guess = numpy.array([guess_amp, 2.*numpy.pi*freq, 0., guess_offset])

    def sinfunc(t, A, w, p, c):  return A * numpy.sin(w*t + p) + c
    popt, pcov = scipy.optimize.curve_fit(sinfunc, tt, yy, p0=guess)
    A, w, p, c = popt
    f = w/(2.*numpy.pi)
    fitfunc = lambda t: A * numpy.sin(w*t + p) + c
    return {"amp": A, "omega": w, "phase": p, "offset": c, "freq": f, "period": 1./f, "fitfunc": fitfunc, "maxcov": numpy.max(pcov), "rawres": (guess,popt,pcov)}

 #todo least square regression, more effective implementation


 #transition weights function
def weights_fun(nofSamples, position, series=1):
    x = position/(nofSamples - 1)
    w1 = 0

    if series == 1:
        w1 = x
    if series == 2:
        w1 = 1 - math.pow(1 - x, 5)
        

    return w1, 1 - w1


##some sine magic test
def mix_clean(s1, s2, ant_arr):
    result = []

    time_len = split_data.time_len(ant_arr)
    v1 = generate_sine(s1, time_len)
    v2 = generate_sine(s2, time_len)

    from_prev = 0
    last = ant_arr[0]
    transition_len = 8
    use_series = 2

    for idx, ant in enumerate(ant_arr):
        if last != ant and ant < 0:
            from_prev = transition_len

        if abs(ant) == 1:
            if from_prev > 0:
                w1, w2 = weights_fun(transition_len, transition_len - from_prev, series=use_series)
                result.append(w1*v1[idx] + w2*v2[idx])
                from_prev = from_prev - 1
            else:
                result.append(v1[idx])

        else:
            if from_prev > 0:
                w1, w2 = weights_fun(transition_len, transition_len - from_prev, series=use_series)
                result.append(w1*v2[idx] + w2*v1[idx])
                from_prev = from_prev - 1
            else:
                result.append(v2[idx])

        last = ant

    return result

def diff(v1, v2):
    result = []
    for idx, val1 in enumerate(v1):
        if(v2[idx] == None):
            result.append(0)
        else:
            result.append(int(val1 - round(v2[idx])))

    return result


if __name__ == "__main__":
    for x in range(8):
        print(weights_fun(8, x, series=3)[1])