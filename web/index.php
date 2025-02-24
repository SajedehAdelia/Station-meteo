<?php
// Database connection
$conn = new mysqli("localhost", "root", "", "esp_database");
if ($conn->connect_error) {
    die("Erreur de connexion : " . $conn->connect_error);
}

function fetch_sensor_data($conn, $location) {
    $sql = "SELECT sensor, value, reading_time 
            FROM sensordata 
            WHERE location = '$location' 
            AND sensor IN ('temperature', 'light')
            ORDER BY reading_time DESC";
    return $conn->query($sql);
}

$result_cuisine = fetch_sensor_data($conn, 'cuisine');

$result_terrasse = fetch_sensor_data($conn, 'terrasse');

?>
<!DOCTYPE html>
<html lang="fr">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Station Météo</title>
    <link rel="stylesheet" href="styles.css">
</head>
<body>

<div class="container">
    <h2>🏠 Données des capteurs - Cuisine</h2>
    <table>
        <tr>
            <th>Capteur</th>
            <th>Valeur</th>
            <th>Heure</th>
        </tr>
        <?php while ($row = $result_cuisine->fetch_assoc()): ?>
        <tr>
            <td><?= htmlspecialchars($row['sensor']) ?></td>
            <td><?= htmlspecialchars($row['value']) ?></td>
            <td><?= htmlspecialchars($row['reading_time']) ?></td>
        </tr>
        <?php endwhile; ?>
    </table>

    <h2>🌿 Données des capteurs - Terrasse</h2>
    <table class="terrasse">
        <tr>
            <th>Capteur</th>
            <th>Valeur</th>
            <th>Heure</th>
        </tr>
        <?php while ($row = $result_terrasse->fetch_assoc()): ?>
        <tr>
            <td><?= htmlspecialchars($row['sensor']) ?></td>
            <td><?= htmlspecialchars($row['value']) ?></td>
            <td><?= htmlspecialchars($row['reading_time']) ?></td>
        </tr>
        <?php endwhile; ?>
    </table>
</div>

</body>
</html>
<?php $conn->close(); ?>
