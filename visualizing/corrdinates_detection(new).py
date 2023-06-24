import cv2
import numpy as np
import os
import argparse
import matplotlib.pyplot as plt
import time


def compress_image(input_image_path, output_image_path, quality):
    # Load the image using OpenCV
    image = cv2.imread(input_image_path)

    # Set the compression parameters
    compression_params = [cv2.IMWRITE_JPEG_QUALITY, quality]

    # Compress and save the image
    cv2.imwrite(output_image_path, image, compression_params)

# Example usage
# input_path = './visualizing/test1.jpeg'  # Path to the input image file
# output_path = './visualizing/compress1.jpg'  # Path to save the compressed image file
# compression_quality = 70  # Set the compression quality (0-100)

# compress_image(input_path, output_path, compression_quality)


def display_image(image):
    # Preprocessing
    #resized_image = cv2.resize(image, (640, 480))  # Resize image for faster processing
    grayscale_image = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)  # Convert to grayscale
    #cv2.imshow('Gray image', grayscale_image)
    height, width = grayscale_image.shape
    for y in range(height//2,height,1):
        for x in range(0,width,1):
        # Get the color value of the pixel
            color = image[y, x]
            if color[0] < 50 and color[1] < 50 and color[2] < 50:
                color=0
                x_coordinates.append(x)
                y_coordinates.append(-y)
                continue
            elif color[0] > 200 and color[1] > 200 and color[2] > 200:
                color=1
                continue
            else:
                color=-1
                continue
        # Print the color value
            print(f"Pixel ({x}, {y}): {color}")
    


    #cv2.waitKey(10000)
    #cv2.destroyAllWindows()
    #plt.close('all')
x_coordinates = []
y_coordinates = []
print(display_image(cv2.imread("./visualizing/test9.jpeg")))
plt.plot(x_coordinates, y_coordinates, 'o')
plt.xlabel('X')
plt.ylabel('Y')
plt.title('Multiple Points')
plt.show()
plt.close()