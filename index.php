<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Station Météo</title>
    <link rel="stylesheet" href="styles.css">
</head>
<body>
<script src="https://cdn.jsdelivr.net/npm/chart.js"></script>

<h2>📊 Dernières Valeurs par Localisation</h2>

<?php
$servername = "localhost";
$dbname = "esp_database";
$username = "root";
$password = ""; 

$conn = new mysqli($servername, $username, $password, $dbname);
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

$sql = "SELECT sensor, location, value, reading_time 
        FROM SensorData 
        WHERE (sensor, location, reading_time) IN (
            SELECT sensor, location, MAX(reading_time) 
            FROM SensorData 
            GROUP BY sensor, location
        )
        ORDER BY location, sensor";

$result = $conn->query($sql);

$localisation_data = [];

while ($row = $result->fetch_assoc()) {
    $localisation_data[$row["location"]][] = $row;
}

$conn->close();

foreach ($localisation_data as $location => $sensors) {
    echo "<h3>🌍 $location</h3>";
    echo "<table>
            <tr><th>Capteur</th><th>Valeur</th><th>Dernière Mise à Jour</th></tr>";
    
    foreach ($sensors as $sensor_data) {
        echo "<tr>
                <td>{$sensor_data['sensor']}</td>
                <td>{$sensor_data['value']}</td>
                <td>{$sensor_data['reading_time']}</td>
              </tr>";
    }
    echo "</table><br>";
}


?>

<h2>📈 Évolution des Valeurs</h2>

<canvas id="myChart"></canvas>

<script>
fetch("get_chart_data.php")
    .then(response => response.json())
    .then(data => {
        const ctx = document.getElementById('myChart').getContext('2d');
        new Chart(ctx, {
            type: 'line',
            data: {
                labels: data.timestamps,
                datasets: data.datasets
            }
        });
    });
</script>

</body>
</html>
