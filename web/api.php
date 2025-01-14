<?php
header("Content-Type: application/json; charset=UTF-8");

// Database connection settings
$dbHost = "mariadb"; // Docker service name for the database
$dbUser = "root"; // Database username
$dbPass = "7YKyE8R2AhKzswfN"; // Database password
$dbName = "Weather_Station"; // Name of the database

// Create a new database connection
$databaseConnection = new mysqli($dbHost, $dbUser, $dbPass, $dbName);

// Check if the connection was successful
if ($databaseConnection->connect_error) {
    sendResponseJson(["error" => "Connection failed: " . $databaseConnection->connect_error], 500);
    exit;
}

// Determine the HTTP request method (GET, POST, DELETE)
$requestMethod = $_SERVER['REQUEST_METHOD'];
switch ($requestMethod) {
    case 'GET':
        retrieveData($databaseConnection);
        break;
    case 'POST':
        addData($databaseConnection);
        break;
    case 'DELETE':
        removeData($databaseConnection);
        break;
    default:
        sendResponseJson(["error" => "Method not allowed."], 405);
        exit;
}

// Close the database connection
$databaseConnection->close();

// Function to handle GET requests
function retrieveData($databaseConnection) {
    $dataId = $_GET['id'] ?? null;

    // Prepare SQL query based on whether an ID is provided
    $query = $dataId ? "SELECT * FROM env WHERE id = ?" : "SELECT * FROM env ORDER BY timestamp DESC";
    $statement = $databaseConnection->prepare($query);
    
    if ($dataId) {
        $statement->bind_param("i", $dataId);
    }

    if ($statement->execute()) {
        $resultSet = $statement->get_result();
        $dataRows = $resultSet->fetch_all(MYSQLI_ASSOC);
        sendResponseJson(["data" => $dataRows]);
    } else {
        sendResponseJson(["error" => "Unable to fetch data."], 500);
    }
    $statement->close();
}

// Function to handle POST requests
function addData($databaseConnection) {
    $inputData = json_decode(file_get_contents('php://input'), true);

    // Validate the JSON input
    if (json_last_error() !== JSON_ERROR_NONE) {
        sendResponseJson(["error" => "Invalid JSON format: " . json_last_error_msg()], 400);
        exit;
    }

    // Ensure required fields are present in the input data
    if (!isset($inputData['temperature'], $inputData['humidity'], $inputData['light_level'])) {
        sendResponseJson(["error" => "Missing required fields: temperature, humidity, and light level."], 400);
        return;
    }

    // Prepare the insert SQL statement
    $insertQuery = "INSERT INTO env (temperature, humidity, light_level) VALUES (?, ?, ?)";
    $statement = $databaseConnection->prepare($insertQuery);
    $statement->bind_param("ddi", $inputData['temperature'], $inputData['humidity'], $inputData['light_level']);

    if ($statement->execute()) {
        sendResponseJson(["success" => "Data successfully inserted.", "id" => $statement->insert_id]);
    } else {
        sendResponseJson(["error" => "Failed to insert data."], 500);
    }
    $statement->close();
}

// Function to handle DELETE requests
function removeData($databaseConnection) {
    $dataId = $_GET['id'] ?? null;

    // Check if an ID is provided for deletion
    if (!$dataId) {
        sendResponseJson(["error" => "ID is required to delete the data."], 400);
        return;
    }

    // Prepare and execute the delete SQL statement
    $deleteQuery = "DELETE FROM env WHERE id = ?";
    $statement = $databaseConnection->prepare($deleteQuery);
    $statement->bind_param("i", $dataId);

    if ($statement->execute()) {
        sendResponseJson(["success" => "Data successfully deleted."]);
    } else {
        sendResponseJson(["error" => "Failed to delete data."], 500);
    }
    $statement->close();
}

// Function to send a JSON response
function sendResponseJson($response, $statusCode = 200) {
    http_response_code($statusCode);
    echo json_encode($response);
    exit;
}
?>