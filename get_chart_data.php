<?php
$servername = "localhost";
$dbname = "esp_database";
$username = "root";
$password = ""; 

$conn = new mysqli($servername, $username, $password, $dbname);
if ($conn->connect_error) {
    die(json_encode(["error" => "Database connection failed"]));
}

$sql = "SELECT sensor, location, value, reading_time FROM SensorData ORDER BY reading_time DESC LIMIT 100";
$result = $conn->query($sql);

$data = [];
while ($row = $result->fetch_assoc()) {
    $data[$row["sensor"]]["label"] = $row["sensor"] . " - " . $row["location"];
    $data[$row["sensor"]]["data"][] = ["x" => $row["reading_time"], "y" => $row["value"]];
}

$response = [
    "timestamps" => array_values(array_unique(array_column($data, "reading_time"))),
    "datasets" => []
];

foreach ($data as $sensor => $sensorData) {
    $response["datasets"][] = [
        "label" => $sensorData["label"],
        "data" => $sensorData["data"],
        "borderColor" => "rgb(" . rand(0, 255) . "," . rand(0, 255) . "," . rand(0, 255) . ")",
        "fill" => false
    ];
}

$conn->close();

header('Content-Type: application/json');
echo json_encode($response);
?>
