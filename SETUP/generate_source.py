import os

def fastest_method(data, method):
	temp = {}
	for i in data.keys():
		temp.update({"PIMC " +str(i):  data[i]["PIMC"][method]})
		temp.update({"STL " +str(i): data[i]["STL"][method]})
		temp.update({"BOOST " +str(i): data[i]["BOOST"][method]})
		temp.update({"PCG " +str(i): data[i]["PCG"][method]})
		
	a = sorted(temp.items(), key=lambda x:x[1])
	engine= a[0][0].split()[0]
	optimization = a[0][0].split()[1]
	for j in a:
		if "O3" in j[0]:
			engine=j[0].split()[0]
			return engine
	#return a, engine, optimization


def generate_source_code(method, eng):
	cpp_source = open(os.getcwd()+"/include/"+method+'.cpp', "w")
	method = "FAST_" + method.upper()
	
	print('#include "RNG.h"', file = cpp_source)
	print('', file = cpp_source)
	print('inline std::unique_ptr<RNG> '+str(method)+'(){', file = cpp_source)
	print('\tstd::unique_ptr<RNG> temp;', file = cpp_source)
	print('\ttemp = GetRNG("{}");'.format(eng), file = cpp_source)
	print('\treturn temp;', file = cpp_source)
	print('\t};', file = cpp_source)
	print('', file = cpp_source)
	print('', file = cpp_source)
	print('inline std::unique_ptr<RNG> '+str(method)+'( uint32 seed){', file = cpp_source)
	print('\tstd::unique_ptr<RNG> temp;', file = cpp_source)
	print('\ttemp = GetRNG("{}", seed);'.format(eng), file = cpp_source)
	print('\treturn temp;', file = cpp_source)
	print('\t};', file = cpp_source)
	print(method.lower()+".cpp created and added to the include directory\n")

	cpp_source.close()


startPIMC= False
startSTD= False
startBOOST= False
startPCG= False

data = {}
for file in ["no_optimization.dat", "O1_optimization.dat", "O2_optimization.dat", "O3_optimization.dat"]:
	PCG = {}
	STD = {}
	BOOST = {}
	PIMC = {}
	for line in open("SETUP/"+file):
		if "These random numbers are from PIMC" in line:
			startPIMC = True
		if startPIMC:
			if "Time for" in line:
				#print( line[:-2].split()[2], line[:-2].split()[-1])
				PIMC.update( {line[:-2].split()[2]: float(line[:-2].split()[-1])})
		 
			if "TOTAL" in line:
				PIMC.update( {line[:-2].split()[0]: float(line[:-2].split()[-1])})
				#PIMC.update({"name":"PIMC"})
				startPIMC = False
				
		if "These random numbers are from STL" in line:
			startSTD = True
		if startSTD:
			if "Time for" in line:
				#print( line[:-2].split()[2], line[:-2].split()[-1])
				STD.update( {line[:-2].split()[2]: float(line[:-2].split()[-1])})
			
			if "TOTAL" in line:
				STD.update( {line[:-2].split()[0]: float(line[:-2].split()[-1])})
				#STD.update({"name": "STD"})
				startSTD = False
	
		if "These random numbers are from BOOST" in line:
			startBOOST = True
		if startBOOST:
			if "Time for" in line:
				#print( line[:-2].split()[2], line[:-2].split()[-1])
				BOOST.update( {line[:-2].split()[2]: float(line[:-2].split()[-1])})
				
			if "TOTAL" in line:
				BOOST.update( {line[:-2].split()[0]: float(line[:-2].split()[-1])})
				#BOOST.update({"name": "BOOST"})
				startBOOST = False
				
		if "These random numbers are from PCG" in line:
			startPCG = True
		if startPCG:
			if "Time for" in line:
				#print( line[:-2].split()[2], line[:-2].split()[-1])
				PCG.update( {line[:-2].split()[2]: float(line[:-2].split()[-1])})
	
			if "TOTAL" in line:
				PCG.update( {line[:-2].split()[0]: float(line[:-2].split()[-1])})
				#PCG.update({"name": "PCG"})
				startPCG = False
	if "no" in file:
		data.update({"no_opt":{"PIMC": PIMC, "STL": STD, "BOOST": BOOST, "PCG": PCG}})
	elif "O1" in file:
		data.update({"O1":{"PIMC": PIMC, "STL": STD, "BOOST": BOOST, "PCG": PCG}})
	elif "O2" in file:
		data.update({"O2":{"PIMC": PIMC, "STL": STD, "BOOST": BOOST, "PCG": PCG}})
	elif "O3" in file:
		data.update({"O3":{"PIMC": PIMC, "STL": STD, "BOOST": BOOST, "PCG": PCG}})
		

methods = ["rand","randInt", "randExp", "randNorm", "randBernoulli"]


for m in methods:
	engine = fastest_method(data, m)
	generate_source_code(m, engine)
