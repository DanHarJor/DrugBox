#DBgui.py
from tkinter import *
import serial
from tkcalendar import Calendar, DateEntry
import datetime as dt
import time
import talk
#ser = serial.Serial("/dev/ttyACM1",baudrate = 9600, timeout = 1)

#___________________________
#helpful functions

def popE(er):
	top = Toplevel(master)
	top.title("Error Message")
	Label(top, text = er).pack()
	Button(top, text = "OK", command = top.destroy).pack()
	top.mainloop()



#helpful functions
#_______________________________

master = Tk()
master.title("Drug Box")
for i in range(22):
    master.columnconfigure(i,weight = 1)

#takes in the day order 1st 2nd etc and the start datetime.
def dayord(ordin,sdD):
    
#    sd_dow = sdD.weekday()
#    ordinTD = dt.timedelta(days=ordin)
#    stim =  dt.time(int(dowT(sd_dow + ordin)[0:2]),int(dowT(sd_dow + ordin)[2:4])) 
#    daydt = sdD + ordinTD
#    dayDT = dt.datetime.combine(daydt,stim)
#    sdayu = str(time.mktime(dayDT.timetuple()))
#    sdayu = sdayu[:-2]
#    return sdayu

#returns times 5 seconds apart,
    sec = ordin*5
    td = dt.timedelta(seconds=sec)
    t = sdD + td
    st = str(time.mktime(t.timetuple()))
    st = st[:-2]
    print("st is : "+st)
    return st
#
#returns the string for the unix time of the box opening.
class day():
	def __init__(self,day,pos):
                self.day = day #I think these allow day.pos = 3 day.day = "mon" functionality rather than day(mon,3).
                #self. allows variables to be used outside init function.
                self.pos = pos
                lbl = Label(master, text = self.day, width = 20)
                lbl.grid(row=0, column = self.pos*3, columnspan = 3)
                
                self.h = Label(master, text = "h")
                self.h.grid(row=1, column = self.pos*3, sticky = E)
                m = Label(master, text = "m")
                m.grid(row=1, column = (self.pos*3)+2, sticky = W)
                self.eh = Entry(master, width = 5)
                self.eh.insert(0,"23")
                self.eh.grid(row=2,column= self.pos*3, sticky = E)
                sep = Label(master, text = ":")
                sep.grid(row=2,column = (self.pos*3)+1)
                self.em = Entry(master, width = 5)
                self.em.insert(0,"23")
                self.em.grid(row=2,column= (self.pos*3)+2, sticky = W)

	def getT (self):
		try: 
                    h = int(self.eh.get())
		except:
			popE("Silly Billy, you typed a letter instead of a number when putting in the time.")
		if (h<0 or h>23): 
			popE("Please insert a valid hour between 00 and 23")
		if (h<=9):
			h = "0"+str(h)
		else:
			h = str(h)
		
		try:
			m = int(self.em.get())
		except:
			popE("Silly Billy, you typed a letter instead of a number when putting in the time.")
		if (m<0 or m>59): 
                        popE("Please insert valid minutes between 00 and 59")
		if (m<=9):
			m = "0"+str(m)
		else:
			m = str(m)
		t = h+m
		return t

#start from--> sets the day of which the week cycle begins
sd = Label(master, text="Start Giving me Drugs on:  ", height = 5).grid(row = 3, columnspan = 3)
SDcal = DateEntry(master, width = 12, background = "lightblue", foreground = "grey", borderwidth = 20, height = 5)
SDcal.grid(row = 3, column = 3, columnspan = 3)

days = ["Monday","Tuesday","Wednesday","Thursday","Friday","Saturday","Sunday"] 

mon = day("Monday",0)
tue = day("Tuesday",1)
wed = day("Wednesday",2)
thu = day("Thursday",3)
fri = day("Friday",4)
sat = day("Saturday",5)
sun = day("Sunday",6)

def dowT(dow):
    if (dow==0 or dow == 7): return mon.getT()
    if (dow==1 or dow == 8): return tue.getT()
    if (dow==2 or dow == 9): return wed.getT()
    if (dow==3 or dow == 10): return thu.getT()
    if (dow==4 or dow == 11): return fri.getT()
    if (dow==5 or dow == 12): return sat.getT()
    if (dow==6): return sun.getT()

def dbConfig():
    config["state"] = DISABLED
    talk.speak('reset','i')
    #the day the box will start
    sdD =  SDcal.get_date()
    sd_dow = sdD.weekday()
    sdT = "0000"
    if (sd_dow==0): sdT = mon.getT()
    if (sd_dow==1): sdT = tue.getT()
    if (sd_dow==2): sdT = wed.getT()
    if (sd_dow==3): sdT = thu.getT()
    if (sd_dow==4): sdT = fri.getT()
    if (sd_dow==5): sdT = sat.getT()
    if (sd_dow==6): sdT = sun.getT()
    sdTT = dt.time(int(sdT[0:2]),int(sdT[2:4]))
    sdDT = dt.datetime.combine(sdD,sdTT)
