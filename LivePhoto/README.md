# Overview 

This script creates animation from list of images using imagemagick

# Dependencies 

Instlation of imagemagick required :
```
sudo apt-get install imagemagick 
```

# Usage 
Usage is verry simple:

```
./create_animation.py  -o /path/to/output/animation.gif --file file1.jpg path/to/file2.jpg ../path/to/file3.jpg
```

Or just :
```
./create_animation.py -f /path/to/folder/with/images/for/animation/*.jpg
```
In that case animation will be created as anim.gif in current folder 

# Additional usage
Acript just calls imagemagick commands to create animation. 
With argument `-c ` you can create shell script for your files and run it separately.
```
➜  CreateAnim git:(master) ./create_animation.py -c converter.sh -o ira.gif --file ~/Pictures/100D3000/IRA/act14/*
➜  CreateAnim git:(master) ✗ cat converter.sh 
mkdir  -p /tmp/3e56614d999948a98e0bf6f115e53154/
cp /home/alex/Pictures/100D3000/IRA/act14/DSC_0222.JPG /tmp/3e56614d999948a98e0bf6f115e53154/1.jpg
mogrify -resize 640x480 /tmp/3e56614d999948a98e0bf6f115e53154/1.jpg
cp /home/alex/Pictures/100D3000/IRA/act14/DSC_0223.JPG /tmp/3e56614d999948a98e0bf6f115e53154/2.jpg
mogrify -resize 640x480 /tmp/3e56614d999948a98e0bf6f115e53154/2.jpg
cp /home/alex/Pictures/100D3000/IRA/act14/DSC_0224.JPG /tmp/3e56614d999948a98e0bf6f115e53154/3.jpg
mogrify -resize 640x480 /tmp/3e56614d999948a98e0bf6f115e53154/3.jpg
cp /home/alex/Pictures/100D3000/IRA/act14/DSC_0225.JPG /tmp/3e56614d999948a98e0bf6f115e53154/4.jpg
mogrify -resize 640x480 /tmp/3e56614d999948a98e0bf6f115e53154/4.jpg
cp /home/alex/Pictures/100D3000/IRA/act14/DSC_0225.JPG /tmp/3e56614d999948a98e0bf6f115e53154/5.jpg
mogrify -resize 640x480 /tmp/3e56614d999948a98e0bf6f115e53154/5.jpg
cp /home/alex/Pictures/100D3000/IRA/act14/DSC_0224.JPG /tmp/3e56614d999948a98e0bf6f115e53154/6.jpg
mogrify -resize 640x480 /tmp/3e56614d999948a98e0bf6f115e53154/6.jpg
cp /home/alex/Pictures/100D3000/IRA/act14/DSC_0223.JPG /tmp/3e56614d999948a98e0bf6f115e53154/7.jpg
mogrify -resize 640x480 /tmp/3e56614d999948a98e0bf6f115e53154/7.jpg
cp /home/alex/Pictures/100D3000/IRA/act14/DSC_0222.JPG /tmp/3e56614d999948a98e0bf6f115e53154/8.jpg
mogrify -resize 640x480 /tmp/3e56614d999948a98e0bf6f115e53154/8.jpg
convert -delay 10 -loop 0 /tmp/3e56614d999948a98e0bf6f115e53154/1.jpg /tmp/3e56614d999948a98e0bf6f115e53154/2.jpg /tmp/3e56614d999948a98e0bf6f115e53154/3.jpg /tmp/3e56614d999948a98e0bf6f115e53154/4.jpg /tmp/3e56614d999948a98e0bf6f115e53154/5.jpg /tmp/3e56614d999948a98e0bf6f115e53154/6.jpg /tmp/3e56614d999948a98e0bf6f115e53154/7.jpg /tmp/3e56614d999948a98e0bf6f115e53154/8.jpg ira.gif
rm -r /tmp/3e56614d999948a98e0bf6f115e53154/
➜  CreateAnim git:(master) ✗ 

```

# TODO 
 - [ ] Automaticaly detect similar scenes in on the images and create multiple animations story
 - [ ] Customize delay  via commandline
 - [ ] Customize backward loop creation via commandline 
 - [ ] Drag and drop
 - [ ] -dir option to create animation from dir with images and automaticaly create output in corresponding directory 
