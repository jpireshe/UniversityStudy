import argparse
import staticmap
import matplotlib
import math
import dinodata
import mapmaker

############# Begin the runtime by processing the parameters #############

parser = argparse.ArgumentParser() # my option was using arparse
parser.add_argument('-z', dest='zipCode', type=int, required=True, help='Zip Code')
parser.add_argument('-d', dest='distance', type=float, required=True, help='Distance')
args = parser.parse_args()

############ creating dinodata class instance and calling functions ################

dinos = dinodata.dinodata()
# read dinos data frame
dinos.readdinos("dinosaur.dat")
# get zip code location
dinos.getLocation(str(args.zipCode))
# cross reference dinoframe and stdLat and stdLng
dinos.getMatches(args.distance)

############ creating mapmaker and calling functions #################

# create map with all data i will need
rMap = mapmaker.mapmaker(dinos.matchPlaces, dinos.stdLat, dinos.stdLng, args.distance, dinos.placename, dinos.matchAges)
# call the function that generates the map
rMap.generateMap()
