import Testing
import NeuralNetUtil
import NeuralNet

n = 0
print "~~~~~~~~~~~~~~~~~~~~~~~TestCarData~~~~~~~~~~~~~~~~~~~~~~~"
while n <= 40:
    c = 0
    carList = []
    print "------- #", n, "neurons per hidden layer -------"
    while c < 5:
        print "Iteration #", c + 1
        car_Net, car_test = Testing.buildNeuralNet(Testing.carData, maxItr = 200, hiddenLayerList = [n])
        carList.append(car_test)
        c += 1
    
    print "Iteration result:"
    print "Accuracy standard deviation", Testing.stDeviation(carList)
    print "Accuracy average:", Testing.average(carList)
    print "Max Accuracy:", max(carList)
    n += 5


