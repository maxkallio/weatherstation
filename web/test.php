<?php

$host = 'mariadb'; 
$port = '3306'; 
$db = 'WeatherStation'; 
$user = 'root'; 
$pass = '7YKyE8R2AhKzswfN'; 

$conn = new mysqli($host, $user, $pass, $db, $port);

if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
} else {
    echo "Connected successfully to the database: $db<br>";
}

$sql = "SHOW TABLES";
$result = $conn->query($sql);

if ($result->num_rows > 0) {
    echo "Tables in database '$db':<br>";
    while($row = $result->fetch_array()) {
        echo $row[0] . "<br>"; 
    }
} else {
    echo "No tables found in database '$db'.";
}

// Close the connection
$conn->close();
?>
