import numpy as np

# The dump file is expected to consist of just the part between "-----begin dump----" and "-----end dump----"
DUMP = '/public/sla/dumps/L04_CDD16C.txt'
raw_data = np.loadtxt(DUMP, delimiter=" ", dtype=str, max_rows=256)

# slice off crc-16 (last 2 bytes)
raw_data_flat = raw_data[:,:32].ravel()

def convert_16bit(x:tuple) -> float:
	trh = x[0]
	trl = x[1]
	return (float.fromhex(trh)/2) -41  + float.fromhex(trl)/512

def convert_8bit(x:str) -> float:
	trh = x[0]
	return (float.fromhex(trh)/2) -41

# convert list to tuples of [(trh, trl), (trh,trl),...] (16-bit mode)
raw_tuple_list = list(zip(*[iter(raw_data_flat)]*2))

# Temperatures in when in 16-bit mode
l_16 = list(map(convert_16bit, raw_tuple_list))
# Temperatures when in 8-bit mode
l_8 = list(map(convert_8bit, raw_data_flat))

# Create csv
np.savetxt(DUMP+"_16bit.csv", l_16, delimiter=",")
np.savetxt(DUMP+"_8bit.csv", l_8, delimiter=",")