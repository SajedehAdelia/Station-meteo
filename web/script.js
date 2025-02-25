async function fetchAndFormatData(url) {
  try {
      const response = await fetch(url);
      const data = await response.json();

      const formattedData = {};
      data.forEach(row => {
          const { location, sensor, value, reading_time } = row;

          if (!formattedData[location]) {
              formattedData[location] = {};
          }
          if (!formattedData[location][sensor]) {
              formattedData[location][sensor] = [];
          }

          formattedData[location][sensor].push({
              valeur: value,
              horodatage: reading_time
          });
      });

      return formattedData;

  } catch (error) {
      console.error("Erreur lors de la récupération des données :", error);
  }
}

async function loadDashboard() {
  const dashboard = document.getElementById('dashboard');

  const data = await fetchAndFormatData("http://localhost/get_data.php");

  Object.entries(data).forEach(([location, sensors]) => {
      const locationSection = document.createElement('div');
      locationSection.className = "location-section";
      locationSection.innerHTML = `<h2 class="location-title">${location}</h2>`;
      
      Object.entries(sensors).forEach(([sensor, readings]) => {
          const sensorTitle = document.createElement('h3');
          sensorTitle.className = "sensor-title";
          sensorTitle.textContent = `${sensor}`;
          
          const tableContainer = document.createElement('div');
          tableContainer.className = "table-container";

          const table = document.createElement('table');
          table.className = "sensor-table";
          table.innerHTML = `
              <thead>
                  <tr>
                      <th>Valeur</th>
                      <th>Horodatage</th>
                  </tr>
              </thead>
              <tbody>
                  ${readings.map(r => `<tr><td>${r.valeur}</td><td>${r.horodatage}</td></tr>`).join('')}
              </tbody>
          `;

          tableContainer.appendChild(table);
          locationSection.appendChild(sensorTitle);
          locationSection.appendChild(tableContainer);
      });

      dashboard.appendChild(locationSection);
  });
}

// Charger les données au démarrage
window.onload = loadDashboard;
