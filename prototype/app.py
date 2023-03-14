import json
import numpy as np
import matplotlib.pyplot as plt
import zipfile

with zipfile.ZipFile('./data/data.zip', 'r') as zf:

    data = json.load(
        zf.open('1661426400[0]-ant121-skifiloc-ang170-iq.json', 'r'))
    iq = np.array(data['i']) + 1j*np.array(data['q'])
    ant = np.array(data['ant'])

    print(iq)

    plt.figure()
    plt.plot(np.abs(iq)[:100], '-o', label='magnitude')
    plt.figure()
    plt.plot(np.angle(iq)[:100], 'o', label='phase')
    plt.figure()
    plt.plot(np.where(ant == 1, np.real(iq), np.nan)
             [:100], 'o-C2', label='I ant1')
    plt.plot(np.where(ant == 2, np.real(iq), np.nan)
             [:100], 'o-C4', label='I ant2')
    plt.plot(np.imag(iq)[:100], 'o-', label='Q')
