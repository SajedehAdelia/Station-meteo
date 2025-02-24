<?php
$conn = new mysqli("localhost", "root", "", "esp_database");
if ($conn->connect_error) {
    die("Erreur de connexion : " . $conn->connect_error);
}

$sql_sensors = "SELECT id, sensor, location, value, reading_time FROM SensorData ORDER BY id DESC";
$result_sensors = $conn->query($sql_sensors);

$sql_alerts = "SELECT id, sensor, location, value FROM Alertes ORDER BY id DESC";
$result_alerts = $conn->query($sql_alerts);

$sql_errors = "SELECT id, sensor, location, value FROM Erreurs ORDER BY id DESC";
$result_errors = $conn->query($sql_errors);
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
    <h2>📊 Données des capteurs</h2>
    <table>
        <tr>
            <th>ID</th>
            <th>Capteur</th>
            <th>Localisation</th>
            <th>Valeur</th>
            <th>Heure</th>
        </tr>
        <?php while ($row = $result_sensors->fetch_assoc()): ?>
        <tr>
            <td><?= htmlspecialchars($row['id']) ?></td>
            <td><?= htmlspecialchars($row['sensor']) ?></td>
            <td><?= htmlspecialchars($row['location']) ?></td>
            <td><?= htmlspecialchars($row['value']) ?></td>
            <td><?= htmlspecialchars($row['reading_time']) ?></td>
        </tr>
        <?php endwhile; ?>
    </table>

    <h2>🚨 Alertes</h2>
    <table class="alert">
        <tr>
            <th>ID</th>
            <th>Capteur</th>
            <th>Localisation</th>
            <th>Valeur</th>
        </tr>
        <?php while ($row = $result_alerts->fetch_assoc()): ?>
        <tr>
            <td><?= htmlspecialchars($row['id']) ?></td>
            <td><?= htmlspecialchars($row['sensor']) ?></td>
            <td><?= htmlspecialchars($row['location']) ?></td>
            <td><?= htmlspecialchars($row['value']) ?></td>
        </tr>
        <?php endwhile; ?>
    </table>

    <h2>❌ Erreurs</h2>
    <table class="error">
        <tr>
            <th>ID</th>
            <th>Capteur</th>
            <th>Localisation</th>
            <th>Valeur</th>
        </tr>
        <?php while ($row = $result_errors->fetch_assoc()): ?>
        <tr>
            <td><?= htmlspecialchars($row['id']) ?></td>
            <td><?= htmlspecialchars($row['sensor']) ?></td>
            <td><?= htmlspecialchars($row['location']) ?></td>
            <td><?= htmlspecialchars($row['value']) ?></td>
        </tr>
        <?php endwhile; ?>
    </table>
</div>

</body>
</html>
<?php $conn->close(); ?>