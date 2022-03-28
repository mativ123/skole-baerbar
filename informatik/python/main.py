alfabetet = ['A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z']

#en variabel med resulatatet i
result = []

#funktionen der kryptere/dekryptere
def kryptering():
    #inputter ordet der skal kruptere/dekrypteres
    ord = input("ord til at kryptere/dekryptere: ")
    #inputter hvor langt hvert bogstav skal rykkes
    offset = int(input("offset: "))
    #inputter man har lyst til kryptere eller dekryptere
    ifKrypter = int(input("0=krypter | 1=dekrypter: "))
    #et variabel som indeolder hvilket bogstav i alfabetet en bogstav er
    alfabetCount = 0

    #et loop som går igennem ordet som skal krypteres/dekrypteres
    for x in ord:
        #tjekker om bogstavet er i alfabetet
        if(x.upper() in alfabetet):
            #et loop som går igennem alfabettet med index istedet for bogstaverne
            for y in range(len(alfabetet)):
                #tjekker om bogstavet i ordet er det samme som i alfabetet
                if (alfabetet[y] == x.upper()):
                    #hvis den er putter den det tal en i alfabetCount variablet
                    alfabetCount = y
            if(ifKrypter == 0):
                #tjekker om tallet går over længden af alfabetet
                if(y+offset>=26):
                    result.append(alfabetet[(alfabetCount+offset)-26])
                else:
                    result.append(alfabetet[alfabetCount+offset])
            elif (ifKrypter == 1):
                #tjekker om tallet gåt under aalfabetet
                if(y-offset<=0):
                    result.append(alfabetet[(alfabetCount-offset)+26])
                else:
                    result.append(alfabetet[alfabetCount-offset])
        else:
            result.append(x)

#køre funktionen
kryptering()

#printer resulatatet
for i in result:
    print(str(i), end = '')
