import Testing
import NeuralNetUtil
import NeuralNet


c = 0
carList = []


print "~~~~~~~~~~~~~~~~~~~~~~~TestCarData~~~~~~~~~~~~~~~~~~~~~~~"

while c < 5:
    print "Iteration #", c + 1
    car_Net, car_test = Testing.testCarData()
    carList.append(car_test)
    c += 1

print "Iteration result:"
print "Accuracy standard deviation", Testing.stDeviation(carList)
print "Accuracy average:", Testing.average(carList)
print "Max Accuracy:", max(carList)
