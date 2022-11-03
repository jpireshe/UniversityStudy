import staticmap
import matplotlib.pyplot as plt
import matplotlib.image as mpimg
import math
import os

class mapmaker:
    def __init__(self, points, originLat, originLng, maxDistance, placeName, ages):
        self.points = points
        self.lat = originLat
        self.lng = originLng
        self.distance = maxDistance
        self.placeName = placeName
        self.ages = ages

    def generateMap(self):
        # create map
        m = staticmap.StaticMap(500,500)
        # create origin
        origin = staticmap.CircleMarker((self.lng, self.lat), 'black', 18)
        m.add_marker(origin)
        # get age difference
        delta = max(self.ages) - min(self.ages)

        # put points
        i = 0
        for point in self.points:
            # % of age in relation to max
            coeff = (self.ages[i]-min(self.ages))/delta

            # amount of blue and red we will then use
            # i know it is a weird way to create a gradient but the "reder" the older :)
            # notice I actually just created a hex string
            redhex = coeff*255
            bluehex = hex(int(255 - redhex)) + "0"
            bluehex = bluehex[2:4]
            redhex = hex(int(redhex)) + "0"
            redhex = redhex[2:4]
            color = "#" + redhex + "00" + bluehex

            # create a map for this guy
            p = staticmap.CircleMarker((point[1], point[0]), color, 18)
            m.add_marker(p)
            i += 1
        
        # create image
        mapImage = m.render(center=(self.lng,self.lat))
        mapImage
        mapImage.save("hidden.png")

        # render image into matlibplot
        img = mpimg.imread("hidden.png")
        imgplot = plt.imshow(img, extent=[self.lng - self.distance,self.lng + self.distance,self.lat - self.distance,self.lat + self.distance])
        plt.title("Dinosaurs near " + self.placeName)
        plt.savefig("OUTPUT.png")

        # remove temporary file
        os.remove("hidden.png")


            