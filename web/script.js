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
        return {};
    }
}

async function loadDashboard() {
    const dashboard = document.getElementById('dashboard');
    dashboard.innerHTML = ''; // Nettoyage avant rechargement

    // Récupération des données
    const data = await fetchAndFormatData("http://localhost/get_data.php");
    const alertData = await fetchAndFormatData("http://localhost/get_alertes.php");
    const errorData = await fetchAndFormatData("http://localhost/get_erreurs.php");

    Object.entries(data).forEach(([location, sensors]) => {
        const locationSection = document.createElement('div');
        locationSection.className = "location-section";
        locationSection.innerHTML = `<h2 class="location-title">${location}</h2>`;

        // Affichage des capteurs
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

    // Générer les alertes et erreurs tout en bas
    generateAlertOrErrorTable(alertData, "📢 Alertes", "alert-section", "alert-table", "yellow");
    generateAlertOrErrorTable(errorData, "❌ Erreurs", "error-section", "error-table", "red");
}

function generateAlertOrErrorTable(data, title, sectionClass, tableClass, color) {
    let alertsContainer = document.getElementById('alerts-container');
    if (!alertsContainer) {
        alertsContainer = document.createElement('div');
        alertsContainer.id = "alerts-container";
        document.body.appendChild(alertsContainer); // Ajoute en bas de la page
    }

    const section = document.createElement('div');
    section.className = sectionClass;
    section.innerHTML = `<h2 class="location-title" style="color:${color}">${title}</h2>`;

    const tableContainer = document.createElement('div');
    tableContainer.className = "table-container";

    const table = document.createElement('table');
    table.className = `sensor-table ${tableClass}`;
    table.innerHTML = `
        <thead>
            <tr>
                <th>Localisation</th>
                <th>Capteur</th>
                <th>Valeur</th>
                <th>Horodatage</th>
            </tr>
        </thead>
        <tbody>
            ${Object.entries(data).map(([location, sensors]) =>
                Object.entries(sensors).map(([sensor, readings]) =>
                    readings.map(r => 
                        `<tr><td>${location}</td><td>${sensor}</td><td>${r.valeur}</td><td>${r.horodatage}</td></tr>`
                    ).join('')
                ).join('')
            ).join('')}
        </tbody>
    `;

    tableContainer.appendChild(table);
    section.appendChild(tableContainer);
    alertsContainer.appendChild(section);
}

// Charger les données au démarrage et rafraîchir toutes les 5 secondes
window.onload = loadDashboard;
