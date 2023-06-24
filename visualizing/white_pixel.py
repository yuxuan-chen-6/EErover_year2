import cv2
import numpy as np
from PIL import Image

path="./visualizing/test.png"

def percentage_near_white_pixels(image_path, tolerance):
    # Open the image
    image = Image.open(image_path)

    # Convert the image to RGB if it has an alpha channel
    image = image.convert("RGB")

    # Get the pixel data of the image
    pixels = image.load()

    # Initialize the count of near white pixels
    near_white_pixel_count = 0

    # Iterate over each pixel in the image
    for i in range(image.width):
        for j in range(image.height):
            # Get the RGB values of the pixel
            r, g, b = pixels[i, j]

            # Check if the pixel is within the tolerance range of white
            if abs(r - 255) <= tolerance and abs(g - 255) <= tolerance and abs(b - 255) <= tolerance:
                near_white_pixel_count += 1

    return 100*near_white_pixel_count/(image.width*image.height)

# Path to the colored image
image_path = "./visualizing/test3.jpeg"

# Tolerance level for each RGB component
tolerance = 100  # Adjust this value based on the desired range of colors

# Call the function to count near white pixels
near_white_pixel_count = percentage_near_white_pixels(image_path, tolerance)

print("percentage of near white pixels:", near_white_pixel_count, "%")

