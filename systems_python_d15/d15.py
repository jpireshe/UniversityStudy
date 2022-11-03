import muchmath
import unittest

class testmath(unittest.TestCase):
    def test_triangleArea(self):
        mathtest = muchmath.MuchMath()
        area = mathtest.triangleArea(2,3)
        self.assertEqual(area, 3)
    
    def test_celsiusToFahrenheit(self):
        mathtest = muchmath.MuchMath()
        c = mathtest.celsiusToFahrenheit(0)
        self.assertEqual(c, 32)

    def test_matrixAdd(self):
        mathtest = muchmath.MuchMath()
        self.assertEqual(mathtest.matrixAdd([[0,0,0], [0,0,0], [0,0,0]], [[1,1,1],[1,1,1],[1,1,1]]), [[1,1,1],[1,1,1],[1,1,1]])

    def test_computelcm(self):
        mathtest = muchmath.MuchMath()
        self.assertEqual(mathtest.compute_lcm(5,7), 35)
        self.assertEqual(mathtest.compute_lcm(7,6), 42)

    def test_leapyear(self):
        mathtest = muchmath.MuchMath()
        self.assertEqual(mathtest.leapyear(2020), True)
        self.assertEqual(mathtest.leapyear(2022), False)

if __name__ == '__main__':
    unittest.main()