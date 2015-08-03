 # Check timetables for Krakow tram number 2 from Filharmonia stop
from lxml import html
from time import localtime, strftime
import requests
from datetime import datetime
import LEDWriter

# show sandclock on LED while loading 
LEDWriter.writeSymbol('clock')

hourFormat = '%H:%M'

page = requests.get('http://rozklady.mpk.krakow.pl/aktualne/0002/0002t005.htm')
tree = html.fromstring(page.text[43:]) #skip the first encoding headers

hours = tree.xpath('//font[@class="fonthour"]/text()')
mins = tree.xpath('//font[@class="fontmin"]/text()')

all = []
for t in zip(hours, mins):
	all.append(map(lambda x,y: x.zfill(2) + ':' + y, [t[0] for i in range(len(t[1].split()))], t[1].split()))

week = sum(all[0::3], [])
saturday = sum(all[1::3], [])
sunday = sum(all[2::3], [])

today = datetime.today().weekday()

if today == 6:
	timeList = sunday
elif today == 5:
	timeList = saturday
else:
	timeList = week	

now = strftime(hourFormat, localtime())

for time in timeList:
	deltaTime = datetime.strptime(time, hourFormat) - datetime.strptime(now, hourFormat)
	if deltaTime.days > -1:
		minutesToNextTram = deltaTime.seconds / 60
		break

print 'Next tram is in {} minutes'.format(minutesToNextTram)
LEDWriter.writeNumber(minutesToNextTram)
