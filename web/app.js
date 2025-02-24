document.addEventListener("DOMContentLoaded", function () {
    const weatherDataElement = document.getElementById("weather-data");
  
    // Fetch the weather data from the server
    fetch('/api/weather')
      .then(response => response.json())
      .then(data => {
        weatherDataElement.innerHTML = `
          <h2>Temperature: ${data.temperature}°C</h2>
          <p>Humidity: ${data.humidity}%</p>
          <p>Pressure: ${data.pressure} hPa</p>
        `;
      })
      .catch(error => {
        console.error('Error fetching weather data:', error);
      });
  });
  