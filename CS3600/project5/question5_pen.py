import Testing
import NeuralNetUtil
import NeuralNet


p = 0
penList= []


print "~~~~~~~~~~~~~~~~~~~~~~~TestPenData~~~~~~~~~~~~~~~~~~~~~~~"

while p < 5:
    print "Iteration #", p + 1
    pen_Net, pen_test = Testing.testCarData()
    penList.append(pen_test)
    p += 1

print "Iteration result:"
print "Accuracy standard deviation", Testing.stDeviation(penList)
print "Accuracy average:", Testing.average(penList)
print "Max Accuracy:", max(penList)
