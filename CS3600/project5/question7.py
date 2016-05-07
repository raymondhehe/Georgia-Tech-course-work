import Testing
import NeuralNetUtil
import NeuralNet

n = 0

while True:
    print "------ #", n, "neurons per hidden layer ------"
    x = 0
    xorList = []
    while x < 5:
        print "Iteration #", x + 1
        xor_Net, xor_test = NeuralNet.buildNeuralNet(Testing.xorData, maxItr = 200, hiddenLayerList = [n])
        xorList.append(xor_test)
        x += 1
        
    print "Iteration result:"
    print "Accuracy standard deviation:", Testing.stDeviation(xorList)
    print "Accuracy average:", Testing.average(xorList)
    print "Max accuracy:", max(xorList)

    if Testing.average(xorList) == 1:
        break
    n += 1
