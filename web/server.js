const express = require('express');
const mysql = require('mysql2');
const app = express();

const connection = mysql.createConnection({
  host: 'localhost',           
  user: 'root',                
  password: '',                
  database: 'esp_database'    
});

connection.connect((err) => {
  if (err) {
    console.error('Error connecting to MySQL:', err.stack);
    return;
  }
  console.log('Connected to MySQL as id ' + connection.threadId);
});

function fetchSensorData(location, callback) {
  const query = `
    SELECT sensor, value, reading_time
    FROM SensorData
    WHERE location = ?
    AND sensor IN ('temperature', 'light')
    ORDER BY reading_time DESC
  `;

  // Run the query with the location parameter
  connection.query(query, [location], (err, results) => {
    if (err) {
      console.error('Error fetching sensor data:', err);
      return;
    }
    callback(results);  
  });
}

app.get('/api/sensor/:location', (req, res) => {
  const location = req.params.location; 

  fetchSensorData(location, (data) => {
    if (data.length > 0) {
      res.json(data);  
    } else {
      res.status(404).json({ error: `No sensor data found for location: ${location}` });
    }
  });
});

// Start the server
app.listen(3000, () => {
  console.log('Server running on port 3000');
});
