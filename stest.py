import os

stream = os.popen('python3 -m serial.tools.list_ports')

output = stream.read()
def sfind (this, inthis):
        count = 0
        for i in inthis:
            count = count + 1
            if (i==this):
                return count

print(sfind('M',output))
print(output[0:12])
