#!/usr/bin/env python
import math
import cairo
import datetime

YEAR = 2018
WIDTH, HEIGHT = 10000, 10000
RADIUS = 0.40
FONT_SIZE = 0.0060
HOLIDAY_SCALE = 1.3
COLOR = (0,0,0)
HOLIDAY_COLOR = (1,0,0)
FACE = 'Georgia'

surface = cairo.ImageSurface (cairo.FORMAT_ARGB32, WIDTH, HEIGHT)
ctx = cairo.Context (surface)

ctx.scale (WIDTH, HEIGHT)
ctx.rectangle (0, 0, 1, 1)
ctx.set_source_rgb(1, 1, 1) 
ctx.fill ()
ctx.translate (0, 0)

def text(ctx, string, pos, theta = 0.0, font_size = FONT_SIZE, font_color = COLOR):
    ctx.save()
    ctx.select_font_face(FACE , cairo.FONT_SLANT_NORMAL, cairo.FONT_WEIGHT_NORMAL)
    ctx.set_font_size(font_size)
    ctx.move_to(pos[0],pos[1])
    ctx.rotate(theta)
    ctx.set_source_rgb(*font_color)
    ctx.show_text(string)
    ctx.restore()

def is_holiday(day):
  date = day_to_date(day)
  return date.weekday() > 4

def day_to_ang(day):
  return 360 * (day/365.0)

def day_to_date(day):
  return datetime.date(YEAR, 1, 1) + datetime.timedelta(day - 1)
  
def day_to_text(day):
  return day_to_date(day).strftime("%d %B %A")

def get_point(ang, radius):
  dx = radius * math.cos(ang)
  dy = radius * math.sin(ang)
  return (0.5 + dx, 0.5 + dy)

ctx.move_to (0, 0)

for x in range (1, 366):
  day = x
  date = day_to_date(day)
  x = day_to_ang(x)
  x = x - 90
  x = math.radians(x)
  if (is_holiday(day)):
    text(ctx, day_to_text(day), get_point(x, RADIUS), x, font_size = FONT_SIZE * HOLIDAY_SCALE, font_color = HOLIDAY_COLOR)
  else:
    text(ctx, day_to_text(day), get_point(x, RADIUS), x)

text(ctx, str(YEAR), (0.37, 0.3), 0,  font_size = 0.1, font_color = HOLIDAY_COLOR)
text(ctx, "Povered by https://github.com/alexkutsan", (0.86, 0.99), 0, font_color = (0.5,0.5,0.5), font_size = 0.006)

surface.write_to_png ("calendar.png") # Output to PNG

