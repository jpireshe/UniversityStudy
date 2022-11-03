import dinodata
import unittest

class testdinos(unittest.TestCase):

    def test_readdinos(self):
        dinotest = dinodata.dinodata()
        dinotest.readdinos("dinosaur.dat")

        # set headers from file
        headers = "occurrence_no	record_type	reid_no	flags	collection_no	identified_name	identified_rank	identified_no	difference	accepted_name	accepted_attr	accepted_rank	accepted_no	early_interval	late_interval	max_ma	min_ma	reference_no	lng	lat	cc	state	county	latlng_basis	latlng_precision	geogscale	geogcomments	research_group".rstrip().split('\t')

        # read file, get dataframe and errors, check for same
        f = open("dinosaur.dat", "r")
        null = f.readline()
        testframe = []
        testerrors = 0
        for line in f:
            splitline = line.rstrip().split('\t')
            if(len(splitline) == len(headers)):
                testframe.append(splitline)
            else:
                testerrors += 1
        f.close()

        # assert everything equal
        self.assertEqual(dinotest.headers, headers)
        self.assertEqual(dinotest.errors,testerrors)
        self.assertEqual(dinotest.dinoframe,testframe)

    def test_init(self):
        dinotest = dinodata.dinodata()
        self.assertEqual(dinotest.dinoframe, "")
        self.assertEqual(dinotest.errors, 0)
        self.assertEqual(dinotest.matchPlaces, [])
        self.assertEqual(dinotest.matchAges, [])

    def test_getLocation(self):
        dinotest = dinodata.dinodata()
        dinotest.getLocation("46556")
        self.assertEqual(dinotest.stdLat, 41.701415)
        self.assertEqual(dinotest.stdLng, -86.24498)
        self.assertEqual(dinotest.placename, "Notre Dame, IN")
    
    def test_getMatches(self):
        dinotest = dinodata.dinodata()
        dinotest.readdinos("dinosaur.dat")
        dinotest.getLocation("46556")
        dinotest.getMatches(2)
        # i used regex to get the lists on match places and ages
        self.assertEqual(dinotest.matchPlaces,[[40.454445, -85.791946], [43.234722, -85.790558], [43.589169, -86.235275], [41.384998, -88.214996], [41.384998, -88.214996], [41.654999, -87.68], [41.384998, -88.214996]])
        self.assertEqual(dinotest.matchAges,[10.3, 0.126, 2.588, 0.0117, 0.0117, 0.0117, 0.0117])

if __name__ == '__main__':
    unittest.main()