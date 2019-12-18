import numpy as np
from wallG import draw_wall as draw
import scipy.misc 

x_pad = 50
y_pad = 50 
curve = np.ones([2000, 2000])

draw(curve, 0, 0, 10, 1000)
draw(curve, 0, 990, 1000, 10)
draw(curve, 490, 990, 10, 300)
draw(curve, 490, 1280, 500, 10)
draw(curve, 980, 990, 10, 300)
draw(curve, 980, 990, 200, 10)
draw(curve, 1170, 200, 10, 800)
draw(curve, 0, 0, 700, 10)
draw(curve, 690, 0, 10, 610)
draw(curve, 690, 200, 490, 10)
draw(curve, 0, 600, 700, 10)
draw(curve, 490, 600, 10, 400)
draw(curve, 500, 0, 10, 300)
draw(curve, 500, 290, 200, 10)
draw(curve, 490, 1190, 200, 10)
draw(curve, 680, 990, 10, 210)
scipy.misc.imsave('out.jpg', curve)
