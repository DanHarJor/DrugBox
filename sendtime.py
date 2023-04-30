import talk
import time
import datetime

now = datetime.datetime.now()
day = datetime.timedelta(days=1)

tom = now +day

print(now)

print(day)

print(tom)

snow = str(time.mktime(now.timetuple()))
stom = str(time.mktime(tom.timetuple()))

talk.speak(snow,"nw")

talk.speak(stom,"st")


