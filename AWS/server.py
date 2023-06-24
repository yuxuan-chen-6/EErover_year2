from flask import Flask, request
import mysql.connector

app = Flask(__name__)

@app.route('/update', methods=['POST'])
def update_database():
    # Get the data from the request
    data = request.get_json()

    # Extract the values from the data
    colour = data['Colour']
    vin = data['Vin']
    vout = data['Vout']
    iout = data['Iout']
    duty = data['Duty']

    # Connect to the MySQL database
    cnx = mysql.connector.connect(user='ethanchen', password='cyx',
                                  host='18.207.219.58', database='Persondb')
    cursor = cnx.cursor()

    # Insert the data into the database
    query = "UPDATE Power SET Vin=%s, Vout=%s, Iout=%s, Duty=%s WHERE Colour=%s"    values = (colour, vin, vout, iout, duty)
    cursor.execute(query, values)
    cnx.commit()

    # Close the database connection
    cursor.close()
    cnx.close()

    return 'Data inserted successfully'

if __name__ == '__main__':
    app.run()