document.addEventListener("DOMContentLoaded", function () {
    const weatherDataElement = document.getElementById("weather-data");
  
    function fetchSensorData(location) {
      fetch(`/api/sensor/${location}`)
        .then(response => response.json())
        .then(data => {
          let dataHtml = `<h2>Sensor Data for ${location}</h2>`;
          data.forEach(sensorData => {
            dataHtml += `
              <p>Sensor: ${sensorData.sensor}</p>
              <p>Value: ${sensorData.value}</p>
              <p>Reading Time: ${sensorData.reading_time}</p>
            `;
          });
          weatherDataElement.innerHTML = dataHtml;
        })
        .catch(error => {
          console.error('Error fetching sensor data:', error);
          weatherDataElement.innerHTML = `<p>Failed to load sensor data.</p>`;
        });
    }
  
    fetchSensorData('kitchen');
  });
  