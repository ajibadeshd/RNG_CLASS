import matplotlib.pyplot as plt
import time
import glob



def plot(rng_obj, engine):
    values = []
    names = []
    for rng in engine:
        values.append(rng[rng_obj])
        names.append(rng["name"])
    #print(values)
    #print(names)
    plt.title(rng_obj)
    plt.bar(names, values)
    plt.show()
    
        


PCG = {}
STD = {}
BOOST = {}
PIMC = {}

for line in open("Sample_size_10000000_PCG.txt", "r").readlines():
    PCG.update({"name": "PCG"})
    PCG.update({line.split()[0]: float(line.split()[1])})

for line in open("Sample_size_10000000_std_mt19937.txt", "r").readlines():
    STD.update({line.split()[0]: float(line.split()[1])})
    STD.update({"name": "STD"})
    
for line in open("Sample_size_10000000_pimc_mt19937.txt", "r").readlines():
    PIMC.update({line.split()[0]: float(line.split()[1])})
    PIMC.update({"name": "PIMC"})
    
for line in open("Sample_size_10000000_boost_mt19937.txt", "r").readlines():
    BOOST.update({line.split()[0]: float(line.split()[1])})
    BOOST.update({"name": "BOOST"})
    
engine= [PCG, STD, BOOST, PIMC]

plot("rand", engine)
plot("randInt", engine)
plot("randExc", engine)
plot("seeded_randExc", engine)
plot("randDblExc", engine)
plot("seeded_randDblExc", engine)
plot("randNorm", engine)
