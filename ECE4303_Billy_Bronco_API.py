
# personal use script     uWCWOwL_ZF8pXUowQQMDXg

#secret	           SyMERL09az-rgYfdCS2yqb-ceP94Hg
import serial
import time
import praw
import re
import pygame

ser = serial.Serial('COM5', 9600)
pygame.init()
#       # Create pygame window
pygame.display.set_caption("TelloTV Live!")
self.screen = pygame.display.set_mode([960, 720])


def create_reddit_object():
    reddit = praw.Reddit(
                        client_id = "uWCWOwL_ZF8pXUowQQMDXg",
                        client_secret = "SyMERL09az-rgYfdCS2yqb-ceP94Hg",
                        user_agent = "Test_api",
                        username = "camyjm1",    
                        password = "1234kira",)
    return reddit

def is_name_in_text(length,text,names):

    possible_name = set(re.findall(r'\bb[a-z]*',text)) #find all words of specific letter in this case lowercase b
    
    if  bool(names.search(str(possible_name))):    
        return True     
    return False 

def is_unicode(s):
    if isinstance(s,str):
        return True
    return False


def led_on_off(switching):
     
    if switching =="on":
       # print("LED is on...")
        time.sleep(0.1) 
        ser.write(b'H') 
        
    elif switching =="off":
       # print("LED is off...")
        time.sleep(0.1)
        ser.write(b'L')
        
 
time.sleep(5)
###### WEBSCRAPPING ##############
reddit = create_reddit_object() 
subred = reddit.subreddit("CalPolyPomona") 
names = re.compile(r'billy')  #THIS IS THE NAME WE'RE LOOKING FOR 
new = subred.new(limit = 10)  #LIMIT of reddit post we'll have the code look at
##################################

#######ARDUINO COMMS###############
startMarker = '<'
endMarker = '>'
dataStarted = False
dataBuf = ""
messageComplete = False
###################################

############### WEBSCRAPPING PORTION ############################
type(new)
x = next(new)
dir(x) 
for i in new: 
   print('####################################################################################')
   print("")
   print(i.selftext)
   length = len(set(re.findall(r'\bw[a-z]*', i.selftext)))

   print('*****')
   print(is_name_in_text(length,i.selftext,names))
   print('*****')
   if (is_name_in_text(length,i.selftext,names)):
        led_on_off("on")
        time.sleep(0.75)
        led_on_off("off")
        time.sleep(0.5)
   else:
        time.sleep(0.5)
   print("")
   print('####################################################################################')
 