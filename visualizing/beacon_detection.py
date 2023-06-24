import cv2
import numpy as np
import sys

image = cv2.imread('./beacon_red.jpeg')

# hsv
lower_red = np.array([0, 100, 100])
upper_red = np.array([10, 255, 255])

lower_yellow = np.array([25, 100, 100])
upper_yellow = np.array([35, 255, 255])

lower_blue = np.array([100, 100, 100])
upper_blue = np.array([130, 255, 255])

# rgb to hsv
hsv_image = cv2.cvtColor(image, cv2.COLOR_BGR2HSV)

# gemo
red_mask = cv2.inRange(hsv_image, lower_red, upper_red)
yellow_mask = cv2.inRange(hsv_image, lower_yellow, upper_yellow)
blue_mask = cv2.inRange(hsv_image, lower_blue, upper_blue)

# detec
if cv2.countNonZero(red_mask) > 0:
    print("Detected color: Red")
    sys.exit(0)
elif cv2.countNonZero(yellow_mask) > 0:
    print("Detected color: Yellow")
    sys.exit(0)
elif cv2.countNonZero(blue_mask) > 0:
    print("Detected color: Blue")
    sys.exit(0)
else:
    print("No color detected")


cv2.waitKey(0)
cv2.destroyAllWindows()
