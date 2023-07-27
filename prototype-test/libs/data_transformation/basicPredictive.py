slot1size = 32
slot2size = 16
sampleCount = 624

def compress(samples, ant):
    result = []
    slot_ant1 = []
    slot_ant2 = []
    slot2Sampled = False
    
    for idx in range(sampleCount):    
        if abs(ant[idx]) == 1:
            if idx < slot1size:
                slot_ant1.append(samples[idx])
                result.append(samples[idx])
                continue

            result.append(samples[idx] - slot_ant1[idx % slot1size])

        if abs(ant[idx]) == 2:
            if not slot2Sampled:
                slot_ant2.append(samples[idx])
                result.append(samples[idx])
                if idx % slot2size == slot2size - 1:
                    slot2Sampled = True
                continue

            result.append(samples[idx] - slot_ant2[idx % slot2size])
    
    return result

def compressCorrective(samples, ant):
    result = []
    slot_ant1 = [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
    slot_ant2 = [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
    count1 = 0
    count2 = 0
    
    windows1 = []
    windows2 = []
    
    for idx in range(sampleCount): 
        if abs(ant[idx]) == 1:
            count2 = 0

            result.append(samples[idx] - slot_ant1[count1%slot1size])
            slot_ant1[count1%slot1size] = samples[idx]

            count1 = count1 + 1

        if abs(ant[idx]) == 2:
            count1 = 0

            result.append(samples[idx] - slot_ant2[count2%slot2size])
            slot_ant2[count2%slot2size] = samples[idx]

            count2 = count2 + 1

    
    return result


if __name__ == "__main__":
    for x in range(8):
        print(weights_fun(8, x, series=3)[1])