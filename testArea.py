#testArea.py
import methbrackets as br
ex = "(9+(6+(2)))*(3+(2+8))"

content = br.braout(ex)

def ev (str):
	return evalv(str)

for i in content:
	ev(i)

