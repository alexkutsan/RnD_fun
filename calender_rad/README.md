# Radians calendar 

## Description 

This calendar made for events dairy.

You should print is on big sheet of paper (A0 or 100cmx120cm, the bigger, the better).
During year you can put on white space some quotes, memories, photos ... 
In the end of the year you will have wonderful flashback for that year. 
[Example](./calendar.png)
## Dependencies
python-cairo

## Generation

Run : 
```
$ python ./main.py
```

File calendar.png will be generated in current dirrectory.

## Customisation

You can modify parameters that you like with constants in the top of script:
```
YEAR = 2018
WIDTH, HEIGHT = 10000, 10000
RADIUS = 0.40
FONT_SIZE = 0.0060
HOLIDAY_SCALE = 1.3
COLOR = (0,0,0)
HOLIDAY_COLOR = (1,0,0)
FACE = 'Georgia'
```


