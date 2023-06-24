const express = require("express");
const cors = require("cors");
const fs = require("fs");
const path = require("path");
const mysql = require('mysql');

const app = express();
const PORT1 = process.env.PORT || 3100;
const PORT2 = process.env.PORT || 3001;

app.use(cors({
  origin: '*',
  methods: ['GET', 'POST', 'PUT', 'DELETE', 'UPDATE', 'PATCH']
}));

const con = mysql.createConnection({
  host: "18.207.219.58",
  user: "ethanchen",
  password: "cyx",
  database: "Persondb"
});

con.connect(function(err) {
  if (err) throw err;
  console.log("Successfully connected to the database...\n");

  // Get all persons
  app.get("/personquery", (req, res) => {
    con.query("SELECT * FROM Power", function(err, result, fields) {
      if (err) throw err;
      res.json(result);
    });
  });

  // Get the matrix
  app.get("/matrix", (req, res) => {
    const filePath = path.join(__dirname, "matrix.txt");
  
    fs.readFile(filePath, "utf8", (err, data) => {
      if (err) {
        console.error("Error reading matrix file:", err);
        return res.status(500).json({ error: "Failed to read matrix file" });
      }
  
      const matrix = JSON.parse(data);
      res.json({ matrix });
    });
  });

  // Update the database
  app.post("/update", (req, res) => {
    const { vin, vout, iout, duty } = req.body;

    const updateQuery = "UPDATE Power SET Vin = ?, Vout = ?, Iout = ?, Duty = ? WHERE Colour = 'Yellow'";
    con.query(updateQuery, [vin, vout, iout, duty], function(err, result) {
      if (err) throw err;
      console.log("Database updated successfully");
      res.send("Database updated successfully");
    });
  });

  app.listen(PORT1, () => {
    console.log(`Server is running on port ${PORT1}`);
  });

  app.listen(PORT2, () => {
    console.log(`Server is running on port ${PORT2}`);
  });
});