<!DOCTYPE html>
<html>
<head>
    <title>Station Météo</title>
</head>
<body>

<h2>📊 Données des capteurs</h2>
<table border="1">
    <tr>
        <th>ID</th>
        <th>Capteur</th>
        <th>Localisation</th>
        <th>Valeur</th>
        <th>Heure</th>
    </tr>
    <?php
    $conn = new mysqli("localhost", "root", "", "esp_database");
    if ($conn->connect_error) {
        die("Erreur de connexion : " . $conn->connect_error);
    }

    $sql = "SELECT id, sensor, location, value, reading_time FROM SensorData ORDER BY id DESC";
    $result = $conn->query($sql);

    while ($row = $result->fetch_assoc()) {
        echo "<tr>
                <td>{$row['id']}</td>
                <td>{$row['sensor']}</td>
                <td>{$row['location']}</td>
                <td>{$row['value']}</td>
                <td>{$row['reading_time']}</td>
              </tr>";
    }

    $conn->close();
    ?>
</table>

<h2>🚨 Alertes</h2>
<table border="1">
    <tr>
        <th>ID</th>
        <th>Capteur</th>
        <th>Localisation</th>
        <th>Valeur</th>
    </tr>
    <?php
    $conn = new mysqli("localhost", "root", "", "esp_database");
    if ($conn->connect_error) {
        die("Erreur de connexion : " . $conn->connect_error);
    }

    $sql = "SELECT id, sensor, location, value FROM Alertes ORDER BY id DESC";
    $result = $conn->query($sql);

    while ($row = $result->fetch_assoc()) {
        echo "<tr>
                <td>{$row['id']}</td>
                <td>{$row['sensor']}</td>
                <td>{$row['location']}</td>
                <td>{$row['value']}</td>
              </tr>";
    }

    $conn->close();
    ?>
</table>

<h2>❌ Erreurs</h2>
<table border="1">
    <tr>
        <th>ID</th>
        <th>Capteur</th>
        <th>Localisation</th>
        <th>Valeur</th>
    </tr>
    <?php
    $conn = new mysqli("localhost", "root", "", "esp_database");
    if ($conn->connect_error) {
        die("Erreur de connexion : " . $conn->connect_error);
    }

    $sql = "SELECT id, sensor, location, value FROM Erreurs ORDER BY id DESC";
    $result = $conn->query($sql);

    while ($row = $result->fetch_assoc()) {
        echo "<tr>
                <td>{$row['id']}</td>
                <td>{$row['sensor']}</td>
                <td>{$row['location']}</td>
                <td>{$row['value']}</td>
              </tr>";
    }

    $conn->close();
    ?>
</table>

</body>
</html>
