import library 
import time

print("Testing SDL abstraction import")

sdl = library.SDL();
window = library.SDLWindow("pybind11",0,0,640,480);

time.sleep(5)
