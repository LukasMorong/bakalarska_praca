slot1size = 16
slot2size = 16
sapleCount = 624

def encode(samples, ant):
    result = []
    slot_ant1 = []
    slot_ant2 = []
    slot2Sampled = False
    
    for idx in range(sapleCount):    
        if abs(ant[idx]) == 1:
            if idx < slot1size:
                slot_ant1.append(samples[idx])
                result.append(samples[idx])
                continue

            result[idx] = samples[idx] - slot_ant1[idx % sapleCount]

        if abs(ant[idx]) == 2:
            if not slot2Sampled:
                slot_ant2[idx % slot2size].append(samples[idx])
                result.append(samples[idx])
                if idx % slot2size == slot1size - 1:
                    slot2Sampled = True
                continue

            result[idx] = samples[idx] - slot_ant2[idx % sapleCount]
    
    return result




if __name__ == "__main__":
    for x in range(8):
        print(weights_fun(8, x, series=3)[1])