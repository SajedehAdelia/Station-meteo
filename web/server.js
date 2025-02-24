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

app.use(express.static('public'));

function getWeatherData(callback) {
  const query = 'SELECT temperature, humidity, pressure FROM weather_data ORDER BY timestamp DESC LIMIT 1';
  connection.query(query, (err, results) => {
    if (err) {
      console.error('Error fetching weather data:', err);
      return;
    }
    if (results.length > 0) {
      callback(results[0]);  
    } else {
      callback(null);  
    }
  });
}

app.get('/api/weather', (req, res) => {
  getWeatherData((data) => {
    if (data) {
      res.json(data);  
    } else {
      res.status(404).json({ error: 'Weather data not found' });
    }
  });
});

app.listen(3000, () => {
  console.log('Server running on port 3000');
});
