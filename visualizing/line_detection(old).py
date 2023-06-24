import cv2
import numpy as np

def detect_road(image):
    # Convert the image to grayscale
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

    # Apply Canny edge detection
    edges = cv2.Canny(gray, 50, 150, apertureSize=3)

    # Apply probabilistic Hough line transform
    lines = cv2.HoughLinesP(edges, rho=1, theta=np.pi / 240, threshold=20, minLineLength=3, maxLineGap=12)

    # Initialize flags for presence of strips on each side
    is_strip_left = False
    is_strip_right = False
    is_strip_front = False
    is_double_strip = False
    dead_or_front = [False, False]

    # Create an empty list to store valid points
    recorded_points = []

    if lines is not None:
        for line in lines:
            x1, y1, x2, y2 = line[0]
            # Calculate slope of the line
            slope = (y2 - y1) / (x2 - x1) if (x2 - x1) != 0 else np.inf
            # Check if the line starts from the bottom of the image
            if y1 > image.shape[0]-3 or y2 > image.shape[0]-3:
                # print(x1,y1, x2,y2, image.shape[0])
                # Check if the slope indicates a vertical line
                if abs(slope) > 1:
                    if (is_double_strip == False):
                        is_double_strip = True
                    else:
                        dead_or_front[0] = True
                
            else:
                if abs(slope) < 1:
                # Check if the line is on the left
                    if slope < 0 and x1 < image.shape[1] / 2 and x2 < image.shape[1] / 2 :
                        is_strip_left = True
                # Check if the line is on the right
                    elif slope > 0 and x1 > image.shape[1] / 2 and x2 > image.shape[1] / 2 :
                        is_strip_right = True
                    elif x1 < image.shape[1] / 2 and x2 > image.shape[1] / 2:
                        is_strip_right = True
                        is_strip_left = True
                        dead_or_front[1] = True
                    # elif (x1 < image.shape[1] / 2 and x2 > image.shape[1] / 2) or (x1 > image.shape[1] / 2 and x2 < image.shape[1] / 2):
                    #     if dead_or_front[0] == True:
                    #         dead_or_front[1] = True
                if abs(slope) > 1:
                    if y2 < image.shape[0] / 2:
                        is_strip_front = True
    if dead_or_front[0] == True:
        if dead_or_front[1] == True:
            return [0,0,0]
        else:
            return [0,1,0]

    # Decision-making logic
    directions = [0,0,0]
    if is_strip_front:
        #directions.append("Front")
        directions[1] = 1
    if is_strip_left:
        #directions.append("Left")
        directions[0] = 1
    if is_strip_right:
        #directions.append("Right")
        directions[2] = 1

    return directions


result = detect_road(cv2.imread("./visualizing/test1.jpeg"))
print(result)
result = detect_road(cv2.imread("./visualizing/test2.jpeg"))
print(result)
result = detect_road(cv2.imread("./visualizing/test3.jpeg"))
print(result)
result = detect_road(cv2.imread("./visualizing/test4.jpeg"))
print(result)
result = detect_road(cv2.imread("./visualizing/test5.jpeg"))
print(result)
result = detect_road(cv2.imread("./visualizing/test6.jpeg"))
print(result)
result = detect_road(cv2.imread("./visualizing/test7.jpeg"))
print(result)
result = detect_road(cv2.imread("./visualizing/test8.jpeg"))
print(result)
result = detect_road(cv2.imread("./visualizing/test10.jpeg"))
print(result)
