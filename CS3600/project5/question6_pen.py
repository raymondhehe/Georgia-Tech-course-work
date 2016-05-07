import Testing
import NeuralNetUtil
import NeuralNet

n = 0
print "~~~~~~~~~~~~~~~~~~~~~~~TestPenData~~~~~~~~~~~~~~~~~~~~~~~"
while n <= 40:
    p = 0
    penList = []
    print "------ #", n, "neurons per hidden layer ------"
    while p < 5:
        print "Iteration #", p + 1
        pen_Net, pen_test = Testing.buildNeuralNet(Testing.penData, maxItr = 200, hiddenLayerList = [n])
        penList.append(pen_test)
        p += 1
        
    print "Iteration result:"
    print "Accuracy standard deviation", Testing.stDeviation(penList)
    print "Accuracy average:", Testing.average(penList)
    print "Max Accuracy", max(penList)
    n += 5
