<?php
$host = "localhost";
$user = "root";
$password = "";
$database = "esp_database";

$conn = new mysqli($host, $user, $password, $database);
if ($conn->connect_error) {
    die("Échec de connexion: " . $conn->connect_error);
}
?>
