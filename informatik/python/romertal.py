def omkodciffer(c):
    if c == "I":
        return 1
    if c == "V":
        return 5
    if c == "X":
        return 10
    if c == "L":
        return 50
    if c == "C":
        return 100
    if c == "D":
        return 500
    if c == "M":
        return 1000

romerTal = input("Indtast romertal: ").upper()
tal = []
sum = 0
skip = 0;

for i in romerTal:
    tal.append(omkodciffer(i))

for i in tal:
    print(str(i), end = ', ')

for i in range(len(tal)):
    if ((len(tal)%2)!=0 and i==(len(tal)-1)):
        sum+=tal[i]
    elif(skip == 1):
        skip -= 1
        continue
    elif(tal[i]<tal[i+1]):
        sum += (tal[i+1]-tal[i])
        skip += 1
    elif(tal[i]>tal[i+1]):
        sum += (tal[i]+tal[i+1])
        skip += 1
    else:
        sum += (tal[i]+tal[i+1])
        skip += 1

print('')
print(sum)

