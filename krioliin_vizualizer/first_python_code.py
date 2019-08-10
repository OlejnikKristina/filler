# map = open("out1.txt", 'r+')
# i = 0

# while i < 300:
# 	if (map.seek(i) == '<'):
# 		map.write("a")
# 	i += 1

# for c in map:
# 	if (c == '<'):
# 		c = 'a'
with open("out1.txt", 'r+') as file:
	data = file

# for n, i in enumerate(data):
# 	for n, i in enumerate(data):
# 		if data[n] == '#':
# 			data[n] = 'a'

print data

with open("out2.txt", "w") as file:
	file.writelines(data)

file.close ()