def spil():
    count = 13
    pInput = 3
    while True:
        print("Computerens tur")
        count -= 4-pInput
        print("der er "+str(count)+" karameller tilbage")
        if(count < 1):
            print("Du tabte!")
            return
        pInput = int(input("din tur. Hvor mange karameller vil du tage(1-3): "))
        while pInput < 1 or pInput > 3:
            print("for højt eller for lavt: "+str(pInput))
            pInput = int(input("din tur. Hvor mange karameller vil du tage(1-3): "))
        count -= pInput
        print("der er "+str(count)+" karameller tilbage")
        if(count < 1):
            print("du vandt!")
            return
    print("spil!")

first = True

while True:
    if(first):
        x = input("Start spil(y/n): ")
        first = False
    elif not first:
        x = input("spil igen(y/n): ")
    if(x=="y"):
        spil()
    elif(x=="n"):
        break
    else:
        print("Error: Invalid input-> "+x)
