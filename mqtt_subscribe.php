<?php
require_once __DIR__ . "/MQTT/phpMQTT.php";
    
if (class_exists("phpMQTT")) {
    echo "La classe phpMQTT est bien chargée !\n";
} else {
    echo "Erreur : la classe phpMQTT n'existe pas !\n";
}

$server = "192.168.231.95"; 
$port = 1883;
$client_id = "PHP_Subscriber_" . rand();

$mqtt = new phpMQTT($server, $port, $client_id);

if (!$mqtt->connect()) {
    die("Connexion au broker MQTT échouée.");
}

$topics["StationMeteoAdeliaLoanGaelMaxence/#"] = ["qos" => 0, "function" => "procMsg"];
$mqtt->subscribe($topics, 0);

function procMsg($topic, $message) {
    echo "Message reçu sur $topic : $message\n";

    $ch = curl_init("http://localhost/insert_data.php");
    curl_setopt($ch, CURLOPT_POST, 1);
    curl_setopt($ch, CURLOPT_POSTFIELDS, [
        "topic" => $topic,
        "value" => $message
    ]);

    curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);

    $response = curl_exec($ch);
    curl_close($ch);

    echo "Réponse de insert_data.php : $response\n";
}

while ($mqtt->proc()) {}

$mqtt->close();
?>
