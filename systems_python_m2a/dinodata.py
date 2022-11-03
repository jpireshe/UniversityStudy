class dinodata:
    def __init__(self):
        self.dinoframe = ""
        self.errors = 0
        self.matchPlaces = []
        self.matchAges = []
    
    def readdinos(self, datfile):
        f = open(datfile)
        self.headers = f.readline().rstrip().split('\t')
        errors = 0
        dinoframe = list()
        for line in f:
            splitline = line.rstrip().split('\t')
            if(len(splitline) == len(self.headers)):
                dinoframe.append(splitline)
            else:
                errors += 1
        self.dinoframe = dinoframe
        self.errors = errors
        f.close()
        return 

    def getLocation(self, zipCode): 
        f = open("zipcodes.dat", "r") # zip code data
        for line in f:
            line = line.rstrip().split(';')
            if line[0] == zipCode: # compare zipcode
                self.stdLat = float(line[3]) # get standard latitude and longitude
                self.stdLng = float(line[4])
                self.placename = line[1] + ", " + line[2]
        f.close()

    def getMatches(self, distance):
        for line in self.dinoframe: # iterate dinoframe
            lat = float(line[19])
            lng = float(line[18])
            age = float(line[15])
            if (lat >= self.stdLat - distance) & (lat <= self.stdLat + distance) & (lng >= self.stdLng - distance) & (lng <= self.stdLng + distance):
            # if within range
                coordinate = [lat, lng] # create a list with lat and lng
                self.matchPlaces.append(coordinate) # put all the finds in the range in self.matches
                self.matchAges.append(age)

            