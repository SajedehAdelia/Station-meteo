<?php
header("Access-Control-Allow-Origin: *");
header("Content-Type: application/json");

include 'config.php';

$sql = "SELECT sensor, location, value, reading_time 
        FROM erreurs
        ORDER BY location, sensor";
$result = $conn->query($sql);

$data = [];
while ($row = $result->fetch_assoc()) {
    $data[] = $row;
}

echo json_encode($data);
$conn->close();
?>
