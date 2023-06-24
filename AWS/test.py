<<<<<<< HEAD
import mysql.connector

# Connect to the MySQL database
cnx = mysql.connector.connect(
    host='3.95.210.12',
    user='ethanchen',
    password='cyx',
    database='Persondb'
)
# Create a cursor object to interact with the database
cursor = cnx.cursor()

# Execute the query to retrieve the values of Dif1 and Dif2
query = "SELECT Dif1, Dif2 FROM Angle WHERE ID = 1"
cursor.execute(query)

# Fetch the results
result = cursor.fetchone()
dif1_value = result[0]
dif2_value = result[1]

# Print the values
print("Dif1:", dif1_value)
print("Dif2:", dif2_value)

# Close the cursor and the database connection
cursor.close()
cnx.close()

=======
import numpy as np

new_matrix = []

# create output maze
for i in range(3):
    row = []
    for j in range(3):
        row.append(1)
    new_matrix.append(row)

array_matrix = np.array(new_matrix)

# Convert array_matrix to string with desired format
output_str = np.array2string(array_matrix, separator=', ', formatter={'int': lambda x: str(x)})

print(output_str)
>>>>>>> 63fafb2 (done)
