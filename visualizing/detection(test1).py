import cv2
import numpy as np

def classify_lines(image):
    # Preprocessing
    resized_image = cv2.resize(image, (640, 480))  # Resize image for faster processing
    grayscale_image = cv2.cvtColor(resized_image, cv2.COLOR_BGR2GRAY)  # Convert to grayscale

    # Thresholding
    _, thresholded_image = cv2.threshold(grayscale_image, 127, 255, cv2.THRESH_BINARY)  # Threshold to separate white from black

    # Edge detection
    edges = cv2.Canny(thresholded_image, 50, 150)  # Perform Canny edge detection

    # Line detection
    lines = cv2.HoughLines(edges, 1, np.pi / 180, threshold=50)  # Perform Hough line detection

    # Reference line
    reference_line_angle = np.pi / 2  # Set the reference line angle (adjust as needed)

    # Line classification
    line_positions = [0, 0, 0]  # Initialize counters for right, left, front
    for line in lines:
        rho, theta = line[0]
        print(theta)
        angle_diff = theta - reference_line_angle
        if angle_diff > np.pi / 4:  # Threshold for line being at the left (adjust as needed)
            line_positions[0] += 1  # Increment left counter
        elif angle_diff < -np.pi / 16:  # Threshold for line being at the right (adjust as needed)
            line_positions[2] += 1  # Increment right counter
        else:
            line_positions[1] += 1  # Increment front counter

    #decition making


    return line_positions


print(classify_lines(cv2.imread("./visualizing/test1.jpeg")))