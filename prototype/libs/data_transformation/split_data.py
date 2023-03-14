import zipfile
import json

REFERENCE_PERIOD = 8e-6
ANT_PERIOD = 4e-6

def split_by_windows(data_arr, ant_arr):
    windows = {
        '1': [],
        '2': []
    }

    while len(ant_arr) > 0:
        value, win_len = get_window_len(ant_arr)

        windows[f'{value}'].append(data_arr[:win_len])
        ant_arr = ant_arr[win_len:]
        data_arr = data_arr[win_len:]

    return windows
    

def get_window_len(ant_arr):
    window_val = abs(ant_arr[0])

    counter = 0
    for value in ant_arr:
        if abs(value) != window_val:
            break
        counter += 1

    return window_val, counter


def split_by_ant(data, ant_switch):
    err = None
    data_separated = {
        '1':[],
        '2':[]
    }

    if len(data) != len(ant_switch):
        err = 'Input arrays need to be equal length'
        return err, {}

    for idx, val in enumerate(data):
        if abs(ant_switch[idx]) == 1:
            data_separated['1'].append(val)
            data_separated['2'].append(None)

        elif abs(ant_switch[idx]) == 2:
            if ant_switch[idx] == 0:
                data_separated['1'].append(None)
                data_separated['2'].append(None)
                continue
            data_separated['1'].append(None)
            data_separated['2'].append(val)

        else:
            err = 'Invalid data'
            return err, {}

    return err, data_separated

def generate_ttyy_axs(data_arr, ant_arr):
    tt = []
    yy = []

    for idx, val in enumerate(data_arr):
        if val != None:
            tt.append(idx * get_sampling_r(ant_arr))
            yy.append(val)

    return tt, yy


#count reference period and first ant sample period
#8us + 4us
def get_sampling_r(ant_arr):
    sample_count = 0

    for val in ant_arr:
        if val != 1:
            break
        sample_count += 1

    return (REFERENCE_PERIOD + ANT_PERIOD)/sample_count

def get_sampling_f(ant_arr):
    return 1/get_sampling_r(ant_arr)

def time_len(ant_arr):
    return len(ant_arr) * get_sampling_r(ant_arr)


if __name__ == "__main__":
        data_file = zipfile.ZipFile('./data/data.zip', 'r')
        data = json.load(data_file.open('1661426400[8]-ant121-skifiloc-ang170-iq.json', 'r'))


        # err, data_separated = split_by_ant(data['i'], data['ant'])

        # if err is None:
        #     print(data_separated)
        # else:
        #     print(err)



        print(split_by_windows(data['i'], data['ant']))
