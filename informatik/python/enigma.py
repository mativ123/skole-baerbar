import random
alfabetet = ['A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z']

rotor1 = 0
rotor2 = 0
rotor3 = 0

result = []

print(str(rotor1)+', '+str(rotor2)+', '+str(rotor3))

rotor1 = int(input("rotor 1 starting position: "))
rotor2 = int(input("rotor 2 starting position: "))
rotor3 = int(input("rotor 3 starting position: "))

random.seed(rotor1*rotor2*rotor3)
seedInt = int(random.random()*26)

choice = input("0=encrypt | 1=decrypt: ")

word = input("Word to encrypr: ")
counter = 0
for x in word:
    alfabetCount = 0
    if (x.upper() in alfabetet):
        for y in range(len(alfabetet)):
            if (x.upper()==alfabetet[y]):
                alfabetCount = y
        if(seedInt+alfabetCount>0):
            seedInt-=26
        elif (seedInt-alfabetCount<0):
            seedInt+=26

        if (choice=="0"):
            result.append(alfabetet[alfabetCount+seedInt])
        elif (choice=="1"):
            result.append(alfabetet[alfabetCount-seedInt])
        rotor1+=1
        random.seed(rotor1*rotor2*rotor3)
        seedInt = int(random.random()*26)
    else:
        result.append(x)

for i in result:
    print(str(i), end = '')
