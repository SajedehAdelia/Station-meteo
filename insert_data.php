<?php
$host = "localhost";
$user = "root";
$password = "";
$dbname = "esp_database";

$conn = new mysqli($host, $user, $password, $dbname);
if ($conn->connect_error) {
    die("Connexion échouée : " . $conn->connect_error);
}

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $topic = $_POST["topic"];
    $value = $_POST["value"];

    $topic_parts = explode("/", $topic);

    if (count($topic_parts) < 3) {
        die("Format de topic invalide.");
    }

    $location = $topic_parts[1];
    $sensor = $topic_parts[2];

    if (isset($topic_parts[3])) {
        if ($topic_parts[3] == "alerte") {
            $stmt = $conn->prepare("INSERT INTO Alertes (sensor, location, value) VALUES (?, ?, ?)");
        } elseif ($topic_parts[3] == "erreur") {
            $stmt = $conn->prepare("INSERT INTO Erreurs (sensor, location, value) VALUES (?, ?, ?)");
        } else {
            die("Type de message inconnu.");
        }
    } else {
        $stmt = $conn->prepare("INSERT INTO SensorData (sensor, location, value) VALUES (?, ?, ?)");
    }

    $stmt->bind_param("ssd", $sensor, $location, $value);

    if ($stmt->execute()) {
        echo "Données insérées avec succès";
    } else {
        echo "Erreur d'insertion: " . $stmt->error;
    }

    $stmt->close();
    $conn->close();
} else {
    echo "Requête invalide";
}
?>