#This sdDT is only for testing, sets start time to 5 sec after now
    sdDT = dt.datetime.now()+dt.timedelta(seconds=5)
    now = dt.datetime.now()
    if (sdDT<now): popE("The first dispence time is set in the past. Please change the settings so that the first dispence time is in the future.")
        #Try and make python print out what the arduino sends like the serial monitor. To reduce the serial confusion. Also I think I need to find a way to wait till recieved before sending again.
    snow = str(time.mktime(now.timetuple()))
    snow = snow[:-2]
    ssd = str(time.mktime(sdDT.timetuple()))
    ssd = ssd[:-2]
    correct = 0

    print("snow sent is:   "+snow)
    talk.speak(snow, "n")
    rec = talk.listen()
    print("snow recieved is:   "+str(rec))
    if (rec != snow): 
        print("broken")
        popE("Whoops there was a communication error, please try again. Sorry.")
    elif(rec == snow):
        print("now was recieved by drug box")
        correct += 1

    print("start time sent:  "+ssd)
    talk.speak(ssd, "s")
    rec = talk.listen()
    print("start time rec:   "+rec)
    if (rec != ssd): 
        print("ssdbroken")
        popE("ssdWhoops there was a communication error, please try again. Sorry.")
    elif(rec == ssd): 
        print("ssd was recieved by drug box")
        correct += 1

    print(dayord(1,sdDT))
    talk.speak(dayord(1,sdDT), "a")
    rec = talk.listen()
    if (rec != dayord(1,sdDT)):
        print("broken")
        popE("Whoops there was a communication error, please try again. Sorry.")
    elif(rec == dayord(1,sdDT)): 
        print("Done was recieved by drug box")
        correct += 1


    print(dayord(2,sdDT))
    talk.speak(dayord(2,sdDT), "b")
    rec = talk.listen()
    if (rec != dayord(2,sdDT)): 
        print("broken")
        popE("Whoops there was a communication error, please try again. Sorry.")
    elif(rec == dayord(2,sdDT)): 
        print("Dtwo was recieved by drug box")
        correct += 1


    print(dayord(3,sdDT))
    talk.speak(dayord(3,sdDT), "c")
    rec = talk.listen()
    if (rec != dayord(3,sdDT)): 
        print("broken")
        popE("Whoops there was a communication error, please try again. Sorry.")
    elif(rec == dayord(3,sdDT)): 
        print("Dthree was recieved by drug box")
        correct += 1


    print(dayord(4,sdDT))
    talk.speak(dayord(4,sdDT), "d")
    rec = talk.listen()
    if (rec != dayord(4,sdDT)): 
        print("broken")
        popE("Whoops there was a communication error, please try again. Sorry.")
    elif(rec == dayord(4,sdDT)): 
        print("Dfour was recieved by drug box")
        correct += 1


    print(dayord(5,sdDT))
    talk.speak(dayord(5,sdDT), "e")
    rec = talk.listen()
    if (rec != dayord(5,sdDT)): 
        print("broken")
        popE("Whoops there was a communication error, please try again. Sorry.")
    elif(rec == dayord(5,sdDT)): 
        print("Dfive was recieved by drug box")
        correct += 1


    print(dayord(6,sdDT))
    talk.speak(dayord(6,sdDT), "f")
    rec = talk.listen()
    if (rec != dayord(6,sdDT)): 
        print("broken")
        popE("Whoops there was a communication error, please try again. Sorry.")
    elif(rec == dayord(6,sdDT)): 
        print("Dsix was recieved by drug box")
        correct += 1

    if (correct == 8): talk.speak('correct','t')


def popE(er):
	top = Toplevel(master)
	top.title("Error Message")
	Label(top, text = er).pack()
	Button(top, text = "OK", command = top.destroy).pack()
	top.mainloop()


class refillWindow:
    def Xbut(self):
        popE("You cannot close the window untill the box has been filled completly.\nFill a compartment, then click 'NEXT Compartment' untill all compartments are full.\nThen click FINISH to close the window.")
    def previous(self):
        print("next happened")
        talk.speak('back','r')
        self.f -= 1
        self.lc = Label(self.rw, text = str(self.f))
        self.lc.grid(row = 1, column = 0)
        if (self.f == 6):
            self.bn.destroy()
            self.bn = Button(self.rw, text = "Next Compartment", command = self.next)
            self.bn.grid(row = 2,column = 0)


    def next(self):
        def ndrefill():
            talk.speak("done","r")
            self.rw.destroy()
            talk.serMT()
            config["state"] = NORMAL

        print("next happened")
        talk.speak('next','r')
        self.f += 1
        self.lc = Label(self.rw, text = str(self.f))
        self.lc.grid(row = 1,column = 0)
        if (self.f == 7):
            self.bn.destroy()
            self.bn = Button(self.rw, text = "FINISHED", command = ndrefill)
            self.bn.grid(row = 2,column = 0)
    def __init__(self): 
        self.f = 1
        self.rw = Toplevel(master)
        self.rw.title("Refill Drug Box")
        self.lc = Label(self.rw, text = str(self.f))
        self.lc.grid(row = 1, column = 0)
        lm = Label(self.rw, text = "Use the buttons below to move between the compartments")
        lm.grid(row = 0,column = 0)
        self.bn = Button(self.rw, text = "Next Compartment", command = self.next)
        self.bn.grid(row = 2,column = 0)
        bp = Button(self.rw, text = "Previous Compartment", command = self.previous)
        bp.grid(row = 3,column = 0)
        lf = Label(self.rw, text = "When you pass 7 the drug box will be locked untill all the drugs have been revealed.")
        lf.grid(row = 4,column = 0)
        self.rw.protocol("WM_DELETE_WINDOW",self.Xbut)#when xbutton is pushed run Xbut.
        self.rw.mainloop()
          
def refill():
    talk.speak("refill",'r')
    rec = talk.listen()
    print(rec)
    if rec == "noem": 
        popE("You cannot refill before the last drugs are revealed")
    elif rec == "em":
        refillWindow()


config = Button(master, text = "Configure My Drug Box", command = dbConfig)
config.grid(row=4, columnspan = 3 )
config["state"] = DISABLED

refill = Button(master, text = "Start Refill", command = refill)
refill.grid(row=4, column = 5, columnspan = 3)
mainloop()


